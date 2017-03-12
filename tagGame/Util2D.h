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

#ifndef TG_UTIL2D_H
#define TG_UTIL2D_H

#include "Matrix.h"

namespace tagGame
{
   /// Some useful utilities for 2D vectors.
   class Util2D
   {
   public:
      static const size_t dim = 2;

      // TODO: inline some of these
      /// Return the two vectors perpendicular to v.
      static RealMatrix perpendicularTo(RealVec const& v);
      /// Return the vector perpendicular to v that is closest in direction to d.
      static RealVec perpendicularTo(RealVec const& v, RealVec const& d);
      static RealVec dir(Real const t);
      static RealVec uniformDir();
      static RealVec normalDir(Real const mean, Real const std);
      static Real angle(RealVec const& v);
      static RealMatrix rotationMatrix(Real const t);
      static RealVec randomPosition(RealVec const& worldDim);
      /// Computes points on circle and on tangent line of p to
      /// circle.
      static RealMatrix tagentLinePts(RealVec const& p, RealVec const& center, Real const radius);
      /// Computes points on circle that intersects with the line
      /// perpendicular to the line from p to center.
      static RealMatrix perpendicularLinePts(RealVec const& p, RealVec const& center, Real const radius);
   };
}

#endif
