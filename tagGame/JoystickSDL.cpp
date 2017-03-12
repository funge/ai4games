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

#include "JoystickSDL.h"

#include <SDL.h>

using namespace tagGame;

JoystickSDL::JoystickSDL()
{
   SDL_Init(SDL_INIT_JOYSTICK);
}

bool JoystickSDL::init()
{
   joystick = SDL_JoystickOpen(0);

   if (joystick && SDL_JoystickOpened(0)) { return true; }

   return false;
}

JoystickSDL::~JoystickSDL()
{
   SDL_JoystickClose(joystick);
}

Real JoystickSDL::getX()
{
   //  Note: SDL_JoystickGetAxis returns a value in the range from -32768 to 32767.
   return SDL_JoystickGetAxis(joystick, 0) / Real(32768);
}

Real JoystickSDL::getY()
{
   //  Note: SDL_JoystickGetAxis returns a value in the range from -32768 to 32767.
   return -SDL_JoystickGetAxis(joystick, 1) / Real(32768);
}

