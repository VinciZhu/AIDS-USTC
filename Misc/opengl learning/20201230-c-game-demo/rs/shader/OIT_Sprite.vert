#version 460 core
layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec4 vColor;
layout( location = 2 ) in vec2 vTexCoord;
out vec4 fvColor;
out vec2 fvTexCoord;
uniform mat4 vPosMat;
void main(){
	gl_Position = vPosMat * vec4(vPosition, 1.0);
	fvColor = vColor;
	fvTexCoord = vTexCoord;
}