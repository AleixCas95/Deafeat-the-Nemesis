#ifndef _UI_SLIDER_
#define _UI_SLIDER_

#include "UIObject.h"

class UISlider : public UIObject {

public:
	UISlider(int x, int y, SDL_Rect thumb_off, SDL_Rect thumb_on, int margin_right, int margin_left, SDL_Texture *tex);
	~UISlider();
	void Update();
	void Draw();
	int x_difference = 0;
};



#endif _UI_SLIDER_