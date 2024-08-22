#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <iostream>

using namespace std;

extern void init();
extern int add(int mId, int mGrade, char mGender[7], int mScore);
extern int remove(int mId);
extern int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGender[][7], int mScore);

/////////////////////////////////////////////////////////////////////////

#define CMD_INIT 100
#define CMD_ADD 200
#define CMD_REMOVE 300
#define CMD_QUERY 400

static bool run() {
	int q;
	scanf("%d", &q);

	int id, grade, score;
	char gender[7];
	int cmd, ans, ret;
	bool okay = true;

	for (int i = 0; i < q; ++i) {
		//if (!okay) break;
		scanf("%d", &cmd);
		switch (cmd) {
		case CMD_INIT:
			init();
			okay = true;
			break;
		case CMD_ADD:
			scanf("%d %d %s %d %d", &id, &grade, gender, &score, &ans);
			ret = add(id, grade, gender, score);
			if (ans != ret) {
				okay = false;
				cout << i << ": " << cmd << " " << id << " " << grade << " " << gender << " " << score << " " << ans << endl;
			}
			break;
		case CMD_REMOVE:
			scanf("%d %d", &id, &ans);
			ret = remove(id);
			if (ans != ret) {
				okay = false;
				cout << i << ": " << cmd << " " << id << " " << ans << endl;
			}
			break;
		case CMD_QUERY: {
			int gradeCnt, genderCnt;
			int gradeArr[3];
			char genderArr[2][7];
			scanf("%d", &gradeCnt);
			if (gradeCnt == 1) {
				scanf("%d %d", &gradeArr[0], &genderCnt);
			}
			else if (gradeCnt == 2) {
				scanf("%d %d %d", &gradeArr[0], &gradeArr[1], &genderCnt);
			}
			else {
				scanf("%d %d %d %d", &gradeArr[0], &gradeArr[1], &gradeArr[2], &genderCnt);
			}
			if (genderCnt == 1) {
				scanf("%s %d %d", genderArr[0], &score, &ans);
			}
			else {
				scanf("%s %s %d %d", genderArr[0], genderArr[1], &score, &ans);
			}
			ret = query(gradeCnt, gradeArr, genderCnt, genderArr, score);
			if (ans != ret) {
				okay = false;
				cout << i << ": " << cmd << " " << gradeCnt;
				for (int i = 0; i < gradeCnt; ++i) {
					cout << " " << gradeArr[i];
				}
				for (int i = 0; i < genderCnt; ++i) {
					cout << " " << genderArr[i];
				}
				cout << " " << score << " " << ans << " " << ret << endl;
			}
			break;
		}
		default:
			okay = false;
			break;
		}
	}
	return okay;
}

int main() {
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
		if (score == 0) break;
	}

	return 0;
}