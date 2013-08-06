#include "body.hpp"
#include "drawable.hpp"
#include "drawableBody.hpp"
#include "environment.hpp"
#include "globfunctions.hpp"
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

  std::vector<Body* > bodyvec;
  std::vector<Body* >::iterator drawit;

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
  const int BORDER_SIZE = 2;
  const int H_TILES = SCREEN_WIDTH/TILE_SIZE;
  const int V_TILES = SCREEN_HEIGHT/TILE_SIZE;

  // initialze field
  std::vector<std::vector<Node*> > field(V_TILES, std::vector<Node*>(H_TILES));
  for (int i = 0; i < V_TILES; i++)
  {
    for (int j = 0; j < H_TILES; j++)
    {
      field[i][j] = new Node(j,i);
    }
  }

  SDL_Rect outtiles[V_TILES][H_TILES];
  for (int i = 0; i < V_TILES; i++)
  {
    for (int j = 0; j < H_TILES; j++)
    {
      outtiles[i][j].x = TILE_SIZE*j;
      outtiles[i][j].y = TILE_SIZE*i;
      outtiles[i][j].w = TILE_SIZE;
      outtiles[i][j].h = TILE_SIZE;
    }
  }

  SDL_Rect insidetiles[V_TILES][H_TILES];
  for (int i = 0; i < V_TILES; i++)
  {
    for (int j = 0; j < H_TILES; j++)
    {
      insidetiles[i][j].x = (TILE_SIZE*j)-BORDER_SIZE;
      insidetiles[i][j].y = (TILE_SIZE*i)-BORDER_SIZE;
      insidetiles[i][j].w = TILE_SIZE-(2*BORDER_SIZE);
      insidetiles[i][j].h = TILE_SIZE-(2*BORDER_SIZE);
    }
  }


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
          bodyvec.clear();
          break;
        case SDLK_f:
          showField = !showField;
          break;
        case SDLK_m:
          mergeBodies = !mergeBodies;
          break;
        case SDLK_1:
          bodyvec = initialpattern::createPattern1(bodyvec, environment, screen, 2, 10);
          break;
        case SDLK_2:
          bodyvec = initialpattern::createPattern1(bodyvec, environment, screen, 3, 5);
          break;
        case SDLK_3:
          bodyvec = initialpattern::createPattern1(bodyvec, environment, screen, 4, 3);
          break;
        case SDLK_4:
          bodyvec = initialpattern::createPattern1(bodyvec, environment, screen, 6, 3);
          break;
        case SDLK_5:
          bodyvec = initialpattern::createPattern1(bodyvec, environment, screen, 8, 2);
          break;
        case SDLK_6:
          bodyvec = initialpattern::createPattern2(bodyvec, environment, screen, 14);
          break;
        case SDLK_7:
          bodyvec = initialpattern::createPattern3(bodyvec, environment, screen, 10);
          break;
        case SDLK_8:
          bodyvec = initialpattern::createPattern4(bodyvec, environment, screen, 10);
          break;
        case SDLK_9:
          bodyvec = initialpattern::createPattern5(bodyvec, environment, screen, 10);
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
          bodyvec.push_back(body);
          bodyvec.back()->setMass(newMass);
          bodyvec.back()->setPosition(mousedownX, mousedownY);
          bodyvec.back()->setRadius(sqrt(newMass*20));
          bodyvec.back()->setVelocity((mouseupX-mousedownX)/500.0,(mouseupY-mousedownY)/500.0);
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
      for (int i = 0; i < V_TILES; i++)
      {
        for (int j = 0; j < H_TILES; j++)
        {
          //          Color tempcol = field[i][j]->getColor();
          SDL_FillRect( screen, &outtiles[i][j], SDL_MapRGB( screen->format, 0, 0, 0) );
          double fieldStrength = environment->getFieldStrength(j*TILE_SIZE+TILE_SIZE/2.0,i*TILE_SIZE+TILE_SIZE/2.0) * 3.0e7;

          fieldStrength = pow(fieldStrength, 1.0/3.0);

          if (fieldStrength > 255)
          {
            fieldStrength = 255;
          }
          //cout << fieldStrength << endl;
          SDL_FillRect( screen, &insidetiles[i][j], SDL_MapRGB( screen->format, fieldStrength, 0, 0) );
        }
      }
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
    if (frame%FRAMES_PER_SECOND == 0)
    {
      int timeFPSframes = SDL_GetTicks()-startFPS;
      std::cout << "fps: " << round(FRAMES_PER_SECOND/(timeFPSframes/1000.0)) << std::endl;
      startFPS = SDL_GetTicks();

      //		    cout << "Energy: " << environment->getEnergy() << endl;
      //		    cout << "Linear Momentum: " << environment->getLinearMomentum() << endl;
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
