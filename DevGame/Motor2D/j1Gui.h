#ifndef _J1GUI_
#define _J1GUI_

#include "j1App.h"
#include "j1Module.h"



class j1Gui : public j1Module{

public:

	j1Gui();

	~j1Gui();

	bool Awake(pugi::xml_node&);

	bool Start();
	bool PreUpdate();
	bool Update(float);
	bool PostUpdate();
	bool CleanUp();

	UIImage* CreateImage(iPoint, SDL_Rect, const SDL_Texture*);

private:
	SDLTesxutre * atlas = nullptr;
	p2SString atlas_file_name;
	p2List<UIObject*> UIObjects;
}

#endif
