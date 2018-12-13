#include "UIObject.h"
#include "j1App.h"
#include "j1Module.h"
#include "j1Render.h"
#include "j1App.h"
#include "p2Log.h"
#include "j1Input.h"
#include "j1Textures.h"


UIObject::UIObject(int x, int y) {


}

UIObject::~UIObject(){}

void UIObject::Update()
{

	mouse_pos = App->input->GetMousePosition( mouse_position);
	LOG("mousepos: %i  %i", mouse_pos.x, mouse_pos.y);

}

void UIObject::Draw() {

	
}