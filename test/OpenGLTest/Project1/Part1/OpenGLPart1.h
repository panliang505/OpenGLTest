/**********************************
*  @description :  
*  @author ��panl 
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

    // ����һ������
    class CPaintWindow : public CPaintBase
    {
    public:
        int paintWindow();
    };

    // ����������
    class CPaintTriangle : public CPaintBase
    {
    public:
        virtual int paintTriangle();

    private:
        static const float m_vertices[9];
        static const char * m_selfFragmentShaderSource;
    };

    // �ò�ͬ�ķ�������������
    using uint_t = unsigned int;
    class CPaintTriangles : public CPaintTriangle
    {
    public:
        enum PaintType
        {
            SameTriangles = 1,  // ����һ���������Ρ�ͬ��ɫ ͬ��С��
            SameRGBTriangles,   // ����ͬ��ɫ��������
            Triangles,          // ������ͬ��ɫ��ͬ��С��������
        };

        virtual int paintTriangles(PaintType paintType);

    private:
        static const float m_rectVertices[12]; 
        static const float m_vertices[18];
        static const uint_t m_indices[6];
    };

    // ʹ����ɫ����
    class ShaderCase : public CPaintBase
    {
    public:
        int paintTriangle();
        
    private:
        static const float m_vertices[9];

    };

    // ����
    class TextureCase : public CPaintBase
    {
    public:
        int paintTexture();

        // ��ʾ��ͬ������
        int paintDiffTexture();

    protected:
        static void processInput2(GLFWwindow* window);

    protected:
        static const float m_vertices[32];
        static const int   m_indices[6];
    };

    // ������ ����ת��
    class CoordinateTransf : public TextureCase
    {
    public:
        int paintTransTexture();

    };

    // �ڰ��� ��ʾ3D������
    class Show3DCube : public CPaintBase
    {
    public:
        int show3DCube(int cubeSize = 1);

    protected:
        static const float m_vertices[];
    };

    // �ھ��� FPS �����
    class FPSCamera : public Show3DCube
    {
    public:
        int showFPSCamera(int cubeSize = 1);

    protected:
        static void processInput3(GLFWwindow* window);
        static void mouseCallback(GLFWwindow* window, double xPos, double yPos);
        static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    protected:
        static float m_deltaTime;
        static float m_lastFrame;
        static float lastX, lastY;
        static bool firstMouse;
        static float yaw , pitch;
        static double fov;
    };
}

#endif // !_OPENGLPART_H_
