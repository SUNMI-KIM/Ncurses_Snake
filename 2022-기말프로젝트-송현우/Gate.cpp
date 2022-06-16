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

