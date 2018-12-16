#ifndef _ENTITYPLAYER_H_
#define _ENTITYPLAYER_H_


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

struct PlayerData
{



	float speed = 80.0f;
	float jumpSpeed = 90.0f;
	float gravity = 150.8f;
	


};



class EntityPlayer :public Entity {

public:

	EntityPlayer(int x, int y, ENTITY_TYPE type);
	~EntityPlayer();


	bool Start();
	bool Update(float dt);
	bool CleanUp();

	int GetPlayerTile(fPoint pos) const;

	bool Load(pugi::xml_node& data);

	bool Save(pugi::xml_node& data) const;

	void LoadAnimation(pugi::xml_node animation_node, Animation* animation);

	void LoadTexture();

	void FindPlayerSpawn();

	void SpawnPLayer();

public:

	//Animation * animation = nullptr;

	Animation idle_right = Animation();
	Animation idle_left = Animation();
	Animation running_right = Animation();
	Animation running_left = Animation();
	Animation jumping_right = Animation();
	Animation jumping_left = Animation();
	Animation die_right = Animation();
	Animation die_left = Animation();
	Animation slide_right = Animation();
	Animation slide_left = Animation();
	Animation fall_right = Animation();
	Animation fall_left = Animation();
	Animation attack_right = Animation();
	Animation attack_left = Animation();


	PlayerData playerData;

	int cont = 0;
	int attack_cont = 0;
	int dash_cont = 0;
	int die_cont = 0;


	bool is_jumping;
	bool is_falling;
	bool can_jump;
	bool is_attacking;
	bool can_attack;
	bool is_dashing;
	bool can_dash;
	bool is_diying;
	bool can_die;


	bool looking_right = false;
	bool looking_left = false;

	bool god_mode = false;

	p2Point<int> spawn;

	fPoint current_pos;
	//SDL_Texture* texture = nullptr;

};


#endif// _ENTITYPLAYER_H_