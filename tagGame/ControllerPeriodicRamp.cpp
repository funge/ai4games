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

#include "ControllerPeriodicRamp.h"
#include "Perception.h"

using namespace tagGame;

// TODO: consider re-implementing ControllerPeriodic in terms of
// ControllerPeriodicRamp
ControllerPeriodicRamp::ControllerPeriodicRamp(PerceptionPtr perception, 
                                               ControllerPtr controller,
                                               PerceptReal distance,
                                               Real const nearDistance,
                                               Real const farDistance,
                                               Real const minPeriod,
                                               Real const maxPeriod) :
   Controller(perception), 
   controller(controller),
   distance(distance), 
   nearDistance(nearDistance),
   farDistance(farDistance),
   minPeriod(minPeriod),
   maxPeriod(maxPeriod),
   timeOfLastDecision(-1)
{
}

ControllerPeriodicRamp::~ControllerPeriodicRamp()
{
}

void ControllerPeriodicRamp::calcAction()
{
   Real const time = perception->getTime();

   Real const periodUnclamped = (Real(maxPeriod)/farDistance) * ((*perception).*(distance))(); // tr1::shared_ptr appears to have no ->* operator
   Real const period = MathUtil::clamp(periodUnclamped, minPeriod, maxPeriod);

#if 0
   Real const d = (perception->*(distance))();

   Real const slope = Real(maxPeriod - minPeriod)/(nearDistance - farDistance);
   Real const intercept = Real(maxPeriod) + nearDistance * slope;
   Real const period = MathUtil::clamp(d * slope + intercept, minPeriod, maxPeriod);
#endif
   
   // TODO: what happens when time wraps around?
   if (0 <= timeOfLastDecision && time - timeOfLastDecision < period) { return; }

   timeOfLastDecision = time;
   controller->calcAction();
   action = controller->getAction();
}

