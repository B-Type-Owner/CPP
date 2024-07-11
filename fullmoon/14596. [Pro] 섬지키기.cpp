#include <vector>
#include <queue>
using namespace std;

struct Position {
	int y, x, dir;
};

vector<Position> candidates[10000];
int map[20][20];
int map_size;

int findRemainArea(int mSeaLevel) {
	bool visited[20][20] = { 0, };
	int dy[4] = { -1, 0, 1, 0 };
	int dx[4] = { 0, 1, 0, -1 };

	int ans = map_size * map_size;
	queue<pair<int, int>> q;
	for (int i = 0; i < map_size; i++) {
		if (map[i][0] < mSeaLevel) {
			q.push({ i, 0 });
			visited[i][0] = true;
			ans--;
		}
		if (map[i][map_size - 1] < mSeaLevel) {
			q.push({ i, map_size - 1 });
			visited[i][map_size - 1] = true;
			ans--;
		}
	}
	for (int i = 1; i < map_size - 1; i++) {
		if (map[0][i] < mSeaLevel) {
			q.push({ 0, i });
			visited[0][i] = true;
			ans--;
		}
		if (map[map_size - 1][i] < mSeaLevel) {
			q.push({ map_size - 1, i });
			visited[map_size - 1][i] = true;
			ans--;
		}
	}

	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || ny >= map_size || nx < 0 || nx >= map_size) continue;
			if (visited[ny][nx]) continue;
			if (map[ny][nx] >= mSeaLevel) continue;
			visited[ny][nx] = true;
			q.push({ ny, nx });
			ans--;
		}
	}

	return ans;
}

void init(int N, int mMap[20][20])
{
	for (int i = 0; i < 10000; i++) {
		candidates[i].clear();
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = mMap[i][j];
		}
	}
	map_size = N;

	for (int m = 1; m < 5; m++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				int diff_num = 0;
				if (i + m < N) {
					for (int k = 0; k < m; k++) {
						diff_num += mMap[i + k][j] - mMap[i + k + 1][j] + 5;
						if (k == m - 1) continue;
						diff_num *= 10;
					}
					candidates[diff_num].push_back({ i, j, 1 });
				}

				diff_num = 0;
				if (j + m < N) {
					for (int k = 0; k < m; k++) {
						diff_num += mMap[i][j + k] - mMap[i][j + k + 1] + 5;
						if (k == m - 1) continue;
						diff_num *= 10;
					}
					candidates[diff_num].push_back({ i, j, 2 });
				}
			}
		}
	}
}

int numberOfCandidate(int M, int mStructure[5])
{
	int ans = 0;
	if (M > 1) {
		int diff_num = 0, diff_num_rev = 0;
		for (int i = 1; i < M; i++) {
			diff_num += mStructure[i] - mStructure[i - 1] + 5;
			if (i == M - 1) continue;
			diff_num *= 10;
		}
		ans = candidates[diff_num].size();

		for (int i = M - 1; i > 0; i--) {
			diff_num_rev += -(mStructure[i] - mStructure[i - 1]) + 5;
			if (i == 1) continue;
			diff_num_rev *= 10;
		}
		if (diff_num != diff_num_rev) {
			ans += candidates[diff_num_rev].size();
		}
	}
	else {
		ans = map_size * map_size;
	}
	return ans;
}

int maxArea(int M, int mStructure[5], int mSeaLevel)
{
	int ans = -1;
	if (M > 1) {
		int diff_num = 0, diff_num_rev = 0;
		for (int i = 1; i < M; i++) {
			diff_num += mStructure[i] - mStructure[i - 1] + 5;
			if (i == M - 1) continue;
			diff_num *= 10;
		}
		int structure_cnt = candidates[diff_num].size();
		for (int i = 0; i < structure_cnt; i++) {
			for (int j = 0; j < M; j++) {
				if (candidates[diff_num][i].dir == 1) {
					map[candidates[diff_num][i].y + j][candidates[diff_num][i].x] += mStructure[j];
				}
				else {
					map[candidates[diff_num][i].y][candidates[diff_num][i].x + j] += mStructure[j];
				}
			}
			int area = findRemainArea(mSeaLevel);
			if (area > ans) ans = area;
			for (int j = 0; j < M; j++) {
				if (candidates[diff_num][i].dir == 1) {
					map[candidates[diff_num][i].y + j][candidates[diff_num][i].x] -= mStructure[j];
				}
				else {
					map[candidates[diff_num][i].y][candidates[diff_num][i].x + j] -= mStructure[j];
				}
			}
		}

		for (int i = M - 1; i > 0; i--) {
			diff_num_rev += -(mStructure[i] - mStructure[i - 1]) + 5;
			if (i == 1) continue;
			diff_num_rev *= 10;
		}
		if (diff_num != diff_num_rev) {
			structure_cnt = candidates[diff_num_rev].size();
			for (int i = 0; i < structure_cnt; i++) {
				for (int j = 0; j < M; j++) {
					if (candidates[diff_num_rev][i].dir == 1) {
						map[candidates[diff_num_rev][i].y + j][candidates[diff_num_rev][i].x] += mStructure[M - 1 - j];
					}
					else {
						map[candidates[diff_num_rev][i].y][candidates[diff_num_rev][i].x + j] += mStructure[M - 1 - j];
					}
				}
				int area = findRemainArea(mSeaLevel);
				if (area > ans) ans = area;
				for (int j = 0; j < M; j++) {
					if (candidates[diff_num_rev][i].dir == 1) {
						map[candidates[diff_num_rev][i].y + j][candidates[diff_num_rev][i].x] -= mStructure[M - 1 - j];
					}
					else {
						map[candidates[diff_num_rev][i].y][candidates[diff_num_rev][i].x + j] -= mStructure[M - 1 - j];
					}
				}
			}
		}
	}
	else {
		for (int i = 0; i < map_size; i++) {
			for (int j = 0; j < map_size; j++) {
				for (int k = 0; k < M; k++) {
					map[i][j] += mStructure[k];
				}
				int area = findRemainArea(mSeaLevel);
				if (area > ans) ans = area;
				for (int k = 0; k < M; k++) {
					map[i][j] -= mStructure[k];
				}
			}
		}
	}
	return ans;
}