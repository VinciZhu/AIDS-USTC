#version 460 core
layout( binding = 0 ) uniform sampler2D TexSrc;
in vec4 fvColor;
in vec2 fvTexCoord;
out vec4 fColor;
uniform bool SingleChannel;
void main(){
	vec4 TempColor = texture(TexSrc, fvTexCoord);
	if(SingleChannel) {
		TempColor = vec4(1.0f,1.0f,1.0f,TempColor.r);
	}
	TempColor = fvColor * TempColor;
	fColor = TempColor;
}