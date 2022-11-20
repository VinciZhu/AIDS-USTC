#pragma once
#include "core.hpp"
namespace znd {

	const string Shader::default_directory = "rs/shader/";

	Shader::Shader() {
	}

	Shader::Shader(uint _type, const string& _src) {
		name = glCreateShader(_type);
		type = _type;
		const char* src = _src.c_str();
		glShaderSource(name, 1, &src, NULL);
		glCompileShader(name);
		int is_compiled;
		glGetShaderiv(name, GL_COMPILE_STATUS, &is_compiled);
		if (!is_compiled) {
			int loglen;
			glGetShaderiv(name, GL_INFO_LOG_LENGTH, &loglen);
			char* log = new char[loglen + 1];
			glGetShaderInfoLog(name, loglen, &loglen, log);
			cerr << "[Znd] Error: failed to compile shader:" << endl << _src << endl << log;
			delete[] log;
		}
	}

	Shader::Shader(const string& _filename, uint _type) {
		FILE* srcfile;
		fopen_s(&srcfile, (default_directory + _filename).c_str(), "rb");
		if (!srcfile) {
			cerr << "[Znd] Error: failed to load" << _filename << endl;
		}
		fseek(srcfile, 0, SEEK_END);
		int srclen = ftell(srcfile);
		char* src = new char[srclen + 1];
		fseek(srcfile, 0, SEEK_SET);
		fread(src, 1, srclen, srcfile);
		fclose(srcfile);
		src[srclen] = '\0';
		new(this) Shader(_type, src);
		delete[] src;
	}

	Shader::~Shader() {
		glDeleteShader(name);
	}


}