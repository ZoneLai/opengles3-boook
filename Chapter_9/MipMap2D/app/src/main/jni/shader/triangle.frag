const char* triangle_frag = STRINGIFY(
\#version 300 es \n

precision mediump float;
in vec2 v_texCoord;
out vec4 o_fragColor;
//layout(location = 0) out vec4 o_fragColor;
uniform sampler2D s_texture;

void main()
{
    o_fragColor = texture(s_texture, v_texCoord);
}
);