CC=../tcc/tcc.exe
LIBS=-lgdi32 -luser32 -lopengl32
SOURCE=./src/matrix.c ./src/opengl_impl.c ./src/game.c ./src/shader.c ./src/render.c ./src/window.c ./src/vector.c ./src/input_handler.c ./src/main.c
INCLUDES=-Iinclude

debug:
	$(CC) -g -Wall -o program_debug.exe $(INCLUDES) $(SOURCE) $(LIBS)
	./program_debug.exe

build:
	$(CC) -Wall -o program.exe $(INCLUDES) $(SOURCE) $(LIBS)

run: build
	./program.exe

