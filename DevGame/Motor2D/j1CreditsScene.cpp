#include "j1CreditsScene.h"
#include "j1StartMenu.h"
#include "UIButton.h"
#include "UIObject.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Render.h"

j1CreditsScene::j1CreditsScene()
{
	name.create("credits_scene");
}

bool j1CreditsScene::Awake(pugi::xml_node &)
{
	return true;
}

bool j1CreditsScene::Start()
{
	SDL_Texture* texture = App->gui->atlas;

	SDL_Rect back_rect;
	back_rect.x = 39;
	back_rect.y = 845;
	back_rect.w = 1024;
	back_rect.h = 770;

	SDL_Rect return_rect_on;
	return_rect_on.x = 1443;
	return_rect_on.y = 298;
	return_rect_on.w = 142;
	return_rect_on.h = 58;

	SDL_Rect return_rect_off;
	return_rect_off.x = 1443;
	return_rect_off.y = 222;
	return_rect_off.w = 141;
	return_rect_off.h = 58;

	SDL_Rect license_rect = { 1173,967,672,487 };

	//background
	background = App->gui->CreateUIImage(0, 0, back_rect, texture);

	//return button
	return_button = App->gui->CreateUIButton(20, 550, return_rect_off, return_rect_on, return_rect_off, texture);

	//license
	license = App->gui->CreateUIImage(170, 60, license_rect, texture);

	//return to menu label
	menu_text = App->gui->CreateUILabel(65, 575, "MENU");

	return true;
}

bool j1CreditsScene::PreUpdate()
{
	return true;
}

bool j1CreditsScene::Update(float)
{
	iPoint mouse_position, mouse_pos;
	mouse_pos = App->input->GetMousePosition(mouse_position);

	////check if mouse is on menu button
	if (mouse_pos.x > return_button->x&&mouse_pos.x<return_button->x + return_button->button_on.w&&mouse_pos.y>return_button->y&&mouse_pos.y < return_button->y + return_button->button_on.h)
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			App->credits_scene->active = false;
			App->startmenu->active = true;
			App->startmenu->Start();
			App->credits_scene->CleanUp();
		}
	}

	return true;
}

bool j1CreditsScene::PostUpdate()
{
	return true;
}

bool j1CreditsScene::CleanUp()
{
	return true;
}
