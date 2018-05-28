const char* triangle_vert = STRINGIFY(
\#version 300 es \n

layout(location = 0) in vec4 a_position;

void main()
{
   gl_Position = a_position;
}
);