#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int student_cnt;
//key : id, value : gender_and_grade , score
unordered_map<int, pair<int, int>> id_map;
vector<pair<int, int>> students[7];

void init() {
	student_cnt = 0;
	id_map.clear();
	for (int i = 0; i < 7; ++i) {
		students[i].clear();
	}
	return;
}

int add(int mId, int mGrade, char mGender[7], int mScore) {
	int gender_and_grade = 0;
	if (mGender[0] == 'm') {
		gender_and_grade = 3;
	}
	gender_and_grade += mGrade;

	id_map[mId] = { gender_and_grade, mScore };
	pair<int, int> p = { mScore, mId };

	auto it = upper_bound(students[gender_and_grade].begin(), students[gender_and_grade].end(), p);
	if (it == students[gender_and_grade].end()) {
		students[gender_and_grade].push_back(p);
	}
	else {
		students[gender_and_grade].insert(it, p);
	}
	return students[gender_and_grade][students[gender_and_grade].size() - 1].second;
}

int remove(int mId) {
	pair<int, int> p = id_map[mId];
	if (p.first == 0) {
		return 0;
	}
	pair<int, int> student = { p.second, mId };
	auto it = lower_bound(students[p.first].begin(), students[p.first].end(), student);
	
	if (it == students[p.first].end()) {
		return 0;
	}
	students[p.first].erase(it);

	if (students[p.first].size() == 0) {
		return 0;
	}
	return students[p.first][0].second;
}

int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGender[][7], int mScore) {
	int gender;
	pair<int, int> score = {mScore, 0};
	pair<int, int> ret = { 400000, 0 };
	for (int ge = 0; ge < mGenderCnt; ++ge) {
		int gender = 0;
		if (mGender[ge][0] == 'm') {
			gender = 3;
		}

		for (int gr = 0; gr < mGradeCnt; ++gr) {
			int gg = gender + mGrade[gr];
			auto it = lower_bound(students[gg].begin(), students[gg].end(), score);
			if (it == students[gg].end()) {
				continue;
			}
			ret = min(ret, *it);
		}

	}
	
	if (ret.first == 400000) {
		return 0;
	}
	return ret.second;
}