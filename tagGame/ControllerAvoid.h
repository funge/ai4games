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

#ifndef TG_CONTROLLERAVOID_H
#define TG_CONTROLLERAVOID_H

#include "Controller.h"

namespace tagGame
{
   /// Simple controller that avoids obstacles.
   class ControllerAvoid : public Controller
   {
   public:
      ControllerAvoid(PerceptionPtr perception, ControllerPtr defaultController);
      virtual ~ControllerAvoid();

      virtual void calcAction();

   protected:
   private:
      ControllerPtr defaultController;
      Real timeLastCollisionDetected;
   };
}

#endif
