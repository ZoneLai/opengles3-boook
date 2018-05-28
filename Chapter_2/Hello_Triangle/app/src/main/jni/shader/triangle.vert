const char* triangle_vert = STRINGIFY(
\#version 300 es \n

layout(location = 0) in vec4 a_position;

uniform mat4 u_mvpMatrix;

void main()
{
   gl_Position = u_mvpMatrix * a_position;
}
);