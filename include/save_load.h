#ifndef _save_h_
#define _save_h_

#include "player.h"


typedef struct Save {
	Vector2D player_position;
	Entity player;
}Save;

void save_file(Save *save, Entity *player);
void load_file(Save *save, Entity *player);
void read_file(Save *save, Entity *player);

#endif