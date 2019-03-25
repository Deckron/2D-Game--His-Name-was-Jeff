#include <stdlib.h>
#include "floater.h"
#include "simple_logger.h"
#include "gf2d_sprite.h"
#include "gf2d_vector.h"
#include "entity.h"
#include "gf2d_shape.h"
#include "gf2d_collision.h"
#include "gf2d_color.h"
#include "gobl.h"




static float frameIncr = 0.0f;
float timer = 0.0f;






void gobl_update(Entity *self);
int gobl_bodyTouch(struct Body_S *self, struct Body_S *other, Collision *collision)
{
	if (collision->collided = 1)
	{
		slog("Body touch successful");
		return 1;
	}
	else return 0;
}

int gobl_worldTouch(struct Body_S *self, Collision *collision)
{
	if (collision->collided = 1)
	{
		slog("World touch successful");
		return 1;
	}
	else return 0;
}


Entity *gobl_new(Vector2D position)
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



	entity->sprite = gf2d_sprite_load_all("images/gobl.png", 25, 55, 4);
	entity->frame = 1;
	entity->update = gobl_update;
	entity->hitbox1 = gf2d_shape_Rectangle(position.x, position.y, 27, 27);
	gf2d_body_set(&entity->body, "entity", PLAYER_LAYER, 1, vector2d(position.x, position.y), vector2d(entity->velocity.x, entity->velocity.y), 1.0f, 0.0f, 0.0f, &entity->hitbox, NULL, gobl_bodyTouch, gobl_worldTouch);
	return entity;
}
void gobl_update(Entity *self, Space *space, Entity *player)
{
	//const Uint8 *keys;
	timer += 0.01f;
	self->velocity = vector2d(0, 2);
	frameIncr += 0.1f;
	if (frameIncr > 4.0f)
	{
		frameIncr = 0.0f;
	}

	//self->velocity = vector2d(1, 1);
	Collision staticHit = gf2d_space_shape_test(space, self->hitbox1);
	self->velocity = vector2d(0, 3);
	if (staticHit.collided >= 1)
	{
		self->velocity = vector2d(0, 0);
		//slog("COLLISION");
	}
	if (player->position.x - self->position.x < 0)//less that if creature is to the right of player
	{
		self->velocity.x = -1;
	}
	else
	{
		self->velocity.x = 1;
	}
	
	
	

	gf2d_shape_draw(self->hitbox1, gf2d_Color(0, 0, 0, 1), vector2d(0, 0));
	self->hitbox1.s.c.x = self->position.x + 20;
	self->hitbox1.s.c.y = self->position.y + 25;






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




