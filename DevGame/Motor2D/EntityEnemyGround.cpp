#include "EntityEnemyGround.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Audio.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "ModuleFadeToBlack.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Entities.h"

EntityEnemyGround::EntityEnemyGround(int x, int y, ENTITY_TYPE type) :Entity(x, y, type) 
{

	pugi::xml_document config_file;
	pugi::xml_node* node = &App->LoadEntitiesAnimation(config_file);
	node = &node->child("groundenemy");

	for (pugi::xml_node animations = node->child("animations").child("animation"); animations; animations = animations.next_sibling("animation")) 
	{
		std::string entenemy2(animations.attribute("name").as_string());

		if (entenemy2 == "idleright")
			LoadAnimation(animations, &idleright);
		else if (entenemy2 == "idleleft")
			LoadAnimation(animations, &idleleft);
		else if (entenemy2 == "runningright")
			LoadAnimation(animations, &runningright);
		else if (entenemy2 == "runningleft")
			LoadAnimation(animations, &runningleft);
		else if (entenemy2 == "fallright")
			LoadAnimation(animations, &fallright);
		else if (entenemy2 == "fallleft")
			LoadAnimation(animations, &fallleft);
		else if (entenemy2 == "jumpingleft")
			LoadAnimation(animations, &jumpingleft);
		else if (entenemy2 == "jumpingright")
			LoadAnimation(animations, &jumpingright);
		else if (entenemy2 == "attackright")
			LoadAnimation(animations, &attackright);
		else if (entenemy2 == "attackleft")
			LoadAnimation(animations, &attackleft);
		else if (entenemy2 == "slideright")
			LoadAnimation(animations, &slideright);
		else if (entenemy2 == "slideleft")
			LoadAnimation(animations, &slideleft);
		else if (entenemy2 == "dieright")
			LoadAnimation(animations, &dieright);
		else if (entenemy2 == "dieleft")
			LoadAnimation(animations, &dieleft);

		animation = &idleleft;
	}

	Start();

}

EntityEnemyGround::~EntityEnemyGround() 
{
	CleanUp();
}

bool EntityEnemyGround::Start()
{
	LoadTexture();

	looking_left = true;
	
	return true;
}

bool EntityEnemyGround::Update(float dt) 
{
	
	if (looking_left)
		animation = &idleleft;
	return true;

}

bool EntityEnemyGround::CleanUp()
{
	
	App->tex->UnLoad(texture);

	return true;

}

bool EntityEnemyGround::Load(pugi::xml_node& data)
{

	pos.x = data.child("position").attribute("x").as_float();
	pos.y = data.child("position").attribute("y").as_float();

	return true;

}

bool EntityEnemyGround::Save(pugi::xml_node&data)const 
{

	pugi::xml_node position = data.append_child("position");

	position.append_attribute("x") = (float)pos.x;
	position.append_attribute("y") = (float)pos.y;

	return true;

}

void EntityEnemyGround::LoadTexture()
{

	texture = App->tex->Load("textures/Player/spritesheetenemy.png");

}

int EntityEnemyGround::GetEnemyGroundTile(fPoint pos)const
{

	iPoint position = App->map->WorldToMap(pos.x, pos.y);

	int tile_number = position.y*App->map->data.width + position.x;

	return tile_number;

}

void EntityEnemyGround::LoadAnimation(pugi::xml_node animation_node, Animation* animation) 
{

	bool ret = true;

	for (pugi::xml_node frame = animation_node.child("frame"); frame&&ret; frame = frame.next_sibling("frame")) 
	{
		animation->PushBack({ frame.attribute("x").as_int() , frame.attribute("y").as_int(), frame.attribute("w").as_int(), frame.attribute("h").as_int() });
	}

	animation->speed = animation_node.attribute("speed").as_float();
	animation->loop = animation_node.attribute("loop").as_bool();

}
