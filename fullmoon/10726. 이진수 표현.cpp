#include <iostream>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		int N, M;
		cin >> N >> M;
		if ((M & ((1 << N) - 1)) == ((1 << N) - 1)) {
			cout << "#" << t << " ON\n";
		}
		else {
			cout << "#" << t << " OFF\n";
		}
	}
	return 0;
}