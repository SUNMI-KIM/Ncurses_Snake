#include "./map/map.cpp"
#include<ncurses.h>
#include<string>
#include<iostream>
using namespace std;
int main(){
    string s = "";
    for(int i=0; i<30; i++){
        for(int j=0; j<40; j++){
            s += to_string(map[i][j]);
        }
        s+= "\n";
    }
    const char * c = s.c_str();
    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    printw(c);
    attroff(COLOR_PAIR(1));
    refresh();
    getch();
    endwin();
    return 0;

}
