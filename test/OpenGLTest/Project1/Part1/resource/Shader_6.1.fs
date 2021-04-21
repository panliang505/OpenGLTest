//片元着色器代码
#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float factor;

void main()
{
	// mix 控制混合结果，参数factor 参数值：0~1
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), factor);
}