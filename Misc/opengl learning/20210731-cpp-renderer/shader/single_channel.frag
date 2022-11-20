#version 460 core
layout( binding = 0 ) uniform sampler2D TexSrc;
in vec4 fvColor;
in vec2 fvTexCoord;
out vec4 fColor;
void main(){
	vec4 temp_color = texture(TexSrc, fvTexCoord);
	temp_color = vec4(1.0, 1.0, 1.0, temp_color.r);
	temp_color = fvColor * temp_color;
	fColor = temp_color;
}