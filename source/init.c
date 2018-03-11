#include <stdio.h>
#include <stdbool.h>
#include <io.h>
#include <time.h>
#include "SDL.h"
#include "position.h"
#include "color.h"
#include "entity.h"
#include "gameloop.h"

bool init(t_game_data * game_data)
{
  t_projectile_list * projectile_list;
  t_invader_list * invader_list;
  t_obstacle_list * obstacle_list;
  t_particle_list * particle_list;

  t_color window_background_color;

  t_inputs * inputs = (t_inputs *)malloc(sizeof(t_inputs));
  t_position window_position;
  t_renderer * renderer = (t_renderer *)malloc(sizeof(t_renderer));
  t_textures * textures = (t_textures *)malloc(sizeof(t_textures));
  t_player player;

  char * game_title = "Stupid Invader !";

  invader_list      = invader_list_create();
  projectile_list   = projectile_list_create();
  obstacle_list     = obstacle_list_create();
  particle_list     = particle_list_create();

  inputs->restart        = false;
  inputs->pause          = false;
  inputs->shoot          = false;
  inputs->quit           = false;
  inputs->is_left_down   = false;
  inputs->is_right_down  = false;
  inputs->is_space_down  = false;

  window_background_color.red    = 255;
  window_background_color.blue   = 255;
  window_background_color.green  = 255;
  window_background_color.alpha  = 255;

  window_position.x   = 0;
  window_position.y   = 0;
  window_position.w   = 1000;
  window_position.h   = 800;

  renderer->window   = NULL;
  renderer->renderer = NULL;

  game_data->pause                   = false;
  game_data->win                     = false;
  game_data->loose                   = false;
  game_data->invader_direction       = 10;
  game_data->game_level              = 0;
  game_data->score                   = 0;
  game_data->renderer                = renderer;
  game_data->player                  = &player;
  game_data->invader_list            = invader_list;
  game_data->projectile_list         = projectile_list;
  game_data->obstacle_list           = obstacle_list;
  game_data->particle_list           = particle_list;
  game_data->inputs                  = inputs;
  game_data->textures                = textures;
  game_data->timer_player_shoot      = 50;
  game_data->timer_invader_shoot     = 50;
  game_data->timer_invader_movement  = 0;

  create_window_and_renderer(renderer, game_title, &window_position, &window_background_color);

  return true;
}
