int cards[50010];
int games[31][20][50010];
int result[1500200][4];
int joker, games_cnt;
int games_front[31][20], games_back[31][20];
int cards_front, cards_back;

void init(int mJoker, int mNumbers[5])
{
	for (int i = 0; i < 31; ++i) {
		for (int j = 0; j < 20; ++j) {
			games_front[i][j] = 50000;
			games_back[i][j] = 0;
		}
	}
	games_cnt = 0;
	cards_front = 50000;
	cards_back = 0;

	joker = mJoker;
	for (int i = 0; i < 5; ++i) {
		cards[cards_back++] = mNumbers[i];
		if (i < 3) continue;
		for (int j = 1; j <= 30; ++j) {
			int sum = 0, start = cards_back - 4;
			for (int k = 0; k < 4; ++k) {
				if (cards[start + k] == -1) {
					sum += j;
				}
				else {
					sum += cards[start + k];
				}
				result[games_cnt][k] = cards[start + k];
			}
			sum %= 20;
			games[j][sum][games_back[j][sum]++] = games_cnt;
			games_cnt++;
		}
	}
}

void putCards(int mDir, int mNumbers[5])
{
	if (mDir == 0) {
		for (int i = 4; i >= 0; --i) {
			cards[cards_front--] = mNumbers[i];
			for (int j = 1; j <= 30; ++j) {
				int sum = 0;
				for (int k = 0; k < 4; ++k) {
					int idx = cards_front + k + 1;
					if (idx > 50000) {
						idx -= 50001;
					}
					if (cards[idx] == -1) {
						sum += j;
					}
					else {
						sum += cards[idx];
					}
					result[games_cnt][k] = cards[idx];
				}
				sum %= 20;
				games[j][sum][games_front[j][sum]--] = games_cnt;
				games_cnt++;
			}
		}
	}
	else {
		for (int i = 0; i < 5; ++i) {
			cards[cards_back++] = mNumbers[i];
			for (int j = 1; j <= 30; ++j) {
				int sum = 0, start = cards_back - 4;
				for (int k = 0; k < 4; ++k) {
					int idx = start + k;
					if (cards[idx] == -1) {
						sum += j;
					}
					else {
						sum += cards[idx];
					}
					result[games_cnt][k] = cards[idx];
				}
				sum %= 20;
				games[j][sum][games_back[j][sum]++] = games_cnt;
				games_cnt++;
			}
		}
	}
}

int findNumber(int mNum, int mNth, int ret[4])
{
	if (50000 - games_front[joker][mNum] + games_back[joker][mNum] >= mNth) {
		int tmp = games_front[joker][mNum] + mNth;
		if (tmp > 50000) {
			tmp -= 50001;
		}
		int idx = games[joker][mNum][tmp];
		for (int i = 0; i < 4; i++) {
			ret[i] = result[idx][i];
		}
		return 1;
	}
	return 0;
}

void changeJoker(int mValue)
{
	joker = mValue;
}