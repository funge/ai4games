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

#ifndef TG_CHARACTER_H
#define TG_CHARACTER_H

#include "Obstacle.h"
#include "Action.h"
#include "Controller.h"
#include "Shape.h"

namespace tagGame
{
   class Controller;

   /// The main class for NPCs and player characters.
   /// NPCs and player characters differ only in their controller's and renderer's.
   /// Characters are also circular obstacles.
   class Character : public Obstacle
   {
   public:
      Character(ShapePtr shape, ControllerPtr controller);
      ~Character();

      /// Get this character's controller
      inline ControllerPtr getController();
      /// Set this character's controller
      inline void setController(ControllerPtr controller);

      inline bool getIsTagged() const;
      inline int getTaggedTime() const;
      // TODO: rename to setTaggedTime
      void setTagged(int tagTime);

      inline void setCollideTime(int collideTime);
      inline int getCollideTime() const;

      inline void calcAction();
      inline Action const& getAction() const;
      inline Real getMaxTurnRate() const;
      inline Real getMaxSpeed() const;
      inline Real getMaxForce() const;

   protected:
   private:
      /// Pointer to this character's (possibly shared) controller
      ControllerPtr controller;
      Action lastAction;
      Real maxTurnRate;
      Real maxSpeed;
      Real maxForce;
      // How long since this character was tagged (-1 if not currently tagged).
      int tagTime;
      // How long since this character collided with something (-1 if never collided).
      int collideTime;
   };

   typedef SharedPtr<Character>::type CharacterPtr;
   typedef std::vector<CharacterPtr> CharacterList;
   typedef CharacterList::const_iterator CharacterIteratorConst;
   typedef CharacterList::iterator CharacterIterator;

   void Character::calcAction()
   {
      controller->calcAction();
      // Controller's can be shared, so save this character's last computed action
      // in the class
      lastAction = controller->getAction();
   }
   
   Action const& Character::getAction() const
   {
      return lastAction;
   }

   bool Character::getIsTagged() const
   {
      return 0 <= tagTime;
   }
   
   int Character::getTaggedTime() const
   {
      return tagTime;
   }
   
   Real Character::getMaxTurnRate() const
   {
      return maxTurnRate;
   }
   
   Real Character::getMaxSpeed() const
   {
      if (getIsTagged()) { return 0.8 * maxSpeed; }
      return maxSpeed;
   }
   
   Real Character::getMaxForce() const
   {
      return maxForce;
   }
   
   ControllerPtr Character::getController()
   {
      return controller;
   }
   
   void Character::setController(ControllerPtr controller)
   {
      this->controller = controller;
   }
   
   void Character::setCollideTime(int collideTime)
   {
      this->collideTime = collideTime;
   }
   
   int Character::getCollideTime() const
   {
      return collideTime;
   }
}

#endif
