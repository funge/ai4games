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

#include "Perception.h"
#include "Util2D.h"

using namespace tagGame;

using namespace std;

Perception::Perception(GameState* gs) :
   gs(gs),
   me(NULL),
   tagged(NULL),
   objectCache(objectCacheSize)
{
   fill(objectCache.begin(),objectCache.end(), static_cast<Obstacle*>(NULL));
}

Perception::~Perception()
{}

Character const* Perception::whoLastTaggedMe() const
{
   map<Character*,Character*>::const_iterator i(lastTaggedByList.find(me));

   if (i != lastTaggedByList.end())
   {
      return i->second;
   }
   return NULL;
}

int Perception::myRecentTaggedCount() const
{
   Util::error("not implemented");
   return 1;
}

bool Perception::myselfRecentlyTagged() const
{
   Util::error("not implemented");
   return false;
}

Character* Perception::nearestCharacter() const
{
   // If the previous calculation of nearestCharacter is still valid, return the
   // cached value.
   if (objectCache[nearestCharacterCache])
   {
      return static_cast<Character*>(objectCache[nearestCharacterCache]);
   }

   Character* who(NULL);
   Real dMin = Inf;
   for (CharacterIterator i = gs->getCharacterListBegin(); i != gs->getCharacterListEnd(); i++)
   {
      if (me == &**i) { continue; } // Don't include me!

      // TODO: use squaredDistanceTo instead
      Real const d = distanceTo(**i);
      if (d < dMin)
      {
         dMin = d;
         who = &**i;
      }
   }
   TG_ASSERT(who);
   // Computing the nearest character is expensive so cache the result in case
   // it's needed again.
   // TODO: Could also be worth caching dMin as the distanceToNearestCharacter.
   objectCache[nearestCharacterCache] = who;
   return who;
}

// TODO: factor out common code from nearestObstacle, nearestCharacter, etc.
Obstacle* Perception::nearestObstacle() const
{
   // If the previous calculation of nearestCharacter is still valid, return the
   // cached value.
   if (objectCache[nearestObstacleCache])
   {
      return static_cast<Obstacle*>(objectCache[nearestObstacleCache]);
   }

   Obstacle* which(NULL);
   Real dMin = Inf;
   for (ObstacleIterator i = gs->getObstacleListBegin(); i != gs->getObstacleListEnd(); i++)
   {
      // TODO: cast needed for me?
      if (me == &**i) { continue; } // Don't include me!

      // TODO: use squaredDistanceTo instead
      Real const d = distanceTo(**i);
      if (d < dMin)
      {
         dMin = d;
         which = &**i;
      }
   }
   // TODO: support no obstacles?
   TG_ASSERT(which);
   // Computing the nearest character is expensive so cache the result
   // in case it's needed again.

   // TODO: Could also be worth caching dMin as the
   // distanceToNearestCharacter.

   objectCache[nearestObstacleCache] = which;
   return which;
}

RealVec Perception::nextCollisionPoint() const
{
   if (!objectCache[nextColliderCache])
   {
      nextCollider();
   }

   if (!objectCache[nextColliderCache])
   {
      RealVec p(Util2D::dim);
      p.set(Inf);
      return p;
   }
   // TODO: This was already calculated in nextCollider, consider caching.
   return objectCache[nextColliderCache]->nearestIntersection(myPosition(), myOrientation());
}

Real Perception::timeToCollision() const
{
   RealVec cp(nextCollisionPoint());
   if (Inf == cp.length())
   {
      return Inf; // No collisions detected.
   }

   RealVec rp(cp.relativeTo(myPosition()));

   // With the current set of assumptions, me could not be on a
   // collision course in the first place if the following assert
   // fails.
   TG_ASSERT(0 <= rp.dot(myVelocity()));
#if 0
   // TODO: To more accurately compute the time to collision we should
   // take into account the velocity of the collider.  But if we do
   // that here, we should have done that in the computation of the
   // nearest collider.  For example, if a collider is moving out of
   // the way faster than we are approaching it, then there is no
   // danger of collision after all.  But remember this whole method
   // is a percept and percepts don't have to be perfect as they are
   // meant to model how the NPC thinks about the world.  And in that
   // vein, using a stationary snapshot of the world is OK for now.
   // Especially so as the snapshot is regularly updated when the
   // percept is recalculated every time an action is selected.
   Real const colliderVel = rp.dot(objectCache[nextColliderCache]);
   Real const relVel = myVel - colliderVel;
#endif

   return rp.length(); // /myVel;
}

Obstacle* Perception::nextCollider() const
{
   // If the previous calculation of the next collider is still valid,
   // return the cached value.
   if (objectCache[nextColliderCache])
   {
      return static_cast<Obstacle*>(objectCache[nextColliderCache]);
   }

   Obstacle* which(NULL);
   Real dMin = Inf;
   for (ObstacleIterator i = gs->getObstacleListBegin(); i != gs->getObstacleListEnd(); i++)
   {
      // TODO: cast needed for me?
      if (me == &**i) { continue; } // Don't include me!

      RealVec rp((*i)->nearestIntersection(myPosition(), myOrientation()));
      // Infinity is used to indicate no intersection.
      if (rp.length() < Inf)
      {
         rp.subtract(myPosition());
         Real const d = rp.length() - myMaxExtent();
         if (d < dMin)
         {
            dMin = d;
            which = &**i;
         }
      }
   }
   // We must at least be on a collision course with one of the sides.
   // TODO: turn side collisions back on
   if (false && !which)
   {
      cerr << myPosition() << "; " << myOrientation() << endl;
      char c; cin >> c;
      TG_ASSERT(which);
   }
   // Computing the nearest collider is expensive so cache the result
   // in case it's needed again.

   // TODO: Could also be worth caching dMin as the distance to the
   // nearest collider.

   objectCache[nextColliderCache] = which;
   return which;
}
