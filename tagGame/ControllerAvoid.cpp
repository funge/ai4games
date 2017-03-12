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

#include "ControllerAvoid.h"
#include "Perception.h"
#include "Gui.h"
#include "Timer.h"
#include "Util2D.h"
#include "Obstacle.h"

// usefule for debugging
#include "Gui.h"

using namespace tagGame;

ControllerAvoid::ControllerAvoid(PerceptionPtr perception, ControllerPtr defaultController) :
   Controller(perception),
   defaultController(defaultController),
   timeLastCollisionDetected(-1)
{
}

ControllerAvoid::~ControllerAvoid()
{
}

void ControllerAvoid::calcAction()
{
   // TODO: could pass this is as a parameter
   Real const soonThreshold = Real(50);

   // TODO: re-factor so that we have a timedEventController.  Then
   // get rid of this "if" and wrap the two controllers in the
   // timedEventController.
#if 0
   Real const t = perception->timeToCollision();
   if (t <= soonThreshold)
   {
      Gui::setColor(Gui::getColorFromName("red"));
   }
   else
   {
      Gui::setColor(Gui::getColorFromName("yellow"));
   }
   RealVec rp1(perception->nextCollisionPoint().relativeTo(perception->myPosition()));
   rp1.normalize();
   rp1.scale(perception->timeToCollision());
   rp1.add(perception->myPosition());
   Gui::drawLineSegment(perception->myPosition(), rp1);
   // Gui::drawLineSegment(perception->myPosition(), perception->nextCollisionPoint());
   // Gui::render(perception->getGameState());
#endif

   // TODO: consider a version that passes in the time to avoid - this is hard-wired to
   // only avoid static obstacles, which is BAD.
   if (perception->timeToCollision() > soonThreshold || (perception->nextCollider() && Inf != perception->nextCollider()->getMass()))
   {  // No collision danger.
      Real const time = perception->getTime();
      // How many milliseconds to wait after a potential collision was detected before
      // resuming with the default controller.  TODO: consider making a settable class variable.
      Real const delay = 0.5;
      if (timeLastCollisionDetected < 0 || time - timeLastCollisionDetected > delay)
      {
         defaultController->calcAction();
         action = defaultController->getAction();
         return;
      }
      else
      {  // Just continue with last action.
         // TODO: consider some time discounted blend of default controller and
         // avoidance vector.
         return;
      }
   }

   timeLastCollisionDetected = perception->getTime();

   // Collision danger present so need to take evasive action.
   // RealVec rp(perception->nextCollisionPoint().relativeTo(perception->myPosition()));
   RealVec rp(perception->nextCollisionPoint().relativeTo(perception->myPosition()));
   rp.normalize();

   RealVec v(Util2D::perpendicularTo(rp, perception->nextCollider()->normalTo(*static_cast<Obstacle*>(perception->getMe()))));

#if 0
   // TODO: get rid of this dynamic_cast
   ObstacleSide* sPtr(dynamic_cast<ObstacleSide*>(perception->nextCollider()));
   if (sPtr)
   {
      RealVec const n(sPtr->normalTo(*static_cast<Obstacle*>(perception->getMe())));
      RealVec const b(sPtr->getBegin());
      RealVec const e(sPtr->getEnd());
      Real const db = b.relativeTo(perception->myPosition()).length();
      Real const de = e.relativeTo(perception->myPosition()).length();
      RealVec const b1(db < de ? b : e);
      RealVec const e1(db < de ? e : b);
      RealVec u(e1.relativeTo(b1));
      Real const alpha = perception->nextCollisionPoint().relativeTo(b1).length()/u.length();
      RealVec const n1(u.scale(alpha).add(n.scale(1.0-alpha)));
      // TODO: there are 2 perpendicular directions, use one closest to obstacle's normal
      v = Util2D::perpendicularTo(rp, n1.normalize());
      // RealVec v(Util2D::perpendicularTo(rp, perception->nextCollider()->normalTo(*static_cast<Obstacle*>(perception->getMe()))));
   }
#endif
   TG_ASSERT(MathUtil::isAlmostZero(v.dot(rp)));
#if 0
   Gui::setColor(Gui::getColorFromName("red"));
   v.scale(50.0);
   Gui::drawArrow(perception->myPosition(), v);
   v.normalize();
   // Gui::drawLineSegment(perception->myPosition(), perception->nextCollisionPoint());
   Gui::render(perception->getGameState());
   Gui::pause(10);
#endif
   action.setDesiredDirection(v);
   // TODO: modulate the speed based on time until collision and whatever the defaultControler
   // set it to.
   action.setDesiredSpeed(1);
}


