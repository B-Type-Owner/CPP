// 수학문제
/*
    C = A + B
    A | B
    2A (2A % C) | B - A ( 2B - C == (2B - C) % C == 2B % C)
    => (전 단계 * 2) % c = 다음 단계
    => k번째 단계 는 (2 ^ k) * (처음 숫자) % C

    제곱 계산 할떄는 특히 숫자가 크니 unsigned long long 사용하기 
*/


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