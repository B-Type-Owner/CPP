#include <iostream>
#include <vector>
#include <queue>

using namespace std;

long long Solution(int K, int mod);

// ��������
// 1�� ���� A, 2�� ���� B, ������ �� A + B = C
// n��° �ܰ迡�� A���� �� ������ 2A�� �ǰ�, ���� A�� �� ũ�� A���� (C - A) ��ŭ ���� �Ǿ� 2A - C�� �ȴ�.
// (2A - C) % C = 2A % C, �̴� 2A % C�� ����
// ��, (2A - C) % C�� (2A) % C�� ����~~~
// �� �� �ݺ��ϸ� (2 ^ 2A) % C => (2^K*A) % C
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	{
		int A, B, K;
		cin >> A >> B >> K;

		long long result = ((long long)Solution(K, A + B) * (long long)A) % (A + B);
		if (result > (A + B) / 2) {
			cout << "#" << test_case << " " << (A + B) - result << '\n';
		}
		else {
			cout << "#" << test_case << " " << result << '\n';
		}
	}
	return 0;
}

long long Solution(int K, int mod)
{
	long long res = 1;
	long long num = 2;

	while (K > 0) {
		if (K % 2 == 1) {
			res = (res * num) % mod;
		}
		num = (num * num) % mod;
		K /= 2;
	}

	return res;
}