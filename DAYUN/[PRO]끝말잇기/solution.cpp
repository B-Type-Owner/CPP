#include <iostream>
#include <queue>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_set>

#define MAX_N 50000
#define MAX_M 50000
#define MAX_LEN 11

using namespace std;

struct player{
    int id;
    player *prev;
    player *next;
};

int numPlayer;
int numWord;
int wordCnt;
player playerList[MAX_N + 10];
priority_queue<string, vector<string>, greater<string> > words[26];
queue<string> queryUsedWords;
unordered_set<string> usedWords;

void init(int N, int M, char mWords[][MAX_LEN])
{
    wordCnt = -1;
    usedWords.clear();
    for(int i = 0; i < 26; ++i) {
        while(!words[i].empty()) words[i].pop();
    }

    numPlayer = N;
    numWord = M;
    for(int i = 0; i <= N; i++) {
        playerList[i].id = i;
        playerList[i].prev = &playerList[i - 1];
        playerList[i].next = &playerList[i + 1];
    }
    playerList[1].prev = &playerList[N];
    playerList[N].next = &playerList[1];


    for(int i = 0; i < M; ++i) {
        //insert words to PQ
        string str = "";
        string reverseStr = "";
        int j = 0;
        while(mWords[i][j] != '\0') {
            str += mWords[i][j];
            j++;
        }
        str += '\0';

        usedWords.insert(str);
        words[mWords[i][0] - 'a'].push(str);
    }
}

int playRound(int mID, char mCh)
{
    int ret = mID;
    while(!words[mCh -'a'].empty()) {
        string str = words[mCh - 'a'].top();
        words[mCh - 'a'].pop();
        
        ret = playerList[ret].next->id;
        mCh = str[str.size() - 2];
        queryUsedWords.push(str);
    }

    //fail member
    playerList[ret].prev->next = playerList[ret].next;
    playerList[ret].next->prev = playerList[ret].prev;

    //reverse 계산
    while(!queryUsedWords.empty()) {
        string reverseStr = "";

        string str = queryUsedWords.front();
        queryUsedWords.pop();

        for(int i = str.size() - 2; i >= 0; --i) {
            reverseStr += str[i];
        }
        reverseStr += '\0';

        if(usedWords.find(reverseStr) == usedWords.end()) {
            usedWords.insert(reverseStr);
            words[reverseStr[0] - 'a'].push(reverseStr);           
        }
    }

	return ret;
}