#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 Texcoord;

uniform sampler2D ourTexture;
uniform sampler2D csTexture;

void main()
{
     FragColor = texture(ourTexture, Texcoord);
}
