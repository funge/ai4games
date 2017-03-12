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

#ifndef TG_PERCEPTION_H
#define TG_PERCEPTION_H

#include "GameState.h"
#include "Character.h"
#include "Timer.h"
#include "Circle.h"

#include <map>

namespace tagGame
{
   /// Controller's should gain all access to game-state information through a
   /// perception object.
   class Perception
   {
   public:
      Perception(GameState* gs);
      ~Perception();

      /// Set the character from whose point of view percepts are to be calculated.
      /// This method should be called prior to the associated character's controller
      /// selecting an action.  Most percepts "pull" information from the game as it is
      /// required by a controller.  The "setMe" method is the main "push" method for telling
      /// a controller which character is selecting an action.
      inline void setMe(Character* me);

      /// Set the character that is currently tagged.
      /// Information about which character is currently tagged could be "pulled" from the
      /// game, but currently the information is only stored locally in the tagged character.
      /// It is therefore more efficient for the game to explicitly "push" the information
      /// whenever a new character is tagged.
      inline void setTagged(Character* tagged);

      /// Accessors for the pushed information.
      inline Character* getMe() const;
      inline Character* getTagged() const;

      /// Some basic information about me.
      inline RealVec const& myPosition() const;
      inline RealVec myVelocity() const;
      inline Real mySpeed() const;
      inline RealVec const& myOrientation() const;
      inline Real myMaxExtent() const;
      inline Real myExtent(RealVec const& dir) const;
      inline Real myMaxSpeed(void) const;
      inline bool myselfTagged() const;

      /// Memory percept for who last tagged me.
      Character const* whoLastTaggedMe() const;

      /// How many milliseconds ago counts as "recent"
      static int const recentThreshold = 5000;

      /// Some memory percepts for recent events.
      int myRecentTaggedCount() const;
      bool myselfRecentlyTagged() const;

      /// Some basic information about the tagged character.
      inline RealVec const& taggedPosition() const;
      inline RealVec taggedVelocity() const;
      inline RealVec taggedRelativePosition() const;
      inline Real distanceSquaredToTagged() const;
      inline Real distanceToTagged() const;

      /// Predictor percept for tagged character's future position.
      inline RealVec taggedFuturePosition() const;

      /// Information about the nearest character.
      Character* nearestCharacter() const;
      inline RealVec const& nearestCharacterPosition() const;
      inline RealVec nearestCharacterRelativePosition() const;
      inline Real distanceSquaredToNearestCharacter() const;
      inline Real distanceToNearestCharacter() const;

      /// Some information about obstacles.
      Obstacle* nearestObstacle() const; 
      inline RealVec nearestObstaclePosition() const;
      inline RealVec nearestObstacleRelativePosition() const;
      inline Real distanceSquaredToNearestObstacle() const;
      inline Real distanceToNearestObstacle() const;

      /// Information about an arbitary obstacle.  Note that,
      /// characters are also obstacles.
      inline RealVec const& position(Obstacle const& which) const;
      inline RealVec relativePosition(Obstacle const& which) const;
      inline Real distanceSquaredTo(Obstacle const& which) const;      
      inline Real distanceTo(Obstacle const& which) const;

      /// Predictor percept for time until my next collision.  For
      /// discrete-event simulation (see Chapter 2), an anlogous
      /// game-side function would need to be defined.  Such a
      /// game-side version would have to provide reliable and
      /// conservative predictions.  In contrast, this predictor
      /// percept only needs to be accurate enough to provide
      /// "reasonable" collision avoidance behavior.  Where, in this
      /// case (as in many games), "reasonable" admits the possibility
      /// of the odd collision not being avoided.
      Real timeToCollision() const;
      /// Predictor percept for my next collision point.
      RealVec nextCollisionPoint() const;
      /// Predictor percept for obstacle for my next collision.
      Obstacle* nextCollider() const;

      /// Some basic information about the game.
      inline int getFrame();
      inline int getTicks();
      inline Real getTime();

      /// Full access to the underlying game-state should be restricted to debugging
      /// use only.
      inline GameState* getGameState();

   private:
      // Update state information about who tagged who last.
      void updateLastTagged();

      // Pointer to the game-state object
      GameState* gs;
      // The character from whose point of view percepts are to be calculated.
      Character* me;
      // The tagged character.
      Character* tagged;
      // The previous tagged character.
      Character* lastTagged;

      std::map<Character*,Character*> lastTaggedByList;

      enum cacheType
      {
         nearestCharacterCache,
         nearestObstacleCache,
         nextColliderCache,
         objectCacheSize
      };

      mutable std::vector<Obstacle*> objectCache;
   };

   typedef bool (Perception::*PerceptBool)() const;
   typedef int (Perception::*PerceptInt)() const;
   typedef Real (Perception::*PerceptReal)() const;

   void Perception::setMe(Character* me)
   {
      TG_ASSERT(me);
   
      this->me = me;
   
      // Currently, the cache is only valid so long as the point of view
      // doesn't change.  That is, when a controller is selecting an
      // action for a single character, some values don't have to be
      // recomputed if they have previously already been determined.
      // Note that, caches could be maintained on a per character basis.
      // This would mean the cache could still be useful even if actions
      // were not computed for each character sequentially.  In addition,
      // caches could only be invalidated after n frames, thus avoiding
      // additional computation at the expense (as n increases) of less
      // accurate information.
      fill(objectCache.begin(),objectCache.end(), static_cast<Obstacle*>(NULL));
   }
   
   void Perception::setTagged(Character* tagged)
   {
      TG_ASSERT(tagged);
      TG_ASSERT(tagged->getIsTagged());
   
      lastTagged = this->tagged;
      this->tagged = tagged;
      // Assume tagged was tagged by last tagged.  The lastTaggedByList will become
      // corrupt if the game ever omits to call setTagged when a new character is
      // tagged.
      lastTaggedByList[tagged] = lastTagged;
   }
   
   Character* Perception::getMe(void) const
   {
      return me;
   }
   
   Character* Perception::getTagged(void) const
   {
      return tagged;
   }
   
   RealVec const& Perception::myPosition() const
   {
      return me->getPosition();
   }
   
   // TODO: add a void for all empty function argument lists
   RealVec Perception::myVelocity(void) const
   {
      return me->getVelocity();
   }
   
   Real Perception::mySpeed() const
   {
      return me->getSpeed();
   }
   
   RealVec const& Perception::myOrientation(void) const
   {
      return me->getOrientation();
   }
   
   Real Perception::myMaxExtent() const
   {
      // TODO: Use more notion of extent in the rest of the game.
      return static_cast<Circle const&>(me->getShape()).getRadius();
   }
   
   Real Perception::myExtent(RealVec const& dir) const
   {
      // Use more notion of extent in the rest of the game.
      return static_cast<Circle const&>(me->getShape()).getRadius();
   }
   
   Real Perception::myMaxSpeed(void) const
   {
      return me->getMaxSpeed();
   }
   
   bool Perception::myselfTagged() const
   {
      return tagged == me;
   }
   
   RealVec const& Perception::taggedPosition(void) const
   {
      TG_ASSERT(tagged);
   
      return tagged->getPosition();
   }
   
   RealVec Perception::taggedVelocity(void) const
   {
      TG_ASSERT(tagged);
   
      return tagged->getVelocity();
   }
   
   RealVec Perception::taggedRelativePosition(void) const
   {
      TG_ASSERT(tagged);
   
      return taggedPosition().relativeTo(myPosition());
   }
   
   Real Perception::distanceSquaredToTagged() const
   {
      assert(tagged);
   
      return me->distanceSquaredTo(*tagged);
   }
   
   Real Perception::distanceToTagged() const
   {
      TG_ASSERT(tagged);
   
      return me->distanceTo(*tagged);
   }
   
   RealVec Perception::taggedFuturePosition() const
   {
      RealVec p(taggedPosition());
      return p.add(taggedVelocity());
   }
   
   RealVec const& Perception::nearestCharacterPosition() const
   {
      return nearestCharacter()->getPosition();
   }
   
   RealVec Perception::nearestCharacterRelativePosition() const
   {
      return nearestCharacterPosition().relativeTo(myPosition());
   }
   
   Real Perception::distanceSquaredToNearestCharacter() const
   {
      return me->distanceSquaredTo(*nearestCharacter());
   }
   
   Real Perception::distanceToNearestCharacter() const
   {
      return me->distanceTo(*nearestCharacter());
   }
   
   RealVec const& Perception::position(Obstacle const& which) const
   {
      return which.getPosition();
   }
   
   RealVec Perception::relativePosition(Obstacle const& which) const
   {
      return position(which).relativeTo(myPosition());
   }
   
   Real Perception::distanceSquaredTo(Obstacle const& which) const
   {
      return me->distanceSquaredTo(which);
   }
   
   Real Perception::distanceTo(Obstacle const& which) const
   {
      return me->distanceTo(which);
   }
   
   RealVec Perception::nearestObstaclePosition() const
   {
      return nearestObstacle()->getPosition();
   }
   
   RealVec Perception::nearestObstacleRelativePosition() const
   {
      return nearestObstaclePosition().relativeTo(myPosition());
   }
   
   Real Perception::distanceSquaredToNearestObstacle() const
   {
      return me->distanceSquaredTo(*nearestObstacle());
   }
   
   Real Perception::distanceToNearestObstacle() const
   {
      return me->distanceTo(*nearestObstacle());
   }
   
   int Perception::getFrame()
   {
      return gs->getFrame();
   }
   
   int Perception::getTicks()
   {
      // characters only know about game time
      return Timer::theTimer().gameTicks();
   }

   Real Perception::getTime()
   {
      // characters only know about game time
      return Timer::theTimer().gameTime();
   }
   
   GameState* Perception::getGameState()
   {
      TG_ASSERT(gs);
   
      return gs;
   }
}

#endif

