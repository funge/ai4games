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

#include "Obstacle.h"
#include "Renderer.h"

using namespace tagGame;

using namespace std;

Obstacle::Obstacle(ShapePtr shape) :
#if !defined(TG_USE_TR1)
   renderer(NULL),
#endif
   shape(shape),
   speed(0),
   mass(Inf) // By default objects are too heavy to move
{
}

Obstacle::~Obstacle()
{
}

void Obstacle::render()
{
   if (renderer) { renderer->render(this); }
}

ostream& Obstacle::output(ostream& out) const
{
   shape->output(out);
   out << "mass: " << mass << endl;
   out << "speed: " << speed << endl;

   return out;
}

ostream& tagGame::operator<<(ostream& out, Obstacle const& o)
{
   return o.output(out);
}

