#include "UIButton.h"
#include "UIObject.h"
#include "j1App.h"
#include "j1StartMenu.h"
#include "j1Render.h"

UIButton::UIButton(int x, int y, SDL_Rect mouse_off, SDL_Rect mouse_on, SDL_Rect mouse_click, SDL_Texture* tex) :UIObject( x, y)
{
	this->x = x;
	this->y = y;
	this->mouse_off = mouse_off;
	this->mouse_on = mouse_on;
	this->mouse_click = mouse_click;
	this->texture = tex;

}

UIButton::~UIButton() {}

void UIButton::Update() 
{
	if (mouse_pos.x < 0 || mouse_pos.x > App->startmenu->settings_button_rect.w || mouse_pos.y<0 || mouse_pos.y>App->startmenu->settings_button_rect.h)
	{
		current_rect = mouse_off;
	}
	else 
	{
		current_rect = mouse_on;
	}
}

void UIButton::Draw() 
{

	App->render->Blit(texture, x, y, &current_rect);

}