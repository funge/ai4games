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

#include "ControllerEvade.h"
#include "Perception.h"
#include "Gui.h"
#include "Timer.h"
#include "Util2D.h"

using namespace tagGame;

ControllerEvade::ControllerEvade(PerceptionPtr perception) :
   Controller(perception)
{
}

ControllerEvade::~ControllerEvade()
{
}

// TODO: Paramterize whole controller with which character to evade.  For example,
// with a percept like the conditional controller.
void ControllerEvade::calcAction()
{
   RealVec v(perception->myPosition().relativeTo(perception->taggedPosition()));

   // Following assert would fail if I am tagged character, i.e. can't evade myself!
   // TODO: necessary?
   TG_ASSERT(!MathUtil::isAlmostZero(v.length()));

   // TODO: consider predicating on v.length() e.g. inversely proportional so
   // that speed increases as tagged character gets closer
   // std::max(Real(0), std::min(Real(1), Real(1) - (Real(0.25)*tagDist)/tagFar));
   action.setDesiredSpeed(Real(1));
   action.setDesiredDirection(v.normalize());
}
