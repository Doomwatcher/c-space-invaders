#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "entity.h"
#include "inputs.h"

void inputs_handler(SDL_Event * event, t_inputs * inputs)
{
  while(SDL_PollEvent(event))  
    {
      if (SDL_QUIT == event->type)  
        inputs->quit =  true;
      else if (SDL_KEYDOWN == event->type) 
	{
	  if (event->key.keysym.sym == SDLK_SPACE) 
	    inputs->is_space_down = true;
	  if (event->key.keysym.sym == SDLK_ESCAPE) 
	    inputs->quit = true;
	  else if (event->key.keysym.sym == SDLK_LEFT) 
	    inputs->is_left_down = true;
	  else if (event->key.keysym.sym == SDLK_RIGHT) 
	    inputs->is_right_down = true;
	  else if (event->key.keysym.sym == SDLK_p) 
	    {
	      if (inputs->pause == true)
		inputs->pause = false;
	      else
		inputs->pause = true;
	    }
	  else if (event->key.keysym.sym == SDLK_r) 
	    {
	      inputs->restart = true;
	    }
	}
      else if (SDL_KEYUP == event->type)
	{
	  if (event->key.keysym.sym == SDLK_SPACE) 
	    inputs->is_space_down = false;
	  if (event->key.keysym.sym == SDLK_LEFT)
	    inputs->is_left_down = false;
	  else if (event->key.keysym.sym == SDLK_RIGHT) 
	    inputs->is_right_down = false;
	}
    }
}

void inputs_refresh(t_inputs * inputs, t_player * player)
{
  if (inputs->is_left_down && player->rect->x > 350)
    inputs->direction = -5;
  else if (inputs->is_right_down && player->rect->x < 650)
    inputs->direction = 5;
  else
    inputs->direction = 0;

  if (inputs->is_space_down)
    inputs->shoot = true;  
  else 
    inputs->shoot = false;
}
