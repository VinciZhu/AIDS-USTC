#pragma once

#include "Scene.hpp"
/*-----------------------------------------------------------------------------------------------*/
struct _MiniGameScene {
	//basic elements
	FPS_BoxInfo *fpsbox;					//fps显示框
	TextBoxInfo *coord_box;					//坐标显示框
	FileBitmapInfo *background_bitmap;		//背景位图（对OpenGL纹理对象的封装，利用stb库从硬盘读取.png格式文件）
	SpriteInfo *background[2];				//背景“精灵”（Sprite"类"储存了渲染所需的信息，每帧都会加入渲染队列）
	//actor
	FileBitmapInfo* actor_bitmap;			//人物位图
	GLuint actor_bitmap_index;	
	EntityPointInfo* actor;					//人物实体（质点。包含位矢、速度、加速度等物理量）
	AnimationInfo* actor_still_anim;		//人物待机动画（动画系统通过对关键帧进行插值实现）
	AnimationInfo* actor_left_anim;			//人物行走动画（向左）
	AnimationInfo* actor_right_anim;		//人物行走动画（向右）
	GLboolean actor_is_walk;				//人物是否在行走
	GLuint actor_direction;					//人物朝向
	GLuint actor_jump;						//人物是否在跳跃（ps:允许二段跳）
	EntityLineInfo *actor_ground;			//人物是否着地
	//terrain
	FileBitmapInfo* terrain_bitmap;			//地形位图
	std::vector<EntityLineInfo*> terrains;	//动态数组，储存指向地形实体对象的指针（地形实体以刚性杆为模型）
	EntityLineInfo* ground;					//地面
	//camera
	EntityPointInfo* camera;				//摄像机实体
	//physics parameters
	GLdouble g;								//重力加速度
	GLdouble k;								//"空气阻力系数"
	GLdouble P;								//人物行走的功率
	GLdouble kf;							//摩擦系数
	GLdouble last_time;						//上一次更新的时间（确保出现跳帧时物理量能正确更新）
} *MiniGameScene;
/*-----------------------------------------------------------------------------------------------*/

void MiniGameSceneKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {

	if (!FrameRender->is_freeze) {
		switch (key) {
		case GLFW_KEY_LEFT:
			if (action == GLFW_PRESS) {
				if (MiniGameScene->actor_jump) {
					SetSpriteBitmapIndex(MiniGameScene->actor->sprite,
						MiniGameScene->actor_bitmap_index % 4 * 3 +
						MiniGameScene->actor_bitmap_index / 4 * 48 +
						(MiniGameScene->actor_jump ? 12 : 14));
				}
				else {
					StopAnimation(MiniGameScene->actor_still_anim);
					StopAnimation(MiniGameScene->actor_right_anim);
					StartAnimation(MiniGameScene->actor_left_anim);
				}
				MiniGameScene->actor_direction = 1;
				MiniGameScene->actor_is_walk = GL_TRUE;
			}
			if (action == GLFW_RELEASE && MiniGameScene->actor_direction == 1) {
				if (MiniGameScene->actor_jump) {
					SetSpriteBitmapIndex(MiniGameScene->actor->sprite,
						MiniGameScene->actor_bitmap_index % 4 * 3 +
						MiniGameScene->actor_bitmap_index / 4 * 48 +
						(MiniGameScene->actor_jump ? 0 : 2));
				}
				else {
					StopAnimation(MiniGameScene->actor_left_anim);
					StartAnimation(MiniGameScene->actor_still_anim);
				}
				MiniGameScene->actor_direction = 0;
				MiniGameScene->actor_is_walk = GL_FALSE;
			}
			break;
		case GLFW_KEY_RIGHT:
			if (action == GLFW_PRESS) {
				if (MiniGameScene->actor_jump) {
					SetSpriteBitmapIndex(MiniGameScene->actor->sprite,
						MiniGameScene->actor_bitmap_index % 4 * 3 +
						MiniGameScene->actor_bitmap_index / 4 * 48 +
						(MiniGameScene->actor_jump ? 24 : 26));
				}
				else {
					StopAnimation(MiniGameScene->actor_still_anim);
					StopAnimation(MiniGameScene->actor_left_anim);
					StartAnimation(MiniGameScene->actor_right_anim);
				}
				MiniGameScene->actor_direction = 2;
				MiniGameScene->actor_is_walk = GL_TRUE;
			}
			if (action == GLFW_RELEASE && MiniGameScene->actor_direction == 2) {
				if (MiniGameScene->actor_jump) {
					SetSpriteBitmapIndex(MiniGameScene->actor->sprite,
						MiniGameScene->actor_bitmap_index % 4 * 3 +
						MiniGameScene->actor_bitmap_index / 4 * 48 +
						(MiniGameScene->actor_jump ? 0 : 2));
				}
				else {
					StopAnimation(MiniGameScene->actor_right_anim);
					StartAnimation(MiniGameScene->actor_still_anim);
				}
				MiniGameScene->actor_direction = 0;
				MiniGameScene->actor_is_walk = GL_FALSE;
			}
			break;
		case GLFW_KEY_SPACE:
			if (action == GLFW_PRESS && MiniGameScene->actor_jump < 2) {
				switch (MiniGameScene->actor_direction) {
				case 0:
					StopAnimation(MiniGameScene->actor_still_anim);
					SetSpriteBitmapIndex(MiniGameScene->actor->sprite,
						MiniGameScene->actor_bitmap_index % 4 * 3 +
						MiniGameScene->actor_bitmap_index / 4 * 48 +
						(MiniGameScene->actor_jump ? 0 : 2));
					break;
				case 1:
					StopAnimation(MiniGameScene->actor_left_anim);
					SetSpriteBitmapIndex(MiniGameScene->actor->sprite,
						MiniGameScene->actor_bitmap_index % 4 * 3 +
						MiniGameScene->actor_bitmap_index / 4 * 48 +
						(MiniGameScene->actor_jump ? 12 : 14));
					break;
				case 2:
					StopAnimation(MiniGameScene->actor_right_anim);
					SetSpriteBitmapIndex(MiniGameScene->actor->sprite,
						MiniGameScene->actor_bitmap_index % 4 * 3 +
						MiniGameScene->actor_bitmap_index / 4 * 48 +
						(MiniGameScene->actor_jump ? 24 : 26));
					break;
				default:
					break;
				}
				MiniGameScene->actor_jump += 1;
				MiniGameScene->actor->v.y = -7.0;
			}
			break;
		case GLFW_KEY_R:
			if (action == GLFW_PRESS) {
				SetGameScene(GameMiniGameScene);
				FadeOutGameGraphics(0.25);
				GameWait(0.25);
				FadeInGameGraphics(0.5);
			}
			break;
		default:
			break;
		}
	}
}

void InitMiniGameScene() {

	MiniGameScene = new struct _MiniGameScene;

	GLfloat width = 1.0f * SystemWindow->width;
	GLfloat height = 1.0f * SystemWindow->height;

	FileBitmapInfo* background_bitmap = CreateFileBitmap(
		GetGameFile(GameGraphicsDir, "001-Sky01.jpg"), 1, 1);
	SpriteInfo* background[2];
	background[0] = CreateSprite(NULL, background_bitmap->bitmap, 0, 0.0f, 0.0f, 0.0f,
		width, height, 0.0f, GUI_White, GL_TRUE);
	background[1] = CreateSprite(background[0], background_bitmap->bitmap, 0, width, 0.0f, 0.0f,
		width, height, 0.0f, GUI_White, GL_TRUE);

	AnimationInfo *roll = CreateAnimation(GL_FALSE, GL_TRUE, GL_FALSE, GL_FALSE);
	AddAnimationKeyframe(roll, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.0, 0.0f);
	AddAnimationKeyframe(roll, 0, -width, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 20.0, 0.0f);
	AddSpriteAnimation(background[0], roll);

	FPS_BoxInfo* fpsbox = CreateFPS_Box(
		GUI_Rectangle, NULL, NULL, 0.0f, 0.0f, 900.0f, 80.0f, 24.0f,
		GUI_GetColor(GUI_Black, 0.8f), GL_TRUE,
		GUI_Horizontal, GUI_AlignCentre, GUI_AlignCentre,
		L"\\s16\\l16fps:"
	);

	TextBoxInfo* coord_box = CreateTextBox(
		GUI_GradBar, NULL, NULL, width - 160.0f, 0.0f, 900.0f, 160.0f, 80.0f,
		GUI_Black, GL_TRUE, L"X: ---\\nY: ---",
		GUI_Horizontal, GUI_AlignCentre, GUI_AlignCentre
	);

	FileBitmapInfo* terrain_bitmap = CreateFileBitmap(
		GetGameFile(GameGraphicsDir, "TileA3.png"), 8, 2);
	MiniGameScene->terrain_bitmap = terrain_bitmap;
	GLdouble max_x = 1.0 * SystemWindow->width / GamePixelsPerMeter;
	GLdouble max_y = 1.0 * SystemWindow->height / GamePixelsPerMeter;
	for (GLuint i = 0; i < 8; i++) {
		EntityLineInfo *terrain = CreateEntityLine(
			max_x * glm::linearRand(0.1, 0.2), 10.0,
			glm::dvec3(
				max_x * 0.25 * (i + 2),
				max_y * glm::linearRand(0.75, 0.8),
				glm::linearRand(1.0, 3.0)
			),
			glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0), glm::dvec3(0.0)
		);
		SpriteInfo* terrain_sprite = CreateSprite(
			NULL,
			MiniGameScene->terrain_bitmap->bitmap,
			(GLuint)glm::linearRand(0.0, 16.0),
			0.0f, 0.0f, 0.0f,
			(GLfloat)terrain->l * GamePixelsPerMeter,
			(GLfloat)(max_y - terrain->r.y) * GamePixelsPerMeter,
			0.0f, GUI_White, GL_TRUE
		);
		SetEntityLineSprite(terrain, terrain_sprite,
			glm::vec2(terrain_sprite->w * 0.5f, 0.0f), 0.0f);
		MiniGameScene->terrains.push_back(terrain);
	}

	const GLchar* actor_bitmap_file;
	switch ((GLuint)glm::linearRand(0.0, 4.0))
	{
	case 0:
		actor_bitmap_file = GetGameFile(GameGraphicsDir, "SF_Monster.png");
		break;
	case 1:
		actor_bitmap_file = GetGameFile(GameGraphicsDir, "SF_People1.png");
		break;
	case 2:
		actor_bitmap_file = GetGameFile(GameGraphicsDir, "SF_People2.png");
		break;
	default:
		actor_bitmap_file = GetGameFile(GameGraphicsDir, "SF_People3.png");
		break;
	}
	GLuint actor_bitmap_index = (GLuint)glm::linearRand(0.0, 8.0);
	FileBitmapInfo* actor_bitmap = CreateFileBitmap(actor_bitmap_file, 12, 8);
	SpriteInfo* actor_sprite = CreateSprite(NULL, actor_bitmap->bitmap, 0,
		0.0f, 0.0f, 0.0f, 96.0f, 96.0f, 0.0f, GUI_White, GL_TRUE);
	SetSpriteCentre(actor_sprite, actor_sprite->bitmap->w / 2.0f, 1.0f * actor_sprite->bitmap->h);
	EntityPointInfo* actor = CreateEntityPoint(1.0,
		glm::dvec3(MiniGameScene->terrains[0]->r.x, MiniGameScene->terrains[0]->r.y, 5.0),
		glm::dvec3(0.0, 0.0, 0.0));
	SetEntityPointSprite(actor, actor_sprite, glm::vec2(0.0f));

	AnimationInfo *stay_front = CreateAnimation(GL_FALSE, GL_TRUE, GL_FALSE, GL_TRUE);
	AddAnimationKeyframe(stay_front, 
		actor_bitmap_index % 4 * 3 + actor_bitmap_index / 4 * 48 + 1,
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.0, 0.0f);
	AddAnimationKeyframe(stay_front,
		actor_bitmap_index % 4 * 3 + actor_bitmap_index / 4 * 48 + 1,
		0.0f, 0.0f, 1.0f, 1.05f, 0.0f,
		GUI_White, GUI_TransparentWhite, 1.0, 1.0f);
	AddAnimationKeyframe(stay_front,
		actor_bitmap_index % 4 * 3 + actor_bitmap_index / 4 * 48 + 1,
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 1.0, 1.0f);
	AddSpriteAnimation(actor_sprite, stay_front);

	AnimationInfo *walk_left = CreateAnimation(GL_TRUE, GL_TRUE, GL_FALSE, GL_TRUE);
	AddAnimationKeyframe(walk_left,
		actor_bitmap_index % 4 * 3 + actor_bitmap_index / 4 * 48 + 12,
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.0, 0.0f);
	AddAnimationKeyframe(walk_left,
		actor_bitmap_index % 4 * 3 + actor_bitmap_index / 4 * 48 + 13,
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.1, 0.0f);
	AddAnimationKeyframe(walk_left,
		actor_bitmap_index % 4 * 3 + actor_bitmap_index / 4 * 48 + 14,
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.1, 0.0f);
	AddAnimationKeyframe(walk_left,
		actor_bitmap_index % 4 * 3 + actor_bitmap_index / 4 * 48 + 13,
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.1, 0.0f);
	AddAnimationKeyframe(walk_left,
		actor_bitmap_index % 4 * 3 + actor_bitmap_index / 4 * 48 + 12,
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.1, 0.0f);
	AddSpriteAnimation(actor_sprite, walk_left);

	AnimationInfo *walk_right = CreateAnimation(GL_TRUE, GL_TRUE, GL_FALSE, GL_TRUE);
	AddAnimationKeyframe(walk_right,
		actor_bitmap_index % 4 * 3 + actor_bitmap_index / 4 * 48 + 24,
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.0, 0.0f);
	AddAnimationKeyframe(walk_right,
		actor_bitmap_index % 4 * 3 + actor_bitmap_index / 4 * 48 + 25
		, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.1, 0.0f);
	AddAnimationKeyframe(walk_right,
		actor_bitmap_index % 4 * 3 + actor_bitmap_index / 4 * 48 + 26,
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.1, 0.0f);
	AddAnimationKeyframe(walk_right,
		actor_bitmap_index % 4 * 3 + actor_bitmap_index / 4 * 48 + 25,
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.1, 0.0f);
	AddAnimationKeyframe(walk_right,
		actor_bitmap_index % 4 * 3 + actor_bitmap_index / 4 * 48 + 24,
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.1, 0.0f);
	AddSpriteAnimation(actor_sprite, walk_right);



	MiniGameScene->fpsbox = fpsbox;
	MiniGameScene->coord_box = coord_box;
	MiniGameScene->background_bitmap = background_bitmap;
	MiniGameScene->background[0] = background[0];
	MiniGameScene->background[1] = background[1];
	MiniGameScene->actor_bitmap = actor_bitmap;
	MiniGameScene->actor_bitmap_index = actor_bitmap_index;
	MiniGameScene->actor = actor;
	MiniGameScene->actor_still_anim = stay_front;
	MiniGameScene->actor_left_anim = walk_left;
	MiniGameScene->actor_right_anim = walk_right;
	MiniGameScene->actor_is_walk = GL_FALSE;
	MiniGameScene->actor_direction = 0;
	MiniGameScene->actor_jump = 0;
	MiniGameScene->actor_ground = MiniGameScene->terrains[0];
	MiniGameScene->camera = CreateEntityPoint(1.0, glm::dvec3(), glm::dvec3());
	MiniGameScene->g = 9.8;
	MiniGameScene->k = 1;
	MiniGameScene->kf = 5;
	MiniGameScene->P = 200;
	MiniGameScene->last_time = SystemTimer->cur;
	SetSystemKeyCallback(MiniGameSceneKeyCallback);

}

void UpdateMiniGameScene() {

	GLdouble max_x = 1.0 * SystemWindow->width / GamePixelsPerMeter;
	GLdouble max_y = 1.0 * SystemWindow->height / GamePixelsPerMeter;

	EntityPointInfo *actor = MiniGameScene->actor;
	GLdouble actor_max_vx = MiniGameScene->P / MiniGameScene->kf * actor->m * MiniGameScene->g;
	GLdouble actor_max_y = 2.0 * SystemWindow->height / GamePixelsPerMeter;
	EntityLineInfo* old_actor_ground = MiniGameScene->actor_ground;

	GLdouble t = SystemTimer->cur - MiniGameScene->last_time;
	GLdouble dt = 0.01;

	/*更新物理状态*/

	while ((t -= dt) > 0) {
		glm::dvec3 old_actor_r = actor->r;
		actor->f = glm::dvec3(0.0);
		actor->f.y += MiniGameScene->actor->m * MiniGameScene->g;
		actor->f.y += -MiniGameScene->k * MiniGameScene->actor->v.y;
		actor->f.x += (2.0 / (1 + glm::exp(10 * actor->v.x)) - 1)
			* MiniGameScene->kf * actor->m * MiniGameScene->g;
		if (MiniGameScene->actor_is_walk) {
			if (MiniGameScene->actor_direction == 1) {
				actor->f.x += glm::max(
					-2 * MiniGameScene->kf * actor->m * MiniGameScene->g,
					MiniGameScene->P / glm::min(-0.01, actor->v.x)
				);
			}
			else if (MiniGameScene->actor_direction == 2) {
				actor->f.x += glm::min(
					2 * MiniGameScene->kf * actor->m * MiniGameScene->g,
					MiniGameScene->P / glm::max(0.01, actor->v.x)
				);
			}
		}
		UpdateEntityPoint(MiniGameScene->actor, dt);
		if (old_actor_r.x >= MiniGameScene->camera->r.x
			&& actor->r.x < MiniGameScene->camera->r.x) {
			actor->r.x = MiniGameScene->camera->r.x;
			actor->v.x = 0.0;
		}
		MiniGameScene->actor_ground = NULL;
		for (std::vector<EntityLineInfo*>::iterator itr = MiniGameScene->terrains.begin();
			itr != MiniGameScene->terrains.end(); ++itr) {
			EntityLineInfo* terrain = *itr;
			if (old_actor_r.x >= terrain->r.x - terrain->l / 2
				&& old_actor_r.x <= terrain->r.x + terrain->l / 2
				&& old_actor_r.y <= terrain->r.y
				&& actor->r.y > terrain->r.y) {
				actor->r.y = terrain->r.y;
				actor->v.y = 0.0;
				MiniGameScene->actor_ground = terrain;
			}
		}
		if (old_actor_r.y <= max_y
			&& actor->r.y > max_y) {
			actor->r.y = max_y;
			actor->v.y = 0.0;
			MiniGameScene->actor_ground = MiniGameScene->ground;
		}
		MiniGameScene->camera->r.x = glm::max(MiniGameScene->camera->r.x, actor->r.x - max_x / 2);
		MiniGameScene->camera->r.y = glm::min(0.0, actor->r.y - max_y / 2);
	}
	MiniGameScene->last_time = SystemTimer->cur - t - dt;

	/*更新渲染信息*/

	if (old_actor_ground && !MiniGameScene->actor_ground) {
		MiniGameScene->actor_jump = 1;
		switch (MiniGameScene->actor_direction) {
		case 0:
			StopAnimation(MiniGameScene->actor_still_anim);
			SetSpriteBitmapIndex(MiniGameScene->actor->sprite, 
				MiniGameScene->actor_bitmap_index % 4 * 3 +
				MiniGameScene->actor_bitmap_index / 4 * 48 + 2);
			break;
		case 1:
			StopAnimation(MiniGameScene->actor_left_anim);
			SetSpriteBitmapIndex(MiniGameScene->actor->sprite, 
				MiniGameScene->actor_bitmap_index % 4 * 3 +
				MiniGameScene->actor_bitmap_index / 4 * 48 + 14);
			break;
		case 2:
			StopAnimation(MiniGameScene->actor_right_anim);
			SetSpriteBitmapIndex(MiniGameScene->actor->sprite, 
				MiniGameScene->actor_bitmap_index % 4 * 3 +
				MiniGameScene->actor_bitmap_index / 4 * 48 + 26);
			break;
		default:
			break;
		}
	}
	else if (!old_actor_ground && MiniGameScene->actor_ground) {
		MiniGameScene->actor_jump = 0;
		switch (MiniGameScene->actor_direction) {
		case 0:
			StartAnimation(MiniGameScene->actor_still_anim);
			break;
		case 1:
			StartAnimation(MiniGameScene->actor_left_anim);
			break;
		case 2:
			StartAnimation(MiniGameScene->actor_right_anim);
			break;
		default:
			break;
		}
	}

	glm::dmat4 transform = glm::translate(glm::dmat4(1.0), -MiniGameScene->camera->r);
	UpdateEntityPointSprite(MiniGameScene->actor, transform);
	for (std::vector<EntityLineInfo*>::iterator itr = MiniGameScene->terrains.begin();
		itr != MiniGameScene->terrains.end(); ++itr) {
		EntityLineInfo* terrain = *itr;
		GLdouble terrain_min_x = MiniGameScene->camera->r.x - terrain->l / 2;
		if (terrain->r.x < terrain_min_x) {
			DestroySprite(terrain->sprite);
			DestroyEntityLine(terrain);
			terrain = CreateEntityLine(
				max_x * glm::linearRand(0.1, 0.2), 10.0,
				glm::dvec3(
					terrain_min_x + max_x * 2,
					actor->r.y - max_y * glm::linearRand(0.1, 0.2),
					glm::linearRand(1.0, 3.0)
				),
				glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0), glm::dvec3(0.0)
			);
			SpriteInfo* terrain_sprite = CreateSprite(
				NULL,
				MiniGameScene->terrain_bitmap->bitmap,
				(GLuint)glm::linearRand(0.0, 16.0),
				0.0f, 0.0f, 0.0f,
				(GLfloat)terrain->l * GamePixelsPerMeter,
				(GLfloat)(max_y - terrain->r.y) * GamePixelsPerMeter,
				0.0f, GUI_White, GL_TRUE
			);
			SetEntityLineSprite(terrain, terrain_sprite,
				glm::vec2(terrain_sprite->w * 0.5f, 0.0f), 0.0f);
			*itr = terrain;
		}
		UpdateEntityLineSprite(terrain, transform);
	}

	UpdateFPS_Box(MiniGameScene->fpsbox);
	SetTextBoxText(MiniGameScene->coord_box, L"X: " 
		+ std::to_wstring((GLint)(actor->r.x - max_x / 2)) + L"m\\nY: " 
		+ std::to_wstring((GLint)(max_y - actor->r.y)) + L"m");
	UpdateTextBox(MiniGameScene->coord_box);
	UpdateSprite(MiniGameScene->background[0]);
	UpdateSprite(MiniGameScene->background[1]);

}

void DestroyMiniGameScene() {
	DestroyFPS_Box(MiniGameScene->fpsbox);
	DestroyTextBox(MiniGameScene->coord_box);
	DestroyFileBitmap(MiniGameScene->background_bitmap);
	DestroySprite(MiniGameScene->background[0]);
	DestroySprite(MiniGameScene->background[1]);
	DestroyFileBitmap(MiniGameScene->actor_bitmap);
	DestroyEntityPoint(MiniGameScene->actor);
	for (std::vector<EntityLineInfo*>::iterator itr = MiniGameScene->terrains.begin();
		itr != MiniGameScene->terrains.end(); ++itr) {
		DestroySprite((*itr)->sprite);
		DestroyEntityLine(*itr);
	}
	DestroyFileBitmap(MiniGameScene->terrain_bitmap);
	DestroyEntityPoint(MiniGameScene->camera);
	delete MiniGameScene;
}
