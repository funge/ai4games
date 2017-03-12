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

#ifndef TG_CONTROLLERWANDER_H
#define TG_CONTROLLERWANDER_H

#include "Controller.h"

namespace tagGame
{
   class Perception;

   /// Random walk controller.
   class ControllerWander : public Controller
   {
   public:
      ControllerWander(PerceptionPtr perception);
      virtual ~ControllerWander();

      virtual void calcAction();

   protected:
   private:
   };
}

#endif
