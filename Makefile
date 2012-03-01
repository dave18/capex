PROG_NAME = capex
OBJS = capex.o cpuclock.o
CROSS_COMPILE = C:/devkitPro/devkitGP2X/bin/arm-linux-
SDL_BASE = C:/devkitPro/devkitGP2X/bin/arm-linux-
LDFLAGS = -static

CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
STRIP = $(CROSS_COMPILE)strip
CLEANUP = rm -f $(ALL_TARGETS) *.o *~

CFLAGS = `$(SDL_BASE)sdl-config --cflags` -O2 -funroll-loops -Wextra -Werror
#CFLAGS = `$(SDL_BASE)sdl-config --cflags` -O2 -funroll-loops -Wall
CXXFLAGS = `$(SDL_BASE)sdl-config --cflags` -O2 -funroll-loops -Wall
LIBS = `$(SDL_BASE)sdl-config --libs`

TARGET = $(PROG_NAME).gpe
SDLTEST_OBJS = $(OBJS)

all : $(TARGET)

$(TARGET) : $(SDLTEST_OBJS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(SDLTEST_OBJS) $(LIBS)
	$(STRIP) $(TARGET)
	$(CLEANUP)
