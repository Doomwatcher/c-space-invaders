#ifndef __ENTITY_H_INCLUDED__
#define __ENTITY_H_INCLUDED__

#include "SDL.h"

typedef struct s_player t_player;

struct s_player
{
  bool is_dead;
  t_position position;
  SDL_Texture * texture;
  SDL_Texture * texture2;
  SDL_Rect * rect;
  bool switch_texture;
};

void player_shoot(SDL_Texture * projectile_player_texture, t_projectile_list * projectile_list, unsigned int x, unsigned int y);
t_player * create_player(SDL_Texture * texture, SDL_Texture * texture2);
void render_player(t_renderer * renderer, t_player * player);
void refresh_player_position(t_player * player, int direction);
void kill_player(t_player * player);

#endif /*__ENTITY_H_INCLUDED__*/
