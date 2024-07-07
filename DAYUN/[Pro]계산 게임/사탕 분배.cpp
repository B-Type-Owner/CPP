 #include<iostream>
using namespace std;

int powMoudleC(int a, int k, int c) {
    unsigned long long ret = a;
    unsigned long long pow = 2;
    while(k) {
        if(k & 1) ret = (ret * pow) % c;
        pow = (pow * pow) % c;
        k >>= 1; 
    }
    return ret;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin>>T;

    int a, b, k;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> a >> b >> k;
        int c = a + b;
        a = powMoudleC(a, k, c);
        b = powMoudleC(b, k, c);
        cout << "#" << test_case << " "<<(a > b ? b : a) << "\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}