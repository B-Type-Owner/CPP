#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <vector>
#include <iostream>
#include <cstring>
#include <deque>
#include <stack>


using namespace std;

struct News{
    int id;
    int channelId;
    int time;
    
    bool operator < (const News &news) const{
        if(time > news.time) return true;
        if(time == news.time) {
            return id > news.id;
        }
        return false;
    }
};

int n;
int k;
int userCnt = 0;
int channelCnt = 0;
int users[510];
priority_queue<News> delayNews;
vector<int>  userNews[510];
vector<int> channelUsers[510];
unordered_map<int, int> userId;
unordered_map<int, int> channelId;
unordered_set<int> channelNews[510];
unordered_set<int> cancel;
int deleteUserNews[510];
bool newsInserted[510];

void init(int N, int K)
{
    userCnt = 0;
    channelCnt = 0;
    userId.clear();
    channelId.clear();
    // memset(cancel, false, xsizeof(cancel));
    memset(deleteUserNews, 0, sizeof(deleteUserNews));
    cancel.clear();
    for(int i = 0; i < 510; ++i) {
        // userNews[i].pop();
        userNews[i].clear();
        // while(!userNews[i].empty()) {
        //     userNews[i].pop();
        // }
        users[i] = 0;
        channelNews[i].clear();
        channelUsers[i].clear();
    }
    while(!delayNews.empty()) delayNews.pop();
    n = N;
    k = K;
}

void insertNews(int mTime) {
    while(!delayNews.empty()) {
        if(mTime < delayNews.top().time) {
            break;
        }

        News nn = delayNews.top();
        delayNews.pop();

        if(cancel.find(nn.id) != cancel.end()) continue;

        for(int i = 0; i < channelUsers[nn.channelId].size(); ++i) {
            // userNews[channelUsers[nn.channelId][i]].push(nn.id);
            userNews[channelUsers[nn.channelId][i]].push_back(nn.id);
            // cout << channelUsers[nn.channelId][i] << nn.channelId << " " << nn.id << " " <<endl;
        }


        channelNews[nn.channelId].insert(nn.id);
    }
    return;
}

void registerUser(int mTime, int mUID, int mNum, int mChannelIDs[])
{
    insertNews(mTime);


    // cout << " " << mTime << " " << mUID << " " << mNum << "  " << mChannelIDs[0] << endl;
    int id;
    if(userId.find(mUID) == userId.end()) {
        id = userCnt++;
        userId[mUID] = id;
    }
    else {
        id = userId[mUID];
    }
    // cout << id;

    // channelUsers
    for(int i = 0; i < mNum; ++i){
        int cid;
        if(channelId.find(mChannelIDs[i]) == channelId.end()) {
            cid = channelCnt++;
            channelId[mChannelIDs[i]] = cid;
        }
        else {
            cid = channelId[mChannelIDs[i]];
        }

        channelUsers[cid].push_back(id);
    }
    // cout << id;

    // for(int i = 0; i < mNum; ++i){
    //     int cid;
    //     if(channelId.find(mChannelIDs[i]) == channelId.end()) {
    //         cid = channelId[mChannelIDs[i]];
    //     }
    //     else {
    //         cid = channelCnt++;
    //         channelId[mChannelIDs[i]] = cid;
    //     }

    //     users[id].channels[i] = cid;
    //     chanelusers[id].c = cid;
    // }

}

int offerNews(int mTime, int mNewsID, int mDelay, int mChannelID)
{
    // cout << " " << mTime;


    News n;
    n.id = mNewsID;
    n.time = mTime + mDelay;
    n.channelId = channelId[mChannelID];
    delayNews.push(n);
    // cout << " " <<channelUsers[n.channelId].size() << endl;
    insertNews(mTime);
    return channelUsers[n.channelId].size();
}

void cancelNews(int mTime, int mNewsID)
{
    if(cancel.find(mNewsID) != cancel.end()) return;
    cancel.insert(mNewsID);
    insertNews(mTime);
    // cout << mTime << endl;
    
    for(int i = 0; i < channelCnt; ++i) {
        if(channelNews[i].find(mNewsID) == channelNews[i].end()) continue;
        for(int j = 0; j < channelUsers[i].size(); ++j) {
            deleteUserNews[channelUsers[i][j]]++;
        }
    }
}

int checkUser(int mTime, int mUID, int mRetIDs[])
{
    int cnt = 0;

    insertNews(mTime);
    int id = userId[mUID];
    int ret = 0;
    int result = 0;
    // int result = userNews[id].size() - deleteUserNews[id];
    // while(!userNews[id].empty()) {
    for(int i = userNews[id].size() - 1; i >= 0 ;--i) {
        int newsId = userNews[id][i];
        if(cancel.find(newsId) != cancel.end()) {
            if(i == (userNews[id].size() - 1)) 
                userNews[id].pop_back();
            continue;
        }
        if(mUID == 7345) {
            cout << newsId << " ";
        }
        if(result < 3) {
            mRetIDs[result] = newsId;
            userNews[id].pop_back();
        }
        result++;

    }
    if(mUID == 7345) {
        cout << "\n";
    }
    // deleteUserNews[id] += ret;

	return result;
}