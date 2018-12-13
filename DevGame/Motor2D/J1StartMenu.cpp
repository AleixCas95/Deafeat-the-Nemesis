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
	play_button_rect.x = 1193;
	play_button_rect.y = 210;
	play_button_rect.w = 168;
	play_button_rect.h = 63;

	//settings_button
	SDL_Rect settings_button_rect;
	settings_button_rect.x = 1193;
	settings_button_rect.y = 210;
	settings_button_rect.w = 168;
	settings_button_rect.h = 63;

	//exit button
	SDL_Rect exit_button_rect;
	exit_button_rect.x = 1193;
	exit_button_rect.y = 210;
	exit_button_rect.w = 168;
	exit_button_rect.h = 63;

	//credits button
	SDL_Rect credits_button_rect;
	credits_button_rect.x = 1193;
	credits_button_rect.y = 210;
	credits_button_rect.w = 168;
	credits_button_rect.h = 63;

	
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
	text_start = App->gui->CreateUILabel(260, 175, "START");
	//test text
	text_continue = App->gui->CreateUILabel(240, 245, "CONTINUE");
	//test text
	text_settings = App->gui->CreateUILabel(240, 315, "SETTINGS");
	//test text
	text_exit = App->gui->CreateUILabel(265, 385, "EXIT");

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
