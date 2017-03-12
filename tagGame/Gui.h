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

#ifndef TG_GUI_H
#define TG_GUI_H

#include "Vec.h"

class GLUquadric;

namespace tagGame
{
   class GameState;

   /// This class is responsible for handling the game's GUI.
   class Gui
   {
   public:
      static const int colorDim = 4; // rgba

      static void createWindow(int const width, int const height, std::string const& title);
      static void destroyWindow();
      static void render(GameState* gs);
      static bool isQuit();

      static void drawCircle(RealVec const& center, RealVec const& orientation, Real const radius);
      static void drawArrow(RealVec const& begin, RealVec const& direction);
      static void drawLineSegment(RealVec const& begin, RealVec const& end);
      static void setColor(RealVec const& color);

      /// Pause for t milliseconds.
      static void pause(int const t);

      static RealVec const& getColorFromName(std::string const& colorName);

   protected:
   private:
      static void initGL(int const width, int const height);
      static GLUquadric* q;
   };
}

#endif
