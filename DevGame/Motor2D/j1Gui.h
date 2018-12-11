#ifndef _J1_GUI_
#define _J1_GUI_

#include "j1Module.h"
#include "p2Point.h"
#include "p2List.h"

class UIObject;

class j1Gui : public j1Module {

	public:

		j1Gui();

		~j1Gui();

		bool Awake(pugi::xml_node&);

		bool Start();
		bool PreUpdate();
		bool Update(float);
		bool PostUpdate();
		bool CleanUp();

		//UIObject* CreateImage(iPoint pos, SDL_Rect rect, SDL_Texture* texture);

	private:
		SDL_Texture * atlas = nullptr;
		p2SString atlas_file_name;
		p2List<UIObject*> UIObjects;
};




#endif // !_J1GUI_
