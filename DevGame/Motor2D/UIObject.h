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
	iPoint mouse_position;
	iPoint mouse_pos;
	SDL_Rect rect;
	p2SString text;
	SDL_Texture* texture = nullptr;
	SDL_Texture* texture_fonts = nullptr;
	SDL_Rect size = { 0,0,0,0 };

};




#endif // !_UIOBJECT_
