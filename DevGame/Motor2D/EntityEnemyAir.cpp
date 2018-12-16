#include "EntityEnemyAir.h"
#include "EntityPlayer.h"
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
#include "j1Pathfinding.h"
#include "Brofiler/Brofiler.h"

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
		

		animation = &idle;
	}


	
	Start();

	
}
EntityEnemyAir::~EntityEnemyAir() {

	CleanUp();
}

bool EntityEnemyAir::Start()
{
	
	LoadTexture();

	
	is_diying=false;
	can_die;
	
	player_pos = App->entities->player->pos;
	last_pos = pos;
	
	
	looking_front = true;

	return true;
}

bool EntityEnemyAir::Update(float dt)
{
	BROFILER_CATEGORY("UpdateEntityEnemyAir", Profiler::Color::OliveDrab)

	
	//update player position
	player_pos = App->entities->player->pos;

	//distance from enemy to player
	distance_to_player = pos.DistanceNoSqrt(player_pos);

	//enemy map position
	enemy_air_position = App->map->WorldToMap(pos.x, pos.y);

	//player map position
	player_map_position = App->map->WorldToMap(player_pos.x, player_pos.y-1);


	
	const p2DynArray<iPoint>* path;
	//if player is in range of pathing
	if (distance_to_player < action_margin && distance_to_player > -action_margin) {
		//if the function creates the path
		if ((App->pathfinding->CreatePath(enemy_air_position, player_map_position) != -1))
		{
			path = App->pathfinding->GetLastPath();

			if (path->Count() > 0) {
				
				next_path_step = iPoint(path->At(0)->x, path->At(0)->y);
				if (next_path_step.x < enemy_air_position.x)
				{
					speedenemy.x = -50 * dt;
					animation = &flyingleft;
				}
				else if (next_path_step.x > enemy_air_position.x)
				{
					speedenemy.x = 50 * dt;
					animation = &flyingright;
				}
				if (next_path_step.y < enemy_air_position.y)
				{
					speedenemy.y = -50 * dt;
				}
				if (next_path_step.y > enemy_air_position.y)
				{
					speedenemy.y = +50 * dt;
				}
			}
		}	
	}
	else {
		path = nullptr;
		speedenemy.x = 0;
		speedenemy.y = 0;
		animation = &idle;
	}

	last_pos = pos;
	pos += speedenemy;

	if (enemy_air_position.x == player_map_position.x && enemy_air_position.y == player_map_position.y  && App->entities->player->god_mode != true && App->entities->player->is_attacking ==false && App->entities->player->is_dashing ==false) {
		die_cont = 0;
		is_diying = true;
		if (is_diying) {
			
			
		}

		if (die_cont = 35) {
			is_diying = false;
			
		}
		App->entities->player->destroy_entity = true;

		App->entities->CleanUp();
		iPoint spawn;
		p2List_item<MapLayer*>* layer = App->map->data.layers.end;
		for (int i = 0; i < (layer->data->width * layer->data->height); i++) {
			if (layer->data->data[i] == 82)
			{
				App->scene->lifes -= 1;
				App->audio->PlayFx(2);
				spawn = App->map->TileToWorld(i);
				App->entities->SpawnEntity(spawn.x, spawn.y, PLAYER);
				
			}
			if (layer->data->data[i] == 105)
			{
				spawn = App->map->TileToWorld(i);
				App->entities->SpawnEntity(spawn.x, spawn.y, ENEMYAIR);

			}
			if (layer->data->data[i] == 107)
			{
				spawn = App->map->TileToWorld(i);
				App->entities->SpawnEntity(spawn.x, spawn.y, ENEMYGROUND);


			}
		}



	}
	if (enemy_air_position.x == player_map_position.x && enemy_air_position.y == player_map_position.y && App->entities->player->god_mode != true && App->entities->player->is_attacking == true) {

		destroy_entity = true;

	}
	if (enemy_air_position.x == player_map_position.x && enemy_air_position.y == player_map_position.y && App->entities->player->god_mode != true && App->entities->player->is_dashing == true) {

		destroy_entity = true;

	}
	die_cont++;
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
	texture = App->tex->Load("textures/Player/spritesheetenemy2.png");
}

int EntityEnemyAir::GetEnemyAirTile(fPoint pos) const
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


