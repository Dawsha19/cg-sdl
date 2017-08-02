#include "GameManager.h"
#include "SDLInit.h"

extern SDL_Window* window;
extern SDL_Surface* screenSurface;

//Screen dimension constants
extern int SCREEN_WIDTH;                    //TODO: currently not using...
extern int SCREEN_HEIGHT;                   //TODO: currently not using...

static SDLInit sdlInit;

bool GameManager::Init() {
	bool initSuccess = sdlInit.Setup();
	return initSuccess;
}

bool GameManager::Cleanup() {
	return sdlInit.Cleanup();
}

//TODO: Add deltatime later...
void GameManager::Update(){
	sdlInit.Update();
}