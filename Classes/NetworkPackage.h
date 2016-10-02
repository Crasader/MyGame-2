#pragma once
#include <string>
#ifdef WIN32
#include <windows.h>
#include <WinSock.h>
#else
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCKET int
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1

#endif
using namespace std;
//����
#define PP_DOUNIU_CREAT_ACCOUNT_REQ	(10000)
#define PP_DOUNIU_CREAT_ACCOUNT_ACK	(10001)
#define PP_DOUNIU_GET_ROLEINFO_REQ	(10002)
#define PP_DOUNIU_GET_ROLEINFO_ACK	(10003)
#define PP_DOUNIU_CREATE_ROOM_REQ	(50000)
#define PP_DOUNIU_CREATE_ROOM_ACK	(50001)
#define PP_DOUNIU_JOIN_ROOM_REQ		(50002)
#define PP_DOUNIU_JOIN_ROOM_ACK		(50003)
#define PP_DOUNIU_QUERY_ZHANJI_REQ	(50004)
#define PP_DOUNIU_QUERY_ZHANJI_ACK	(50005)
#define PP_DOUNIU_QUIT_ROOM_REQ		(50006)
#define PP_DOUNIU_QUIT_ROOM_ACK		(50007)
#define PP_DOUNIU_READY_REQ			(50008)
#define PP_DOUNIU_READY_ACK			(50009)
#define PP_DOUNIU_FAPAI_REQ			(50010)
#define PP_DOUNIU_FAPAI_ACK			(50011)
#define PP_DOUNIU_TANPAI_REQ		(50012)
#define PP_DOUNIU_TANPAI_ACK		(50013)
#define PP_DOUNIU_CHONGZHI_REQ		(50014)
#define PP_DOUNIU_CHONGZHI_ACK		(50015)
#define PP_DOUNIU_QIANGZHUANG_REQ	(50016)
#define PP_DOUNIU_QIANGZHUANG_ACK	(50017)
#define PP_DOUNIU_YAZHU_REQ			(50018)
#define PP_DOUNIU_YAZHU_ACK			(50019)

//8�ֽ�������ת������
unsigned __int64 my_htonll(unsigned __int64 val);

//8�ֽ�������ת������
unsigned __int64 my_ntohll(unsigned __int64 val);

//���ṹ
//������ɫ����
#pragma pack(1)
struct S_CreatePlayerReq
{
	S_CreatePlayerReq(string account, string roleName, int sex) :m_cmd(PP_DOUNIU_CREAT_ACCOUNT_REQ), m_key(0),
		m_account(account), m_roleName(roleName),m_sex(sex), m_yanZhengMa(1), m_yanZhengTime(1)
	{
		m_strAccountLen = m_account.length()+1;
		m_strRoleNameLen = m_roleName.length()+1;
		m_packageLen = 4 + 4 + 2 + m_strAccountLen + 2 + m_strRoleNameLen + 4 + 4 + 4;
		//ת���ֽ���
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
		m_strAccountLen = htons(m_strAccountLen);
		m_strRoleNameLen = htons(m_strRoleNameLen);
		m_sex = htonl(m_sex);
		m_yanZhengMa = htonl(m_yanZhengMa);
		m_yanZhengTime = htonl(m_yanZhengTime);

	}
	short m_packageLen;						//����
	int	  m_key;							//��֮���к�
	short m_cmd;							//Э���
	short m_strAccountLen;					//�˺ų���
	string m_account;						//�˺�
	short m_strRoleNameLen;					//��ɫ������
	string m_roleName;						//��ɫ��
	int m_sex;								//�Ա�
	int m_yanZhengMa;						//��֤��	
	int m_yanZhengTime;						//��֤ʱ��
};

//������ɫ��Ӧ
struct S_CreatePlayerACK
{
	S_CreatePlayerACK() :m_packageLen(8),m_cmd(0),m_statusCode(0){}
	//��̬���������ڽ�����������ת���ɸýṹ��
	static S_CreatePlayerACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_CreatePlayerACK s;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_statusCode, pData, 4);
		s.m_statusCode = ntohl(s.m_statusCode);
		return s;
	}
	short m_packageLen;
	short m_cmd;
	int m_statusCode;				//0ʧ�ܣ�1�ɹ���2���д�
};

//��ȡ��ɫ��Ϣ����
struct S_GetPlayerInfoReq
{
	S_GetPlayerInfoReq(unsigned __int64 playerID) :m_cmd(PP_DOUNIU_GET_ROLEINFO_REQ), m_packageLen(8 + sizeof(m_playerID)),
	m_key(0),m_playerID(playerID)
	{
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
		m_playerID = my_htonll(m_playerID);
	}
	short m_packageLen;
	int	  m_key;							//��֮���к�
	short m_cmd;
	unsigned __int64 m_playerID;
};

//��ȡ��ɫ��Ϣ��Ӧ
struct S_GetPlayerInfoACK
{
	S_GetPlayerInfoACK() :m_cmd(0){}
	//��̬���������ڽ�����������ת���ɸýṹ��
	static S_GetPlayerInfoACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_GetPlayerInfoACK s;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_playerID, pData, 8);
		s.m_playerID = my_ntohll(unsigned __int64(s.m_playerID));
		pData += 8;
		memcpy(&s.m_playerNameLen, pData, 2);
		s.m_playerNameLen = ntohs(s.m_playerNameLen);
		pData += 2;
		char buf[1024];
		memcpy(buf, pData, s.m_playerNameLen);
		s.m_strPlayerName = buf;
		pData += s.m_playerNameLen;
		memcpy(&s.m_sex, pData, 2);
		s.m_sex = ntohl(s.m_sex);
		pData += 4;
		memcpy(&s.m_currentDiamond, pData, 4);
		s.m_currentDiamond = ntohl(s.m_currentDiamond);
		return s;
	}
	short m_packageLen;
	short m_cmd;
	unsigned __int64 m_playerID;
	short m_playerNameLen;
	string m_strPlayerName;
	int m_sex;
	int m_currentDiamond;
};

//������������
struct S_CreateRoomReq
{
	S_CreateRoomReq() :m_cmd(PP_DOUNIU_CREATE_ROOM_REQ),m_packageLen(8),m_key(0)
	{
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	short m_packageLen;
	int	  m_key;							//��֮���к�
	short m_cmd;
};

//����������Ӧ
struct S_CreateRoomACK
{
	S_CreateRoomACK() :m_cmd(0){}

	static S_CreateRoomACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_CreateRoomACK s;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_roomID, pData, 4);
		s.m_roomID = ntohl(s.m_roomID);
		return s;
	}

	short m_packageLen;
	short m_cmd;
	int m_roomID;
};

//���뷿������
struct S_JoinRoomReq
{
	S_JoinRoomReq(int roomID) :m_cmd(PP_DOUNIU_JOIN_ROOM_REQ),m_packageLen(12),m_key(0)
	{
		m_roomID = htonl(roomID);
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	short m_packageLen;
	int	  m_key;							//��֮���к�
	short m_cmd;
	int m_roomID;
};

//���뷿����Ӧ
struct S_JoinRoomACK
{
	S_JoinRoomACK() :m_cmd(0), m_isOK(0){}

	static S_JoinRoomACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_JoinRoomACK s;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_isOK, pData, 4);
		s.m_isOK = ntohl(s.m_isOK);
		pData += 4;
		memcpy(&s.m_roomID, pData, 4);
		s.m_roomID = ntohl(s.m_roomID);
		return s;
	}

	short m_packageLen;
	short m_cmd;
	int m_isOK;					//0ʧ�ܣ�1�ɹ�
	int m_roomID;
};

//��ѯս������
struct S_SearchZhanjiReq
{
	S_SearchZhanjiReq() :m_cmd(PP_DOUNIU_QUERY_ZHANJI_REQ),m_packageLen(8),m_key(0)
	{
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	short m_packageLen;
	int	  m_key;							//��֮���к�
	short m_cmd;
};

//��ѯս����Ӧ
struct S_SearchZhanjiACK
{
	S_SearchZhanjiACK() :m_cmd(0){}

	static S_SearchZhanjiACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_SearchZhanjiACK s;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_zhanjiLen, pData, 2);
		s.m_zhanjiLen = ntohl(s.m_zhanjiLen);
		pData += 2;
		char buf[2048];
		memcpy(buf, pData, s.m_zhanjiLen);
		s.m_zhanji = buf;
		return s;
	}

	short m_packageLen;
	short m_cmd;
	short m_zhanjiLen;
	string m_zhanji;
};


//�˳���������
struct S_QuitRoomReq
{
	S_QuitRoomReq() :m_cmd(PP_DOUNIU_QUIT_ROOM_REQ),m_packageLen(8),m_key(0)
	{
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}

	short m_packageLen;
	int	  m_key;							//��֮���к�
	short m_cmd;
};

//�˳�������Ӧ
struct S_QuitRoomACK
{
	S_QuitRoomACK() :m_cmd(0), m_isOK(0){}

	static S_QuitRoomACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_QuitRoomACK s;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_isOK, pData, 4);
		s.m_isOK = ntohl(s.m_isOK);
		pData += 4;
		memcpy(&s.m_roomID, pData, 4);
		s.m_roomID = ntohl(s.m_roomID);
		return s;
	}

	short m_packageLen;
	short m_cmd;
	int m_isOK;			//0ʧ�ܣ�1�ɹ�
	int m_roomID;
};

//׼����Ϸ����
struct S_ReadyPlayReq
{
	S_ReadyPlayReq() :m_cmd(PP_DOUNIU_READY_REQ), m_packageLen(8),m_key(0)
	{
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	short m_packageLen;
	int	  m_key;							//��֮���к�
	short m_cmd;
};

//׼����Ϸ��Ӧ
struct S_ReadyPlayACK
{
	S_ReadyPlayACK() :m_cmd(0){}

	static S_ReadyPlayACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_ReadyPlayACK s;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_isOK, pData, 4);
		s.m_isOK = ntohl(s.m_isOK);
		return s;
	}

	short m_packageLen;
	short m_cmd;
	int m_isOK;						//0ʧ�ܣ�1�ɹ�
};

//��������
struct S_FaPaiReq
{
	S_FaPaiReq() :m_cmd(PP_DOUNIU_FAPAI_REQ),m_packageLen(8),m_key(0)
	{
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	short m_packageLen;
	int	  m_key;							//��֮���к�
	short m_cmd;
};

//������Ӧ
struct S_FaPaiACK
{
	S_FaPaiACK() :m_cmd(0){}

	static S_FaPaiACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_FaPaiACK s;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_pokerlilstLen, pData, 2);
		s.m_pokerlilstLen = ntohs(s.m_pokerlilstLen);
		pData += 2;
		char buf[2048];
		memcpy(buf, pData, s.m_packageLen);
		s.m_pokerList = buf;
		return s;
	}

	short m_packageLen;
	short m_cmd;
	short m_pokerlilstLen;
	string m_pokerList;
};

//̯������
struct S_TanPaiReq
{
	S_TanPaiReq() :m_cmd(PP_DOUNIU_TANPAI_REQ),m_packageLen(8),m_key(0)
	{
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	short m_packageLen;
	int	  m_key;							//��֮���к�
	short m_cmd;
};

//̯����Ӧ
struct S_TanPaiACK
{
	S_TanPaiACK() :m_cmd(0){}

	static S_TanPaiACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_TanPaiACK s;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_isSmaller, pData, 4);
		s.m_isSmaller = ntohl(s.m_isSmaller);
		return s;
	}
	
	short m_packageLen;
	short m_cmd;
	int m_isSmaller;//0:��,1:С
};

//����ʯ����
struct S_BuyDiamondReq
{
	S_BuyDiamondReq(int wantBuy) :m_cmd(PP_DOUNIU_CHONGZHI_REQ), m_packageLen(12), m_wantBuy(0),m_key(0)
	{
		m_wantBuy = htonl(wantBuy);
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	short m_packageLen;
	int	  m_key;							//��֮���к�
	short m_cmd;
	int m_wantBuy;
};

//����ʯ��Ӧ
struct S_BuyDiamondACK
{
	S_BuyDiamondACK() :m_cmd(0),m_isOK(0),m_currentDiamond(0){}

	static S_BuyDiamondACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_BuyDiamondACK s;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_isOK, pData, 4);
		s.m_isOK = ntohl(s.m_isOK);
		pData += 4;
		memcpy(&s.m_currentDiamond, pData, 4);
		s.m_currentDiamond = ntohl(s.m_currentDiamond);
		return s;
	}

	short m_packageLen;
	short m_cmd;
	int m_isOK;
	int m_currentDiamond;
};

//��������
struct S_QiangZhuangReq
{
	S_QiangZhuangReq() :m_cmd(PP_DOUNIU_QIANGZHUANG_REQ),m_packageLen(8),m_key(0){
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	short m_packageLen;
	int	  m_key;							//��֮���к�
	short m_cmd;
};

//������Ӧ
struct S_QiangZhuangACK
{
	S_QiangZhuangACK() :m_cmd(0),m_ZhuangJiaID(0){}

	static S_QiangZhuangACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_QiangZhuangACK s;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_ZhuangJiaID, pData, 4);
		s.m_ZhuangJiaID = my_ntohll(s.m_ZhuangJiaID);

		return s;
	}

	short m_packageLen;
	short m_cmd;
	unsigned __int64 m_ZhuangJiaID;
};

//Ѻע����
struct S_YaZhuReq
{
	S_YaZhuReq(int beishu) :m_cmd(PP_DOUNIU_YAZHU_REQ),m_packageLen(12),m_key(0){
		m_beishu = htonl(beishu);
		m_packageLen = htons(m_packageLen);
		m_cmd = htons(m_cmd);
	}
	short m_packageLen;
	int	  m_key;							//��֮���к�
	short m_cmd;
	int m_beishu;
};

//Ѻע��Ӧ
struct S_YaZhuACK
{
	S_YaZhuACK() :m_cmd(0){}

	static S_YaZhuACK convertDataFromBinaryData(void* binaryData)
	{
		char* pData = (char*)binaryData;
		S_YaZhuACK s;
		memcpy(&s.m_packageLen, pData, 2);
		s.m_packageLen = ntohs(s.m_packageLen);
		pData += 2;
		memcpy(&s.m_cmd, pData, 2);
		s.m_cmd = ntohs(s.m_cmd);
		pData += 2;
		memcpy(&s.m_isOK, pData, 4);
		s.m_isOK = my_ntohll(s.m_isOK);

		return s;
	}

	short m_packageLen;
	short m_cmd;
	int m_isOK;
};
#pragma pack(4)
