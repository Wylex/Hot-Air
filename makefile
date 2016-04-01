CC=g++
CFLAGS= -lsfml-graphics -lsfml-window -lsfml-system

OBJECTS = .main.o .World.o .Ballon.o .Bird.o .Score.o .FPS.o

start: $(OBJECTS)
	$(CC) -std=c++11 .*.o $(CFLAGS)

.main.o: main.cpp World.h
	$(CC) -std=c++11 -o $@ -c main.cpp

.World.o: World.cpp World.h Bird.h Ballon.h FPS.h Score.h
	$(CC) -std=c++11 -o $@ -c World.cpp

.Ballon.o: Ballon.cpp Ballon.h
	$(CC) -std=c++11 -o $@ -c Ballon.cpp

.Bird.o: Bird.cpp Bird.h
	$(CC) -std=c++11 -o $@ -c Bird.cpp

.Score.o: Score.cpp Score.h
	$(CC) -std=c++11 -o $@ -c Score.cpp

.FPS.o: FPS.cpp FPS.h
	$(CC) -std=c++11 -o $@ -c FPS.cpp
