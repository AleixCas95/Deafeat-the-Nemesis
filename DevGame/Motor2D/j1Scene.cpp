#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "ModuleFadeToBlack.h"
//#include "ModulePlayer.h"
#include "j1Entities.h"
#include "EntityPlayer.h"
#include "Entity.h"
#include "EntityEnemyAir.h"
#include "EntityEnemyGround.h"
#include "j1Pathfinding.h"
#include "j1Gui.h"
#include "j1StartMenu.h"
#include "j1SettingsScene.h"
#include "UIButton.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	for (pugi::xml_node map_node = config.child("maps"); map_node != nullptr; map_node = map_node.next_sibling("maps"))
	{

		const char* name = map_node.attribute("map").as_string();

		MapsList_String.add(name);
	}

	CurrentMap = MapsList_String.start;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->audio->PlayMusic("audio/music/Interstellar_Odyssey.ogg");
	
	//if (App->map->Load(CurrentMap->data) == true)
	if (App->map->Load("level1.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data) == true)
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	else if (App->map->Load("Level2.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data) == true)
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	App->entities->SpawnEntity(0, 0, PLAYER);
	iPoint spawnenemy;
	iPoint spawnenemy2;
	p2List_item<MapLayer*>* layer = App->map->data.layers.end;
	for (int i = 0; i < (layer->data->width * layer->data->height); i++)
	{
		if (layer->data->data[i] == 105)
		{
			spawnenemy = App->map->TileToWorld(i);
			App->entities->SpawnEntity(spawnenemy.x, spawnenemy.y, ENEMYAIR);

		}
		if (layer->data->data[i] == 107)
		{
			spawnenemy2 = App->map->TileToWorld(i);
			App->entities->SpawnEntity(spawnenemy2.x, spawnenemy2.y, ENEMYGROUND);

		}
	}
	
	texture = App->gui->atlas;
	
	background_rect = { 1944,847,1022,7680 };
	button_off_mouse = { 1193,210,168,63 };
	button_on_mouse = { 1189,286,170,65 };
	//IF ESCAPE PAUSE THE GAME
	
	

	////return to main menu button
	//back_to_menu_button = App->gui->CreateUIButton(870, 550, return_rect_off, return_rect_on, return_rect_off, texture);

	////return button label
	//menu_label = App->gui->CreateUILabel(915, 575, "MENU");

	
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	
	LOG("camera: %i", App->render->camera.x);

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		LoadScene(1);
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		LoadScene(0);
	}

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		LoadScene();
	}

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		App->SaveGame("save_game.xml");
	}

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		App->LoadGame("save_game.xml");

	}

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		App->map->draw_logic = !App->map->draw_logic;
	}

	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {

		
		App->entities->player->god_mode = !App->entities->player->god_mode;
		App->entities->player->is_falling = true;
		App->entities->player->is_jumping = false;

	}
	int camera_speed = 2;

	if (App->entities->player->god_mode)
		camera_speed = 4;

	//App->render->camera.y = -550;

	if (App->entities->player->pos.x - (-App->render->camera.x + (1 * App->render->camera.w / 2)) >= 0)
	{
		if (App->render->camera.x - App->render->camera.w > -(App->map->data.width*App->map->data.tile_width))
			App->render->camera.x -= camera_speed;
	}

	if (App->entities->player->pos.x - (-App->render->camera.x + (1 * App->render->camera.w / 2)) <= 0)
	{
		if (App->render->camera.x < 0)
			App->render->camera.x += camera_speed;
	}

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && !pause_menu)
	{
		pause_menu = true;

		App->entities->active = false;

		//play button
		resume_button = App->gui->CreateUIButton(400, 200, button_off_mouse, button_on_mouse, button_off_mouse, texture);

		//settings button
		settings_button = App->gui->CreateUIButton(400, 280, button_off_mouse, button_on_mouse, button_off_mouse, texture);

		//exit button
		main_menu_button = App->gui->CreateUIButton(400, 360, button_off_mouse, button_on_mouse, button_off_mouse, texture);

		//exit button
		exit_button = App->gui->CreateUIButton(400, 440, button_off_mouse, button_on_mouse, button_off_mouse, texture);



		//start text
		text_resume = App->gui->CreateUILabel(-App->render->camera.x + 450, 225, "RESUME");


		//settings text
		text_settings = App->gui->CreateUILabel(-App->render->camera.x + 440, 305, "SETTINGS");


		//main menu text
		text_main_menu = App->gui->CreateUILabel(-App->render->camera.x + 435, 385, "MAIN MENU");

		//continue text
		text_exit = App->gui->CreateUILabel(-App->render->camera.x + 420, 465, "SAVE & EXIT");

	
		

		
	}
	
	mouse_pos = App->input->GetMousePosition(mouse_position);

	//check if mouse is on exit button
	if (App->entities->active == false) {
		if (mouse_pos.x > exit_button->x&&mouse_pos.x<exit_button->x + exit_button->button_on.w&&mouse_pos.y>exit_button->y&&mouse_pos.y < exit_button->y + exit_button->button_on.h)
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			{
				close_game = true;
			}
		}

		if (mouse_pos.x > resume_button->x&&mouse_pos.x<resume_button->x + resume_button->button_on.w&&mouse_pos.y>resume_button->y&&mouse_pos.y < resume_button->y + resume_button->button_on.h)
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			{
				pause_menu = false;
				App->gui->CleanUp();
				App->entities->active = true;
			}
		}

		if (mouse_pos.x > main_menu_button->x&&mouse_pos.x<main_menu_button->x + main_menu_button->button_on.w&&mouse_pos.y>main_menu_button->y&&mouse_pos.y < main_menu_button->y + main_menu_button->button_on.h)
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			{
				pause_menu = false;
				App->scene->active = false;
				App->startmenu->active = true;
				App->startmenu->Start();
				App->scene->CleanUp();
				App->entities->CleanUp();
			
				
			}
		}

		if (mouse_pos.x > settings_button->x&&mouse_pos.x<settings_button->x + settings_button->button_on.w&&mouse_pos.y>settings_button->y&&mouse_pos.y < settings_button->y + settings_button->button_on.h)
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			{
				App->scene->active = false;
				App->settings_scene->active = true;
				App->settings_scene->Start();
				App->scene->CleanUp();
				App->entities->CleanUp();

			}
		}

		
	}

	
	

	

	//FadeToBlack

	//if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	//{
	//
	//	App->fade->FadeToBlack(App->map, App->map,1.5f);
	//}

	//App->render->Blit(img, 0, 0);
	App->map->Draw();


	// "Map:%dx%d Tiles:%dx%d Tilesets:%d"
	/*p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		App->map->data.width, App->map->data.height,
		App->map->data.tile_width, App->map->data.tile_height,
		App->map->data.tilesets.count());

	App->win->SetTitle(title.GetString());*/

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{

	bool ret = true;

	if (close_game)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{

	if (App->entities->player != nullptr) {
		App->entities->player->destroy_entity = true;

		App->entities->player = nullptr;
	}
	
	App->map->CleanUp();

	//App->audio->CleanUp();
	

	LOG("Freeing scene");
	return true;
}

bool j1Scene::LoadScene(int map)
{
	
	App->map->CleanUp();
	App->tex->FreeTextures();
	App->entities->player->LoadTexture();

	


	p2List_item<Entity*>* item = App->entities->entities.start;
	while (item != nullptr)
	{
		delete item->data;
		App->entities->entities.del(item);
		item = item->next;
	}
	

	if (map == -1) {

		if (CurrentMap->next != nullptr)
		{
			CurrentMap = CurrentMap->next;
			currmap++;
		}
		else
		{
			CurrentMap = MapsList_String.start;
			currmap = 1;
		}
	}
	else if (map > 0)
	{
		CurrentMap = MapsList_String.start;
		for (int i = 1; i < map; i++) {
			if (CurrentMap->next != nullptr)
			{
				CurrentMap = CurrentMap->next;
				currmap = map;
			}
			else
				break;
		}

	}
	App->map->Load(CurrentMap->data);

	App->entities->player->FindPlayerSpawn();

	App->entities->SpawnEntity(0, 0, PLAYER);

	p2List_item<MapLayer*>* layer = App->map->data.layers.end;

	iPoint spawnenemy;
	iPoint spawnenemy2;

	for (int i = 0; i < (layer->data->width * layer->data->height); i++)
	{
		if (layer->data->data[i] == 105)
		{
			spawnenemy = App->map->TileToWorld(i);
			App->entities->SpawnEntity(spawnenemy.x, spawnenemy.y, ENEMYAIR);

		}
		if (layer->data->data[i] == 107)
		{
			spawnenemy2 = App->map->TileToWorld(i);
			App->entities->SpawnEntity(spawnenemy2.x, spawnenemy2.y, ENEMYGROUND);

		}
	}

	

	return true;
}

// Load
bool j1Scene::Load(pugi::xml_node&  savegame) {
	currmap = savegame.child("Map").attribute("CurrentMap").as_int();

	App->map->CleanUp();

	switch (currmap)
	{
	case 1:
		App->map->Load("level1.tmx");
		break;
	case 2:
		App->map->Load("Level2.tmx");
		break;
	default:
		break;
	}

	App->entities->player->Load(savegame);
	return true;
}

//Save
bool j1Scene::Save(pugi::xml_node& data) const {

	pugi::xml_node map = data.append_child("Map");

	map.append_attribute("CurrentMap") = currmap;
	App->entities->player->Save(data);
	

	return true;
}