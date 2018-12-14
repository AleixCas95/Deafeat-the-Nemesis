#ifndef _UI_SLIDER_
#define _UI_SLIDER_

#include "UIObject.h"

class UISlider : public UIObject {

public:
	UISlider(int x, int y, SDL_Rect rect, SDL_Texture *texture);
	~UISlider();

};



#endif _UI_SLIDER_