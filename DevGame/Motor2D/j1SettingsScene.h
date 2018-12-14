#pragma once
#ifndef _J1_SETTINGSSCENE_
#define _J1_SETTINGSSCENE_

#include "j1Module.h"


class UIImage;
class UILabel;
class UIObject;


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

	SDL_Rect background_rect = { 40,36,1024,768 };

	SDL_Texture* texture;

};


#endif 
