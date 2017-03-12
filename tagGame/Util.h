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

#ifndef TG_UTIL_H
#define TG_UTIL_H

#include <iostream> // TODO: replace with iosfwd
#include <cstdlib>
#include <cassert>
#include <string>

#undef TG_USE_TR1
#if defined(__GNUC__) && (__GNUC__ >= 4)
#define TG_USE_TR1 1
#endif

#if defined(TG_USE_TR1)
#include <tr1/memory>
#endif

namespace tagGame
{
   // The purpose of these typedefs is to reduce the number of code changes
   // involved in replacing these TR1 data structures with equivalent ones
   // (the additional struct syntax is needed because C++ doesn't allow us to
   // directly define typedef templates).

   template<class T>
   struct SharedPtr
   {
#ifdef TG_USE_TR1
      typedef std::tr1::shared_ptr<T> type;
#else
      typedef T* type;
#endif
   };

   struct DeleteObject
   {
      template <typename T>
      void operator()(T* p) { delete p;}
   };

   /// Miscellaneous utility functions.
   class Util
   {
   public:

      /// Print the warning message and continue.
      static void warn(std::string const& message);

      /// Print the error message and exit.
      static void error(std::string const& message);

      /// Called by the TG_ASSERT macros.
      static void error(std::string const& errorStr, int const line, std::string const& filename, std::string const& message = "");

      /// Iff condition is false, print the warning message.
      static void warn(bool const condition, std::string const& message);

      /// Convert n to a string.
      static std::string itos(int n);

   protected:
   private:
   };
}

#if defined(DEBUG)
   #define TG_ASSERT(c) ((c) ? (void)0 : tagGame::Util::error(#c, __LINE__, __FILE__))
   #define TG_ASSERT_MSG(c, s) ((c) ? (void)0 : tagGame::Util::error(#c, __LINE__, __FILE__, s))
#else
   #define TG_ASSERT(c)
   #define TG_ASSERT_MSG(c, s)
#endif

#define TG_ARRAY_COUNT(x) (sizeof(x)/sizeof((x)[0]))

#endif
