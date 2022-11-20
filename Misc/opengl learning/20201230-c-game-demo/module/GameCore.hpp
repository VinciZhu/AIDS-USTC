#pragma once

#include "BasicModules.hpp"
/*-----------------------------------------------------------------------------------------------*/
//文件路径
const GLchar* const GameResourceDir = "rs/";
const GLchar* const GameShaderDir = "rs/shader/";
const GLchar* const GameFontDir = "rs/font/";
const GLchar* const GameGraphicsDir = "rs/graphics/";
const GLchar* const GameAudioDir = "rs/audio/";
const GLchar* const GameBGM_Dir = "rs/audio/bgm/";
const GLchar* const GameBGS_Dir = "rs/audio/bgs/";
const GLchar* const GameME_Dir = "rs/audio/me/";
const GLchar* const GameSE_Dir = "rs/audio/se/";

//窗口
const GLchar* const GameWindowCaption = "Test";
const GLsizei GameWindowWidth = 1200;
const GLsizei GameWindowHeight = 800;
const GLsizei GameWindowDepth = 1000;
//基本着色器
const GLuint GameShape2D_ShaderNum = 2;
const GLchar* const GameShape2D_ShaderFiles[] = {
	"rs/shader/Shape2D.vert", "rs/shader/Shape2D.frag"
};
const GLuint GameShape2D_TexShaderNum = 2;
const GLchar* const GameShape2D_TexShaderFiles[] = {
	"rs/shader/TexShape2D.vert", "rs/shader/TexShape2D.frag"
};
const GLuint GameShape2D_PositionLoc = 0;
const GLuint GameShape2D_ColorLoc = 1;
const GLuint GameShape2D_TexCoordLoc = 2;
const GLuint GameShape2D_TexBinding = 0;
const GLchar* const GameShape2D_TransMatStr = "vPosMat";
const GLchar* const GameRenderOIT_ShaderFiles[] = {
	"rs/shader/OIT_Render.vert", "rs/shader/OIT_Render.frag"
};
//...
//...
//精灵着色器
const GLuint GameSpriteShaderNum = 2;
const GLchar* const GameSpriteShaderFiles[] = {
	"rs/shader/Sprite.vert", "rs/shader/Sprite.frag"
};
const GLchar* const GameSpriteOIT_ShaderFiles[] = {
	"rs/shader/OIT_Sprite.vert", "rs/shader/OIT_Sprite.frag"
};
const GLchar* const GameSpriteFlashColorStr = "FlashColor";
const GLchar* const GameSpriteSingleChannelStr = "SingleChannel";
//字体
const GLchar* const GameFontFile = "msyh.ttc";
const GLsizei GameFontSize = 24;
const GLsizei GameFontLineWidth = 32;
const GLsizei GameFontBolden = 0;
const GLsizei GameFontItalic = 0;
const glm::vec4 GameFontColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
const GLsizei GameFontOutline = 0;
const glm::vec4 GameFontOutlineColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//图像
const GLchar* const GameOptionCursorFile = "option_cursor.png";
const GLchar* const GameTitleBackgroundFile = "Mountains1.png";
//用语
const wchar_t* const GameNewGameStr = L"新游戏";
const wchar_t* const GameLoadGameStr = L"读取存档";
const wchar_t* const GameExitGameStr = L"结束";
//其他
const GLuint GamePixelsPerMeter = 72;
//全局缓存
GLchar GameFilePathCache[256];
//函数声明
GLchar* GetGameFile(const GLchar* const dir, const GLchar* const filename);
void InitGameCore();
void UpdateGameCore();
void DestroyGameCore();
/*-----------------------------------------------------------------------------------------------*/
GLchar* GetGameFile(const GLchar* const dir, const GLchar* const filename) {
	GameFilePathCache[0] = '\0';
	strcat_s(GameFilePathCache, dir);
	strcat_s(GameFilePathCache, filename);
	return GameFilePathCache;
}

void InitGameCore() {
	InitSystem();
	InitSystemTimer();
	InitSystemWindow(
		GameWindowCaption,
		GameWindowWidth,
		GameWindowHeight,
		GameWindowDepth
	);
	InitShape2D(
		GameShape2D_ShaderFiles,
		GameShape2D_TexShaderFiles,
		GameShape2D_PositionLoc,
		GameShape2D_ColorLoc,
		GameShape2D_TexCoordLoc,
		GameShape2D_TexBinding,
		GameShape2D_TransMatStr,
		GameSpriteSingleChannelStr
	);
//	InitTriangle2D();
	InitQuad2D();
	InitTextureDraw();
	InitFontLibrary();
	InitSpriteShader(
		GameSpriteShaderFiles,
		GameSpriteFlashColorStr
	);
	InitBitmapDraw();
	InitOIT_Render(
		GameRenderOIT_ShaderFiles,
		GameSpriteOIT_ShaderFiles
	);
	InitFrameRender();
	InitAudio(); 
}

void UpdateGameCore() {
	UpdateSystemTimer();
	UpdateSystemWindow();
	ProcessSystemEvents();
}

void DestroyGameCore() {
	DestroyAudio();
	DestroyFrameRender();
	DestroyOIT_Render();
	DestroyBitmapDraw();
	DestroySpriteShader();
	DestroyFontLibrary();
	DestroyQuad2D();
	//	DestroyTriangle2D();
	DestroyShape2D();
	DestroySystemWindow();
	DestroySystemTimer();
	DestroySystem();
}