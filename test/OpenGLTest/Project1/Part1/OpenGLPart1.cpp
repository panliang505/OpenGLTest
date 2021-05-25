/**********************************
*  @description :
*  @author ：panl
*  @date : 2020.04.17
***********************************/

#include "OpenGLPart1.h"
#include <iostream>
#include "../Shader/Shader.h"

using namespace std;
using namespace OpenGLPart1;

// 定点着色代码
const char * CPaintBase::m_vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n" 
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";	//千万别忘记这个\0

// 片元着色器代码
const char * CPaintBase::m_fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
//"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"	FragColor = ourColor;\n"
"}\0";	//千万别忘记这个\0

// 片元着色器1代码
const char * CPaintBase::m_fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.0f, 0.1f, 1.0f);\n"
"}\0";	//千万别忘记这个\0

void CPaintBase::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);  // 调整OpenGL视口区域
}

void CPaintBase::processInput(GLFWwindow* window)
{
    // 检查Esc键是否按下
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        // 设置窗口关闭
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
    glfwInit(); // 初始化glfw窗口
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // 指定OpenGL的主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // 指定OpenGL的子版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 使用OpenGL的核心模式（可编程渲染管道的模型）
    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (nullptr == window)
    {
        cout << "Failed to create GLFW window." << endl;
        glfwTerminate(); // 出错则终止进程
        return -1;
    }
    // 将窗口的上下文环境设置为当前线程的上下文环境
    glfwMakeContextCurrent(window);
    // 初始化glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD." << endl;
        return -1;
    }
    // 注册窗口回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        processInput(window); // 处理输入事件

        // 渲染
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f); // 设置清屏颜色（黄色）
        glClear(GL_COLOR_BUFFER_BIT);         // 清屏
        // 将显示缓存和离屏缓存交互（显示离屏缓存中的内容）
        glfwSwapBuffers(window);
        // 检查是否有事件触发（例如鼠标输入和键盘输入事件）
        glfwPollEvents();
    }
    glfwTerminate(); // 终止进程
    return 0;
}


const float CPaintTriangle::m_vertices[9] = {
    -0.5f, -0.5f, 0.0f,		//左
    0.5f, -0.5f, 0.0f,		//右
    0.0f, 0.5f, 0.0f		//上
};
// 片元着色器代码
const char * CPaintTriangle::m_selfFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
//"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"	FragColor = ourColor;\n"
"}\0";	//千万别忘记这个\0

int CPaintTriangle::paintTriangle()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 创建窗口
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

    // 创建、编译着色器程序
    // 定点着色器
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &m_vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // 片元着色器
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

    // 链接着色器
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // 别忘了释放着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int vBo, vAo;
    glGenVertexArrays(1, &vAo);
    glBindVertexArray(vAo);

    // 顶点缓存对象
    glGenBuffers(1, &vBo); // 生成唯一ID
    glBindBuffer(GL_ARRAY_BUFFER, vBo); // 指定为顶点缓存对象
    /**
    * typedef void (APIENTRYP PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
    * GLAPI PFNGLBUFFERDATAPROC glad_glBufferData;
    * #define glBufferData glad_glBufferData
    * 将顶点数据复制到vbo
    * para 1: 我们的顶点数据需要拷贝到的地方（之前绑定的vbo）
    * para 2: 数组的大小
    * para 3: 数组的地址
    * para 4: 指定显卡要采用什么方式来管理我们的数据，GL_STATIC_DRAW表示这些数据不会经常改变
    **/
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    /**
    * typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
    * GLAPI PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer;
    * #define glVertexAttribPointer glad_glVertexAttribPointer
    * #endif
    * 指明顶点格式
    * para 1: 指明我们想要配置的顶点属性
    * para 1: 顶点属性的大小。我们用到的顶点是一个vec3的结果，所以大小为3
    * para 3: 数据的类型
    * para 4: 指明数据是否要被规范化
    * para 5: 表示属性的跨度
    * para 6: 指明了数据的起始偏移量
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
        * 这里是一个习惯，上面的操作把属性都保存到了VAO中，这里只需要绑定就可以
        * 如果要显示的东西不同，也只需要在这里绑定不同的东西就可以显示
        */
        glBindVertexArray(vAo);
        // 绘制三角形 (0表示顶点数组的起始索引，3表示有3个顶点)
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vBo);
    glfwTerminate();
    return 0;
}


const float CPaintTriangles::m_vertices[18] = {
    -0.5f, -0.5f, 0.0f,		//左
    0.5f, -0.5f, 0.0f,		//右
    0.0f, 0.5f, 0.0f,		//上
    1.0f, 0.0f, 0.0f,
    0.75f, 0.5f, 0.0f,
    0.5f, 0.0f, 0.0f
};
const float CPaintTriangles::m_rectVertices[12] = {
    0.5f, 0.5f, 0.0f,		//右上角
    0.5f, -0.5f, 0.0f,		//右下角
    -0.5f, -0.5f, 0.0f,		//左下角
    -0.5f, 0.5f, 0.0f		//左上角
};
const uint_t CPaintTriangles::m_indices[6] = {
    0, 1, 3,		//第一个三角形
    1, 2, 3			//第二个三角形
};

int CPaintTriangles::paintTriangles(PaintType paintType)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 创建窗口
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

    // 创建、编译着色器程序
    // 定点着色器
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &m_vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // 片元着色器
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &m_fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // 链接着色器
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // 片元着色器1
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

    // 别忘了释放着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    uint_t vBo, vAo;
    glGenVertexArrays(1, &vAo);
    glBindVertexArray(vAo);

    // 顶点缓存对象
    glGenBuffers(1, &vBo); // 生成唯一ID
    glBindBuffer(GL_ARRAY_BUFFER, vBo); // 指定为顶点缓存对象
    switch (paintType)
    {
    case CPaintTriangles::SameRGBTriangles:
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
        break;

    case CPaintTriangles::Triangles:
        // 第一个环境
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
        // 第二个环境
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
    //位置				//颜色
    -0.5f, -0.5f, 0.0f, //1.0f, 0.0f, 0.0f,		//左
    0.5f, -0.5f, 0.0f,	//0.0f, 1.0f, 0.0f,		//右
    0.0f, 0.5f, 0.0f//,	0.0f, 0.0f, 1.0f		//上
};
int ShaderCase::paintTriangle()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 创建窗口
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

    // 获取最大属性数量
    int attributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributes);
    std::cout << "最大支持的属性数量为：" << attributes << std::endl;

    // 创造着色器
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
    //位置					// 颜色					//纹理坐标
    0.5f,	0.5f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f,	1.0f,	//右上角
    0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,	0.0f,	//右下角
    -0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	//左下角
    -0.5f,	0.5f,	0.0f,	1.0f,	1.0f,	0.0f,	0.0f,	1.0f	//左上角

};
const int TextureCase::m_indices[6] = {
    0, 1, 3,		//第一个三角形
    1, 2, 3			//第二个三角形
};
#define STB_IMAGE_IMPLEMENTATION
#include "../thirdpart/stb_image.h"
int TextureCase::paintTexture()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 创建窗口
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

    // 获取最大属性数量
    int attributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributes);
    std::cout << "最大支持的属性数量为：" << attributes << std::endl;

    // 创造着色器
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

    // 纹理
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 设置纹理包装和过滤的方式
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
        std::cout << "无法加载问题， 请检查代码或资源是否有误。" << std::endl;
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
    // 创建窗口
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

    // 获取最大属性数量
    int attributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributes);
    std::cout << "最大支持的属性数量为：" << attributes << std::endl;

    // 创造着色器
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

    // 纹理1
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 设置纹理包装和过滤的方式
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
        std::cout << "无法加载问题， 请检查代码或资源是否有误。" << std::endl;
    }
    stbi_image_free(data);

    // 纹理2
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // 设置纹理包装和过滤的方式
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
        std::cout << "无法加载问题， 请检查代码或资源是否有误。" << std::endl;
    }
    stbi_image_free(data2);

    //告诉OpenGL哪个采样器属于哪个纹理单元
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

    // 获取最大属性数量
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    cout << "最大支持的属性数量为：" << nrAttributes << endl;

    // 创建着色器
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

    // 纹理1
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 设置纹理包装和过滤的方式
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
        std::cout << "无法加载问题， 请检查代码或资源是否有误。" << std::endl;
    }
    stbi_image_free(data);

    // 纹理2
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // 设置纹理包装和过滤的方式
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
        std::cout << "无法加载问题， 请检查代码或资源是否有误。" << std::endl;
    }
    stbi_image_free(data2);

    //告诉OpenGL哪个采样器属于哪个纹理单元
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    // 旋转
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

    //获取最大属性数量
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "support max attributes:" << nrAttributes << std::endl;

    glEnable(GL_DEPTH_TEST);

    // 创建着色器
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

    // 纹理1
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 设置纹理包装和过滤的方式
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
        std::cout << "无法加载问题， 请检查代码或资源是否有误。" << std::endl;
    }
    stbi_image_free(data);

    // 纹理2
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // 设置纹理包装和过滤的方式
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
        std::cout << "无法加载问题， 请检查代码或资源是否有误。" << std::endl;
    }
    stbi_image_free(data2);

    //告诉OpenGL哪个采样器属于哪个纹理单元
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
