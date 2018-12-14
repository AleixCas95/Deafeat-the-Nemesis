#include "j1App.h"
#include "j1Module.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "j1StartMenu.h"
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

	
	//background
	
	background_rect.x = 40;
	background_rect.y = 36;
	background_rect.w = 1024;
	background_rect.h = 768;

	//button 
	
	button_off_mouse.x = 1193;
	button_off_mouse.y = 210;
	button_off_mouse.w = 168;
	button_off_mouse.h = 63;

	
	button_on_mouse.x = 1189;
	button_on_mouse.y = 286;
	button_on_mouse.w = 170;
	button_on_mouse.h = 65;




	////settings_button
	//
	//settings_button_rect.x = 1193;
	//settings_button_rect.y = 210;
	//settings_button_rect.w = 168;
	//settings_button_rect.h = 63;

	////exit button
	//SDL_Rect exit_button_rect;
	//exit_button_rect.x = 1193;
	//exit_button_rect.y = 210;
	//exit_button_rect.w = 168;
	//exit_button_rect.h = 63;

	////credits button
	//SDL_Rect credits_button_rect;
	//credits_button_rect.x = 1193;
	//credits_button_rect.y = 210;
	//credits_button_rect.w = 168;
	//credits_button_rect.h = 63;

	SDL_Rect none;
	none.x = 3;
	none.y = 3;
	none.w = 2;
	none.h = 2;

	
	SDL_Texture* texture;
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
	
	//settings_button = App->gui->CreateUIImage(200, 220, settings_button_rect, texture);
	
	//exit_button = App->gui->CreateUIImage(200, 290, exit_button_rect, texture);
	
	//credits_button = App->gui->CreateUIImage(200, 360, credits_button_rect, texture);




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

	iPoint mouse_position, mouse_pos;

	mouse_pos = App->input->GetMousePosition(mouse_position);
	//LOG("%i %i", mouse_pos.x, mouse_pos.y);

	//if (mouse_pos.x > exit_button->x&&mouse_pos.x<exit_button->x + exit_button->rect.w&&mouse_pos.y>exit_button->y&&mouse_pos.y < exit_button->y + exit_button->rect.h)
	if (mouse_pos.x > exit_button->x&&mouse_pos.x<exit_button->x + exit_button->button_on.w&&mouse_pos.y>exit_button->y&&mouse_pos.y < exit_button->y + exit_button->button_on.h)
	{
		LOG("IN");
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT) 
		{

			LOG("YEAH");
			close_game = true;
		}
		else {
			LOG("NOPE");
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
