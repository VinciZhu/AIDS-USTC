#version 460 core
layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec4 vColor;
out vec4 fvColor;
uniform mat4 PosMat;
void main(){
	gl_Position = PosMat * vec4(vPosition, 1.0);
	fvColor = vColor;
}