/**********************************
*  @description : 着色器
*  @author ：panl
*  @date : 2020.04.19
***********************************/

#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    // 1、读取着色器代码
    std::string vertexCode, fragmentCode;
    if (readShader(vertexPath, fragmentPath, vertexCode, fragmentCode))
    {
        // 2、编译着色器
        compileShader(vertexCode, fragmentCode);
    }
}

void Shader::use()
{
    glUseProgram(m_id);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()),value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

bool Shader::readShader(const GLchar* vertexPath, const GLchar* fragmentPath, std::string& vertexCode, std::string& fragmentCode)
{
    std::ifstream vertexShaderFile, fragmentShaderFile;
    // 确保文件流会会输出异常
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // 打开文件
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);
        std::stringstream vshaderStream, fshaderStream;
        // 读取文件到流中
        vshaderStream << vertexShaderFile.rdbuf();
        fshaderStream << fragmentShaderFile.rdbuf();
        // 关闭文件 
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // 将流转换为字符串
        vertexCode = vshaderStream.str();
        fragmentCode = fshaderStream.str();

        return true;
    }
    catch (std::ifstream::failure &e)
    {
        std::cout << "错误：读取文件失败，请检查文件是否存在！" << std::endl;
        return false;
    }
}

void Shader::compileShader(std::string& vertexCode, std::string& fragmentCode)
{
    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // 顶点着色器
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (0 == success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "编译顶点着色器失败，错误信息" << infoLog << std::endl;
    }

    // 片元着色器
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (0 == success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "编译片元着色器失败，错误信息" << infoLog << std::endl;
    }

    // 着色器程序
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (0 == success)
    {
        glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
        std::cout << "链接着色器程序失败，错误信息" << infoLog << std::endl;
    }

    // 删除着色器程序
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

