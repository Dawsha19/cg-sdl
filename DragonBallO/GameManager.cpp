#include "GameManager.h"
#include "SDLInit.h"
#include "Player.h"
#include "Camera.h"

#define PAN_CAMERA_INSTEAD true
#define SHOW_COLLIDERS false

//Also camera dimension...
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int WORLD_WIDTH = 2400;
const int WORLD_HEIGHT = 2400;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

Camera gCamera;

static SDLInit sdlInit;

namespace {
	Camera camera;
	Player player;
	Sprite tree;
	Sprite house;
	Sprite gridGuide;
	Sprite boulder;
}

void InitEntities() {
	//Setting path names...
	player.SetTexturePath("textures/link_sprite.png");
	tree.SetTexturePath("textures/tree_green.gif");
	house.SetTexturePath("textures/link_house.png");
	gridGuide.SetTexturePath("textures/gridGuide.png");
	boulder.SetTexturePath("textures/boulder.png");

	//Loading textures...
	sdlInit.LoadTexture(player);
	sdlInit.LoadTexture(tree);
	sdlInit.LoadTexture(house);
	sdlInit.LoadTexture(gridGuide);
	sdlInit.LoadTexture(boulder);

	//Setting position information...
	player.SetPosition(0, 0);
	tree.SetPosition(200, 300);
	house.SetPosition(400, 100);
	gridGuide.SetPosition(0, 0);
	boulder.SetPosition(200, 150);

	//Setting size information...
	player.SetSpriteSize(50, 50);
	tree.SetSpriteSize(64, 78);
	house.SetSpriteSize(232, 178);
	gridGuide.SetSpriteSize(640, 480);
	boulder.SetSpriteSize(45, 45);

	//Set sprite sheet texture coordinates...
	player.InitSpriteSheet(0, 15, 10);
	player.SetSpriteClip(90, 1, 30, 30, 3);			//up...

	//up move...
	player.SetSpriteClip(0, 121, 30, 30, 75);	
	player.SetSpriteClip(30, 121, 30, 30, 76);
	player.SetSpriteClip(60, 121, 30, 30, 77);
	player.SetSpriteClip(90, 121, 30, 30, 78);
	player.SetSpriteClip(120, 121, 30, 30, 79);
	player.SetSpriteClip(150, 121, 30, 30, 80);
	player.SetSpriteClip(180, 121, 30, 30, 81);
	player.SetSpriteClip(210, 121, 30, 30, 82);


	player.SetSpriteClip(30, 1, 30, 30, 1);			//down...

	player.SetSpriteClip(0, 31, 30, 30, 15);		//down move...
	player.SetSpriteClip(30, 31, 30, 30, 16);		//down move...
	player.SetSpriteClip(60, 31, 30, 30, 17);		//down move...
	player.SetSpriteClip(90, 31, 30, 30, 18);		//down move...
	player.SetSpriteClip(120, 31, 30, 30, 19);		//down move...
	player.SetSpriteClip(150, 31, 30, 30, 20);		//down move...
	player.SetSpriteClip(180, 31, 30, 30, 21);		//down move...
	player.SetSpriteClip(210, 31, 30, 30, 22);		//down move...


	player.SetSpriteClip(240, 121, 30, 30, 83);		//right...

	player.SetSpriteClip(270, 121, 30, 30, 84);		//right move...
	player.SetSpriteClip(300, 121, 30, 30, 85);
	player.SetSpriteClip(330, 120, 30, 30, 86);
	player.SetSpriteClip(360, 120, 30, 30, 87);
	player.SetSpriteClip(390, 120, 30, 30, 88);


	player.SetSpriteClip(240, 30, 30, 30, 23);			//left...

	player.SetSpriteClip(270, 31, 30, 30, 24);		//left move...
	player.SetSpriteClip(300, 31, 30, 30, 25);
	player.SetSpriteClip(330, 31, 30, 30, 26);
	player.SetSpriteClip(360, 31, 30, 30, 27);
	player.SetSpriteClip(390, 31, 30, 30, 28);


	player.SetSpriteClip(170, 141, 30, 31, 61);		//first left attack...
	player.SetSpriteClip(173, 109, 30, 30, 48);		//second left attack...
	player.SetSpriteClip(173, 71, 30, 30, 34);		//last left attack...

	player.SetSpriteClip(203, 142, 30, 30, 62);		//last right attack...
	player.SetSpriteClip(203, 109, 30, 30, 49);		//second right attack...
	player.SetSpriteClip(203, 77, 30, 31, 35);		//first right attack...

	//Set sprite sheet anchor positions...
	player.SetAnchorOffset({-16, -13}, 61);			//first left attack...
	player.SetAnchorOffset({-23, -10}, 48);			//second left attack...
	player.SetAnchorOffset({-26, -5}, 34);			//last left attack...

	player.SetAnchorOffset({4, 0}, 62);				//last right attack...
	player.SetAnchorOffset({2, -10}, 49);			//second right attack...
	player.SetAnchorOffset({-11, -13}, 35);			//first right attack...=>2

	//Setup collision...
	player.ConfigureCollision(true, { 0, 14 }, { 35, 16 });
	tree.ConfigureCollision(true, { 80,90 }, { 0,15 }); //(left offset, topoffset) second set (right offset, down offset)
	house.ConfigureCollision(true, { 250,200}, { 0,40 });
	boulder.ConfigureCollision(true);

	//player.AddCollidableEntity(tree);
	player.AddCollidableEntity(boulder);
	//player.AddCollidableEntity(house);
}

bool GameManager::Init(){
	bool initSuccess = sdlInit.Setup();
	if (initSuccess) {
		InitEntities();
	}

	return initSuccess;
}

void GameManager::Cleanup(){
	sdlInit.CleanupSprite(player);
	sdlInit.CleanupSprite(tree);
	sdlInit.CleanupSprite(house);
	sdlInit.CleanupSprite(boulder);
	sdlInit.Cleanup();
}

//TODO: Add deltatime later...
void GameManager::Update() {
	tree.Update();
	player.Update();
	boulder.Update();

	//Needs to come last...
	if (PAN_CAMERA_INSTEAD) {
		gCamera.PanWith(player);
	}
	else {
		gCamera.LookAt(player);
	}

	sdlInit.Update();
}

void GameManager::Render() {
	sdlInit.Render();

	sdlInit.DrawSprite(tree);
	sdlInit.DrawSprite(boulder);
	sdlInit.DrawSprite(player);
	sdlInit.DrawSprite(house);

	//Needs to come last...
	if (SHOW_COLLIDERS) {
		//sdlInit.DrawEntityCollider(tree);
		sdlInit.DrawEntityCollider(boulder);
		sdlInit.DrawEntityCollider(player);
	}
}