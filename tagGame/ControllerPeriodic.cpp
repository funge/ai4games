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

#include "ControllerPeriodic.h"
#include "Perception.h"

using namespace tagGame;

ControllerPeriodic::ControllerPeriodic(PerceptionPtr perception,
                                       Real const period,
                                       ControllerPtr controller) :
   Controller(perception),
   timeOfLastDecision(-1),
   period(period),
   controller(controller)
{
}

ControllerPeriodic::~ControllerPeriodic()
{
}

// Consider making a periodic controller where the period varies according to
// some condition.  For example, according to the distance of the tagged character:
// Real const slope = Real(maxFreq - minFreq)/(tagNear - tagFar);
// Real const intercept = Real(maxFreq) + tagNear * slope;
// int const freq(MathUtil::clamp(MathUtil::round(tagDist * slope + intercept), minFreq, maxFreq));

void ControllerPeriodic::calcAction()
{
   Real const time = perception->getTime();
   // TODO: what happens when time wraps around?
   if (0 <= timeOfLastDecision && time - timeOfLastDecision < period) { return; }

   timeOfLastDecision = time;
   controller->calcAction();
   action = controller->getAction();
}

