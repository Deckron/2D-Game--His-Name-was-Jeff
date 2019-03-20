#include "gf2d_collision.h"
#include "simple_logger.h"
#include "gf2d_draw.h"
#include <stdlib.h>

Collision *gf2d_collision_new()
{
	Collision *collision = NULL;
	collision = (Collision *)malloc(sizeof(Collision));
	if (!collision)
	{
		slog("failed to allocate data for a collision object");
		return NULL;
	}
	memset(collision, 0, sizeof(Collision));
	return collision;
}

void gf2d_collision_free(Collision *collision)
{
	if (!collision)return;
	free(collision);
}

void gf2d_collision_list_free(List *list)
{
	int i, count;
	Collision *collision;
	if (!list)return;
	count = gf2d_list_get_count(list);
	for (i = 0; i < count; i++)
	{
		collision = (Collision*)gf2d_list_get_nth(list, i);
		if (!collision)continue;
		gf2d_collision_free(collision);
	}
	gf2d_list_delete(list);
}

Collision *gf2d_collision_space_static_shape_clip(Shape a, Shape *s)
{
	Collision *collision;
	Vector2D poc, normal;
	if (!gf2d_shape_overlap_poc(a, *s, &poc, &normal))
	{
		return NULL;
	}
	collision = gf2d_collision_new();
	collision->collided = 1;
	collision->blocked = 1;
	vector2d_copy(collision->pointOfContact, poc);
	vector2d_copy(collision->normal, normal);
	collision->shape = s;
	collision->body = NULL;
	collision->bounds = 0;
	collision->timeStep = 0;
	return collision;
}


