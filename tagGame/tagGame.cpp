// ----------------------------------------------------------------------------
//
// tagGame - Example code from the book:
//
//           Artficial Intelligence for Computer Games: An Introduction
//           by John David Funge
//
//           www.ai4games.org
//
// Source code distributed under the Copyright (c) 2003-2007, John David Funge
// Original author: John David Funge (www.jfunge.com)
//
// Licensed under the Academic Free License version 3.0 
// (for details see LICENSE.txt in this directory).
//
// ----------------------------------------------------------------------------

#include "Simulator.h"
#include "Gui.h"
#include "Character.h"
#include "ControllerPC.h"
#include "ControllerPursue.h"
#include "ControllerEvade.h"
#include "ControllerWander.h"
#include "ControllerPeriodic.h"
#include "ControllerPeriodicRamp.h"
#include "ControllerConditional.h"
#include "ControllerAvoid.h"
#include "ControllerRandomize.h"
#include "Perception.h"
#include "Util.h"
#include "Obstacle.h"
#include "CircleRenderer.h"
#include "Circle.h"
#include "Side.h"
#include "JoystickSDL.h"
#include "KeyboardSDL.h"
#include "Timer.h"
#include "CharacterRenderer.h"
#include "Util2D.h"

#if defined(__APPLE__)
#include <SDL.h>  // needed on MacOSX
#endif

#if defined(_MSC_VER)
#define NOMINMAX
#include <windows.h>
#endif

#include <cstdlib>

using namespace tagGame;

using namespace std;

// TODO: make more ptr variables const
// TODO: remove calc prefixes

static ControllerPtr createPCController(PerceptionPtr perception)
{
   ControllerPtr c(new ControllerPC<JoystickSDL>(perception));
   // TODO: figure out how to use std::tr1::static_pointer_cast
   // Note: &*c returns a naked pointer regardless or whether c is a SharedPtr or a naked one
   // TODO: make a dummy wrapper class around regular pointers and give it methods required
   // to avoid this, and similar, hacks
   if (!static_cast<ControllerPC<JoystickSDL>*>(&*c)->init())
   {
      Util::warn("Failed to find a joystick, defaulting to keyboard control.");
      // TODO: make a dummy wrapper class around regular pointers and give it methods required
      // to avoid this, and similar, conditional compilations.
#if defined(TG_USE_TR1)
      c.reset(new ControllerPC<KeyboardSDL>(perception));
#else
      c = new ControllerPC<KeyboardSDL>(perception);
#endif
   }
#if 0
   ControllerPtr wander(new ControllerPeriodic(perception, 10, new ControllerWander(perception)));
   c = new ControllerAvoid(perception, wander);
#endif
   return c;
}

static ControllerPtr createNPCController(PerceptionPtr perception, Real radius)
{
   // Define what counts as the tagged character being "near"
   Real const tagNear = Real(2) * radius;
   
   // Define what counts as the tagged character being "far"
   Real const tagFar = Real(10) * tagNear;

   // What's the minimum time (in seconds) allowed between decisions
   Real const minPeriod = 0.2;

   // What's the maximum time (in seconds) allowed between decisions
   Real const maxPeriod = 0.4;

   return ControllerPtr(
             new ControllerConditional(perception,
             &Perception::myselfTagged,
             ControllerPtr(new ControllerAvoid(perception, ControllerPtr(new ControllerPursue(perception)))),
             ControllerPtr(new ControllerAvoid(perception,
                ControllerPtr(new ControllerPeriodicRamp(perception,
                   ControllerPtr(new ControllerRandomize(perception,
                      ControllerPtr(new ControllerEvade(perception)),
                      &Perception::distanceToTagged, tagNear, tagFar)),
                                                         &Perception::distanceToTagged, tagNear, tagFar, minPeriod, maxPeriod))))));
}

static void setupCharacters(GameState& gs)
{
   // add some characters
   size_t const characterCount = 5;

   CharacterRendererPtr rendererPCPtr(new CharacterRenderer());
   rendererPCPtr->setColor(Gui::getColorFromName("blue"));
   rendererPCPtr->setColorFlash(Gui::getColorFromName("red"));

   // Shared renderer for all NPCs
   CharacterRendererPtr rendererNPCPtr(new CharacterRenderer());
   rendererNPCPtr->setColor(Gui::getColorFromName("green"));
   rendererNPCPtr->setColorFlash(Gui::getColorFromName("red"));

   Real const radius = Real(10);
   
   // Shared perception object (see Chapter 3)
   PerceptionPtr perception(new Perception(&gs));

   for (size_t i = 0; i < characterCount; i++)
   {
      CirclePtr cs(new Circle());
      cs->setRadius(radius);
      CharacterPtr c;
      if (0 == i)
      {
#if defined(TG_USE_TR1)
         c.reset(new Character(cs, createPCController(perception)));
#else
         c = new Character(cs, createPCController(perception));
#endif
         c->setRenderer(rendererPCPtr);
      }
      else
      {
#if defined(TG_USE_TR1)
         c.reset(new Character(cs, createNPCController(perception, radius)));
#else
         c = new Character(cs, createNPCController(perception, radius));
#endif
         c->setRenderer(rendererNPCPtr);
      }
      c->setPosition(Util2D::randomPosition(gs.getWorldDim()));
      c->setMass(1);
      // TODO: set obstacle properties too
      // TODO: add sets to contructor parameters for all objects
      // TODO: set other properties
      // TODO: inside obstacle circle set radius to more default looking defaults
      // TODO: assert that me is not NULL for all relevant percepts (ditto for tagged, etc)
      gs.addCharacter(c);
   }
}

static void setupObstacles(GameState& gs)
{
   CircleRendererPtr osr(new CircleRenderer());
   osr->setColor(Gui::getColorFromName("white"));

   RealVec const& worldDim(gs.getWorldDim());

   size_t const circularObstacleCount = 7;
   for (size_t i = 0; i < circularObstacleCount; i++)
   {
      ObstaclePtr o(new Obstacle(CirclePtr(new Circle())));
      o->setRenderer(osr);
      o->setPosition(Util2D::randomPosition(worldDim));
      gs.addObstacle(o);
   }

   RealVec normal(Util2D::dim);
   RealVec begin(Util2D::dim);
   RealVec end(Util2D::dim);

   vector<ObstaclePtr> sides(4);

   SidePtr s(new Side());
   begin.set(0);
   end.set(0);
   end[1] = worldDim[1];
   s->setBegin(end);
   s->setEnd(begin);
   normal.set(Real(0));
   normal[0] = Real(1);
   s->setNormal(normal);
   s->setDistance(Real(0));
#if defined(TG_USE_TR1)
   sides[0].reset(new Obstacle(s));

   s.reset(new Side());
#else
   sides[0] = new Obstacle(s);

   s = new Side();
#endif
   begin[0] = worldDim[0];
   end[0] = worldDim[0];
   s->setBegin(end);
   s->setEnd(begin);
   normal[0] = Real(-1);
   s->setNormal(normal);
   s->setDistance(-worldDim[0]);
#if defined(TG_USE_TR1)
   sides[1].reset(new Obstacle(s));

   s.reset(new Side());
#else
   sides[1] = new Obstacle(s);

   s = new Side();
#endif
   begin.set(0);
   end[1] = 0;
   s->setBegin(end);
   s->setEnd(begin);
   normal.set(Real(0));
   normal[1] = Real(1);
   s->setNormal(normal);
   s->setDistance(Real(0));
#if defined(TG_USE_TR1)
   sides[2].reset(new Obstacle(s));

   s.reset(new Side());
#else
   sides[2] = new Obstacle(s);

   s = new Side();
#endif
   begin[1] = worldDim[1];
   end[1] = worldDim[1];
   s->setBegin(end);
   s->setEnd(begin);
   normal[1] = Real(-1);
   s->setNormal(normal);
   s->setDistance(-worldDim[1]);
#if defined(TG_USE_TR1)
   sides[3].reset(new Obstacle(s));
#else
   sides[3] = new Obstacle(s);
#endif

   for (size_t i = 0; i < sides.size(); i++)
   {
      gs.addObstacle(sides[i]);
   }
}

int main(int argc, char** argv)
{
   RealVec worldDim(Util2D::dim);
   worldDim.set(512.0);
   GameState gs(worldDim);
   Simulator sim(&gs);

   setupCharacters(gs);

   setupObstacles(gs);

   Gui::createWindow(int(worldDim[0]), int(worldDim[1]), "tagGame");

   Timer& theTimer = Timer::theTimer();

   theTimer.start();

   // Make character 0 the tagged character.
   (*gs.getCharacterListBegin())->setTagged(theTimer.gameTicks());

   Real lastGameTime = theTimer.gameTime();
   Real lastWallTime = theTimer.time();
   int const fpsFreq(100);
   while (true)
   {
      Gui::render(&gs);
      gs.incFrame();
      Real const gameTime = theTimer.gameTime();
      Real const deltaGT = gameTime - lastGameTime;
      lastGameTime = gameTime;
      if (false && 0 == gs.getFrame() % fpsFreq)
      {
         Real const wallTime = theTimer.time();
         Real const deltaWT = wallTime - lastWallTime;
         lastWallTime = wallTime;
         cerr << "fps: " << Real(fpsFreq)/deltaWT << endl;
      }
      if (Gui::isQuit()) { break; }
      sim.forward(deltaGT);
   }

   Gui::destroyWindow();

   exit(EXIT_SUCCESS);
}
