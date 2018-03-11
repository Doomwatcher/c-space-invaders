#ifndef __INPUTS_H_INCLUDED__
#define __INPUTS_H_INCLUDED__

#include "SDL.h"
#include "SDL_image.h"
#include "player.h"

typedef struct s_inputs t_inputs;

struct s_inputs
{
  bool restart;
  bool pause;
  bool shoot;
  bool quit;
  bool is_space_down;
  bool is_left_down;
  bool is_right_down;
  int direction;
};

void inputs_handler(SDL_Event * event, t_inputs * inputs);
void inputs_refresh(t_inputs * inputs, t_player * player);

#endif /*__INPUTS_H_INCLUDED__*/
