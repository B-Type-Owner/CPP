#include <iostream>
#include <cstring>
#include <vector>
#include <cstring>
using namespace std;

struct node {
	node *prev;
	node *next;
	int ch;
};

int height;
int weight;
int query_cnt = 1;
node* cursor;
//vector<pair<char, int>> memo;
//vector<char> memo;
node head[310];
node tail[310];
node nodes[90100];
int nodes_cnt = 0;
int alpha[310][26];
int memo_len;
int cursor_num;

node* insertNode(char ch, node *prev, node *next) {
	node* new_node = &nodes[nodes_cnt++];
	new_node->prev = prev;
	new_node->next = next;
	prev->next = new_node;
	next->prev = new_node;
	
	new_node->ch = ch - 'a';
	memo_len++;
	return new_node;
}

void init(int H, int W, char mStr[])
{
	query_cnt += 2;

	memo_len = 0;
	cursor = &head[0];
	cursor_num = 0;
	nodes_cnt = 0;
	memset(alpha, 0, sizeof(alpha));
	for (int i = 0; i < H; ++i) {
		head[i].next = &tail[i];
		tail[i].prev = &head[i];
		head[i].prev = nullptr;
		tail[i].next = nullptr;
	}

	height = H;
	weight = W;
	int row = -1;
	node* temp;
	for (int i = 0; i < strlen(mStr); ++i) {
		int ch = mStr[i] - 'a';

		if ((i % weight) == 0) {
			row++;
			temp = &head[i / weight];
		}
		
		node *new_node = insertNode(mStr[i], temp, temp->next);
		temp = temp->next;
		alpha[i / weight][ch]++;
	}
}

void insert(char mChar)
{
	query_cnt++;
	node* new_node = insertNode(mChar, cursor, cursor->next);

	for (int row = (cursor_num / weight); row < (memo_len/weight); ++row) {
		//delete
		node* n = tail[row].prev;
		tail[row].prev = n->prev;
		n->prev->next = &tail[row];
		alpha[row][n->ch]--;

		//insert
		n->prev = &head[row + 1];
		n->next = head[row + 1].next;
		head[row + 1].next = n;
		n->next->prev = n;
		alpha[row + 1][n->ch]++;
	}
	cursor_num++;
	cursor = new_node->next;
}

char moveCursor(int mRow, int mCol, char ans)
{
	query_cnt++;
	char ret = '$';

	node* temp = &head[mRow - 1];
	cursor_num = mRow * weight + mCol;
	for (int i = 0; i < mCol; ++i) {
		if (temp->next == nullptr) {
			cursor = temp->prev;
			cursor_num = memo_len;
			return ret;
		}

		temp = temp->next;
	}
	cursor = temp;
	ret = temp->prev->ch + 'a';
	if (ans != ret) {
		cout << query_cnt << ":" << mRow << " " << mCol << " " << ans << " ret:" << ret;
	}
	return ret;
}

int countCharacter(char mChar, int ans)
{
	query_cnt++;
	int ret = 0;
	int ch = mChar - 'a';
	node* temp = cursor;
	while (temp->next != nullptr) {
		if (temp->ch == ch) {
			ret++;
		}

		temp = temp->next;
	}
	for (int i = (cursor_num/ weight) + 1; i <= (memo_len / weight); ++i) {
		ret += alpha[i][ch];
	}

	if (ans != ret) {
		cout << query_cnt << ":" << mChar << " " << ans << " ret:" << ret;
	}
	return ret;
	//return ans;
}
