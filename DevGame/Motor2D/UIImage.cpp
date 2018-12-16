#include "UIImage.h"
#include "j1App.h"
#include "j1Render.h"



UIImage::UIImage(int x, int y, SDL_Rect rec, SDL_Texture* tex, bool is_hud): UIObject( x, y){

	
	this->x = x;
	this->y = y;
	rect = rec;
	this->texture = tex;
	this->is_hud = is_hud;

}
UIImage::~UIImage(){}


void UIImage::Draw() {

	App->render->Blit(texture, x, y, &rect,0);

}