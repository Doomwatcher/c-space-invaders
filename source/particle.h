#ifndef __ENTITY_H_INCLUDED__
#define __ENTITY_H_INCLUDED__

#include "SDL.h"

typedef struct s_particle_list t_particle_list;
typedef struct s_particle t_particle;

struct s_particle_list
{
  unsigned int size;
  t_particle * head; 
  t_particle * tail; 
};

struct s_particle
{
  t_position position;
  SDL_Texture * texture;
  SDL_Rect * rect;
  t_particle * next;
  int velocity;
  int lifetime;
  float direction_x;
  float direction_y;
  int size;
  bool destroy_it;
};

t_particle_list * particle_list_create(void);
void create_particle(t_renderer * renderer, t_particle_list * particle_list, unsigned int x, unsigned int y);
void particle_add_to_list(t_particle * particle, t_particle_list * particle_list);
t_particle * find_particle(unsigned int num, t_particle_list * particle_list);
void refresh_particle_position(t_particle_list * particle_list);
void render_particle(t_renderer * renderer, t_particle_list * particle_list);
void kill_particle(t_particle * particle, t_particle_list * particle_list);

#endif /*__ENTITY_H_INCLUDED__*/
