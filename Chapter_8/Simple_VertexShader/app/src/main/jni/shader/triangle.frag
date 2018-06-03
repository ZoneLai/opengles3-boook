const char* triangle_frag = STRINGIFY(
\#version 300 es \n

precision mediump float;
in  vec3 v_color;
in	vec2 v_textcoord;

out vec4 o_fragColor;

void main()
{
    o_fragColor = vec4(v_color, 1.0);
}
);