#ifndef player_h
#define player_h
#include <SDL.h>
#include "entity.h"
#include "gf2d_vector.h"
#include "gf2d_sprite.h"
#include "gf2d_text.h"
#include "simple_logger.h"

/***
@brief create player in a place
@param Vector2d arguement position
@return pointer to player object
***/
Entity *player_new(Vector2D position);


/***
@brief get pointer to player
@param nothing
@return pointer to player
***/
Entity *player_get();


/***
@brief give player a position
@param position for the new player
@return
***/
void player_set_position(Vector2D position);

void player_spawn(Vector2D position);




#endif