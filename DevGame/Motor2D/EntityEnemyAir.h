#ifndef _ENTITYENEMYAIR_H_
#define _ENTITYENEMYAIR_H_


#include "Entity.h"
#include "j1Entities.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Audio.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "ModuleFadeToBlack.h"
#include "j1Window.h"
#include "Animation.h"


struct SDL_Texture;




class EntityEnemyAir:public Entity {

public:

	EntityEnemyAir(int x, int y, ENTITY_TYPE type);
	~EntityEnemyAir();


	bool Start();
	bool Update(float dt);
	bool CleanUp();

	int GetEnemyAirTile(fPoint pos) const;

	bool Load(pugi::xml_node& data);

	bool Save(pugi::xml_node& data) const;

	void LoadAnimation(pugi::xml_node animation_node, Animation* animation);

	void LoadTexture();



public:

	//Animation * animation = nullptr;

	Animation idle = Animation();
	Animation flyingright = Animation();
	Animation flyingleft = Animation();
	Animation dyingfront = Animation();
	Animation dyingright = Animation();
	Animation dyingleft = Animation();
	


	bool looking_front = false;


	fPoint enemy_air_position;
	fPoint origin_pos;
	fPoint player_pos;
	float distance_to_player;
	int action_margin = 10000;
	iPoint spawn = iPoint(96,400);
	iPoint speed;


};


#endif// _ENTITYENEMYAIR_H_