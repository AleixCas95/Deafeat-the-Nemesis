#include "EntityEnemyGround.h"
#include "EntityPlayer.h"
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
#include "j1Pathfinding.h"
#include "Brofiler/Brofiler.h"

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

	player_pos2 = App->entities->player->pos;
	last_pos = pos;

	looking_left = true;
	is_diying = false;
	can_die;
	
	return true;
}

bool EntityEnemyGround::Update(float dt)
{
	BROFILER_CATEGORY("UpdateEntityEnemyGround", Profiler::Color::BurlyWood)



		player_pos2 = App->entities->player->pos;

	distance_to_player2 = pos.DistanceNoSqrt(player_pos2);

	enemy_ground_position = App->map->WorldToMap(pos.x, pos.y);

	player_map_position2 = App->map->WorldToMap(player_pos2.x, player_pos2.y);

	const p2DynArray<iPoint>* path;

	if (distance_to_player2 < action_margin2 && distance_to_player2 > -action_margin2)
	{
		if (App->pathfinding->CreatePath(enemy_ground_position, player_map_position2) != -1)
		{

			path = App->pathfinding->GetLastPath();

			if (path->Count() > 0)
			{

				next_path_step2 = iPoint(path->At(0)->x, path->At(0)->y);

				if (next_path_step2.x < enemy_ground_position.x)
				{

					speedenemy.x = -50 * dt;
					animation = &runningleft;

				}
				else if (next_path_step2.x > enemy_ground_position.x)
				{

					speedenemy.x = 50 * dt;
					animation = &runningright;

				}
			}

		}
		else if (App->pathfinding->CreatePath(enemy_ground_position, player_map_position2) == -1)
		{

			path = nullptr;
			speedenemy.x = 0;
			speedenemy.y = 0;
			animation = &idleright;
		}
	}
	/*else
	{
		path = nullptr;
		speedenemy.x = 0;
		speedenemy.y = 0;
		animation = &idleleft;
	}*/

	last_pos = pos;
	pos += speedenemy;

	if (enemy_ground_position.x == player_map_position2.x && enemy_ground_position.y-1 == player_map_position2.y && App->entities->player->god_mode != true) {
		die_cont = 0;
		is_diying = true;
		if (is_diying) {
			App->audio->PlayFx(2);

		}

		if (die_cont = 35) {
			is_diying = false;

		}
		App->entities->player->destroy_entity = true;
		App->entities->CleanUp();

		App->entities->SpawnEntity(0, 0, PLAYER);
		iPoint spawnenemy;
		iPoint spawnenemy2;
		p2List_item<MapLayer*>* layer = App->map->data.layers.end;
		for (int i = 0; i < (layer->data->width * layer->data->height); i++)
		{
			if (layer->data->data[i] == 105)
			{
				spawnenemy = App->map->TileToWorld(i);
				App->entities->SpawnEntity(spawnenemy.x, spawnenemy.y, ENEMYAIR);

			}
			if (layer->data->data[i] == 107)
			{
				spawnenemy2 = App->map->TileToWorld(i);
				App->entities->SpawnEntity(spawnenemy2.x, spawnenemy2.y, ENEMYGROUND);

			}
		}
	}
	die_cont++;
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

	texture = App->tex->Load("textures/Player/spritesheetsenemy.png");

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
