CXX = g++
CPPFLAGS = $(shell sdl-config --cflags)
LIBS = $(shell sdl-config --libs) -lGL -lGLU -lm

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM -MG $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

sources := $(wildcard *.cpp)
regressions := $(wildcard *Test.cpp)

sources := $(filter-out $(regressions),$(sources))

objects := $(patsubst %.cpp,%.o,$(sources))

tagGame : $(objects)
	$(CXX) -o tagGame $(objects) $(LIBDIR) $(LIBS)

include $(sources:.cpp=.d)

clean:
	rm -f core *.o *.d

