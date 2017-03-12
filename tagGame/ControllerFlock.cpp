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

#include "ControllerFlock.h"
#include "Perception.h"

using namespace tagGame;

ControllerFlock::ControllerFlock(PerceptionPtr perception) :
   Controller(perception)
{
}

ControllerFlock::~ControllerFlock()
{
}

void ControllerFlock::calcAction()
{
   Util::error("not implemented");
}
