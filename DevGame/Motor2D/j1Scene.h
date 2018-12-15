#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

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


	SDL_Rect background_rect = { 40,36,1024,768 };
	SDL_Rect return_rect_on = { 1443, 298,142,58 };
	SDL_Rect return_rect_off = { 1443,222,141,58 };
	SDL_Texture* texture;
private:

	p2List<const char*>  MapsList_String;
	p2List_item<const char*>* CurrentMap = nullptr;
};

#endif // __j1SCENE_H__