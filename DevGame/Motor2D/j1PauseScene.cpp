#include "j1PauseScene.h"
#include "UIButton.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Render.h"

j1PauseScene::j1PauseScene()
{
	name.create("pause_scene");
}

bool j1PauseScene::Awake(pugi::xml_node &)
{
	return true;
}

bool j1PauseScene::Start()
{
	SDL_Texture* texture = App->gui->atlas;

	SDL_Rect background_rect = { 1944,847,1022,7680 };

	//background
	background = App->gui->CreateUIImage(0, 0, background_rect, texture);

	return true;
}

bool j1PauseScene::PreUpdate()
{
	return true;
}

bool j1PauseScene::Update(float)
{
	return true;
}

bool j1PauseScene::PostUpdate()
{
	return true;
}

bool j1PauseScene::CleanUp()
{
	return true;
}
