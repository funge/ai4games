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

#ifndef TG_MATH_H
#define TG_MATH_H

#include "Util.h"

#include <cmath>

// Not defined on all supported architectures.
#ifndef M_PI
#   define M_PI         3.14159265358979323846
#endif
#ifndef M_PI_2
#   define M_PI_2       1.57079632679489661923
#endif

namespace tagGame
{
   // Re-define this to float if you don't need doubles.
   typedef double Real;

   Real const Inf = HUGE_VAL;

   /// Some basic math related utility functions. 
   class MathUtil
   {
   public:

      /// True iff x is within eps of y.
      inline static bool isAlmostEq(Real const x, Real const y);

      /// True iff x is within eps of zero.
      inline static bool isAlmostZero(Real const x);

      /// Round x to the nearest integer value.
      inline static int round(Real const x);

      /// Return the sign of x.
      inline static int sgn(Real const x);

      /// Return t in degrees.
      inline static Real radToDeg(Real const t);

      /// Return t in radians.
      inline static Real degToRad(Real const t);

      /// Clamp x to the closed range [lower, upper].
      inline static Real clamp(Real const x, Real lower, Real upper);

      /// Clamp the angle t to the half-open range [-180, 180).
      /// The range is half-open because the angle -180 is the same as the
      /// angle 180 and we only want one representation for an angle.
      inline static Real angleClamp(Real const t);

      /// Uniformly pick a Real in the range [0, 1].
      inline static Real uniform01();

      /// Uniformly pick an integer in the range [0, n).
      inline static int uniform(int n);

      /// Pick a Real according to the normal distribution with mean and standard
      /// deviation as provided.
      inline static Real normal(Real const mean = Real(0), Real const std = Real(1));

      /// Pick an angle (in degrees) according to an approximate normal distribution.
      /// The normal distribution is only approximate because there is only finite support
      /// i.e. return value \in [-180,180].  But provided the std is less than about 70 degrees,
      /// then less than 1% of the probability mass would lie outside that range anyway.
      inline static Real normalAngle(Real const mean = Real(0), Real const std = Real(70));

   protected:
   private:
   };

   // TODO: make this relative
   bool MathUtil::isAlmostEq(Real const x, Real const y)
   {
      Real const eps = 0.00001;
   
      return (fabs(x - y) <= eps) || (x == Inf && y == Inf);
   }
   
   bool MathUtil::isAlmostZero(Real const x)
   {
      return isAlmostEq(x, Real(0));
   }
   
   int MathUtil::round(Real const x)
   {
      return int(x + 0.5);
   }
   
   int MathUtil::sgn(Real const x)
   {
      return x < 0 ? -1 : 1;
   }
   
   Real MathUtil::radToDeg(Real const x)
   {
      return x * Real(180) / M_PI;
   }
   
   Real MathUtil::degToRad(Real const x)
   {
      return x * M_PI / Real(180);
   }
   
   Real MathUtil::uniform01()
   {
      // TODO: use a better random number generator.
      return Real(rand())/Real(RAND_MAX);
   }
   
   int MathUtil::uniform(int n)
   {
      TG_ASSERT_MSG(n <= RAND_MAX, "n: " + Util::itos(n) + " must be <= RAND_MAX: " + Util::itos(RAND_MAX));
      // TODO: use a better random number generator.
      return rand() % n;
   }
   
   Real MathUtil::clamp(Real x, Real lower, Real upper)
   {
      TG_ASSERT(lower <= upper);
   
      return x < lower ? lower : (upper < x ? upper : x);
   }
   
   Real MathUtil::angleClamp(Real const t)
   {
      // The test for exact equality with -360 is a small technicality.  If it weren't
      // there, then all angles would be clamped into the open range (-180,180), instead
      // of the desired half-open range [-180, 180).
      Real const x(t == Real(-360) ? t : Real(sgn(t)) * fmod(fabs(t), Real(360)));
      TG_ASSERT(Real(-360) <= x && x < Real(360));
      return x < Real(-180) ? x + Real(360) : (x >= Real(180) ? x - Real(360) : x);
   }
   
   Real MathUtil::normalAngle(Real const mean, Real const std)
   {
      return angleClamp(normal(mean, std));
   }

   // draw number from a normal random distribution
   Real MathUtil::normal(Real const mean, Real const std)
   {
      // For an explanation of the theory behind this code see:
      // Eric W. Weisstein. "Box-Muller Transformation." From MathWorld--A Wolfram Web Resource.
      // http://mathworld.wolfram.com/Box-MullerTransformation.html

      static bool validCache(false);
      static Real rho(0);
      static Real r1(0);
      // Real const pi(3.14159265358979323846);

      if (!validCache)
      {
         Real const r0(uniform01());
         r1 = uniform01();
         rho = sqrt(-Real(2) * log(Real(1) - r0));
         validCache = true;

         return rho * cos(Real(2) * M_PI * r1) * std + mean;
      }
      else
      {
         validCache = false;
      }
      return rho * sin(Real(2) * M_PI * r1) * std + mean;
   }
}

#endif
