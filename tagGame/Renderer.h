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

#ifndef TG_RENDERER_H
#define TG_RENDERER_H

namespace tagGame
{
   class Obstacle;

   /// The abstract base class for all the renderers.
   class Renderer
   {
   public:
      inline Renderer();
      inline virtual ~Renderer();

      virtual void render(Obstacle const* o) = 0;

   protected:
   private:
   };

   Renderer::Renderer()
   {
   }

   Renderer::~Renderer()
   {
   }
}

#endif
