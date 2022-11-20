#version 460 core

struct _Material {
    sampler2D diffuse;
    sampler2D specular;
	sampler2D normal;
	float shininess;
};

struct _DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct _PointLight {
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 fvPositon;
in vec3 fvNormal;
in vec2 fvTexCoord;
in mat3 fvNormalMat;
uniform _Material Material;
uniform _DirLight DirLight;
uniform _PointLight PointLight;
uniform vec3 CameraPos;
out vec4 fColor;
vec3 fDiffuse;
vec3 fSpecular;
vec3 fNormal;
vec3 fCameraDir;
vec3 BlinnPhong(vec3 light_dir);
vec3 BlinnPhong(_DirLight dir_light);
vec3 BlinnPhong(_PointLight point_light);

void main() {
	fNormal = fvNormal;
	//fNormal = normalize(fvNormalMat * (texture(Material.normal, fvTexCoord).rgb * 2.0 - 1.0));
	fDiffuse = pow(texture(Material.diffuse, fvTexCoord).rgb, vec3(2.2));
	fSpecular = pow(texture(Material.specular, fvTexCoord).rgb, vec3(2.2));
	fCameraDir = normalize(CameraPos-fvPositon);
	fColor.rgb = pow(BlinnPhong(DirLight) + BlinnPhong(PointLight), vec3(1.0 / 2.2));
	fColor.a = 1.0;
}

vec3 BlinnPhong(vec3 light_dir) {
	vec3 reflect_dir = normalize(reflect(-light_dir, fNormal));
	vec3 halfway_dir = normalize(light_dir + fCameraDir);
	float diff = max(dot(fNormal, light_dir), 0.0);
    float spec = pow(max(dot(fNormal, halfway_dir), 0.0), Material.shininess);
	vec3 ambient = DirLight.ambient * fDiffuse;
	vec3 diffuse = DirLight.diffuse * diff * fDiffuse;
	vec3 specular = DirLight.specular * spec * fSpecular;
	return ambient + diffuse + specular;
}

vec3 BlinnPhong(_DirLight dir_light) {
	return BlinnPhong(normalize(-dir_light.direction));
}

vec3 BlinnPhong(_PointLight point_light) {  
	float dist = length(point_light.position - fvPositon);
	float attenuation = 1.0 / 
		(point_light.constant + point_light.linear * dist + point_light.quadratic * (dist * dist));
	return BlinnPhong(normalize(point_light.position - fvPositon)) * attenuation;
}