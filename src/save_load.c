#include <stdio.h>
#include "save_load.h"

void save_file(Save *save, Entity *player)
{
	save->player_position = player->position;
	save->player = *player;
	FILE *file_save = fopen("save/saveFile.his_name_was_jeff", "wb");

	fwrite(&(*save), sizeof(struct Save), 1, file_save);

	fclose(file_save);
	
}
void load_file(Save*save, Entity *player)
{
	
	FILE *file_save = fopen("save/saveFile.his_name_was_jeff", "rb");
	fread(&(*save), sizeof(struct Save), 1, file_save); //Read to contents of save file once into the address of out save struct.
	fclose(file_save);
	vector2d_copy(player->position, save->player_position);
	player->position= save->player_position;
	//player->player = save->player;
}

void read_file(Save *save, Entity *player)
{

	FILE *file_save = fopen("save/saveFile.his_name_was_jeff", "rb");
	fread(&(*save), sizeof(struct Save), 1, file_save); //Read to contents of save file once into the address of out save struct.
	fclose(file_save);
}