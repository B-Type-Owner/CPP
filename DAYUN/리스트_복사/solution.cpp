#include <unordered_map>
#include <vector>

using namespace std;

const int MAX_TIME = 100005;

struct Node {
    int index;
    int value;
    int time;
};

int cntArr = 0;
int cntCopyArr = 10;
//int time = 0;
int arr[10][200000];
//first = index 
vector<pair<int, int>> arrLog[5020];
unordered_map < string, int> arrLink;
unordered_map < string, int> arrCopyTime;

void init()
{
    for (int i = 0; i < cntCopyArr; i++) {
        arrLog[i].clear();
    }
    cntArr = 0;
    cntCopyArr = 10;
}

void makeList(char mName[], int mLength, int mListValue[])
{
    arrLink[mName] = cntArr;
    memcpy(arr[cntArr++], mListValue, sizeof(int) * mLength);
}

void copyList(char mDest[], char mSrc[], bool mCopy)
{
    if (mCopy) {
        arrLink[mDest] = cntCopyArr;
        arrLog[cntCopyArr++].push_back({ (-1) * arrLog[arrLink[mSrc]].size(), arrLink[mSrc]});
    }
    else {
        arrLink[mDest] = arrLink[mSrc];
    }
}

void updateElement(char mName[], int mIndex, int mValue)
{
    arrLog[arrLink[mName]].push_back({ mIndex, mValue});
}

int element(char mName[], int mIndex)
{
    int linkIndex = arrLink[mName];
    for (int i = arrLog[linkIndex].size() - 1; i >= 0; i--) {
        if (arrLog[linkIndex][i].first == mIndex) {
            return arrLog[linkIndex][i].second;
        }
        else if (i == 0 && linkIndex >= 10) {
            linkIndex = arrLog[linkIndex][i].second;
            i = arrLog[linkIndex][i].first;
        }
    }
    
    return arr[linkIndex][mIndex];
}