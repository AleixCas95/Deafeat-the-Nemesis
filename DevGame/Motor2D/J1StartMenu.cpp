#include "j1App.h"
#include "j1Module.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "j1StartMenu.h"
#include "j1SettingsScene.h"
#include "UIObject.h"
#include "UIButton.h"
#include "j1Scene.h"
#include "j1Entities.h"
#include "j1Audio.h"
#include "p2Log.h"

j1StartMenu::j1StartMenu() : j1Module(){

	name.create("startmenu");
}


bool j1StartMenu::Awake(pugi::xml_node& cofing) {

	return true;
}
bool j1StartMenu::Start() {

	texture = App->gui->atlas;

	//background
	background = App->gui->CreateUIImage(0, 0, background_rect, texture);

	//play button
	play_button = App->gui->CreateUIButton(200, 150, button_off_mouse, button_on_mouse, button_off_mouse, texture);

	//settings button
	continue_button = App->gui->CreateUIButton(200, 220, button_off_mouse, button_on_mouse, button_off_mouse, texture);

	//exit button
	settings_button = App->gui->CreateUIButton(200, 290, button_off_mouse, button_on_mouse, button_off_mouse, texture);

	//credits button
	exit_button = App->gui->CreateUIButton(200, 360, button_off_mouse, button_on_mouse, button_off_mouse, texture);
	
	//start text
	text_start = App->gui->CreateUILabel(260, 175, "START");

	//continue text
	text_continue = App->gui->CreateUILabel(240, 245, "CONTINUE");

	//settings text
	text_settings = App->gui->CreateUILabel(240, 315, "SETTINGS");

	//exit text
	text_exit = App->gui->CreateUILabel(265, 385, "EXIT");

	
	return true;
}
bool j1StartMenu::PreUpdate() {

	return true;
}
bool j1StartMenu::Update(float) {

	iPoint mouse_position, mouse_pos;

	mouse_pos = App->input->GetMousePosition(mouse_position);
	//LOG("%i %i", mouse_pos.x, mouse_pos.y);

	//check if mouse is on exit button
	if (mouse_pos.x > exit_button->x&&mouse_pos.x<exit_button->x + exit_button->button_on.w&&mouse_pos.y>exit_button->y&&mouse_pos.y < exit_button->y + exit_button->button_on.h)
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT) 
		{
			close_game = true;
		}
	}
	//check if mouse is on settings button
	if (mouse_pos.x > settings_button->x&&mouse_pos.x<settings_button->x + settings_button->button_on.w&&mouse_pos.y>settings_button->y&&mouse_pos.y < settings_button->y + settings_button->button_on.h)
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			App->startmenu->active = false;
			App->settings_scene->active = true;
			App->settings_scene->Start();
			App->startmenu->CleanUp();
		}
	}

	return true;
}
bool j1StartMenu::PostUpdate() {
	bool ret = true;

	if (close_game)
		ret = false;

	return ret;

}
bool j1StartMenu::CleanUp() {


	return true;
}
