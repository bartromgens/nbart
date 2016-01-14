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
#include "trajectory.hpp"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

int MainSimulator::nEnvironments = 1;

MainSimulator::MainSimulator(std::shared_ptr<SimulatorController> controller)
  : m_controller(controller),
    m_bodies(),
    m_drawableBodies(),
    m_trajectories(),
    m_massUserDefined(3.0)
{
  m_screenWidth = import::getHres();
  m_screenHeight = import::getVres();
  m_fps = import::getFPS();
  assert(m_fps > 0);
}


MainSimulator::~MainSimulator()
{
  std::cout << "MainSimulator::~MainSimulator()" << std::endl;
}


void
MainSimulator::run()
{
  std::cout << "MainSimulator::run()" << std::endl;

  // initialize SDL objects
  SDL_Surface *screen = NULL;
  screen = gf::init(screen, "SDL template Title");
  std::cout << "SDL screen initialized... " << std::endl;

  // initialze auxiliary
  int frame = 0;
  srand ( time(NULL) );

  std::vector<Environment*> environments;
  for (int i = 0; i < nEnvironments; ++i)
  {
    environments.push_back(new Environment(screen));
  }
  std::cout << "Environments created... " << std::endl;

  SDL_Surface* background = NULL;
  background = gf::load_image( "./data/black.png" , false);
  std::cout << "Background loaded..." << std::endl;

  const int TILE_SIZE = 20;
  const int TILE_BORDER_SIZE = 2;
  const int H_TILES = m_screenWidth/TILE_SIZE;
  const int V_TILES = m_screenHeight/TILE_SIZE;

  const int LINE_RATE = import::getLineRate();

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

    if (m_controller->getPlay())
    {
      oneStep(environments);
    }

    gf::apply_surface( 0, 0 , background, screen );

    // While there's events to handle
    handleKeyAndMouseEvents(environments, screen, mouseState);
    updateBodyList(environments);

    if ( frame%m_fps == 0)
    {
      sortBodies(m_bodies, environments);
    }

    if (m_controller->getClear())
    {
      deleteAllBodies(environments);
    }

    // Draw Field
    if (m_controller->getShowField())
    {
//      gravityField.draw(screen, environment); // needs to work with vector of environments
    }


    for (auto iter = m_bodies.begin(); iter != m_bodies.end(); ++iter)
    {
      assert(m_drawableBodies.find(iter->second->getId()) != m_drawableBodies.end());
      assert(m_trajectories.find(iter->second->getId()) != m_trajectories.end());
      std::array<double, 4> x = iter->second->getState();
      m_drawableBodies[iter->second->getId()]->setCenterPos(x[0], x[1]);

      if ( (frame % (LINE_RATE)) == 0)
      {
        m_trajectories[iter->second->getId()]->addPoint(x[0], x[1]);
      }
    }

    // Draw Bodies
    if (m_controller->getShowBodies())
    {
      drawBodies();
    }

    // Draw Trajectory
    if (m_controller->getShowTrajectories())
    {
//      std::cout << "show trajectories!" << std::endl;
      for (auto iter = m_bodies.begin(); iter != m_bodies.end(); ++iter)
      {
        assert(m_trajectories.find(iter->second->getId()) != m_trajectories.end());
        m_trajectories[iter->second->getId()]->draw();
      }
    }

    //Sleep the remaining frame time
    double timeleft = ( 1000.0 / m_fps ) - (SDL_GetTicks()-startFrameTime);
    if ( frame%m_fps == 0)
    {
      int timeFPSframes = SDL_GetTicks()-startFPS;
      std::cout << "fps: " << round(m_fps/(timeFPSframes/1000.0)) << ", bodies: " << m_bodies.size() << std::endl;
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

//  delete environment;

  std::cout << "MainSimulator::run() - END" << std::endl;
}


void
MainSimulator::oneStep(std::vector<Environment*> environments)
{
  double stepsize = m_controller->getStepSize();
  for (auto iter = environments.begin(); iter != environments.end(); ++iter)
  {
    Environment* environment = *iter;
    environment->oneStep(m_controller->getSimulationSpeed(), stepsize);
  }
}


void
MainSimulator::drawBodies()
{
  for (auto iter = m_bodies.begin(); iter != m_bodies.end(); ++iter)
  {
    assert(m_drawableBodies.find(iter->second->getId()) != m_drawableBodies.end());
    m_drawableBodies[iter->second->getId()]->draw();
  }
}


void
MainSimulator::updateBodyList(std::vector<Environment*> environments)
{
  m_bodies.clear();
  for (auto iter = environments.begin(); iter != environments.end(); ++iter)
  {
    Environment* environment = *iter;
    const std::list<Body*>& bodies = environment->getBodies();
    for (auto iter = bodies.begin(); iter != bodies.end(); ++iter)
    {
      m_bodies[(*iter)->getId()] = *iter;
    }
  }
}


void
MainSimulator::deleteAllBodies(std::vector<Environment*> environments)
{
  for (auto iter = environments.begin(); iter != environments.end(); ++iter)
  {
    (*iter)->clearAllBodies();
    m_drawableBodies.clear();
    m_trajectories.clear();
    updateBodyList(environments);
  }
  m_controller->setClear(false);
}


Body*
MainSimulator::createBody(Environment* environment, int mass, SDL_Surface* screen, std::string imageloc)
{
  Body* body = new Body(imageloc);
  body->setMass(mass);
  int radius = sqrt(mass*20);
  body->setRadius(radius);
  std::unique_ptr<Drawable> drawable = std::unique_ptr<Drawable>(new Drawable(screen, imageloc));
  drawable->setSize(2*radius);
  m_drawableBodies[body->getId()] = std::move(drawable);
  m_trajectories[body->getId()].reset(new Trajectory(screen));
  environment->addBody(body);
  return body;
}


Body*
MainSimulator::createMasslessBody(Environment* environment, SDL_Surface* screen, std::string imageloc)
{
  Body* body = new Body(imageloc);
  environment->addMasslessBody(body);
  m_drawableBodies[body->getId()].reset( new Drawable(screen, imageloc) );
  return body;
}


void
MainSimulator::sortBodies(std::map<std::size_t, const Body*> bodies, std::vector<Environment*> environments)
{
  int nBucketsPerDim = 1;
  std::vector<std::vector<const Body*> > bodyBuckets(nBucketsPerDim*nBucketsPerDim, std::vector<const Body*>(0, 0)); // TODO BR: optimize
//  std::cout << "sortBodies() - nBodies: " << bodies.size() << std::endl;
  for (auto iter = bodies.begin(); iter != bodies.end(); ++iter)
  {
    const Body* body = iter->second;
    const std::array<double, 4>& x = body->getState();
    int width = std::floor(x[0]/(double(m_screenWidth)/nBucketsPerDim));
    int height = std::floor(x[1]/(double(m_screenHeight)/nBucketsPerDim));
    int bucket = height*nBucketsPerDim + width;
    if ( bucket < 0 || bucket >= static_cast<int>(bodyBuckets.size()) )
    {
      continue;
    }
    assert(bucket < static_cast<int>(bodyBuckets.size()));
    bodyBuckets[bucket].push_back(body);
  }

  for (auto iter = environments.begin(); iter != environments.end(); ++iter)
  {
    (*iter)->clearAllBodies();
  }

  unsigned int environNr = 0;
  for (std::size_t i = 0; i < bodyBuckets.size(); ++i)
  {
    for (std::size_t j = 0; j < bodyBuckets[i].size(); ++j)
    {
      assert(environNr < environments.size());
      environments[environNr]->addBody(const_cast<Body*>(bodyBuckets[i][j]));
    }
    environNr++;
  }
}

//void
//MainSimulator::filterBodiesByDistance(int distance_px)
//{

//}


void
MainSimulator::handleKeyAndMouseEvents(std::vector<Environment*> environments, SDL_Surface* screen, MouseState& mouseState)
{
  SDL_Event event;

  while ( SDL_PollEvent(&event) )
  {
    handleKeyEvent(event, environments, screen);

    handleMouseEvent(event, environments, screen, mouseState);
  }
}


void
MainSimulator::handleKeyEvent(SDL_Event event, std::vector<Environment*> /*environments*/, SDL_Surface* screen)
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
//    case SDLK_1:
//      initialpattern::createPattern1(environment, screen, 2, 10);
//      break;
//    case SDLK_2:
//      initialpattern::createPattern1(environment, screen, 3, 5);
//      break;
//    case SDLK_3:
//      initialpattern::createPattern1(environment, screen, 4, 3);
//      break;
//    case SDLK_4:
//      initialpattern::createPattern1(environment, screen, 6, 3);
//      break;
//    case SDLK_5:
//      initialpattern::createPattern1(environment, screen, 8, 2);
//      break;
//    case SDLK_6:
//      initialpattern::createPattern2(environment, screen, 14);
//      break;
//    case SDLK_7:
//      initialpattern::createPattern3(environment, screen, 10);
//      break;
//    case SDLK_8:
//      initialpattern::createPattern4(environment, screen, 10);
//      break;
//    case SDLK_9:
//      initialpattern::createPattern5(environment, screen, 10);
//      break;
    default:
      break;
    }
  }
}


void
MainSimulator::handleMouseEvent(SDL_Event event, std::vector<Environment*> environments, SDL_Surface* screen, MouseState& mouseState)
{
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
      std::cout << "Mouse Wheel Up..." << std::endl;
      m_massUserDefined *= 1.1;
    }
    else if( event.button.button == SDL_BUTTON_WHEELDOWN )
    {
      std::cout << "Mouse Wheel Down..." << std::endl;
      m_massUserDefined *= 0.9;
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
      double angle = 0.0;
//      for (std::size_t i = 0; i < environments.size(); ++i)
      for (std::size_t i = 0; i < 1; ++i)
      {
        std::string imageFile;
        int environmentNr = i%nEnvironments;
        switch (environmentNr%3)
        {
          case 0:
          {
            imageFile = "./data/blurball.png";
            break;
          }
          case 1:
          {
            imageFile = "./data/greenball.png";
            break;
          }
          case 2:
          {
            imageFile = "./data/mars_small.png";
            break;
          }
          default:
          {
            assert(false);
          }
        }
        body = createBody(environments[environmentNr], m_massUserDefined, screen, imageFile);
//        environments[environmentNr]->addBody(body);

        double vx = (mouseState.m_mouseupX - mouseState.m_mousedownX) / 500.0;
        double vy = (mouseState.m_mouseupY - mouseState.m_mousedownY) / 500.0;
        body->setPosition(mouseState.m_mousedownX, mouseState.m_mousedownY);
//        body->setVelocity(vx*cos(angle), vy*sin(angle));
        body->setVelocity(vx, vy);
        angle += (2.0*M_PI)/nEnvironments;
      }

    }
    else if ( event.button.button == SDL_BUTTON_RIGHT)
    {
      body = createMasslessBody(environments[0], screen, "./data/greenball.png");
      body->setMass(0.1);
      body->setRadius(sqrt(0.4*20));
//      environments[0]->addMasslessBody(body);v

      double vx = (mouseState.m_mouseupX - mouseState.m_mousedownX) / 500.0;
      double vy = (mouseState.m_mouseupY - mouseState.m_mousedownY) / 500.0;
      body->setPosition(mouseState.m_mousedownX, mouseState.m_mousedownY);
      body->setVelocity(vx, vy);
    }
  }
}

