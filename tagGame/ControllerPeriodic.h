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

#ifndef TG_CONTROLLERPERIODIC_H
#define TG_CONTROLLERPERIODIC_H

#include "Controller.h"

namespace tagGame
{
   /// Only calculate a new action periodically.
   class ControllerPeriodic : public Controller
   {
   public:
      ControllerPeriodic(PerceptionPtr perception, Real const period, ControllerPtr controller);
      virtual ~ControllerPeriodic();

      inline void setPeriod(Real const period);
      inline Real getPeriod();

      inline void setController(ControllerPtr controller);
      inline ControllerPtr getController();

      virtual void calcAction();

   protected:
      Real timeOfLastDecision;
      Real period;
      ControllerPtr controller;
   private:
   };

   void ControllerPeriodic::setPeriod(Real const period)
   {
      this->period = period;
   }
   
   Real ControllerPeriodic::getPeriod()
   {
      return period;
   }
   
   void ControllerPeriodic::setController(ControllerPtr controller)
   {
      this->controller = controller;
   }
   
   ControllerPtr ControllerPeriodic::getController()
   {
      return controller;
   }
}

#endif
