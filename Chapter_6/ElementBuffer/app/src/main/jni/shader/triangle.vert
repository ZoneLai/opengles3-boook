const char* triangle_vert = STRINGIFY(
\#version 300 es \n

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec4 a_color;

uniform mat4 u_mvpMatrix;

out vec4 v_color;

void main()
{
   v_color      = a_color;
   gl_Position  = u_mvpMatrix * a_position;
}
);