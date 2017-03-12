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

#include "ControllerRandomize.h"
#include "Util2D.h"

using namespace tagGame;

ControllerRandomize::ControllerRandomize(PerceptionPtr perception,
                                         ControllerPtr controller,
                                         PerceptReal const distance,
                                         Real const nearDistance,
                                         Real const farDistance) :
   Controller(perception),
   controller(controller),
   distance(distance),
   nearDistance(nearDistance),
   farDistance(farDistance)
{
}

ControllerRandomize::~ControllerRandomize()
{
}

void ControllerRandomize::calcAction()
{
   controller->calcAction();
   Action const a(controller->getAction());

   Real const d(((*perception).*(distance))()); // tr1::shared_ptr appears to have no ->* operator

   // Compute the distance as a fraction of "farDistance"
   Real const dFrac(std::min(Real(1), d/farDistance));

   Real const angle(Util2D::angle(a.getDesiredDirection()) + dFrac * Real(MathUtil::uniform(360) - 180));
   action.setDesiredDirection(Util2D::dir(angle));

#if 0
   // TODO: pass in desired distribution (and associated parameters) to the constructor
   // Add more variance when the tagged character is far away.
   Real const stdMax = Real(130);
   Real const std(std::min(stdMax, stdMax * d/farDistance));

   v = Util2D::normalDir(Util2D::angle(v), std);
#endif

   // TODO: consider randomizing speed too?  Or make separate randomizeDirection
   // and randomizeSpeed?
   action.setDesiredSpeed(a.getDesiredSpeed());
   TG_ASSERT(0 < action.getDesiredSpeed());
}
