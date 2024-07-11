#include <iostream>
#include <string>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		int N;
		cin >> N;
		int visited = 0;
		int cnt = 1;
		while (true)
		{
			string s = to_string(N * cnt++);
			for (char c : s) {
				int n = c - '0';
				visited |= (1 << n);
			}
			if ((visited & ((1 << 10) - 1)) == ((1 << 10) - 1)) {
				cout << "#" << t << " " << s << "\n";
				break;
			}
		}
	}
	return 0;
}