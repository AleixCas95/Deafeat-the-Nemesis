#ifndef _UIBUTTON_
#define _UIBUTTON_

#include "UIObject.h"

class UIButton :public UIObject
{
public: 

	UIButton(int x, int y, SDL_Rect mouse_off, SDL_Rect mouse_on, SDL_Rect mouse_click, SDL_Texture* tex);
	~UIButton();
	void Update();
	void Draw();
	



public:
	bool is_on = false;
	//bool is_off = true;
	
};


#endif
