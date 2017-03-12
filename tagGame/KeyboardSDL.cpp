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

#include "KeyboardSDL.h"

#include <SDL.h>

using namespace tagGame;

KeyboardSDL::KeyboardSDL()
{
}

bool KeyboardSDL::init()
{
   return true;
}

KeyboardSDL::~KeyboardSDL()
{
}


Real KeyboardSDL::getX()
{
   Uint8* keys(SDL_GetKeyState(NULL));

#if 0 // useful for debugging
   for (int i = SDLK_FIRST; i < SDLK_LAST; i++)
   {
      if (keys[i]) { cerr << int(i) << ": " << int(keys[i]) << endl; }
   }
#endif

   if (keys[SDLK_LEFT]) { return -1; }
   if (keys[SDLK_RIGHT]) { return 1; }

   return 0;
}

Real KeyboardSDL::getY()
{
   Uint8* keys(SDL_GetKeyState(NULL));

   if (keys[SDLK_UP]) { return 1; }
   if (keys[SDLK_DOWN]) { return -1; }

   return 0;
}


