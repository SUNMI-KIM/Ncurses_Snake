#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string map = "";
    string line;
    ifstream file("map.txt");
    if(file.is_open()){
        while(getline(file, line)) {
            map += line;
            map += "\n";
        }  
    }
    const char * MAP = map.c_str();
    initscr();     // curses 모드 시작
    start_color(); // color 사용 선언
    init_pair(1, COLOR_RED, COLOR_WHITE); // 색 attribute 설정 (글자 색, 글자 배경 색)
    attron(COLOR_PAIR(1));   // Attribute 적용
    printw(MAP);   // Hello world 출력
    attroff(COLOR_PAIR(1));  // Attribute 해제
    refresh();               // 실제 스크린에 출력
    getch();                 // 사용자 입력 대기
    endwin();                // curses 모드 종료
    return 0;
}