#include "UIImage.h"
#include "j1App.h"
#include "j1Render.h"



UIImage::UIImage(iPoint pos, SDL_Rect rec, SDL_Texture* tex): UIObject(pos){

	rect = rec;
	texture = tex;
}
UIImage::~UIImage(){}


void UIImage::Draw() {

	App->render->Blit(texture, pos.x, pos.y, &rect);

}