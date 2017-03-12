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

#ifndef TG_SIDE_H
#define TG_SIDE_H

#include "Shape.h"

namespace tagGame
{
   /// The sides of the world are a special kind of obstacle
   class Side : public Shape
   {
   public:
      // TODO: more arguments in constructor, ditto for circle obstacles
      Side();
      virtual ~Side();

      virtual std::ostream& output(std::ostream& out) const;

      inline void setNormal(RealVec const& normal);

      inline void setDistance(Real const distance);

      inline RealVec const& getNormal() const;

      inline Real getDistance() const;

      inline RealVec const& getBegin() const;
      inline RealVec const& getEnd() const;

      inline void setBegin(RealVec const& begin);
      inline void setEnd(RealVec const& end);

      virtual RealVec nearestIntersection(RealVec const& p, RealVec const& v) const;

      virtual RealVec normalTo(Shape const& o) const;
      virtual RealVec normalTo(Circle const& c) const;

      virtual Real distanceTo(Shape const& o) const;
      virtual Real distanceTo(Circle const& c) const;
      virtual Real distanceTo(Side const& s) const;

   protected:
   private:
      RealVec normal;
      Real distance;
      RealVec begin;
      RealVec end;
   };

   RealVec const& Side::getNormal() const
   {
      return normal;
   }

   Real Side::getDistance() const
   {
      return distance;
   }

   RealVec const& Side::getBegin() const
   {
      return begin;
   }

   RealVec const& Side::getEnd() const
   {
      return end;
   }

   void Side::setNormal(RealVec const& normal)
   {
      // TG_ASSERT_MSG(1 == normal.length() && 2 == normal.size() && (normal[0] = 0 || normal[2] = 0),
      //              string("Only 2D axis aligned side obstacles are currently supported"));
      this->normal = normal;
   }

   void Side::setDistance(Real const distance)
   {
      this->distance = distance;
   }

   void Side::setBegin(RealVec const& begin)
   {
      this->begin = begin;
   }

   void Side::setEnd(RealVec const& end)
   {
      this->end = end;
   }
}

#endif
