#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <QOpenGLFunctions>

class Shader
{
public:
    Shader() = delete;
    Shader(const char* vertexPath, const char* fragmentPath, QOpenGLFunctions *fp);
    ~Shader();
    void use();
    void del();
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
private:
    GLuint shaderID;
    QOpenGLFunctions *f;
};

#endif