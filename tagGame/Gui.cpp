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

#include "Gui.h"
#include "Util.h"
#include "Timer.h"
#include "GameState.h"
#include "Util2D.h"

#if defined(_MSC_VER)
#define NOMINMAX
#include <windows.h>
#endif

#include <SDL.h>
#include <SDL_opengl.h>

#if defined(TG_USE_TR1)
#include <tr1/functional>
#endif

using namespace tagGame;

using namespace std;

GLUquadric* Gui::q = NULL;

RealVec const& Gui::getColorFromName(string const& colorName)
{
   static RealVec white(colorDim);
   static RealVec black(colorDim);
   static RealVec red(colorDim);
   static RealVec green(colorDim);
   static RealVec blue(colorDim);
   static RealVec yellow(colorDim);

   static bool set(false);
   if (!set)
   {
      white.set(1.0);
      red[0] = 1.0;
      red[3] = 1.0;
      green[1] = 1.0;
      green[3] = 1.0;
      blue[2] = 1.0;
      blue[3] = 1.0;
      yellow.set(1.0);
      yellow[2] = 0.0;
      set = true;
   }

   if (colorName == "yellow")
   {
      return yellow;
   }
   else if (colorName == "white")
   {
      return white;
   }
   else if (colorName == "green")
   {
      return green;
   }
   else if (colorName == "red")
   {
      return red;
   }
   else if (colorName == "blue")
   {
      return blue;
   }
   else
   {
      Util::error("unknown color name: " + colorName);
   }

   return black;
}

void Gui::drawCircle(RealVec const& center, RealVec const& orientation, Real const radius)
{
   glPushMatrix();
   glTranslatef(GLfloat(center[0]), GLfloat(center[1]), 0.0);
   glRotatef(GLfloat(MathUtil::radToDeg(Util2D::angle(orientation))), 0, 0, 1);
   gluPartialDisk(Gui::q, 0.0, radius, 20, 1, 0.0, 360.0);
   glPopMatrix();
}

void Gui::drawLineSegment(RealVec const& begin, RealVec const& end)
{
   glBegin(GL_LINES);
   glVertex2f(GLfloat(begin[0]), GLfloat(begin[1]));
   glVertex2f(GLfloat(end[0]), GLfloat(end[1]));
   glEnd();
}

void Gui::drawArrow(RealVec const& begin, RealVec const& direction)
{
   RealVec lvec(direction);

   Real const lineSize = lvec.length();
   Real const headSize = 0.5*lineSize;
   Real const lAngle = 2.5;
   Real const rAngle = -2.5;

   lvec.normalize();

   RealVec hvec1(Util2D::rotationMatrix(lAngle).multiply(lvec));
   RealVec hvec2(Util2D::rotationMatrix(rAngle).multiply(lvec));
   hvec1.scale(headSize);
   hvec2.scale(headSize);
   lvec.scale(lineSize);

   bool const rightWay(true);
   glPushMatrix();
   if (rightWay)
   {
      glTranslatef(GLfloat(begin[0]), GLfloat(begin[1]), 0.0);
   }
   else
   {
      glTranslatef(GLfloat(begin[0] - lvec[0]), GLfloat(begin[1] - lvec[1]), 0.0);
   }
   glBegin(GL_LINE_STRIP);
   glVertex2f(0, 0);
   glVertex2f(GLfloat(lvec[0]), GLfloat(lvec[1]));
   glVertex2f(GLfloat(lvec[0] + hvec1[0]), GLfloat(lvec[1] + hvec1[1]));
   glEnd();
   glPopMatrix();

   glPushMatrix();
   if (rightWay)
   {
      glTranslatef(GLfloat(begin[0] + lvec[0]), GLfloat(begin[1] + lvec[1]), 0.0);
   }
   else
   {
      glTranslatef(GLfloat(begin[0]), GLfloat(begin[1]), 0.0);
   }
   glBegin(GL_LINES);
   glVertex2f(0, 0);
   glVertex2f(GLfloat(hvec2[0]), GLfloat(hvec2[1]));
   glEnd();
   glPopMatrix();
}

void Gui::pause(int const t)
{
   SDL_Delay(t);
}

void Gui::setColor(RealVec const& color)
{
   // TODO: why doesn't next line work properly?  sets color to whatever it was
   // set to previously! maybe something funny todo with memory addresses?
   // glColor4fv((GLfloat*) &color[0]);
   glColor4f(GLfloat(color[0]), GLfloat(color[1]), GLfloat(color[2]), GLfloat(color[3]));
}

void Gui::render(GameState* gs)
{
#if defined(TG_USE_TR1)
   for_each(gs->getObstacleListBegin(), gs->getObstacleListEnd(), std::tr1::mem_fn(&Obstacle::render));
#else
   for_each(gs->getObstacleListBegin(), gs->getObstacleListEnd(), std::mem_fun(&Obstacle::render));
#endif

   SDL_GL_SwapBuffers();
   glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
}

bool Gui::isQuit()
{
   SDL_Event event;
   while (SDL_PollEvent(&event))
   {
      switch (event.type)
      {
      case SDL_QUIT:
         return true;
      default:
         break;
      }
   }

   Uint8* keys(SDL_GetKeyState(NULL));
   if (keys[SDLK_ESCAPE]) { return true; }

   // if (gs->getTimeStep() > 1) { return true; }

   return false;
}

void Gui::initGL(int const width, int const height)
{
   TG_ASSERT(0 != height);

   glViewport(0, 0, width, height);

   // Set the world to screen coordinate transform
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   glOrtho(0, width, 0, height, -2.0, 2.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // Default disables...
   glDepthFunc(GL_ALWAYS);
   glDisable(GL_LINE_STIPPLE);

   glClearColor(0.00f, 0.00f, 0.00f, 0.0f);

   q = gluNewQuadric();
}


void Gui::destroyWindow()
{
   gluDeleteQuadric(q);

   SDL_Quit();
}

void Gui::createWindow(int const width, int const height, string const& title)
{
   if (SDL_Init(SDL_INIT_VIDEO) < 0) { Util::error("Couldn't init SDL"); }

   if (!SDL_SetVideoMode(width, height, 0, SDL_OPENGL)) { Util::error("SDL problem"); }

   SDL_WM_SetCaption(title.c_str(), title.c_str());

   initGL(width, height);
}


