CC = gcc
PKG_CONFIG ?= pkg-config

CFLAGS = -O2 -Wall -Wextra
RAYLIB_CFLAGS := $(shell $(PKG_CONFIG) --cflags raylib 2>/dev/null)
RAYLIB_LIBS := $(shell $(PKG_CONFIG) --libs raylib 2>/dev/null)

# Fallback if pkg-config doesn't know raylib
ifeq ($(strip $(RAYLIB_LIBS)),)
	RAYLIB_LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lXrandr -lXi -lXcursor -lXinerama
endif

TARGET = app
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(RAYLIB_CFLAGS) $(SRC) -o $(TARGET) $(RAYLIB_LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
