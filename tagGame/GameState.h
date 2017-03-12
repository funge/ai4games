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

#ifndef TG_GAME_STATE_H
#define TG_GAME_STATE_H

#include "Character.h"
#include "Timer.h"

namespace tagGame
{
   /// The game-state provides full access to the current state of the game world.
   class GameState
   {
   public:
      inline GameState(RealVec const& worldDim);
      inline ~GameState();

      inline ObstacleIterator getObstacleListBegin();
      inline ObstacleIterator getObstacleListEnd();

      inline ObstacleIteratorConst getObstacleListBegin() const;
      inline ObstacleIteratorConst getObstacleListEnd() const;

      inline CharacterIterator getCharacterListBegin();
      inline CharacterIterator getCharacterListEnd();

      inline CharacterIteratorConst getCharacterListBegin() const;
      inline CharacterIteratorConst getCharacterListEnd() const;

      inline ObstacleIterator getNonCharacterObstacleListBegin();
      inline ObstacleIterator getNonCharacterObstacleListEnd();

      inline ObstacleIteratorConst getNonCharacterObstacleListBegin() const;
      inline ObstacleIteratorConst getNonCharacterObstacleListEnd() const;

      // Add objects
      inline void addCharacter(CharacterPtr c);
      inline void addObstacle(ObstaclePtr o);

      inline RealVec const& getWorldDim() const;

      inline int getFrame() const;
      inline void incFrame();

      inline int getLastTaggedTime();
      inline void setTagged();

   protected:
   private:
      // List of all obstacles
      ObstacleList obstacles;
      // The current frame number
      int frame;
      // Instead of maintaining separate lists of characters and non-character obstacles,
      // some other options are:
      //  i) Just use dynamic_cast to figure out which type an obstacle is;
      // ii) Maintain lists of indices into the obstacles list.
      // But i) requires run-time type information and can be slow, while ii)
      // adds an extra level of indirection that doesn't really gain us much.
      // In future, we might consider adding a new moveable obstacle type.
      CharacterList characters;
      ObstacleList nonCharacterObstacles;

      RealVec worldDim;

      int lastTagTime;
   }; // GameState

   GameState::GameState(RealVec const& worldDim) :
      frame(0),
      worldDim(worldDim),
      lastTagTime(-1)
   {}

   GameState::~GameState()
   {
   }

   int GameState::getLastTaggedTime()
   {
      return lastTagTime;
   }

   ObstacleIterator GameState::getObstacleListBegin()
   {
      return obstacles.begin();
   }

   ObstacleIterator GameState::getObstacleListEnd()
   {
      return obstacles.end();
   }

   ObstacleIteratorConst GameState::getObstacleListBegin() const
   {
      return obstacles.begin();
   }

   ObstacleIteratorConst GameState::getObstacleListEnd() const
   {
      return obstacles.end();
   }

   CharacterIterator GameState::getCharacterListBegin()
   {
      return characters.begin();
   }

   CharacterIterator GameState::getCharacterListEnd()
   {
      return characters.end();
   }

   CharacterIteratorConst GameState::getCharacterListBegin() const
   {
      return characters.begin();
   }

   CharacterIteratorConst GameState::getCharacterListEnd() const
   {
      return characters.end();
   }

   ObstacleIterator GameState::getNonCharacterObstacleListBegin()
   {
      return nonCharacterObstacles.begin();
   }

   ObstacleIterator GameState::getNonCharacterObstacleListEnd()
   {
      return nonCharacterObstacles.end();
   }

   ObstacleIteratorConst GameState::getNonCharacterObstacleListBegin() const
   {
      return nonCharacterObstacles.begin();
   }

   ObstacleIteratorConst GameState::getNonCharacterObstacleListEnd() const
   {
      return nonCharacterObstacles.end();
   }

   RealVec const& GameState::getWorldDim() const
   {
      return worldDim;
   }
   
   int GameState::getFrame() const
   {
      return frame;
   }
   
   void GameState::incFrame()
   {
      frame++;
   }
   
   void GameState::setTagged()
   {
      lastTagTime = Timer::theTimer().gameTicks();
   }

   void GameState::addCharacter(CharacterPtr c)
   {
      characters.push_back(c);
      obstacles.push_back(c);
   }

   void GameState::addObstacle(ObstaclePtr o)
   {
      obstacles.push_back(o);
      nonCharacterObstacles.push_back(o);
   }
}

#endif
