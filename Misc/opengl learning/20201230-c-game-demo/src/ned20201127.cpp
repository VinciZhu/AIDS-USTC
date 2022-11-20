//////////////////////////////////
// hasined 2020.11.27
// OpenGL version 4.6 core profile
//////////////////////////////////

#include "GameModules.hpp"

int main(int argc, char* argv[]) {
	InitGameCore(); 
	SetGameScene(GameLogoScene);
	while (!SystemWindow->should_close) {
		UpdateGameScene();
	}
	DestroyGameScene();
	DestroyGameCore();
	return 0;
}
