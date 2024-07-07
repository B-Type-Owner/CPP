#include <string>
#include <unordered_map>
#include <memory.h>

using namespace ::std;

// ����Ʈ�� �ִ� ���� : 10
// ����Ʈ�� �ִ� ���� : 200000
// ����� �ִ� ���� : 10 + 5000 + 100000 + 400 = 105410

const int MAX_MAKE_LIST = 10;
const int MAX_LENGTH = 200000;
const int MAX_ADDRESS = 6000;
const int MAX_CHANGE = 110000;

// ������� �迭�� ����
int init_num;
// �ʱ��� �迭 ����
int init_value[MAX_MAKE_LIST + 1][MAX_LENGTH + 1];

// �����ϴ� �迭, ���� �ٷ�� �迭�� ����
int address_num;
// �迭 �̸�, ���� �迭�ǹ�ȣ
unordered_map<string, int> address;

// ��ɾ� ����
int change_num;
// ��ɾ ����ϴ� �迭
int change_log[MAX_CHANGE + 1][2];
// makeList : (-1, ���� �迭 ��ȣ)
// copyList : (-1, -1) ���� �߰��ϱ�, ���� ����
// updateElement : (idx, value)

// i�� ���� �迭�� ������ ��ȭ event ��ȣ
int last_change[MAX_ADDRESS + 1];
// i�� ��ȭ�� ���� ��ȭ event ��ȣ
int prev_change[MAX_CHANGE + 1];

void init()
{
    init_num = 0;
    address_num = 0;
    address.clear();
    change_num = 0;
}

// ����Ʈ �����~~~
void makeList(char mName[], int mLength, int mListValue[])
{
    // �ʱⰪ �迭�� �迭 �߰�
    memcpy(init_value[init_num], mListValue, mLength * sizeof(int));
    // �����ϴ� �迭 �߰�
    address[string(mName)] = address_num;
    address_num++;

    // ��ȭ
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
        // ���� �����, �׷��� ���ο� ��� �߰�
        address[string(mDest)] = address_num;
        address_num++;

        change_log[change_num][0] = -1;
        change_log[change_num][1] = -1;

        // ���������� ��ȭ�� ���� ����Ѵ�.
        prev_change[change_num] = last_change[address[string(mSrc)]];
        last_change[address[string(mDest)]] = change_num;
        change_num++;
    }
    else {
        // ���� ���� �����, �׷��� A�迭�� �״�� �����Ѵٰ� �Ѵ�.
        address[string(mDest)] = address[string(mSrc)];
    }
}

void updateElement(char mName[], int mIndex, int mValue)
{
    // ��ȭ ��� �迭�� ����
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
        // ���� ��ȭ�� ������ ������ makeList;
        if (prev_change[c] == -1) {
            return init_value[change_log[c][1]][mIndex];
        }

        // mIndex�� ������Ʈ �� ���� ������
        if (change_log[c][0] == mIndex) {
            return change_log[c][1];
        }

        c = prev_change[c];
    }
    return 0;
}