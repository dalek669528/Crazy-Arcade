CC = g++
OBJS = world.cpp room.cpp Bomb.cpp graphic.cpp Player.cpp main.cpp
TARGETS = project

all: $(TARGETS)

# $(OBJS).o: $(OBJS).c
# 	$(CC) -c -o $@ $<

project: $(OBJS)
	$(CC) -o $@ $^ -lncurses

clean:
# 	rm *.o
	rm $(TARGETS)
