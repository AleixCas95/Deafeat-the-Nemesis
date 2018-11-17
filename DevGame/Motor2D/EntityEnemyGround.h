#ifndef _ENTITYENEMYGROUND_H_
#define  _ENTITYENEMYGROUND_H_


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


class EntityEnemyGround :public Entity{

public:

	EntityEnemyGround(int x, int y, ENTITY_TYPE type);
	~EntityEnemyGround();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	int GetEnemyGroundTile(fPoint pos) const;

	bool Load(pugi::xml_node& data);

	bool Save(pugi::xml_node& data) const;

	void LoadAnimation(pugi::xml_node animation_node, Animation* animation);

	void LoadTexture();

public:

	Animation idleright = Animation();
	Animation idleleft = Animation();
	Animation runningright = Animation();
	Animation runningleft = Animation();
	Animation fallright = Animation();
	Animation fallleft = Animation();
	Animation jumpingleft = Animation();
	Animation jumpingright = Animation();
	Animation attackright = Animation();
	Animation attackleft = Animation();
	Animation slideright = Animation();
	Animation slideleft = Animation();
	Animation dieright = Animation();
	Animation dieleft = Animation();


	bool looking_left = false;

	iPoint enemy_ground_position;
	iPoint player_map_position2;
	
	fPoint player_pos2;
	float distance_to_player2;
	int action_margin2 = 45000;
	iPoint next_path_step2;

};

#endif // _ENTITYENEMYGROUND_H_