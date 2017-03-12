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

#ifndef TG_ACTION_H
#define TG_ACTION_H

#include "Vec.h"

namespace tagGame
{
   /// This class is for representing actions in the tag game.
   /// Currently, the only action is to select a speed and direction.
   class Action
   {
   public:
      Action();
      Action(Action const& a);

      Action& operator=(Action const& a);

      inline void setDesiredDirection(RealVec const& direction);
      inline RealVec const& getDesiredDirection() const;
      inline void setDesiredSpeed(Real const speed);
      inline Real getDesiredSpeed() const;

      // TODO: give all objects output methds
      // TODO: put most of these TODOs into a bugzilla
      std::ostream& output(std::ostream& out) const;

   protected:
   private:
      // Direction and speed are separate so that a character can stop and still
      // remember which direction it was heading.  Also avoids potential rounding
      // problems with vectors whose length might otherwise get close to 0.

      // direction is a unit vector
      RealVec direction;
      // speed is in the range [0, 1]
      Real speed;
   };

   std::ostream& operator<<(std::ostream& out, Action const& a);

   void Action::setDesiredDirection(RealVec const& direction)
   {
      this->direction = direction;
   }
   
   RealVec const& Action::getDesiredDirection() const
   {
      return direction;
   }
   
   void Action::setDesiredSpeed(Real const speed)
   {
      this->speed = speed;
   }
   
   Real Action::getDesiredSpeed() const
   {
      return speed;
   }
}

#endif
