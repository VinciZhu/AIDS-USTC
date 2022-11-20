#pragma once

#include "GUI_Module.hpp"
#include "EntityModule.hpp"
/*-----------------------------------------------------------------------------------------------*/
enum GameSceneIndex {
	GameNullScene,
	GameLogoScene,
	GameTitleScene,
	GameMiniGameScene
};
GLenum GameCurrentScene = GameNullScene;
//LogoScene
void InitLogoScene();
void UpdateLogoScene();
void DestroyLogoScene();
//TitleScene
void InitTitleScene();
void UpdateTitleScene();
void DestroyTitleScene();
//MiniGameScene
void InitMiniGameScene();
void UpdateMiniGameScene();
void DestroyMiniGameScene();
/*-----------------------------------------------------------------------------------------------*/
void InitScene(GLenum index) {
	switch (index)
	{
	case GameNullScene:
		break;
	case GameLogoScene:
		InitLogoScene();
		break;
	case GameTitleScene:
		InitTitleScene();
		break;
	case GameMiniGameScene:
		InitMiniGameScene();
		break;
	default:
		break;
	}
}
void UpdateScene(GLenum index) {
	switch (index)
	{
	case GameNullScene:
		break;
	case GameLogoScene:
		UpdateLogoScene();
		break;
	case GameTitleScene:
		UpdateTitleScene();
		break;
	case GameMiniGameScene:
		UpdateMiniGameScene();
		break;
	default:
		break;
	}
}
void DestroyScene(GLenum index) {
	switch (index)
	{
	case GameNullScene:
		break;
	case GameLogoScene:
		DestroyLogoScene();
		break;
	case GameTitleScene:
		DestroyTitleScene();
		break;
	case GameMiniGameScene:
		DestroyMiniGameScene();
		break;
	default:
		break;
	}
}
void SetGameScene(GLenum index) {
	DestroyScene(GameCurrentScene);
	GameCurrentScene = index;
	InitScene(index);
}
void UpdateGameScene() {
	UpdateScene(GameCurrentScene); 
	UpdateGameGraphics();
	UpdateGameCore();
}
void DestroyGameScene() {
	DestroyScene(GameCurrentScene);
}