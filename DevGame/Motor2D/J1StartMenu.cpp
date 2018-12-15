#include "j1App.h"
#include "j1Module.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "j1StartMenu.h"
#include "j1SettingsScene.h"
#include "j1CreditsScene.h"
#include "UIObject.h"
#include "UIButton.h"
#include "j1Scene.h"
#include "j1Entities.h"
#include "j1Audio.h"
#include "p2Log.h"
#include "j1Fonts.h"
#include "j1Entities.h"
#include "EntityPlayer.h"

j1StartMenu::j1StartMenu() : j1Module(){

	name.create("startmenu");
}


bool j1StartMenu::Awake(pugi::xml_node& cofing) {

	return true;
}
bool j1StartMenu::Start() {

	SDL_Texture* texture = App->gui->atlas;

	SDL_Rect background_rect = { 40,36,1024,768 };
	SDL_Rect button_off_mouse = { 1193,210,168,63 };
	SDL_Rect button_on_mouse = { 1189,286,170,65 };
	SDL_Rect return_rect_on = { 1440,296,142,59 };
	SDL_Rect return_rect_off = { 1440,220,141,59 };

	//background
	background = App->gui->CreateUIImage(0, 0, background_rect, texture);

	//play button
	play_button = App->gui->CreateUIButton(200, 150, button_off_mouse, button_on_mouse, button_off_mouse, texture);

	//settings button
	continue_button = App->gui->CreateUIButton(200, 220, button_off_mouse, button_on_mouse, button_off_mouse, texture);

	//exit button
	settings_button = App->gui->CreateUIButton(200, 290, button_off_mouse, button_on_mouse, button_off_mouse, texture);

	//credits button
	credits_button = App->gui->CreateUIButton(200, 360, button_off_mouse, button_on_mouse, button_off_mouse, texture);

	//exit button
	exit_button=App->gui->CreateUIButton(860, 560, return_rect_off, return_rect_on, return_rect_off, texture);

	//slider test
	slider_test = App->gui->CreateUISlider(100, 0, button_off_mouse, button_on_mouse, 300, 20, texture);
	
	//start text
	text_start = App->gui->CreateUILabel(-App->render->camera.x + 260, 175, "START");

	//continue text
	text_continue = App->gui->CreateUILabel(-App->render->camera.x + 240, 245, "CONTINUE");

	//settings text
	text_settings = App->gui->CreateUILabel(-App->render->camera.x + 240, 315, "SETTINGS");

	//credit text
	text_credits = App->gui->CreateUILabel(-App->render->camera.x + 245, 385, "CREDITS");

	//exit text
	text_exit = App->gui->CreateUILabel(-App->render->camera.x + 908, 585, "EXIT");

	//title text
	text_title = App->gui->CreateUILabel(-App->render->camera.x + 30, 30, "D E F E A T   T H E   N E M E S I S");

	return true;
}
bool j1StartMenu::PreUpdate() {

	return true;
}
bool j1StartMenu::Update(float) {

	mouse_pos = App->input->GetMousePosition(mouse_position);


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
			App->startmenu->CleanUp();
			App->settings_scene->Start();
			
		}
	}
	//check if mouse is on play button
	if (mouse_pos.x > play_button->x&&mouse_pos.x<play_button->x + play_button->button_on.w&&mouse_pos.y>play_button->y&&mouse_pos.y < play_button->y + play_button->button_on.h)
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			App->startmenu->active = false;
			App->scene->active = true;
			App->entities->active = true;
			App->startmenu->CleanUp();
			App->scene->Start();
			
		}

	}
	//check if mouse is on credits button
	if (mouse_pos.x > credits_button->x&&mouse_pos.x<credits_button->x + credits_button->button_on.w&&mouse_pos.y>credits_button->y&&mouse_pos.y < credits_button->y + credits_button->button_on.h)
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			App->startmenu->active = false;
			App->credits_scene->active = true;
			App->startmenu->CleanUp();
			App->credits_scene->Start();

		}

	}

	
	//if (mouse_pos.x > continue_button->x&&mouse_pos.x<continue_button->x + continue_button->button_on.w&&mouse_pos.y>continue_button->y&&mouse_pos.y < continue_button->y + continue_button->button_on.h)
	//{
	//	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	//	{
	//	App->startmenu->active = false;
	//	App->scene->active = true;
	//	App->startmenu->CleanUp();
	//	App->scene->Start();
	//	}

	//}


	return true;
}
bool j1StartMenu::PostUpdate() {
	bool ret = true;

	if (close_game)
		ret = false;

	return ret;

}
bool j1StartMenu::CleanUp() {


	App->gui->CleanUp();


	return true;
}
