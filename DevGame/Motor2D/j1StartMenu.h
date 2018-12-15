#ifndef _J1_START_MENU_
#define _J1_START_MENU_

#include "j1Module.h"


class UIImage;
class UILabel;
class UIObject;


class j1StartMenu : public j1Module {

public:
	j1StartMenu();
	~j1StartMenu(){}


	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float);
	bool PostUpdate();
	bool CleanUp();

	UIObject * background = nullptr;
	UIObject * play_button = nullptr;
	UIObject * settings_button = nullptr;
	UIObject * credits_button = nullptr;
	UIObject * exit_button = nullptr;
	UIObject * continue_button = nullptr;
	
	UIObject* text_start = nullptr;
	UIObject* text_continue = nullptr;
	UIObject* text_settings = nullptr;
	UIObject* text_credits = nullptr;
	UIObject* text_title = nullptr;
	UIObject* text_exit = nullptr;

	bool close_game=false;
	

};


#endif // !_J1_START_MENU_

