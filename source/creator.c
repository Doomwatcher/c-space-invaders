#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "entity.h"
#include "gameloop.h"

void creator(t_game_data * game_data)
{
  for (unsigned int i = 0 ; i < 2 ; i++)
    {
      create_invader(11,game_data->textures->invader2_texture,game_data->textures->invader2_texture2,game_data->invader_list,350,100+i*30);
    }     

  for (unsigned int i = 0 ; i < 2 ; i++)
    {
      create_invader(11,game_data->textures->invader1_texture,game_data->textures->invader1_texture2,game_data->invader_list,350,200+i*30);
    }     

  for (unsigned int i = 0 ; i < 2 ; i++)
    {
      create_invader(11,game_data->textures->invader3_texture,game_data->textures->invader3_texture2,game_data->invader_list,350,300+i*30);
    }     

  for (unsigned int i = 0 ; i < 3 ; i++)
    {
      create_obstacle(game_data->obstacle_list,385+i*100,600,game_data->renderer);
    }

  game_data->player = create_player(game_data->textures->player_texture,game_data->textures->player_texture2);
}
