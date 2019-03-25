#include <stdlib.h>
#include "floater.h"
#include "simple_logger.h"
#include "gf2d_sprite.h"
#include "gf2d_vector.h"
#include "entity.h"
#include "gf2d_shape.h"
#include "gf2d_collision.h"
#include "gf2d_color.h"
#include "mage.h"




static float frameIncr = 0.0f;
static float timer = 0.0f;





void mage_update(Entity *self);
int mage_bodyTouch(struct Body_S *self, struct Body_S *other, Collision *collision)
{
	if (collision->collided = 1)
	{
		slog("Body touch successful");
		return 1;
	}
	else return 0;
}

int mage_worldTouch(struct Body_S *self, Collision *collision)
{
	if (collision->collided = 1)
	{
		slog("World touch successful");
		return 1;
	}
	else return 0;
}


Entity *mage_new(Vector2D position)
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



	entity->sprite = gf2d_sprite_load_all("images/mage.png", 64, 64, 9);
	entity->frame = 1;
	entity->update = mage_update;
	entity->hitbox = gf2d_shape_Rectangle(position.x, position.y, 27, 27);
	gf2d_body_set(&entity->body, "entity", PLAYER_LAYER, 1, vector2d(position.x, position.y), vector2d(entity->velocity.x, entity->velocity.y), 1.0f, 0.0f, 0.0f, &entity->hitbox, NULL, mage_bodyTouch, mage_worldTouch);
	return entity;
}
void mage_update(Entity *self, Space *space, Entity *player)
{
	//const Uint8 *keys;
	timer += 0.01f;
	self->velocity = vector2d(0, 2);
	frameIncr += 0.1f;
	if (frameIncr > 36.0f)
	{
		frameIncr = 0.0f;
	}

	//self->velocity = vector2d(1, 1);
	Collision staticHit = gf2d_space_shape_test(space, self->hitbox);
	//self->velocity = vector2d(0, 3);
	if (staticHit.collided >= 1)
	{
		self->velocity = vector2d(0, 0);
		//slog("COLLISION");
	}

	if (timer < 1.0f)
	{
		self->position.x -= 1;
	}
	else if (timer >= 1.0f)
	{
		self->position.x += 1;

	}
	if (timer >= 2.0f)
	{
		timer = 0.0f;
	}



	if (timer < 1.0f)
	{
		return 0;
	}
	else if (timer >= 1.0f)
	{
		//draw_ent(projectile);

	}
	if (timer >= 2.0f)
	{
		timer = 0.0f;
	}


	gf2d_shape_draw(self->hitbox, gf2d_Color(0, 0, 0, 1), vector2d(0, 0));
	self->hitbox.s.c.x = self->position.x + 20;
	self->hitbox.s.c.y = self->position.y + 25;
	self->frame = (int)frameIncr;

	//if (keys[SDL_SCANCODE_S])self->position.y += 1;
	vector2d_add(self->position, self->position, self->velocity);
	
}




