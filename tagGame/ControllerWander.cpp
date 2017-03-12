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

#include "ControllerWander.h"
#include "Perception.h"
#include "Util2D.h"

using namespace tagGame;

ControllerWander::ControllerWander(PerceptionPtr perception) :
   Controller(perception)
{
}

ControllerWander::~ControllerWander()
{
}

void ControllerWander::calcAction()
{
   action.setDesiredDirection(Util2D::uniformDir());
   // Speed is clamped to at least 0.25 because slow movement is boring!
   action.setDesiredSpeed(MathUtil::clamp(MathUtil::uniform01(), 0.25, 1));
}

