#ifndef __DESTROY_H_INCLUDED__
#define __DESTROY_H_INCLUDED__

#include "SDL.h"
#include "gameloop.h"

void destroy(t_game_data * game_data);
void empty_list(t_game_data * game_data);
void destroy_textures(t_game_data * game_data);
void free_list(t_game_data * game_data);
void free_player(t_game_data * game_data);

#endif /*__DESTROY_H_INCLUDED__*/
