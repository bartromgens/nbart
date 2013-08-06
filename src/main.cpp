#include "body.hpp"
#include "drawable.hpp"
#include "drawableBody.hpp"
#include "environment.hpp"
#include "globfunctions.hpp"
#include "gravityfield.hpp"
#include "importsettings.hpp"
#include "initialpattern.hpp"
#include "node.hpp"

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

int main(int argc, char *argv[])
{
  const int SCREEN_WIDTH = import::getHres();
  const int SCREEN_HEIGHT = import::getVres();
  const int FRAMES_PER_SECOND = import::getFPS();

  // initialize SDL objects
  SDL_Surface *screen = NULL;
  screen = gf::init(screen, "SDL template Title");
  std::cout << "SDL screen initialized... " << std::endl;
  SDL_Event event;

  // initialze auxiliary
  bool quit = false;
  int frame = 0;
  double simSpeed = import::getSimulationSpeed();
  bool showBodies = true;
  bool showTrajectory = false;
  bool showField = false;
  bool mergeBodies = false;
  bool pause = false;
  int mousedownX, mousedownY, mouseupX, mouseupY;
  srand ( time(NULL) );
  double newMass = 3.0;

  Environment* environment = new Environment(screen);
  std::cout << "Environment created... " << std::endl;

  std::vector<Body*> bodies;

  std::cout << "Body vectors initialized... " << std::endl;

  //  const int nBodies = N_BODIES;
  //bodyvec = createPattern4(bodyvec, environment, screen, nBodies);
  //bodyvec = createPattern2(bodyvec, environment, screen, nBodies);
  //bodyvec = createPattern3(bodyvec, environment, screen, nBodies);
  //Body* body = new Body(environment, screen, "./data/whiteball.png");
  //environment->addBody(body);
  //bodyvec.push_back(body);
  //bodyvec.back()->setMass(50);
  //bodyvec.back()->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
  //bodyvec.back()->setVelocity(0,0);
  //bodyvec.back()->setRadius(25);
  std::cout << "Bodies created... " << std::endl;

  SDL_Surface *background = NULL;
  background = gf::load_image( "./data/black.png" , false);
  std::cout << "Background loaded..." << std::endl;

  const int TILE_SIZE = 20;
  const int TILE_BORDER_SIZE = 2;
  const int H_TILES = SCREEN_WIDTH/TILE_SIZE;
  const int V_TILES = SCREEN_HEIGHT/TILE_SIZE;

  GravityField gravityField(V_TILES, H_TILES, TILE_SIZE, TILE_BORDER_SIZE);

  int startFPS = SDL_GetTicks();

  //While the user hasn't quit
  while( quit == false)
  {
    int startFrameTime = SDL_GetTicks();
    //Update the screen
    if( SDL_Flip( screen ) == -1 )
    {
      return 1;
    }
    //Increment the frame counter
    frame++;

    //While there's events to handle
    while( SDL_PollEvent( &event ) )
    {
      //If the user has Xed out the window
      if( event.type == SDL_QUIT )
      {
        //Quit the program
        quit = true;
      }

      if ( event.key.keysym.sym == SDLK_q )
      {
        quit = true;
      }

      switch(event.type){
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
        case SDLK_UP:
          simSpeed *= 1.1;
          break;
        case SDLK_DOWN:
          simSpeed *= 0.9;
          break;
        case SDLK_SPACE:
          pause = !pause;
          break;
        case SDLK_b:
          showBodies = !showBodies;
          break;
        case SDLK_t:
          showTrajectory = !showTrajectory;
          break;
        case SDLK_p:
          SDL_SaveBMP(screen, "screenshot.bmp");
          break;
        case SDLK_c:
          environment->clearAllBodies();
          bodies.clear();
          break;
        case SDLK_f:
          showField = !showField;
          break;
        case SDLK_m:
          mergeBodies = !mergeBodies;
          break;
        case SDLK_1:
          bodies = initialpattern::createPattern1(bodies, environment, screen, 2, 10);
          break;
        case SDLK_2:
          bodies = initialpattern::createPattern1(bodies, environment, screen, 3, 5);
          break;
        case SDLK_3:
          bodies = initialpattern::createPattern1(bodies, environment, screen, 4, 3);
          break;
        case SDLK_4:
          bodies = initialpattern::createPattern1(bodies, environment, screen, 6, 3);
          break;
        case SDLK_5:
          bodies = initialpattern::createPattern1(bodies, environment, screen, 8, 2);
          break;
        case SDLK_6:
          bodies = initialpattern::createPattern2(bodies, environment, screen, 14);
          break;
        case SDLK_7:
          bodies = initialpattern::createPattern3(bodies, environment, screen, 10);
          break;
        case SDLK_8:
          bodies = initialpattern::createPattern4(bodies, environment, screen, 10);
          break;
        case SDLK_9:
          bodies = initialpattern::createPattern5(bodies, environment, screen, 10);
          break;
        default:
          break;
        }
      }

      //If a mouse button was pressed
      if( event.type == SDL_MOUSEBUTTONDOWN )
      {
        //If the left mouse button was pressed
        if ( event.button.button == SDL_BUTTON_LEFT)
        {
          SDL_GetMouseState(&mousedownX, &mousedownY);
          std::cout << "Left Mouse Down..." << std::endl;
        }
        else if ( event.button.button == SDL_BUTTON_RIGHT)
        {
          SDL_GetMouseState(&mousedownX, &mousedownY);
          std::cout << "Right Mouse Down..." << std::endl;
        }
        else if( event.button.button == SDL_BUTTON_WHEELUP )
        {
          newMass *= 1.1;
        }
        else if( event.button.button == SDL_BUTTON_WHEELDOWN )
        {
          newMass *= 0.9;
        }
      }

      //If a mouse button was released
      if( event.type == SDL_MOUSEBUTTONUP )
      {
        //If the left mouse button was pressed
        if ( event.button.button == SDL_BUTTON_LEFT)
        {
          SDL_GetMouseState(&mouseupX, &mouseupY);
          std::cout << "Left Mouse Up..." << std::endl;
          Body* body = new Body(environment, screen, "./data/blurball.png");
          environment->addBody(body);
          bodies.push_back(body);
          bodies.back()->setMass(newMass);
          bodies.back()->setPosition(mousedownX, mousedownY);
          bodies.back()->setRadius(sqrt(newMass*20));
          bodies.back()->setVelocity((mouseupX-mousedownX)/500.0,(mouseupY-mousedownY)/500.0);
        }
        else if ( event.button.button == SDL_BUTTON_RIGHT)
        {
          SDL_GetMouseState(&mouseupX, &mouseupY);
          std::cout << "Right Mouse Up..." << std::endl;
          Body* body = new Body(environment, screen, "./data/greenball.png");

          body->setMass(0.1);
          body->setPosition(mousedownX, mousedownY);
          body->setRadius(sqrt(0.4*20));
          body->setVelocity((mouseupX-mousedownX)/500.0,(mouseupY-mousedownY)/500.0);
          environment->addMasslessBody(body);
        }
      }
    }

    gf::apply_surface( 0, 0 , background, screen );

    if (!pause)
    {
      for (int i = 0 ; i < simSpeed*1 ; i++)
      {
        environment->oneStep();
      }
    }

    // Draw Field
    if (showField)
    {
      gravityField.draw(screen, environment);
    }

    // Draw Trajectory
    if (showTrajectory)
    {
      environment->drawTrajectories();
    }

    // Draw Bodies
    if (showBodies)
    {
      environment->drawBodies();
    }

    // Check for Collisions
    if (mergeBodies)
    {
      environment->mergeBodies();
    }

    //Sleep the remaining frame time
    double timeleft = ( 1000.0 / FRAMES_PER_SECOND ) - (SDL_GetTicks()-startFrameTime);
    if ( frame%FRAMES_PER_SECOND == 0)
    {
      int timeFPSframes = SDL_GetTicks()-startFPS;
      std::cout << "fps: " << round(FRAMES_PER_SECOND/(timeFPSframes/1000.0)) << std::endl;
      startFPS = SDL_GetTicks();
    }

    if (timeleft > 0)
    {
      SDL_Delay(timeleft);
    }
  }

  //Free the surfaces and quit SDL
  SDL_FreeSurface(screen);
  SDL_FreeSurface(background);

  return 0;
}
