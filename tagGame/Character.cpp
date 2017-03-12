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

#include "Character.h"
#include "Perception.h"

using namespace tagGame;

Character::Character(ShapePtr shape, ControllerPtr controller) :
   Obstacle(shape),
   controller(controller),
   maxTurnRate(10.0),
   maxSpeed(100.0),
   maxForce(150.0),
   // maxSpeed(50.0),
   // maxForce(950.0),
   tagTime(-1),
   collideTime(-1)
{
}

Character::~Character()
{
}

void Character::setTagged(int tagTime)
{
   // Important to update the perception object with the new information about who the
   // tagged character is.  Otherwise the information has to be calculated by looping
   // through all the characters, which is an unnecessarily inefficiency.
   this->tagTime = tagTime;
   if (0 <= tagTime)
   {  // NOTE: tagTime = -1 implies this character was tagged, but is no longer
      // TODO: make a separate untagged method
      getController()->getPerception()->setTagged(this);
   }
}

