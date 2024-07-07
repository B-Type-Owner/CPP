#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

#define MAXCARDS 50010

int endPoint;
int startPoint;
int joker;
int cards[50010];
// [jokerNum][mNum]
deque<int> moduleNum[20][20];

void init(int mJoker, int mNumbers[5])
{
    endPoint = 5;
    startPoint = 0;
    joker = mJoker % 20;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            moduleNum[i][j].clear();
        }
    }

    for (int i = 0; i < 5; i++) {
        cards[i] = mNumbers[i];
    }

    for (int i = 0; i < 2; i++) {
        int num = 0;
        int jokerNum = 0;
        for (int j = 0; j < 4; j++) {
            if (cards[i + j] == -1) jokerNum++;
            else num += cards[i + j];
        }

        for (int j = 0; j < 20; j++) {
            moduleNum[j][(num + (jokerNum * j)) % 20].push_back(i);
        }
    }
}

void putCards(int mDir, int mNumbers[5])
{
    if (mDir) {
        for (int i = 0; i < 5; i++) {
            cards[i + endPoint] = mNumbers[i];
        }

        for (int i = endPoint - 3; i < endPoint + 2; i++) {
            int num = 0;
            int jokerNum = 0;
            for (int j = 0; j < 4; j++) {
                if (cards[i + j] == -1) jokerNum++;
                else num += cards[i + j];
            }

            for (int j = 0; j < 20; j++) {
                moduleNum[j][(num + (jokerNum * j)) % 20].push_back(i);
            }
        }
        endPoint += 5;
    }
    else {
        startPoint = (startPoint + MAXCARDS - 5) % MAXCARDS;
        for (int i = 0; i < 5; i++) {
            cards[i + startPoint] = mNumbers[i];
        }

        for (int i = startPoint + 4; i >= startPoint ; i--) {
            int num = 0;
            int jokerNum = 0;
            for (int j = 0; j < 4; j++) {
                if (cards[(i + j) % MAXCARDS] == -1) jokerNum++;
                else num += cards[(i + j) % MAXCARDS];
            }

            //주의 : 앞부터 넣어야지...
            for (int j = 0; j < 20; j++) {
                moduleNum[j][(num + (jokerNum * j)) % 20].push_front(i % MAXCARDS);
            }
        }
    }
}

int findNumber(int mNum, int mNth, int ret[4])
{
    if (moduleNum[joker][mNum].size() < mNth) return 0;
    int index = moduleNum[joker][mNum][mNth - 1];
    for (int i = 0; i < 4; i++) {
        ret[i] = cards[(index + i) % MAXCARDS];
    }
    return 1;
}

void changeJoker(int mValue)
{
    joker = mValue % 20;
}