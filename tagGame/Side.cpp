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

#include "Side.h"
#include "Circle.h"
#include "Util2D.h"

using namespace tagGame;

using namespace std;

// TODO: pass normal and distance into constructor (analogously for circle)
Side::Side() :
   Shape(),
   normal(Util2D::dim),
   distance(Real(0))
{
   // TODO: setPosition to something appropriate
}

Side::~Side()
{
}

ostream& Side::output(ostream& out) const
{
   out << "normal: " << getNormal() << endl;
   out << "distance: " << getDistance() << endl;

   return out;
}

RealVec Side::nearestIntersection(RealVec const& p, RealVec const& v) const
{
   RealVec u(end.relativeTo(begin));
   RealVec r(Util2D::dim);

   // Following code assumes 2D.
   TG_ASSERT(2 == Util2D::dim);

   // TODO: turn collision detection for sides back on by deleting next 2 lines
   r.set(Inf);
   return r;

   Real const d = v[1] * u[0] - v[0] * u[1];
   // The two lines are parallel.
   if (MathUtil::isAlmostZero(d))
   {
      r.set(Inf);
      return r;
   }

   Real const s = (v[0] * (begin[1] - p[1]) - v[1] * (begin[0] - p[0])) / d;
   // Intersection point is not on the line segment between begin and end.
   if (s < 0 || 1 < s)
   {
      r.set(Inf);
      return r;
   }

   Real const t = (u[0] * (begin[1] - p[1]) - u[1] * (begin[0] - p[0])) / d;

   // Intersection point is behind p.
   if (t < 0)
   {
      r.set(Inf);
      return r;
   }

   r = u;
   r.scale(s);
   r.add(begin);

   return r;
}

RealVec Side::normalTo(Shape const& o) const
{
   return normal;
}

RealVec Side::normalTo(Circle const& o) const
{  
   return normal;
}  

Real Side::distanceTo(Shape const& o) const
{
   return o.distanceTo(*this);
}

Real Side::distanceTo(Circle const& c) const
{
   return Inf; // TODO: delete this line to turn collisions with sides back on

   Real const d = normal.dot(c.getPosition()) - distance;

   return d < 0 ? d + c.getRadius() : d - c.getRadius();
}

Real Side::distanceTo(Side const& s) const
{
   Util::error("Side::distanceTo not implemented for side obstacles");

   return 0;
}


