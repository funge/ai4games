This is the source code v1.3.0 associated with the book:

   Artificial Intelligence for Computer Games: An Introduction
   by John David Funge
   http://www.ai4games.org

The code is not intended to ever become a fully fledged game or game
engine.  It is simply a small pedagogical example used to illustrate
some of the ideas from the book about how game code can be structured.

The code compiles and runs on Windows, MacOSX and Linux.  See below
for additional details.

The code requires SDL (http://www.libsdl.org) to be installed.

Windows
=======

The code is intended to compile and run under Windows XP using Visual
C++ (including free Express Editions).

For the Express Editions, you'll also need to install the Microsoft
platform SDK (PSDK) free download.

Remember you also need to install SDL and setup Visual C++ to be able
to compile and run SDL applications.  There is a lot of information
available on the web about how to do this.  Some of the information
refers to other versions of Visual C++, but it shouldn't be hard to
map the information to your particular setup.

The SCons script should work with various version of Visual C++, but
has not been recently tested.

MacOSX
======

The code is intended to compile and run under MacOSX 10.x using SCons
and XCode 2.x.

A minimal .xcodeproj is also project is included in the distribution,
but it is not guaranteed to be up-to-date.  Depending on where you
installed SDL, you may need to change some of the paths to use it.

The code should compile and run under other compilers and versions of
MacOSX, but they are not officially supported.

Linux
=====

The code is intended to compile and run using SCons and GCC 4.x.

The code should compile and run under other compilers and various
versions of Linux.

There is also a minimal Makefile that can build the game, but not the
regressions.


