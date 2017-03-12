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

#ifndef TG_CONTROLLERCONDITIONAL_H
#define TG_CONTROLLERCONDITIONAL_H

#include "Controller.h"
#include "Perception.h"

namespace tagGame
{
   /// If the condition is true use controllerTrue, otherwise use controllerFalse.
   class ControllerConditional : public Controller
   {
   public:
      ControllerConditional(PerceptionPtr perception, PerceptBool condition, ControllerPtr controllerTrue, ControllerPtr controllerFalse);
      virtual ~ControllerConditional();

      inline PerceptBool getCondition();
      inline ControllerPtr getControllerTrue();
      inline ControllerPtr getControllerFalse();

      inline void setCondition(PerceptBool condition);
      inline void setControllerTrue(ControllerPtr controllerTrue);
      inline void setControllerFalse(ControllerPtr controllerFalse);

      virtual void calcAction();

   protected:
      PerceptBool condition;
      ControllerPtr controllerTrue;
      ControllerPtr controllerFalse;
   private:
   };

   void ControllerConditional::setCondition(PerceptBool condition)
   {
      this->condition = condition;
   }
   
   PerceptBool ControllerConditional::getCondition()
   {
      return condition;
   }
   
   void ControllerConditional::setControllerTrue(ControllerPtr controllerTrue)
   {
      this->controllerTrue = controllerTrue;
   }
   
   ControllerPtr ControllerConditional::getControllerTrue()
   {
      return controllerTrue;
   }
   
   void ControllerConditional::setControllerFalse(ControllerPtr controllerFalse)
   {
      this->controllerFalse= controllerFalse;
   }
   
   ControllerPtr ControllerConditional::getControllerFalse()
   {
      return controllerFalse;
   }
}

#endif
