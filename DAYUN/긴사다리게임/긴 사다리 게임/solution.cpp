#include <set>
#include <iostream>

using namespace std;

set<int> bridge[100];
//mx 라인 -> mx -1 라인도 확인

void init()
{
    for(int i = 0; i < 100; i++) {
        bridge[i].clear();
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

int numberOfCross(int mID)
{
    while()
	return 0;
}

int participant(int mX, int mY)
{
	return 0;
}