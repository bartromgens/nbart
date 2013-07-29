#include "drawable.hpp"

#include "drawableBody.hpp"

DrawableBody::DrawableBody(SDL_Surface *screen, std::string imageloc)
  : Drawable(screen, imageloc)
{
}
