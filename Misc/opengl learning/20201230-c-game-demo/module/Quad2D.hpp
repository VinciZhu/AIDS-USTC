#pragma once

#include "Shape2D.hpp"

/*-----------------------------------------------------------------------------------------------*/
struct _Quad2D {
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
} * Quad2D;

typedef struct _Quad2D_Info {
	glm::vec3 positions[4];
	glm::vec4 colors[4];
	glm::vec2 tex_coords[4];
	GLuint vao;
	GLuint vbo;
	ShaderProgramInfo* program;
}Quad2D_Info;

GLuint GenQuad2D_VAO(GLuint vbo, GLuint ebo);

GLuint GenQuad2D_VBO();

GLuint GenQuad2D_EBO();

void InitQuad2D();

void DestroyQuad2D();

Quad2D_Info* CreateShapeQuad2D(
	GLfloat bl_x, GLfloat bl_y, glm::vec4 bl_c,
	GLfloat br_x, GLfloat br_y, glm::vec4 br_c,
	GLfloat tr_x, GLfloat tr_y, glm::vec4 tr_c,
	GLfloat tl_x, GLfloat tl_y, glm::vec4 tl_c,
	GLfloat z, GLuint vao, GLuint vbo, ShaderProgramInfo* program
);

void SetShapeQuad2D_Positions(Quad2D_Info* quad,
	GLfloat bl_x, GLfloat bl_y, GLfloat br_x, GLfloat br_y,
	GLfloat tr_x, GLfloat tr_y, GLfloat tl_x, GLfloat tl_y, GLfloat z
);

void SetShapeQuad2D_Colors(Quad2D_Info* quad,
	glm::vec4 bl_c, glm::vec4 br_c, glm::vec4 tr_c, glm::vec4 tl_c
);

void SetShapeQuad2D_TexCoords(Quad2D_Info* quad,
	GLfloat bl_x, GLfloat bl_y, GLfloat br_x, GLfloat br_y,
	GLfloat tr_x, GLfloat tr_y, GLfloat tl_x, GLfloat tl_y
);

void DrawShapeQuad2D(Quad2D_Info* vertices, TexInfo* texture, glm::mat4 trans);

void DestroyShapeQuad2D(Quad2D_Info* quad);

void DrawQuad2D(
	GLfloat bl_x, GLfloat bl_y, glm::vec4 bl_c,
	GLfloat br_x, GLfloat br_y, glm::vec4 br_c,
	GLfloat tr_x, GLfloat tr_y, glm::vec4 tr_c,
	GLfloat tl_x, GLfloat tl_y, glm::vec4 tl_c,
	GLfloat z, TexInfo* texture, glm::mat4 trans
);
/*-----------------------------------------------------------------------------------------------*/

GLuint GenQuad2D_VAO(GLuint vbo, GLuint ebo) {
	GLuint vao;
	glCreateVertexArrays(1, &vao);
	glEnableVertexArrayAttrib(vao, Shape2D->color_loc);
	glEnableVertexArrayAttrib(vao, Shape2D->position_loc);
	glEnableVertexArrayAttrib(vao, Shape2D->tex_coord_loc);
	glVertexArrayAttribFormat(vao, Shape2D->position_loc, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(vao, Shape2D->color_loc, 4, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(vao, Shape2D->tex_coord_loc, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayVertexBuffer(vao, 0, vbo, offsetof(Quad2D_Info, positions), sizeof(glm::vec3));
	glVertexArrayVertexBuffer(vao, 1, vbo, offsetof(Quad2D_Info, colors), sizeof(glm::vec4));
	glVertexArrayVertexBuffer(vao, 2, vbo, offsetof(Quad2D_Info, tex_coords), sizeof(glm::vec2));
	glVertexArrayAttribBinding(vao, Shape2D->position_loc, 0);
	glVertexArrayAttribBinding(vao, Shape2D->color_loc, 1);
	glVertexArrayAttribBinding(vao, Shape2D->tex_coord_loc, 2);
	glVertexArrayElementBuffer(vao, ebo);
	return vao;
}

GLuint GenQuad2D_VBO() {
	GLuint vbo;
	glCreateBuffers(1, &vbo);
	glNamedBufferStorage(vbo, offsetof(Quad2D_Info, vao), NULL, GL_DYNAMIC_STORAGE_BIT);
	return vbo;
}

GLuint GenQuad2D_EBO() {
	GLuint ebo;
	GLuint indices[4] = { 1, 2, 0, 3 };
	glCreateBuffers(1, &ebo);
	glNamedBufferData(ebo, sizeof(indices), indices, GL_STATIC_DRAW);
	return ebo;
}

void InitQuad2D() {

	GLuint vbo = GenQuad2D_VBO();
	GLuint ebo = GenQuad2D_EBO();
	GLuint vao = GenQuad2D_VAO(vbo, ebo);

	Quad2D = new struct _Quad2D;
	Quad2D->vao = vao;
	Quad2D->vbo = vbo;
	Quad2D->ebo = ebo;
}

void DestroyQuad2D() {
	glDeleteVertexArrays(1, &Quad2D->vao);
	glDeleteBuffers(1, &Quad2D->vbo);
	glDeleteBuffers(1, &Quad2D->ebo);
	delete Quad2D;
}

Quad2D_Info* CreateShapeQuad2D(
	GLfloat bl_x, GLfloat bl_y, glm::vec4 bl_c,
	GLfloat br_x, GLfloat br_y, glm::vec4 br_c,
	GLfloat tr_x, GLfloat tr_y, glm::vec4 tr_c,
	GLfloat tl_x, GLfloat tl_y, glm::vec4 tl_c,
	GLfloat z, GLuint vao, GLuint vbo, ShaderProgramInfo* program
) {
	Quad2D_Info* quad = new Quad2D_Info; 
	quad->tex_coords[0] = TexBottomLeft;
	quad->tex_coords[1] = TexBottomRight;
	quad->tex_coords[2] = TexTopRight;
	quad->tex_coords[3] = TexTopLeft;
	quad->vao = vao;
	quad->vbo = vbo;
	quad->program = program;
	SetShapeQuad2D_Positions(quad, bl_x, bl_y, br_x, br_y, tr_x, tr_y, tl_x, tl_y, z);
	SetShapeQuad2D_Colors(quad, bl_c, br_c, tr_c, tl_c);
	SetShapeQuad2D_TexCoords(quad, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	return quad;
}

void SetShapeQuad2D_Positions(Quad2D_Info* quad,
	GLfloat bl_x, GLfloat bl_y, GLfloat br_x, GLfloat br_y,
	GLfloat tr_x, GLfloat tr_y, GLfloat tl_x, GLfloat tl_y, GLfloat z
) {
	quad->positions[0] = glm::vec3(bl_x, bl_y, z);
	quad->positions[1] = glm::vec3(br_x, br_y, z);
	quad->positions[2] = glm::vec3(tr_x, tr_y, z);
	quad->positions[3] = glm::vec3(tl_x, tl_y, z);
	glNamedBufferSubData(quad->vbo, offsetof(Quad2D_Info, positions), sizeof(quad->positions), quad);
}

void SetShapeQuad2D_Colors(Quad2D_Info* quad,
	glm::vec4 bl_c, glm::vec4 br_c, glm::vec4 tr_c, glm::vec4 tl_c
) {
	quad->colors[0] = bl_c;
	quad->colors[1] = br_c;
	quad->colors[2] = tr_c;
	quad->colors[3] = tl_c;
	glNamedBufferSubData(quad->vbo, sizeof(quad->positions), sizeof(quad->colors), quad->colors);
}

void SetShapeQuad2D_TexCoords(Quad2D_Info* quad,
	GLfloat bl_x, GLfloat bl_y, GLfloat br_x, GLfloat br_y,
	GLfloat tr_x, GLfloat tr_y, GLfloat tl_x, GLfloat tl_y
) {
	quad->tex_coords[0] = glm::vec2(bl_x, bl_y);
	quad->tex_coords[1] = glm::vec2(br_x, br_y);
	quad->tex_coords[2] = glm::vec2(tr_x, tr_y);
	quad->tex_coords[3] = glm::vec2(tl_x, tl_y);
	glNamedBufferSubData(quad->vbo, sizeof(quad->positions) + sizeof(quad->colors),
		sizeof(quad->tex_coords), quad->tex_coords);
}

void DrawShapeQuad2D(Quad2D_Info* quad, TexInfo* texture, glm::mat4 trans) {
	UseShaderProgram(quad->program);
	SetShaderMat4(quad->program, Shape2D->trans_mat_str, trans);
	if (texture) {
		SetShaderBool(quad->program, Shape2D->single_channel_str, texture->channels_num == 1);
		glBindTextureUnit(Shape2D->tex_binding, texture->name);
	}
	glBindVertexArray(quad->vao);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
}

void DestroyShapeQuad2D(Quad2D_Info* quad) {
	delete quad;
}

void DrawQuad2D(
	GLfloat bl_x, GLfloat bl_y, glm::vec4 bl_c,
	GLfloat br_x, GLfloat br_y, glm::vec4 br_c,
	GLfloat tr_x, GLfloat tr_y, glm::vec4 tr_c,
	GLfloat tl_x, GLfloat tl_y, glm::vec4 tl_c,
	GLfloat z, TexInfo* texture, glm::mat4 trans
) {
	Quad2D_Info* quad = CreateShapeQuad2D(
		bl_x, bl_y, bl_c, br_x, br_y, br_c, tr_x, tr_y, tr_c, tl_x, tl_y, tl_c,
		z, Quad2D->vao, Quad2D->vbo, texture ? Shape2D->tex_program : Shape2D->program
	);
	DrawShapeQuad2D(quad, texture, trans);
	DestroyShapeQuad2D(quad);
}
