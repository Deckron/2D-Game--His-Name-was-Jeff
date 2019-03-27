#include <stdlib.h>
#include "projectile.h"
#include "simple_logger.h"
#include "gf2d_sprite.h"
#include "gf2d_vector.h"
#include "entity.h"
#include "gf2d_shape.h"
#include "gf2d_collision.h"
#include "gf2d_color.h"
#include "player.h"




static float frameIncr = 0.0f;
static float timer = 0.0f;


void projectile_update(Entity *self);
int projectile_bodyTouch(struct Body_S *self, struct Body_S *other, Collision *collision)
{
	if (collision->collided = 1)
	{
		slog("Body touch successful");
		return 1;
	}
	else return 0;
}

int projectile_worldTouch(struct Body_S *self, Collision *collision)
{
	if (collision->collided = 1)
	{
		slog("World touch successful");
		return 1;
	}
	else return 0;
}


Entity *projectile_new(Vector2D position)
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



	entity->sprite = gf2d_sprite_load_all("images/Axe_You_A_Question.png", 64, 64, 1);
	entity->frame = 1;
	entity->update = projectile_update;
	entity->hitbox = gf2d_shape_Rectangle(position.x, position.y, 10, 10);
	gf2d_body_set(&entity->body, "entity", PLAYER_LAYER, 1, vector2d(position.x, position.y), vector2d(entity->velocity.x, entity->velocity.y), 1.0f, 0.0f, 0.0f, &entity->hitbox, NULL, projectile_bodyTouch, projectile_worldTouch);
	return entity;
}
void projectile_update(Entity *self, Space *space, Entity *player)
{
	//const Uint8 *keys;
	timer += 0.1f;
	
	
	if (player->position.x - self->position.x < 0)//less that if creature is to the right of player
	{
		self->velocity.x = -1;
	}
	else
	{
		self->velocity.x = 1;
	}

	gf2d_shape_draw(self->hitbox, gf2d_Color(0, 0, 0, 1), vector2d(0, 0));
	self->hitbox.s.c.x = self->position.x + 20;
	self->hitbox.s.c.y = self->position.y + 25;
	self->frame = (int)frameIncr;
	ClipFilter filter; 
	filter.layer = 1; 
	filter.team = 1;
	//Collision staticHit = gf2d_space_shape_test(space, player->hitbox);
	Collision staticHit;
	gf2d_space_body_collision_test_filter(space, self->hitbox, &staticHit, filter);
//		Collision bodyHit;
	

//	gf2d_space_body_collision_test_filter(space, self->hitBox, &bodyHit, filter);


	if (timer < 1.0f)
	{
		return 0;
	}
	else if (timer >= 1.0f)
	{
		//projectile_new(vector2d(mage->position.x, mage->position.y), self);
		draw_ent(self);
	}
	if (timer >= 2.0f)
	{
		timer = 0.0f;
	}
	
	
	
	if (filter.team = 1)
	{
		
		destroy_entity(self);
		
	}
	
	vector2d_add(self->position, self->position, self->velocity);
	
}




