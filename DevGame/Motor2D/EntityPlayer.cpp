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






EntityPlayer::EntityPlayer(int x, int y, ENTITY_TYPE type) : Entity(x, y, type)
{

	pugi::xml_document	config_file;
	pugi::xml_node* node = &App->LoadEntitiesAnimation(config_file);
	node = &node->child("player");

	for (pugi::xml_node animations = node->child("animations").child("animation"); animations; animations = animations.next_sibling("animation"))
	{
		std::string ent(animations.attribute("name").as_string());

		if (ent == "idle_right")
			LoadAnimation(animations, &idle_right);
		else if (ent == "idle_left")
			LoadAnimation(animations, &idle_left);
		else if (ent == "running_right")
			LoadAnimation(animations, &running_right);
		else if (ent == "running_left")
			LoadAnimation(animations, &running_left);
		else if (ent == "fall_right")
			LoadAnimation(animations, &fall_right);
		else if (ent == "fall_left")
			LoadAnimation(animations, &fall_left);
		else if (ent == "jumping_left")
			LoadAnimation(animations, &jumping_left);
		else if (ent == "jumping_right")
			LoadAnimation(animations, &jumping_right);
		else if (ent == "attack_right")
			LoadAnimation(animations, &attack_right);
		else if (ent == "attack_left")
			LoadAnimation(animations, &attack_left);
		else if (ent == "die_right")
			LoadAnimation(animations, &die_right);
		else if (ent == "die_left")
			LoadAnimation(animations, &die_left);
		else if (ent == "slide_right")
			LoadAnimation(animations, &slide_right);
		else if (ent == "slide_left")
			LoadAnimation(animations, &slide_left);

		animation = &idle_right;
	}



	Start();

	/*App->audio->fx.add[1] = App->audio->LoadFx("audio/fx/JumpFx.wav");
	App->audio->fx.add[2] = App->audio->LoadFx("audio/fx/HurtFx.wav");*/
}
EntityPlayer::~EntityPlayer() {

	CleanUp();
}

bool EntityPlayer::Start()
{
	LoadTexture();
	App->audio->LoadFx("audio/fx/JumpFx.wav");
	App->audio->LoadFx("audio/fx/HurtFx.wav");

	FindPlayerSpawn();
	SpawnPLayer();
	is_diying = false;
	is_sliding = false;
	is_attacking = false;
	is_jumping = false;
	looking_right = true;
	return true;
}

bool EntityPlayer::Update(float dt)
{

	//if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
	//	App->fade->FadeToBlack(App->scene, App->scene, 0.5f);
	//}

	if (looking_right)
		animation = &idle_right;
	else if (looking_left)
		animation = &idle_left;

	float falling_speed = playerData.gravity;
	if (can_jump)
		falling_speed -= 1.5;

	fPoint tempPos = pos;

	// numbers in CheckCollision calls are there to avoid the character from levitating in a border (collision looks cleaner)
	if (god_mode == false)
	{
		tempPos.y += falling_speed;
		if (CheckCollision(GetPlayerTile({ tempPos.x + 5, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR
			&& CheckCollision(GetPlayerTile({ tempPos.x + 10, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR
			&& is_jumping == false && is_attacking == false && is_sliding == false)
		{

			can_die = false;
			can_slide = false;
			can_attack = false;
			can_jump = false;
			is_falling = true;
			pos = tempPos;
			if (looking_left && can_jump == false)
				animation = &fall_left;
			else if (looking_right && can_jump == false)
				animation = &fall_right;
		}
		else
		{
			is_falling = false;
			can_jump = true;
			can_attack = true;
			can_slide = true;
			can_die = true;
		}

		if (CheckCollision(GetPlayerTile({ tempPos.x + 5, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::DEATH
			&& CheckCollision(GetPlayerTile({ tempPos.x + 10, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::DEATH)
		{
			
			App->audio->PlayFx(2);

			if (is_diying == false && can_die)
			{

				can_die = false;
				die_left.Reset();
				die_right.Reset();
				is_diying = true;
				die_cont = 0;
			}

			if (is_diying) {
				
				if (looking_left)
					animation = &die_left;
				else if (looking_right)
					animation = &die_right;
			}
			if (die_cont == 35)
			{
				is_diying = false;
				SpawnPLayer();
			}
			//App->fade->FadeToBlack(App->scene, App->scene, 0.5f);
			
		}
		else if (CheckCollision(GetPlayerTile({ tempPos.x + 1, tempPos.y - animation->GetCurrentFrame().h - 2})) == COLLISION_TYPE::DEATH
			&& CheckCollision(GetPlayerTile({ tempPos.x + 1, tempPos.y - animation->GetCurrentFrame().h - 2 })) == COLLISION_TYPE::DEATH)
		{
			App->audio->PlayFx(2);
			//App->fade->FadeToBlack(App->scene, App->scene, 0.5f);
			SpawnPLayer();
		}

		//else if (CheckCollision(GetPlayerTile({ tempPos.x - animation->GetCurrentFrame().w, tempPos.y  })) == COLLISION_TYPE::DEATH
		//	&& CheckCollision(GetPlayerTile({ tempPos.x - animation->GetCurrentFrame().w, tempPos.y  })) == COLLISION_TYPE::DEATH)
		//{
		//	App->audio->PlayFx(2);
		//	//App->fade->FadeToBlack(App->scene, App->scene, 0.5f);
		//	if (is_diying == false && can_die)
		//	{

		//		can_die = false;
		//		die_left.Reset();
		//		die_right.Reset();
		//		is_diying = true;
		//		die_cont = 0;
		//	}

		//	if (is_diying) {

		//		if (looking_left)
		//			animation = &die_left;
		//		else if (looking_right)
		//			animation = &die_right;
		//	}
		//	if (die_cont == 35)
		//	{
		//		is_diying = false;
		//		SpawnPLayer();
		//	}
		//}
		else if (CheckCollision(GetPlayerTile({ tempPos.x + 5 + animation->GetCurrentFrame().w , tempPos.y  })) == COLLISION_TYPE::DEATH
			&& CheckCollision(GetPlayerTile({ tempPos.x + 10 + animation->GetCurrentFrame().w, tempPos.y})) == COLLISION_TYPE::DEATH)
		{
			App->audio->PlayFx(2);
			//App->fade->FadeToBlack(App->scene, App->scene, 0.5f);
			if (is_diying == false && can_die)
			{

				can_die = false;
				die_left.Reset();
				die_right.Reset();
				is_diying = true;
				die_cont = 0;
			}

			if (is_diying) {

				if (looking_left)
					animation = &die_left;
				else if (looking_right)
					animation = &die_right;
			}
			if (die_cont == 35)
			{
				is_diying = false;
				SpawnPLayer();
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			tempPos = pos;

			tempPos.x += playerData.speed;

			if (CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y })) == COLLISION_TYPE::AIR
				&& CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR)
			{
				pos.x = tempPos.x;
				if (is_falling == false)
					animation = &running_right;
			}

			else if (CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y })) == COLLISION_TYPE::WIN
				&& CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::WIN)
			{
				App->scene->LoadScene(); //with number 0, LoadScene 
			}

			looking_left = false;
			looking_right = true;
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			tempPos = pos;

			tempPos.x -= playerData.speed;

			if (CheckCollision(GetPlayerTile({ tempPos.x, tempPos.y })) == COLLISION_TYPE::AIR
				&& CheckCollision(GetPlayerTile({ tempPos.x, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR)
			{
				if (tempPos.x >= App->render->camera.x)
					pos.x = tempPos.x;
				if (is_falling == false)
					animation = &running_left;
			}

			looking_left = true;
			looking_right = false;
		}

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN && is_jumping == false && can_jump)
		{
			App->audio->PlayFx(1);
			can_jump = false;
			jumping_left.Reset();
			jumping_right.Reset();
			is_jumping = true;
			cont = 0;
		}

		if (is_jumping)
		{
			tempPos = pos;

			tempPos.y -= playerData.jumpSpeed;
			if (CheckCollision(GetPlayerTile({ tempPos.x + 5, tempPos.y })) == COLLISION_TYPE::AIR
				&& CheckCollision(GetPlayerTile({ tempPos.x + 10, tempPos.y })) == COLLISION_TYPE::AIR)
			{
				if (tempPos.y >= App->render->camera.y)
					pos.y = tempPos.y;
				if (looking_left)
					animation = &jumping_left;
				else if (looking_right)
					animation = &jumping_right;
			}
			if (cont == 35)
			{
				is_jumping = false;
			}
		}

	
	}
	else
	{
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			tempPos.y -= 4;
			if (tempPos.y >= App->render->camera.y)
				pos.y -= 4;
		}
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			tempPos.y += 4;
			if (tempPos.y + animation->GetCurrentFrame().h <= App->render->camera.y + App->win->height)
				pos.y += 4;
		}
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			pos.x += 4;
			animation = &running_right;
			if (CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y })) == COLLISION_TYPE::WIN
				&& CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::WIN)
			{
				App->scene->LoadScene(); //with number 3 LoadScene loads the next map
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			if (tempPos.x >= App->render->camera.x)
				pos.x -= 4;
			animation = &running_left;
		}
	}

	//attack right


	if ((App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN && is_attacking == false && can_attack))
	{
	
		can_attack = false;
		attack_left.Reset();
		attack_right.Reset();
		is_attacking = true;
		attack_cont = 0;
	}
	
	if (is_attacking){
		tempPos = pos;
			if (looking_left)
				animation = &attack_left;
			else if (looking_right)
				animation = &attack_right;
		}
		if (attack_cont == 35)
		{
			is_attacking = false;
			
		}
		//slide

		if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN && is_sliding == false && can_slide) {

			can_slide = false;
			slide_left.Reset();
			slide_right.Reset();
			is_sliding = true;
			slide_cont = 0;
		}
		if (is_sliding) {

			tempPos = pos;

			if (looking_right && CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y })) == COLLISION_TYPE::AIR
				&& CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR) {
				animation = &slide_right;
				pos.x = pos.x++;
				if (CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y })) == COLLISION_TYPE::WIN
					&& CheckCollision(GetPlayerTile({ tempPos.x + animation->GetCurrentFrame().w, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::WIN)
				{
					App->scene->LoadScene(); //with number 3 LoadScene loads the next map
				}
			
			}
			else if (looking_left && CheckCollision(GetPlayerTile({ tempPos.x, tempPos.y })) == COLLISION_TYPE::AIR
				&& CheckCollision(GetPlayerTile({ tempPos.x, tempPos.y + animation->GetCurrentFrame().h })) == COLLISION_TYPE::AIR) {
					animation = &slide_left;
					pos.x = pos.x--;
					
				}
				

				}
			
			if (slide_cont == 35)
			{
				is_sliding = false;
			}
		
			//die
			
	
	die_cont++;
	slide_cont++;
	attack_cont++;
	cont++;
	return true;
}

bool EntityPlayer::CleanUp()
{
	App->tex->UnLoad(texture);

	return true;
}

bool EntityPlayer::Load(pugi::xml_node& data)
{
	pos.x = data.child("position").attribute("x").as_float();
	pos.y = data.child("position").attribute("y").as_float();

	return true;
}

bool EntityPlayer::Save(pugi::xml_node& data) const
{
	pugi::xml_node position = data.append_child("position");

	position.append_attribute("x") = (float)pos.x;
	position.append_attribute("y") = (float)pos.y;

	return true;
}

void EntityPlayer::LoadTexture()
{
	texture = App->tex->Load("textures/Player/spritesheetsmain.png");
}

int EntityPlayer::GetPlayerTile(fPoint pos) const
{
	iPoint position = App->map->WorldToMap(pos.x, pos.y);

	int tile_number = position.y * App->map->data.width + position.x;

	return tile_number;
}

void EntityPlayer::LoadAnimation(pugi::xml_node animation_node, Animation* animation)
{
	bool ret = true;

	for (pugi::xml_node frame = animation_node.child("frame"); frame && ret; frame = frame.next_sibling("frame"))
		animation->PushBack({ frame.attribute("x").as_int() , frame.attribute("y").as_int(), frame.attribute("w").as_int(), frame.attribute("h").as_int() });

	animation->speed = animation_node.attribute("speed").as_float();
	animation->loop = animation_node.attribute("loop").as_bool();

}


void EntityPlayer::FindPlayerSpawn()
{
	p2List_item<MapLayer*>* layer = App->map->data.layers.end;
	for (int i = 0; i < (layer->data->width * layer->data->height); i++)
	{
		if (layer->data->data[i] == 82)
		{
			spawn = App->map->TileToWorld(i);
		}
	}
}

void EntityPlayer::SpawnPLayer()
{
	pos.x = spawn.x;
	pos.y = spawn.y;
	App->render->camera.x = 0;
}