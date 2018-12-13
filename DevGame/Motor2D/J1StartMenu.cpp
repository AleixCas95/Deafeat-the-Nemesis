#include "j1App.h"
#include "j1Module.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "j1StartMenu.h"


j1StartMenu::j1StartMenu() : j1Module(){

	name.create("startmenu");
}


bool j1StartMenu::Awake(pugi::xml_node& cofing) {

	return true;
}
bool j1StartMenu::Start() {

	//background
	SDL_Rect background_rect;
	background_rect.x = 40;
	background_rect.y = 36;
	background_rect.w = 1024;
	background_rect.h = 768;

	//play button
	SDL_Rect play_button_rect;
	play_button_rect.x = 1798;
	play_button_rect.y = 214;
	play_button_rect.w = 134;
	play_button_rect.h = 62;

	//settings_button
	SDL_Rect settings_button_rect;
	settings_button_rect.x = 1798;
	settings_button_rect.y = 214;
	settings_button_rect.w = 134;
	settings_button_rect.h = 62;

	//exit button
	SDL_Rect exit_button_rect;
	exit_button_rect.x = 1798;
	exit_button_rect.y = 214;
	exit_button_rect.w = 134;
	exit_button_rect.h = 62;

	//credits button
	SDL_Rect credits_button_rect;
	credits_button_rect.x = 1798;
	credits_button_rect.y = 214;
	credits_button_rect.w = 134;
	credits_button_rect.h = 62;

	
	SDL_Texture* texture;
	texture = App->gui->atlas;

	//background
	background = App->gui->CreateUIImage(0, 0, background_rect, texture);
	//play button
	play_button = App->gui->CreateUIImage(200, 150, play_button_rect, texture);
	//settings button
	settings_button = App->gui->CreateUIImage(200, 220, settings_button_rect, texture);
	//exit button
	exit_button = App->gui->CreateUIImage(200, 290, exit_button_rect, texture);
	//credits button
	credits_button = App->gui->CreateUIImage(200, 360, credits_button_rect, texture);


	//test text
	text_one = App->gui->CreateUILabel(245, 170, "S T A R T");
	return true;
}
bool j1StartMenu::PreUpdate() {

	return true;
}
bool j1StartMenu::Update(float) {

	return true;
}
bool j1StartMenu::PostUpdate() {

	return true;
}
bool j1StartMenu::CleanUp() {

	return true;
}
