#include <stdio.h>
#include <stdbool.h>
#include <io.h>
#include <time.h>
#include "SDL.h"
#include "gameloop.h"
#include "destroy.h"
#include "collision.h"

void destroy(t_game_data * game_data)
{
  empty_list(game_data);

  destroy_textures(game_data);

  free_list(game_data);

  SDL_Quit();

  free_player(game_data);
}

void empty_list(t_game_data * game_data)
{
  for (unsigned int i = 1 ; i <= game_data->projectile_list->size ; i++)
    {
      kill_projectile(find_projectile(i,game_data->projectile_list),game_data->projectile_list);
    }
  for (unsigned int i = 1 ; i <= game_data->invader_list->size ; i++)
    {
      kill_invader(find_invader(i,game_data->invader_list),game_data->invader_list,game_data->particle_list,game_data->renderer);
    }
  for (unsigned int i = 1 ; i <= game_data->obstacle_list->size ; i++)
    {
      kill_obstacle(find_obstacle(i,game_data->obstacle_list),game_data->obstacle_list,game_data->particle_list,game_data->renderer);
    }
  for (unsigned int i = 1 ; i <= game_data->particle_list->size ; i++)
    {
      kill_particle(find_particle(i,game_data->particle_list),game_data->particle_list);
    }

  destroy_flagged_entities(game_data);
}

void destroy_textures(t_game_data * game_data)
{
  SDL_DestroyTexture(game_data->textures->player_texture);
  SDL_DestroyTexture(game_data->textures->player_texture2);
  SDL_DestroyTexture(game_data->textures->invader1_texture);
  SDL_DestroyTexture(game_data->textures->invader1_texture2);
  SDL_DestroyTexture(game_data->textures->invader2_texture);
  SDL_DestroyTexture(game_data->textures->invader2_texture2);
  SDL_DestroyTexture(game_data->textures->invader3_texture);
  SDL_DestroyTexture(game_data->textures->invader3_texture2);
  SDL_DestroyTexture(game_data->textures->projectile_player_texture);
  SDL_DestroyTexture(game_data->textures->projectile_invader_texture);
  SDL_DestroyTexture(game_data->textures->projectile_invader_texture2);
}

void free_list(t_game_data * game_data)
{
  free(game_data->inputs);
  free(game_data->renderer);
  free(game_data->textures);
  free(game_data->invader_list);
  free(game_data->projectile_list);
  free(game_data->obstacle_list);
  free(game_data->particle_list);
}

void free_player(t_game_data * game_data)
{
  free(game_data->player->rect);
  free(game_data->player);
}
