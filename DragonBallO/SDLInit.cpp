#include "SDLInit.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//The window we'll be rendering to
SDL_Window* window = NULL;

//The surface contained by the window
SDL_Surface* screenSurface = NULL;


bool SDLInit::Setup() {
	 
	bool success = true;
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window                                                             //TODO: Make this name global...
		window = SDL_CreateWindow("Dragon Ball O!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface white                                       //May want to make bg color global
			Uint32 color = SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF);
			if (SDL_FillRect(screenSurface, NULL, color) < 0) {
				printf("SDL rect could not be filled! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
		}
	}
	return success;
};

bool SDLInit::Cleanup() {
	bool initSuccess = true;

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();
	return initSuccess;
}

//TODO: add delta time to update
void SDLInit::Update() {
	//Update the surface
	SDL_UpdateWindowSurface(window);
	//Wait two seconds
	//SDL_Delay(2000);
}

