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

#include "CharacterRenderer.h"
#include "Character.h"
#include "GameState.h"
#include "Gui.h"
#include "Circle.h"

using namespace tagGame;

CharacterRenderer::CharacterRenderer() :
   CircleRenderer()
{
}

CharacterRenderer::~CharacterRenderer()
{
}

void CharacterRenderer::render(Obstacle const* o)
{
   Character const* c(static_cast<Character const*>(o));

   if (c->getIsTagged()) { flashingOn(); }
   else { flashingOff(); }

   CircleRenderer::render(o);

   // return;

   RealVec start(o->getPosition());
   RealVec v(o->getOrientation());
   v.scale(static_cast<Circle const&>(c->getShape()).getRadius());

   start.add(v);
   v = o->getOrientation();
   v.scale(1.5 * static_cast<Circle const&>(c->getShape()).getRadius() * (c->getSpeed()/c->getMaxSpeed()));
   Gui::drawArrow(start, v);
}
