#include <stdlib.h>
#include "player.h"
#include "simple_logger.h"
#include "gf2d_sprite.h"
#include "gf2d_vector.h"
#include "entity.h"

static float frameIncr = 0.0f;


void player_update(Entity *self);


Entity *player_new(Vector2D position)
{
	Entity *entity = NULL;
	slog("sent");
	entity = ent_new();
	

	if (!entity)
	{
		slog("no player entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/space_bug.png", 128, 128, 16);
	entity->frame = 1;
	entity->update = player_update;
	return entity;
}
void player_update(Entity *self)
{
	const Uint8 *keys;
	
	frameIncr += 0.1f;
	if (frameIncr > 16.0f)
	{
		frameIncr = 0.0f;
	}
	self->frame = (int)frameIncr;
	keys = SDL_GetKeyboardState(NULL);
	if (SDL_SCANCODE_W[keys])self->position.y -= 1;
	if (keys[SDL_SCANCODE_A])self->position.x -= 1;
	if (keys[SDL_SCANCODE_D])self->position.x += 1;
	if (keys[SDL_SCANCODE_S])self->position.y += 1;

}




