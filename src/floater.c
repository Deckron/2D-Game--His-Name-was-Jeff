#include <stdlib.h>
#include "floater.h"
#include "simple_logger.h"
#include "gf2d_sprite.h"
#include "gf2d_vector.h"
#include "entity.h"
#include "gf2d_shape.h"
#include "gf2d_collision.h"
#include "gf2d_color.h"




static float frameIncr = 0.0f;
//float timerInc = 0.0f;






void floater_update(Entity *self);
int floater_bodyTouch(struct Body_S *self, struct Body_S *other, Collision *collision)
{
	if (collision->collided = 1)
	{
		slog("Body touch successful");
		return 1;
	}
	else return 0;
}

int floater_worldTouch(struct Body_S *self, Collision *collision)
{
	if (collision->collided = 1)
	{
		slog("World touch successful");
		return 1;
	}
	else return 0;
}


Entity *floater_new(Vector2D position)
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



	entity->sprite = gf2d_sprite_load_all("images/zombie7.png", 64, 64, 3);
	entity->frame = 1;
	entity->update = floater_update;
	entity->hitbox = gf2d_shape_Rectangle(position.x, position.y, 27, 27);
	gf2d_body_set(&entity->body, "entity", MONSTER_LAYER, 1, vector2d(position.x, position.y), vector2d(entity->velocity.x, entity->velocity.y), 1.0f, 0.0f, 0.0f, &entity->hitbox, NULL, floater_bodyTouch, floater_worldTouch);
	//entity->enemy_update = floater_update;
	return entity;
}
void floater_update(Entity *self, Space *space, Entity *player)
{
	//const Uint8 *keys;
	//timerInc += 0.1f;
	frameIncr += 0.1f;
	if (frameIncr > 12.0f)
	{
		frameIncr = 0.0f;
	}
	ClipFilter filter; filter.layer = 2; filter.team = 2;
	Collision staticHit;
	gf2d_space_body_collision_test_filter(space, self->hitbox, &staticHit, filter);
	//self->velocity = vector2d(1, 1);
	
	if (player->position.x-self->position.x<0)//less that if creature is to the right of player
	{
		self->velocity.x = -1;
	}
	else
	{
		self->velocity.x = 1;
	}
	if (player->position.y - self->position.y < 0)
	{
		self->velocity.y = -1;
	}
	else
	{
		self->velocity.y = 1;
	}

	gf2d_shape_draw(self->hitbox, gf2d_Color(0, 0, 0, 1), vector2d(0, 0));
	self->hitbox.s.c.x = self->position.x + 20;
	self->hitbox.s.c.y = self->position.y + 25;

	
	


	
	self->frame = (int)frameIncr;
	
	//if (keys[SDL_SCANCODE_S])self->position.y += 1;
	vector2d_add(self->position, self->position, self->velocity);
	//if (timerInc >= 0.5f)
	//{
	//	self->velocity = vector2d(0, 10);
	//	timerInc = 0.0;
	//}
	//List *colliderList = gf2d_collision_check_space_shape(space, self->hitbox, ClipFilterStatic);
	//for (int i = 0; sizeof(colliderList); i++)
	//{
		//if (colliderList[i].collided=1)
		//{

		//}
	//	slog("collided");
	//}
}




