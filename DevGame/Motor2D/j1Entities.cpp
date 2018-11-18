#include "j1Entities.h"
#include "Entity.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Window.h"
#include "j1Audio.h"
#include "EntityPlayer.h"
#include "EntityEnemyAir.h"
#include "EntityEnemyGround.h"
#include "Brofiler/Brofiler.h"

j1Entities::j1Entities() {

	name.create("entities");

}


j1Entities::~j1Entities() {}

bool j1Entities::Awake(pugi::xml_node& config) {

	bool ret = true;
	return ret;
}

bool j1Entities::Start() {

	return true;
}

bool j1Entities::PreUpdate() {

	BROFILER_CATEGORY("PreUpdatej1entities", Profiler::Color::Tomato)
	p2List_item<Entity*>* item = entities.start;
	while (item != nullptr)
	{
		if (item->data->destroy_entity == true) {
			delete item->data;
			entities.del(item);
		}
		item = item->next;
		
	}


	return true;
}

bool j1Entities::Update(float dt) {
	BROFILER_CATEGORY("Updatej1Entities", Profiler::Color::Tomato)

	for (int i = 0; i < entities.count(); ++i) {

		if (entities.At(i) != nullptr) {

			entities.At(i)->data->Update(dt);
		}
	}
	for (int i = 0; i < entities.count(); ++i) {

		if (entities.At(i) != nullptr) {

			entities.At(i)->data->Draw();
		}
	}
	return true;
}

bool j1Entities::CleanUp() {

	p2List_item<Entity*>* item = entities.start;
	while (item != nullptr)
	{
		delete item->data;
		entities.del(item);
		item = item->next;
	}
	return true;
}

bool j1Entities::SpawnEntity(int x, int y, ENTITY_TYPE type) {

	bool ret = false;

	switch (type) {

	case ENTITY_TYPE::PLAYER:
	{

		player = new EntityPlayer(x, y, PLAYER);
		entities.add(player);

		break;
	}
	case ENTITY_TYPE::ENEMYAIR: 
	{

		EntityEnemyAir* enemyair = new EntityEnemyAir(x, y, ENEMYAIR);
		entities.add(enemyair);

		break;
	}
	case ENTITY_TYPE::ENEMYGROUND: 
	{

		EntityEnemyGround* enemyground = new EntityEnemyGround(x, y, ENEMYGROUND);
		entities.add(enemyground);
		
		break;
	}

	default:

		break;
	}

	return ret;

}

EntityPlayer* j1Entities::GetPlayer()const
{

	for (uint i = 0; i < entities.count(); ++i)
	{

		if (entities.At(i) != nullptr)
		{

			if (entities.At(i)->data->type == PLAYER)
			{

				return(EntityPlayer*)entities.At(i);
			}
		}
	}
	return nullptr;

}


EntityEnemyAir* j1Entities::GetEnemyAir()const 
{

	for (uint i = 0; i < entities.count(); ++i)
	{

		if (entities.At(i) != nullptr)
		{

			if (entities.At(i)->data->type == ENEMYAIR) 
			{

				return(EntityEnemyAir*)entities.At(i);
			}
		}
	}
	return nullptr;

}

EntityEnemyGround* j1Entities::GetEnemyGround()const 
{

	for (uint i = 0; i < entities.count(); ++i)
	{
		if (entities.At(i) != nullptr)
		{
			if (entities.At(i)->data->type == ENEMYGROUND) 
			{
				return(EntityEnemyGround*)entities.At(i);
			}
		}
	}
	return nullptr;

}

