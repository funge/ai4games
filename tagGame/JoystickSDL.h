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

#ifndef TG_JOYSTICK_SDL_H
#define TG_JOYSTICK_SDL_H

#include "MathUtil.h"

typedef struct _SDL_Joystick SDL_Joystick;

namespace tagGame
{
   /// This class uses SDL to provide joystick feedback.
   class JoystickSDL
   {
   public:
      JoystickSDL();
      ~JoystickSDL();

      bool init();

      // Returns a value from -1 to 1.
      Real getX();
      // Return a value from -1 to 1.
      Real getY();
   protected:
   private:
      SDL_Joystick* joystick;
   };
}

#endif
