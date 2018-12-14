#ifndef _J1_SETTINGS_SCENE_
#define _J1_SETTINGS_SCENE_

#include "j1Module.h"

class UIImage;

class j1SettingsScene :public j1Module 
{

public:
	j1SettingsScene();
	~j1SettingsScene();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float);
	bool PostUpdate();
	bool CleanUp();

};

#endif 
