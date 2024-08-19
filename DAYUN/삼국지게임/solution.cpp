#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

unordered_map<string, pair<int, int>> monarches_area;
int soldier[25][25];
int group_id[25][25];
vector<pair<int, int>> group[625];
vector<int> enemy[625];
int group_recruit[625];
int sizeN;

void init(int N, int mSoldier[25][25], char mMonarch[25][25][11])
{
	sizeN = N;
	monarches_area.clear();
	memset(group_recruit, 0, sizeof(group_recruit));
	int group_cnt = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			monarches_area.insert({ string(mMonarch[i][j]), {i, j}});
			soldier[i][j] = mSoldier[i][j];
			group_id[i][j] = group_cnt++;
			group[group_id[i][j]].push_back({ i, j });
		}
	}
}

void destroy()
{

}

int ally(char mMonarchA[11], char mMonarchB[11])
{
	//union 
	pair<int, int> a = monarches_area[string(mMonarchA)];
	pair<int, int> b = monarches_area[string(mMonarchB)];

	//이미 같은 그룹인지 확인
	int a_group = group_id[a.first][a.second];
	int b_group = group_id[b.first][b.second];
	if (a_group==b_group) {
		return -1;
	}
	//적 그룹인지 확인
	for (int i = 0; i < enemy[a_group].size(); ++i) {
		if (enemy[a_group][i] == b_group)
			return -2;
	}
	for (int i = 0; i < group[b_group].size(); ++i) {
		group[a_group].push_back(group[b_group][i]);
		group_id[group[b_group][i].first][group[b_group][i].second] = a_group;
	}
	for (int i = 0; i < enemy[b_group].size(); ++i) {
		enemy[a_group].push_back(enemy[b_group][i]);
		enemy[enemy[b_group][i]].push_back(a_group);
	}
	return 1;
}

int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11])
{
	int ret = 0;
	pair<int, int> a = monarches_area[string(mMonarchA)];
	pair<int, int> b = monarches_area[string(mMonarchB)];
	int a_group = group_id[a.first][a.second];
	int b_group = group_id[b.first][b.second];
	
	int attackSoliders = 0;
	int defenseSoliders = 0;
	if (a_group == b_group) {
		return -1;
	}

	//적대관계 정의
	enemy[a_group].push_back(b_group);
	enemy[b_group].push_back(a_group);


	for (int i = b.first - 1; i <= (b.first + 1); ++i) {
		if (i < 0 || i >= sizeN) continue;
		for (int j = b.second -1; j <= (b.second + 1); ++j) {
			if (j < 0 || j >= sizeN) continue;
			int gi = group_id[i][j];
			if (a_group == gi) {
				attackSoliders += (soldier[i][j] / 2);
				soldier[i][j] = (soldier[i][j] + 1) / 2;
			}
			else if (b_group == gi) {
				defenseSoliders += (soldier[i][j] / 2);
				soldier[i][j] = (soldier[i][j] + 1) / 2;
			}
		}
	}
	defenseSoliders += soldier[b.first][b.second];

	if (defenseSoliders >= attackSoliders) {
		soldier[b.first][b.second] = defenseSoliders - attackSoliders;
		return 0;
	}
	else {
		soldier[b.first][b.second] = attackSoliders - defenseSoliders;
		monarches_area.insert({ string(mGeneral), {b.first, b.second} });
		return 1;
	}

	return -3;
}

int recruit(char mMonarch[11], int mNum, int mOption)
{
	pair<int, int> a = monarches_area[string(mMonarch)];
	if (mOption == 0) {
		soldier[a.first][a.second] += mNum;
		return soldier[a.first][a.second];
	}
	else {
		int gi = group_id[a.first][a.second];
		int result = 0;
		for (int i = 0; i < group[gi].size(); ++i) {
			soldier[group[gi][i].first][group[gi][i].second] += mNum;
			result += soldier[group[gi][i].first][group[gi][i].second];
		}
		return result;
	}

	return -1;
}
