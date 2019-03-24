#include <stdlib.h>
#include "player.h"
#include "simple_logger.h"
#include "gf2d_sprite.h"
#include "gf2d_vector.h"
#include "entity.h"
#include "gf2d_shape.h"
#include "gf2d_collision.h"
#include "gf2d_color.h"
//#include "gf2d_dynamic_body.h"
//#include "gf2d_space.h"

static float frameIncr = 0.0f;
float timerInc = 0.0f;





void player_update(Entity *self);
int player_bodyTouch(struct Body_S *self, struct Body_S *other, Collision *collision)
{
	if (collision->collided = 1)
	{
		slog("Body touch successful");
		return 1;
	}
	else return 0;
}

int player_worldTouch(struct Body_S *self, Collision *collision)
{
	if (collision->collided = 1)
	{
		slog("World touch successful");
		return 1;
	}
	else return 0;
}


Entity *player_new(Vector2D position)
{
	Entity *entity;
	slog("sent");
	entity = ent_new();
	

	if (!entity)
	{
		slog("no player entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	

	entity->sprite = gf2d_sprite_load_all("images/jeff_walk.png", 64, 64, 9);
	entity->frame = 27;
	entity->update = player_update;
	entity->hitbox = gf2d_shape_Rectangle(position.x, position.y, 27, 35);
	gf2d_body_set(&entity->body, entity, PLAYER_LAYER,1,vector2d(position.x,position.y), vector2d(entity->velocity.x,entity->velocity.y),1.0f,0.0f,0.0f,&entity->hitbox,NULL,player_bodyTouch,player_worldTouch);
	return entity;
}
void player_update(Entity *self, Space *space)
{
	const Uint8 *keys;
	timerInc += 0.1f;



	gf2d_shape_draw(self->hitbox, gf2d_Color(0, 0, 0, 1), vector2d(0,0));
	self->hitbox.s.c.x = self->position.x+20;
	self->hitbox.s.c.y = self->position.y+25;
	
	self->frame = 27;
	//self->velocity = vector2d(0, 2);
	
	/*
	ClipFilter ClipFil;
	ClipFil.worldclip = 1;
	ClipFil.cliplayer = 1;
	ClipFil.touchlayer = 1;
	ClipFil.team = 1;*/
	//frameIncr += 0.1f;
	//if (frameIncr > 36.0f)
	//{
	//	frameIncr = 0.0f;
	//}
	
	Collision staticHit = gf2d_space_shape_test(space, self->hitbox);
	self->velocity = vector2d(0, 3);
	if (staticHit.collided >= 1)
	{
		self->velocity = vector2d(0, 0);
		slog("COLLISION");
	}
	if (staticHit.collided = 0)
	{
		self->velocity= vector2d(0, 6);
	}
	self->frame = (int)frameIncr;
	keys = SDL_GetKeyboardState(NULL);
	if (SDL_SCANCODE_W[keys])self->position.y -= 7;
	if (keys[SDL_SCANCODE_A])
	{
		frameIncr = 10.0f;
		frameIncr += 0.1f;
		if (frameIncr > 18.0f)
			frameIncr = 10.0f;
	}
	if (keys[SDL_SCANCODE_A])self->position.x -= 1;
	if (keys[SDL_SCANCODE_D])self->position.x += 1;
	if (keys[SDL_SCANCODE_D])
	{
		
		frameIncr = 28.0f;
		frameIncr += 0.1f;
		if (frameIncr > 36.0f)
			frameIncr = 28.0f;
	}
	//if (keys[SDL_SCANCODE_S])self->position.y += 1;
	vector2d_add(self->position, self->position, self->velocity);
	if (timerInc >= 0.5f)
	{
		self->velocity = vector2d(0, 10);
		timerInc = 0.0;
	}
	//List *colliderList = gf2d_collision_check_space_shape(space, self->hitbox, ClipFilterStatic);
	//for (int i = 0; sizeof(colliderList); i++)
	//{
		//if (colliderList[i].collided=1)
		//{

		//}
	//	slog("collided");
	//}
}




