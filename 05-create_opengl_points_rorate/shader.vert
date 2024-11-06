#version 330 core
layout (location = 0) in vec3 aPos;

uniform float point_size;
uniform mediump mat4 matrix;

void main()
{
    gl_Position = matrix * vec4(aPos, 1.0);
    gl_PointSize = point_size;
}
