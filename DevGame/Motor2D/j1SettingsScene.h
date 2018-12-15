#pragma once
#ifndef _J1_SETTINGSSCENE_
#define _J1_SETTINGSSCENE_

#include "j1Module.h"


class UIImage;
class UILabel;
class UIObject;
class UIButton;


class j1SettingsScene : public j1Module {

public:
	j1SettingsScene();
	~j1SettingsScene() {}


	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float);
	bool PostUpdate();
	bool CleanUp();

	UIObject* background = nullptr;
	UIObject* title = nullptr;
	UIObject* return_button = nullptr;
	UIObject* menu_label = nullptr;
	UIObject* return_game_button = nullptr;
	UIObject* menu_game = nullptr;

	SDL_Rect background_rect = { 40,36,1024,768 };
	SDL_Rect return_rect_on = { 1443, 298,142,58 };
	SDL_Rect return_rect_off = { 1443,222,141,58 };

	SDL_Texture* texture;

};


#endif 
