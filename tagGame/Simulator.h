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

#ifndef TG_SIMULATOR_H
#define TG_SIMULATOR_H

#include "Action.h"
#include "GameState.h"

namespace tagGame
{
   /// This class is responsible for implementing the game's physics and
   /// updating the game-state accordingly.
   class Simulator
   {
   public:
      Simulator(GameState* gs);
      void forward(Real const deltaT);
   protected:
   private:
      void generateActions();
      void processActions(Real const deltaT);
      void updateCharacter(Real const deltaT, Character* c);
      void resolveCollisions();
      void updateGameState(Real const deltaT);
      void setTagged(Character& newTagged, Character& oldTagged);

      GameState* gs;
   };
}

#endif
