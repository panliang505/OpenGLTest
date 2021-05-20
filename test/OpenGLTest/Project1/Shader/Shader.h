/**********************************
*  @description : 着色器
*  @author ：panl
*  @date : 2020.04.19
***********************************/

#ifndef _SHADER_H_
#define _SHADER_H_

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
public:
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

    unsigned int getID() { return m_id; }

    // 使用着色器
    void use();
    // 设置uniform 变量
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, float value[]) const;

private:
    // 读取着色器代码
    bool readShader(const GLchar* vertexPath, const GLchar* fragmentPath, std::string& vertexCode, std::string& fragmentCode);
    // 编译着色器
    void compileShader(std::string& vertexCode, std::string& fragmentCode);

private:
    // 进程id
    unsigned int m_id;
};

#endif // !_SHADER_H_
