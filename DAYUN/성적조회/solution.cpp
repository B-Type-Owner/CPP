#include <unordered_map>


/// <summary>
/// 세그먼트 트리 
/// </summary>
/// 

using namespace std;

const int N = 1 << 10;
int students[3][8][N << 1];
int student_cnt = N;

void init() {
	int student_cnt = 0;
	memset(students, -1, sizeof(students));
	return;
}

int add(int mId, int mGrade, char mGender[7], int mScore) {
	
	return 0;
}

int remove(int mId) {
	return 0;
}

int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGender[][7], int mScore) {
	return 0;
}