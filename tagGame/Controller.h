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

#ifndef TG_CONTROLLER_H
#define TG_CONTROLLER_H

#include "Action.h"

namespace tagGame
{
   class Perception;
   class Action;
   class Controller;

   typedef SharedPtr<Perception>::type PerceptionPtr;
   typedef SharedPtr<Controller>::type ControllerPtr;

   /// The base class for all controllers.
   class Controller
   {
   public:
      inline Controller(PerceptionPtr perception);
      inline virtual ~Controller();

      /// Calculate an action.
      virtual void calcAction() = 0;
      /// Get the last computed action.
      inline Action const& getAction();
      /// Overide the last computed action.
      inline void setAction(Action const& action);
      /// Get a pointer to the current perception object.
      inline PerceptionPtr getPerception();
      /// Use a new perception object.
      /// Being able to swap in different perception objects can be used
      /// for some interesting AI effects (see Chapter 3 for more details).
      inline void setPerception(PerceptionPtr perception);
   protected:
      // The controller's perception object (see Chapter 3).
      PerceptionPtr perception;
      // The last calculated action.
      Action action;
   private:
   }; // Controller

   Controller::Controller(PerceptionPtr perception) :
      perception(perception)
   {
   }

   Controller::~Controller()
   {
   }

   Action const& Controller::getAction()
   {
      return this->action;
   }
   
   void Controller::setAction(Action const& action)
   {
      this->action = action;
   }
   
   PerceptionPtr Controller::getPerception()
   {
      return perception;
   }
   
   void Controller::setPerception(PerceptionPtr perception)
   {
      this->perception = perception;
   }
}

#endif
