#ifndef GLOBFUNCTIONS_H_
#define GLOBFUNCTIONS_H_

#include <iostream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "importsettings.hpp"

namespace gf {

	SDL_Surface *load_image( std::string filename , bool transparent);
	void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
	SDL_Surface* init(SDL_Surface *screen, std::string windowtitle);

}

#endif /* GLOBFUNCTIONS_H_ */

