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

#ifndef TG_CIRCLE_H
#define TG_CIRCLE_H

#include "Shape.h"

namespace tagGame
{
   /// Common base class for all circular obstacles.
   class Circle : public Shape
   {
   public:
      Circle();

      virtual std::ostream& output(std::ostream& out) const;

      inline Real getRadius() const;
      inline void setRadius(Real const radius);

      virtual RealVec nearestIntersection(RealVec const& p, RealVec const& v) const;

      virtual RealVec normalTo(Shape const& o) const;
      virtual RealVec normalTo(Circle const& c) const;

      virtual Real distanceTo(Shape const& o) const;
      virtual Real distanceTo(Circle const& c) const;
      virtual Real distanceTo(Side const& s) const;

   protected:
   private:
      Real radius;
   };

   Real Circle::getRadius() const
   {
      return radius;
   }
   
   void Circle::setRadius(Real const radius)
   {
      this->radius = radius;
   }
}

#endif
