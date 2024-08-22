#include <set>
#include <iostream>

using namespace std;

#define MAX 1e9

set<int> bridge[101];
//mx 라인 -> mx -1 라인도 확인

void init()
{
    for(int i = 0; i <= 100; i++) {
        bridge[i].clear();
        bridge[i].insert(0);
        bridge[i].insert(MAX);
    }
}

void add(int mX, int mY)
{
    bridge[mX].insert(mY);
}

void remove(int mX, int mY)
{
    bridge[mX].erase(mY);
}

// lower bound : 찾는 값 이상 첫 위치
//UPPER BOUND : 찾는 값 초과 나오는 첫 위치
int numberOfCross(int mID)
{
    int ret = -1;
    int i = 0;
    while(i != MAX) {
        ret++;
        int s1 = *bridge[mID].upper_bound(i);
        int s2 = *bridge[mID - 1].upper_bound(i);
        if(s2 < s1) {
            i = s2;
            mID--;
        }
        else {
            i = s1;
            mID++;
        }
    }
	return ret;
}

int participant(int mX, int mY)
{
    bool test =false;
    if(mX == 100 && mY == 50) test = true;
    int ret = mX;
    int i = mY;
    int pm = 0;
    if(*bridge[ret].lower_bound(i) == 0) {
        return ret;
    }
    while(i != 0){
        ret += pm;
        int s1 = *(--bridge[ret].lower_bound(i));
        int s2 = *(--bridge[ret - 1].lower_bound(i));
        if(s1 < s2) {
            i = s2;
            pm  = -1;
        }
        else {
            i = s1;
            pm = 1;
        }
    }

	return ret;
}