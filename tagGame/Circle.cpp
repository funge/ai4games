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

#include "Circle.h"
#include "Side.h"
#include "Util2D.h"

using namespace tagGame;

using namespace std;

Circle::Circle() :
   Shape(),
   radius(10.0)
{
}

ostream& Circle::output(ostream& out) const
{
   out << "center: " << getPosition() << endl;
   out << "radius: " << getRadius() << endl;

   return out;
}

Real Circle::distanceTo(Shape const& o) const
{
   return o.distanceTo(*this);
}

Real Circle::distanceTo(Circle const& c) const
{
   return (getPosition().relativeTo(c.getPosition())).length() - getRadius() - c.getRadius();
}

Real Circle::distanceTo(Side const& s) const
{
   return s.distanceTo(*this);
}

// TODO: What we really want is the future intersection point of
// another circle.  This could be done by temporarily adding the other
// circle's radius to this and intersecting with a line as below.
// Then projecting the intersection point back onto this.  An
// analogous trick could be done when intersecting with a side object.
RealVec Circle::nearestIntersection(RealVec const& p, RealVec const& v) const
{
   TG_ASSERT(MathUtil::isAlmostEq(v.length(), 1));

   RealVec const rp = p.relativeTo(getPosition());
   Real const k0 = rp.squaredLength() - getRadius() * getRadius();
   Real const k1 = v.dot(rp);

   vector<Real> roots;
   Real const k = k1 * k1 - k0;
   if (MathUtil::isAlmostZero(k))
   {
      roots.push_back(-k1);
   }
   else if (0 < k)
   {
      Real const kSqrt = sqrt(k);
      roots.push_back(-k1 - kSqrt);
      roots.push_back(-k1 + kSqrt);
      TG_ASSERT(roots[0] < roots[1]);
   }

   RealVec q(Util2D::dim);
   // This code assumes 2D.
   TG_ASSERT(2 == Util2D::dim);
   q.set(Inf);

   for (size_t i = 0; i < roots.size(); i++)
   {
      if (MathUtil::isAlmostZero(roots[i]) || 0 < roots[i])
      {
         q = v;
         q.scale(roots[i]);
         q.add(p);
         break;
      }
   }

   return q;
}

RealVec Circle::normalTo(Shape const& o) const
{
   return o.normalTo(static_cast<Circle const&>(*this)).scale(-1);
}

RealVec Circle::normalTo(Circle const& c) const
{
   return (c.getPosition().relativeTo(getPosition())).normalize();
}

