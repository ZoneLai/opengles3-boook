const char* triangle_frag = STRINGIFY(
\#version 300 es \n

precision mediump float;
in  vec4 v_color;
out vec4 o_fragColor;

void main()
{
    o_fragColor = v_color;
}
);