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

//���Խ׶�ģ��ļ򵥷�����
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
	void createPoke();				//��������˿�
	string createPlayerName();						//��������û���
	void update();									//���̺߳���
				
private:
	static DebugSimpleServer* m_pServerInstance;
	map<string, vector<int>> m_mapPlayer2Pokes;
	vector<string> m_vecPlayersInRoom;				//����������
	mutex m_mutex;
	bool m_alwInRoom;
	queue<playerInfo> m_queue;

};

