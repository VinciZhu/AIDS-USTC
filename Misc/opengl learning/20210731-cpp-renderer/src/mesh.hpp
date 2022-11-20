#pragma once
#include "core.hpp"
namespace znd {

	map<string, vector<Mesh*>> Mesh::cache;
	Mesh::FileLoader Mesh::loader;

	Mesh::Mesh() {
	}

	Mesh::~Mesh() {
		glDeleteBuffers(1, &ebo);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}

	Mesh::Mesh(const vector<Vert>& _vertices, const vector<uint>& _indices, const vector<Texture*>& _textures) {
		vertices = _vertices;
		indices = _indices;
		textures = _textures;
		ebo = create_ebo();
		vbo = create_vbo();
		vao = create_vao(vbo, ebo);
		shininess = 0.0f;
	}

	uint Mesh::create_vao(uint _vbo, uint _ebo) {
		uint vao;
		glCreateVertexArrays(1, &vao);
		glEnableVertexArrayAttrib(vao, 0);
		glEnableVertexArrayAttrib(vao, Model::normal_loc);
		glEnableVertexArrayAttrib(vao, 2);
		glEnableVertexArrayAttrib(vao, Model::tangent_loc);
		glEnableVertexArrayAttrib(vao, Model::bitangent_loc);
		glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribFormat(vao, Model::normal_loc, 3, GL_FLOAT, GL_FALSE, 12);
		glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, 24);
		glVertexArrayAttribFormat(vao, Model::tangent_loc, 3, GL_FLOAT, GL_FALSE, 32);
		glVertexArrayAttribFormat(vao, Model::bitangent_loc, 3, GL_FLOAT, GL_FALSE, 44);
		glVertexArrayVertexBuffer(vao, 0, _vbo, 0, 56);
		glVertexArrayAttribBinding(vao, 0, 0);
		glVertexArrayAttribBinding(vao, Model::normal_loc, 0);
		glVertexArrayAttribBinding(vao, 2, 0);
		glVertexArrayAttribBinding(vao, Model::tangent_loc, 0);
		glVertexArrayAttribBinding(vao, Model::bitangent_loc, 0);
		glVertexArrayElementBuffer(vao, _ebo);
		return vao;
	}

	uint Mesh::create_vbo() {
		uint vbo;
		glCreateBuffers(1, &vbo);
		glNamedBufferStorage(vbo, vertices.size() * sizeof(Vert), &vertices[0], GL_DYNAMIC_STORAGE_BIT);
		return vbo;
	}

	uint Mesh::create_ebo() {
		uint ebo;
		glCreateBuffers(1, &ebo);
		glNamedBufferStorage(ebo, indices.size() * sizeof(uint), &indices[0], GL_DYNAMIC_STORAGE_BIT);
		return ebo;
	}

	void Mesh::FileLoader::process_node(const aiNode* _node) {
		for (uint i = 0; i < _node->mNumMeshes; ++i) {
			aiMesh* mesh = scene->mMeshes[_node->mMeshes[i]];
			vector<Vert> vertices;
			vector<uint> indices;
			vector<Texture*> textures;
			for (uint i = 0; i < mesh->mNumVertices; ++i) {
				Vert vertex;
				vertex.position.x = mesh->mVertices[i].x;
				vertex.position.y = mesh->mVertices[i].y;
				vertex.position.z = mesh->mVertices[i].z;
				if (mesh->HasNormals()) {
					vertex.normal.x = mesh->mNormals[i].x;
					vertex.normal.y = mesh->mNormals[i].y;
					vertex.normal.z = mesh->mNormals[i].z;
				}
				if (mesh->mTextureCoords[0]) {
					vertex.tex_coord.x = mesh->mTextureCoords[0][i].x;
					vertex.tex_coord.y = mesh->mTextureCoords[0][i].y;
					vertex.tangent.x = mesh->mTangents[i].x;
					vertex.tangent.y = mesh->mTangents[i].y;
					vertex.tangent.z = mesh->mTangents[i].z;
					vertex.bitangent.x = mesh->mBitangents[i].x;
					vertex.bitangent.y = mesh->mBitangents[i].y;
					vertex.bitangent.z = mesh->mBitangents[i].z;
				}
				else {
					vertex.tex_coord = vec2(0.0f, 0.0f);
				}
				vertices.push_back(vertex);
			}
			for (uint i = 0; i < mesh->mNumFaces; ++i) {
				aiFace face = mesh->mFaces[i];
				for (uint j = 0; j < face.mNumIndices; ++j)
					indices.push_back(face.mIndices[j]);
			}

			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			aiString _str;
			for (uint i = 0; i < material->GetTextureCount(aiTextureType_AMBIENT); ++i) {
				material->GetTexture(aiTextureType_AMBIENT, i, &_str);
				string filename = directory + '/' + _str.C_Str();
				textures.push_back(&Texture::get(filename, Texture::ambient));
			}
			for (uint i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); ++i) {
				material->GetTexture(aiTextureType_DIFFUSE, i, &_str);
				string filename = directory + '/' + _str.C_Str();
				textures.push_back(&Texture::get(filename, Texture::diffuse));
			}
			for (uint i = 0; i < material->GetTextureCount(aiTextureType_SPECULAR); ++i) {
				material->GetTexture(aiTextureType_SPECULAR, i, &_str);
				string filename = directory + '/' + _str.C_Str();
				textures.push_back(&Texture::get(filename, Texture::specular));
			}
			for (uint i = 0; i < material->GetTextureCount(aiTextureType_NORMALS); ++i) {
				material->GetTexture(aiTextureType_NORMALS, i, &_str);
				string filename = directory + '/' + _str.C_Str();
				textures.push_back(&Texture::get(filename, Texture::normal));
			}
			for (uint i = 0; i < material->GetTextureCount(aiTextureType_HEIGHT); ++i) {
				material->GetTexture(aiTextureType_HEIGHT, i, &_str);
				string filename = directory + '/' + _str.C_Str();
				//textures.push_back(&Texture::get(filename, Texture::height));
				textures.push_back(&Texture::get(filename, Texture::normal));
			}

			(*meshes).push_back(new Mesh(vertices, indices, textures));
			material->Get(AI_MATKEY_SHININESS, (*meshes)[counter]->shininess);
			++counter;
		}
		for (uint i = 0; i < _node->mNumChildren; i++) {
			process_node(_node->mChildren[i]);
		}
	}

	vector<Mesh*>& Mesh::get(const string& _filename) {
		auto itr = cache.find(_filename);
		if (itr == cache.end()) {
			Assimp::Importer importer;
			loader.counter = 0;
			loader.meshes = &cache[_filename];
			loader.directory = _filename.substr(0, _filename.find_last_of('/'));
			loader.scene = importer.ReadFile(
				_filename,
				aiProcess_Triangulate | aiProcess_GenSmoothNormals
				| aiProcess_FlipUVs | aiProcess_CalcTangentSpace
			);
			if (!loader.scene || loader.scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !loader.scene->mRootNode) {
				cerr << "[Znd] Error: failed to load model:" << _filename << endl;
			}
			loader.process_node(loader.scene->mRootNode);
			return cache[_filename];
		}
		else {
			return itr->second;
		}
	}

}

