#include "UISlider.h"
#include "UIObject.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Fonts.h"
#include "j1Render.h"

UISlider::UISlider(int x, int y, SDL_Rect thumb_off, SDL_Rect thumb_on, int margin_right, int margin_left, SDL_Texture *tex):UIObject(x,y)
{
	this->x = x;
	this->y = y;
	this->button_off = thumb_off;
	this->button_on = thumb_on;
	this->texture = tex;
	this->margin_left = margin_left;
	this->margin_right = margin_right;
}

UISlider::~UISlider(){}

void UISlider::Update() 
{

	mouse_pos = App->input->GetMousePosition(mouse_position);

	if (mouse_pos.x >= x && mouse_pos.x <= x + button_off.w && mouse_pos.y >= y && mouse_pos.y <= y + button_off.h) 
	{
		current_rect = button_off;
		if ((App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT) && x<margin_right-button_off.w && x>margin_left)
		{
			current_rect = button_on;
			x = mouse_pos.x-40;
		}
		else if ((App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT) && x >= margin_right-button_off.w) 
		{
			x -= 1;
		}
		else if ((App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT) && x <= margin_left)
		{
			x += 1;
		}

	}
	else 
	{
		x_difference = mouse_pos.x - x;
		current_rect = button_on;
	
	}
	
}

void UISlider::Draw() 
{
	App->render->Blit(texture, x, y, &current_rect,0);
}


