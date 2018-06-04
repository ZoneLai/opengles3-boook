const char* triangle_vert = STRINGIFY(
\#version 300 es \n

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoord;

uniform mat4 u_mvpMatrix;

out vec2 v_texCoord;

void main()
{
   v_texCoord   = a_texCoord;
   gl_Position  = u_mvpMatrix * vec4(a_position, 1.0);
}
);