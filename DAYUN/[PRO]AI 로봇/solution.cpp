#include <queue>
#include <vector>
#include <map>
#include <cstring>
#include <iostream>

using namespace std;



struct node {
    int energy;
    int num;
};

 struct max_cmp {
     bool operator()(const node a, const node b) {
         if (a.energy < b.energy) return true;
         else if (a.energy == b.energy) return a.num >= b.num;
         else return false;
     }
 };

 struct min_cmp {
     bool operator()(const node a, const node b) {
         if (a.energy > b.energy) return true;
         else if (a.energy == b.energy) return a.num >= b.num;
         else return false;
     }
 };

int intelligence[50010];
int position[50010];
vector<pair<int, vector<int> > > job;

//0 : 높은 지능 우선 방식
priority_queue < node, vector<node>, max_cmp > maxTraining;
//1 : 낮은 지능 우선 방식 
priority_queue < node, vector<node>, min_cmp > minTraining;
//map<int, priority_queue<int, vector<int>, greater<int> > > training;
// priority_queue<int, vector<int>, cmp > training2;


void init(int N)
{
    while (!maxTraining.empty()) maxTraining.pop();
    while (!minTraining.empty()) minTraining.pop();
    job.clear();
    memset(intelligence, 0, sizeof(intelligence));
    memset(position, 0, sizeof(position));

    job.resize(1);
    for (int i = 1; i <= N; ++i) {
        minTraining.push({0, i});
        maxTraining.push({0, i});
    }

}

int callJob(int cTime, int wID, int mNum, int mOpt)
{
    int ret = 0;
    vector<int> vect;
    priority_queue<int>pq;
    map<int, priority_queue<int, vector<int>, greater<int> > >::iterator it;

    vect.resize(mNum);
    //높은 지능 우선방식

    int id;
    for (int i = 0; i < mNum; ++i) {
        if (mOpt == 0) {
            while (maxTraining.top().energy != intelligence[maxTraining.top().num]) maxTraining.pop();
            id = maxTraining.top().num;
            maxTraining.pop();
        } 
        else {
            while (minTraining.top().energy != intelligence[minTraining.top().num]) minTraining.pop();
            id = minTraining.top().num;
            minTraining.pop();
        }
        if (position[id] != 0) {
            i--;
            continue;
        }


        vect[i] = id;
        position[id] = job.size();
        //cout << id << " ";
        ret += id;

    }
    //cout << endl;
    job.push_back({ cTime, vect});
    // cout << job.size() << "?";
    // cout << ret << endl ;
    return ret;
}

void returnJob(int cTime, int wID)
{
    for (int i = 0; i < job[wID].second.size(); ++i) {
        int robotID = job[wID].second[i];
        if (position[robotID] != wID) continue;
        intelligence[robotID] -= (cTime - job[wID].first);
        maxTraining.push({ intelligence[robotID],  robotID });
        minTraining.push({ intelligence[robotID],  robotID });
        position[robotID] = 0;
    }
}

void broken(int cTime, int rID)
{
    if (position[rID] <= 0) {
        return;
    }

    position[rID] = -1;
}

void repair(int cTime, int rID)
{
    if (position[rID] != -1) return;

    minTraining.push({ -cTime, rID });
    maxTraining.push({ -cTime, rID });
    intelligence[rID] = -cTime;
    position[rID] = 0;
}

int check(int cTime, int rID)
{
    if (position[rID] == -1) {
        return 0;
    }
    else if (position[rID] > 0) {
        return position[rID] * -1;
    }
    else {
        return intelligence[rID] + cTime;
    }
    return 0;
}
