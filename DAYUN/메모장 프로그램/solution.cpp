#include <iostream>
#include <cstring>

using namespace std;

struct node {
	node* prev;
	node* next;
	char ch;
};

int num_character[300][26];
int node_cnt;
int h;
int w;
node *cursor;
int row_;
node n[10000];
node head[300];
node tail[300];

void init(int H, int W, char mStr[])
{
	int node_cnt = 0;
	memset(num_character, 0, sizeof(num_character));
	for (int i = 0; i < H; ++i) {
		head[i].next = &tail[i];
		tail[i].prev = &tail[i];
	}

	h = H;
	w = W;
	cursor = &head[0];
	line_node_cnt = 0;

}

void insert(char mChar)
{
	node* new_node = &n[node_cnt++];
	n->ch = mChar;


}

char moveCursor(int mRow, int mCol)
{
	return '$';
}

int countCharacter(char mChar)
{
	return -1;
}
