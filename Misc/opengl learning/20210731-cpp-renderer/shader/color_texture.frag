#version 460 core
layout( binding = 0 ) uniform sampler2D TexSrc;
in vec4 fvColor;
in vec2 fvTexCoord;
out vec4 fColor;
void main(){
	vec4 temp_color = texture(TexSrc, fvTexCoord);
	fColor =  fvColor * temp_color;
}