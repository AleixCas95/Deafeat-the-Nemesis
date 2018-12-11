#ifndef _UIOBJECT_
#define _UIOBJECT_

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

	virtual void Update(float);
	virtual void Draw();

private:
	const SDL_Texture *texture = nullptr;
	
};




#endif // !_UIOBJECT_
