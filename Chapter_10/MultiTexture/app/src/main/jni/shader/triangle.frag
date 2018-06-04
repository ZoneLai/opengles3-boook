const char* triangle_frag = STRINGIFY(
\#version 300 es \n

precision mediump float;
in vec2 v_texCoord;
layout(location = 0) out vec4 o_fragColor;

uniform float		u_mixValue;
uniform sampler2D   s_texture;
uniform sampler2D   s_textureLight;

void main()
{
    vec4 v_color1	= texture(s_texture, v_texCoord);
    vec4 v_color2	= texture(s_textureLight, v_texCoord);

    o_fragColor     =  mix(v_color1, v_color2, u_mixValue);
}
);