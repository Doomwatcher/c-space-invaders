#ifndef __RENDERER_H_INCLUDED__
#define __RENDERER_H_INCLUDED__

#include "SDL.h"
#include "SDL_image.h"
#include "position.h"
#include "color.h"

typedef struct s_renderer t_renderer;

struct s_renderer
{
  SDL_Window * window;
  SDL_Renderer * renderer;
};

bool create_window_and_renderer(t_renderer * renderer, char const * title, t_position * position, t_color * color);
void destroy_window_and_renderer(t_renderer * renderer);

#endif /*__RENDERER_H_INCLUDED__*/
