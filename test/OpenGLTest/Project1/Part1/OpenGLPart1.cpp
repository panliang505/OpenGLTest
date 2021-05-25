/**********************************
*  @description :
*  @author ��panl
*  @date : 2020.04.17
***********************************/

#include "OpenGLPart1.h"
#include <iostream>
#include "../Shader/Shader.h"

using namespace std;
using namespace OpenGLPart1;

// ������ɫ����
const char * CPaintBase::m_vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n" 
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";	//ǧ����������\0

// ƬԪ��ɫ������
const char * CPaintBase::m_fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
//"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"	FragColor = ourColor;\n"
"}\0";	//ǧ����������\0

// ƬԪ��ɫ��1����
const char * CPaintBase::m_fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.0f, 0.1f, 1.0f);\n"
"}\0";	//ǧ����������\0

void CPaintBase::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);  // ����OpenGL�ӿ�����
}

void CPaintBase::processInput(GLFWwindow* window)
{
    // ���Esc���Ƿ���
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        // ���ô��ڹر�
        glfwSetWindowShouldClose(window, true);
    }
}

#include <Windows.h>
std::string CPaintBase::getProgramDir()
{
    char exeFullPath[MAX_PATH];
    std::string strPath = "";
    GetModuleFileNameA(nullptr, exeFullPath, MAX_PATH);
    strPath = (std::string)exeFullPath;
    int pos = strPath.find_last_of('\\', strPath.length());
    return strPath.substr(0, pos);
}


int CPaintWindow::paintWindow()
{
    glfwInit(); // ��ʼ��glfw����
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // ָ��OpenGL�����汾��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // ָ��OpenGL���Ӱ汾��
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // ʹ��OpenGL�ĺ���ģʽ���ɱ����Ⱦ�ܵ���ģ�ͣ�
    // ��������
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (nullptr == window)
    {
        cout << "Failed to create GLFW window." << endl;
        glfwTerminate(); // ��������ֹ����
        return -1;
    }
    // �����ڵ������Ļ�������Ϊ��ǰ�̵߳������Ļ���
    glfwMakeContextCurrent(window);
    // ��ʼ��glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD." << endl;
        return -1;
    }
    // ע�ᴰ�ڻص�����
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // ��Ⱦѭ��
    while (!glfwWindowShouldClose(window))
    {
        processInput(window); // ���������¼�

        // ��Ⱦ
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f); // ����������ɫ����ɫ��
        glClear(GL_COLOR_BUFFER_BIT);         // ����
        // ����ʾ������������潻������ʾ���������е����ݣ�
        glfwSwapBuffers(window);
        // ����Ƿ����¼������������������ͼ��������¼���
        glfwPollEvents();
    }
    glfwTerminate(); // ��ֹ����
    return 0;
}


const float CPaintTriangle::m_vertices[9] = {
    -0.5f, -0.5f, 0.0f,		//��
    0.5f, -0.5f, 0.0f,		//��
    0.0f, 0.5f, 0.0f		//��
};
// ƬԪ��ɫ������
const char * CPaintTriangle::m_selfFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
//"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"	FragColor = ourColor;\n"
"}\0";	//ǧ����������\0

int CPaintTriangle::paintTriangle()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // ��������
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ������������ɫ������
    // ������ɫ��
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &m_vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // ƬԪ��ɫ��
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &m_selfFragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    int success;
    char infoLog[512] = { 0 };
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (0 == success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "Failed to get shaderiv." << std::endl;
        return -1;
    }

    // ������ɫ��
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // �������ͷ���ɫ��
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int vBo, vAo;
    glGenVertexArrays(1, &vAo);
    glBindVertexArray(vAo);

    // ���㻺�����
    glGenBuffers(1, &vBo); // ����ΨһID
    glBindBuffer(GL_ARRAY_BUFFER, vBo); // ָ��Ϊ���㻺�����
    /**
    * typedef void (APIENTRYP PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
    * GLAPI PFNGLBUFFERDATAPROC glad_glBufferData;
    * #define glBufferData glad_glBufferData
    * ���������ݸ��Ƶ�vbo
    * para 1: ���ǵĶ���������Ҫ�������ĵط���֮ǰ�󶨵�vbo��
    * para 2: ����Ĵ�С
    * para 3: ����ĵ�ַ
    * para 4: ָ���Կ�Ҫ����ʲô��ʽ���������ǵ����ݣ�GL_STATIC_DRAW��ʾ��Щ���ݲ��ᾭ���ı�
    **/
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    /**
    * typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
    * GLAPI PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer;
    * #define glVertexAttribPointer glad_glVertexAttribPointer
    * #endif
    * ָ�������ʽ
    * para 1: ָ��������Ҫ���õĶ�������
    * para 1: �������ԵĴ�С�������õ��Ķ�����һ��vec3�Ľ�������Դ�СΪ3
    * para 3: ���ݵ�����
    * para 4: ָ�������Ƿ�Ҫ���淶��
    * para 5: ��ʾ���ԵĿ��
    * para 6: ָ�������ݵ���ʼƫ����
    **/
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float outColor[] = {0.5f, 0.5f, 0.5f, 1.0f};
        int outColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(outColorLocation, outColor[0], outColor[1], outColor[2], outColor[3]);
        //glUniform4fv(outColorLocation, 4, reinterpret_cast<const GLfloat*>(&outColor));

        glUseProgram(shaderProgram);

        /*
        * ������һ��ϰ�ߣ�����Ĳ��������Զ����浽��VAO�У�����ֻ��Ҫ�󶨾Ϳ���
        * ���Ҫ��ʾ�Ķ�����ͬ��Ҳֻ��Ҫ������󶨲�ͬ�Ķ����Ϳ�����ʾ
        */
        glBindVertexArray(vAo);
        // ���������� (0��ʾ�����������ʼ������3��ʾ��3������)
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vBo);
    glfwTerminate();
    return 0;
}


const float CPaintTriangles::m_vertices[18] = {
    -0.5f, -0.5f, 0.0f,		//��
    0.5f, -0.5f, 0.0f,		//��
    0.0f, 0.5f, 0.0f,		//��
    1.0f, 0.0f, 0.0f,
    0.75f, 0.5f, 0.0f,
    0.5f, 0.0f, 0.0f
};
const float CPaintTriangles::m_rectVertices[12] = {
    0.5f, 0.5f, 0.0f,		//���Ͻ�
    0.5f, -0.5f, 0.0f,		//���½�
    -0.5f, -0.5f, 0.0f,		//���½�
    -0.5f, 0.5f, 0.0f		//���Ͻ�
};
const uint_t CPaintTriangles::m_indices[6] = {
    0, 1, 3,		//��һ��������
    1, 2, 3			//�ڶ���������
};

int CPaintTriangles::paintTriangles(PaintType paintType)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // ��������
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ������������ɫ������
    // ������ɫ��
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &m_vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // ƬԪ��ɫ��
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &m_fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // ������ɫ��
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // ƬԪ��ɫ��1
    int shaderProgram1 = glCreateProgram();
    if (CPaintTriangles::Triangles == paintType)
    {
        int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader1, 1, &m_fragmentShaderSource1, nullptr);
        glCompileShader(fragmentShader1);

        glAttachShader(shaderProgram1, vertexShader);
        glAttachShader(shaderProgram1, fragmentShader1);
        glLinkProgram(shaderProgram1);

        glDeleteShader(fragmentShader1);
    }

    // �������ͷ���ɫ��
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    uint_t vBo, vAo;
    glGenVertexArrays(1, &vAo);
    glBindVertexArray(vAo);

    // ���㻺�����
    glGenBuffers(1, &vBo); // ����ΨһID
    glBindBuffer(GL_ARRAY_BUFFER, vBo); // ָ��Ϊ���㻺�����
    switch (paintType)
    {
    case CPaintTriangles::SameRGBTriangles:
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
        break;

    case CPaintTriangles::Triangles:
        // ��һ������
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices) / 2, m_vertices, GL_STATIC_DRAW);
        break;

    case CPaintTriangles::SameTriangles:
    default:
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_rectVertices), m_rectVertices, GL_STATIC_DRAW);
        break;
    }
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    uint_t vBo1, vAo1;
    switch (paintType)
    {
    case CPaintTriangles::SameRGBTriangles:
        break;

    case CPaintTriangles::Triangles:
        // �ڶ�������
        glGenVertexArrays(1, &vAo1);
        glBindVertexArray(vAo1);

        glGenBuffers(1, &vBo1);
        glBindBuffer(GL_ARRAY_BUFFER, vBo1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices) / 2, m_vertices + 9, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);
        break;

    case CPaintTriangles::SameTriangles:
    default:
        uint_t eBo;
        glGenBuffers(1, &eBo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eBo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);
        break;
    }

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(vAo);
        switch (paintType)
        {
        case CPaintTriangles::SameRGBTriangles:
            glDrawArrays(GL_TRIANGLES, 0, 6);
            break;

        case CPaintTriangles::Triangles:
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glUseProgram(shaderProgram1);
            glBindVertexArray(vAo1);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            break;

        case CPaintTriangles::SameTriangles:
        default:
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            break;
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vBo);
    glfwTerminate();
    return 0;
}


const float ShaderCase::m_vertices[9] = {
    //λ��				//��ɫ
    -0.5f, -0.5f, 0.0f, //1.0f, 0.0f, 0.0f,		//��
    0.5f, -0.5f, 0.0f,	//0.0f, 1.0f, 0.0f,		//��
    0.0f, 0.5f, 0.0f//,	0.0f, 0.0f, 1.0f		//��
};
int ShaderCase::paintTriangle()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // ��������
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ��ȡ�����������
    int attributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributes);
    std::cout << "���֧�ֵ���������Ϊ��" << attributes << std::endl;

    // ������ɫ��
    std::string path = getProgramDir();
    std::string vertexPath = path + "\\Shader.vs";
    std::string fragmentPath = path + "\\Shader.fs";
    Shader shader(vertexPath.c_str(), fragmentPath.c_str());

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

const float TextureCase::m_vertices[32] = {
    //λ��					// ��ɫ					//��������
    0.5f,	0.5f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f,	1.0f,	//���Ͻ�
    0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,	0.0f,	//���½�
    -0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	//���½�
    -0.5f,	0.5f,	0.0f,	1.0f,	1.0f,	0.0f,	0.0f,	1.0f	//���Ͻ�

};
const int TextureCase::m_indices[6] = {
    0, 1, 3,		//��һ��������
    1, 2, 3			//�ڶ���������
};
#define STB_IMAGE_IMPLEMENTATION
#include "../thirdpart/stb_image.h"
int TextureCase::paintTexture()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // ��������
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ��ȡ�����������
    int attributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributes);
    std::cout << "���֧�ֵ���������Ϊ��" << attributes << std::endl;

    // ������ɫ��
    std::string path = getProgramDir();
    std::string vertexPath = path + "\\TextureShader.vs";
    std::string fragmentPath = path + "\\TextureShader.fs";
    Shader shader(vertexPath.c_str(), fragmentPath.c_str());

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

    // ����
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // ���������װ�͹��˵ķ�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    std::string filePath = path + "\\beauty.jpg";
    //std::string filePath = path + "\\1.bmp";
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "�޷��������⣬ ����������Դ�Ƿ�����" << std::endl;
    }
    stbi_image_free(data);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

float factor = 0.2f;
int TextureCase::paintDiffTexture()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // ��������
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ��ȡ�����������
    int attributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributes);
    std::cout << "���֧�ֵ���������Ϊ��" << attributes << std::endl;

    // ������ɫ��
    std::string path = getProgramDir();
    std::string vertexPath = path + "\\Shader_6.1.vs";
    std::string fragmentPath = path + "\\Shader_6.1.fs";
    Shader shader(vertexPath.c_str(), fragmentPath.c_str());

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

    // ����1
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // ���������װ�͹��˵ķ�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    std::string filePath = path + "\\1.bmp";
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (data)
    {
        GLint format = channels == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "�޷��������⣬ ����������Դ�Ƿ�����" << std::endl;
    }
    stbi_image_free(data);

    // ����2
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // ���������װ�͹��˵ķ�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    std::string filePath2 = path + "\\1.png";
    unsigned char* data2 = stbi_load(filePath2.c_str(), &width, &height, &channels, 0);
    if (data2)
    {
        GLint format = channels == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "�޷��������⣬ ����������Դ�Ƿ�����" << std::endl;
    }
    stbi_image_free(data2);

    //����OpenGL�ĸ������������ĸ�����Ԫ
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    while (!glfwWindowShouldClose(window))
    {
        processInput2(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        shader.use();
        shader.setFloat("factor", factor);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

void TextureCase::processInput2(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        factor += 0.01f;
        std::cout << "factor:" << factor << std::endl;
        if (factor > 1.0f)
            factor = 1.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        factor -= 0.01f;
        std::cout << "factor:" << factor << std::endl;
        if (factor < 0.0f)
            factor = 0.0f;
    }
}


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
int CoordinateTransf::paintTransTexture()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (nullptr == window)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // ��ȡ�����������
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    cout << "���֧�ֵ���������Ϊ��" << nrAttributes << endl;

    // ������ɫ��
    std::string path = getProgramDir();
    std::string vertexPath = path + "\\Shader_7.vs";
    std::string fragmentPath = path + "\\Shader_6.1.fs";
    Shader shader(vertexPath.c_str(), fragmentPath.c_str());

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

    // ����1
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // ���������װ�͹��˵ķ�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    std::string filePath = path + "\\beauty.jpg";
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (data)
    {
        GLint format = channels == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "�޷��������⣬ ����������Դ�Ƿ�����" << std::endl;
    }
    stbi_image_free(data);

    // ����2
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // ���������װ�͹��˵ķ�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    std::string filePath2 = path + "\\awesomeface.png";
    unsigned char* data2 = stbi_load(filePath2.c_str(), &width, &height, &channels, 0);
    if (data2)
    {
        GLint format = channels == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "�޷��������⣬ ����������Դ�Ƿ�����" << std::endl;
    }
    stbi_image_free(data2);

    //����OpenGL�ĸ������������ĸ�����Ԫ
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    // ��ת
    glm::mat4 trans;
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

    while (!glfwWindowShouldClose(window))
    {
        processInput2(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glm::mat4 trans;
        trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        shader.use();
        shader.setMat4("transform", glm::value_ptr(trans));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

const float Show3DCube::m_vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

const glm::vec3 gcubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)
};

int Show3DCube::show3DCube(int cubeSize /*= 1*/)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //��ȡ�����������
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "support max attributes:" << nrAttributes << std::endl;

    glEnable(GL_DEPTH_TEST);

    // ������ɫ��
    std::string path = getProgramDir();
    std::string vertexPath = path + "\\Shader_8.vs";
    std::string fragmentPath = path + "\\Shader_6.fs";
    Shader shader(vertexPath.c_str(), fragmentPath.c_str());

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // ����1
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // ���������װ�͹��˵ķ�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    std::string filePath = path + "\\beauty.jpg";
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (data)
    {
        GLint format = channels == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB/*format*/, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "�޷��������⣬ ����������Դ�Ƿ�����" << std::endl;
    }
    stbi_image_free(data);

    // ����2
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // ���������װ�͹��˵ķ�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    std::string filePath2 = path + "\\awesomeface.png";
    unsigned char* data2 = stbi_load(filePath2.c_str(), &width, &height, &channels, 0);
    if (data2)
    {
        GLint format = channels == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA/*format*/, width, height, 0, format, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "�޷��������⣬ ����������Դ�Ƿ�����" << std::endl;
    }
    stbi_image_free(data2);

    //����OpenGL�ĸ������������ĸ�����Ԫ
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    glm::mat4 view;
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        shader.use();
        shader.setMat4("view", glm::value_ptr(view));
        shader.setMat4("projection", glm::value_ptr(projection));

        glBindVertexArray(VAO);
        for (int i = 0; i < cubeSize; ++i)
        {
            glm::mat4 model;
            model = glm::translate(model, gcubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMat4("model", glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}
