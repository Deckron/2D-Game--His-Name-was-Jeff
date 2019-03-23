#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include <SDL.h>
#include "gf2d_types.h"
#include "gf2d_vector.h"
#include "gf2d_sprite.h"
#include "gf2d_shape.h"

typedef struct
{
	Uint32 width, height;
	Vector2D start, end;
	Sprite *tileset;
	char *map;
	Shape hitbox;
	Vector2D position;
	Vector2D scale;
}TileMap;

TileMap *tile_new(Vector2D position, Vector2D scale);
TileMap *tilemap_load(char *filename);
void tilemap_free(TileMap *tilemap);
void tilemap_draw(TileMap *tilemap, Vector2D position);
void tilemap_draw_path(Vector2D *path, int length, TileMap *tilemap, Vector2D position);

#endif