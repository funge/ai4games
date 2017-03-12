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

#include "ControllerConditional.h"
#include "Perception.h"

using namespace tagGame;

ControllerConditional::ControllerConditional(PerceptionPtr perception,
                                                 PerceptBool condition,
                                                 ControllerPtr controllerTrue,
                                                 ControllerPtr controllerFalse) :
   Controller(perception),
   condition(condition),
   controllerTrue(controllerTrue),
   controllerFalse(controllerFalse)
{
}

ControllerConditional::~ControllerConditional()
{
}

void ControllerConditional::calcAction()
{
   // TODO: explain how to re-factor the avoid controller using this conditional controller
   if (((*perception).*(condition))()) // tr1::shared_ptr appears to have no ->* operator
   {
      controllerTrue->calcAction();
      action = controllerTrue->getAction();
      return;
   }

   TG_ASSERT(!(((*perception).*(condition))())); // tr1::shared_ptr appears to have no ->* operator

   controllerFalse->calcAction();
   action = controllerFalse->getAction();
}


