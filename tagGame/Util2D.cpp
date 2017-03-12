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

#include "Util2D.h"

using namespace tagGame;

RealMatrix Util2D::perpendicularTo(RealVec const& v)
{
   // TODO: add more asserts of this nature
   TG_ASSERT(dim == v.size());
   RealVec n0(dim);
   n0[0] = v[1];
   n0[1] = -v[0];

   RealVec n1(dim);
   n1[0] = -v[1];
   n1[1] = v[0];

   RealMatrix pts(dim, dim);
   pts.setRow(0, n0);
   pts.setRow(1, n1);

   return pts;
}

RealVec Util2D::perpendicularTo(RealVec const& v, RealVec const& d)
{
   TG_ASSERT(MathUtil::isAlmostEq(1,v.length()));
   TG_ASSERT(MathUtil::isAlmostEq(1,d.length()));

   RealMatrix m(perpendicularTo(v));
   Real const cosA = d.dot(m.getRow(0));
   // Real const cosB = d.dot(m.getRow(1));

   if (MathUtil::isAlmostZero(cosA)) { return m.getRow(0); }

   // Pick the one with non-zero component in the d direction.
   // Since row 1 and row 2 are 180 degrees apart, this should be unambiguous.
   return 0 < cosA ? m.getRow(0) : m.getRow(1);
}

RealVec Util2D::dir(Real const t)
{
   RealVec v(dim);
   Real const tr = MathUtil::degToRad(t);
   v[0] = cos(tr);
   v[1] = sin(tr);

   return v;
}

RealVec Util2D::uniformDir()
{
   return dir(MathUtil::uniform01() * Real(360) - Real(180));
}

RealVec Util2D::normalDir(Real const mean, Real const std)
{
   return dir(MathUtil::normalAngle(mean, std));
}

Real Util2D::angle(RealVec const& v)
{
   TG_ASSERT(dim == v.size());

   RealVec u(v);
   u.normalize();
   return MathUtil::radToDeg(atan2(u[1], u[0]));
}

RealMatrix Util2D::rotationMatrix(Real const t)
{
   RealMatrix m(dim, dim);
   m[0][0] = cos(t); m[0][1] = -sin(t);
   m[1][0] = sin(t); m[1][1] = cos(t);

   return m;
}

RealVec Util2D::randomPosition(RealVec const& worldDim)
{
   RealVec p(dim);

   p.randomize();
   p.scale(worldDim);

   return p;
}

RealMatrix Util2D::tagentLinePts(RealVec const& p, RealVec const& center, Real const radius)
{
   RealVec v(center.relativeTo(p));
   Real const d = v.length();

   TG_ASSERT_MSG(d < radius, "tangentLinePts: point is inside circle");

   Real const alpha = atan2(v[1],v[0]);
   Real const theta = asin(radius/d);
   Real const beta1 = alpha + theta;
   Real const beta2 = alpha - theta;
   Real const h = sqrt(d * d - radius * radius);

   RealVec q0(dim);
   q0[0] = cos(beta1);
   q0[1] = sin(beta1);
   q0.scale(h);
   q0.add(p);

   RealVec q1(dim);
   q1[0] = cos(beta2);
   q1[1] = sin(beta2);
   q1.scale(h);
   q1.add(p);

   RealMatrix pts(dim, dim);
   pts.setRow(0, q0);
   pts.setRow(1, q1);

   return pts;
}

RealMatrix Util2D::perpendicularLinePts(RealVec const& p, RealVec const& center, Real const radius)
{
   RealVec v(center.relativeTo(p));

   Real const alpha = atan2(v[1], v[0]);

   RealVec q0(dim);
   q0[0] = cos(alpha + M_PI_2);
   q0[1] = sin(alpha + M_PI_2);
   q0.add(center);

   RealVec q1(dim);
   q1[0] = cos(alpha - M_PI_2);
   q1[1] = sin(alpha - M_PI_2);
   q1.add(center);

   RealMatrix pts(dim, dim);
   pts.setRow(0, q0);
   pts.setRow(1, q1);

   return pts;
}

