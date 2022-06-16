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

