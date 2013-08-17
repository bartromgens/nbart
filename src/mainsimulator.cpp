#include "mainsimulator.h"

#include "body.hpp"
#include "drawable.hpp"
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

  // initialze auxiliary
  int frame = 0;
  srand ( time(NULL) );

  Environment* environment = new Environment(screen);
  std::cout << "Environment created... " << std::endl;

  SDL_Surface* background = NULL;
  background = gf::load_image( "./data/black.png" , false);
  std::cout << "Background loaded..." << std::endl;

  const int TILE_SIZE = 20;
  const int TILE_BORDER_SIZE = 2;
  const int H_TILES = SCREEN_WIDTH/TILE_SIZE;
  const int V_TILES = SCREEN_HEIGHT/TILE_SIZE;

  GravityField gravityField(V_TILES, H_TILES, TILE_SIZE, TILE_BORDER_SIZE);

  int startFPS = SDL_GetTicks();

  MouseState mouseState;

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
    handleKeyAndMouseEvents(environment, screen, mouseState);

    gf::apply_surface( 0, 0 , background, screen );

    if (m_controller->getClear())
    {
      environment->clearAllBodies();
      m_controller->setClear(false);
    }

    if (m_controller->getPlay())
    {
      for (int i = 0 ; i < m_controller->getSimulationSpeed(); i++)
      {
        environment->oneStep();
      }
    }

    // Draw Field
    if (m_controller->getShowField())
    {
      gravityField.draw(screen, environment);
    }

    // Draw Trajectory
    if (m_controller->getShowTrajectories())
    {
      environment->drawTrajectories();
    }

    // Draw Bodies
    if (m_controller->getShowBodies())
    {
      environment->drawBodies();
    }

//    // Check for Collisions
//    if (mergeBodies)
//    {
//      environment->mergeBodies();
//    }

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

  SDL_Quit();

  delete environment;

  std::cout << "MainSimulator::run() - END" << std::endl;
}


void
MainSimulator::handleKeyAndMouseEvents(Environment* environment, SDL_Surface* screen, MouseState& mouseState)
{
  SDL_Event event;

  while ( SDL_PollEvent(&event) )
  {
    handleKeyEvent(event, environment, screen);

    handleMouseEvent(event, environment, screen, mouseState);
  }
}


void
MainSimulator::handleKeyEvent(SDL_Event event, Environment* environment, SDL_Surface* screen)
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

  switch(event.type)
  {
  case SDL_KEYDOWN:
    switch(event.key.keysym.sym)
    {
    case SDLK_UP:
      m_controller->increaseSimulationSpeed();
      break;
    case SDLK_DOWN:
      m_controller->decreaseSimulationSpeed();
      break;
    case SDLK_SPACE:
      m_controller->togglePlay();
      break;
    case SDLK_b:
      m_controller->toggleShowBodies();
      break;
    case SDLK_t:
      m_controller->toggleShowTrajectories();
      break;
    case SDLK_p:
      SDL_SaveBMP(screen, "screenshot.bmp");
      break;
    case SDLK_c:
      m_controller->setClear(true);
      break;
    case SDLK_f:
      m_controller->toggleShowField();
      break;
    case SDLK_m:
//      mergeBodies = !mergeBodies;
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
}


void
MainSimulator::handleMouseEvent(SDL_Event event, Environment* environment, SDL_Surface* screen, MouseState& mouseState)
{
  double newMass = 3.0;

  if( event.type == SDL_MOUSEBUTTONDOWN )
  {
    //If the left mouse button was pressed
    if ( event.button.button == SDL_BUTTON_LEFT)
    {
      SDL_GetMouseState(&mouseState.m_mousedownX, &mouseState.m_mousedownY);
      std::cout << "Left Mouse Down..." << std::endl;
    }
    else if ( event.button.button == SDL_BUTTON_RIGHT)
    {
      SDL_GetMouseState(&mouseState.m_mousedownX, &mouseState.m_mousedownY);
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
  if ( event.type == SDL_MOUSEBUTTONUP )
  {
    if (event.button.button == SDL_BUTTON_LEFT
        || event.button.button == SDL_BUTTON_RIGHT)
    {
      SDL_GetMouseState(&mouseState.m_mouseupX, &mouseState.m_mouseupY);
    }
    else
    {
      return;
    }

    Body* body = 0;
    //If the left mouse button was pressed
    if ( event.button.button == SDL_BUTTON_LEFT)
    {
      body = new Body(environment, screen, "./data/blurball.png");
      body->setMass(newMass);
      body->setRadius(sqrt(newMass*20));\
      environment->addBody(body);
    }
    else if ( event.button.button == SDL_BUTTON_RIGHT)
    {
      body = new Body(environment, screen, "./data/greenball.png");
      body->setMass(0.1);
      body->setRadius(sqrt(0.4*20));
      environment->addMasslessBody(body);
    }

    double vx = (mouseState.m_mouseupX - mouseState.m_mousedownX) / 500.0;
    double vy = (mouseState.m_mouseupY - mouseState.m_mousedownY) / 500.0;
    body->setPosition(mouseState.m_mousedownX, mouseState.m_mousedownY);
    body->setVelocity(vx, vy);
  }
}

