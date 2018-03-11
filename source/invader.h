#ifndef __ENTITY_H_INCLUDED__
#define __ENTITY_H_INCLUDED__

#include "SDL.h"

typedef struct s_invader_list t_invader_list;
typedef struct s_invader t_invader;

struct s_invader_list
{
  unsigned int size;
  t_invader * head; 
  t_invader * tail; 
};

struct s_invader
{
  t_position position;
  SDL_Texture * texture;
  SDL_Texture * texture2;
  SDL_Rect * rect;
  t_invader * next;
  bool destroy_it;
  bool switch_texture;
};

t_invader_list * invader_list_create(void);
void create_invader(unsigned int num, SDL_Texture * texture, SDL_Texture * texture2, t_invader_list * invader_list, unsigned int x, unsigned int y);
void invader_add_to_list(t_invader * invader, t_invader_list * invader_list);
t_invader * find_invader(unsigned int num, t_invader_list * invader_list);
void render_invader(t_renderer * renderer, t_invader_list * invader_list);
void refresh_invader_position(t_invader_list * invader_list, int * invader_direction);
void kill_invader(t_invader * invader, t_invader_list * invader_list);
void invader_go_down(t_invader_list * invader_list);
void invader_shoot(SDL_Texture * projectile_invader_texture, SDL_Texture * projectile_invader_texture2, t_projectile_list * projectile_list, t_invader_list * invader_list);
void change_invader_texture(t_invader_list * invader_list);

#endif /*__ENTITY_H_INCLUDED__*/
