#ifndef _UI_OBJECT_
#define _UI_OBJECT_

#include "SDL/include/SDL.h"
#include "j1Textures.h"
#include "p2Defs.h"
#include "p2Point.h"

class j1Module;



enum UIObjectType {

	NoObjectType,
	ImageObject,
	LabelObject
};

class UIObject {

public:
	UIObject(int x, int y);

	~UIObject();


	virtual void Update(float);
	virtual void Draw();



protected:
	int x;
	int y;
	SDL_Rect rect;
	SDL_Texture* texture = nullptr;
};




#endif // !_UIOBJECT_
