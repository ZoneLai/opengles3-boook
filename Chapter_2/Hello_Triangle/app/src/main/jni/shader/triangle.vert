const char* triangle_vert = STRINGIFY(
\#version 300 es \n

in vec4 v_position;

void main()
{
   gl_Position = v_position;
}
);