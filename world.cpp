#include <fstream>
#include <cstdlib>
#include <utility>
#include "project.h"

World::World()
{
	map=NULL;
	for(int i=0;i<4;i++){
		ploc[i][0]=0;
		ploc[i][1]=0;
	}
	t=clock();
	time(&now);
 	timeinfo=localtime(&now);
	range_x=0;
	range_y=0;
	max_player=0;
}
void World::readmap(char *filename)
{
	ifstream infile(filename);
	if (infile.fail())
	{
		cout << "Map " << filename << " does not exist !!"<< endl;
		endwin();
		exit (EXIT_FAILURE);
	}
	infile>>range_x>>range_y;
	string mapf[range_x][range_y];
	map=new location *[range_x];
	for(int i=0;i<range_x;i++){
		map[i]=new location [range_y];
	}
	char item;
	for(int i=0;i<range_x;i++){
		infile.get();
		infile.get();
		for(int j=0;j<range_y;j++){
			infile.get(item);
			mapf[i][j]=item;
			resetitem(i,j);
			setitem(mapf[i][j],i,j,0);
		}
	}
	infile.close();
	// debug(string("read map ") + filename);
	// endwin();
	if((LINES < (range_x*5-3)) || (COLS < (range_y*10-2))){
		endwin();
		exit(0);
	}
	game=newwin(range_x*5+3,range_y*10+2,(LINES-range_x*5-3)/2,(COLS-range_y*10-2)/2);
 	nodelay(game,TRUE);
	box(game,'|','-');
	swap(ploc[3],ploc[1]);
	// debug(to_string(range_x) + " : " + to_string(range_x) + " : " + to_string(LINES) + " : " + to_string(COLS));
	for(int i=0;i<4;i++){
		if(p[i].set==1){
			setitem("p",ploc[i][0],ploc[i][1],i);
		}
	}
}
void World::resetitem(int x, int y)
{
		map[x][y].x=x;
		map[x][y].y=y;
		map[x][y].item="n";
		map[x][y].p=NULL;
		map[x][y].temp=NULL;
		map[x][y].bptr=NULL;
		map[x][y].prop=0;
		map[x][y].walkable=0;
		map[x][y].breakable=0;
		map[x][y].pushable=0;
		map[x][y].breaked=0;
}
void World::mainmap()
{
	for(int i=0;i<range_x;i++){
		for(int j=0;j<range_y;j++){
			printitem(i,j);
		}
	}
	t=clock();
	time(&now);
 	timeinfo=localtime(&now);
 	wattron(game,A_REVERSE);
	mvwprintw(game,range_x*5+1,range_y*5-24,"The current date/time is: %s",asctime(timeinfo));
	wattroff(game,A_REVERSE);
	touchwin(game);
    wrefresh(game);
}
void World::setitem(string item, int x, int y, int i=0)
{
	if(item=="p"){
		map[x][y].p=&p[i];
		p[i].setxy(x,y);
	}
	else if(item=="prop"){
		map[x][y].item=proptype();
		if(map[x][y].item=="n"){
			map[x][y].prop=0;
		}
		else{
			map[x][y].prop=1;
		}
		map[x][y].walkable=1;
		map[x][y].breakable=0;
		map[x][y].pushable=0;
	}
	else{
		map[x][y].p=NULL;
		map[x][y].bptr=NULL;
		if(item=="B"){
			map[x][y].item=item;
			map[x][y].walkable=0;
			map[x][y].breakable=1;
			map[x][y].pushable=0;
		}
		else if(item=="Y"){
			if(map[x][y].item!="I"){
				map[x][y].item=item;
			}
			map[x][y].walkable=0;
			map[x][y].breakable=1;
			map[x][y].pushable=1;
			map[x][y].prop=0;
		}
		else if(item=="X"||item=="T"){
			map[x][y].item=item;
			map[x][y].walkable=0;
			map[x][y].breakable=0;
			map[x][y].pushable=0;
		}
		else if(item=="I"){
			map[x][y].item=item;
			map[x][y].walkable=1;
			map[x][y].breakable=0;
			map[x][y].pushable=0;
		}
		else{
			if(item=="P"){
				ploc[max_player][0]=x;
				ploc[max_player][1]=y;
				max_player++;
			}
			map[x][y].item="n";
			map[x][y].walkable=1;
			map[x][y].breakable=0;
			map[x][y].pushable=0;
			map[x][y].breaked=0;
		}
	}
}
void World::move(int mov, int up, int down, int left, int right, int i)
{
	if(p[i].drown==0&&p[i].dead==0){
		if(mov==up){
			if(p[i].x>0&&map[p[i].x-1][p[i].y].walkable==1){
				if(i==map[p[i].x][p[i].y].p->i){
					map[p[i].x][p[i].y].p=map[p[i].x][p[i].y].temp;
				}
				map[p[i].x][p[i].y].temp=NULL;
				if(map[p[i].x-1][p[i].y].p!=NULL){
					map[p[i].x-1][p[i].y].temp=map[p[i].x-1][p[i].y].p;
					if(map[p[i].x-1][p[i].y].p->drown==1){
						if(map[p[i].x-1][p[i].y].p->team==p[i].team){
							map[p[i].x-1][p[i].y].p->drown=0;
							p[i].assist++;
						}
						else{
							map[p[i].x-1][p[i].y].p->dead=1;
							map[p[i].x-1][p[i].y].p->death++;
							map[p[i].x-1][p[i].y].temp=NULL;
							p[i].kill++;
						}
					}
				}
				setitem("p",p[i].x-1,p[i].y,i);
			}
			else if(p[i].x>1&&map[p[i].x-1][p[i].y].pushable==1&&map[p[i].x-2][p[i].y].walkable==1&&map[p[i].x-2][p[i].y].p==NULL){
				if(i==map[p[i].x][p[i].y].p->i){
					map[p[i].x][p[i].y].p=map[p[i].x][p[i].y].temp;
				}
				map[p[i].x][p[i].y].temp=NULL;
				setitem("n",p[i].x-1,p[i].y);
				setitem("p",p[i].x-1,p[i].y,i);
				setitem("Y",p[i].x-1,p[i].y);
			}
		}
		else if(mov==down){
			if(p[i].x<range_x-1&&map[p[i].x+1][p[i].y].walkable==1){
				if(i==map[p[i].x][p[i].y].p->i){
					map[p[i].x][p[i].y].p=map[p[i].x][p[i].y].temp;
				}
				map[p[i].x][p[i].y].temp=NULL;
				if(map[p[i].x+1][p[i].y].p!=NULL){
					map[p[i].x+1][p[i].y].temp=map[p[i].x+1][p[i].y].p;
					if(map[p[i].x+1][p[i].y].p->drown==1){
						if(map[p[i].x+1][p[i].y].p->team==p[i].team){
							map[p[i].x+1][p[i].y].p->drown=0;
							p[i].assist++;
						}
						else{
							map[p[i].x+1][p[i].y].p->dead=1;
							map[p[i].x+1][p[i].y].p->death++;
							map[p[i].x+1][p[i].y].temp=NULL;
							p[i].kill++;
						}
					}
				}
				setitem("p",p[i].x+1,p[i].y,i);
			}
			else if(p[i].x<range_x-2&&map[p[i].x+1][p[i].y].pushable==1&&map[p[i].x+2][p[i].y].walkable==1&&map[p[i].x+2][p[i].y].p==NULL){
				if(i==map[p[i].x][p[i].y].p->i){
					map[p[i].x][p[i].y].p=map[p[i].x][p[i].y].temp;
				}
				map[p[i].x][p[i].y].temp=NULL;
				setitem("n",p[i].x+1,p[i].y);
				setitem("p",p[i].x+1,p[i].y,i);
				setitem("Y",p[i].x+1,p[i].y);
			}
		}
		else if(mov==left){
			if(p[i].y>0&&map[p[i].x][p[i].y-1].walkable==1){
				if(i==map[p[i].x][p[i].y].p->i){
					map[p[i].x][p[i].y].p=map[p[i].x][p[i].y].temp;
				}
				map[p[i].x][p[i].y].temp=NULL;
				if(map[p[i].x][p[i].y-1].p!=NULL){
					map[p[i].x][p[i].y-1].temp=map[p[i].x][p[i].y-1].p;
					if(map[p[i].x][p[i].y-1].p->drown==1){
						if(map[p[i].x][p[i].y-1].p->team==p[i].team){
							map[p[i].x][p[i].y-1].p->drown=0;
							p[i].assist++;
						}
						else{
							map[p[i].x][p[i].y-1].p->dead=1;
							map[p[i].x][p[i].y-1].p->death++;
							map[p[i].x][p[i].y-1].temp=NULL;
							p[i].kill++;
						}
					}
				}
				setitem("p",p[i].x,p[i].y-1,i);
			}
			else if(p[i].y>1&&map[p[i].x][p[i].y-1].pushable==1&&map[p[i].x][p[i].y-2].walkable==1&&map[p[i].x][p[i].y-2].p==NULL){
				if(i==map[p[i].x][p[i].y].p->i){
					map[p[i].x][p[i].y].p=map[p[i].x][p[i].y].temp;
				}
				map[p[i].x][p[i].y].temp=NULL;
				setitem("n",p[i].x,p[i].y-1);
				setitem("p",p[i].x,p[i].y-1,i);
				setitem("Y",p[i].x,p[i].y-1);
			}
		}
		else if(mov==right){
			if(p[i].y<range_y-1&&map[p[i].x][p[i].y+1].walkable==1){
				if(i==map[p[i].x][p[i].y].p->i){
					map[p[i].x][p[i].y].p=map[p[i].x][p[i].y].temp;
				}
				map[p[i].x][p[i].y].temp=NULL;
				if(map[p[i].x][p[i].y+1].p!=NULL){
					map[p[i].x][p[i].y+1].temp=map[p[i].x][p[i].y+1].p;
					if(map[p[i].x][p[i].y+1].p->drown==1){
						if(map[p[i].x][p[i].y+1].p->team==p[i].team){
							map[p[i].x][p[i].y+1].p->drown=0;
							p[i].assist++;
						}
						else{
							map[p[i].x][p[i].y+1].p->dead=1;
							map[p[i].x][p[i].y+1].p->death++;
							map[p[i].x][p[i].y+1].temp=NULL;
							p[i].kill++;
						}
					}
				}
				setitem("p",p[i].x,p[i].y+1,i);
			}
			else if(p[i].y<range_y-2&&map[p[i].x][p[i].y+1].pushable==1&&map[p[i].x][p[i].y+2].walkable==1&&map[p[i].x][p[i].y+2].p==NULL){
				if(i==map[p[i].x][p[i].y].p->i){
					map[p[i].x][p[i].y].p=map[p[i].x][p[i].y].temp;
				}
				map[p[i].x][p[i].y].temp=NULL;
				setitem("n",p[i].x,p[i].y+1);
				setitem("p",p[i].x,p[i].y+1,i);
				setitem("Y",p[i].x,p[i].y+1);
			}
		}
	}
}
void World::setbomb(int i)
{
	if(p[i].drown==0&&p[i].dead==0){
		for(int j=0;j<p[i].amount;j++){
			if(p[i].bomb[j].set==0){
				map[p[i].x][p[i].y].walkable=0;
				p[i].bomb[j].t=t;
				map[p[i].x][p[i].y].bptr=&(p[i].bomb[j]);
				p[i].bomb[j].set=1;
				p[i].bomb[j].bang=0;
				break;
			}
		}
	}
}
void World::checkbomb()
{
	for(int i=0;i<range_x;i++){
		for(int j=0;j<range_y;j++){
			if(map[i][j].bptr!=NULL&&map[i][j].bptr->bang==1){
				if(((float)(t-map[i][j].bptr->t))/CLOCKS_PER_SEC>=0.5){
					map[i][j].bptr->set=0;
	 				map[i][j].bptr=NULL;
	 				map[i][j].walkable=1;
				}
			}
		}
	}
	for(int i=0;i<range_x;i++){
		for(int j=0;j<range_y;j++){
			if(map[i][j].bptr!=NULL&&map[i][j].bptr->bang==0){
				if(((float)(t-map[i][j].bptr->t))/CLOCKS_PER_SEC>=2){
					explode(i, j, map[i][j].bptr);
					for(int k=0;k<range_x;k++){
						for(int l=0;l<range_y;l++){
							map[k][l].breaked=0;
						}
					}
				}
			}
		}
	}
}
void World::explode(int i, int j, Bomb *b)
{
	map[i][j].walkable=1;
	b->t=t;
	b->bang=1;
	for(int k=1;k<=*b->pow;k++){
		if(i+k<range_x){
			if(map[i+k][j].walkable==1&&map[i+k][j].breaked==0){
				map[i+k][j].prop=0;
				map[i+k][j].bptr=b;
			}
			else if(map[i+k][j].bptr!=NULL&&map[i+k][j].bptr->bang==0){
				explode(i+k, j, map[i+k][j].bptr);
			}
			else if(map[i+k][j].breakable==0||map[i+k][j].breaked==1){
				break;
			}
			else if(map[i+k][j].breakable==1){
				map[i+k][j].breaked=1;
				setitem("prop",i+k,j);
				map[i+k][j].bptr=b;
				break;
			}
		}
	}
	for(int k=1;k<=*b->pow;k++){
		if(i-k>=0){
			if(map[i-k][j].walkable==1&&map[i-k][j].breaked==0){
				map[i-k][j].prop=0;
				map[i-k][j].bptr=b;
			}
			else if(map[i-k][j].bptr!=NULL&&map[i-k][j].bptr->bang==0){
				explode(i-k, j, map[i-k][j].bptr);
			}
			else if(map[i-k][j].breakable==0||map[i-k][j].breaked==1){
				break;
			}
			else if(map[i-k][j].breakable==1){
				map[i-k][j].breaked=1;
				setitem("prop",i-k,j);
				map[i-k][j].bptr=b;
				break;
			}
		}
	}
	for(int k=1;k<=*b->pow;k++){
		if(j+k<range_y){
			if(map[i][j+k].walkable==1&&map[i][j+k].breaked==0){
				map[i][j+k].prop=0;
				map[i][j+k].bptr=b;
			}
			else if(map[i][j+k].bptr!=NULL&&map[i][j+k].bptr->bang==0){
				explode(i, j+k, map[i][j+k].bptr);
			}
			else if(map[i][j+k].breakable==0||map[i][j+k].breaked==1){
				break;
			}
			else if(map[i][j+k].breakable==1){
				map[i][j+k].breaked=1;
				setitem("prop",i,j+k);
				map[i][j+k].bptr=b;
				break;
			}
		}
	}
	for(int k=1;k<=*b->pow;k++){
		if(j-k>=0){
			if(map[i][j-k].walkable==1&&map[i][j-k].breaked==0){
				map[i][j-k].prop=0;
				map[i][j-k].bptr=b;
			}
			else if(map[i][j-k].bptr!=NULL&&map[i][j-k].bptr->bang==0){
				explode(i, j-k, map[i][j-k].bptr);
			}
			else if(map[i][j-k].breakable==0||map[i][j-k].breaked==1){
				break;
			}
			else if(map[i][j-k].breakable==1){
				map[i][j-k].breaked=1;
				setitem("prop",i,j-k);
				map[i][j-k].bptr=b;
				break;
			}
		}
	}
}
string World::proptype()
{
	int x;
	x=rand()%100;
	if(x>=0&&x<15){
		return "1";
	}
	else if(x>=15&&x<30){
		return "2";
	}
	else if(x>=30&&x<37){
		return "3";
	}
	else if(x>=37&&x<40){
		return "4";
	}
	else{
		return "n";
	}
}
void World::checkplayer()
{
	for(int i=0;i<4;i++){
		if(p[i].set==1){
			if(map[p[i].x][p[i].y].bptr!=NULL&&map[p[i].x][p[i].y].bptr->bang==1){
				p[i].drown=1;
				p[i].t=clock();
			}
			if(p[i].drown==1&&((float)(t-p[i].t))/CLOCKS_PER_SEC>=10&&p[i].dead==0){
				map[p[i].x][p[i].y].p=NULL;
				p[i].dead=1;
				p[i].death++;
			}
			if(map[p[i].x][p[i].y].prop==1){
				if(map[p[i].x][p[i].y].item=="1"){
					p[i].powerup();
				}
				else if(map[p[i].x][p[i].y].item=="2"){
					p[i].amountup();
				}
				else if(map[p[i].x][p[i].y].item=="3"){
					p[i].money+=100;
				}
				else if(map[p[i].x][p[i].y].item=="4"){
					p[i].money+=500;
				}
				map[p[i].x][p[i].y].prop=0;
			}
		}
	}
	int alive[4], j=0, winteam=0;
	for(int i=0;i<4;i++){
		if(p[i].set==1){
			if(p[i].dead==0){
				alive[j]=i;
				j++;
			}
		}
	}
	winteam=p[alive[0]].team;
	for(int i=0;i<j;i++){
		if(winteam!=p[alive[i]].team){
			winteam=-1;
		}
	}
	if(winteam!=-1){
		end(winteam);
	}
}
bool World::setted(int i)
{
	return p[i].set;
}
void World::reset()
{
	map=NULL;
	for(int i=0;i<4;i++){
		ploc[i][0]=0;
		ploc[i][1]=0;
	}
	t=clock();
	time(&now);
 	timeinfo=localtime(&now);
	range_x=0;
	range_y=0;
	max_player=0;
	for(int i=0;i<4;i++){
		p[i].reset();
	}
}
