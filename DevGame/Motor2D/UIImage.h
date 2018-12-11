#ifndef _UIIMAGE_
#define _UIIMAGE_

#include "UIObject.h"
#include "p2Point.h"

class UIImage : public UIObject {

public:
	UIImage(iPoint pos, SDL_Rect rect, SDL_Texture* texture);


};

#endif