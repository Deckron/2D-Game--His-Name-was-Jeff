//WAHluigi
#include <stdlib.h>
#include "entity.h"
#include "simple_logger.h"
#include "gf2d_sprite.h"

typedef struct {
	Entity *entityList;
	Uint32 *maxEntities;
}EntityManager;

//create entity manager as static can only be one, and it sits running as its own instance
static EntityManager entityManager = { 0 };




//destroy entity manager

void entity_manager_close()
{
	slog("welcome");
	//iterate through all entities
	int i;
	for (i = 0; i < entityManager.maxEntities; i++)
	{
		//destroy if there
		destroy_entity(&entityManager.entityList[i]);//kills address
	}
	if (entityManager.entityList)//if there is a list of entities, kill
	{
		destroy_entity(entityManager.entityList);
	}
	entityManager.maxEntities = 0;
	entityManager.entityList = NULL;
}

void entity_manager_init(Uint32 maxEnts)
{
	//if max entity value is not present
	if (!maxEnts)
	{
		slog("no entities");
		return;
	}
	//else, allocate memory base on maxent values(and error check)
	entityManager.entityList = (Entity*)malloc(sizeof(Entity)*maxEnts);
	slog("manager check");
	if (!entityManager.entityList)
	{
		slog("failed to allocate memory");
	}

	entityManager.maxEntities = maxEnts;
	//set memory for manipulation
	memset(entityManager.entityList, 0, sizeof(Entity)*maxEnts);
	slog("memory allocated");
	//if exiting the game, destroy entity manager
	atexit(entity_manager_close);
}

//create new entity
Entity *ent_new()
{
	slog("welcome");
	int i;
	for (i = 0; i < entityManager.maxEntities; i++)
	{
		if (entityManager.entityList[i].inUse)
		{
			continue;
		}
		//set flag and make entity
		entityManager.entityList[i].inUse = 1;
		slog("Entity is in use");
		entityManager.entityList[i].scale.x = 1;
		entityManager.entityList[i].scale.y = 1;
		return &entityManager.entityList[i];
	}
	//if no empty entity slots
	slog("all slots taken");
	return NULL;
}



void destroy_entity(Entity *self)
{
	if (!self)
	{
		return;
	}
	if (self->sprite != NULL);
	{
		gf2d_sprite_free(self->sprite);
	}
	memset(self, 0, sizeof(Entity));

}

//draw entity
void draw_ent(Entity *self)
{
	if (!self)
	{
		return;
	}
	gf2d_sprite_draw(
		self->sprite,//sprite
		self->position,//position
		&self->scale,//self scale, address of self ->scale
		NULL,//scaleCenterPoint
		NULL,//rotation
		NULL,//Flip
		NULL,//colorShift
		self->frame);//frame
		//slog("drawn");

}

void update_ent(Entity *self)
{
	if ((!self) || (!self->inUse))return;
	self->frame += 0.35;
	if (self->frame > self->frame_limit)self->frame = 0;
	vector2d_add(self->position, self->position, self->velocity);
	if (self->update)self->update(self);
	//slog("updated");

}