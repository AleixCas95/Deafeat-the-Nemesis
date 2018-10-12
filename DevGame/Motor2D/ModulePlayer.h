#ifndef _j1PLAYER_H__
#define _j1PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;

enum ANIMATION_STATE 
{
	IDLE_LEFT,
	IDLE_RIGHT,
	RUNNING_LEFT,
	RUNNING_RIGHT,
	JUMPING_LEFT,
	JUMPING_RIGHT
};

struct PlayerData 
{

	int player_width = 25;
	int player_height = 30;

	fPoint pos;

	float speed = 350.0f;
	float jumpSpeed = 800.0f;

	ANIMATION_STATE anim_state;
};

class ModulePlayer : public j1Module
{
public:

	ModulePlayer();
	virtual ~ModulePlayer();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	int GetPlayerTile(fPoint pos) const;

	bool Load(pugi::xml_node& data);

	bool Save(pugi::xml_node& data) const;

	void LoadTexture();

	void FindPlayerSpawn();

	void SpawnPlayer();

public:

	Animation* animation = nullptr;

	Animation idle_right = Animation();
	Animation idle_left = Animation();
	Animation running_right = Animation();
	Animation running_left = Animation();
	Animation jumping_right = Animation();
	Animation jumping_left = Animation();

	PlayerData playerData;

	fPoint initial_pos;

	bool looking_right = false;
	bool looking_left = false;

	SDL_Texture* texture = nullptr;

	p2Point<int> spawn;

};

#endif