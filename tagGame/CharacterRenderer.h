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

#ifndef TG_CHARACTER_RENDERER
#define TG_CHARACTER_RENDERER

#include "CircleRenderer.h"

namespace tagGame
{
   /// This class is responsible for rendering characters.
   class CharacterRenderer : public CircleRenderer
   {
   public:
      CharacterRenderer();
      virtual ~CharacterRenderer();

      virtual void render(Obstacle const* o);

   protected:
   private:
   };

   typedef SharedPtr<CharacterRenderer>::type CharacterRendererPtr;
}

#endif

