//Using SDL and standard IO

#include "GameManager.h"

extern bool gQuitGame;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
	GameManager gameManager;

	if (gameManager.Init()) {
		while (!gQuitGame) {
			gameManager.Update();
			gameManager.Render();
		}
	}



			//Wait two seconds
			//SDL_Delay( 2000 );
			gameManager.Cleanup();
			return 0;



	return 0;
}