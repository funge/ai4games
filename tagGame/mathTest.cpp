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

using namespace std;

IntVec intScaleBy2(IntVec const& v)
{
   IntVec u(v);
   return u.scale(2);
}

void mathTestInt()
{
   IntVec u(2);
   u[0] = 3;
   u[1] = 4;

   TG_ASSERT(25 == u.squaredLength());
   TG_ASSERT(5 == int(u.length()));

   vector<int> data(2);
   data[0] = 6;
   data[1] = 8;
   IntVec v(data);

   TG_ASSERT(2 == v.size());
   TG_ASSERT(data == static_cast< vector<int>& >(v));

   IntVec w(intScaleBy2(u));
   TG_ASSERT(v == w);
   TG_ASSERT(3 == u[0] && 4 == u[1]);
   w = u;
   w.scale(2);
   TG_ASSERT(v == w);
   TG_ASSERT(3 == u[0] && 4 == u[1]);
   u.scale(2);
   TG_ASSERT(v == u);

   v.add(u);
   v.subtract(w);
   TG_ASSERT(v == u);

   v.scale(u);
   TG_ASSERT(36 == v[0] && 64 == v[1]);

   // Makes no sense for IntVec
   v.normalize();
   TG_ASSERT(v.isAlmostZero());

   // Doesn't currently work for IntVec
   // v.randomize();

   v[1] = 8;

   while (0 == v[0] && 8 == v[1])
   {
      v.shuffle();
   }
   v.scale(-1);

   TG_ASSERT(-8 == v.minElement());
   TG_ASSERT(0 == v.maxElement());

   v.scale(-2);
   TG_ASSERT(1 == v.argMin());
   TG_ASSERT(0 == v.argMax());

   u[0] = 6;
   u[1] = 8;
   u.clampMaxLength(80);
   TG_ASSERT(6 == u[0] && 8 == u[1]);

   u.setLength(5);

   // doesn't work for IntVec
   TG_ASSERT(u.isAlmostZero());

   v[0] = -180;
   v[1] = 200;
   u[0] = 50;
   u[1] = 100;
   v.wrap(u);

   TG_ASSERT(20 == v[0] && 100 == v[1]);
}

void mathTestReal()
{
   RealVec u(2);
   u[0] = 3.0;
   u[1] = 4.0;

   TG_ASSERT(25.0 == u.squaredLength());
   TG_ASSERT(5.0 == u.length());

   vector<Real> data(2);
   data[0] = 6.0;
   data[1] = 8.0;
   RealVec v(data);

   TG_ASSERT(2 == v.size());
   TG_ASSERT(data == static_cast< vector<Real>& >(v));

   RealVec w(u);
   w.scale(2.0);
   TG_ASSERT(v == w);
   TG_ASSERT(3.0 == u[0] && 4.0 == u[1]);
   u.scale(2.0);
   TG_ASSERT(v == u);

   v.add(u);
   v.subtract(w);
   TG_ASSERT(v == u);

   v.scale(u);
   TG_ASSERT(36.0 == v[0] && 64.0 == v[1]);

   v.normalize();
   TG_ASSERT(MathUtil::isAlmostEq(1.0, v.length()));

   v.randomize();

   u = v;

   while (u == v)
   {
      v.shuffle();
   }

   v.scale(-1);

   v[0] = 0.0;
   v[1] = -8.0;
   TG_ASSERT(-8.0 == v.minElement());
   TG_ASSERT(0.0 == v.maxElement());

   v.scale(-2.0);
   TG_ASSERT(0 == v.argMin());
   TG_ASSERT(1 == v.argMax());

   u[0] = 6.0;
   u[1] = 8.0;
   u.clampMaxLength(80);
   TG_ASSERT(6.0 == u[0] && 8.0 == u[1]);

   u.setLength(5.0);

   TG_ASSERT(3.0 == u[0] && 4.0 == u[1]);

   v[0] = -180.0;
   v[1] = 200.0;
   u[0] = 50.0;
   u[1] = 100.0;
   v.wrap(u);

   TG_ASSERT(20.0 == v[0] && 100.0 == v[1]);

   v[0] = 4.0;
   v[1] = 4.0;
   TG_ASSERT(MathUtil::isAlmostEq(45.0, Util2D::angle(v)));
   TG_ASSERT(MathUtil::isAlmostEq(1.0, Util2D::uniformDir().length()));

   v[0] = 1.0;
   v[1] = 0;
   u.set(1);
   u.normalize();
   RealVec a(Util2D::perpendicularTo(v, u));
   TG_ASSERT(0 == a[0] && 1 == a[1]);
}

void mathTestStats()
{
   // TODO: proper statistical tests, this just writes out a string that
   // can be used to easily create a plot in octave for visual inspection
   IntVec angles(360);
   fill(angles.begin(), angles.end(), 0);

   for (size_t i = 0; i < 100000; i++)
   {
      int const angle(int(Real(180) + MathUtil::normalAngle(0, 30)));
      TG_ASSERT_MSG(0 <= angle && angle <= 360, "angle: " + Util::itos(angle));
      angles[angle]++;
   }
   cout << "v = [ " << angles << "];\n";
   cout << "plot(v, \"^\")\n";

   fill(angles.begin(), angles.end(), 0);

   for (size_t i = 0; i < 100000; i++)
   {
      int const angle(int(Real(180) + Util2D::angle(Util2D::normalDir(0, 30))));
      TG_ASSERT_MSG(0 <= angle && angle <= 360, "angle: " + Util::itos(angle));
      angles[angle]++;
   }
   cout << "v = [ " << angles << "];\n";
   cout << "plot(v, \"^\")\n";
}

int main(int argc, char** argv)
{
   mathTestInt();

   mathTestReal();

   mathTestStats();

   exit(EXIT_SUCCESS);
}

