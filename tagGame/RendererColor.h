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

#ifndef TG_RENDERER_COLOR_H
#define TG_RENDERER_COLOR_H

#include "Renderer.h"
#include "Vec.h"

namespace tagGame
{
   class Obstacle;

   /// A class to handle colors.
   class RendererColor : public Renderer
   {
   public:
      RendererColor();
      virtual ~RendererColor();

      virtual void render(Obstacle const* o);

      inline RealVec const& getColor() const;
      inline RealVec const& getColorAlternative() const;
      inline RealVec const& getColorFlash() const;

      inline void setColor(RealVec const& color);
      inline void setColorAlternative(RealVec const& colorAlternative);
      inline void setColorFlash(RealVec const& colorFlash);

      inline void flashingOn();
      inline void flashingOff();

      inline void alternativeOn();
      inline void alternativeOff();

   protected:
   private:
      RealVec color;
      RealVec colorAlternative;
      RealVec colorFlash;

      bool flash;
      bool alternative;
   };

   RealVec const& RendererColor::getColor() const
   {
      return color;
   }
   
   RealVec const& RendererColor::getColorAlternative() const
   {
      return colorAlternative;
   }
   
   RealVec const& RendererColor::getColorFlash() const
   {
      return colorFlash;
   }
   
   void RendererColor::setColor(RealVec const& color)
   {
      this->color = color;
   }
   
   void RendererColor::setColorAlternative(RealVec const& colorAlternative)
   {
      this->colorAlternative = colorAlternative;
   }
   
   void RendererColor::setColorFlash(RealVec const& colorFlash)
   {
      this->colorFlash = colorFlash;
   }
   
   void RendererColor::flashingOn()
   {
      flash = true;
   }
   
   void RendererColor::flashingOff()
   {
      flash = false;
   }
   
   void RendererColor::alternativeOn()
   {
      alternative = true;
   }
   
   void RendererColor::alternativeOff()
   {
      alternative = false;
   }
}

#endif
