#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "collision.h"

void check_collisions(t_game_data * game_data)
{
  bool collision_detected;

  for (unsigned int i = 1 ; i <= game_data->projectile_list->size ; i++)
    {
      if (find_projectile(i,game_data->projectile_list)->player_projectile)
	{
	  for (unsigned int j = 1 ; j <= game_data->invader_list->size ; j++)
	    {	      
	      collision_detected = false;
	      collision_detected = is_colliding(game_data,i,j,1);
	      if (collision_detected)
		{
		  find_projectile(i,game_data->projectile_list)->destroy_it = true;
		  find_invader(j,game_data->invader_list)->destroy_it = true;
		} 
	      collision_detected = false;
	    }
	  for (unsigned int j = 1 ; j <= game_data->obstacle_list->size ; j++)
	    {	      
	      collision_detected = false;
	      collision_detected = is_colliding(game_data,i,j,2);
	      if (collision_detected)
		{
		  find_projectile(i,game_data->projectile_list)->destroy_it = true;
		} 
	      collision_detected = false;
	    }
	  for (unsigned int j = 1 ; j <= game_data->projectile_list->size ; j++)
	    {	
	      if (!find_projectile(j,game_data->projectile_list)->player_projectile)
		{
		  collision_detected = false;
		  collision_detected = is_colliding(game_data,i,j,4);
		  if (collision_detected)
		    {
		      find_projectile(i,game_data->projectile_list)->destroy_it = true;
		      find_projectile(j,game_data->projectile_list)->destroy_it = true;
		    } 
		  collision_detected = false;
		}
	    }
	}
      else if (!find_projectile(i,game_data->projectile_list)->player_projectile)
	{
	  for (unsigned int j = 1 ; j <= game_data->obstacle_list->size ; j++)
	    {	      
	      collision_detected = false;
	      collision_detected = is_colliding(game_data,i,j,2);
	      if (collision_detected)
		{
		  find_projectile(i,game_data->projectile_list)->destroy_it = true;
		  find_obstacle(j,game_data->obstacle_list)->destroy_it = true;
		} 
	      collision_detected = false;
	      collision_detected = is_colliding(game_data,i,0,3);
	      if (collision_detected)
		{
		  find_projectile(i,game_data->projectile_list)->destroy_it = true;
		  game_data->player->is_dead = true;
		} 
	      collision_detected = false;
	    }
	}
    }
}

bool is_colliding(t_game_data * game_data, unsigned int projectile_index, unsigned int entity_index, unsigned int collision_type)
{ 
  unsigned int projectile_x;
  unsigned int projectile_y;
  unsigned int projectile_w;
  unsigned int projectile_h;
  unsigned int entity_x;
  unsigned int entity_y;
  unsigned int entity_w;
  unsigned int entity_h;	      

  projectile_x = find_projectile(projectile_index,game_data->projectile_list)->rect->x;
  projectile_y = find_projectile(projectile_index,game_data->projectile_list)->rect->y;
  projectile_w = find_projectile(projectile_index,game_data->projectile_list)->rect->w;
  projectile_h = find_projectile(projectile_index,game_data->projectile_list)->rect->h;

  if (collision_type == 1)
    {
      entity_x = find_invader(entity_index,game_data->invader_list)->rect->x;
      entity_y = find_invader(entity_index,game_data->invader_list)->rect->y;
      entity_w = find_invader(entity_index,game_data->invader_list)->rect->w;
      entity_h = find_invader(entity_index,game_data->invader_list)->rect->h;
    }
  else if (collision_type == 2)
    {
      entity_x = find_obstacle(entity_index,game_data->obstacle_list)->rect->x;
      entity_y = find_obstacle(entity_index,game_data->obstacle_list)->rect->y;
      entity_w = find_obstacle(entity_index,game_data->obstacle_list)->rect->w;
      entity_h = find_obstacle(entity_index,game_data->obstacle_list)->rect->h;
    }
  else if (collision_type == 3 && entity_index == 0)
    {
      entity_x = game_data->player->rect->x;
      entity_y = game_data->player->rect->y;
      entity_w = game_data->player->rect->w;
      entity_h = game_data->player->rect->h;
    }
  else if (collision_type == 4)
    {
      entity_x = find_projectile(entity_index,game_data->projectile_list)->rect->x;
      entity_y = find_projectile(entity_index,game_data->projectile_list)->rect->y;
      entity_w = find_projectile(entity_index,game_data->projectile_list)->rect->w;
      entity_h = find_projectile(entity_index,game_data->projectile_list)->rect->h;
    }

  if(!find_projectile(projectile_index,game_data->projectile_list)->destroy_it)
    {
      if ((entity_x >= projectile_x + projectile_w)
	  || (entity_x + entity_w <= projectile_x)
	  || (entity_y >= projectile_y + projectile_h)
	  || (entity_y + entity_h <= projectile_y))
	return false;
      else
	return true;
    }
  return false;
}

void destroy_flagged_entities(t_game_data * game_data)
{
  t_projectile * projectile;
  t_invader * invader;
  t_obstacle * obstacle;
  t_particle * particle;

  for (unsigned int i = 1 ; i <= game_data->projectile_list->size ; i++)
    {
      projectile = find_projectile(i,game_data->projectile_list);

      if (projectile->destroy_it)
	kill_projectile(projectile,game_data->projectile_list);
    }

  for (unsigned int i = 1 ; i <= game_data->invader_list->size ; i++)
    {
      invader = find_invader(i,game_data->invader_list);

      if (invader->destroy_it)
	kill_invader(invader,game_data->invader_list,game_data->particle_list,game_data->renderer);
    }
  for (unsigned int i = 1 ; i <= game_data->obstacle_list->size ; i++)
    {
      obstacle = find_obstacle(i,game_data->obstacle_list);

      if (obstacle->destroy_it)
	kill_obstacle(obstacle,game_data->obstacle_list,game_data->particle_list,game_data->renderer);
    }
  for (unsigned int i = 1 ; i <= game_data->particle_list->size ; i++)
    {
      particle = find_particle(i,game_data->particle_list);

      if (particle->destroy_it)
	kill_particle(particle,game_data->particle_list);
    }
  if (game_data->player->is_dead)
    kill_player(game_data->player,game_data->particle_list,game_data->renderer);
}

void remove_leaking_entities(t_projectile_list * projectile_list, t_particle_list * particle_list)
{
  for (unsigned int i = 1 ; i <= projectile_list->size ; i++)
    {
      if ((find_projectile(i,projectile_list)->rect->y < 0)
	  || (find_projectile(i,projectile_list)->rect->y >1000))

	  find_projectile(i,projectile_list)->destroy_it = true;
    }
  for (unsigned int i = 1 ; i <= particle_list->size ; i++)
    {
      if ((find_particle(i,particle_list)->rect->x < 0)
	  || (find_particle(i,particle_list)->rect->x >1000)
	  || (find_particle(i,particle_list)->rect->y < 0)
	  || (find_particle(i,particle_list)->rect->y >1000))

	  find_particle(i,particle_list)->destroy_it = true;
    }
}
