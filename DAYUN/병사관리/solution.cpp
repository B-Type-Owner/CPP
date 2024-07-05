struct Person {
    int mID;
    int ver;
    Person* next;
};

struct Team {
    Person* head[6];
    Person* tail[6];
};


//??55인 이유는 뭘까....
Person person[200055];
int version[100055];
int personTeam[100055];
int cnt = 0;
Team team[6];

Person* getNewNode(int mID, int ver, Person* next) {
    Person* ret = &person[cnt++];
    ret->mID = mID;
    ret->next = next;
    ret->ver = ver;
    return ret;
}

void init()
{
    cnt = 0;
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) {
            team[i].tail[j] = getNewNode(0, 0, nullptr);
            team[i].head[j] = team[i].tail[j];
        }
    }
}

void hire(int mID, int mTeam, int mScore)
{
    Person* newP = getNewNode(mID, 0, nullptr);
    team[mTeam].tail[mScore]->next = newP;
    team[mTeam].tail[mScore] = newP;
    version[mID] = 0;
    personTeam[mID] = mTeam;
}

void fire(int mID)
{
    version[mID] = -1;
}

void updateSoldier(int mID, int mScore)
{
    int mTeam = personTeam[mID];
    Person* newP = getNewNode(mID, ++version[mID], nullptr);
    team[mTeam].tail[mScore]->next = newP;
    team[mTeam].tail[mScore] = newP;
}

void updateTeam(int mTeam, int mChangeScore)
{
    if (mChangeScore < 0) {
        int i = 2;
        for (; (i + mChangeScore) <= 1; ++i) {
            //추가하기
            if (team[mTeam].head[i]->next == nullptr) continue;

            team[mTeam].tail[1]->next = team[mTeam].head[i]->next;
            team[mTeam].tail[1] = team[mTeam].tail[i];

            //비우기
            team[mTeam].head[i]->next = nullptr;
            team[mTeam].tail[i] = team[mTeam].head[i];
        }
        for (; i < 6; ++i) {
            if (team[mTeam].head[i]->next == nullptr) continue;

            //옮기기
            team[mTeam].head[i + mChangeScore]->next = team[mTeam].head[i]->next;
            team[mTeam].tail[i + mChangeScore] = team[mTeam].tail[i];
            //비우기
            team[mTeam].head[i]->next = nullptr;
            team[mTeam].tail[i] = team[mTeam].head[i];
        }
    }
    else if (mChangeScore > 0) {
        int i = 4;
        for (; (i + mChangeScore) >= 5; --i) {
            if (team[mTeam].head[i]->next == nullptr) continue;

            //추가하기
            team[mTeam].tail[5]->next = team[mTeam].head[i]->next;
            team[mTeam].tail[5] = team[mTeam].tail[i];

            //비우기
            team[mTeam].head[i]->next = nullptr;
            team[mTeam].tail[i] = team[mTeam].head[i];
        }
        for (; i > 0; --i) {
            if (team[mTeam].head[i]->next == nullptr) continue;

            //옮기기 주소값 참조 주의
            // 그대로 == 하면 모두 비워짐 -> next로 변경
            // tail은 새로운 값을 넣는 것이기 때문에 되나?
            team[mTeam].head[i + mChangeScore]->next = team[mTeam].head[i]->next;
            team[mTeam].tail[i + mChangeScore] = team[mTeam].tail[i];
            //비우기
            team[mTeam].head[i]->next = nullptr;
            team[mTeam].tail[i] = team[mTeam].head[i];
        }
    }
}

int bestSoldier(int mTeam)
{
    int ret = 0;
    for (int i = 5; i > 0; --i) {
        Person* temp = team[mTeam].head[i]->next;
        while (temp != nullptr) {
            if (temp->mID > ret && version[temp->mID] == temp->ver) {
                ret = temp->mID;
            }
            temp = temp->next;
        }
        if (ret != 0) {
            return ret;
        }
    }

    return 0;
}