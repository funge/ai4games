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

#ifndef TG_KEYBOARD_SDL_H
#define TG_KEYBOARD_SDL_H

#include "MathUtil.h"

namespace tagGame
{
   /// This class uses SDL to provide keyboard feedback.
   class KeyboardSDL
   {
   public:
      KeyboardSDL();
      ~KeyboardSDL();

      bool init();

      // Returns a value from -1 to 1.
      Real getX();
      // Return a value from -1 to 1.
      Real getY();
   protected:
   private:
   };
}

#endif
