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

#include "CircleRenderer.h"
#include "Circle.h"
#include "GameState.h"
#include "Gui.h"

using namespace tagGame;

CircleRenderer::CircleRenderer() :
   RendererColor()
{
}

CircleRenderer::~CircleRenderer()
{
}

void CircleRenderer::render(Obstacle const* o)
{
   RendererColor::render(o);

   RealVec const& p(o->getPosition());
   RealVec const& v(o->getOrientation());
   Real const r = static_cast<Circle const&>(o->getShape()).getRadius();

   Gui::drawCircle(p, v, r);
}
