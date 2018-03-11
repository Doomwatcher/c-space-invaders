#ifndef __GAMELOOP_H_INCLUDED__
#define __GAMELOOP_H_INCLUDED__

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "SDL.h"
#include "renderer.h"
#include "entity.h"
#include "inputs.h"

typedef struct s_game_data t_game_data;
typedef struct s_textures t_textures;

struct s_game_data
{
  bool pause;
  bool win;
  bool loose;
  int invader_direction;
  int elapsed_time;
  unsigned int game_level;
  unsigned int score;
  t_renderer * renderer;
  t_player * player;
  t_invader_list * invader_list;
  t_projectile_list * projectile_list;
  t_obstacle_list * obstacle_list;
  t_particle_list * particle_list;
  t_inputs * inputs;
  t_textures * textures;
  unsigned int timer_player_shoot;
  unsigned int timer_invader_shoot;
  unsigned int timer_invader_movement;
};

struct s_textures
{
  SDL_Texture * player_texture;
  SDL_Texture * player_texture2;
  SDL_Texture * invader1_texture;
  SDL_Texture * invader1_texture2;
  SDL_Texture * invader2_texture;
  SDL_Texture * invader2_texture2;
  SDL_Texture * invader3_texture;
  SDL_Texture * invader3_texture2;
  SDL_Texture * projectile_player_texture;
  SDL_Texture * projectile_invader_texture;
  SDL_Texture * projectile_invader_texture2;
};

bool init(t_game_data * game_data);
void loader(t_game_data * game_data);
void creator(t_game_data * game_data);
void gameloop(t_game_data * game_data);
void restart(t_game_data * game_data);

bool load_texture(char const * path, t_renderer * renderer, SDL_Texture ** texture);
void destroy_texture(SDL_Texture * texture);

void refresh_entities_positions(t_game_data * game_data);
void render_entities(t_game_data * game_data);
void open_fire_for_elligible_entities(t_game_data * game_data);
void check_collisions_and_leakings(t_game_data * game_data);

#endif /*__GAMELOOP_H_INCLUDED__*/
