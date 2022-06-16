#include <ncurses.h>
#include <time.h>
#include <string>
#include <iostream>
#include <vector>
#include <random>
#include "map.h"
#define WIDTH 40
#define HEIGHT 30
using namespace std;


int cur_stage = 0;

int sizeTarget[] = {5, 5, 6, 7};
int gateCount[] = {1, 1, 2, 3};
int plusCount[] = {1, 1, 2, 3};
int minusCount[] = {0, 0, 1, 2};

class Gate
{
public:
    pair<int,int> gate1;
    pair<int,int> gate2;
    Gate();
    ~Gate();
    void appearGate();
    void disappearGate();
};
class Snake
{
public:
    Snake(int x, int y);
    int head_x, head_y;
    int size = 3;
    char ahead; // n, s, e, w
    int snake_length = 3;
    vector <pair<int, int>> body;
    int item[2];
    int itemType[2] = {6, 7};

    int plusItemCount = 0;
    int minusItemCount = 0;
    int gateCount = 0;

    bool gameContinue;
    bool passingGate;
    bool isWall(int i, int j);
    bool diffItem(int f, int s);
    void setSnake();
    void showSnake();
    pair<int,int> moveSnake(Gate& gate);
    pair<int,int> throughGate(Gate& gate);
    void SpawnItem();
    void DelItem();
    bool UnableItem(int p1, int p2);
    bool GetItem(int f, int s);
    int dir[4][2] = {
        {0, -1} , {1, 0},
        {0, 1},  {-1, 0} 
    };
    vector<pair<int,int>> gateList;
    void readMap();
    char readPoint(int,int);
    bool checkSize();
    bool checkGateCount(int cnt);
    bool checkPlus(int cnt);
    bool checkMinus(int cnt);
};
bool Snake::checkSize(){ //목표 길이
    return sizeTarget[cur_stage] <= size;
}
// bool Snake::checkGateCount(int cnt){ // 게이트 이동횟수
//     return gateCount[cur_stage] <= cnt;
// }
bool Snake::checkPlus(int cnt){ // + 몇번 먹었는지
    return plusCount[cur_stage] <= cnt;
}
bool Snake::checkMinus(int cnt){ // - 몇번 먹었는지
    return minusCount[cur_stage] >= cnt;
}
bool Snake::isWall(int i, int j){
    for(int i=0; i<gateList.size(); i++){
        if (gateList[i].first == i && gateList[i].second == j) return false;
    }
    return true;
}
Snake::Snake(int x=20, int y=15)
{
    head_x = x;
    head_y = y;
    ahead = 'w';
    gameContinue = true;
    passingGate = false;
}
void Snake::setSnake()
{
    body.push_back(pair<int,int>(head_y,head_x));
    body.push_back(pair<int, int>(head_y, head_x+1));
    body.push_back(pair<int, int>(head_y, head_x+2));
}
void Snake::showSnake()
{
    for(int i = 0; i < body.size(); i++)
        map[cur_stage][body[i].first][body[i].second] = 3;
}
void Snake::SpawnItem() {
    srand(time(NULL));
    int itemShape = rand() % 2;
    item[0] = rand() % 30;
    item[1] = rand() % 40;
    while (!UnableItem(item[0], item[1])) {
        item[0] = rand() % 30;
        item[1] = rand() % 40;
    }
    map[cur_stage][item[0]][item[1]] = itemType[itemShape];
}
void Snake::DelItem()
{
    map[cur_stage][item[0]][item[1]] = 0;
    SpawnItem();
}
bool Snake::UnableItem(int p1, int p2) {
    if (map[cur_stage][p1][p2] != 0) {
        return false;
    }
    return true;
}
bool Snake::GetItem(int f, int s)
{
    if(f == item[0] && s == item[1]) return true;
    return false;
}
bool Snake::diffItem(int f, int s){ 
    if(map[cur_stage][f][s] == 6){
        return true;
    }
    else if(map[cur_stage][f][s] == 7){
        return false;
    }
    return true;
}
pair<int,int> Snake::moveSnake(Gate& gate)
{
    if (map[cur_stage][head_y][head_x]==5){
        passingGate = true;
        gateCount++;
        pair<int,int> otherGate = throughGate(gate);
        ahead = readPoint(otherGate.first, otherGate.second);
    }
    else if (map[cur_stage][head_y][head_x]==1)
        gameContinue = false; 
    else {
        body.insert(body.begin(), pair<int,int>(head_y,head_x));
        passingGate = false;
    }
    pair<int,int> pop_body = body[size];
    map[cur_stage][body.back().first][body.back().second] = 0;
    body.pop_back();     
    return pop_body; 
}
void Snake::readMap(){
    gateList.clear();
    for(int i=1; i<29; i++){
        for(int j=1; j<39; j++){
            if(map[cur_stage][i][j] == 1){
                gateList.push_back(pair<int,int>(i, j));
            }
        }
    }
}
char Snake::readPoint(int i, int j) // 머리의 방향을 정해주는 함수 , iswall == false
{
    int cnt_gate = 0;
    vector<int> d;
    char dchar[] = {'s', 'e', 'n', 'w'};
    for(int i=0; i<4; i++){
        if(map[cur_stage][i +dir[i][0]][j+dir[i][1]] == 0){
            cnt_gate ++;
            d.push_back(i);
        }
    }
    if(cnt_gate == 1) return dchar[d[0]];
    else{
        for(int i=0; i<d.size(); i++){
            if(ahead == dchar[d[i]]){
                return ahead;
            }
        }
        return dchar[d[0]]; // 미완성
    }
}
pair<int,int> Snake::throughGate(Gate& gate)
{
    body.erase(body.begin());
    // 머리 위치 변경
    if(head_y==gate.gate1.first && head_x==gate.gate1.second){
        head_y = gate.gate2.first;
        head_x = gate.gate2.second;
    }
    else if(head_y==gate.gate2.first && head_x==gate.gate2.second){
        head_y = gate.gate1.first;
        head_x = gate.gate1.second;
    }
    return pair<int,int>(head_y,head_y);

}

Gate::Gate()
{
    gate1 = pair<int,int>(0,0);
    gate2 = pair<int,int>(0,0);
}
Gate::~Gate()
{
}
void Gate::appearGate()
{
    do{    
        random_device rd1;
        mt19937 gen1(rd1());
        uniform_int_distribution<int> dis1(1, WIDTH-2);
        random_device rd2;
        mt19937 gen2(rd2());
        uniform_int_distribution<int> dis2(1, HEIGHT-2);
        int random = dis1(gen1);
        int random2 = dis2(gen2);
        if(random%4==0){
            gate1.first = random;
            gate1.second = 0;
        }
        else if(random%4==1){
            gate1.first = random;
            gate1.second = HEIGHT-1;
        }
        else if(random%4==2){
            gate1.first = 0;
            gate1.second = random2;
        }
        else{
            gate1.first = WIDTH-1;
            gate1.second = random2;
        }
        random = dis1(gen1);
        if(random%4==0){
            gate2.first = random;
            gate2.second = 0;
        }
        else if(random%4==1){
            gate2.first = random;
            gate2.second = HEIGHT-1;
        }
        else if(random%4==2){
            gate2.first = 0;
            gate2.second = random2;
        }
        else{
            gate2.first = WIDTH-1;
            gate2.second = random2;
        }
    }while(gate1.first==gate2.first && gate1.second==gate2.second);

    map[cur_stage][gate1.second][gate1.first] = 5;
    map[cur_stage][gate2.second][gate2.first] = 5;    
}
void Gate::disappearGate()
{
    map[cur_stage][gate1.second][gate1.first] = 1;
    map[cur_stage][gate2.second][gate2.first] = 1;
}

void color()
{
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_RED);
    init_pair(4, COLOR_WHITE, COLOR_BLUE);
    init_pair(5, COLOR_GREEN, COLOR_GREEN);
    init_pair(6, COLOR_RED, COLOR_RED);
}
int main()
{
    while(cur_stage<4) {
        Snake MainSnake = Snake();
        MainSnake.readMap();
        MainSnake.setSnake();
        MainSnake.SpawnItem();

        Gate gate = Gate();


        initscr();
        color();
        resize_term(35, 80);
        border('@', '@', '@', '@', '@', '@', '@', '@');
        refresh();


        WINDOW* gameBoard = newwin(30, 40, 2, 2);
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        attron(COLOR_PAIR(1));
        attroff(COLOR_PAIR(1));
        refresh();
        keypad(gameBoard, TRUE);

        WINDOW* scoreBoard = newwin(14, 36, 3, 43);
        init_pair(3, COLOR_BLACK, COLOR_WHITE);
        wmove(scoreBoard, 0, 0);
        wattron(scoreBoard, COLOR_PAIR(3));
        wborder(scoreBoard, '|', '|', '-', '-', '*', '*', '*', '*');
        wbkgd(scoreBoard, COLOR_PAIR(3));


        WINDOW* missionBoard = newwin(14, 36, 18, 43);
        wbkgd(missionBoard, COLOR_PAIR(6));
        init_pair(3, COLOR_BLACK, COLOR_WHITE);
        wmove(missionBoard, 0, 0);
        wattron(missionBoard, COLOR_PAIR(3));
        wborder(missionBoard, '|', '|', '-', '-', '*', '*', '*', '*');
        wbkgd(missionBoard, COLOR_PAIR(3));

        int count = 0;
        wtimeout(gameBoard, 300);
        while (MainSnake.gameContinue) {
            int key;
            noecho();
            key = wgetch(gameBoard);

            if(count++%30==0 && !MainSnake.passingGate)    
                gate.appearGate();

            switch(key){
            case(KEY_DOWN):
                if(MainSnake.ahead!='n' && MainSnake.ahead!='s') {
                    MainSnake.head_y += 1;
                    MainSnake.ahead = 's';
                    pair<int,int> s = MainSnake.moveSnake(gate);
                    if(MainSnake.GetItem(MainSnake.head_y,MainSnake.head_x)){
                        if(MainSnake.diffItem(MainSnake.head_y,MainSnake.head_x)){
                            pair<int,int> tmp = MainSnake.body[MainSnake.size];
                            MainSnake.body.insert(MainSnake.body.end(),s);
                            MainSnake.size++;
                            MainSnake.plusItemCount++;
                        }
                        else{
                            MainSnake.size--;
                            map[cur_stage][MainSnake.body.back().first][MainSnake.body.back().second] = 0;
                            MainSnake.body.pop_back();
                            MainSnake.minusItemCount++;
                        }
                    }
                }
                else if(MainSnake.ahead=='n') {
                    MainSnake.gameContinue = false;
                    cur_stage = 0;
                }
                break;
            case(KEY_UP):
                if(MainSnake.ahead!='s' && MainSnake.ahead !='n'){
                    MainSnake.head_y -= 1;
                    MainSnake.ahead = 'n';
                    pair<int,int> s = MainSnake.moveSnake(gate);
                    if(MainSnake.GetItem(MainSnake.head_y,MainSnake.head_x)){
                        if(MainSnake.diffItem(MainSnake.head_y,MainSnake.head_x)){
                            pair<int,int> tmp = MainSnake.body[MainSnake.size];
                            MainSnake.body.insert(MainSnake.body.end(),s);
                            MainSnake.size++;
                            MainSnake.plusItemCount++;
                        }
                        else{
                            MainSnake.size--;
                            map[cur_stage][MainSnake.body.back().first][MainSnake.body.back().second] = 0;
                            MainSnake.body.pop_back();
                            MainSnake.minusItemCount++;
                        }
                    }
                }
                else if(MainSnake.ahead=='s'){
                    MainSnake.gameContinue = false;
                    cur_stage = 0;
                }
                break;
            case(KEY_LEFT):
                if(MainSnake.ahead!='e' && MainSnake.ahead!='w'){
                    MainSnake.head_x -= 1;
                    MainSnake.ahead = 'w';
                    pair<int,int> s = MainSnake.moveSnake(gate);
                    if(MainSnake.GetItem(MainSnake.head_y,MainSnake.head_x)){
                        if(MainSnake.diffItem(MainSnake.head_y,MainSnake.head_x)){
                            pair<int,int> tmp = MainSnake.body[MainSnake.size];
                            MainSnake.body.insert(MainSnake.body.end(),s);
                            MainSnake.size++;
                            MainSnake.plusItemCount++;
                        }
                        else{
                            MainSnake.size--;
                            map[cur_stage][MainSnake.body.back().first][MainSnake.body.back().second] = 0;
                            MainSnake.body.pop_back();
                            MainSnake.minusItemCount++;
                        }
                    }
                }
                else if(MainSnake.ahead=='e') {
                    MainSnake.gameContinue = false;
                    cur_stage = 0;
                }
                break;
            case(KEY_RIGHT):
                if(MainSnake.ahead!='w'&&MainSnake.ahead!='e'){
                    MainSnake.head_x += 1;
                    MainSnake.ahead = 'e';
                    pair<int,int> s = MainSnake.moveSnake(gate);
                    if(MainSnake.GetItem(MainSnake.head_y,MainSnake.head_x)){
                        if(MainSnake.diffItem(MainSnake.head_y,MainSnake.head_x)){
                            pair<int,int> tmp = MainSnake.body[MainSnake.size];
                            MainSnake.body.insert(MainSnake.body.end(),s);
                            MainSnake.size++;
                            MainSnake.plusItemCount++;
                        }
                        else{
                            MainSnake.size--;
                            map[cur_stage][MainSnake.body.back().first][MainSnake.body.back().second] = 0;
                            MainSnake.body.pop_back();
                            MainSnake.minusItemCount++;
                        }
                    }
                }
                else if(MainSnake.ahead=='w'){
                    MainSnake.gameContinue = false;
                    cur_stage = 0;
                }
                break;
            case(-1):
                switch(MainSnake.ahead){
                    case('n'):
                        MainSnake.head_y -= 1;
                        break;
                    case('s'):
                        MainSnake.head_y += 1;
                        break;
                    case('e'):
                        MainSnake.head_x += 1;
                        break;
                    case('w'):
                        MainSnake.head_x -= 1;
                        break;
                }
                pair<int,int> s = MainSnake.moveSnake(gate);
                if(MainSnake.GetItem(MainSnake.head_y,MainSnake.head_x)){
                    if(MainSnake.diffItem(MainSnake.head_y,MainSnake.head_x)){
                        pair<int,int> tmp = MainSnake.body[MainSnake.size];
                        MainSnake.body.insert(MainSnake.body.end(),s);
                        MainSnake.size++;
                        MainSnake.plusItemCount++;
                    }
                    else{
                        MainSnake.size--;
                        map[cur_stage][MainSnake.body.back().first][MainSnake.body.back().second] = 0;
                        MainSnake.body.pop_back();
                        MainSnake.minusItemCount++;
                    }
                }
            }
            
            if(MainSnake.size < 3) return 0;
            MainSnake.showSnake();

            mvwprintw(scoreBoard, 3, 3, "body: %d", MainSnake.size);
            mvwprintw(scoreBoard, 4, 3, "grow: %d", MainSnake.plusItemCount);
            mvwprintw(scoreBoard, 5, 3, "poison: %d", MainSnake.minusItemCount);
            mvwprintw(scoreBoard, 6, 3, "gate: %d", MainSnake.snake_length);

            mvwprintw(missionBoard, 3, 13, "STAGE  %d", cur_stage);
            mvwprintw(missionBoard, 4, 3, "");
            mvwprintw(missionBoard, 5, 3, "~~ SIZE_TARGET : %d ~~", sizeTarget[cur_stage]);
            mvwprintw(missionBoard, 6, 3, "Size  : %d", MainSnake.size);
            mvwprintw(missionBoard, 7, 3, "~~ MINUSTARGET : %d ~~", minusCount[cur_stage]);
            mvwprintw(missionBoard, 8, 3, "Minus : %d", MainSnake.minusItemCount);
            mvwprintw(missionBoard, 9, 3, "~~ PLUS_TARGET : %d ~~", plusCount[cur_stage]);
            mvwprintw(missionBoard, 10, 3, "plus  : %d", MainSnake.plusItemCount);            
            wrefresh(scoreBoard); 
            wrefresh(missionBoard);
            wrefresh(gameBoard);
            for (int i = 0; i < 30; i++) {
                for (int j = 0; j < 40; j++) {
                    switch (map[cur_stage][i][j]) {
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
                    case 5:
                        mvwprintw(gameBoard, i, j, "D");
                        break;
                    case 6:
                        mvwprintw(gameBoard, i, j, "+");
                        break;
                    case 7:
                        mvwprintw(gameBoard, i, j, "-");
                        break;
                    }
                }
            }
            if(count%30==29){
                MainSnake.DelItem();
                if(!MainSnake.passingGate)
                    gate.disappearGate();
            }
            if(MainSnake.checkMinus(MainSnake.minusItemCount) && MainSnake.checkPlus(MainSnake.plusItemCount) && MainSnake.checkSize() && MainSnake.checkMinus(MainSnake.minusItemCount)){
                for(int i = 0; i < HEIGHT; i++) {
                    for(int j = 0; j < WIDTH; j++) {
                        map[cur_stage][i][j] = 0;
                    }
                }
                cur_stage++;
                break;
            }
            else if(MainSnake.size<3)
                cur_stage = 0;
        }
    }
    endwin();
    return 0;
}
