#include <vector>
#include <string.h>
#include <queue>
using namespace std;

int mapSize;
int map[20][20];
bool visited[20][20];
int dir[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
vector<pair<int, int>> candidate_horizontal[10000];
vector<pair<int, int>> candidate_vertical[10000];

int area(int M, int mSeaLevel);

void init(int N, int mMap[20][20])
{
    int hash;
    mapSize = N;
    memcpy(map, mMap, sizeof(map));
    for (int i = 0; i < 9999; i++) {
        while (!candidate_horizontal[i].empty()) {
            candidate_horizontal[i].pop_back();
        }
        while (!candidate_vertical[i].empty()) {
            candidate_vertical[i].pop_back();
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            hash = 0;
            for (int k = 1; k <= 4; k++) {
                if ((j + k) >= N) break;
                hash = (hash * 10) + (mMap[i][j + k] - mMap[i][j + k - 1] + 5);
                candidate_horizontal[hash].push_back({ i, j });
            }
            hash = 0;
            for (int k = 1; k <= 4; k++) {
                if ((i + k) >= N) break;
                hash = (hash * 10) + (mMap[i + k][j] - mMap[i + k - 1][j] + 5);
                candidate_vertical[hash].push_back({ i, j });
            }
        }
    }
}

int numberOfCandidate(int M, int mStructure[5])
{
    int hash = 0;
    int hash_reverse = 0;

    if (M == 1) {
        return mapSize * mapSize;
    }

    for (int i = 1; i < M; i++) {
        hash = (hash * 10) + (mStructure[i - 1] - mStructure[i] + 5);
        hash_reverse = (hash_reverse * 10) + (mStructure[M - i] - mStructure[M - i - 1] + 5);
    }
    if (hash == hash_reverse) {
        return candidate_horizontal[hash].size() + candidate_vertical[hash].size();
    }
    return candidate_horizontal[hash].size() + candidate_horizontal[hash_reverse].size() + candidate_vertical[hash].size() + candidate_vertical[hash_reverse].size();
}

int maxArea(int M, int mStructure[5], int mSeaLevel)
{
    int ret = -1;
    int a;
    if (M == 1) {
        for (int i = 0; i < mapSize; i++) {
            for (int j = 0; j < mapSize; j++) {
                map[i][j] += mStructure[i];
                a = area(M, mSeaLevel);
                ret = ret > a ? ret : a;
                map[i][j] -= mStructure[i];
            }
        }
    }
    else {
        int hash = 0;
        int hash_reverse = 0;
        for (int i = 1; i < M; i++) {
            hash = (hash * 10) + (mStructure[i - 1] - mStructure[i] + 5);
            hash_reverse = (hash_reverse * 10) + (mStructure[M - i] - mStructure[M - i - 1] + 5);
        }

        for (int i = 0; i < candidate_horizontal[hash].size(); i++) {
            int y = candidate_horizontal[hash][i].first;
            int x = candidate_horizontal[hash][i].second;

            for (int i = 0; i < M; i++) {
                map[y][x + i] += mStructure[i];
            }
            a = area(M, mSeaLevel);
            ret = ret > a ? ret : a;
            for (int i = 0; i < M; i++) {
                map[y][x + i] -= mStructure[i];
            }
        }
        for (int i = 0; i < candidate_horizontal[hash_reverse].size(); i++) {
            int y = candidate_horizontal[hash_reverse][i].first;
            int x = candidate_horizontal[hash_reverse][i].second;

            for (int i = 0; i < M; i++) {
                    map[y][x + i] += mStructure[M - 1 - i];
            }
            a = area(M, mSeaLevel);
            ret = ret > a ? ret : a;
            for (int i = 0; i < M; i++) {
                map[y][x + i] -= mStructure[M - 1 - i];
            }
        }
        for (int i = 0; i < candidate_vertical[hash].size(); i++) {
            int y = candidate_vertical[hash][i].first;
            int x = candidate_vertical[hash][i].second;

            for (int i = 0; i < M; i++) {
                map[y][x + i] += mStructure[i];
            }
            a = area(M, mSeaLevel);
            ret = ret > a ? ret : a;
            for (int i = 0; i < M; i++) {
                map[y + i][x] -= mStructure[i];
            }
        }
        for (int i = 0; i < candidate_vertical[hash_reverse].size(); i++) {
            int y = candidate_vertical[hash_reverse][i].first;
            int x = candidate_vertical[hash_reverse][i].second;

            for (int i = 0; i < M; i++) {
                map[y + i][x] += mStructure[M - 1 - i];
            }
            a = area(M, mSeaLevel);
            ret = ret > a ? ret : a;
            for (int i = 0; i < M; i++) {
                map[y + i][x] -= mStructure[M - 1 - i];
            }
        }
    }

    return ret;
}

int area(int M, int mSeaLevel) {
    queue<pair<int, int>> q;
    memset(visited, false, sizeof(visited));
    int ret = mapSize * mapSize;

    for (int i = 0; i < mapSize; i++) {
        if (mSeaLevel > map[i][0]) {
            visited[i][0] = true;
            q.push({ i, 0 });
            ret--;
        }
        if (mSeaLevel > map[i][mapSize - 1]) {
            visited[i][mapSize - 1] = true;
            q.push({ i, mapSize - 1 });
            ret--;
        }
    }
    for (int i = 1; i < (mapSize - 1); i++) {
        if (mSeaLevel > map[0][i]) {
            visited[0][i] = true;
            q.push({ 0, i });
            ret--;
        }
        if (mSeaLevel > map[mapSize - 1][i]) {
            visited[mapSize - 1][i] = true;
            q.push({ mapSize - 1, i });
            ret--;
        }
    }

    while (!q.empty()) {
        int nowY = q.front().first;
        int nowX = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nextY = nowY + dir[i][0];
            int nextX = nowX + dir[i][1];

            if ((nextY >= 0) && (nextY < mapSize) && (nextX >= 0) && (nextX < mapSize) && !visited[nextY][nextX] && (map[nextY][nextX] < mSeaLevel)) {
                visited[nextY][nextX] = true;
                q.push({ nextY, nextX });
                ret--;
            }
        }
    }
    return ret;
}