//segment tree시도, 시간 초과 실패

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;

const int N = 1 << 15;
//grade, id
pair<int, int> students[4][8][N << 1];
pair<unsigned int, unsigned int> students_min[4][8][N << 1];
unordered_map<int, int> student_id;
int student_cnt;

void init() {
	student_cnt = 1 ;
	memset(students, -1, sizeof(students));
	memset(students_min, -1, sizeof(students));
	student_id.clear();
	return;
}

int add(int mId, int mGrade, char mGender[7], int mScore) {
	int grade = 1 << (mGrade - 1);
	int gender = 1;
	if (mGender[0] == 'm') gender = 2;



	//mGrade학생 중 mGender인 학생 점수가 가장 높은 학생의 아이디
	//만약 학생 id가 같다면, id가 큰 학생 리턴
	int new_id = student_cnt++;
	for (int i = 1; i < 4; ++i) {
		if (!(i & gender)) {
			continue;
		}
		for (int j = 1; j < 8; ++j) {
			if (!(j & grade)) {
				continue;
			}
			//update node
			int temp = new_id + N;
			students[i][j][temp] = { mScore, mId };
			students_min[i][j][temp] = { mScore, mId };
			temp /= 2;
			while (temp >= 1) {
				students[i][j][temp] = max(students[i][j][temp * 2], students[i][j][temp * 2 + 1]);
				pair<unsigned int, unsigned int> a = min(students_min[i][j][temp * 2], students_min[i][j][temp * 2 + 1]);
				students_min[i][j][temp] = min(students_min[i][j][temp * 2], students_min[i][j][temp * 2 + 1]);
				temp /= 2;
			}
		}
	}
	student_id.insert({ mId, new_id });
	return students[gender][grade][1].second;
}


pair<int, int> find(int gender, int grade, int temp, int score, pair<int, int> found)
{
	if (temp >= N) return found;

	if (students[gender][grade][temp * 2].first >= score && students_min[gender][grade][temp * 2].first <= found.first ) {
		found = find(gender, grade, temp * 2, score, min(students[gender][grade][temp * 2], found));
	}
	//right find
	if (students[gender][grade][temp * 2 + 1].first >= score && students_min[gender][grade][temp * 2 + 1].first <= found.first) {
		found = find(gender, grade, temp * 2 + 1, score, min(students[gender][grade][temp * 2 + 1], found));
	}

	return found;
}


int remove(int mId) {
	int id = student_id[mId];
	int gender = 0;
	int grade = 0;
	for (int i = 1; i < 4; ++i) {
		for (int j = 1; j < 8; ++j) {

			//update node
			int temp = id + N;
			if (students[i][j][temp].first != -1) {
				students[i][j][temp] = { -1, -1 };
				students_min[i][j][temp] = { -1, -1 };
				if (i != 3 && (j == 2 || j == 4 || j == 1)) {
					gender = i;
					grade = j;
				}
			}
			else {
				continue;
			}

			temp /= 2;
			while (temp >= 1) {
				students[i][j][temp] = max(students[i][j][temp * 2], students[i][j][temp * 2 + 1]);
				students_min[i][j][temp] = min(students_min[i][j][temp * 2], students_min[i][j][temp * 2 + 1]);
				temp /= 2;
			}
		}
	}

	if (gender == 0 || students_min[gender][grade][1].second == -1) return 0;
	return students_min[gender][grade][1].second;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
}

int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGender[][7], int mScore) {

	pair<int, int> ret = { 300010, 0 };
	int grade = 0;
	int gender = 0;

	for (int i = 0; i < mGradeCnt; ++i) {
		grade += (1 << (mGrade[i] - 1));
	}
	if (mGenderCnt == 2) {
		gender = 3;
	}
	else if (mGender[0][0] == 'm') {
		gender = 2;
	}
	else gender = 1;

	if (students[gender][grade][1].first > mScore) {
		ret = find(gender, grade, 1, mScore, ret);
	}
	return ret.second;
}