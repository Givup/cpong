CC=..\TCC\tcc.exe
LIBS=-lgdi32 -luser32 -lopengl32
BDIR=./build/
DEPS=
SOURCE=./src/matrix.c ./src/opengl_impl.c ./src/game.c ./src/shader.c ./src/render.c ./src/window.c ./src/vector.c
MAIN=./src/main.c
INCLUDES=-Iinclude

run:
	$(CC) -Wall $(DEBS) $(LIBS) -o program.exe $(INCLUDES) $(SOURCE) $(MAIN)
	./program.exe

