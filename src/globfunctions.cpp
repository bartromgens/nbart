#include "globfunctions.hpp"

using namespace std;

SDL_Surface*
gf::load_image( std::string filename , bool transparent)
{
  //The image that's loaded
  SDL_Surface* loadedImage = NULL;

  //The optimized image that will be used
  SDL_Surface* optimizedImage = NULL;

  //Load the image
  loadedImage = IMG_Load( filename.c_str() );
  if (transparent)
  {
    SDL_SetColorKey( loadedImage, SDL_SRCCOLORKEY, SDL_MapRGB(loadedImage->format, 0, 0, 0) );
  }
  //If the image loaded
  if (loadedImage != NULL)
  {
    //Create an optimized image
    optimizedImage = SDL_DisplayFormatAlpha( loadedImage );

    //Free the old image
    SDL_FreeSurface( loadedImage );

  }
  else
  {
    cout << filename << " not found." << endl;
  }

  //Return the optimized image
  return optimizedImage;
}


void
gf::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
  //Temporary rectangle to hold the offsets
  SDL_Rect offset;

  //Get the offsets
  offset.x = x;
  offset.y = y;

  //Blit the surface
  SDL_BlitSurface( source, NULL, destination, &offset );
}


SDL_Surface*
gf::init(SDL_Surface *screen, std::string windowtitle)
{
  // Initialize all SDL subsystems
  if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
  {
    cout << "failure initializing subsystems " << endl;
  }

  // Set up the screen
  const SDL_VideoInfo* vidinfo = SDL_GetVideoInfo();
  if (import::getFullscreen() == 1)
  {
    screen = SDL_SetVideoMode(  import::getHres(),  import::getVres(), 32, SDL_FULLSCREEN|SDL_HWSURFACE );
  }
  else
  {
    screen = SDL_SetVideoMode(  import::getHres(),  import::getVres(), 32, SDL_HWSURFACE );
  }

  // If there was an error in setting up the screen
  if( screen == NULL )
  {
    cout << "there was an error in setting up the screen " << endl;
  }

  // Set the window caption
  SDL_WM_SetCaption( windowtitle.c_str(), NULL );

  // If everything initialized fine
  return screen;
}
