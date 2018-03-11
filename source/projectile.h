#ifndef __ENTITY_H_INCLUDED__
#define __ENTITY_H_INCLUDED__

#include "SDL.h"

typedef struct s_projectile_list t_projectile_list;
typedef struct s_projectile t_projectile;

struct s_projectile_list
{
  unsigned int size;
  t_projectile * head; 
  t_projectile * tail; 
};

struct s_projectile
{
  bool player_projectile;
  t_position position;
  SDL_Texture * texture;
  SDL_Texture * texture2;
  SDL_Rect * rect;
  t_projectile * next;
  bool destroy_it;
  bool switch_texture;
};

t_projectile_list * projectile_list_create(void);
void create_projectile (SDL_Texture * texture, SDL_Texture * texture2, t_projectile_list * projectile_list, unsigned int x, unsigned int y, bool player_projectile);
void projectile_add_to_list(t_projectile * projectile, t_projectile_list * projectile_list);
t_projectile * find_projectile(unsigned int num, t_projectile_list * projectile_list);
void render_projectile(t_renderer * renderer, t_projectile_list * projectile_list);
void refresh_projectile_position(t_projectile_list * projectile_list);
void kill_projectile(t_projectile * projectile, t_projectile_list * projectile_list);
void change_projectile_texture(t_projectile * projectile);

#endif /*__ENTITY_H_INCLUDED__*/
