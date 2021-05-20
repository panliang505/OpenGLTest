/**********************************
*  @description : ��ɫ��
*  @author ��panl
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

    // ʹ����ɫ��
    void use();
    // ����uniform ����
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, float value[]) const;

private:
    // ��ȡ��ɫ������
    bool readShader(const GLchar* vertexPath, const GLchar* fragmentPath, std::string& vertexCode, std::string& fragmentCode);
    // ������ɫ��
    void compileShader(std::string& vertexCode, std::string& fragmentCode);

private:
    // ����id
    unsigned int m_id;
};

#endif // !_SHADER_H_
