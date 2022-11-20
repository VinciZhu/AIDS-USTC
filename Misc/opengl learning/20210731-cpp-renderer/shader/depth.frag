#version 460 core
out vec4 fColor;
void main(){
    fColor = vec4(vec3(gl_FragCoord.z), 1.0);
}