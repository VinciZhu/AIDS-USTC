#version 460 core
layout (binding = 0) uniform sampler2D TexSrc;
in vec2 fvTexCoord;
layout (location = 0) out vec4 fColor;
layout (location = 1) out float fRspPtr;
uniform float RspPtr;
uniform vec4 Color;
uniform vec4 MixColor;
void main() {
	vec4 temp_color = texture(TexSrc, fvTexCoord);
	temp_color = MixColor * temp_color;
	fColor = vec4(mix(temp_color.rgb, Color.rgb, Color.a), temp_color.a);
	fRspPtr = RspPtr;
	if(fColor.a == 0.0) discard;
}