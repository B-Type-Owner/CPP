#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>
using namespace std;

struct node{
    node * prev;
    node * next;
    int id;
    int abailty;
};

node leage_head[10];
node leage_tail[10];
node players[40000];
int player_cnt = 0;
int num_leages;
int num_of_players_for_leage;
vector<pair<int, int> > leage[10];
node *leage_middle[10];
int cnt = 0;

void init(int N, int L, int mAbility[])
{
    num_leages = L;
    player_cnt =0;
    num_of_players_for_leage = N / L;
    //vector insert, 
    deque<int> n;
    n.push_back(1);
    n.push_back(2);
    n.push_back(3);
    n.push_back(4);
    n.push_back(5);
    cout << n[2] << endl; 
    //deque

    for(int i = 0; i < L; ++i) {
        leage_head->next = nullptr;
        leage_tail->prev = nullptr;
        leage[i].clear();
        leage[i].resize(N / L);
    }

    cout << 1;
    for(int i = 0; i < N; ++i) {
        leage[i / num_of_players_for_leage][i % num_of_players_for_leage].first = mAbility[i];
        leage[i / num_of_players_for_leage][i % num_of_players_for_leage].second = -i;
    }
    cout << 2;
    int cnt = 0;
    for(int i = 0; i < L; ++i) {
        sort(leage[i].begin(), leage[i].end());
        node *temp = &leage_head[i];
        for(int j = 0; j < num_of_players_for_leage; ++j) {
            cout << leage[i][j].first << "," << leage[i][j].second << " ";
            node *player = &players[player_cnt++];
            player->abailty = leage[i][j].first;
            player->id = -leage[i][j].second;
            temp->next = player;
            player->prev = temp;
            temp = player;
            if(j == (num_of_players_for_leage / 2)) {
                leage_middle[i] = player;
            }
        }
        cout << endl;
        cout << cnt++;
        leage_tail[i].prev = temp;
        temp->next = &leage_tail[i];
    }
}

void printplayers() {
    for(int i = 0; i < num_leages; ++i) {
        node *temp = leage_head[i].next;
        while(temp != &leage_tail[i]) {
            cout << temp->id << "," << temp->abailty << " ";
            temp = temp->next;
        }
        cout << endl;
    }
}

//return less than middle : false else true
pair<int, int> changeNode(node *n1, node *n2, int leage_index) {
    printplayers();
    pair<int, int> ret;
    
    cout << cnt++ << " ."<< endl;

    //delete
    n1->prev->next = n1->next;
    n1->next->prev = n1->prev;
    n2->prev->next = n2->next;
    n2->next->prev = n2->prev;

    cout << cnt++ << endl;
    //insert n2 to leage_index
    int middle_toggle = -1;
    node *temp = &leage_head[leage_index];
    while(temp != nullptr) {
        node * next = temp->next;
        if(next == nullptr) {
            //temp == tail;
            temp->prev->next = n2;
            n2->prev = temp->prev;
            n2->next = temp;
            break;
        }

        if((next->abailty > n2->abailty) && (next->abailty == n2->abailty && next->id < n2->id)) {
            //insert next to temp
            cout << "!" << next-> abailty << n2->abailty << next->id << n2->id << "!" <<endl;
            temp->next = n2;
            n2->prev = temp;
            next->prev = n2;
            n2->next = next;
            break;
        }

        if(next == leage_middle[leage_index]) {
            middle_toggle = 1;
        }
        temp = next;
    }
    ret.first = 1;
    cout << cnt++ << endl;
    

    //insert n1 to leage_index + 1
    middle_toggle = -1;
    temp = leage_head[leage_index + 1].next;
    while(temp != nullptr) {
        node * next = temp->next;
        if(next == nullptr) {
            //temp == tail;
            temp->prev->next = n1;
            n1->prev = temp->prev;
            n1->next = temp;
            break;
        }

        if((next->abailty > n1->abailty) && (next->abailty == n1->abailty && next->id < n1->id)) {
            //insert next to temp
            temp->next = n1;
            n1->prev = temp;
            next->prev = n1;
            n1->next = next;
            break;
        }
        temp = next;

        if(next == leage_middle[leage_index]) {
            middle_toggle = 1;
        }
    }
    ret.second = middle_toggle;
    printplayers();

    return ret;
}

int move()
{
    int result = 0;
    node *changePlayer[10][2];
    int middle_toggle[10];
    for(int i = 0; i < num_leages; ++i) {
        changePlayer[i][1] = leage_head[i].next;
        changePlayer[i][0] = leage_tail[i].prev;
        middle_toggle[i] = 0;
    }
    cout << cnt++ << endl;

    middle_toggle[0] = 1;
    middle_toggle[num_leages - 1] = -1;
    for(int i = 0; i < (num_leages - 1); ++i) {
        result += changePlayer[i][1]->id;
        result += changePlayer[i + 1][0]->id;
        cout << cnt++ << endl;
        pair<int, int> p = changeNode(changePlayer[i][1], changePlayer[i + 1][0], i);
        middle_toggle[i] += p.first;
        middle_toggle[i + 1] += p.second;
    }
    cout << cnt++ << endl;


    for(int i = 0; i < num_leages; ++i) {
        if(middle_toggle[i] == -2) {
            leage_middle[i] = leage_middle[i]->prev;
        }
        else if(middle_toggle[i] == 2) {
            leage_middle[i] = leage_middle[i]->next;
        }
    }
    cout << cnt++ << endl;

    return result;
}

int trade()
{
    int result = 0;
    node *changePlayer[10][2];
    int middle_toggle[10];
    for(int i = 0; i < num_leages; ++i) {
        changePlayer[i][1] = leage_middle[i];
        leage_middle[i] = leage_middle[i]->prev;
        changePlayer[i][0] = leage_tail[i].prev;
        middle_toggle[i] = 0;
    }

    middle_toggle[0] = 1;
    middle_toggle[num_leages - 1] = -1;
    for(int i = 0; i < (num_leages - 1); ++i) {
        result += changePlayer[i][1]->id;
        result += changePlayer[i + 1][0]->id;
        pair<int, int> p = changeNode(changePlayer[i][1], changePlayer[i + 1][0], i);
        middle_toggle[i] += p.first;
        middle_toggle[i + 1] += p.second;
    }

    for(int i = 0; i < num_leages; ++i) {
        if(middle_toggle[i] == -2) {
            leage_middle[i] = leage_middle[i]->prev;
        }
        else if(middle_toggle[i] == 2) {
            leage_middle[i] = leage_middle[i]->next;
        }
    }

    return result;

    return 0;
}