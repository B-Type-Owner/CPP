#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int height;
int weight;
int query_cnt = 1;
int cursor;
//vector<pair<char, int>> memo;

vector<char> memo;


void init(int H, int W, char mStr[])
{
	query_cnt += 2;
	memo.clear();
	cursor = 0;


	height = H;
	weight = W;
	for (int i = 0; i < strlen(mStr); ++i) {
		memo.push_back(mStr[i]);
	}
}

void insert(char mChar)
{
	query_cnt++;
	memo.insert(memo.begin() + cursor, mChar);
	cursor++;
}

char moveCursor(int mRow, int mCol, char ans)
{
	query_cnt++;
	char ret = '$';
	
	mRow--;
	mCol--;
	int index = (mRow * weight) + mCol;
	if (index >= memo.size()) {
		cursor = memo.size();
		ret = '$';
	}
	else {
		cursor = index;
		ret = memo[cursor];
	}
	

	if (ans != ret) {
		cout << query_cnt << ":" << mRow << " " << mCol << " " << ans << " ret:" << ret;
	}
	return ret;
}

int countCharacter(char mChar, int ans)
{
 	query_cnt++;
	int ret = 0;
	for (int i = cursor; i < memo.size(); ++i) {
		if (memo[i] == mChar) {
			ret++;
		}
	}

	if (ans != ret) {
		cout << query_cnt << ":" << mChar << " " << ans << " ret:" << ret;
	}
	return ret;
	//return ans;
}
