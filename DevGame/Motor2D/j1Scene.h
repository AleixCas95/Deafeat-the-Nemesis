#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "j1Timer.h"

struct SDL_Texture;
class UIObject;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load
	bool Load(pugi::xml_node& savegame);

	bool LoadScene(int map = -1);

	//Save
	bool Save(pugi::xml_node& data) const;

	int currmap = 1;

	
	UIObject* back_to_menu_button = nullptr;
	UIObject* menu_label = nullptr;


	SDL_Rect background_rect;
	SDL_Rect return_rect_on = { 1443, 298,142,58 };
	SDL_Rect return_rect_off = { 1443,222,141,58 };
	
	SDL_Rect button_off_mouse;
	SDL_Rect button_on_mouse;

	SDL_Rect three_lifes_rect = { 1124,35,46,84 };
	SDL_Rect two_lifes_rect = { 1188,34,46,84 };
	SDL_Rect one_lifes_rect = { 1187,122,44,85 };

	SDL_Rect thumb_rect_off = { 1642,35,84,84 };
	SDL_Rect thumb_rect_on = { 1642,125,84,85 };
	SDL_Rect volumen_rect = { 1100,458,431,88 };

	SDL_Texture* texture;

	UIObject * resume_button = nullptr;
	UIObject * exit_button = nullptr;
	UIObject * settings_button = nullptr;
	UIObject * main_menu_button = nullptr;
	UIObject * text_ingame_settings = nullptr;
	

	UIObject* three_lifes = nullptr;
	UIObject* two_lifes = nullptr;
	UIObject* one_life = nullptr;

	UIObject* volume_pause_thumb = nullptr;
	UIObject* volume_bar = nullptr;

	UIObject* text_resume = nullptr;
	UIObject* text_exit = nullptr;
	UIObject* text_settings = nullptr;
	UIObject* text_main_menu = nullptr;
	UIObject* points_text = nullptr;
	UIObject* time_text = nullptr;
	
	SDL_Rect attack_on_rect = { 1146, 145, 18,15 };
	SDL_Rect attack_off_rect = { 1116,145,18,15 };
	SDL_Rect dash_on_rect = { 1146,172,18,15 };
	SDL_Rect dash_off_rect = { 1116,171,18,15 };

	UIObject* attack_off = nullptr;
	UIObject* attack_on = nullptr;
	UIObject* dash_off = nullptr;
	UIObject* dash_on = nullptr;

	iPoint mouse_position, mouse_pos;

	p2SString points_string = nullptr;
	p2SString time_string = nullptr;

	int lifes = 3;
	int points = 0;

	j1Timer time;
	
	float game_time = 0.0f;
	
	
	bool time_pause = false;



private:

	p2List<const char*>  MapsList_String;
	p2List_item<const char*>* CurrentMap = nullptr;
	bool close_game = false;
	bool pause_menu = false;
	p2SString atlas_file_name;



	
};

#endif // __j1SCENE_H__