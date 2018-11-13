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
#include "j1Entities.h"
#include "Animation.h"


struct SDL_Texture;

struct EnemyAirData
{


};



class EntityEnemyAir:public Entity {

public:

	EntityEnemyAir(int x, int y, ENTITY_TYPE type);
	~EntityEnemyAir();


	bool Start();
	bool Update(float dt);
	bool CleanUp();

	int GetPlayerTile(fPoint pos) const;

	bool Load(pugi::xml_node& data);

	bool Save(pugi::xml_node& data) const;

	void LoadAnimation(pugi::xml_node animation_node, Animation* animation);

	void LoadTexture();

	void FindEntityEnemySpawn();

	void SpawnEnemyAir();
	

public:

	//Animation * animation = nullptr;

	Animation idle = Animation();
	Animation flyingright = Animation();
	Animation flyingleft = Animation();
	Animation dyingfront = Animation();
	Animation dyingright = Animation();
	Animation dyingleft = Animation();
	

	EnemyAirData enemy1Data;

	bool looking_front = false;


	p2Point<int> spawn;



};


#endif// _ENTITYENEMYAIR_H_