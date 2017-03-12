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

#ifndef TG_CONTROLLEREVADE_H
#define TG_CONTROLLEREVADE_H

#include "Controller.h"

namespace tagGame
{
   /// Simple controller that heads away from the tagged character.
   /// TODO: pass in the percept for who to evade as a parameter.
   class ControllerEvade : public Controller
   {
   public:
      ControllerEvade(PerceptionPtr perception);
      virtual ~ControllerEvade();

      virtual void calcAction();

   protected:
   private:
   };
}

#endif
