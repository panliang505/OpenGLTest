
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "GLFW\glfw3native.h"
#include <iostream>
#include "Part1\OpenGLPart1.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


/// 绘制一个窗口
int paintWindow();

/// 渲染三角形
int paintTriangle();
// 设置
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEGHT = 720;
// 定点着色代码
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";	//千万别忘记这个\0
// 片元着色器代码
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";	//千万别忘记这个\0
float vertices[] = {
    -0.5f, -0.5f, 0.0f,		//左
    0.5f, -0.5f, 0.0f,		//右
    0.0f, 0.5f, 0.0f		//上
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

// 绘制窗体
int paintWindow()
{
    
    glfwInit(); // 初始化glfw窗口
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // 指定OpenGL的主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // 指定OpenGL的子版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 使用OpenGL的核心模式（可编程渲染管道的模型）
    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEGHT, "LearnOpenGL", nullptr, nullptr);
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); // 出错则终止进程
        return -1;
    }
    // 将窗口的上下文环境设置为当前主线程的上下文环境
    glfwMakeContextCurrent(window);
    // 初始化glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // 注册窗口回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // 渲染循环
    while (!glfwWindowShouldClose(window)) // 检测是否关闭窗口
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

// 绘制三角形
int paintTriangle()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 创建窗口
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

    // 创建、编译着色器程序
    // 定点着色器
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // 片元着色器
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);  // 调整OpenGL视口区域
}

void processInput(GLFWwindow* window)
{
    // 检查Esc键是否按下
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        // 设置窗口关闭
        glfwSetWindowShouldClose(window, true);
    }
}
