const char* triangle_frag = STRINGIFY(
\#version 300 es \n

precision mediump float;
uniform vec4 u_color;
in float v_lifetime;

layout(location = 0) out vec4 o_fragColor;
uniform sampler2D s_texture;

void main()
{
  vec4 texColor;
  texColor      = texture(s_texture, gl_PointCoord);
  o_fragColor   = vec4(u_color) * texColor;
  o_fragColor.a *= v_lifetime;
}
);