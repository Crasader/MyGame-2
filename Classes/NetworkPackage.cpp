#include "NetworkPackage.h"

//8�ֽ�������ת������
unsigned __int64 my_htonll(unsigned __int64 val) {
	return (((unsigned __int64)htonl(val)) << 32) + htonl(val >> 32);
}

//8�ֽ�������ת������
unsigned __int64 my_ntohll(unsigned __int64 val) {
	return (((unsigned __int64)ntohl(val)) << 32) + ntohl(val >> 32);
}
