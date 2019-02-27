#include <stdlib.h>
#include "player.h"
#include "simple_logger.h"
#include "gf2d_sprite.h"
#include "gf2d_vector.h"



static Entity *player = NULL;


void player_draw(Entity *self);
void player_think(Entity *self);
void player_update(Entity *self);
void player_touch(Entity *self, Entity *other);
void player_damage(Entity *self, int amount, Entity *source);
void player_die(Entity *self);


typedef struct
{
	int speed;
	int jumpHeight;

}PlayerData;

/*
static PlayerData playerData {
	3,50,3,
	0,100,
	0,100,
	0,100,
	0,0}*/

Entity *player_get()
{
	return player;
}

void player_set_position(Vector2D position)
{
	if (!player)
	{
		slog("no player loaded");
		return;
	}
	vector2d_copy(player->position, position);
	//vector2d_copy(player->body.position, position);

}
void player_spawn(Vector2D position)
{
	if (player = NULL)
	{
		vector2d_copy(player->position, position);
		//level_add_entity(player);
		return;
	}
	player_new(position);
}

Entity *player_new(Vector2D position)
{
	//Entity *self;
	player = ent_new();
	if (!player)
	{
		slog("failed to allocate new player memory");
		return NULL;
	}
	else
	{
		player->position = vector2d(200, 310);
		player->scale = vector2d(0.2, 20);
		player->sprite = gf2d_sprite_load_all("images/space_bug.png", 128, 128, 16);
		player->frame = 0;
		player->frame_limit = 16;
		player->update = player_update;
		slog("player made");
	}
	//vector2d_copy(player->position, position);
	//player->sprite = gf2d_sprite_load_all("images/space_bug.png", 128, 128, 16);
		

	//gf2d_line_cpy(player->sprite, "player");

}
void player_update(Entity *self)
{
	Uint8 *keys;
	keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W])self->position.y += 1;
	if (keys[SDL_SCANCODE_D])self->position.x += 1;
	if (keys[SDL_SCANCODE_A])self->position.x -= 1;
}