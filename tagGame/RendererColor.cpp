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

#include "RendererColor.h"
#include "GameState.h"
#include "Gui.h"
#include "Timer.h"

using namespace tagGame;

RendererColor::RendererColor() :
   Renderer(),
   color(Gui::colorDim),
   colorAlternative(Gui::colorDim),
   colorFlash(Gui::colorDim),
   flash(false),
   alternative(false)
{
}

RendererColor::~RendererColor()
{
}

void RendererColor::render(Obstacle const* o)
{
   if (alternative) { Gui::setColor(colorAlternative); }
   else { Gui::setColor(color); }

   static unsigned count = 0;
   if (flash && fmod(Timer::theTimer().gameTime(), 2) < Real(1))
   {
      Gui::setColor(colorFlash);
   }
   count++;
}
