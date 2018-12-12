#include "j1App.h"
#include "j1Textures.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "j1Module.h"
#include "p2Log.h"
#include "UIImage.h"
#include "UIObject.h"
#include "p2List.h"

j1Gui::j1Gui() : j1Module() {

	name.create("gui");

}


j1Gui::~j1Gui(){}

bool j1Gui::Awake(pugi::xml_node& conf) {

	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

bool j1Gui::Start() {

	atlas = App->tex->Load(atlas_file_name.GetString());
	return true;
}

bool j1Gui::PreUpdate() {


	return true;
}

bool j1Gui::Update(float dt) {

	for (int i = 0; i < UIObjects.count(); ++i) {

		if (UIObjects.At(i) != nullptr) {

			UIObjects.At(i)->data->Draw();
		}
	}

	return true;
}

bool j1Gui::PostUpdate() {

	return true;
}

bool j1Gui::CleanUp() {

	return true;
}


UIObject* j1Gui::CreateUIImage(int x, int y, SDL_Rect rect, SDL_Texture* texture) {

	if (texture == nullptr) {
		UIImage* image = new UIImage(x ,y, rect, atlas);

		UIObjects.add(image);
		return image;

	
	}
	else {
		UIImage* image = new UIImage(x, y, rect, texture);

		UIObjects.add(image);
		return image;


	}

	
}