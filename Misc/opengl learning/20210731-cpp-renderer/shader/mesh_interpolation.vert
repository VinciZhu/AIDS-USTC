#version 460 core
layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec3 vNormal;
layout( location = 2 ) in vec2 vTexCoord;
layout( location = 3 ) in vec3 vTangent;
layout( location = 4 ) in vec3 vBitangent;
layout( location = 10 ) in vec3 vTargetPosition;
layout( location = 11 ) in vec3 vTargetNormal;
layout( location = 12 ) in vec2 vTargetTexCoord;
layout( location = 13 ) in vec3 vTargetTangent;
layout( location = 14 ) in vec3 vTargetBitangent;
uniform mat4 CameraMat;
uniform mat4 PosMat;
uniform mat3 NormalMat;
uniform float Interpolation;
out vec3 fvPositon;
out vec3 fvNormal;
out vec2 fvTexCoord;
out mat3 fvNormalMat;
void main(){
	fvPositon = vec3(PosMat * vec4(mix(vPosition, vTargetPosition, Interpolation), 1.0));
	fvNormal = mix(vNormal, vTargetNormal, Interpolation);
	fvTexCoord = mix(vTexCoord, vTargetTexCoord, Interpolation);
	fvNormalMat = mat3(mix(vTangent, vTargetTangent, Interpolation), mix(vBitangent, vTargetBitangent, Interpolation), fvNormal);
	gl_Position = CameraMat * PosMat * vec4(mix(vPosition, vTargetPosition, Interpolation), 1.0);
}