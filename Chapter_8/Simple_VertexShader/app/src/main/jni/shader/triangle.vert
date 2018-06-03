const char* triangle_vert = STRINGIFY(
\#version 300 es \n

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_color;
layout(location = 2) in vec2 a_textcoord;

uniform mat4 u_mvpMatrix;

out vec3 v_color;
out	vec2 v_textcoord;

void main()
{
   v_color      = a_color;
   v_textcoord	= a_textcoord;
   gl_Position  = u_mvpMatrix * vec4(a_position, 1.0);
}
);