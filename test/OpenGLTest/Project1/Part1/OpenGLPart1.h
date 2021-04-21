/**********************************
*  @description :  
*  @author ：panl 
*  @date : 2020.04.17
***********************************/

#ifndef _OPENGLPART_H_
#define _OPENGLPART_H_

#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "GLFW\glfw3native.h"
#include <functional>

class Shader;

namespace OpenGLPart1
{
    const unsigned int SCR_WIDTH = 1280;
    const unsigned int SCR_HEIGHT = 720;

    using frameBufferCallback = std::function<void(GLFWwindow* window, int width, int height)>;
    class CPaintBase
    {
    protected:
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void processInput(GLFWwindow* window);
        
        std::string getProgramDir();

    protected:
        static const char * m_vertexShaderSource;
        static const char * m_fragmentShaderSource;
        static const char * m_fragmentShaderSource1;
    };

    // 绘制一个窗口
    class CPaintWindow : public CPaintBase
    {
    public:
        int paintWindow();
    };

    // 绘制三角形
    class CPaintTriangle : public CPaintBase
    {
    public:
        virtual int paintTriangle();

    private:
        static const float m_vertices[9];
        static const char * m_selfFragmentShaderSource;
    };

    // 用不同的方法绘制三角形
    using uint_t = unsigned int;
    class CPaintTriangles : public CPaintTriangle
    {
    public:
        enum PaintType
        {
            SameTriangles = 1,  // 两个一样的三角形【同颜色 同大小】
            SameRGBTriangles,   // 两个同颜色的三角形
            Triangles,          // 两个不同颜色不同大小的三角形
        };

        virtual int paintTriangles(PaintType paintType);

    private:
        static const float m_rectVertices[12]; 
        static const float m_vertices[18];
        static const uint_t m_indices[6];
    };

    // 使用着色器类
    class ShaderCase : public CPaintBase
    {
    public:
        int paintTriangle();
        
    private:
        static const float m_vertices[9];

    };

    // 纹理
    class TextureCase : public CPaintBase
    {
    public:
        int paintTexture();

    private:
        static const float m_vertices[32];
        static const int   m_indices[6];
    };

}

#endif // !_OPENGLPART_H_
