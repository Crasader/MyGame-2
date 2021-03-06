#pragma once
#include <vector>
#include <cstdlib>
#include <map>
#include <utility>
#include <thread>
#include <mutex>
#include <ctime> 
#include <queue>
using namespace std;

struct playerInfo
{
	bool join;
	unsigned long long playerid;
	string name;
	int diamond;
	int money;
};

//测试阶段模拟的简单服务器
class DebugSimpleServer
{
public:
	static DebugSimpleServer* getInstance();
	virtual ~DebugSimpleServer();
	map<string, vector<int>> getPokes();
	void playerReady(string name);
	bool isAllReady();
	void quitRoom(const string& name);
	playerInfo getQueueFront();
	bool isEmpty();
	void pop();
private:
	DebugSimpleServer();
	void createPoke();				//随机生成扑克
	string createPlayerName();						//随机生成用户名
	void update();									//子线程函数
				
private:
	static DebugSimpleServer* m_pServerInstance;
	map<string, vector<int>> m_mapPlayer2Pokes;
	vector<string> m_vecPlayersInRoom;				//房间里的玩家
	mutex m_mutex;
	bool m_alwInRoom;
	queue<playerInfo> m_queue;

};

