#pragma once
#include "cocos2d.h"
#include <thread>
#include <mutex>
using namespace std;
USING_NS_CC;

const int g_nMaxRequsetDataSize = 1000*1024;

//typedef std::function<void(void* pResponseData)> TCPResponseCallback;			//响应回调原型
//
////注册回调的宏
//#define ALW_CALLBACK_1(__selector__,__target__) std::bind(&__selector__,__target__, std::placeholders::_1)

class CTCPRequest:public Ref
{
public:
	CTCPRequest();
	virtual ~CTCPRequest();
	void setRequestData(char* requestData, int size);
	void* getRequestData(){ return m_dataBuf; }
	int getRequestDataLen(){ return m_nDataLen; }
private:
	unsigned char *m_dataBuf ;		//数据缓冲
	int m_nDataLen;								//实际数据长度
	mutex m_dataMutex;
	
};

