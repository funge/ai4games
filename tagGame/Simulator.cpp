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

#include "Simulator.h"
#include "Character.h"
#include "GameState.h"
#include "Timer.h"
#include "Controller.h"
#include "Perception.h"
#include "Util2D.h"

using namespace tagGame;

Simulator::Simulator(GameState* gs) :
   gs(gs)
{
}

void Simulator::forward(Real const deltaT)
{
   // NOTE: all characters select actions using the state of the game world at time t.
   // Only after all the actions are selected is the game state updated (using
   // those actions) to the correct state at time t + deltaT.
   // This avoids any of the problems that are described in the book with one
   // character continually "going first".

   generateActions();
   processActions(deltaT);
   resolveCollisions();
   updateGameState(deltaT);
}

void Simulator::generateActions()
{
   for (CharacterIterator i = gs->getCharacterListBegin(); i != gs->getCharacterListEnd(); i++)
   {
      // IMPORTANT: Make all percepts be computed from character i's point of view.
      (*i)->getController()->getPerception()->setMe(&**i);
      (*i)->calcAction();
   }
}

void Simulator::processActions(Real const deltaT)
{
   for (CharacterIterator i = gs->getCharacterListBegin(); i != gs->getCharacterListEnd(); i++)
   {
      // calculate character's required acceleration from the desired velocity
      RealVec acceleration((*i)->getAction().getDesiredDirection());
      acceleration.scale((*i)->getAction().getDesiredSpeed() * (*i)->getMaxSpeed());
      acceleration.subtract((*i)->getVelocity());
      // calculate required force from the acceleration
      RealVec force(acceleration.scale((*i)->getMass()));
      // force can't be greater than the maximum possible force
      force.clampMaxLength((*i)->getMaxForce());
      // re-calculate acceleration for new (possibly) clamped force
      acceleration = force.scale(1.0/(*i)->getMass());
      acceleration.scale(deltaT);
      // v = character's current velocity
      RealVec v((*i)->getVelocity());
      v.add(acceleration);

      v.clampMaxLength((*i)->getMaxSpeed());

      (*i)->setVelocity(v);
   }
}

void Simulator::updateCharacter(Real const deltaT, Character* c)
{
   RealVec p(c->getPosition());
   RealVec v(c->getVelocity());
   v.scale(deltaT);
   p.add(v);
   p.wrap(gs->getWorldDim());
   c->setPosition(p);
}

void Simulator::updateGameState(Real const deltaT)
{
   for (CharacterIterator i = gs->getCharacterListBegin(); i != gs->getCharacterListEnd(); i++)
   {
      updateCharacter(deltaT, &**i);
   }
}

static RealVec scaleAndAdd(RealVec const& v0, Real s0, RealVec const& v1, Real s1)
{
   RealVec v(v0);
   v.scale(s0);
   RealVec tmp(v1);
   tmp.scale(s1);
   v.add(tmp);

   return v;
}

void Simulator::resolveCollisions()
{
   Real const e = 0.75;           // coefficient of restitution
   int const minTagInterval = 3000; // minimum time allowed between re-tagging

   int const now = Timer::theTimer().gameTicks();
   int loopCount = 0;

   while (true)
   {
      bool isCollision = false;

      for (CharacterIterator i = gs->getCharacterListBegin(); i != gs->getCharacterListEnd(); i++)
      {
         for (CharacterIterator j = gs->getCharacterListBegin(); j != gs->getCharacterListEnd(); j++)
         {
            if (*i == *j) { continue; }
   
            if (!(*i)->isColliding(**j)) { continue; }

            isCollision = true;

            // We have to keep computing these in case they changed in a previous collision
            RealVec const& uc((*i)->getVelocity());
            Real const mc = (*i)->getMass();

            RealVec t((*i)->normalTo(**j));
            RealVec n(Util2D::perpendicularTo(t).getRow(0));

            Real const uct = uc.dot(t);
            Real const ucn = uc.dot(n);

            Real const mo = (*j)->getMass();

            RealVec const& uo((*j)->getVelocity());

            Real const uot = uo.dot(t);
            Real const uon = uo.dot(n);

            Real const k = (uct - uot)/(mc + mo);
            Real const vct = uct - (1 + e) * mo * k;
            Real const vot = uot + (1 + e) * mc * k;

            (*i)->setVelocity(scaleAndAdd(t, vct, n, ucn));

            (*j)->setVelocity(scaleAndAdd(t, vot, n, uon));

            // TODO: re-factor to remove duplicated code
            if ((*j)->getIsTagged() && (now - gs->getLastTaggedTime() > minTagInterval))
            {
               setTagged(**i, **j);
            }
            else if ((*i)->getIsTagged() && (now - gs->getLastTaggedTime() > minTagInterval))
            {
               setTagged(**j, **i);
            }
         }

         for (ObstacleIterator j = gs->getNonCharacterObstacleListBegin(); j != gs->getNonCharacterObstacleListEnd(); j++)
         {
            if (!(*i)->isColliding(**j)) { continue; }

            isCollision = true;

            RealVec const& uc((*i)->getVelocity());

            RealVec t((*i)->normalTo(**j));
            RealVec n(Util2D::perpendicularTo(t).getRow(0));

            Real const uct = uc.dot(t);
            Real const ucn = uc.dot(n);

            Real const vct = -e * uct;
            (*i)->setVelocity(scaleAndAdd(t, vct, n, ucn));
         }
      }

      if (!isCollision) { break; }

      TG_ASSERT_MSG(loopCount < 1000, "something probably went wrong");
      loopCount++;
   }
}

void Simulator::setTagged(Character& newTagged, Character& oldTagged)
{
   int const now = Timer::theTimer().gameTicks();

   newTagged.setTagged(now);
   oldTagged.setTagged(-1);
   gs->setTagged();
}

