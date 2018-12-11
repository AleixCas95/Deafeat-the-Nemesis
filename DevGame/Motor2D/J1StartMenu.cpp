#include "j1App.h"
#include "j1Module.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "j1StartMenu.h"


j1StartMenu::j1StartMenu() : j1Module(){

	name.create("startmenu");
}


bool j1StartMenu::Awake(pugi::xml_node& cofing) {

	return true;
}
bool j1StartMenu::Start() {

	return true;
}
bool j1StartMenu::PreUpdate() {

	return true;
}
bool j1StartMenu::Update(float) {

	return true;
}
bool j1StartMenu::PostUpdate() {

	return true;
}
bool j1StartMenu::CleanUp() {

	return true;
}
