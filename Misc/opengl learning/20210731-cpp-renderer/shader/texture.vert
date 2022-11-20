#version 460 core
layout( location = 0 ) in vec3 vPosition;
layout( location = 2 ) in vec2 vTexCoord;
out vec2 fvTexCoord;
uniform mat4 PosMat;
void main(){
	gl_Position = PosMat * vec4(vPosition, 1.0);
	fvTexCoord = vTexCoord;
}