#pragma once
#include <string>
#include <windows.h>
using namespace std;

//
class OTNM2000PipeClient
{
	HANDLE m_hPipe;
public:
	OTNM2000PipeClient(string strInterfaceName);
	~OTNM2000PipeClient(void);
	bool SendByteByPipe(const char* pData, int iLength);
};
