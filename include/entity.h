#pragma once
#ifndef entity_h
#define entity_h
#include <SDL.h>
#include "gf2d_vector.h"
#include "gf2d_sprite.h"
#include "gf2d_text.h"
#include "simple_logger.h"
#include "gf2d_shape.h"
#include "gf2d_collision.h"
typedef struct entity
{
	int inUse;
	Vector2D position;
	Vector2D scale;
	Vector2D flip;
	Vector2D velocity;
	Sprite *sprite;
	Shape shape;
	Shape hitbox;
	Body body;
	float frame;
	int will_to_live;
	int frame_limit;
	void(*update)(struct entities * entity);
	
}Entity;
/***
manages entities
takes ent limit
return NULL
***/
void entity_manager_init(Uint32 maxEnts);

/***
@brief creates a new entity
@param takes nothing
@return  blank Entity, null if it doesnt work
***/
Entity *ent_new();

void destroy_entity(Entity *entity);


/***
@brief draws a new entity
@param takes entity
@return nothing
***/
void draw_ent(Entity *entity);

/*@brief updates entity
@param takes entity*/
void update_ent(Entity *entity);




#endif