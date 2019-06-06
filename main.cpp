#include "project.h"
#include "sockop.h"
#include <unistd.h>
#include <cstdlib>
#include <cstring>

void initial();
int kbhit ();

int connfd;
int debug(string str){
    // cout<<"str: "<<str<<"--\n";
    if(connfd == -1){
        return -1;
    }
    else{
        str+="\n";
        if(write(connfd, str.c_str(), str.size()) == -1){
            perror("Error: write()\n");
            return -1;
        }
        return 0;
    }
}

int main(int argc, char** argv) {

    if(argc == 3){
        connfd = connectsock(argv[1], argv[2], "tcp");
    }
    else if(argc == 2){
        connfd = connectsock("127.0.0.1", argv[1], "tcp");
    }
    else {
        connfd = -1;
    }
    
    initial();
    World w;
    int x;
    w.gameroom();
    w.readmap(w.mapchoose());
    w.mainmap();
    // endwin();
    while(1) {
        if (kbhit()) {
            x=getch();
            // cout<<x<<endl;
            w.checkplayer();
            w.checkbomb();
            switch (x){
                case 'w':
                case 's':
                case 'a':
                case 'd':
                    if(w.setted(0)){
                        w.move(x,'w','s','a','d',0);
                    }
                    break;
                case '\t':
                    if(w.setted(0)){
                        w.setbomb(0);
                    }
                    break;
                case KEY_UP:
                case KEY_DOWN:
                case KEY_LEFT:
                case KEY_RIGHT:
                    if(w.setted(1)){
                        w.move(x,KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT,1);
                    }
                    break;
                case ' ':
                    if(w.setted(1)){
                        w.setbomb(1);
                    }
                    break;
                case 'g':
                case 'b':
                case 'v':
                case 'n':
                    if(w.setted(2)){
                        w.move(x,'g','b','v','n',2);
                    }
                    break;
                case 'x':
                    if(w.setted(2)){
                        w.setbomb(2);
                    }
                    break;
                case 'o':
                case 'l':
                case 'k':
                case ';':
                    if(w.setted(3)){
                        w.move(x,'o','l','k',';',3);
                    }
                    break;
                case 'h':
                    if(w.setted(3)){
                        w.setbomb(3);
                    }
                    break;
                case 27:
                    w.quitgame();
            }
            w.mainmap();
        }
        else{
            w.checkplayer();
            w.checkbomb();
            w.mainmap();
        }
    }
    endwin();
    if(connfd != -1)
        close(connfd);
    return 0;
}

void initial()
{
    initscr();
    cbreak();       //unblocking keyboard intupt
    start_color();
    init_color(COLOR_BLACK, 100, 100, 100);
    init_pair(0,COLOR_BLACK,COLOR_BLACK);
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    init_pair(3,COLOR_YELLOW,COLOR_BLACK);
    init_pair(4,COLOR_BLUE,COLOR_BLACK);
    init_pair(5,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(6,COLOR_CYAN,COLOR_BLACK);
    init_pair(7,COLOR_WHITE,COLOR_BLACK);
    nonl();
    curs_set(0);
    nodelay(stdscr,TRUE);
    noecho();
    // echo();
    intrflush(stdscr,FALSE);
    keypad(stdscr,TRUE);
    refresh();
}
int kbhit()
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}
