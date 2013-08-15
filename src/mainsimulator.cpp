#include "mainsimulator.h"

#include "body.hpp"
#include "drawable.hpp"
#include "drawableBody.hpp"
#include "environment.hpp"
#include "globfunctions.hpp"
#include "gravityfield.hpp"
#include "importsettings.hpp"
#include "initialpattern.hpp"
#include "node.hpp"
#include "simulatorcontroller.h"


#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

MainSimulator::MainSimulator(std::shared_ptr<SimulatorController> controller)
  : m_controller(controller)
{

}


MainSimulator::~MainSimulator()
{
  std::cout << "MainSimulator::~MainSimulator()" << std::endl;
}


void
MainSimulator::run()
{
  std::cout << "MainSimulator::run()" << std::endl;

  const int SCREEN_WIDTH = import::getHres();
  const int SCREEN_HEIGHT = import::getVres();
  const int FRAMES_PER_SECOND = import::getFPS();

  // initialize SDL objects
  SDL_Surface *screen = NULL;
  screen = gf::init(screen, "SDL template Title");
  std::cout << "SDL screen initialized... " << std::endl;
  SDL_Event event;

  // initialze auxiliary
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
  while (!m_controller->getClose())
  {
    int startFrameTime = SDL_GetTicks();
    //Update the screen
    if( SDL_Flip( screen ) == -1 )
    {
      break;
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
        m_controller->setClose(true);
      }

      if ( event.key.keysym.sym == SDLK_q )
      {
        m_controller->setClose(true);
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
          m_controller->setClear(true);
          break;
        case SDLK_f:
          showField = !showField;
          break;
        case SDLK_m:
          mergeBodies = !mergeBodies;
          break;
        case SDLK_1:
          initialpattern::createPattern1(environment, screen, 2, 10);
          break;
        case SDLK_2:
          initialpattern::createPattern1(environment, screen, 3, 5);
          break;
        case SDLK_3:
          initialpattern::createPattern1(environment, screen, 4, 3);
          break;
        case SDLK_4:
          initialpattern::createPattern1(environment, screen, 6, 3);
          break;
        case SDLK_5:
          initialpattern::createPattern1(environment, screen, 8, 2);
          break;
        case SDLK_6:
          initialpattern::createPattern2(environment, screen, 14);
          break;
        case SDLK_7:
          initialpattern::createPattern3(environment, screen, 10);
          break;
        case SDLK_8:
          initialpattern::createPattern4(environment, screen, 10);
          break;
        case SDLK_9:
          initialpattern::createPattern5(environment, screen, 10);
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
          body->setMass(newMass);
          body->setPosition(mousedownX, mousedownY);
          body->setRadius(sqrt(newMass*20));
          body->setVelocity((mouseupX-mousedownX)/500.0,(mouseupY-mousedownY)/500.0);
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

    if (m_controller->getClear())
    {
      environment->clearAllBodies();
      m_controller->setClear(false);
    }

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

  std::cout << "MainSimulator::run() - END" << std::endl;
}