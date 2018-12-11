#ifndef _UI_IMAGE_
#define _UI_IMAGE_

#include "UIObject.h"
#include "p2Point.h"

class UIImage : public UIObject {

	


public:

	UIImage(iPoint pos, SDL_Rect rect, SDL_Texture* texture);
	~UIImage();

	void Draw();

};

#endif