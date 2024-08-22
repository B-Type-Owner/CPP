#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> horse;
vector<int> cow;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);


	int test_case;
	int T;
    int n;
    int m;
    int c1;
    int c2;

	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> n >> m;
        cin >> c1 >> c2;
        
        cow.resize(n);
        horse.resize(m);
        for(int i = 0; i < n; i++) {
            cin >> cow[i];
        }
        for(int i = 0; i < m; i++) {
            cin >> horse[i];
        }
        sort(cow.begin(), cow.end());
        sort(horse.begin(), horse.end());


        int c = 0;
        int h = 0;
        int cd = cow[0];
        int hd = horse[0];
        int minDist = 1e9 * 2;
        int dist = 0;
        int minNum;
        while(c < n && h < m) {
            hd =horse[h];
            cd = cow[c];
            if(cd < hd) {
                c++;
                dist = hd - cd;
            }else {
                h++;
                dist = cd - hd;
            }

            if(minDist > dist) {
                minNum = 1;
                minDist = dist;
            }
            else if(minDist == dist) {
                minNum++;
            }
        }

	
        cout << "#" << test_case << " " << minDist + abs(c1 - c2) << " " << minNum << "\n";
    }

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}