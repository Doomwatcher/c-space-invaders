#include <stdio.h>
#include <stdbool.h>
#include <io.h>
#include <time.h>
#include "SDL.h"
#include "SDL_image.h"
#include "gameloop.h"

void loader(t_game_data * game_data)
{
  char const * player_img_1_path;
  char const * player_img_2_path;
  char const * invader1_img_1_path;
  char const * invader1_img_2_path;
  char const * invader2_img_1_path;  
  char const * invader2_img_2_path;
  char const * invader3_img_1_path;
  char const * invader3_img_2_path;
  char const * projectile_player_path;
  char const * projectile_invader_path;
  char const * projectile2_invader_path;
  
  player_img_1_path        = "assets/player.png";
  player_img_2_path        = "assets/player-1.png";
  invader1_img_1_path      = "assets/Inv1.png";
  invader1_img_2_path      = "assets/Inv1-1.png";
  invader2_img_1_path      = "assets/Inv2.png";
  invader2_img_2_path      = "assets/Inv2-1.png";
  invader3_img_1_path      = "assets/Inv3.png";
  invader3_img_2_path      = "assets/Inv3-1.png";
  projectile_player_path   = "assets/fire2.png";
  projectile_invader_path  = "assets/fire1.png";
  projectile2_invader_path = "assets/fire1-1.png";

  load_texture(player_img_1_path,game_data->renderer,&game_data->textures->player_texture);
  load_texture(player_img_2_path,game_data->renderer,&game_data->textures->player_texture2);
  load_texture(invader1_img_1_path,game_data->renderer,&game_data->textures->invader1_texture);
  load_texture(invader1_img_2_path,game_data->renderer,&game_data->textures->invader1_texture2);
  load_texture(invader2_img_1_path,game_data->renderer,&game_data->textures->invader2_texture);
  load_texture(invader2_img_2_path,game_data->renderer,&game_data->textures->invader2_texture2);
  load_texture(invader3_img_1_path,game_data->renderer,&game_data->textures->invader3_texture);
  load_texture(invader3_img_2_path,game_data->renderer,&game_data->textures->invader3_texture2);
  load_texture(projectile_player_path,game_data->renderer,&game_data->textures->projectile_player_texture);
  load_texture(projectile_invader_path,game_data->renderer,&game_data->textures->projectile_invader_texture);
  load_texture(projectile2_invader_path,game_data->renderer,&game_data->textures->projectile_invader_texture2);
}

bool load_texture(char const * path, t_renderer * renderer, SDL_Texture ** texture)
{
  *texture = IMG_LoadTexture(renderer->renderer,path);

  if (!texture)
      return false;

  return true;
}

void destroy_texture(SDL_Texture * texture)
{
  if (texture)
    SDL_DestroyTexture(texture);
}
