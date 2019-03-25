#ifndef bug_h
#define bug_h
#include <SDL.h>
#include "entity.h"
#include "gf2d_vector.h"
#include "gf2d_sprite.h"
#include "gf2d_text.h"
#include "simple_logger.h"
#include "player.h"

/***
@brief create player in a place
@param Vector2d arguement position
@return pointer to player object
***/
Entity *bug_new(Vector2D position);


/***
@brief get pointer to player
@param nothing
@return pointer to player
***/
Entity *bug_get();


/***
@brief give player a position
@param position for the new player
@return
***/
void bug_set_position(Vector2D position);

void bug_spawn(Vector2D position);






#endif
