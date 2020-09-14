#include "StdAfx.h"
#include "OTNM2000PipeClient.h"

OTNM2000PipeClient::OTNM2000PipeClient(string strInterfaceName)
{
	m_hPipe = NULL;
	string strPipeName = "\\\\.\\pipe\\" + strInterfaceName;
	if (!WaitNamedPipe(strPipeName.c_str(), 6000))
	{
		return;
	}
	// 打开已创建的管道句柄
	m_hPipe = CreateFile(strPipeName.c_str(),
		GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (m_hPipe == INVALID_HANDLE_VALUE)
	{
		m_hPipe = CreateFile(strPipeName.c_str(),
			GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (m_hPipe == INVALID_HANDLE_VALUE)
		{
			m_hPipe = NULL;
		}
	}
}
//
OTNM2000PipeClient::~OTNM2000PipeClient(void)
{
	if (m_hPipe != NULL)
	{
		CloseHandle(m_hPipe); // 关闭管道句柄
		m_hPipe = NULL;
	}
}
//
bool OTNM2000PipeClient::SendByteByPipe(const char* pData, int iLength)
{
	if (m_hPipe == NULL)
	{
		return false;
	}
	DWORD dwWriteNum;
	if (!WriteFile(m_hPipe, pData, iLength, &dwWriteNum, NULL))
	{
		return false;
	}
	Sleep(20);
	return true;
}
