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

#ifndef TG_TIMER_H
#define TG_TIMER_H

#include "MathUtil.h"

#include <SDL.h>

namespace tagGame
{
   class Timer
   {
   public:
      // Time is measured in milliseconds
      static int const ticksPerSec = 1000;

      /// Singleton access.
      inline static Timer& theTimer();

      /// Start the game time counter.
      inline void start();

      /// Stop the game time counter.
      inline void stop();

      /// True if and only if the game time counter is stopped.
      inline bool isStopped() const;

      /// Game time.
      /// Measures the time (in ticks) in the game.
      /// Note: unlike wall clock time (see below), game time halts if
      /// the game is paused and then re-starts when the game is unpaused.
      inline int gameTicks() const;

      /// Game time in seconds.
      inline Real gameTime() const;

      /// Wall clock time.
      /// Measures the time (in ticks) since the game started.
      /// Note: so long as the program is running wall clock time, unlike
      /// game time (see above), continues incrementing.
      inline static int ticks();

      /// Wall clock time in seconds.
      inline static Real time();

   protected:
   private:
      /// Purposefully hidden so that there can be only one Timer.
      inline Timer();
      inline ~Timer();

      /// Purposefully not implemented.
      Timer(Timer const& timer);

      /// Purposefully not implemented.
      Timer& operator=(Timer const& timer);

      int startTime;
      int baseTime;
      bool isRunning;
   }; // Timer

   Timer::Timer() :
      startTime(0),
      baseTime(0),
      isRunning(false)
   {
   }

   Timer::~Timer()
   {
   }

   Timer& Timer::theTimer()
   {
      static Timer theTimer;

      return theTimer;
   }

   void Timer::start()
   {
      if (!isRunning)
      {
         startTime = ticks();
         isRunning = true;
      }
   }
   
   void Timer::stop()
   {
      if (isRunning)
      {
         baseTime = baseTime + (ticks() - startTime);
         isRunning = false;
      }
   }
   
   bool Timer::isStopped() const
   {
      return !isRunning;
   }
   
   int Timer::gameTicks() const
   {
      if (isRunning)
      {
         return baseTime + (ticks() - startTime);
      }

      return baseTime;
   }

   Real Timer::gameTime() const
   {
      return Real(gameTicks())/Real(ticksPerSec);
   }

   // We use SDL to implement the ticks method.  Simply re-implement this method to
   // if you don't want to use SDL or to port the timer class to other platforms
   // that don't support SDL.
   int Timer::ticks()
   {
      return SDL_GetTicks();
   }

   Real Timer::time()
   {
      return Real(ticks())/Real(ticksPerSec);
   }
}

#endif
