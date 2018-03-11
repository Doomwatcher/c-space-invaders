#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "renderer.h"

bool create_window_and_renderer(t_renderer * renderer, char const * title, t_position * position, t_color * color)
{
  if (0 != SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER))
    return false;

  renderer->window = SDL_CreateWindow(title, position->x, position->y, position->w, position->h, SDL_WINDOW_SHOWN);

  if (!renderer->window)
    return false;

  renderer->renderer = SDL_CreateRenderer(renderer->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer->renderer)
    return false;

  SDL_SetRenderDrawColor(renderer->renderer, color->red, color->green, color->blue, color->alpha);
  SDL_RenderClear(renderer->renderer);
  SDL_SetRenderDrawBlendMode(renderer->renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer->renderer, 255, 255, 255, 50);

  return true;
}

void destroy_window_and_renderer(t_renderer * renderer)
{
  if (renderer->renderer)
    SDL_DestroyRenderer(renderer->renderer);
  if (renderer->window)
    SDL_DestroyWindow(renderer->window);
}
