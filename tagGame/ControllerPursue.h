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

#ifndef TG_CONTROLLERPURSUE_H
#define TG_CONTROLLERPURSUE_H

#include "Controller.h"

namespace tagGame
{
   class Character;
   class Obstacle;

   /// Simple controller that chases the character it's "angry" with, unless
   /// it's not angry in which cases it chases the nearest character.
   class ControllerPursue : public Controller
   {
   public:
      ControllerPursue(PerceptionPtr perception);
      virtual ~ControllerPursue();

      virtual void calcAction();

   protected:
      Character* calcWhoToChase();
      void calcIsAngry();

   private:
      bool isAngry;
   };
}

#endif
