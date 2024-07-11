#include <iostream>
#include <unordered_map>
using namespace std;

int src_list[12][200002];
unordered_map<string, int> address;
pair<int, int> change[100002];
int pre_list[105020];
int last_list[5020];
int src_cnt, arr_cnt, change_cnt;

void init()
{
	address.clear();
	src_cnt = 0;
	arr_cnt = 0;
	change_cnt = 0;
}

void makeList(char mName[], int mLength, int mListValue[])
{
	for (int i = 0; i < mLength; i++) {
		src_list[src_cnt][i] = mListValue[i];
	}
	address.insert({ mName, arr_cnt });
	change[change_cnt] = { -1, src_cnt };
	last_list[arr_cnt] = change_cnt;
	arr_cnt++;
	src_cnt++;
	change_cnt++;
}

void copyList(char mDest[], char mSrc[], bool mCopy)
{
	if (mCopy) {
		address.insert({ mDest, arr_cnt });
		change[change_cnt] = { -1, -1 };
		pre_list[change_cnt] = last_list[address[mSrc]];
		last_list[arr_cnt] = change_cnt;
		arr_cnt++;
		change_cnt++;
	}
	else {
		address.insert({ mDest, address[mSrc] });
	}
}

void updateElement(char mName[], int mIndex, int mValue)
{
	change[change_cnt] = { mIndex, mValue };
	pre_list[change_cnt] = last_list[address[mName]];
	last_list[address[mName]] = change_cnt;
	change_cnt++;
}

int element(char mName[], int mIndex)
{
	int target = last_list[address[mName]];
	while (true) {
		if (change[target].first == mIndex) {
			return change[target].second;
		}
		if (change[target].first == -1 && change[target].second != -1) {
			return src_list[change[target].second][mIndex];
		}
		target = pre_list[target];
	}
	return 0;
}