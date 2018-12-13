#ifndef _UI_LABEL_
#define _UI_LABEL_

#include "UIObject.h"

class UILabel : public UIObject {

public:

	UILabel(int x, int y, p2SString text);
	~UILabel();

	void Draw();
private:
	/*SDL_Rect size = { 0,0,0,0 };
	p2SString text;
	SDL_Texture* texture_fonts = nullptr;*/
};

#endif 