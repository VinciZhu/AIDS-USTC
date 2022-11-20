#pragma once
#include "core.hpp"
namespace znd {

	map<string, Texture> Texture::cache;

	const string Texture::str[type_num] = {
		"TexSrc",
		"ambient",
		"diffuse",
		"specular",
		"normal",
		"tangent",
		"bitangent",
		"height"
	};

	Texture::Texture() {
	}

	Texture::Texture(const string& _filename, uint _type) {
		Bitmap bitmap(_filename);
		new(this) Texture(bitmap, _type);
	}

	Texture::Texture(const Bitmap& _bitmap, uint _type) {
		glCreateTextures(GL_TEXTURE_2D, 1, &name);
		type = _type;
		const byte* data = _bitmap.data.size() ? &_bitmap.data[0] : nullptr;
		switch (_bitmap.channel_num) {
		case 1:
			glTextureStorage2D(name, 1, GL_R8, _bitmap.width, _bitmap.height);
			if (data) {
				glTextureSubImage2D(name, 0, 0, 0, _bitmap.width, _bitmap.height, GL_RED, GL_UNSIGNED_BYTE, data);
			}
			break;
		case 3:
			glTextureStorage2D(name, 1, GL_RGB8, _bitmap.width, _bitmap.height);
			if (data) {
				glTextureSubImage2D(name, 0, 0, 0, _bitmap.width, _bitmap.height, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			break;
		case 4:
			glTextureStorage2D(name, 1, GL_RGBA8, _bitmap.width, _bitmap.height);
			if (data) {
				glTextureSubImage2D(name, 0, 0, 0, _bitmap.width, _bitmap.height, GL_RGBA, GL_UNSIGNED_BYTE, data);
			}
			break;
		}
		glTextureParameteri(name, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(name, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTextureParameteri(name, GL_TEXTURE_WRAP_T, _type == common ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTextureParameteri(name, GL_TEXTURE_WRAP_S, _type == common ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glGenerateTextureMipmap(name);
	}

	Texture::~Texture() {
		glDeleteTextures(1, &name);
	}

	void Texture::bind(uint _binding) {
		glBindTextureUnit(_binding, name);
	}

	Texture& Texture::get(const string& _filename, uint _type) {
		auto itr = cache.find(_filename);
		if (itr == cache.end()) {
			Texture& texture = cache[_filename];
			new(&texture) Texture(_filename, _type);
			return texture;
		}
		else {
			return itr->second;
		}
	}

}