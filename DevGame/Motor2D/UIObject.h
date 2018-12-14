#ifndef _UI_OBJECT_
#define _UI_OBJECT_

#include "SDL/include/SDL.h"
#include "j1Textures.h"
#include "p2Defs.h"
#include "p2Point.h"
#include "j1Gui.h"

class j1Module;





class UIObject {

public:
	UIObject(int x, int y);

	~UIObject();


	virtual void Update();
	virtual void Draw();



protected:
	int x;
	int y;
	iPoint uidimension = iPoint { 500,200 };
	iPoint mouse_position;
	iPoint mouse_pos;
	SDL_Rect rect;
	p2SString text;
	SDL_Texture* texture = nullptr;
	SDL_Texture* texture_fonts = nullptr;
	SDL_Rect size = { 0,0,0,0 };
	SDL_Rect button_off;
	SDL_Rect button_on;
	SDL_Rect button_clicked;
	SDL_Rect current_rect;



};




#endif // !_UIOBJECT_
