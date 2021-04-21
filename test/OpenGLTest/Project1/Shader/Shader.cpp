/**********************************
*  @description : ��ɫ��
*  @author ��panl
*  @date : 2020.04.19
***********************************/

#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    // 1����ȡ��ɫ������
    std::string vertexCode, fragmentCode;
    if (readShader(vertexPath, fragmentPath, vertexCode, fragmentCode))
    {
        // 2��������ɫ��
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
    // ȷ���ļ����������쳣
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // ���ļ�
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);
        std::stringstream vshaderStream, fshaderStream;
        // ��ȡ�ļ�������
        vshaderStream << vertexShaderFile.rdbuf();
        fshaderStream << fragmentShaderFile.rdbuf();
        // �ر��ļ� 
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // ����ת��Ϊ�ַ���
        vertexCode = vshaderStream.str();
        fragmentCode = fshaderStream.str();

        return true;
    }
    catch (std::ifstream::failure &e)
    {
        std::cout << "���󣺶�ȡ�ļ�ʧ�ܣ������ļ��Ƿ���ڣ�" << std::endl;
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

    // ������ɫ��
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (0 == success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "���붥����ɫ��ʧ�ܣ�������Ϣ" << infoLog << std::endl;
    }

    // ƬԪ��ɫ��
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (0 == success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "����ƬԪ��ɫ��ʧ�ܣ�������Ϣ" << infoLog << std::endl;
    }

    // ��ɫ������
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (0 == success)
    {
        glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
        std::cout << "������ɫ������ʧ�ܣ�������Ϣ" << infoLog << std::endl;
    }

    // ɾ����ɫ������
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

