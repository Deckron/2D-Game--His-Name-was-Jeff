#ifndef __GF2D_BODY_H__
#define __GF2D_BODY_H__
#include "gf2d_shape.h"
#include "gf2d_list.h"
#include "gf2d_text.h"

typedef struct Body_S
{
	char		name; //name used for debugging
	int			inactive;//internal use only
	float		gravity;//factor to which body adheres to gravity
	Uint8		worldclip;//if this body clips the world bounds and static shapes
	Uint32		cliplayer;//only bodies that share one or more layers will collide with eachother
	Uint32		touchlayer;//only bodies that share one or more layers will have their functions called
	Uint32		team;//bodies that share a team will NOT interact
	Vector2D	position;//position of center of mass
	Vector2D	velocity;//rateof change of position over time;
	Vector2D	newvelocity;//after collision, this is the new calculated velocity
	float		mass;//used to calculate inertia
	float		elasticity;//how much bounce this body has
	Shape		*shape;//which shape data will be used to collide for this body
	void		*data;//custom data pointer
	int(*touch)(struct Body_S *self, List *collision);//function to call when two bodies collide
}Body;

/***
@brief check if the two bodies are overlapping anywhere
@param a one body
@param b the other body
@return 0 one error or no collision, 1 otherwise
***/
Uint8 gf2d_body_body_collide(Body *a, Body *b);

/***
@brief draw a body to the screen. shape will be magenta, center point will be a green pixel
@param the body to draw, a no-op if this is null
@param offset to adjust for camera or other position change realtive to the body center
***/
void gf2d_body_draw(Body *body, Vector2D offset);

/***
@brief initializes a body to zero
@warning do no use this on a body in use
***/
void gf2d_body_clear(Body *body);

/***
@brief set all parameters for a body
@param the body to se the parameters for
@param name of the body
@param worldclip if this body should clip the world itself
@param cliplayer the layer mask for what bodies to call the touch functions for
@param team the team this body is on
@param position the position in space for the body to be added at
@param velocity the velo at which the body is moving
@param mass the mass of the body(to calculate momentum)
@param gravity the factor to which this body adheres to gravity
@param elasticity how much bounce this body has
@param shape a pointer to the shape data to be used
@param data any custom data you want associated with current body
@param bodyTouch the callback to invoke when this body touches another body
@param worldTouch the callback to invoke when this body touches the world
***/
void gf2d_body_set(
	Body	*body,
	char	name,
	Uint8	worldClip,
	Uint32	cliplayer,
	Uint32	touchlayer,
	Uint32	team,
	Vector2D position,
	Vector2D velocity,
	float	mass,
	float	gravity,
	float	elasticity,
	Shape	*shape,
	void	*data,
	int		(*touch)(struct Body_S *self, List *collision)
);

/***
@brief apply a force to a body taking into account momentum
@param body to move
@oaram durection a unit vector for direction
@param the amount of fouce to apply
***/
void gf2d_body_push(Body *body, Vector2D direction, float force);

/***
@brief get the shape, adjusted for position for the provided body
@param a the body to get the shape for 
@return an empty{0} shape on error, or the body shape information otherwise
***/
Shape gf2d_body_to_shape(Body *a);

#endif
