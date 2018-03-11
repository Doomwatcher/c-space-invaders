#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <io.h>
#include "entity.h"

t_projectile_list * projectile_list_create(void)
{
  t_projectile_list * projectile_list = (t_projectile_list *)malloc(sizeof(t_projectile_list));

  projectile_list->size = 0;
  projectile_list->head = NULL;
  projectile_list->tail = NULL;

  return projectile_list;
}

void create_projectile (SDL_Texture * texture, SDL_Texture * texture2, t_projectile_list * projectile_list, unsigned int x, unsigned int y, bool player_projectile)
{
  t_projectile * projectile = (t_projectile *)malloc(sizeof(t_projectile));
  SDL_Rect * rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));

  rect->x = x;
  rect->y = y;
  rect->w = (player_projectile) ? 3 : 6;
  rect->h = (player_projectile) ? 20 : 11;

  projectile->texture = texture;
  projectile->texture2 = texture2;
  projectile->rect = rect;

  projectile->player_projectile = player_projectile;

  projectile->destroy_it = false;
  projectile->switch_texture = false;

  projectile_add_to_list(projectile,projectile_list); 
}

void refresh_projectile_position(t_projectile_list * projectile_list)
{
  t_projectile * projectile;

  for (unsigned int i = 1 ; i <= projectile_list->size ; i++)
    {
      projectile = find_projectile(i,projectile_list);
      if (projectile->player_projectile)
	projectile->rect->y -= 5;
      else
	{
	  projectile->rect->y += 2;
	  if (projectile->rect->y%10 == 0)
	    {
	      change_projectile_texture(projectile);
	    }
	}
    }
}

void change_projectile_texture(t_projectile * projectile)
{
  if (!projectile->switch_texture)
    projectile->switch_texture = true;
  else if (projectile->switch_texture)
    projectile->switch_texture = false;
}


 void projectile_add_to_list(t_projectile * projectile, t_projectile_list * projectile_list)
{
  if (projectile_list->head == NULL)
    {
      projectile_list->size++;
      projectile_list->head = projectile;
      projectile->next = NULL;
    }
  else
    {
      projectile_list->size++;
      projectile->next = NULL;
      find_projectile(projectile_list->size-1,projectile_list)->next = projectile;
    }

  projectile_list->tail = find_projectile(projectile_list->size,projectile_list);
}

t_projectile * find_projectile(unsigned int num, t_projectile_list * projectile_list)
{ 
  t_projectile * finded_projectile;

  if (projectile_list->size == 0)
    return NULL;

  if (num > projectile_list->size)
    return 0;

  if (num == 1)
    return projectile_list->head;

  finded_projectile = projectile_list->head;

  for (unsigned int i = 1 ; i < num ; i++)
    {
      finded_projectile = finded_projectile->next;  
    }

  return finded_projectile;
}

void render_projectile(t_renderer * renderer, t_projectile_list * projectile_list)
{
  t_projectile * projectile;

  for (unsigned int i = 1 ; i <= projectile_list->size ; i++)
    {
      projectile = find_projectile(i,projectile_list);
      if (projectile->player_projectile)
	SDL_RenderCopy(renderer->renderer, projectile->texture, NULL, projectile->rect);
      else
	{
	  if (!projectile->switch_texture)
	    {
	    SDL_Rect src = {20,16,12,22};
	    SDL_RenderCopy(renderer->renderer, projectile->texture, &src, projectile->rect);
	    }
	  else if (projectile->switch_texture)
	    {
	    SDL_Rect src = {19,14,12,22};
	    SDL_RenderCopy(renderer->renderer, projectile->texture2, &src, projectile->rect);
	    }
	}	
    }
}

void player_shoot(SDL_Texture * projectile_player_texture, t_projectile_list * projectile_list, unsigned int x, unsigned int y)
{
  create_projectile(projectile_player_texture,NULL,projectile_list,x+10,y,true);
}

void invader_shoot(SDL_Texture * projectile_invader_texture, SDL_Texture * projectile_invader_texture2, t_projectile_list * projectile_list, t_invader_list * invader_list)
{
  unsigned int x;
  unsigned int y;
  t_invader * shooting_invader;
  if (invader_list->size > 0)
    shooting_invader = find_invader(rand() % invader_list->size,invader_list);
  else
    return;
  x = shooting_invader->rect->x;
  y = shooting_invader->rect->y;

  create_projectile(projectile_invader_texture,projectile_invader_texture2,projectile_list,x,y,false);
}

void kill_projectile(t_projectile * projectile, t_projectile_list * projectile_list)
{
  if (projectile_list->size ==  1)
    {
      projectile_list->head = NULL;
      projectile_list->tail = NULL;
    }
  else if (projectile == projectile_list->head)
    { 
      projectile_list->head = projectile->next;

    }
  else if (projectile == projectile_list->tail)
    {
      projectile_list->tail = find_projectile(projectile_list->size-1,projectile_list);
      find_projectile(projectile_list->size-1,projectile_list)->next = NULL;
    }
  else
    {      
      for (unsigned int i = 1 ; i <= projectile_list->size ; i++)
	{
	  if (find_projectile(i,projectile_list) == projectile)
	    {
	      find_projectile(i-1,projectile_list)->next = projectile->next;
	      break;
	    }
	}
    }
  projectile_list->size--;
  free_projectile(projectile);
}

void free_projectile(t_projectile * projectile)
{
  free(projectile->rect);
  free(projectile);
}
