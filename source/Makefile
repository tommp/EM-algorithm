program_EXECUTABLE := ./../em

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

program_CXX_SRCS := $(wildcard *.cpp)
program_OBJS := ${program_CXX_SRCS:.cpp=.o}


SDL_LIB = -L/usr/local/lib -lSDL2 -lSDL2_gfx -lSDL2_ttf -Wl,-rpath=/usr/local/lib 
program_INCLUDE_DIRS := current_dir ./headers/
program_LIBRARY_DIRS :=
program_LIBRARIES :=  m

LDFLAGS += $(SDL_LIB)
CXXFLAGS += -Wall -g -std=c++11
CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))


.PHONY: all clean distclean
all: $(program_EXECUTABLE)

$(program_OBJS):%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(program_EXECUTABLE): $(program_OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $(program_OBJS) -o $(program_EXECUTABLE) $(LDFLAGS)

clean:
	@- $(RM) $(program_EXECUTABLE)
	@- $(RM) $(program_OBJS)

distclean: clean

