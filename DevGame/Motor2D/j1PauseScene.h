#ifndef _J1_PAUSESCENE_
#define _J1_PAUSESCENE_

#include "j1Module.h"

class UIImage;
class UIObject;
class UILabel;

class j1PauseScene :public j1Module 
{
public:

	j1PauseScene();
	~j1PauseScene(){}

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float);
	bool PostUpdate();
	bool CleanUp();

	UIObject* background = nullptr;
};

#endif