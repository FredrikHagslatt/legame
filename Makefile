CC = g++
LANG_STD = -std=c++17
CFLAGS = -Wall \
		 -Wfatal-errors
SRC = src/*.cpp \
	  src/*/*.cpp
INCLUDES = -I"libs"\
		   -I"src"
LINKER = -lSDL2 \
		 -lSDL2_image \
		 -lSDL2_ttf \
		 -lSDL2_mixer \
		 -llua5.3
EXECUTABLE = gameengine
	
build:
	$(CC) $(CFLAGS) $(LANG_STD) $(SRC) $(INCLUDES) $(LINKER) -o $(EXECUTABLE);

run:
	./$(EXECUTABLE)

clean:
	rm $(EXECUTABLE)