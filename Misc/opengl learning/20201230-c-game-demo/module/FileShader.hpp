#pragma once

#include "Shader.hpp"

/*-----------------------------------------------------------------------------------------------*/
typedef struct _FileShaderInfo {
	ShaderInfo* shader;
	const GLchar* filename;
}FileShaderInfo;

FileShaderInfo* CreateFileShader(GLenum type, const GLchar* filename);

void DestroyFileShader(FileShaderInfo* shader);
/*-----------------------------------------------------------------------------------------------*/

FileShaderInfo* CreateFileShader(GLenum type, const GLchar* filename) {
	FILE* srcfile;
	fopen_s(&srcfile, filename, "rb");
	if (!srcfile) {
#ifdef _DEBUG
		std::cerr << "Error: shader source file not found" << std::endl;
#endif // _DEBUG
	}
	fseek(srcfile, 0, SEEK_END);
	GLsizei srclen = ftell(srcfile);
	GLchar* src = (GLchar*)malloc(sizeof(GLchar)*(srclen + 1));
	fseek(srcfile, 0, SEEK_SET);
	fread(src, 1, srclen, srcfile);
	fclose(srcfile);
	src[srclen] = '\0';

	FileShaderInfo* shader = new FileShaderInfo;
	shader->shader = CreateShader(type, src);
	shader->filename = filename;

	free(src);
	return shader;
}

void DestroyFileShader(FileShaderInfo* shader) {
	DestroyShader(shader->shader);
	delete shader;
}
