#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include "project.h"

void World::printitem(int x, int y)													//improvable
{
	if(map[x][y].bptr!=NULL&&map[x][y].bptr->bang==0){
		wattron(game,COLOR_PAIR(6));
		mvwprintw(game,x*5+1,y*10+1,"   ____   ");
		mvwprintw(game,x*5+2,y*10+1,"  /    \\  ");
		mvwprintw(game,x*5+3,y*10+1," (      ) ");
		mvwprintw(game,x*5+4,y*10+1,"  \\____/  ");
		mvwprintw(game,x*5+5,y*10+1,"          ");
		wattroff(game,COLOR_PAIR(6));
	}
	else if(map[x][y].bptr!=NULL&&map[x][y].bptr->bang==1){
		wattron(game,COLOR_PAIR(6));
		mvwprintw(game,x*5+1,y*10+1,"o o o o o ");
		mvwprintw(game,x*5+2,y*10+1,"oooooooooo");
		mvwprintw(game,x*5+3,y*10+1,"oooooooooo");
		mvwprintw(game,x*5+4,y*10+1,"oooooooooo");
		mvwprintw(game,x*5+5,y*10+1," o o o o o");
  		wattroff(game,COLOR_PAIR(6));

	}
	else if(map[x][y].prop==1){														//improvable
		if(map[x][y].item=="1"){
			wattron(game,COLOR_PAIR(0)|A_DIM);
			mvwprintw(game,x*5+1,y*10+1,"          ");
			mvwprintw(game,x*5+2,y*10+1,"    ==    ");
			mvwprintw(game,x*5+3,y*10+1,"   ====   ");
			mvwprintw(game,x*5+4,y*10+1,"  ======  ");
			mvwprintw(game,x*5+5,y*10+1,"          ");
   			wattroff(game,COLOR_PAIR(0)|A_DIM);
		}
		else if(map[x][y].item=="2"){
			wattron(game,COLOR_PAIR(0)|A_DIM);
			mvwprintw(game,x*5+1,y*10+1,"          ");
			mvwprintw(game,x*5+2,y*10+1,"    ==    ");
			mvwprintw(game,x*5+3,y*10+1,"   ====   ");
			mvwprintw(game,x*5+4,y*10+1,"    ==    ");
			mvwprintw(game,x*5+5,y*10+1,"          ");
   			wattroff(game,COLOR_PAIR(0)|A_DIM);
		}
		else if(map[x][y].item=="3"){
			wattron(game,COLOR_PAIR(0)|A_DIM);
			mvwprintw(game,x*5+1,y*10+1,"   ____   ");
			mvwprintw(game,x*5+2,y*10+1," /--ww--\\  ");
			mvwprintw(game,x*5+3,y*10+1," | $100 |  ");
			mvwprintw(game,x*5+4,y*10+1," |______|  ");
			mvwprintw(game,x*5+5,y*10+1,"          ");
   			wattroff(game,COLOR_PAIR(0)|A_DIM);
		}
		else if(map[x][y].item=="4"){
			wattron(game,COLOR_PAIR(0)|A_DIM);
			mvwprintw(game,x*5+1,y*10+1,"   ____   ");
			mvwprintw(game,x*5+2,y*10+1," /--ww--\\  ");
			mvwprintw(game,x*5+3,y*10+1," | $500 |  ");
			mvwprintw(game,x*5+4,y*10+1," |______|  ");
			mvwprintw(game,x*5+5,y*10+1,"          ");
   			wattroff(game,COLOR_PAIR(0)|A_DIM);
		}
		else{
			wattron(game,COLOR_PAIR(7));
			mvwprintw(game,x*5+1,y*10+1,"          ");
			mvwprintw(game,x*5+2,y*10+1,"          ");
			mvwprintw(game,x*5+3,y*10+1,"          ");
			mvwprintw(game,x*5+4,y*10+1,"          ");
			mvwprintw(game,x*5+5,y*10+1,"          ");
   			wattroff(game,COLOR_PAIR(7));
		}
	}
	else {
		if(map[x][y].item=="B"){
			wattron(game,COLOR_PAIR(3));
			mvwprintw(game,x*5+1,y*10+1,"          ");
			mvwprintw(game,x*5+2,y*10+1,"   ====   ");
			mvwprintw(game,x*5+3,y*10+1,"   ====   ");
			mvwprintw(game,x*5+4,y*10+1,"   ====   ");
			mvwprintw(game,x*5+5,y*10+1,"          ");
   			wattroff(game,COLOR_PAIR(3));
		}
		else if(map[x][y].item=="Y"){
			wattron(game,COLOR_PAIR(7));
			mvwprintw(game,x*5+1,y*10+1,"          ");
			mvwprintw(game,x*5+2,y*10+1,"   ====   ");
			mvwprintw(game,x*5+3,y*10+1,"   =  =   ");
			mvwprintw(game,x*5+4,y*10+1,"   ====   ");
			mvwprintw(game,x*5+5,y*10+1,"          ");
   			wattroff(game,COLOR_PAIR(7));
		}
		else if(map[x][y].item=="T"){
			wattron(game,COLOR_PAIR(2));
			mvwprintw(game,x*5+1,y*10+1,"    /\\    ");
			mvwprintw(game,x*5+2,y*10+1,"   /XX\\   ");
			mvwprintw(game,x*5+3,y*10+1,"  /XAX/\\  ");
			mvwprintw(game,x*5+4,y*10+1," /A/X/XA\\ ");
   			wattroff(game,COLOR_PAIR(2));
			wattron(game,COLOR_PAIR(7));
			mvwprintw(game,x*5+5,y*10+1,"    ||    ");
   			wattroff(game,COLOR_PAIR(7));
		}
		else if(map[x][y].item=="X"){
			wattron(game,COLOR_PAIR(2));
			mvwprintw(game,x*5+1,y*10+1,"  ______  ");
			mvwprintw(game,x*5+2,y*10+1," /      \\ ");
			mvwprintw(game,x*5+3,y*10+1,"/________\\");
			mvwprintw(game,x*5+4,y*10+1,"| []  [] |");
			mvwprintw(game,x*5+5,y*10+1,"|________|");
   			wattroff(game,COLOR_PAIR(2));
		}
		else{
			wattron(game,COLOR_PAIR(7));
			mvwprintw(game,x*5+1,y*10+1,"          ");
			mvwprintw(game,x*5+2,y*10+1,"          ");
			mvwprintw(game,x*5+3,y*10+1,"          ");
			mvwprintw(game,x*5+4,y*10+1,"          ");
			mvwprintw(game,x*5+5,y*10+1,"          ");
   			wattroff(game,COLOR_PAIR(7));
		}
    }
    
	if(map[x][y].p!=NULL){
  		int i=map[x][y].p->name.size();
		char *name=new char [i+1];
  		strcpy (name,map[x][y].p->name.c_str());
		if(map[x][y].p->drown==0){
			if(map[x][y].p->team==0){
				wattron(game,COLOR_PAIR(1)|A_BOLD);
			}
			else if(map[x][y].p->team==1){
				wattron(game,COLOR_PAIR(4)|A_BOLD);
			}
			else if(map[x][y].p->team==2){
				wattron(game,COLOR_PAIR(2)|A_BOLD);
			}
			else if(map[x][y].p->team==3){
				wattron(game,COLOR_PAIR(5)|A_BOLD);
			}
			mvwprintw(game,x*5+2,y*10+5,    "[]");
			mvwprintw(game,x*5+3,y*10+4,   "====");
			mvwprintw(game,x*5+4,y*10+5,    "/\\");
			mvwprintw(game,x*5+5,y*10+6-i/2,"%s",name);
   			if(map[x][y].p->team==0){
				wattroff(game,COLOR_PAIR(1)|A_BOLD);
			}
			else if(map[x][y].p->team==1){
				wattroff(game,COLOR_PAIR(4)|A_BOLD);
			}
			else if(map[x][y].p->team==2){
				wattroff(game,COLOR_PAIR(2)|A_BOLD);
			}
			else if(map[x][y].p->team==3){
				wattroff(game,COLOR_PAIR(5)|A_BOLD);
			}
		}
		else{
			wattron(game,COLOR_PAIR(6));
			mvwprintw(game,x*5+1,y*10+3+now%3,  "oooo");
			mvwprintw(game,x*5+2,y*10+2+now%3, "oooooo");
			mvwprintw(game,x*5+3,y*10+1+now%3,"oooooooo");
			mvwprintw(game,x*5+4,y*10+2+now%3, "oooooo");
			mvwprintw(game,x*5+5,y*10+3+now%3,  "oooo");
			wattroff(game,COLOR_PAIR(6));
			if(map[x][y].p->team==0){
				wattron(game,COLOR_PAIR(1)|A_BOLD);
			}
			else if(map[x][y].p->team==1){
				wattron(game,COLOR_PAIR(4)|A_BOLD);
			}
			else if(map[x][y].p->team==2){
				wattron(game,COLOR_PAIR(2)|A_BOLD);
			}
			else if(map[x][y].p->team==3){
				wattron(game,COLOR_PAIR(5)|A_BOLD);
			}
			mvwprintw(game,x*5+2,y*10+4+now%3, "[]");
			mvwprintw(game,x*5+3,y*10+3+now%3,"====");
			mvwprintw(game,x*5+4,y*10+4+now%3, "/\\");
			mvwprintw(game,x*5+5,y*10+5-i/2,"%s",name);
   			if(map[x][y].p->team==0){
				wattroff(game,COLOR_PAIR(1)|A_BOLD);
			}
			else if(map[x][y].p->team==1){
				wattroff(game,COLOR_PAIR(4)|A_BOLD);
			}
			else if(map[x][y].p->team==2){
				wattroff(game,COLOR_PAIR(2)|A_BOLD);
			}
			else if(map[x][y].p->team==3){
				wattroff(game,COLOR_PAIR(5)|A_BOLD);
			}
		}
	}
	if(map[x][y].item=="I"){
		wattron(game,COLOR_PAIR(2));
		mvwprintw(game,x*5+1,y*10+1,"          ");
		mvwprintw(game,x*5+2,y*10+1," \\\\ /\\ /\\ ");
		mvwprintw(game,x*5+3,y*10+1," //\\//\\/\\ ");
		mvwprintw(game,x*5+4,y*10+1," \\\\/\\\\\\// ");
		mvwprintw(game,x*5+5,y*10+1," //\\//\\\\\\ ");
		wattroff(game,COLOR_PAIR(2));
	}
}
void World::end(int winteam)
{
	win=newwin(25,86,(LINES-25)/2,(COLS-86)/2);
	nodelay(win,TRUE);
    box(win,'|','-');
	mvwprintw(win,3,10,"");
	mvwprintw(win,4,10,"");
	mvwprintw(win,5,10,"");
	mvwprintw(win,6,10,"");
	mvwprintw(win,7,10,"");
	mvwprintw(win,9,23,"|   I D   |  kill  |  dead  |  assist  |   Money   |");
	for(int i=0,j=0;j<4;j++){
		if(p[j].set==1){
			char *name=new char [p[j].name.size()+1];
			strcpy (name,p[j].name.c_str());
			wattron(win,COLOR_PAIR(6)|A_BOLD);
			mvwprintw(win,10+i,10," %d ",i+1);
			wattroff(win,COLOR_PAIR(6)|A_BOLD);
			if(p[j].team==winteam){
				wattron(win,COLOR_PAIR(3)|A_BOLD);
				mvwprintw(win,10+i,14,"  W I N  ");
			}
			else{
				wattron(win,COLOR_PAIR(4)|A_BOLD);
				mvwprintw(win,10+i,14," L O S E ");
			}
			mvwprintw(win,10+i,25," %-8s ", name);
			mvwprintw(win,10+i,35,"  %2d       %2d        %2d     ", p[j].kill, p[j].death, p[j].assist);
			mvwprintw(win,10+i,64,"  %4d", p[i].money);
			i++;
		}
		
	}
	wattroff(win,COLOR_PAIR(3)|COLOR_PAIR(4));
	wattroff(win,A_BOLD);
	wattron(win,COLOR_PAIR(7)|A_REVERSE);
	mvwprintw(win,24,(COLS-26)/2,"Please press enter to quit");
	wattron(win,COLOR_PAIR(7)|A_REVERSE);
    touchwin(win);
    wrefresh(win);
	sleep(1);
	while(getch()!='\r'){}
	touchwin(win);
	werase(win);
	wrefresh(win);
	touchwin(game);
	werase(game);
	wrefresh(game);
	reset();
	gameroom();
	readmap(mapchoose());
	mainmap();
}
void World::quitgame()
{
	int x;
	quit=newwin(10,60,(LINES-10)/2,(COLS-60)/2);
    box(quit,'|','-');
	mvwprintw(quit,3,14,"Are you suer to quit the game???");
	mvwprintw(quit,5,14,"       ------       ------      ");
	mvwprintw(quit,6,14,"      |yes(y)|     | no(n)|     ");
	mvwprintw(quit,7,14,"       ------       ------      ");
    touchwin(quit);
    wrefresh(quit);
	nodelay(quit,FALSE);
	while(1){
		x=getch();
		if(x=='y'){
	    	touchwin(stdscr);
		    endwin();
			exit (1);
		}
		else if(x=='n'){
			delwin(quit);
			break;
		}
	}
}
void World::outofrange(int range_x, int range_y)
{
	reminder=newwin(5,30,(LINES-10)/2,(COLS-30)/2);
    box(reminder,'|','-');
	mvwprintw(reminder,2,5,"Screen out of range!");
    touchwin(reminder);
    wrefresh(reminder);
	nodelay(reminder,FALSE);
	while((LINES < range_x)||(COLS < range_y)){
		debug("screen out of range");
	    wrefresh(reminder);
	    usleep(50000);
	}
	delwin(reminder);
}