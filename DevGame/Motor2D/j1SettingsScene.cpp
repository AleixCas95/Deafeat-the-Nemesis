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
#include "j1SettingsScene.h"
#include "Brofiler/Brofiler.h"

j1SettingsScene::j1SettingsScene()
{
	name.create("settings_scene");
}

bool j1SettingsScene::Awake(pugi::xml_node &)
{
	return true;
}

bool j1SettingsScene::Start()
{
	texture = App->gui->atlas;

	//background
	background = App->gui->CreateUIImage(0, 0, background_rect, texture,false);

	//return to main menu button
	return_button = App->gui->CreateUIButton(20, 550, return_rect_off, return_rect_on, return_rect_off, texture);

	//volumen bar
	volume_bar = App->gui->CreateUIImage(20, 150, volumen_rect, texture,false);

	//volumen slider
	volume_thumb = App->gui->CreateUISlider(215, 150, thumb_rect_off, thumb_rect_on, volume_bar->x + volumen_rect.w, volume_bar->x, texture, volume_bar);

	//volumen bar
	volume_bar_fx = App->gui->CreateUIImage(20, 350, volumen_rect, texture, false);

	//volumen slider
	volume_thumb_fx = App->gui->CreateUISlider(215, 350, thumb_rect_off, thumb_rect_on, volume_bar_fx->x + volumen_rect.w, volume_bar_fx->x, texture, volume_bar_fx);




	//title (settings)
	title = App->gui->CreateUILabel(-App->render->camera.x + 20, 20, "S E T T I N G S",false);


	//return button label
	menu_label = App->gui->CreateUILabel(-App->render->camera.x + 65, 575, "MENU",false);

	//volume music label
	volume_music_label = App->gui->CreateUILabel(-App->render->camera.x + 20, 120, "FX VOLUME",false);

	//volume music label
	volume_fx_label = App->gui->CreateUILabel(-App->render->camera.x + 20, 320, "MUSIC VOLUME", false);

	return true;
}

bool j1SettingsScene::PreUpdate()
{
	return true;
}

bool j1SettingsScene::Update(float)
{
	BROFILER_CATEGORY("UpdateSettingsScene", Profiler::Color::PeachPuff)
	mouse_pos = App->input->GetMousePosition(mouse_position);
	//return to menu
		if (mouse_pos.x > return_button->x&&mouse_pos.x<return_button->x + return_button->button_on.w&&mouse_pos.y>return_button->y&&mouse_pos.y < return_button->y + return_button->button_on.h)
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			{
				App->settings_scene->active = false;
				App->startmenu->active = true;
				App->startmenu->Start();
				
			}
		}

		App->startmenu->CheckF8();
	return true;
}

bool j1SettingsScene::PostUpdate()
{
	return true;
}

bool j1SettingsScene::CleanUp()
{
	return true;
}
