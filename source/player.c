#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "SDL_image.h"
#include "entity.h"
#include "gameloop.h"

t_player *  create_player(SDL_Texture * texture, SDL_Texture * texture2)
{
  t_player * player = (t_player *)malloc(sizeof(t_player));
  SDL_Rect * rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));

  rect->x = 500;
  rect->y = 700;
  rect->w = 20;
  rect->h = 20;

  player->is_dead = false;

  player->texture = texture;
  player->texture2 = texture2;
  player->rect = rect;

  return player;
}

void refresh_player_position(t_player * player, int direction)
{
  if(player->is_dead)
    return;

  player->rect->x = player->rect->x + direction;
}

void render_player(t_renderer * renderer, t_player * player, bool * shoot)
{
  if (player->is_dead)
    return;

  if (*shoot)
    SDL_RenderCopy(renderer->renderer, player->texture2, NULL, player->rect);
  else
    SDL_RenderCopy(renderer->renderer, player->texture, NULL, player->rect);
}

void kill_player(t_player * player, t_particle_list * particle_list, t_renderer * renderer)
{
  
  if (!player->stop_particles)
    {
      for (unsigned int i = 0 ; i <= 2 ; i++)
	{
	  create_particle(renderer,particle_list,player->rect->x,player->rect->y);
	}
      player->stop_particles = true;
    }

  player->rect->x = 0;
  player->rect->y = 0;
  player->rect->w = 0; 
  player->rect->h = 0;
}
