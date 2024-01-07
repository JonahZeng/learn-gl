#include "shader.h"
#include <QDebug>

Shader::Shader(const char *vertexPath, const char *fragmentPath, QOpenGLFunctions *fp): f(fp)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();       

        vShaderFile.close();
        fShaderFile.close();

        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();     
    }
    catch(std::ifstream::failure e)
    {
        qDebug() << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ";
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    int success;
    char infoLog[512];

    unsigned int vertex = f->glCreateShader(GL_VERTEX_SHADER);
    f->glShaderSource(vertex, 1, &vShaderCode, NULL);
    f->glCompileShader(vertex);
    f->glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        f->glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog;
    }

    unsigned int fragment = f->glCreateShader(GL_FRAGMENT_SHADER);
    f->glShaderSource(fragment, 1, &fShaderCode, NULL);
    f->glCompileShader(fragment);
    f->glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        f->glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog;
    }

    shaderID = f->glCreateProgram();
    f->glAttachShader(shaderID, vertex);
    f->glAttachShader(shaderID, fragment);
    f->glLinkProgram(shaderID);

    f->glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if (!success)
    {
        f->glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog;
    }

    f->glDeleteShader(vertex);
    f->glDeleteShader(fragment);
}

Shader::~Shader()
{
    if(shaderID)
    {
        f->glDeleteProgram(shaderID);
        shaderID = 0;
    }
}

void Shader::use()
{
    if(shaderID)
        f->glUseProgram(shaderID);
}

void Shader::del()
{
    if(shaderID)
    {
        f->glDeleteProgram(shaderID);
        shaderID = 0;
    }
}

void Shader::setBool(const std::string &name, bool value) const
{
    GLint loc = f->glGetUniformLocation(shaderID, name.c_str());
    f->glUniform1i(loc, (int)value); 
}

void Shader::setInt(const std::string &name, int value) const
{
    GLint loc = f->glGetUniformLocation(shaderID, name.c_str());
    f->glUniform1i(loc, value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    GLint loc = f->glGetUniformLocation(shaderID, name.c_str());
    f->glUniform1f(loc, value);
}

void Shader::setMatrix4fv(const std::string &name, int matCnt, bool transpose, float* data) const
{
    GLint loc = f->glGetUniformLocation(shaderID, name.c_str());
    f->glUniformMatrix4fv(loc, 1, GL_FALSE, data);
}