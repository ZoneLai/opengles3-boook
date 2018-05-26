const char* triangle_frag = STRINGIFY(
\#version 300 es \n

precision mediump float;
out vec4 o_fragColor;

void main()
{
    o_fragColor = vec4 (1.0, 0.0, 0.0, 1.0);
}
);