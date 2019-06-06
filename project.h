#ifndef PROJECT_H
#define PROJECT_H
#include <iostream>
#include <ncurses.h>
#include <string>
#include <time.h>
using namespace std;

int debug(string str);

class Bomb
{
friend class World;
public:
	Bomb();
	void powerptr(int *p);
private:
	int *pow;
	bool bang;
	bool set;
	clock_t t;
};

class Player;

typedef struct location
{
	int x;
	int y;
	string item;
	Player *p;
	Player *temp;
 	Bomb *bptr;
	bool prop;
	bool breaked;
	bool walkable;
	bool breakable;
	bool pushable;
} location;

class Player
{
friend class World;
public:
    Player();
	void setxy(int , int);
	void powerup();
	void amountup();
	void setname(string );
	void teamchoose(int , int , int);
	void rolechoose(int , int , int);
	bool setted();
	void reset();
	void test();
private:
	string name;
	int role;
	int team, mode;
	int x, y, i;
	int maxpower, maxamount;
	int amount, pow;
	int kill, death, assist, money;
	bool drown;
	bool dead;
	bool set;
	Bomb *bomb;
	clock_t t;
};


class World
{
public:
	World();
	bool setted(int );
	void gameroom();
	void printroom();
	string mapchoose();
    void readmap(string);
	void mainmap();
    void resetitem(int , int);
    void setitem(string , int , int, int);
	string proptype();
	void printitem(int , int);
	void move(int , int , int , int , int , int);
	void setbomb(int );
	void checkbomb();
	void explode(int , int , Bomb *);
	void checkplayer();
	void quitgame();
	void end(int);
	void reset();
	void test();
private:
	WINDOW *game, *room, *win, *quit, *mapch, *testw;
	location **map;
	int ploc[4][2];
	Player p[4];
	clock_t t;
	time_t now;
	struct tm * timeinfo;
	int range_x, range_y, max_player;
};

#endif
