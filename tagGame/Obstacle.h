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

#ifndef TG_OBSTACLE_H
#define TG_OBSTACLE_H

#include "Vec.h"
#include "Shape.h"

namespace tagGame
{
   class Renderer;
   class Obstacle;

   typedef SharedPtr<Renderer>::type RendererPtr;
   typedef SharedPtr<Obstacle>::type ObstaclePtr;

   /// Common base class for all obstacles.
   class Obstacle
   {
   public:
      Obstacle(ShapePtr shape);
      virtual ~Obstacle();

      inline void setRenderer(function<void (Obstacle*)> renderer);

      inline void setRenderer(RendererPtr renderer);
      inline RendererPtr getRenderer();

      inline Shape const& getShape() const;

      inline RealVec const& getPosition() const;
      inline void setPosition(RealVec const& position);
      inline Real getSpeed() const;
      inline void setSpeed(Real const Speed);
      inline Real const& getMass() const;
      inline void setMass(Real const mass);

      inline RealVec getVelocity() const;
      inline void setVelocity(RealVec const& velocity);

      inline RealVec const& getOrientation() const;
      inline void setOrientation(RealVec const& orientation);

      void render();

      virtual std::ostream& output(std::ostream& out) const;

      inline bool isTouching(Obstacle const& o) const;
      inline bool isColliding(Obstacle const& o) const;

      /// Calculate the nearest intersection point of a line in the
      /// direction v from the point p.
      inline RealVec nearestIntersection(RealVec const& p, RealVec const& v) const;

      /// Return a vector that is normal to o, with respect to this.
      inline RealVec normalTo(Obstacle const& o) const;

      inline Real distanceTo(Obstacle const& o) const;

      inline Real distanceSquaredTo(Obstacle const& o) const;

   protected:
      RendererPtr renderer;

   private:
      ShapePtr shape;
      Real speed;
      Real mass;
   };

   typedef std::vector<ObstaclePtr> ObstacleList;
   typedef ObstacleList::const_iterator ObstacleIteratorConst;
   typedef ObstacleList::iterator ObstacleIterator;

   std::ostream& operator<<(std::ostream& out, Obstacle const& o);

   RealVec const& Obstacle::getPosition() const
   {
      return shape->getPosition();
   }

   void Obstacle::setPosition(RealVec const& position)
   {
      shape->setPosition(position);
   }

   void Obstacle::setVelocity(RealVec const& velocity)
   {
      RealVec v(velocity);
      Real const s = v.length();
      if (MathUtil::isAlmostZero(s))
      {
         setSpeed(0);
         // Don't change the orientation if the speed is zero.
      }
      else
      {
         setSpeed(s);
         setOrientation(v.normalize());
      }
   }

   RealVec Obstacle::getVelocity() const
   {
      // TODO: cache v in a class variable and invalidate as appropriate.
      // Then make this return a const reference (remember to change the
      // corresponding percept too).
      RealVec v(shape->getOrientation());
      return v.scale(getSpeed());
   }

   Real Obstacle::getSpeed() const
   {
      return speed;
   }

   void Obstacle::setSpeed(Real const speed)
   {
      TG_ASSERT(mass < Inf); // Infinitely heavy object can't move
      this->speed = speed;
   }

   Real const& Obstacle::getMass() const
   {
      return mass;
   }

   void Obstacle::setMass(Real const mass)
   {
      this->mass = mass;
   }

   RealVec const& Obstacle::getOrientation() const
   {
      return shape->getOrientation();
   }

   void Obstacle::setOrientation(RealVec const& orientation)
   {
      TG_ASSERT(MathUtil::isAlmostEq(1, orientation.length()));

      shape->setOrientation(orientation);
   }

   bool Obstacle::isTouching(Obstacle const& o) const
   {
      return shape->isTouching(*o.shape);
   }

   bool Obstacle::isColliding(Obstacle const& o) const
   {
      RealVec const& v0(getVelocity());
      RealVec const& v1(o.getVelocity());
      RealVec const n(normalTo(o));

      return isTouching(o) && v0.dot(n) > v1.dot(n);
   }

   RealVec Obstacle::nearestIntersection(RealVec const& p, RealVec const& v) const
   {
      return shape->nearestIntersection(p, v);
   }

   RealVec Obstacle::normalTo(Obstacle const& o) const
   {
      return shape->normalTo(*o.shape);
   }

   Real Obstacle::distanceTo(Obstacle const& o) const
   {
      return shape->distanceTo(*o.shape);
   }

   Real Obstacle::distanceSquaredTo(Obstacle const& o) const
   {
      return shape->distanceSquaredTo(*o.shape);
   }

   void Obstacle::setRenderer(RendererPtr renderer)
   {
      // Not all shapes need renderers
      if (renderer) { this->renderer = renderer; }
   }

   Shape const& Obstacle::getShape() const
   {
      return *shape;
   }

   RendererPtr Obstacle::getRenderer()
   {
      return renderer;
   }
}

#endif
