#include <stdio.h>
#include <stdbool.h>
#include <io.h>
#include "SDL.h"
#include "gameloop.h"
#include "collision.h"
#include "destroy.h"

void gameloop(t_game_data * game_data)
{
  unsigned int time = SDL_GetTicks();

  SDL_Rect rect;

  rect.x = 0;
  rect.y = 0;
  rect.w = 1000;
  rect.h = 1000;

  while (!game_data->inputs->quit && !game_data->inputs->restart)
    {  
      unsigned int new_time = SDL_GetTicks();
      game_data->elapsed_time = new_time - time;
      time = new_time;
 
      SDL_Event event;

      while (game_data->inputs->pause)
	{
	  inputs_handler(&event,game_data->inputs); 
	  if (game_data->inputs->quit)
	    game_data->inputs->pause = false;
	}

      inputs_handler(&event,game_data->inputs);
      inputs_refresh(game_data->inputs,game_data->player);

      refresh_entities_positions(game_data);
      render_entities(game_data);
      
      open_fire_for_elligible_entities(game_data);

      check_collisions_and_leakings(game_data) ;

      SDL_RenderFillRect(game_data->renderer->renderer, &rect);
      SDL_RenderPresent(game_data->renderer->renderer);
    }

  if (game_data->inputs->restart)
    restart(game_data);  
}

void restart(t_game_data * game_data)
{
  destroy(game_data);
  init(game_data);
  loader(game_data);
  creator(game_data);
  gameloop(game_data);
}

void refresh_entities_positions(t_game_data * game_data)
{
  refresh_player_position(game_data->player,game_data->inputs->direction);
  refresh_projectile_position(game_data->projectile_list);
  refresh_particle_position(game_data->particle_list);

  if (game_data->timer_invader_movement >= game_data->invader_list->size)
    {
      refresh_invader_position(game_data->invader_list,&game_data->invader_direction);
      game_data->timer_invader_movement = 0;
    }
  else
    game_data->timer_invader_movement++;
}

void render_entities(t_game_data * game_data)
{
  render_player(game_data->renderer,game_data->player,&game_data->inputs->shoot);
  render_invader(game_data->renderer,game_data->invader_list);
  render_projectile(game_data->renderer,game_data->projectile_list);
  render_particle(game_data->renderer,game_data->particle_list);
  render_obstacle(game_data->renderer,game_data->obstacle_list);
}

void open_fire_for_elligible_entities(t_game_data * game_data)
{
  if (game_data->inputs->shoot && game_data->timer_player_shoot >= 5)
    {
      player_shoot(game_data->textures->projectile_player_texture,game_data->projectile_list,game_data->player->rect->x,game_data->player->rect->y);
      game_data->timer_player_shoot = 0;
    }
  else
    game_data->timer_player_shoot++;

  if (game_data->timer_invader_shoot >= 10)
    {
      invader_shoot(game_data->textures->projectile_invader_texture,game_data->textures->projectile_invader_texture2,game_data->projectile_list,game_data->invader_list);
      game_data->timer_invader_shoot = 0;
    }
  else
    game_data->timer_invader_shoot++;
}

void check_collisions_and_leakings(t_game_data * game_data)
{
  check_collisions(game_data);
  particle_life_time(game_data->particle_list);
  remove_leaking_entities(game_data->projectile_list,game_data->particle_list);
  destroy_flagged_entities(game_data);
}
