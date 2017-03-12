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

#include "ControllerPursue.h"
#include "Perception.h"
#include "Timer.h"
#include "Util2D.h"

using namespace tagGame;

using namespace std;

ControllerPursue::ControllerPursue(PerceptionPtr perception) :
   Controller(perception),
   isAngry(false)
{
}

ControllerPursue::~ControllerPursue()
{
}

void ControllerPursue::calcAction()
{
   // Currently always chases nearest, TODO: take anger into account
   RealVec v(perception->nearestCharacterPosition().relativeTo(perception->myPosition()));

   // go as fast as possible all the time!
   // TODO: consider predicating speed on v.length()
   action.setDesiredSpeed(1.0); 

   action.setDesiredDirection(v.normalize());
}

Character* ControllerPursue::calcWhoToChase()
{
   Real const minChaseDist = Real(10);
   Real const minChaseRatio = 0.5;
   Character* const c(perception->nearestCharacter());
   Character* const t(perception->getTagged());

   // Sometimes it is obvious who to chase
   if (c == t) { return c; }

   Real const dc = perception->distanceToNearestCharacter();
   // If a character is really close, chase them no matter what
   // Note: minChaseDist is part of the character definition passed in
   //       to the controller's constructor
   if (dc < minChaseDist) { return c; }

   Real const dt = perception->distanceToTagged();
   // If the character who last tagged me is a lot farther away forget it
   // Note: minChaseRatio is also part of the character definition
   if (dt/dc < minChaseRatio) { return c; }

   // OK, it's reasonable to chase the character who last tagged me
   return t;
}

void ControllerPursue::calcIsAngry()
{
   if (!perception->myselfTagged())
   {  // If I'm not tagged then don't be angry
      isAngry = false;
      return;
   }

   // If I'm tagged and angry then stay angry
   if (isAngry) { return; }

   // If I'm tagged and not angry then there's a small chance I'll get angry
   Real probAngry = 0.1;

   // But if I just got tagged, then I get angry in proportion
   // to how often I've been tagged recently
   if (perception->myselfRecentlyTagged())
   {
      int const n(max(9, perception->myRecentTaggedCount()));
      probAngry = Real(n)/Real(10);
   }

   Real const r = MathUtil::uniform01();
   if (r < probAngry) { isAngry = true; }
   else { isAngry = false; }
}

