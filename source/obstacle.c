#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "entity.h"
#include "gameloop.h"

t_obstacle_list * obstacle_list_create(void)
{
  t_obstacle_list * obstacle_list = (t_obstacle_list *)malloc(sizeof(t_obstacle_list));

  obstacle_list->size = 0;
  obstacle_list->head = NULL;
  obstacle_list->tail = NULL;

  return obstacle_list;
}

void create_obstacle(t_obstacle_list * obstacle_list, unsigned int x, unsigned int y, t_renderer * renderer)
{
  unsigned int y_count = 0;
  unsigned int x_count = 0;

  for (unsigned int i = 0 ; i < 25 ; i++)
    { 
      t_obstacle * obstacle = (t_obstacle *)malloc(sizeof(t_obstacle));
      SDL_Rect * rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));

      if (i%5 == 0)
	{
	  y_count++;
	}
     
      if (x_count >= 50)
	{
	  x_count = 0;
	}

      rect->x = x + x_count;
      rect->y = y + y_count*10;
      rect->w = 10; 
      rect->h = 10;

      obstacle->texture = SDL_CreateTextureFromSurface(renderer->renderer, SDL_CreateRGBSurface(0, rect->w, rect->h, 32, 0, 0, 0, 0));

      obstacle->rect = rect;

      obstacle->destroy_it = false;

      obstacle_add_to_list(obstacle,obstacle_list);
      
      x_count += 10;
    }
}

void obstacle_add_to_list(t_obstacle * obstacle, t_obstacle_list * obstacle_list)
{
  if (obstacle_list->head == NULL)
    {
      obstacle_list->size++;
      obstacle_list->head = obstacle;
      obstacle->next = NULL;
    }
  else
    {   
      obstacle_list->size++;
      obstacle->next = NULL;
      find_obstacle(obstacle_list->size-1,obstacle_list)->next = obstacle;
    }
  obstacle_list->tail = find_obstacle(obstacle_list->size,obstacle_list);
}

t_obstacle * find_obstacle(unsigned int num, t_obstacle_list * obstacle_list)
{ 
  t_obstacle * finded_obstacle;

  if (obstacle_list->size == 0)
    return NULL;

  if (num > obstacle_list->size)
    return 0;

  if (num == 1)
    return obstacle_list->head;

  finded_obstacle = obstacle_list->head;

  for (unsigned int i = 1 ; i < num ; i++)
    {
      finded_obstacle = finded_obstacle->next;  
    }

  return finded_obstacle;
}

void render_obstacle(t_renderer * renderer, t_obstacle_list * obstacle_list)
{
  t_obstacle * obstacle;

  for (unsigned int i = 1 ; i <= obstacle_list->size ; i++)
    {
      obstacle = find_obstacle(i,obstacle_list);
      SDL_RenderCopy(renderer->renderer, obstacle->texture, NULL, obstacle->rect);
    }
}

void kill_obstacle(t_obstacle * obstacle, t_obstacle_list * obstacle_list, t_particle_list * particle_list, t_renderer * renderer)
{
  if (obstacle_list->size ==  1)
    {
      obstacle_list->head = NULL;
      obstacle_list->tail = NULL;
    }
  else if (obstacle == obstacle_list->head)
    { 
      obstacle_list->head = obstacle->next;
    }
  else if (obstacle == obstacle_list->tail)
    {
      obstacle_list->tail = find_obstacle(obstacle_list->size-1,obstacle_list);
      find_obstacle(obstacle_list->size-1,obstacle_list)->next = NULL; 
    }
  else
    {      
      for (unsigned int i = 1 ; i <= obstacle_list->size ; i++)
	{
	  if (find_obstacle(i,obstacle_list) == obstacle)
	    {
	      find_obstacle(i-1,obstacle_list)->next = obstacle->next;
	      break;
	    }
	}
    }
  create_particle(renderer,particle_list,obstacle->rect->x,obstacle->rect->y);
  obstacle_list->size--;
  free_obstacle(obstacle);
}

void free_obstacle(t_obstacle * obstacle)
{
  SDL_DestroyTexture(obstacle->texture);
  free(obstacle->rect);
  free(obstacle);
}
