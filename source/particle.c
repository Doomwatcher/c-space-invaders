#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "entity.h"
#include "gameloop.h"

t_particle_list * particle_list_create(void)
{
  t_particle_list * particle_list = (t_particle_list *)malloc(sizeof(t_particle_list));

  particle_list->size = 0;
  particle_list->head = NULL;
  particle_list->tail = NULL;

  return particle_list;
}

void create_particle(t_renderer * renderer, t_particle_list * particle_list, unsigned int x, unsigned int y)
{
  unsigned int num;

  num = 10;//rand()%5 + 5;

  for (unsigned int i = 0 ; i < num ; i++)
    { 
      t_particle * particle = (t_particle *)malloc(sizeof(t_particle));
      SDL_Rect * rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));

      particle->size = rand()%2 + 2;
      particle->direction_x = rand()%10 - 6;
      particle->direction_y = rand()%10 - 6;
      particle->time_to_live = rand()%20 + 20;

      while (particle->direction_x == 0 && particle->direction_y == 0)
	{
	  particle->direction_x = rand()%10 - 6;
	  particle->direction_y = rand()%10 - 6;
	}

      particle->velocity = 2;
      particle->lifetime = 50;

      rect->x = x;
      rect->y = y;
      rect->w = particle->size; 
      rect->h = particle->size;

      particle->texture = SDL_CreateTextureFromSurface(renderer->renderer, SDL_CreateRGBSurface(0, rect->w, rect->h, 32, 0, 0, 0, 0));
      particle->rect = rect;

      particle->destroy_it = false;

      particle_add_to_list(particle,particle_list);     
    }
}

void particle_add_to_list(t_particle * particle, t_particle_list * particle_list)
{
  if (particle_list->head == NULL)
    {
      particle_list->size++;
      particle_list->head = particle;
      particle->next = NULL;
    }
  else
    {   
      particle_list->size++;
      particle->next = NULL;
      find_particle(particle_list->size-1,particle_list)->next = particle;
    }
  particle_list->tail = find_particle(particle_list->size,particle_list);
}

t_particle * find_particle(unsigned int num, t_particle_list * particle_list)
{ 
  t_particle * finded_particle;

  if (particle_list->size == 0)
    return NULL;

  if (num > particle_list->size)
    return 0;

  if (num == 1)
    return particle_list->head;

  finded_particle = particle_list->head;

  for (unsigned int i = 1 ; i < num ; i++)
    {
      finded_particle = finded_particle->next;  
    }

  return finded_particle;
}

void refresh_particle_position(t_particle_list * particle_list)
{
  t_particle * particle;

  for (unsigned int i = 1 ; i <= particle_list->size ; i++)
    {
      particle = find_particle(i,particle_list);
      particle->rect->x += particle->direction_x + particle->velocity;
      particle->rect->y += particle->direction_y + particle->velocity;
    }
}

void render_particle(t_renderer * renderer, t_particle_list * particle_list)
{
  t_particle * particle;

  for (unsigned int i = 1 ; i <= particle_list->size ; i++)
    {
      particle = find_particle(i,particle_list);
      SDL_RenderCopy(renderer->renderer, particle->texture, NULL, particle->rect);
    }
}

void kill_particle(t_particle * particle, t_particle_list * particle_list)
{
  if (particle_list->size ==  1)
    {
      particle_list->head = NULL;
      particle_list->tail = NULL;
    }
  else if (particle == particle_list->head)
    { 
      particle_list->head = particle->next;
    }
  else if (particle == particle_list->tail)
    {
      particle_list->tail = find_particle(particle_list->size-1,particle_list);
      find_particle(particle_list->size-1,particle_list)->next = NULL;
    }
  else
    {      
      for (unsigned int i = 1 ; i <= particle_list->size ; i++)
	{
	  if (find_particle(i,particle_list) == particle)
	    {
	      destroy_texture(find_particle(i,particle_list)->texture);
	      find_particle(i-1,particle_list)->next = particle->next;
	      break;
	    }
	}
    }
  particle_list->size--;
  free(particle);
}

void free_particle(t_particle * particle)
{
  SDL_DestroyTexture(particle->texture);
  free(particle->rect);
  free(particle);
}

void particle_life_time(t_particle_list * particle_list)
{
  t_particle * particle;

  for (unsigned int i = 1 ; i <= particle_list->size ; i++)
    {
      particle = find_particle(i,particle_list);
      if (particle->time_to_live >= particle->lifetime)
	particle->destroy_it = true;
      else
	particle->time_to_live++;
    }
}
