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

#ifndef TG_CONTROLLERPC_H
#define TG_CONTROLLERPC_H

#include "Controller.h"
#include "Util2D.h"

namespace tagGame
{
   /// The player character controller.
   template<class T>
   class ControllerPC : public Controller
   {
   public:
      ControllerPC(PerceptionPtr perception);
      virtual ~ControllerPC();

      bool init();

      virtual void calcAction();

   protected:
   private:
      T joystick;
   }; // ControllerPC

   template<class T>
   ControllerPC<T>::ControllerPC(PerceptionPtr perception) :
      Controller(perception)
   {
   }
   
   template<class T>
   ControllerPC<T>::~ControllerPC()
   {
   }
   
   template<class T>
   bool ControllerPC<T>::init()
   {
      return joystick.init();
   }
   
   template<class T>
   void ControllerPC<T>::calcAction()
   {
      RealVec v(Util2D::dim);
      v[0] = joystick.getX();
      v[1] = joystick.getY();
   
      if (v.isAlmostZero())
      {
         // direction unchanged
         action.setDesiredSpeed(Real(0));
      }
      else
      {
         action.setDesiredSpeed(std::min(1.0, v.length()));
         v.normalize();
         action.setDesiredDirection(v);
      }
   }
}

#endif
