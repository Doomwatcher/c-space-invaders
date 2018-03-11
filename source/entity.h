#ifndef __ENTITY_H_INCLUDED__
#define __ENTITY_H_INCLUDED__

#include "SDL.h"
#include "renderer.h"

typedef struct s_invader_list t_invader_list;
typedef struct s_projectile_list t_projectile_list;
typedef struct s_obstacle_list t_obstacle_list;
typedef struct s_particle_list t_particle_list;
typedef struct s_player t_player;
typedef struct s_invader t_invader;
typedef struct s_projectile t_projectile;
typedef struct s_obstacle t_obstacle;
typedef struct s_particle t_particle;

struct s_invader_list
{
  unsigned int size;
  t_invader * head; 
  t_invader * tail; 
};

struct s_projectile_list
{
  unsigned int size;
  t_projectile * head; 
  t_projectile * tail; 
};

struct s_obstacle_list
{
  unsigned int size;
  t_obstacle * head; 
  t_obstacle * tail; 
};

struct s_particle_list
{
  unsigned int size;
  t_particle * head; 
  t_particle * tail; 
};

struct s_player
{
  bool is_dead;
  SDL_Texture * texture;
  SDL_Texture * texture2;
  SDL_Rect * rect;
  bool switch_texture;
  bool stop_particles;
};

struct s_invader
{
  SDL_Texture * texture;
  SDL_Texture * texture2;
  SDL_Rect * rect;
  t_invader * next;
  bool destroy_it;
  bool switch_texture;
};

struct s_projectile
{
  bool player_projectile;
  SDL_Texture * texture;
  SDL_Texture * texture2;
  SDL_Rect * rect;
  t_projectile * next;
  bool destroy_it;
  bool switch_texture;
};

struct s_obstacle
{
  SDL_Texture * texture;
  SDL_Rect * rect;
  t_obstacle * next;
  bool destroy_it;
};

struct s_particle
{
  SDL_Texture * texture;
  SDL_Rect * rect;
  t_particle * next;
  int velocity;
  int lifetime;
  int time_to_live;
  float direction_x;
  float direction_y;
  int size;
  bool destroy_it;
};

void player_shoot(SDL_Texture * projectile_player_texture, t_projectile_list * projectile_list, unsigned int x, unsigned int y);
t_player * create_player(SDL_Texture * texture, SDL_Texture * texture2);
void render_player(t_renderer * renderer, t_player * player, bool * space);
void refresh_player_position(t_player * player, int direction);
void kill_player(t_player * player, t_particle_list * particle_list, t_renderer * renderer);

t_invader_list * invader_list_create(void);
void create_invader(unsigned int num, SDL_Texture * texture, SDL_Texture * texture2, t_invader_list * invader_list, unsigned int x, unsigned int y);
void invader_add_to_list(t_invader * invader, t_invader_list * invader_list);
t_invader * find_invader(unsigned int num, t_invader_list * invader_list);
void render_invader(t_renderer * renderer, t_invader_list * invader_list);
void refresh_invader_position(t_invader_list * invader_list, int * invader_direction);
void kill_invader(t_invader * invader, t_invader_list * invader_list, t_particle_list * particle_list, t_renderer * renderer);
void invader_go_down(t_invader_list * invader_list);
void invader_shoot(SDL_Texture * projectile_invader_texture, SDL_Texture * projectile_invader_texture2, t_projectile_list * projectile_list, t_invader_list * invader_list);
void change_invader_texture(t_invader_list * invader_list);
void free_invader(t_invader * invader);

t_projectile_list * projectile_list_create(void);
void create_projectile (SDL_Texture * texture, SDL_Texture * texture2, t_projectile_list * projectile_list, unsigned int x, unsigned int y, bool player_projectile);
void projectile_add_to_list(t_projectile * projectile, t_projectile_list * projectile_list);
t_projectile * find_projectile(unsigned int num, t_projectile_list * projectile_list);
void render_projectile(t_renderer * renderer, t_projectile_list * projectile_list);
void refresh_projectile_position(t_projectile_list * projectile_list);
void kill_projectile(t_projectile * projectile, t_projectile_list * projectile_list);
void change_projectile_texture(t_projectile * projectile);
void free_projectile(t_projectile * projectile);

t_obstacle_list * obstacle_list_create(void);
void create_obstacle(t_obstacle_list * obstacle_list, unsigned int x, unsigned int y, t_renderer * renderer);
void obstacle_add_to_list(t_obstacle * obstacle, t_obstacle_list * obstacle_list);
t_obstacle * find_obstacle(unsigned int num, t_obstacle_list * obstacle_list);
void render_obstacle(t_renderer * renderer, t_obstacle_list * obstacle_list);
void kill_obstacle(t_obstacle * obstacle, t_obstacle_list * obstacle_list, t_particle_list * particle_list, t_renderer * renderer);
void free_obstacle(t_obstacle * obstacle);

t_particle_list * particle_list_create(void);
void create_particle(t_renderer * renderer, t_particle_list * particle_list, unsigned int x, unsigned int y);
void particle_add_to_list(t_particle * particle, t_particle_list * particle_list);
t_particle * find_particle(unsigned int num, t_particle_list * particle_list);
void refresh_particle_position(t_particle_list * particle_list);
void render_particle(t_renderer * renderer, t_particle_list * particle_list);
void kill_particle(t_particle * particle, t_particle_list * particle_list);
void free_particle(t_particle * particle);
void particle_life_time(t_particle_list * particle_list);

#endif /*__ENTITY_H_INCLUDED__*/
