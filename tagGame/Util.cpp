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

#include "Util.h"

#include <sstream>

using namespace tagGame;

using namespace std;

void Util::warn(string const& message)
{
   cerr << message << endl;
}

void Util::error(string const& message)
{
   warn(message);
   exit(0);
}

void Util::error(string const& errorStr, int const line, string const& filename, string const& message)
{
   cerr << "assert failed: " << errorStr << " (Line: " << line << ", file: " << filename << ")" << endl;
   error(message);
}

void Util::warn(bool const condition, string const& message)
{
   if (!condition)
   {
      warn(message);
   }
}

string Util::itos(int n)
{
  ostringstream os;
  os << n << flush;

  return os.str();
}
