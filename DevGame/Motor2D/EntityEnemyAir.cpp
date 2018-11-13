#include "EntityEnemyAir.h"
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

EntityEnemyAir::EntityEnemyAir(int x, int y, ENTITY_TYPE type) : Entity(x, y, type)
{

	pugi::xml_document	config_file;
	pugi::xml_node* node = &App->LoadEntitiesAnimation(config_file);
	node = &node->child("airenemy");

	for (pugi::xml_node animations = node->child("animations").child("animation"); animations; animations = animations.next_sibling("animation"))
	{
		std::string entenemy1(animations.attribute("name").as_string());

		if (entenemy1 == "idle")
			LoadAnimation(animations, &idle);
		else if (entenemy1 == "flyingright")
			LoadAnimation(animations, &flyingright);
		else if (entenemy1 == "flyingleft")
			LoadAnimation(animations, &flyingleft);
		else if (entenemy1 == "dyingfront")
			LoadAnimation(animations, &dyingfront);
		else if (entenemy1 == "dyingright")
			LoadAnimation(animations, &dyingright);
		else if (entenemy1 == "dyingleft")
			LoadAnimation(animations, &dyingleft);
	}



	Start();

	/*App->audio->fx.add[1] = App->audio->LoadFx("audio/fx/JumpFx.wav");
	App->audio->fx.add[2] = App->audio->LoadFx("audio/fx/HurtFx.wav");*/
}
EntityEnemyAir::~EntityEnemyAir() {

	CleanUp();
}

bool EntityEnemyAir::Start()
{
	LoadTexture();
	/*App->audio->LoadFx("audio/fx/JumpFx.wav");
	App->audio->LoadFx("audio/fx/HurtFx.wav");
*/
	FindEntityEnemySpawn();
	SpawnEnemyAir();
	looking_front = true;

	return true;
}

bool EntityEnemyAir::Update(float dt)
{

	if (looking_front)
		animation = &idle;
	
	return true;
}

bool EntityEnemyAir::CleanUp()
{
	App->tex->UnLoad(texture);

	return true;
}

bool EntityEnemyAir::Load(pugi::xml_node& data)
{
	pos.x = data.child("position").attribute("x").as_float();
	pos.y = data.child("position").attribute("y").as_float();

	return true;
}

bool EntityEnemyAir::Save(pugi::xml_node& data) const
{
	pugi::xml_node position = data.append_child("position");

	position.append_attribute("x") = (float)pos.x;
	position.append_attribute("y") = (float)pos.y;

	return true;
}

void EntityEnemyAir::LoadTexture()
{
	texture = App->tex->Load("textures/Player/spritesheetenemi2.png");
}

int EntityEnemyAir::GetPlayerTile(fPoint pos) const
{
	iPoint position = App->map->WorldToMap(pos.x, pos.y);

	int tile_number = position.y * App->map->data.width + position.x;

	return tile_number;
}

void EntityEnemyAir::LoadAnimation(pugi::xml_node animation_node, Animation* animation)
{
	bool ret = true;

	for (pugi::xml_node frame = animation_node.child("frame"); frame && ret; frame = frame.next_sibling("frame"))
		animation->PushBack({ frame.attribute("x").as_int() , frame.attribute("y").as_int(), frame.attribute("w").as_int(), frame.attribute("h").as_int() });

	animation->speed = animation_node.attribute("speed").as_float();
	animation->loop = animation_node.attribute("loop").as_bool();

}


void EntityEnemyAir::FindEntityEnemySpawn()
{
	p2List_item<MapLayer*>* layer = App->map->data.layers.end;
	for (int i = 0; i < (layer->data->width * layer->data->height); i++)
	{
		if (layer->data->data[i] == 105)
		{
			spawn = App->map->TileToWorld(i);
		}
	}
}

void EntityEnemyAir::SpawnEnemyAir()
{
	pos.x = spawn.x;
	pos.y = spawn.y;
	App->render->camera.x = 0;
}