#pragma once

#include"SpriteModule.hpp"
/*-----------------------------------------------------------------------------------------------*/
typedef struct _EntityPointInfo {

	SpriteInfo* sprite;
	glm::vec2 sprite_r;
	GLdouble m;
	glm::dvec3 r;
	glm::dvec3 v;
	glm::dvec3 a;
	glm::dvec3 f;

}EntityPointInfo;

EntityPointInfo* CreateEntityPoint(GLdouble m, glm::dvec3 r, glm::dvec3 v);

void UpdateEntityPoint(EntityPointInfo* point, GLdouble dt);

void UpdateEntityPointSprite(EntityPointInfo* point, glm::dmat4 transform);

void DestroyEntityPoint(EntityPointInfo* point);

void SetEntityPointSprite(EntityPointInfo* point, SpriteInfo* sprite, glm::vec2 r);
/*-----------------------------------------------------------------------------------------------*/
EntityPointInfo* CreateEntityPoint(GLdouble m, glm::dvec3 r, glm::dvec3 v) {
	EntityPointInfo* point = new EntityPointInfo;
	point->sprite = NULL;
	point->m = m;
	point->r = r;
	point->v = v;
	point->a = glm::dvec3(0.0);
	point->f = glm::dvec3(0.0);
	return point;
}

void UpdateEntityPoint(EntityPointInfo* point, GLdouble dt) {
	point->a = point->f / point->m;
	point->v += dt * point->a;
	point->r += dt * point->v;
}

void UpdateEntityPointSprite(EntityPointInfo* point, glm::dmat4 transform) {
	glm::dvec4 r = transform * glm::dvec4(point->r, 1.0);
	if (point->sprite) {
		point->sprite->x = (GLfloat)r.x * GamePixelsPerMeter - point->sprite_r.x;
		point->sprite->y = (GLfloat)r.y * GamePixelsPerMeter - point->sprite_r.y;
		point->sprite->z = (GLfloat)r.z * GamePixelsPerMeter;
		UpdateSprite(point->sprite);
	}
}

void DestroyEntityPoint(EntityPointInfo* point) {
	delete point;
}

void SetEntityPointSprite(EntityPointInfo* point, SpriteInfo* sprite, glm::vec2 r) {
	point->sprite = sprite;
	point->sprite_r = r;
}