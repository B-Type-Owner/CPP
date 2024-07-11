#include <iostream>
using namespace std;

int N, M, L;

struct NODE {
	int v;
	NODE* prev;
	NODE* next;
	NODE() {}
	NODE(int v, NODE* prev, NODE* next) :v(v), prev(prev), next(next) {}
}*head;

void input()
{
	cin >> N >> M >> L;
	NODE* cur = head;
	for (int i = 0; i < N; i++)
	{
		int x;
		cin >> x;
		if (i == 0)
		{
			head = new NODE(x, 0, 0);
			cur = head;
		}
		else
		{
			cur->next = new NODE(x, cur, 0);
			cur = cur->next;
		}
	}
}

void func()
{
	for (int m = 0; m < M; m++)
	{
		char cmd;
		cin >> cmd;
		if (cmd == 'I')
		{
			int idx, x;
			cin >> idx >> x;
			if (idx == 0)
			{
				NODE* node = new NODE(x, 0, head);
				head->prev = node;
				head = node;
			}
			else
			{
				NODE* cur = head;
				while (--idx) cur = cur->next;
				NODE* node = new NODE(x, cur, cur->next);
				if (cur->next) cur->next->prev = node;
				cur->next = node;
			}
			N++;
		}
		else if (cmd == 'D')
		{
			int idx;
			cin >> idx;
			if (idx == 0)
			{
				if (N > 1)
				{
					head = head->next;
					head->prev = NULL;
				}
				else head = NULL;
			}
			else
			{
				NODE* cur = head;
				while (--idx) cur = cur->next;
				cur->next = cur->next->next;
				if (cur->next) cur->next->prev = cur;
			}
			N--;
		}
		else if (cmd == 'C')
		{
			int idx, x;
			cin >> idx >> x;

			NODE* cur = head;
			while (idx--) cur = cur->next;
			cur->v = x;
		}
	}

	if (N > 0)
	{
		NODE* cur = head;
		while (L--)
		{
			cur = cur->next;
			if (!cur) break;
		}
		if (!cur) cout << -1 << "\n";
		else cout << cur->v << "\n";
	}
	else
	{
		cout << -1 << "\n";
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		input();
		cout << "#" << t << " ";
		func();
	}
	return 0;
}