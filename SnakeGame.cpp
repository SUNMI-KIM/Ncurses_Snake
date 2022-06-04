#include <ncurses.h>
#include <time.h>
#include <string>
#include <iostream>
using namespace std;

class Snake
{
    public:
        int head_x, head_y;
        int snake_length = 3;
        Snake(int x, int y):head_x(x), head_y(y) {}
        char map[30][40] = {
            {9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9}
        };
        char mapTem[30][40];
        void showSnake() { // Snake의 모양에 따라 map의 원소를 변경
            for(int i = 0; i < 30; i++) {
                for(int j = 0; j < 40; j++) {
                    mapTem[i][j] = map[i][j];
                }
            }
            int l = snake_length;
            int x = head_x;
            int y = head_y;
            while(l--) {   // Snake head 방향에 따라 새로운 코드 구현 필요
                mapTem[x][y++] = 3;
            }   
        }
        void snakeGrow() { // Snake 길이 늘어나야하는 순간에 수동적으로 실행해야 하는 함수
            snake_length++;
        }
};

void color() {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_RED);
    init_pair(4, COLOR_WHITE, COLOR_BLUE);
    init_pair(5, COLOR_GREEN, COLOR_GREEN);
    init_pair(6, COLOR_RED, COLOR_RED);
}

int main() {
    initscr();
    color();
    resize_term(35,80);
    border('@', '@', '@', '@', '@', '@', '@', '@');
    refresh();

    Snake MainSnake = Snake(15, 20); // Snake head 초기에 가장 중앙에 배치함

    time_t start = time(NULL);

    time_t tmp = start + 0.5;
    time_t prev = start;

    while(time(NULL) - start < 60) {
        if (prev >= tmp) {
            prev = time(NULL);
            tmp = prev + 0.5;
            MainSnake.showSnake();           // 변경사항 생길 때마다 실행해야함
            int key;
            noecho();
            key = getch();
            switch(key){
                case(0402): // KEY_DOWN
                    MainSnake.head_x += 1;
                    break;
                case(0403): // KEY_UP
                    MainSnake.head_x -= 1;
                    break;
                case(0404): // KEY_LEFT
                    MainSnake.head_y -= 1;
                    break;
                case(0405): // KEY_RIGHT
                    MainSnake.head_y += 1;
                    break;
                default:
                    endwin();
                    break;
            }
            start_color();
            init_pair(1, COLOR_GREEN, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            attroff(COLOR_PAIR(1));
            refresh();

            WINDOW *gameBoard = newwin(30, 40, 2, 2);
            for(int i = 0; i < 30; i++) {
                for(int j = 0; j < 40; j++) {
                    switch(MainSnake.mapTem[i][j]) {
                        case 0:
                            mvwprintw(gameBoard, i, j, " ");
                            break;
                        case 1:
                            mvwprintw(gameBoard, i, j, "#");
                            break;
                        case 3:
                            mvwprintw(gameBoard, i, j, "*");
                            break;
                        case 4:
                            mvwprintw(gameBoard, i, j, "@");
                            break;
                    }
                }
                wrefresh(gameBoard);
            }
            
            WINDOW *scoreBoard = newwin(14, 36, 3, 43);
            init_pair(3, COLOR_BLACK, COLOR_WHITE);
            wmove(scoreBoard, 0, 0);
            wattron(scoreBoard, COLOR_PAIR(3));
            wborder(scoreBoard, '|', '|', '-', '-', '*', '*', '*', '*');
            wbkgd(scoreBoard, COLOR_PAIR(3));
            mvwprintw(scoreBoard, 3, 3, "body: %d", MainSnake.snake_length);
            mvwprintw(scoreBoard, 4, 3, "grow: %d", MainSnake.snake_length);
            mvwprintw(scoreBoard, 5, 3, "poison: %d", MainSnake.snake_length);
            mvwprintw(scoreBoard, 6, 3, "gate: %d", MainSnake.snake_length);
            wrefresh(scoreBoard);

            WINDOW *missionBoard = newwin(14, 36, 18, 43);
            wbkgd(missionBoard, COLOR_PAIR(6));
            init_pair(3, COLOR_BLACK, COLOR_WHITE);
            wmove(missionBoard, 0, 0);
            wattron(missionBoard, COLOR_PAIR(3));
            wborder(missionBoard, '|', '|', '-', '-', '*', '*', '*', '*');
            wbkgd(missionBoard, COLOR_PAIR(3));
            mvwprintw(missionBoard, 3, 3, "body: %d", MainSnake.snake_length);
            mvwprintw(missionBoard, 4, 3, "grow: %d", MainSnake.snake_length);
            mvwprintw(missionBoard, 5, 3, "poison: %d", MainSnake.snake_length);
            mvwprintw(missionBoard, 6, 3, "gate: %d", MainSnake.snake_length);
            wrefresh(missionBoard);
        }
    }
    endwin();
    
    return 0;

}
