#pragma once
#include "core.hpp"
namespace znd {

	Program::Program() {
	}

	Program::Program(uint _size, Shader* const _shaders[]) {
		name = glCreateProgram();
		for (uint i = 0; i < _size; ++i) {
			glAttachShader(name, _shaders[i]->name);
		}
		glLinkProgram(name);
		int is_linked;
		glGetProgramiv(name, GL_LINK_STATUS, &is_linked);
		if (!is_linked) {
			int loglen;
			glGetProgramiv(name, GL_INFO_LOG_LENGTH, &loglen);
			char* log = new char[loglen + 1];
			glGetProgramInfoLog(name, loglen, &loglen, log);
			cerr << "[Znd] Error: failed to link program" << endl << log;
			delete[] log;
		}
	}

	Program::Program(uint _size, const string _filenames[], const uint _types[]) {
		Shader** shaders = new Shader*[_size];
		for (uint i = 0; i < _size; ++i) {
			shaders[i] = new Shader(_filenames[i], _types[i]);
		}
		new(this) Program(_size, shaders);
		for (uint i = 0; i < _size; ++i) {
			delete shaders[i];
		}
		delete[] shaders;
	}

	Program::~Program() {
		glDeleteProgram(name);
	}


	void Program::use() {
		glUseProgram(name);
	}

	void Program::uniform_vec2(const string& _dest, const vec2& _src) {
		glProgramUniform2fv(name, glGetUniformLocation(name, _dest.c_str()), 1, value_ptr(_src));
	}

	void Program::uniform_vec3(const string& _dest, const vec3& _src) {
		glProgramUniform3fv(name, glGetUniformLocation(name, _dest.c_str()), 1, value_ptr(_src));
	}

	void Program::uniform_vec4(const string& _dest, const vec4& _src) {
		glProgramUniform4fv(name, glGetUniformLocation(name, _dest.c_str()), 1, value_ptr(_src));
	}

	void Program::uniform_mat3(const string& _dest, const mat3& _src) {
		glProgramUniformMatrix3fv(name, glGetUniformLocation(name, _dest.c_str()), 1, GL_FALSE, value_ptr(_src));
	}

	void Program::uniform_mat4(const string& _dest, const mat4& _src) {
		glProgramUniformMatrix4fv(name, glGetUniformLocation(name, _dest.c_str()), 1, GL_FALSE, value_ptr(_src));
	}

	void Program::uniform_bool(const string& _dest, bool _src) {
		glProgramUniform1i(name, glGetUniformLocation(name, _dest.c_str()), _src);
	}

	void Program::uniform_int(const string& _dest, int _src) {
		glProgramUniform1i(name, glGetUniformLocation(name, _dest.c_str()), _src);
	}

	void Program::uniform_uint(const string& _dest, uint _src) {
		glProgramUniform1ui(name, glGetUniformLocation(name, _dest.c_str()), _src);
	}

	void Program::uniform_float(const string& _dest, float _src) {
		glProgramUniform1f(name, glGetUniformLocation(name, _dest.c_str()), _src);
	}

}