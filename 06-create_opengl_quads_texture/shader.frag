#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 Texcoord;

uniform sampler2D ourTexture;
uniform sampler2D csTexture;

void main()
{
     FragColor = mix(texture(ourTexture, Texcoord), texture(csTexture, Texcoord), 0.5);
}
