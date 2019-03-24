#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "entity.h"
#include "tilemap.h"
#include "gf2d_vector.h"
#include "player.h"
#include "gf2d_collision.h"
#include "floater.h"
//#include "gf2d_space.h"





int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *sprite;
	Entity *player = NULL;
	Entity *floater = NULL;
	slog("declared");
    
    int mx,my;
    float mf = 0;
    Sprite *mouse;
	Entity *ent;
	TileMap *map;
    Vector4D mouseColor = {255,100,255,200};
	Space *space= NULL;
	

	//space = gf2d_space_new_full(10, gf2d_Rectangle(0, 0, 1200, 720), 10.0f, vector2d(0,0), 0.0f, 0.1f);
	static Vector2D path[2];
    
    /*program initializtion*/
    init_logger("gf2d.log");
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(1024);
	entity_manager_init(1024);
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
    sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
	player = player_new(vector2d(0, 0), player);
	floater = floater_new(vector2d(300, 0), floater);
	map = tilemap_load("levels/tilemap.map");
	vector2d_copy(path[0], map->start);
	vector2d_copy(path[1], map->end);
	space = gf2d_space_new_full(10, gf2d_Rectangle(0, 0, 1200, 720), 10.0f, vector2d(0, 4), 1.0f, 0.3f);
	gf2d_space_add_static_shape(space, gf2d_shape_Rectangle(0, 100, 550, 30));
	//gf2d_space_add_body(space, &player->body);
	//gf2d_space_add_body(space, &floater->body);
	slog("init");
	//player = gf2d_sprite_load_all("images/space_bug.png", 128, 128, 16);
	//those two lines go into both floater and player
	//create entity(player)
	/*
	player = player_new();
	if (!player)
	{
		slog("could not draw player");
		return;
	}
	else
	{
		player = player_new(vector2d(1000, 0), player);
		slog("player drawn");
	}
	
	*/

    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;
		slog("beginning loop");
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            gf2d_sprite_draw_image(sprite,vector2d(0,0));
			draw_ent(player);
			draw_ent(floater);
			//update_ent(player);
			player_update(player, space);
			floater_update(floater, space, player);
			//tilemap_draw(map, vector2d(86, 24));
			//tilemap_draw_path(path, 2, map, vector2d(86, 24));

			//slog("check here");
			gf2d_space_draw(space, vector2d(0, 0));
			
		
			

			
			
            
            //UI elements last
            gf2d_sprite_draw(
                mouse,
                vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseColor,
                (int)mf);
        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
