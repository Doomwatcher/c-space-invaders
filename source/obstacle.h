#ifndef __ENTITY_H_INCLUDED__
#define __ENTITY_H_INCLUDED__

#include "SDL.h"

typedef struct s_obstacle_list t_obstacle_list;
typedef struct s_obstacle t_obstacle;

struct s_obstacle_list
{
  unsigned int size;
  t_obstacle * head; 
  t_obstacle * tail; 
};

struct s_obstacle
{
  t_position position;
  SDL_Texture * texture;
  SDL_Rect * rect;
  t_obstacle * next;
  bool destroy_it;
};

t_obstacle_list * obstacle_list_create(void);
void create_obstacle(t_obstacle_list * obstacle_list, unsigned int x, unsigned int y, t_renderer * renderer);
void obstacle_add_to_list(t_obstacle * obstacle, t_obstacle_list * obstacle_list);
t_obstacle * find_obstacle(unsigned int num, t_obstacle_list * obstacle_list);
void render_obstacle(t_renderer * renderer, t_obstacle_list * obstacle_list);
void kill_obstacle(t_obstacle * obstacle, t_obstacle_list * obstacle_list);

#endif /*__ENTITY_H_INCLUDED__*/
