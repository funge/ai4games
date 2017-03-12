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

#include "Action.h"
#include "Util2D.h"

using namespace tagGame;

using namespace std;

Action::Action() :
   direction(Util2D::dim),
   speed(Real(0))
{
   // Head in direction (1, 0) to start with
   direction[0] = Real(1);
}

Action::Action(Action const& a)
{
   *this = a;
}

Action& Action::operator=(Action const& a)
{
   if (this != &a)
   {
      direction = a.direction;
      speed = a.speed;
   }
   return *this;
}

ostream& Action::output(ostream& out) const
{
   out << "(" << direction << ") * " << speed;
   return out;
}

ostream& tagGame::operator<<(ostream& out, Action const& a)
{
   return a.output(out);
}


