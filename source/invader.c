#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "entity.h"
#include "gameloop.h"

t_invader_list * invader_list_create(void)
{
  t_invader_list * invader_list = (t_invader_list *)malloc(sizeof(t_invader_list));

  invader_list->size = 0;
  invader_list->head = NULL;
  invader_list->tail = NULL;

  return invader_list;
}

void create_invader(unsigned int num, SDL_Texture * texture, SDL_Texture * texture2, t_invader_list * invader_list, unsigned int x, unsigned int y)
{
  for (unsigned int i = 0 ; i < num ; i++)
    { 
      t_invader * invader = (t_invader *)malloc(sizeof(t_invader));
      SDL_Rect * rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));

      rect->x = x + i*25;
      rect->y = y;
      rect->w = 20; 
      rect->h = 20;

      invader->texture = texture;
      invader->texture2 = texture2;
      invader->rect = rect;

      invader->destroy_it = false;
      invader->switch_texture = false;

      invader_add_to_list(invader,invader_list);     
    }
}

void invader_add_to_list(t_invader * invader, t_invader_list * invader_list)
{
  if (invader_list->head == NULL)
    {      
      invader_list->size++;
      invader_list->head = invader;
      invader->next = NULL;
    }
  else
    {   
      invader_list->size++;
      invader->next = NULL;
      find_invader(invader_list->size-1,invader_list)->next = invader;
    }
  invader_list->tail = find_invader(invader_list->size,invader_list);
}

t_invader * find_invader(unsigned int num, t_invader_list * invader_list)
{ 
  t_invader * finded_invader;

  if (invader_list->size == 0)
    return NULL;

  if (num > invader_list->size)
    return 0;

  if (num == 1)
    return invader_list->head;

  finded_invader = invader_list->head;

  for (unsigned int i = 1 ; i < num ; i++)
    {
      finded_invader = finded_invader->next;  
    }

  return finded_invader;
}

void refresh_invader_position(t_invader_list * invader_list, int * invader_direction)
{
  t_invader * invader;

  for (unsigned int i = 1 ; i <= invader_list->size ; i++)
    {
      find_invader(i,invader_list)->rect->x += *invader_direction;	  
    }

  for (unsigned int i = 1 ; i <= invader_list->size ; i++)
    {
      invader = find_invader(i,invader_list);
      if (invader->rect->x >= 650)
	{
	  *invader_direction = -10;  
	  invader_go_down(invader_list);
	  break;
	}
      else if (invader->rect->x <= 350)
	{
	  *invader_direction = 10;
	  invader_go_down(invader_list);
	  break;
	}
    } 
  change_invader_texture(invader_list);
}

void change_invader_texture(t_invader_list * invader_list)
{
  t_invader * invader;

  for (unsigned int i = 1 ; i <= invader_list->size ; i++)
    {
      invader = find_invader(i,invader_list);
      if (!invader->switch_texture)
	  invader->switch_texture = true;
      else if (invader->switch_texture)
	  invader->switch_texture = false;
    }
}

void invader_go_down(t_invader_list * invader_list)
{
   for (unsigned int i = 1 ; i <= invader_list->size ; i++)
	{
	  find_invader(i,invader_list)->rect->y += 10;	  
	}
}

void render_invader(t_renderer * renderer, t_invader_list * invader_list)
{
  t_invader * invader;

  for (unsigned int i = 1 ; i <= invader_list->size ; i++)
    {
      invader = find_invader(i,invader_list);
      if (!invader->switch_texture)
	  SDL_RenderCopy(renderer->renderer, invader->texture, NULL, invader->rect);
      else if (invader->switch_texture)
	  SDL_RenderCopy(renderer->renderer, invader->texture2, NULL, invader->rect);
    }
}

void kill_invader(t_invader * invader, t_invader_list * invader_list, t_particle_list * particle_list, t_renderer * renderer)
{
  if (invader_list->size ==  1)
    {
      invader_list->head = NULL;
      invader_list->tail = NULL;
    }
  else if (invader == invader_list->head)
    { 
      invader_list->head = invader->next;
    }
  else if (invader == invader_list->tail)
    {
      invader_list->tail = find_invader(invader_list->size-1,invader_list);
      find_invader(invader_list->size-1,invader_list)->next = NULL;
    }
  else
    {      
      for (unsigned int i = 1 ; i <= invader_list->size ; i++)
	{
	  if (find_invader(i,invader_list) == invader)
	    {
	      find_invader(i-1,invader_list)->next = invader->next;
	      break;
	    }
	}
    }
  create_particle(renderer,particle_list,invader->rect->x,invader->rect->y);
  invader_list->size--;
  free_invader(invader);
}

void free_invader(t_invader * invader)
{
  free(invader->rect);
  free(invader);
}
