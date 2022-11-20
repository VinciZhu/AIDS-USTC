#pragma once
#include "core.hpp"
namespace znd {

	const string Model::shader_files[2] = {
		"mesh.vert",
		"mesh.frag"
	};

	const string Model::oit_shader_files[2] = {
	};

	const uint Model::normal_loc = 1;
	const uint Model::tangent_loc = 3;
	const uint Model::bitangent_loc = 4;
	Program Model::program;

	Model::Model() {
	}

	Model::~Model() {
	}

	Model::Model(const string& _filename, const vec3& _translation) :
		Node(_translation) {
		meshes = &Mesh::get(_filename);
	}

	Model::Model(const vector<Mesh*>& _meshes, const vec3& _translation) :
		Node(_translation) {
		meshes = const_cast<vector<Mesh*>*>(&_meshes);
	}

	void Model::render(const Camera& _camera, const DirLight& _dir_light, const PointLight& _point_light) {
		for (auto itr = meshes->begin(); itr != meshes->end(); ++itr) {
			Mesh& mesh = **itr;
			program.use();
			program.uniform_mat4("CameraMat", graphics.canvas->trans_mat * _camera.trans_mat);
			program.uniform_mat4("PosMat", trans_mat);
			program.uniform_mat3("NormalMat", mat3(transpose(inverse(trans_mat))));
			map<uint, uint> tex_num;
			for (uint i = 0; i < mesh.textures.size(); ++i) {
				string str = "Material." + Texture::str[mesh.textures[i]->type];
				if (tex_num[mesh.textures[i]->type]++) {
					str += to_string(tex_num[mesh.textures[i]->type] - 1);
				}
				program.uniform_int(str, i);
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, mesh.textures[i]->name);
			}
			program.uniform_vec3("CameraPos", _camera.position);
			program.uniform_vec3("DirLight.direction", _dir_light.direction);
			program.uniform_vec3("DirLight.ambient", _dir_light.ambient);
			program.uniform_vec3("DirLight.diffuse", _dir_light.diffuse);
			program.uniform_vec3("DirLight.specular", _dir_light.specular);
			program.uniform_vec3("PointLight.position", _point_light.position);
			program.uniform_vec3("PointLight.ambient", _point_light.ambient);
			program.uniform_vec3("PointLight.diffuse", _point_light.diffuse);
			program.uniform_vec3("PointLight.specular", _point_light.specular);
			program.uniform_float("PointLight.constant", _point_light.constant);
			program.uniform_float("PointLight.linear", _point_light.linear);
			program.uniform_float("PointLight.quadratic", _point_light.quadratic);
			program.uniform_float("Material.shininess", mesh.shininess);
			glBindVertexArray(mesh.vao);
			glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
		}
	}

	void Model::init() {
		const uint shader_types[] = {
			Shader::vertex, Shader::fragment
		};
		new(&Model::program) Program(2, Model::shader_files, shader_types);
	}

	void Model::update() {
		update_actions();
		update_trans_mat();
	}

}
