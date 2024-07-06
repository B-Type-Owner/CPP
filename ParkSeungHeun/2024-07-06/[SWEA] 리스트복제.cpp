#include <string>
#include <unordered_map>
#include <memory.h>

using namespace ::std;

// 리스트의 최대 개수 : 10
// 리스트의 최대 길이 : 200000
// 명령의 최대 개수 : 10 + 5000 + 100000 + 400 = 105410

const int MAX_MAKE_LIST = 10;
const int MAX_LENGTH = 200000;
const int MAX_ADDRESS = 6000;
const int MAX_CHANGE = 110000;

// 만들어진 배열의 개수
int init_num;
// 초기의 배열 정보
int init_value[MAX_MAKE_LIST + 1][MAX_LENGTH + 1];

// 존재하는 배열, 실제 다루는 배열의 개수
int address_num;
// 배열 이름, 원본 배열의번호
unordered_map<string, int> address;

// 명령어 개수
int change_num;
// 명령어를 기록하는 배열
int change_log[MAX_CHANGE + 1][2];
// makeList : (-1, 원본 배열 번호)
// copyList : (-1, -1) 정보 추가하기, 깊은 복사
// updateElement : (idx, value)

// i번 원본 배열의 마지막 변화 event 번호
int last_change[MAX_ADDRESS + 1];
// i번 변화의 직전 변화 event 번호
int prev_change[MAX_CHANGE + 1];

void init()
{
    init_num = 0;
    address_num = 0;
    address.clear();
    change_num = 0;
}

// 리스트 만들기~~~
void makeList(char mName[], int mLength, int mListValue[])
{
    // 초기값 배열에 배열 추가
    memcpy(init_value[init_num], mListValue, mLength * sizeof(int));
    // 존재하는 배열 추가
    address[string(mName)] = address_num;
    address_num++;

    // 변화
    change_log[change_num][0] = -1;
    change_log[change_num][1] = init_num;

    prev_change[change_num] = -1;
    last_change[address[string(mName)]] = change_num;
    change_num++;
    init_num++;

}

void copyList(char mDest[], char mSrc[], bool mCopy)
{
    if (mCopy) {
        // 깊은 복사다, 그러면 새로운 노드 추가
        address[string(mDest)] = address_num;
        address_num++;

        change_log[change_num][0] = -1;
        change_log[change_num][1] = -1;

        // 이전까지의 변화를 노드로 기억한다.
        prev_change[change_num] = last_change[address[string(mSrc)]];
        last_change[address[string(mDest)]] = change_num;
        change_num++;
    }
    else {
        // 만약 얕은 복사다, 그러면 A배열을 그대로 참조한다고 한다.
        address[string(mDest)] = address[string(mSrc)];
    }
}

void updateElement(char mName[], int mIndex, int mValue)
{
    // 변화 목록 배열에 갱신
    change_log[change_num][0] = mIndex;
    change_log[change_num][1] = mValue;
    prev_change[change_num] = last_change[address[string(mName)]];
    last_change[address[string(mName)]] = change_num;
    change_num++;
}

int element(char mName[], int mIndex)
{
    int c = last_change[address[string(mName)]];
    while (true) {
        // 이전 변화가 없으면 최초의 makeList;
        if (prev_change[c] == -1) {
            return init_value[change_log[c][1]][mIndex];
        }

        // mIndex가 업데이트 된 적이 있으면
        if (change_log[c][0] == mIndex) {
            return change_log[c][1];
        }

        c = prev_change[c];
    }
    return 0;
}