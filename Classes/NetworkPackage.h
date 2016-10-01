#pragma once
#include <string>
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


//���ṹ
//������ɫ����
#pragma pack(1)
struct S_CreatePlayerReq
{
	S_CreatePlayerReq() :m_cmd(PP_DOUNIU_CREAT_ACCOUNT_REQ),
		m_account("alw_123"), m_roleName("ALW"),m_sex(1), m_yanZhengMa(1), m_yanZhengTime(1)
	{
		m_strAccountLen = m_account.length()+1;
		m_strRoleNameLen = m_roleName.length()+1;
		m_packageLen = 4 + 2 + m_strAccountLen + 2 + m_strRoleNameLen + 4 + 4 + 4;
	}
	short m_packageLen;						//����
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
	short m_packageLen;
	short m_cmd;
	int m_statusCode;				//0ʧ�ܣ�1�ɹ���2���д�
};

//��ȡ��ɫ��Ϣ����
struct S_GetPlayerInfoReq
{
	S_GetPlayerInfoReq() :m_cmd(PP_DOUNIU_GET_ROLEINFO_REQ),m_packageLen(4+sizeof(m_playerID)),m_playerID(0){}
	short m_packageLen;
	short m_cmd;
	unsigned long long m_playerID;
};

//��ȡ��ɫ��Ϣ��Ӧ
struct S_GetPlayerInfoACK
{
	S_GetPlayerInfoACK() :m_cmd(0){}
	short m_packageLen;
	short m_cmd;
	unsigned long long m_playerID;
	short m_playerNameLen;
	string m_strPlayerName;
	int m_sex;
	int m_currentDiamond;
};

//������������
struct S_CreateRoomReq
{
	S_CreateRoomReq() :m_cmd(PP_DOUNIU_CREATE_ROOM_REQ),m_packageLen(4){}
	short m_packageLen;
	short m_cmd;
};

//����������Ӧ
struct S_CreateRoomACK
{
	S_CreateRoomACK() :m_cmd(0){}
	short m_packageLen;
	short m_cmd;
	int m_roomID;
};

//���뷿������
struct S_JoinRoomReq
{
	S_JoinRoomReq() :m_cmd(PP_DOUNIU_JOIN_ROOM_REQ),m_packageLen(8){}
	short m_packageLen;
	short m_cmd;
	int m_roomID;
};

//���뷿����Ӧ
struct S_JoinRoomACK
{
	S_JoinRoomACK() :m_cmd(0), m_isOK(0){}
	short m_packageLen;
	short m_cmd;
	int m_isOK;					//0ʧ�ܣ�1�ɹ�
	int m_roomID;
};

//��ѯս������
struct S_SearchZhanjiReq
{
	S_SearchZhanjiReq() :m_cmd(PP_DOUNIU_QUERY_ZHANJI_REQ),m_packageLen(4){}
	short m_packageLen;
	short m_cmd;
};

//��ѯս����Ӧ
struct S_SearchZhanjiACK
{
	S_SearchZhanjiACK() :m_cmd(0){}
	short m_packageLen;
	short m_cmd;
	short m_zhanjiLen;
	string m_zhanji;
};


//�˳���������
struct S_QuitRoomReq
{
	S_QuitRoomReq() :m_cmd(PP_DOUNIU_QUIT_ROOM_REQ),m_packageLen(4){}
	short m_packageLen;
	short m_cmd;
};

//�˳�������Ӧ
struct S_QuitRoomACK
{
	S_QuitRoomACK() :m_cmd(0), m_isOK(0){}
	short m_packageLen;
	short m_cmd;
	int m_isOK;			//0ʧ�ܣ�1�ɹ�
	int m_roomID;
};

//׼����Ϸ����
struct S_ReadyPlayReq
{
	S_ReadyPlayReq() :m_cmd(PP_DOUNIU_READY_REQ), m_packageLen(4){}
	short m_packageLen;
	short m_cmd;
};

//׼����Ϸ��Ӧ
struct S_ReadyPlayACK
{
	S_ReadyPlayACK() :m_cmd(0){}
	short m_packageLen;
	short m_cmd;
	int m_isOK;						//0ʧ�ܣ�1�ɹ�
};

//��������
struct S_FaPaiReq
{
	S_FaPaiReq() :m_cmd(PP_DOUNIU_FAPAI_REQ),m_packageLen(4){}
	short m_packageLen;
	short m_cmd;
};

//������Ӧ
struct S_FaPaiACK
{
	S_FaPaiACK() :m_cmd(0){}
	short m_packageLen;
	short m_cmd;
	short m_pokerlilstLen;
	string m_pokerList;
};

//̯������
struct S_TanPaiReq
{
	S_TanPaiReq() :m_cmd(PP_DOUNIU_TANPAI_REQ),m_packageLen(4){}
	short m_packageLen;
	short m_cmd;
};

//̯����Ӧ
struct S_TanPaiACK
{
	S_TanPaiACK() :m_cmd(0){}
	short m_packageLen;
	short m_cmd;
	int m_isSmaller;//0:��,1:С
};

//����ʯ����
struct S_BuyDiamondReq
{
	S_BuyDiamondReq() :m_cmd(PP_DOUNIU_CHONGZHI_REQ), m_packageLen(8), m_wantBuy(0){}
	short m_packageLen;
	short m_cmd;
	int m_wantBuy;
};

//����ʯ��Ӧ
struct S_BuyDiamondACK
{
	S_BuyDiamondACK() :m_cmd(0),m_isOK(0),m_currentDiamond(0){}
	short m_packageLen;
	short m_cmd;
	int m_isOK;
	int m_currentDiamond;
};

//��������
struct S_QiangZhuangReq
{
	S_QiangZhuangReq() :m_cmd(PP_DOUNIU_QIANGZHUANG_REQ),m_packageLen(4){}
	short m_packageLen;
	short m_cmd;
};

//������Ӧ
struct S_QiangZhuangACK
{
	S_QiangZhuangACK() :m_cmd(0),m_ZhuangJiaID(0){}
	short m_packageLen;
	short m_cmd;
	unsigned long long m_ZhuangJiaID;
};

//Ѻע����
struct S_YaZhuReq
{
	S_YaZhuReq() :m_cmd(PP_DOUNIU_YAZHU_REQ),m_packageLen(8){}
	short m_packageLen;
	short m_cmd;
	int m_beishu;
};

//Ѻע��Ӧ
struct S_YaZhuACK
{
	S_YaZhuACK() :m_cmd(0){}
	short m_packageLen;
	short m_cmd;
	int m_isOK;
};
#pragma pack(4)
