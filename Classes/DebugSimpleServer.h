#pragma once
#include <vector>
#include <cstdlib>
#include <map>
#include <utility>
#include <thread>
#include <mutex>
#include <ctime> 
using namespace std;

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
};

