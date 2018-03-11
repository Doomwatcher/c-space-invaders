#include <stdio.h>
#include <stdbool.h>
#include <io.h>
#include <time.h>
#include "SDL.h"
#include "gameloop.h"
#include "destroy.h"

int main(int ac, char ** av)
{
  (void)ac;(void)av;

  time_t t;
  t_game_data game_data;

  srand((unsigned)time(&t));

  init(&game_data);
  loader(&game_data);
  creator(&game_data);

  gameloop(&game_data);

  destroy(&game_data);

  SDL_Quit();

  return 0;
}
