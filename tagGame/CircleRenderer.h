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

#ifndef TG_CIRCLE_RENDERER_H
#define TG_CIRCLE_RENDERER_H

#include "RendererColor.h"

namespace tagGame
{
   /// This class is responsible for rendering circular objects.
   class CircleRenderer : public RendererColor
   {
   public:
      CircleRenderer();
      virtual ~CircleRenderer();

      virtual void render(Obstacle const* o);

   protected:
   private:
   };

   typedef SharedPtr<CircleRenderer>::type CircleRendererPtr;
}

#endif
