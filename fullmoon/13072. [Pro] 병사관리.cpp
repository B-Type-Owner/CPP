struct NODE {
    int id, ver;
    NODE* prev;
    NODE* next;
    NODE() {}
    NODE(int id, int ver, NODE* prev, NODE* next) :id(id), ver(ver), prev(prev), next(next) {}
}*head[6][6], * tail[6][6];

struct Team {
    int version, mTeam, mScore;
}team[100002];

int latest[100002];

void init()
{
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 1; j <= 5; j++)
        {
            head[i][j] = tail[i][j] = new NODE(0, 0, 0, 0);
        }
    }
}

void hire(int mID, int mTeam, int mScore)
{
    NODE* node = new NODE(mID, ++latest[mID], tail[mTeam][mScore], 0);
    if (!head[mTeam][mScore]->next) head[mTeam][mScore]->next = node;
    else tail[mTeam][mScore]->next = node;
    tail[mTeam][mScore] = node;
    team[mID] = { latest[mID], mTeam, mScore };
}

void fire(int mID)
{
    team[mID].version = -1;
}

void updateSoldier(int mID, int mScore)
{
    fire(mID);
    hire(mID, team[mID].mTeam, mScore);
}

void updateTeam(int mTeam, int mChangeScore)
{
    if (mChangeScore > 0)
    {
        for (int i = 5; i > 0; i--)
        {
            if (!head[mTeam][i]->next) continue;

            int score = i + mChangeScore;
            if (score > 5) score = 5;
            else if (score < 1) score = 1;
            if (score == i) continue;

            head[mTeam][i]->next->prev = tail[mTeam][score];
            tail[mTeam][score]->next = head[mTeam][i]->next;
            tail[mTeam][score] = tail[mTeam][i];
            head[mTeam][i]->next = 0;
            tail[mTeam][i] = head[mTeam][i];
        }
    }
    else if (mChangeScore < 0)
    {
        for (int i = 1; i <= 5; i++)
        {
            if (!head[mTeam][i]->next) continue;

            int score = i + mChangeScore;
            if (score > 5) score = 5;
            else if (score < 1) score = 1;
            if (score == i) continue;

            head[mTeam][i]->next->prev = tail[mTeam][score];
            tail[mTeam][score]->next = head[mTeam][i]->next;
            tail[mTeam][score] = tail[mTeam][i];
            head[mTeam][i]->next = 0;
            tail[mTeam][i] = head[mTeam][i];
        }
    }
}

int bestSoldier(int mTeam)
{
    int ans = 0;
    for (int i = 5; i > 0; i--)
    {
        NODE* cur = head[mTeam][i]->next;
        while (cur)
        {
            if (team[cur->id].version == cur->ver) {
                if (cur->id > ans)
                {
                    ans = cur->id;
                }
            }
            cur = cur->next;
        }
        if (ans > 0) break;
    }
    return ans;
}