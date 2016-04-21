CC = g++
OPCOES_COMPILADOR= -lglut -lGLU -lGLEW -lSOIL -lGL
TODOS_ARQUIVOS_PONTOH = skybox.h garra.h
TODOS_ARQUIVOS_OBJ = main.o skybox.o garra.o

%.o: ../%.c $(TODOS_ARQUIVOS_PONTOH)
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	$(CC) -o main $^ $(OPCOES_COMPILADOR)

run: all
	./main

install:
	sudo apt-get install build-essential
	sudo apt-get install freeglut3-dev
	sudo apt-get install libglew1.6-dev
	sudo apt-get install libsoil-dev
	sudo apt-get install libsfml-dev

clean:
	rm *.o main
