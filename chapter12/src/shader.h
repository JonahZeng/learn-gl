#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    Shader() = delete;
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void use();
    void del();
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setMatrix4fv(const std::string &name, int matCnt, bool transpose, float* data) const;
private:
    unsigned int ID;
};

#endif