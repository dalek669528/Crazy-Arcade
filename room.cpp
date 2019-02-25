#include "project.h"
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <fstream>

int kbhit(void);

void World::gameroom()
{
	int x;
	room=newwin(46,172,(LINES-46)/2,(COLS-172)/2);
	nodelay(room,TRUE);
	while(1) {
		printroom();
		if (kbhit()) {
			x=getch();
			switch (x){
				case '\t':
					if(p[0].setted()&&p[0].mode<3){
						p[0].mode++;
					}
					else if(!p[0].setted()){
						p[0].mode++;
						p[0].set=1;
						p[0].i=0;
						p[0].team=0;
					}
					break;
				case ' ':
					if(p[1].setted()&&p[1].mode<3){
						p[1].mode++;
					}
					else if(!p[1].setted()){
						p[1].mode++;
						p[1].set=1;
						p[1].i=1;
						p[1].team=1;
					}
					break;
				case 'x':
					if(p[2].setted()&&p[2].mode<3){
						p[2].mode++;
					}
					else if(!p[2].setted()){
						p[2].mode++;
						p[2].set=1;
						p[2].i=2;
						p[2].team=2;
					}
					break;
				case 'h':
					if(p[3].setted()&&p[3].mode<3){
						p[3].mode++;
					}
					else if(!p[3].setted()){
						p[3].mode++;
						p[3].set=1;
						p[3].i=3;
						p[3].team=3;
					}
					break;

				case 'a':
				case 'd':
					if(p[0].setted()&&p[0].mode==1){
						p[0].rolechoose(x,'a','d');
					}
					else if(p[0].setted()&&p[0].mode==2){
						p[0].teamchoose(x,'a','d');
					}
					break;
				case KEY_LEFT:
				case KEY_RIGHT:
					if(p[1].setted()&&p[1].mode==1){
						p[1].rolechoose(x,KEY_LEFT,KEY_RIGHT);
					}
					else if(p[1].setted()&&p[1].mode==2){
						p[1].teamchoose(x,KEY_LEFT,KEY_RIGHT);
					}
					break;
				case 'v':
				case 'n':
					if(p[2].setted()&&p[2].mode==1){
						p[2].rolechoose(x,'v','n');
					}
					else if(p[2].setted()&&p[2].mode==2){
						p[2].teamchoose(x,'v','n');
					}
					break;
				case 'k':
				case ';':
					if(p[3].setted()&&p[3].mode==1){
						p[3].rolechoose(x,'k',';');
					}
					else if(p[3].setted()&&p[3].mode==2){
						p[3].teamchoose(x,'k',';');
					}
					break;
				case 27:
					quitgame();
					break;
			}
			bool start=1;
			int pl=0;
			for(int i=0;i<4;i++){
				if(p[i].setted()){
					if(p[i].mode!=3){
						start=0;
					}
				pl++;
				}
			}
			if(pl>1&&start==1){
				printroom();
				return ;
			}
		}
	}
}
void World::printroom()
{
	char button[4][6];
	strcpy(button[0]," tab ");
	strcpy(button[1],"space");
	strcpy(button[2],"  x  ");
	strcpy(button[3],"  h  ");
    box(room,'+','+');
	mvwprintw(room,23,3," ------ ");
	mvwprintw(room,24,3,"| team |");
	mvwprintw(room,25,3," ------ ");
	for(int i=0;i<4;i++){
		if(!p[i].setted()){
			mvwprintw(room, 3,11+40*i,"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
			mvwprintw(room, 4,11+40*i,"O                            O");
			mvwprintw(room, 5,11+40*i,"O                            O");
			mvwprintw(room, 6,11+40*i,"O                            O");
			mvwprintw(room, 7,11+40*i,"O                            O");
			mvwprintw(room, 8,11+40*i,"O                            O");
			mvwprintw(room, 9,11+40*i,"O                            O");
			mvwprintw(room,10,11+40*i,"O                            O");
			mvwprintw(room,11,11+40*i,"O        Please press        O");
			mvwprintw(room,12,11+40*i,"O                            O");
			mvwprintw(room,13,11+40*i,"O       to join the game     O");
			mvwprintw(room,14,11+40*i,"O                            O");
			mvwprintw(room,15,11+40*i,"O                            O");
			mvwprintw(room,16,11+40*i,"O                            O");
			mvwprintw(room,17,11+40*i,"O                            O");
			mvwprintw(room,18,11+40*i,"O                            O");
			mvwprintw(room,19,11+40*i,"O                            O");
			mvwprintw(room,20,11+40*i,"O                            O");
			mvwprintw(room,21,11+40*i,"O                            O");
			mvwprintw(room,22,11+40*i,"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
			mvwaddstr(room,12,24+40*i,button[i]);
		}
		else if(p[i].role==0){
			mvwprintw(room, 3,11+40*i,"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
			mvwprintw(room, 4,11+40*i,"O      _________________      O");
			mvwprintw(room, 5,11+40*i,"O     /                 \\     O");
			mvwprintw(room, 6,11+40*i,"O    /                   \\    O");
			mvwprintw(room, 7,11+40*i,"O    |                   |    O");
			mvwprintw(room, 8,11+40*i,"O    |     o       o     |    O");
			mvwprintw(room, 9,11+40*i,"O    |         ^         |    O");
			mvwprintw(room,10,11+40*i,"O    \\___________________/    O");
			mvwprintw(room,11,11+40*i,"O   T T T   oo H oo   T T T   O");
			mvwprintw(room,12,11+40*i,"O   XXXXXX  oo H oo  XXXXXX   O");
			mvwprintw(room,13,11+40*i,"O   \\\\XX//  oo H oo  \\\\XX//   O");
			mvwprintw(room,14,11+40*i,"O        =============        O");
			mvwprintw(room,15,11+40*i,"O         XXXXXXXXXXX         O");
			mvwprintw(room,16,11+40*i,"O          XXX   XXX          O");
			mvwprintw(room,17,11+40*i,"O         XXXX   XXXX         O");
			mvwprintw(room,18,11+40*i,"O          ______________     O");
			mvwprintw(room,19,11+40*i,"O   power:[______________]    O");
			mvwprintw(room,20,11+40*i,"O    ball:[______________]    O");
			mvwprintw(room,21,11+40*i,"O                             O");
			mvwprintw(room,22,11+40*i,"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
		}
		else if(p[i].role==1){
			mvwprintw(room, 3,11+40*i,"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
			mvwprintw(room, 4,11+40*i,"O    //\\_______________/\\\\    O");
			mvwprintw(room, 5,11+40*i,"O   //             \\     \\\\   O");
			mvwprintw(room, 6,11+40*i,"O    |              \\    |    O");
			mvwprintw(room, 7,11+40*i,"O  ---               X   ---  O");
			mvwprintw(room, 8,11+40*i,"O  ---     o       o  X  ---  O");
			mvwprintw(room, 9,11+40*i,"O  ---         v       \\ ---  O");
			mvwprintw(room,10,11+40*i,"O   \\\\                   //   O");
			mvwprintw(room,11,11+40*i,"O   T T T   oo + oo   T T T   O");
			mvwprintw(room,12,11+40*i,"O   XXXXXX  oo + oo  XXXXXX   O");
			mvwprintw(room,13,11+40*i,"O   \\\\XX//  oo + oo  \\\\XX//   O");
			mvwprintw(room,14,11+40*i,"O        =============        O");
			mvwprintw(room,15,11+40*i,"O         XXXXXXXXXXX         O");
			mvwprintw(room,16,11+40*i,"O          XXX   XXX          O");
			mvwprintw(room,17,11+40*i,"O         XXXX   XXXX         O");
			mvwprintw(room,18,11+40*i,"O          __________         O");
			mvwprintw(room,19,11+40*i,"O   power:[__________]_       O");
			mvwprintw(room,20,11+40*i,"O    ball:[____________]      O");
			mvwprintw(room,21,11+40*i,"O                             O");
			mvwprintw(room,22,11+40*i,"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
		}
		else if(p[i].role==2){
			mvwprintw(room, 3,11+40*i,"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
			mvwprintw(room, 4,11+40*i,"O     /\\_______________/\\     O");
			mvwprintw(room, 5,11+40*i,"O    /        ___        \\    O");
			mvwprintw(room, 6,11+40*i,"O    |        _|_        |    O");
			mvwprintw(room, 7,11+40*i,"O  ---        _|_        ---  O");
			mvwprintw(room, 8,11+40*i,"O  ---     \\       /     ---  O");
			mvwprintw(room, 9,11+40*i,"O  ---        III        ---  O");
			mvwprintw(room,10,11+40*i,"O   \\\\                   //   O");
			mvwprintw(room,11,11+40*i,"O   T T T   oo v oo   T T T   O");
			mvwprintw(room,12,11+40*i,"O   XXXXXX  oo v oo  XXXXXX   O");
			mvwprintw(room,13,11+40*i,"O   \\\\XX//  oo v oo  \\\\XX//   O");
			mvwprintw(room,14,11+40*i,"O        =============        O");
			mvwprintw(room,15,11+40*i,"O         XXXXXXXXXXX         O");
			mvwprintw(room,16,11+40*i,"O          XXX   XXX          O");
			mvwprintw(room,17,11+40*i,"O         XXXX   XXXX         O");
			mvwprintw(room,18,11+40*i,"O          ____________       O");
			mvwprintw(room,19,11+40*i,"O   power:[____________]      O");
			mvwprintw(room,20,11+40*i,"O    ball:[__________]        O");
			mvwprintw(room,21,11+40*i,"O                             O");
			mvwprintw(room,22,11+40*i,"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
		}
		if(p[i].setted()){
			for(int j=0;j<p[i].pow;j++){
				wattron(room,A_REVERSE);
				mvwprintw(room,19,22+40*i+2*j,"  ");
				wattroff(room,A_REVERSE);
			}
			for(int j=0;j<p[i].amount;j++){
				wattron(room,A_REVERSE);
				mvwprintw(room,20,22+40*i+2*j,"  ");
				wattroff(room,A_REVERSE);
			}
		}
		if(p[i].setted()&&p[i].mode>1){
			mvwprintw(room,23,11+40*i,"   -----------------------   ");
			mvwprintw(room,24,11+40*i,"   |          %2d         |    ", p[i].team+1);
			mvwprintw(room,25,11+40*i,"   -----------------------   ");
		}
		if(p[i].mode==3){
			wattron(room,COLOR_PAIR(3));
			mvwprintw(room,27,11+40*i,"      -----------------      ");
			mvwprintw(room,28,11+40*i,"      |     READY     |      ");
			mvwprintw(room,29,11+40*i,"      -----------------      ");
			wattroff(room,COLOR_PAIR(3));
		}
	}
	
	wattron(room,COLOR_PAIR(7)|A_REVERSE);
	mvwprintw(room,44,(172-26)/2,"Please press esc to quit");
	wattroff(room,COLOR_PAIR(7)|A_REVERSE);
    touchwin(room);
    wrefresh(room);
}
char* World::mapchoose()
{
	ifstream infile("map.txt");
	if (infile.fail())
	{
		cout << "Map list does not exist !!"<< endl;
		endwin();
		exit (EXIT_FAILURE);
	}
	int i;
	infile>>i;
	string mapname[i];
	for(int j=0;j<i;j++){
		infile>>mapname[j];
	}
	infile.close();
	int x, j=0, size=0;
	mapch=newwin(7,50,LINES/2+10,(COLS-50)/2);
	nodelay(mapch,TRUE);
	box(mapch,'o','o');
	while(1) {
		size=mapname[j].size();
		char *name=new char [size+1];
  		strcpy (name,mapname[j].c_str());

		mvwprintw(mapch,1,23,"M A P");
		mvwprintw(mapch,3,14,"<                    >");
		mvwprintw(mapch,3,25-size/2,"%s",name);
		mvwprintw(mapch,5,2,"Please use \"<-\" \"->\" \"space\" to choose the map");
	    touchwin(mapch);
	    wrefresh(mapch);
		if (kbhit()) {
			x=getch();
			switch (x){
				case KEY_LEFT:
					j--;
					if(j<0){
						j+=i;
					}
					break;
				case KEY_RIGHT:
					j++;
					if(j>=i){
						j-=i;
					}
					break;
				case 27:
					quitgame();
					break;
				case ' ':
					mapname[j]=mapname[j]+".txt";
					char *filename=new char [size+5];
					strcpy (filename,mapname[j].c_str());
					sleep(1);
					touchwin(mapch);
					werase(mapch);
					wrefresh(mapch);
					touchwin(room);
					werase(room);
					wrefresh(room);
					return filename;
			}

		}
	}
}

void Player::test()
{
	WINDOW *testw;
	testw=newwin(60,50,20,0);
	box(testw,' ',' ');

	mvwprintw(testw,3+i*6,1,"i %d set %d mode %d", i, set, mode);
	mvwprintw(testw,4+i*6,1,"role %d team %d Bomb %d", role, team, sizeof(bomb));
	mvwprintw(testw,5+i*6,1,"x %d  y %d drown %d dead %d", x, y, drown, dead);
	mvwprintw(testw,6+i*6,1,"maxpower %d maxamount %d power %d amount %d", maxpower, maxamount, pow, amount);
	mvwprintw(testw,7+i*6,1,"kill %d death %d assist %d money %d", kill, death, assist, money);

	touchwin(testw);
	wrefresh(testw);
}
void World::test()
{
	testw=newwin(60,50,20,0);
	box(testw,' ',' ');

	mvwprintw(testw,1,1,"max_player %d",max_player);
	
	for(int i=0;i<4;i++){
		mvwprintw(testw,3+i*6,1,"i %d set %d mode %d", p[i].i, p[i].set, p[i].mode);
		mvwprintw(testw,4+i*6,1,"role %d team %d Bomb %d", p[i].role, p[i].team, sizeof(p[i].bomb));
		mvwprintw(testw,5+i*6,1,"x %d  y %d drown %d dead %d", p[i].x, p[i].y, p[i].drown, p[i].dead);
		mvwprintw(testw,6+i*6,1,"maxpower %d maxamount %d power %d amount %d", p[i].maxpower, p[i].maxamount, p[i].pow, p[i].amount);
		mvwprintw(testw,7+i*6,1,"kill %d death %d assist %d money %d", p[i].kill, p[i].death, p[i].assist, p[i].money);
	}
	touchwin(testw);
	wrefresh(testw);
}
