#include <iostream>
#include <algorithm>
using namespace std;

unsigned long long candy(unsigned long long x, unsigned long long p, unsigned long long c) {
	unsigned long long res = 1;
	while (p) {
		if (p & 1) res *= x;
		x *= x;
		p >>= 1;
		if (x > c) x %= c;
		if (res > c) res %= c;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		unsigned long long A, B, K;
		cin >> A >> B >> K;
		unsigned long long C = A + B, ans = 0;
		ans = (A * candy(2, K, C)) % C;
		ans = min(ans, C - ans);
		cout << "#" << t << " " << ans << "\n";
	}
	return 0;
}