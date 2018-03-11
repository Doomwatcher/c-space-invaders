#ifndef __COLLISION_H_INCLUDED__
#define __COLLISION_H_INCLUDED__

#include "SDL.h"
#include "gameloop.h"

void check_collisions(t_game_data * game_data);
bool is_colliding(t_game_data * game_data, unsigned int projectile_index, unsigned int entity_index, unsigned int collision_type);
void destroy_flagged_entities(t_game_data * game_data);
void remove_leaking_entities(t_projectile_list * projectile_list, t_particle_list * particle_list);

#endif /*__COLLISION_H_INCLUDED__*/
