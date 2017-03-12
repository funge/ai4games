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

#ifndef TG_SHAPE_H
#define TG_SHAPE_H

#include "Util2D.h"

namespace tagGame
{
   class Circle;
   class Side;
   class Shape;

   typedef SharedPtr<Circle>::type CirclePtr;
   typedef SharedPtr<Side>::type SidePtr;
   typedef SharedPtr<Shape>::type ShapePtr;

   template<typename Function, typename Allocator = std::allocator<void> >
   class function;

   /// Common base class for all obstacles.
   class Shape
   {
   public:
      inline Shape();
      inline virtual ~Shape();

      inline RealVec const& getPosition() const;
      inline void setPosition(RealVec const& position);

      inline RealVec const& getOrientation() const;
      inline void setOrientation(RealVec const& orientation);

      virtual std::ostream& output(std::ostream& out) const = 0;

      inline bool isTouching(Shape const& o) const;

      /// Calculate the nearest intersection point of a line in the
      /// direction v from the point p.
      virtual RealVec nearestIntersection(RealVec const& p, RealVec const& v) const = 0;

      /// Return a vector that is normal to o, with respect to this.
      virtual RealVec normalTo(Shape const& o) const = 0;
      virtual RealVec normalTo(Circle const& c) const = 0;

      // Multiple dispatch is implemented using virtual functions
      // only, as described in "Item 31: Making functions virtual with
      // respect to more than one object" in "More Effective C++" by
      // Scott Meyers.  More sophisticated techniques are described in
      // the reference and also in the "Multimethods" chapter of
      // "Modern C++ Design" by Andrei Alexandrescu.
      virtual Real distanceTo(Shape const& o) const = 0;
      virtual Real distanceTo(Circle const& c) const = 0;
      virtual Real distanceTo(Side const& s) const = 0;

      inline Real distanceSquaredTo(Shape const& o) const;

   protected:
   private:
      RealVec position;
      RealVec orientation;
   };

   typedef std::vector<ShapePtr> ShapeList;
   typedef ShapeList::const_iterator ShapeIteratorConst;
   typedef ShapeList::iterator ShapeIterator;

   Shape::Shape() :
      position(Util2D::dim),
      orientation(Util2D::dim)
   {
      orientation[0] = 1;
   }

   Shape::~Shape()
   {
   }

   inline std::ostream& operator<<(std::ostream& out, Shape const& o)
   {
      return o.output(out);
   }

   RealVec const& Shape::getPosition() const
   {
      return position;
   }

   void Shape::setPosition(RealVec const& position)
   {
      this->position = position;
   }

   RealVec const& Shape::getOrientation() const
   {
      return orientation;
   }

   void Shape::setOrientation(RealVec const& orientation)
   {
      TG_ASSERT(MathUtil::isAlmostEq(1, orientation.length()));

      this->orientation = orientation;
   }

   bool Shape::isTouching(Shape const& o) const
   {
      return distanceTo(o) <= Real(0);
   }

   // TODO: re-implement distanceTo in terms of distanceSquaredTo (instead
   // of the other way around) so that
   // distanceSquaredTo avoids the square root and can be used whenever
   // possible in place of distanceTo.
   Real Shape::distanceSquaredTo(Shape const& o) const
   {
      Real const d(distanceTo(o));

      return d * d;
   }

}

#endif
