#pragma once

#include"SpriteModule.hpp"
/*-----------------------------------------------------------------------------------------------*/
typedef struct _EntityLineInfo {

	SpriteInfo* sprite;
	glm::vec2 sprite_r;
	GLfloat sprite_thita;
	GLdouble l;
	GLdouble m;
	glm::dvec3 r;
	glm::dvec3 v;
	glm::dvec3 a;
	glm::dvec3 f;
	GLdouble J;
	glm::dvec3 thita;
	glm::dvec3 omega;
	glm::dvec3 beta;
	glm::dvec3 M;	

}EntityLineInfo;

EntityLineInfo* CreateEntityLine(GLdouble l, GLdouble m, glm::dvec3 r, glm::dvec3 v,
	glm::dvec3 thita, glm::dvec3 omega);

void UpdateEntityLine(EntityLineInfo* line, GLdouble dt);

void UpdateEntityLineSprite(EntityLineInfo* line, glm::dmat4 transform);

void DestroyEntityLine(EntityLineInfo* line);

void SetEntityLineSprite(EntityLineInfo* line, SpriteInfo* sprite, glm::vec2 r, GLfloat thita);
/*-----------------------------------------------------------------------------------------------*/
EntityLineInfo* CreateEntityLine(GLdouble l, GLdouble m, glm::dvec3 r, glm::dvec3 v,
	glm::dvec3 thita, glm::dvec3 omega) {
	EntityLineInfo* line = new EntityLineInfo;
	line->sprite = NULL;
	line->l = l;
	line->m = m;
	line->r = r;
	line->v = v;
	line->a = glm::dvec3(0.0);
	line->f = glm::dvec3(0.0);
	line->J = m * l * l / 3.0;
	line->thita = thita;
	line->omega = omega;
	line->beta = glm::dvec3(0.0);
	line->M = glm::dvec3(0.0);
	return line;

}

void UpdateEntityLine(EntityLineInfo* line, GLdouble dt) {
	line->a = line->f / line->m;
	line->v += dt * line->a;
	line->r += dt * line->v;
}

void UpdateEntityLineSprite(EntityLineInfo* line, glm::dmat4 transform) {
	glm::dvec4 r = transform * glm::dvec4(line->r, 1.0);
	if (line->sprite) {
		line->sprite->x = (GLfloat)r.x * GamePixelsPerMeter - line->sprite_r.x;
		line->sprite->y = (GLfloat)r.y * GamePixelsPerMeter - line->sprite_r.y;
		line->sprite->z = (GLfloat)r.z * GamePixelsPerMeter;
		line->sprite->angle = (GLfloat)line->thita.z - line->sprite_thita;
		UpdateSprite(line->sprite);
	}
}

void DestroyEntityLine(EntityLineInfo* line) {
	delete line;
}

void SetEntityLineSprite(EntityLineInfo* line, SpriteInfo* sprite, glm::vec2 r, GLfloat thita) {
	line->sprite = sprite;
	line->sprite_r = r;
	line->sprite_thita = thita;
}