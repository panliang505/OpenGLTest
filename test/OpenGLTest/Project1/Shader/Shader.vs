//顶点着色器代码
#version 330 core
layout (location = 0) in vec3 aPos;
//"layout (location = 1) in vec3 aColor;\n"
out vec3 ourColor;
void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = vec3(0.5f, 0.0f, 0.0f);
}
