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
#include "j1Timer.h"
#include "Brofiler/Brofiler.h"

#define LIFES_X 50
#define LIFES_Y 40
#define POINTS_X 120
#define POINTS_Y 100
#define TIME_X 180
#define TIME_Y 100

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

	
	time.Start();

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
	BROFILER_CATEGORY("UpdateScene", Profiler::Color::OrangeRed)
	LOG("lifes %i", lifes);

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

	//F8 state
	App->startmenu->CheckF8();

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

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && !pause_menu && time_pause == false)
	{
		pause_menu = true;
		time_pause = true;
		
		App->entities->active = false;

		//play button
		resume_button = App->gui->CreateUIButton(400, 200, button_off_mouse, button_on_mouse, button_off_mouse, texture);

		//settings button
		main_menu_button = App->gui->CreateUIButton(400, 280, button_off_mouse, button_on_mouse, button_off_mouse, texture);

		//exit button
		exit_button = App->gui->CreateUIButton(400, 360, button_off_mouse, button_on_mouse, button_off_mouse, texture);

		//volume bar
		volume_bar = App->gui->CreateUIImage(260, 440, volumen_rect, texture, false);

		//volume slider
		volume_pause_thumb = App->gui->CreateUISlider(430, 442, thumb_rect_off, thumb_rect_on, volume_bar->x + volumen_rect.w, volume_bar->x, texture, volume_bar);

		//start text
		text_resume = App->gui->CreateUILabel(-App->render->camera.x + 450, 225, "RESUME",false);


		//settings text
		text_main_menu = App->gui->CreateUILabel(-App->render->camera.x + 430, 305, "MAIN MENU",false);


		//main menu text
		text_exit = App->gui->CreateUILabel(-App->render->camera.x + 415, 385, "SAVE & EXIT",false);

		//text settings ingame
		text_ingame_settings = App->gui->CreateUILabel(-App->render->camera.x+100, 480, "MUSIC VOLUME",false);
		
	}

	
	//int to string
	points_string.create("%i", points);

	//float to string
	time_string.create("%.3f", game_time);
	
	//check number of lifes and print ui
	switch (lifes) 
	{
	case 3:
		App->gui->HUDCleanUp();
		three_lifes = App->gui->CreateUIImage(LIFES_X, LIFES_Y, three_lifes_rect, texture,true);
		dash_off = App->gui->CreateUIImage(270, 100, dash_off_rect, texture, true);
		attack_off = App->gui->CreateUIImage(300, 100, attack_off_rect, texture, true);
		if (App->entities->player->is_attacking == true) {
			attack_on = App->gui->CreateUIImage(300, 100, attack_on_rect, texture, true);
		}
		if (App->entities->player->is_dashing == true) {
			dash_on = App->gui->CreateUIImage(270, 100, dash_on_rect, texture, true);
		}
		points_text = App->gui->CreateUILabel(-App->render->camera.x + POINTS_X, POINTS_Y, points_string, true);
		
		time_text= App->gui->CreateUILabel(-App->render->camera.x + TIME_X, TIME_Y, time_string, true);
		break;
	case 2:
		App->gui->HUDCleanUp();
		two_lifes = App->gui->CreateUIImage(LIFES_X, LIFES_Y, two_lifes_rect, texture,true);
		dash_off = App->gui->CreateUIImage(270, 100, dash_off_rect, texture, true);
		attack_off = App->gui->CreateUIImage(300, 100, attack_off_rect, texture, true);
		if (App->entities->player->is_attacking == true) {
			attack_on = App->gui->CreateUIImage(300, 100, attack_on_rect, texture, true);
		}
		if (App->entities->player->is_dashing == true) {
			dash_on = App->gui->CreateUIImage(270, 100, dash_on_rect, texture, true);
		}
		points_text = App->gui->CreateUILabel(-App->render->camera.x + POINTS_X, POINTS_Y, points_string, true);
		time_text = App->gui->CreateUILabel(-App->render->camera.x + TIME_X, TIME_Y, time_string, true);
		break;
	case 1:
		App->gui->HUDCleanUp();
		one_life = App->gui->CreateUIImage(LIFES_X, LIFES_Y, one_lifes_rect, texture,true);
		dash_off = App->gui->CreateUIImage(270, 100, dash_off_rect, texture, true);
		attack_off = App->gui->CreateUIImage(300, 100, attack_off_rect, texture, true);
		if (App->entities->player->is_attacking == true) {
			attack_on = App->gui->CreateUIImage(300, 100, attack_on_rect, texture, true);
		}
		if (App->entities->player->is_dashing == true) {
			dash_on = App->gui->CreateUIImage(270, 100, dash_on_rect, texture, true);
		}
		points_text = App->gui->CreateUILabel(-App->render->camera.x + POINTS_X, POINTS_Y, points_string, true);
		time_text = App->gui->CreateUILabel(-App->render->camera.x + TIME_X, TIME_Y, time_string, true);
		break;
	case 0:
		/*time.Start();
		lifes = 3;
		points = 0;*/
		pause_menu = false;
		App->scene->active = false;
		App->startmenu->active = true;
		App->startmenu->Start();
		App->scene->CleanUp();
		App->gui->HUDCleanUp();
		App->entities->CleanUp();
		time.Start();
		lifes = 3;
		points = 0;

		break;
	}
	
	mouse_pos = App->input->GetMousePosition(mouse_position);

	//check if mouse is on exit button
	if (App->entities->active == false) {
		if (mouse_pos.x > exit_button->x&&mouse_pos.x<exit_button->x + exit_button->button_on.w&&mouse_pos.y>exit_button->y&&mouse_pos.y < exit_button->y + exit_button->button_on.h)
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			{
				App->SaveGame("save_game.xml");
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
				time_pause = false;
				
			}
		}

		if (mouse_pos.x > main_menu_button->x&&mouse_pos.x<main_menu_button->x + main_menu_button->button_on.w&&mouse_pos.y>main_menu_button->y&&mouse_pos.y < main_menu_button->y + main_menu_button->button_on.h)
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			{
				time_pause = true;
				pause_menu = false;
				App->scene->active = false;
				App->startmenu->active = true;
				App->startmenu->Start();
				App->scene->CleanUp();
				App->gui->HUDCleanUp();
				App->entities->CleanUp();
			
				
			}
		}	
	}

	
	

	if (time_pause == false) {
		game_time = time.ReadSec();
		
	}
	App->map->Draw();

	
	

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
	//App->tex->FreeTextures();
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