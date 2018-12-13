#ifndef _J1_GUI_
#define _J1_GUI_

#include "j1Module.h"
#include "p2Point.h"
#include "p2List.h"
#include "SDL/include/SDL.h"

class UIObject;

enum UIObjectType {

	NoObjectType,
	ImageObject,
	LabelObject,
};

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

		UIObject* CreateUIImage(int x, int y, SDL_Rect rect, SDL_Texture* texture);
		UIObject* CreateUILabel(int x, int y, p2SString text);
		UIObject* CreateUIButton(int x, int y, SDL_Rect mouse_off, SDL_Rect mouse_on, SDL_Rect mouse_click, SDL_Texture* texture);


		SDL_Texture* atlas = nullptr;
	
		

	private:
		
		p2List<UIObject*> UIObjects;
		
		p2SString atlas_file_name;
};




#endif // !_J1_GUI_
