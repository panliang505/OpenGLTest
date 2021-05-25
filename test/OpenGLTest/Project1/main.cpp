
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "GLFW\glfw3native.h"
#include <iostream>
#include "Part1\OpenGLPart1.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


/// ����һ������
int paintWindow();

/// ��Ⱦ������
int paintTriangle();
// ����
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEGHT = 720;
// ������ɫ����
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";	//ǧ����������\0
// ƬԪ��ɫ������
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";	//ǧ����������\0
float vertices[] = {
    -0.5f, -0.5f, 0.0f,		//��
    0.5f, -0.5f, 0.0f,		//��
    0.0f, 0.5f, 0.0f		//��
};


int main()
{
    //OpenGLPart1::CPaintWindow paintWin;
    //return paintWin.paintWindow();
    //return paintWindow();
    
    //OpenGLPart1::CPaintTriangle paintTria;
    //return paintTria.paintTriangle();
    //return paintTriangle();

    //OpenGLPart1::CPaintTriangles paintTrias;
    //paintTrias.paintTriangle();
    //paintTrias.paintTriangles(OpenGLPart1::CPaintTriangles::PaintType::SameTriangles);
    //paintTrias.paintTriangles(OpenGLPart1::CPaintTriangles::PaintType::SameRGBTriangles);
    //return paintTrias.paintTriangles(OpenGLPart1::CPaintTriangles::PaintType::Triangles);

    /*OpenGLPart1::ShaderCase shaderCase;
    return shaderCase.paintTriangle();*/

    //OpenGLPart1::TextureCase textureCase;
    //return textureCase.paintTexture();
    //return textureCase.paintDiffTexture();

    //OpenGLPart1::CoordinateTransf coordinateTransf;
    //coordinateTransf.paintTransTexture();

    OpenGLPart1::Show3DCube threaddCube;
    threaddCube.show3DCube(10);

    return 0;
}

// ���ƴ���
int paintWindow()
{
    
    glfwInit(); // ��ʼ��glfw����
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // ָ��OpenGL�����汾��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // ָ��OpenGL���Ӱ汾��
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // ʹ��OpenGL�ĺ���ģʽ���ɱ����Ⱦ�ܵ���ģ�ͣ�
    // ��������
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEGHT, "LearnOpenGL", nullptr, nullptr);
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); // ��������ֹ����
        return -1;
    }
    // �����ڵ������Ļ�������Ϊ��ǰ���̵߳������Ļ���
    glfwMakeContextCurrent(window);
    // ��ʼ��glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // ע�ᴰ�ڻص�����
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // ��Ⱦѭ��
    while (!glfwWindowShouldClose(window)) // ����Ƿ�رմ���
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

// ����������
int paintTriangle()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // ��������
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEGHT, "LearnOpenGL", nullptr, nullptr);
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
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // ƬԪ��ɫ��
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);  // ����OpenGL�ӿ�����
}

void processInput(GLFWwindow* window)
{
    // ���Esc���Ƿ���
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        // ���ô��ڹر�
        glfwSetWindowShouldClose(window, true);
    }
}
