#version 460 core
layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec3 vNormal;
layout( location = 2 ) in vec2 vTexCoord;
layout( location = 3 ) in vec3 vTangent;
layout( location = 4 ) in vec3 vBitangent;
uniform mat4 CameraMat;
uniform mat4 PosMat;
uniform mat3 NormalMat;
out vec3 fvPositon;
out vec3 fvNormal;
out vec2 fvTexCoord;
out mat3 fvNormalMat;
void main(){
	fvPositon = vec3(PosMat * vec4(vPosition, 1.0));
	fvNormal = vNormal;
	fvTexCoord = vTexCoord;
	fvNormalMat = mat3(vTangent, vBitangent, vNormal);
	gl_Position = CameraMat * PosMat * vec4(vPosition, 1.0);
}