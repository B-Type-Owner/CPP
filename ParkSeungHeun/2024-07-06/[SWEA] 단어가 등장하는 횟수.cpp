#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// HASH : 나만의 표현법을 만들귀~~

const int EXPONENT1 = 32;
const int EXPONENT2 = 37;
const int EXPONENT3 = 41;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	{
		string str;
		string cmp;

		cin >> str >> cmp;

		int hash1 = 0;
		int pattern1 = 0;

		int hash2 = 0;
		int pattern2 = 0;

		int hash3 = 0;
		int pattern3 = 0;

		int power1 = 1;
		int power2 = 1;
		int power3 = 1;

		int count = 0;

		for (int i = 0; i <= str.length() - cmp.length(); i++) {
			// 초기~~
			if (i == 0) {
				for (int j = 0; j < cmp.length(); j++) {
					hash1 += str[cmp.length() - 1 - j] * power1;
					hash2 += str[cmp.length() - 1 - j] * power2;
					hash3 += str[cmp.length() - 1 - j] * power3;

					pattern1 += cmp[cmp.length() - 1 - j] * power1;
					pattern2 += cmp[cmp.length() - 1 - j] * power2;
					pattern3 += cmp[cmp.length() - 1 - j] * power3;

					if (j < cmp.length() - 1) {
						power1 *= EXPONENT1;
						power2 *= EXPONENT2;
						power3 *= EXPONENT3;
					}
				}
			}
			else {
				hash1 = EXPONENT1 * (hash1 - str[i - 1] * power1) + str[cmp.length() - 1 + i];
				hash2 = EXPONENT2 * (hash2 - str[i - 1] * power2) + str[cmp.length() - 1 + i];
				hash3 = EXPONENT3 * (hash3 - str[i - 1] * power3) + str[cmp.length() - 1 + i];
			}

			if (hash1 == pattern1 && hash2 == pattern2 && hash3 == pattern3) {
				count++;
			}

		}

		cout << "#" << test_case << " " << count << '\n';
	}
	return 0;
}
