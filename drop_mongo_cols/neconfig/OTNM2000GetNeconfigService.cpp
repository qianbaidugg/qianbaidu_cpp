#include "..\StdAfx.h"

#include "OTNM2000GetNeconfigService.h"
#include "neconfigclient.h"
#include "neconfigmodel.h"
//#define _AFXDLL
#undef _WINDOWS_
#include "ritpub.h"
#include "json/json.h"
#include "JsonReaderAndWriter.h"

#include "NeConfigErrorCode.h"
#include ".\\..\..\\..\\common\\otnmbusclient\\include\\otnmbuscliexport.h"
#include "iTenna.h"
#include "XsdParser.hpp"

#include <utility>
#include <hash_map>
#include "MSMPClientAPI.h"

#include "iTenna.h"          // D:\OTNM\src\common\include
#include "NeSetDataTrans.h"
#include "NeMaskCommond.h"

#include "..\\..\\..\\NeStatus_Ui\\serialize.h"
CStringArray g_arOutTmp;
bool g_mccInCallBack = false;

#if 0
#include "..\\..\\MB_Manage_UI\\DeviceCfgData.h"
#include "..\\..\\MB_Manage_UI\\DeviceObject.h"
#include "..\\..\\MB_Manage_UI\\MbmpGuiLib.h"
#pragma  comment(lib, "D:\\OTNM\\src\\Client\\cmake_lib\\mbmpgui.lib")
//using namespace MBMPGUI;
//class CBusinessEventObserver;//cpp 中的class xxxx;
#endif

//#include "..\\NetConfigObser.h"
//CNetConfigObserver mNetConfigObserver;

// extern string g_strProcessPath;
// extern void GetprocessPath();

struct stNeconfigService{

	OTNM2000GetNeconfigService *tmpThis;
	int nIndex;
	int nTypeIndex;
	eThreadType eType;
};

 
void GetBandWidthStr(string &str, EServiceType eServiceType)
{// void CBusinessEnumValueString::GetServiceType(std::vector<std::pair<EServiceType, std::string> > &vecDat)
	switch(eServiceType)
	{
	case ST_OTHER://, CTextTraits::GetLangString(0x010A))); //OTHER
		{	
			str = "OTHER";
			break;
		}
	case ST_STM_1://, CTextTraits::GetLangString(0x012C))); //STM-1
		{	
			str = "STM-1";
			break;
		}
	case ST_STM_4://, CTextTraits::GetLangString(0x012D))); //STM-4
		{	
			str = "STM-4";
			break;
		}
	case ST_STM_16://, CTextTraits::GetLangString(0x010B))); //STM-16 
		{	
			str = "STM-16";
			break;
		}
	case ST_STM_64://, CTextTraits::GetLangString(0x010C))); //STM-64
		{	
			str = "STM-64";
			break;
		}
	case ST_STM_256://, CTextTraits::GetLangString(0x010D)));//STM-256
		{	
			str = "STM-256";
			break;
		}
	case ST_OTU1://, CTextTraits::GetLangString(0x010E))); // OTU1
		{	
			str = "OTU1";
			break;
		}
	case ST_OTU2://, CTextTraits::GetLangString(0x010F))); // OTU2
		{	
			str = "OTU2";
			break;
		}
	case ST_OTU2e://, CTextTraits::GetLangString(0x011D)));//OTU2e
		{	
			str = "OTU2e";
			break;
		}
	case ST_OTU2f://, CTextTraits::GetLangString(0x011E)));//OTU2f
		{	
			str = "OTU2f";
			break;
		}
	case ST_OTU3://, CTextTraits::GetLangString(0x0110)));  //OTU3
		{	
			str = "OTU3";
			break;
		}
	case ST_OTU3e1://, CTextTraits::GetLangString(0x011F)));
		{	
			str = "OTU3e1";
			break;
		}
	case ST_OTU3e2://, CTextTraits::GetLangString(0x0120)));
		{	
			str = "OTU3e2";
			break;
		}
	case ST_OTU3f://, CTextTraits::GetLangString(0x033B)));
		{	
			str = "OTU3f";
			break;
		}
	case ST_OTU4://, CTextTraits::GetLangString(0x0337)));
		{	
			str = "OTU4";
			break;
		}
	case ST_ODU0://, CTextTraits::GetLangString(0x0343)));
		{	
			str = "ODU0";
			break;
		}
	case ST_ODU1://, CTextTraits::GetLangString(0x0111))); //ODU1
		{	
			str = "ODU1";
			break;
		}
	case ST_ODU2://, CTextTraits::GetLangString(0x0112))); 
		{	
			str = "ODU2";
			break;
		}
	case ST_ODU2e://, CTextTraits::GetLangString(0x0121)));
		{	
			str = "ODU2e";
			break;
		}
	case ST_ODU2f://, CTextTraits::GetLangString(0x0122)));
		{	
			str = "ODU2f";
			break;
		}
	case ST_ODU3://, CTextTraits::GetLangString(0x0113))); 
		{	
			str = "ODU3";
			break;
		}
	case ST_ODU3e1://, CTextTraits::GetLangString(0x0123)));
		{	
			str = "ODU3e1";
			break;
		}
	case ST_ODU3e2://, CTextTraits::GetLangString(0x0124)));
		{	
			str = "ODU3e2";
			break;
		}
	case ST_ODU3f://, CTextTraits::GetLangString(0x03D9)));
		{	
			str = "ODU3f";
			break;
		}
	case ST_ODU4://, CTextTraits::GetLangString(0x0338)));
		{	
			str = "ODU4";
			break;
		}
	case ST_GE://, CTextTraits::GetLangString(0x0118)));
		{	
			str = "GE";
			break;
		}
	case ST_10GE_WAN://, CTextTraits::GetLangString(0x0114))); 
		{	
			str = "10GE_WAN";
			break;
		}
	case ST_10GE_LAN://, CTextTraits::GetLangString(0x0115)));
		{	
			str = "10GE_LAN";
			break;
		}
	case ST_100GE://, CTextTraits::GetLangString(0x0339)));
		{	
			str = "100GE";
			break;
		}
	case ST_40GE://, CTextTraits::GetLangString(0x033A)));
		{	
			str = "40GE";
			break;
		}
	case ST_1GFC://, CTextTraits::GetLangString(0x0116)));
		{	
			str = "1GFC";
			break;
		}
	case ST_2GFC://, CTextTraits::GetLangString(0x0117)));
		{	
			str = "2GFC";
			break;
		}
	case ST_4GFC://, CTextTraits::GetLangString(0x033C)));
		{	
			str = "4GFC";
			break;
		}
	case ST_8GFC://, CTextTraits::GetLangString(0x0125)));
		{	
			str = "8GFC";
			break;
		}
	case ST_10GFC://, CTextTraits::GetLangString(0x011C)));
		{	
			str = "10GFC";
			break;
		}
	case ST_ESCON://, CTextTraits::GetLangString(0x0119)));
		{	
			str = "ESCON";
			break;
		}
	case ST_FICON://, CTextTraits::GetLangString(0x011A)));
		{	
			str = "FICON";
			break;
		}
	case ST_DVB://, CTextTraits::GetLangString(0x011B)));
		{	
			str = "DVB";
			break;
		}
	case ST_FC1600:
		{	
			str = "FC1600";
			break;
		}

	case ST_OTU3_GFP_F_6_2://, CTextTraits::GetLangString(0x0126)));   // OTU3/GFP-F(6.2)
		{	
			str = "OTU3/GFP-F(6.2)";
			break;
		}
	case ST_OTU3_GFP_F_7_3://, CTextTraits::GetLangString(0x0127)));   // OTU3/GFP-F(7.3)
		{	
			str = "OTU3/GFP-F(7.3)";
			break;
		}
	case ST_OTU2_GFP_F_6_2://, CTextTraits::GetLangString(0x0128)));   // OTU2/GFP-F(6.2)
		{	
			str = "OTU2/GFP-F(6.2)";
			break;
		}
	case ST_OTU2_GFP_F_7_3://, CTextTraits::GetLangString(0x0129)));   // OTU2/GFP-F(7.3)
		{	
			str = "OTU2/GFP-F(7.3)";
			break;
		}
	case ST_ODU2_GFP_F_6_2://, CTextTraits::GetLangString(0x012A)));   // ODU2/GFP-F(6.2)
		{	
			str = "ODU2/GFP-F(6.2)";
			break;
		}
	case ST_ODU2_GFP_F_7_3://, CTextTraits::GetLangString(0x012B)));   // ODU2/GFP-F(7.3)
		{	
			str = "ODU2/GFP-F(7.3)";
			break;
		}
	case ST_CBR://, CTextTraits::GetLangString(0x012E)));
		{	
			str = "CBR";
			break;
		}
	case ST_OTU1_ODU0://, CTextTraits::GetLangString(0x0332)));
		{	
			str = "ODU0";
			break;
		}
	case ST_OTU1_OPTS://, CTextTraits::GetLangString(0x0333)));
		{	
			str = "OTU1_OPTS";
			break;
		}
	case ST_FE://, CTextTraits::GetLangString(0x0334)));
		{	
			str = "FE";
			break;
		}
	case ST_HD_SDI://, CTextTraits::GetLangString(0x0335)));
		{	
			str = "HD_SDI";
			break;
		}
	case ST_HD_SDI_SMPTE_292M://, CTextTraits::GetLangString(0x0336))); // HD_SDI(SMPTE 292M)
		{	
			str = "HD_SDI(SMPTE 292M)";
			break;
		}
	case ST_ODU2_ODTU12_01://, CTextTraits::GetLangString(0x033D)));   // ODU2(ODTU12/01)
		{	
			str = "ODU2(ODTU12/01)";
			break;
		}
	case ST_ODU2_ODTU2_1://, CTextTraits::GetLangString(0x033E)));  // ODU2(ODTU2.1)
		{	
			str = "ODU2(ODTU2.1)";
			break;
		}
	case ST_ODU2_ODTU12://, CTextTraits::GetLangString(0x033F)));   // ODU2(ODTU12)
		{	
			str = "ODU2(ODTU12)";
			break;
		}
	case ST_OTU2_ODTU12_01://, CTextTraits::GetLangString(0x0340))); // OTU2(ODTU12/01)
		{	
			str = "OTU2(ODTU12/01)";
			break;
		}
	case ST_OTU2_ODTU2_1://, CTextTraits::GetLangString(0x0341)));   // OTU2(ODTU2.1)
		{	
			str = "OTU2(ODTU2.1)";
			break;
		}
	case ST_OTU2_ODTU12://, CTextTraits::GetLangString(0x0342)));   // OTU2(ODTU12)
		{	
			str = "OTU2(ODTU12)";
			break;
		}
	case ST_ODU2_ODTU2_ts://, CTextTraits::GetLangString(0x0344))); // ODU2(ODTU2.ts)
		{	
			str = "ODU2(ODTU2.ts)";
			break;
		}
	case ST_OTU2_ODTU2_ts://, CTextTraits::GetLangString(0x0345))); // OTU2(ODTU2.ts)
		{	
			str = "OTU2(ODTU2.ts)";
			break;
		}
	case BW_VC12://, CTextTraits::GetLangString(0x012F)));
		{	
			str = "VC12";
			break;
		}
	case BW_VC3://, CTextTraits::GetLangString(0x0130)));
		{	
			str = "VC3";
			break;
		}
	case BW_VC4://, CTextTraits::GetLangString(0x0131)));
		{	
			str = "VC4";
			break;
		}
	case BW_VC4_4://, CTextTraits::GetLangString(0x0132)));   // VC4_4
		{	
			str = "VC4_4";
			break;
		}
	case BW_VC4_16://, CTextTraits::GetLangString(0x0133)));  // VC4_16
		{	
			str = "VC4_16";
			break;
		}
	case BW_VC4_64://, CTextTraits::GetLangString(0x0134)));  // VC4_64
		{	
			str = "VC4_64";
			break;
		}
	case BW_K://, CTextTraits::GetLangString(0x0125)));
		{	
			str = "K";
			break;
		}
	case BW_64K://, CTextTraits::GetLangString(0x0136)));
		{	
			str = "64K";
			break;
		}
	case BW_M://, CTextTraits::GetLangString(0x0137)));
		{	
			str = "M";
			break;
		}

	case ST_CPRI_1:
		{	
			str = "CPRI_1";
			break;
		}
	case ST_CPRI_2:
		{	
			str = "CPRI_2";
			break;
		}
	case ST_CPRI_3:
		{	
			str = "CPRI_3";
			break;
		}
	case ST_CPRI_4:
		{	
			str = "CPRI_4";
			break;
		}
	case ST_CPRI_5:
		{	
			str = "CPRI_5";
			break;
		}
	case ST_CPRI_6:
		{	
			str = "CPRI_6";
			break;
		}
	case ST_CPRI_7:
		{	
			str = "CPRI_7";
			break;
		}
	case ST_CPRI_8:
		{	
			str = "CPRI_8";
			break;
		}
	case ST_CPRI_10:
		{	
			str = "CPRI_10";
			break;
		}
	case ST_FICON_Express:
		{	
			str = "FICON_Express";
			break;
		}
	case ST_FICON_4G:
		{	
			str = "FICON_4G";
			break;
		}
		//ao-end
	default:
		str = "-";
	}
}


std::string UTF8_To_string(const std::string & str)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	if((nwLen > 10240)||(nwLen==0)){
		std::string retStr("");
		return retStr;
	}
	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr = pBuf;

	delete []pBuf;
	delete []pwBuf;

	pBuf = NULL;
	pwBuf = NULL;

	return retStr;
}


#if 0

void test_inline_nested (void)
{
	char *str11;
	bson_t bcon, expected, foo, bar, third, third1;

	bson_init (&bcon);
	bson_init (&expected);
	bson_init (&foo);
	bson_init (&bar);
	bson_init (&third);
	bson_init (&third1);

	BCON_APPEND(&third1, "$ref", "example_coll_40", "$id", "102");
	//	bson_append_utf8 (&third1, "hello1", -1, "world1", -1);

	bson_append_utf8 (&third, "hello", -1, "world", -1);
	bson_append_int32 (&bar, "0", -1, 1);
	bson_append_int32 (&bar, "1", -1, 2);
	bson_append_document (&bar, "2", -1, &third);
	bson_append_document (&bar, "3", -1, &third1);

	bson_append_array (&foo, "bar", -1, &bar);
	bson_append_document (&expected, "foo", -1, &foo);
	bson_append_int32 (&expected, "10", -1, 1);

	//	bson_eq_bson (&bcon, &expected);

	str11 = bson_as_json(&expected, NULL);
	printf ("%s\n", str11);
	bson_free (str11);

	bson_destroy (&bcon);
	bson_destroy (&expected);
	bson_destroy (&foo);
	bson_destroy (&bar);
	bson_destroy (&third);
}

#endif

bool OTNM2000GetNeconfigService::m_bFirstInClass = true;

//
OTNM2000GetNeconfigService::OTNM2000GetNeconfigService(void):
strSrvUsr("admin"),
strSrvPassword("admin"),
strSrvIP("127.0.0.1"),
nSrvPort(5002),
bIfNeedInit(true),
m_nCatchErrorCnt(0),
m_hSess(NULL)
{
	if (m_bFirstInClass)
	{//  
		Sleep(3500);  // 重启后，防止StartUsingiTenna卡住；给closeOtn2000Debug；3秒时间关闭，和释放网管接口资源；
		m_bFirstInClass = false;
	}

	//	InitNetClient();

#if LONG_CONNECT
	if (!neconfig::client::IsInitialize()){
		if (!neconfig::client::Initialize()){
			//return ;
		}
	}
#endif

	strTABLE_PATH=""; 
	strTABLE_PATHINFO=""; 
	strTABLE_FLOW="";
	strTABLE_L2vpn="";
	strTABLE_L3vpn="";
	strTABLE_ProtectPair="";
	strTABLE_Pw="";
	strTABLE_Tunnel="";	
	m_bIsGloab = false;
	nFreqInit = 5;
	nRestartFlag=0;

}

void OTNM2000GetNeconfigService::InitNetClient()
{
	irit::StartUsingiTenna();  // 卡住了，要有策略恢复；
}

OTNM2000GetNeconfigService::OTNM2000GetNeconfigService(const string &pipName, const std::string &strUserName, const std::string &strPassword, const std::string &strIp, unsigned int nPort, const string &strTaskTable, const string &strTaskID)
{	
	m_nCatchErrorCnt =0;
	m_bIsGloab = false;
	strTABLE_PATH=""; 
	strTABLE_PATHINFO=""; 
	strTABLE_FLOW="";
	strTABLE_L2vpn="";
	strTABLE_L3vpn="";
	strTABLE_ProtectPair="";
	strTABLE_Pw="";
	strTABLE_Tunnel="";
	nFreqInit = 5;
	nRestartFlag = 0;

	InitLoginNetWork(pipName, strUserName, strPassword, strIp, nPort,strTaskTable, strTaskID);
}

void OTNM2000GetNeconfigService::InitLoginNetWork(const string &pipName, const std::string &strUserName, const std::string &strPassword, const std::string &strIp, unsigned int nPort,const string &strTaskTable, const string &strTaskID)
{
	//	irit::StartUsingiTenna();
	strSrvUsr = strUserName;
	strSrvPassword = strPassword;
	strSrvIP = strIp;
	nSrvPort = nPort;
	m_hSess = NULL;

	m_strPipeName=pipName;
	m_strTaskTable=strTaskTable;
	m_strTaskID=strTaskID;
	bIfNeedInit =true;
}

void OTNM2000GetNeconfigService::SendMongoDBResultState(const char*pipName, const char*pState)
{
	OTNM2000PipeClient oPipeClient(pipName);
	Json::Value valRet;		
	valRet["errorCode"] = Json::Value(pState);

	char* pTempJson = GetJsonStringByJsonValue(&valRet);
	oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));
	printf(pTempJson);
	delete [] pTempJson;
	pTempJson = NULL;
}

//
OTNM2000GetNeconfigService::~OTNM2000GetNeconfigService(void)
{
	//	if (m_bIsGloab)
	{
		irit::StopUsingiTenna();  // => 释放时，卡在DestroyOAClient了。
		//		exit(0);   // => 所以，强制退出了。  =》导致弹出错误的宏窗口；
		//		exit(0);
	}
}


void GetOnlyRecordID(char *buf)
{
	ULONGLONG ullTime = GetTickCount64();
	sprintf(buf, "%I64u_%d", ullTime, rand()/10000);	
}

void GetNeName(string &strNeName, int dwNeId)
{
	XNE_PTR poNe = GET_XNE(dwNeId);
	if (NULL != poNe){
		XDWORDTABLE arBoardId;
		poNe->GetBoards(arBoardId);
		CString str = poNe->GetName();

		strNeName = str.GetBuffer();
	}
}

void GetBoardNeSlots(std::vector<std::string> &vctStrSlots, std::vector<int> &vctBoardId, DWORD dwNeId)
{
	XNE_PTR poNe = GET_XNE(dwNeId);
	if (NULL != poNe){
		XDWORDTABLE arBoardId;
		poNe->GetBoards(arBoardId);
		CString str = poNe->GetName();  // 网元名称；

		char name[100]="";
		strcpy(name, str.GetBuffer());

		for (int i = 0; i < arBoardId.GetCount(); ++i){
			XBOARD_PTR poBoard = GET_XBOARD(arBoardId[i]);
			if (NULL == poBoard){
				continue;
			}
			CString strBoard = poBoard->GetName(); // 单板名称；

			CString strCTmp = irit::GetXObjectFullName(arBoardId[i]);
			vctStrSlots.push_back(strCTmp.GetBuffer()); // 槽位名称；
			vctBoardId.push_back(arBoardId[i]);
		}
	}
}

void GetNeBoardNameFromID(CString &strNeName, CString &strBoardName, int BoardId, DWORD dwNeId)
{
	XNE_PTR poNe = GET_XNE(dwNeId);
	if (NULL != poNe){
		XDWORDTABLE arBoardId;
		poNe->GetBoards(arBoardId);
		strNeName = poNe->GetName();  // 网元名称；

		XBOARD_PTR poBoard = GET_XBOARD(BoardId);
		if (NULL == poBoard){
			return ;
		}
		strBoardName = poBoard->GetName(); // 单板名称；
	}
}

bool GetBoardFromKnowMsg(int &BoardId, string &strSlotName,DWORD dwNeId, WORD wKnowSetGroupNo, DWORD dwKnowSetBoardType, WORD wKnowSetSlotNo)
{
	XNE_PTR poNe = GET_XNE(dwNeId);
	if (NULL != poNe){
		XDWORDTABLE arBoardId;
		poNe->GetBoards(arBoardId);

		for (int i = 0; i < arBoardId.GetCount(); ++i){
			XBOARD_PTR poBoard = GET_XBOARD(arBoardId[i]);
			if (NULL == poBoard){
				continue;
			}

			WORD wSetGroupNo = poBoard->GetGroupNo();
			DWORD dwSetBoardType = poBoard->GetBoardType();

			const XBOARDPROP *pBoardProp = poBoard->GetBoardProp();
			WORD wSetSlotNo = pBoardProp->slotaddress;
			if ((wSetGroupNo == wKnowSetGroupNo) 
				&& (wKnowSetSlotNo == wSetSlotNo)
				&& (dwSetBoardType == dwKnowSetBoardType))
			{// 找到指定网元，槽位，上面的单盘id和槽位名称等信息；	
				BoardId = poBoard->GetBoardId();

				CString strCTmp = irit::GetXObjectFullName(arBoardId[i]);  // 槽位名称；
				strSlotName = strCTmp.GetBuffer(0);

				return true;
			}
		}
	}

	return false;
}


void GetMsgFromNeBoardID(CString &strNeName, CString &strBoardName, CString &strSlots,int BoardId, DWORD dwNeId)
{
	XNE_PTR poNe = GET_XNE(dwNeId);
	if (NULL != poNe){
		XDWORDTABLE arBoardId;
		poNe->GetBoards(arBoardId);
		strNeName = poNe->GetName();  // 网元名称；

		XBOARD_PTR poBoard = GET_XBOARD(BoardId);
		if (NULL == poBoard){
			return ;
		}
		strBoardName = poBoard->GetName(); // 单板名称；
		strSlots = irit::GetXObjectFullName(BoardId); // 槽位名称；
	}
}

/// void CRouteViewWnd::CRouteViewTraits::ParseRoute(const CPTNEthNodeData *pNode, CRouteTable *pTable,EETHServiceType eType)
void GetPortFullName(string &strPortName, int neType, EETHServiceType eType, int nAttributeType, int iVlanId, int iIndex,int iPwLabel)
{
	char buf[20] = "";
	bool b615Aor610A = false;
	if((neType == 265) || (neType== 270)){
		b615Aor610A = true;
	}

	if (b615Aor610A && E_TREE == eType){

		if (iVlanId > 0 && iVlanId < 4096){

			sprintf(buf, "%s.%d", strPortName.c_str(), iVlanId);
			strPortName = buf;
		}		
	}
	else if (ATTR_IPRAN_CES == nAttributeType){// 时隙
		if (iIndex > 0){
			if (iPwLabel > 0){
				sprintf(buf, "/%d.%d", iIndex, iPwLabel);
			}
			else{
				sprintf(buf, "/%d", iIndex);
			}
			strPortName = buf;
		}
	}
}

void OTNM2000GetNeconfigService::GetOneProtectSetToMongoDB(XC_PROTECT_RELATION &xcEthSvc, int nIndex)
{	
#if 1	
	m_pKey[nIndex] = BCON_NEW("_id", BCON_INT32(xcEthSvc.m_iId));
	BCON_APPEND(m_pKey[nIndex], "tableType", TABLE_PROTECT);			
	BCON_APPEND(m_pKey[nIndex], "activeState", BCON_INT32(xcEthSvc.m_eState));

	string strCurName = string_To_UTF8(xcEthSvc.m_sName);			
	BCON_APPEND(m_pKey[nIndex], "name", strCurName.c_str());// xxx

	BCON_APPEND(m_pKey[nIndex], "createTime", BCON_INT64(xcEthSvc.m_tmCreateTime));		
	strCurName = string_To_UTF8(xcEthSvc.m_sCreateUserName);
	BCON_APPEND(m_pKey[nIndex], "createUserName", strCurName.c_str());
	BCON_APPEND(m_pKey[nIndex], "modifyTime", BCON_INT64(xcEthSvc.m_tmModifyTime));	
	strCurName = string_To_UTF8(xcEthSvc.m_sModifyUserName);
	BCON_APPEND(m_pKey[nIndex], "modifyUserName", strCurName.c_str());		
	BCON_APPEND(m_pKey[nIndex], "netType", BCON_INT32(xcEthSvc.m_eNetType));//网络类型	
	BCON_APPEND(m_pKey[nIndex], "serviceLayer", BCON_INT32(xcEthSvc.m_eServiceLayer));//业务层次	
	BCON_APPEND(m_pKey[nIndex], "protectType", BCON_INT32(xcEthSvc.m_eProtectType));	// 保护类型
	BCON_APPEND(m_pKey[nIndex], "switchStatus", BCON_INT32(xcEthSvc.m_eSwitchStatus));// 倒换状态
	BCON_APPEND(m_pKey[nIndex], "waitForRestoreTime", BCON_INT32(xcEthSvc.m_iWaitForRestoreTime));// 等待恢复时间
	BCON_APPEND(m_pKey[nIndex], "returnType", BCON_INT32(xcEthSvc.m_eReturnType));	// 返回类型
	//双归保护组保护时
	BCON_APPEND(m_pKey[nIndex], "groupId", BCON_INT32(xcEthSvc.u.m_iGroupId));//双归保护组 ID
	BCON_APPEND(m_pKey[nIndex], "bfdId", BCON_INT32(xcEthSvc.u.m_iBfdId));//BFD ID	
	// 主备电路id  
	BCON_APPEND(m_pKey[nIndex], "mainCircuitId", BCON_INT32(xcEthSvc.m_iMainCircuitId));
	BCON_APPEND(m_pKey[nIndex], "backupCircuitId", BCON_INT32(xcEthSvc.m_iBackupCircuitId));	

#endif

#if 1
	/// 
	m_pKeyRef[nIndex] = BCON_NEW("_id", BCON_INT32(xcEthSvc.m_iId));
	bson_t childDataRef;
	bson_init(&childDataRef);
	BCON_APPEND(&childDataRef, "$ref", strTABLE_ProtectPair_data.c_str(), "$id", BCON_INT32(xcEthSvc.m_iId));					
	bson_append_document (m_pKeyRef[nIndex], "dataRef", -1, &childDataRef);
	bson_destroy(&childDataRef);

	bson_t childTunnellayer,childTunnellayerDoc;
	bson_init(&childTunnellayer);
	BCON_APPEND(&childTunnellayer, "$ref", strTABLE_Pw_data.c_str(), "$id", BCON_INT32(xcEthSvc.m_iMainCircuitId));				
	bson_init(&childTunnellayerDoc);
	bson_append_document (&childTunnellayerDoc, "0", -1, &childTunnellayer);
	bson_destroy(&childTunnellayer);
	bson_append_array(m_pKeyRef[nIndex], "dependenciesRef", -1, &childTunnellayerDoc);
	bson_destroy(&childTunnellayerDoc);

	bson_t childTunnellayerProtect,childTunnellayerProtectDoc;
	bson_init(&childTunnellayerProtect);			
	BCON_APPEND(&childTunnellayerProtect, "$ref", strTABLE_Pw_data.c_str(), "$id", BCON_INT32(xcEthSvc.m_iBackupCircuitId));		
	bson_init(&childTunnellayerProtectDoc);
	bson_append_document (&childTunnellayerProtectDoc, "0", -1, &childTunnellayerProtect);
	bson_destroy(&childTunnellayerProtect);

	bson_append_array(m_pKeyRef[nIndex], "dependenciesProtectRef", -1, &childTunnellayerProtectDoc);
	bson_destroy(&childTunnellayerProtectDoc);
#endif
}


DWORD DealThreadProtectFunction( LPVOID lpParam)
{
	stNeconfigService *stTmpNeconfigService = (stNeconfigService *)lpParam;
	OTNM2000GetNeconfigService *tmpThis = stTmpNeconfigService->tmpThis;
	int nIndex = stTmpNeconfigService->nIndex;		
	stThreadUse tmpData = tmpThis->m_tmpThreadUseData[nIndex];
	tmpThis->GetOneProtectSetToMongoDB(*(XC_PROTECT_RELATION*)(tmpData.Data), nIndex);

	return 0;
}

DWORD DealThreadL2Function( LPVOID lpParam)
{
	stNeconfigService *stTmpNeconfigService = (stNeconfigService *)lpParam;
	OTNM2000GetNeconfigService *tmpThis = stTmpNeconfigService->tmpThis;
	int nIndex = stTmpNeconfigService->nIndex;		
	stThreadUse tmpData = tmpThis->m_tmpThreadUseData[nIndex];	
	tmpThis->GetOneSrvL2vpnSetToMongoDB(*(XC_ETH_SERVICE*)(tmpData.Data), nIndex);

	return 0;
}

DWORD DealThreadL3Function( LPVOID lpParam)
{
	stNeconfigService *stTmpNeconfigService = (stNeconfigService *)lpParam;
	OTNM2000GetNeconfigService *tmpThis = stTmpNeconfigService->tmpThis;
	int nIndex = stTmpNeconfigService->nIndex;		
	stThreadUse tmpData = tmpThis->m_tmpThreadUseData[nIndex];
	tmpThis->GetOneSrvL3vpnSetToMongoDB(*(XC_IPRAN_L3VPN_SERVICE*)(tmpData.Data), nIndex);

	return 0;
}

DWORD DealThreadRingFunction( LPVOID lpParam)
{
	stNeconfigService *stTmpNeconfigService = (stNeconfigService *)lpParam;
	OTNM2000GetNeconfigService *tmpThis = stTmpNeconfigService->tmpThis;
	int nIndex = stTmpNeconfigService->nIndex;		
	stThreadUse tmpData = tmpThis->m_tmpThreadUseData[nIndex];
	tmpThis->GetOneRingSetToMongoDB(*(XC_RING*)(tmpData.Data), nIndex);

	return 0;
}

void OTNM2000GetNeconfigService::GetRingBandDataToMap(XC_CIRCUIT &tmpOneCircuit, int nTypeIndex)
{
	if(tmpOneCircuit.m_eServiceLayer != PTN_LAYER_TMP){// tunnel
		return ; // 只有tunnel才查环；
	}

	VEC_XC_RING_BIND vecXCRingBind;
	bool bCalc = false; // 只有勾选的环路径才会被查出来；
	int iPathIndex = 0; 

	ERROR_CODE_EX eCode = MutiServPlatform::SNC_GetRingBinding(m_hSess, 
		tmpOneCircuit, iPathIndex, bCalc, vecXCRingBind);
	if(ERR_OK != eCode){
		char buf[256] = "";
		sprintf(buf, "GetRingBandDataToMap fail! tunnel id:%d;\n", tmpOneCircuit.m_iId);
		WriteLog(buf);	
		int iRet = ConnectNetClient(1, ".\\");
		if ((iRet == -1) || (iRet == -2)){	
			sprintf(buf, "GetRingBandDataToMap reconnect fail! tunnel id:%d;\n", tmpOneCircuit.m_iId);
			WriteLog(buf);
			return;
		}

		eCode = MutiServPlatform::SNC_GetRingBinding(m_hSess, 
			tmpOneCircuit, iPathIndex, bCalc, vecXCRingBind);
		if (ERR_OK != eCode){
			sprintf(buf, "GetRingBandDataToMap reGet fail! tunnel id:%d;\n", tmpOneCircuit.m_iId);
			WriteLog(buf);
			return;
		}
	}

	for (int k = 0; k < (int)vecXCRingBind.size(); ++k){

		int nRingID = vecXCRingBind[k].m_iRingId;
		if (mapFromRinglIDGetTunnel.find(nRingID) != mapFromRinglIDGetTunnel.end()){

			map<int, char> &tmpOneTunnel = mapFromRinglIDGetTunnel[nRingID];
			if (tmpOneTunnel.find(tmpOneCircuit.m_iId) == tmpOneTunnel.end()){

				tmpOneTunnel[tmpOneCircuit.m_iId] = 1;
			}
			else{
				continue;
			}
		}
		else{
			map<int, char> tmpOneTunnel;
			tmpOneTunnel[tmpOneCircuit.m_iId] = 1;
			mapFromRinglIDGetTunnel[nRingID] = tmpOneTunnel;
		}	
	}
}


DWORD DealThreadeCircuitsFunction(LPVOID lpParam)
{// 电路分pw,tunnel...
	stNeconfigService *stTmpNeconfigService = (stNeconfigService *)lpParam;
	OTNM2000GetNeconfigService *tmpThis = stTmpNeconfigService->tmpThis;
	int nIndex = stTmpNeconfigService->nIndex;
	int nTypeIndex = stTmpNeconfigService->nTypeIndex;
	stThreadUse tmpData = tmpThis->m_tmpThreadUseData[nIndex];

	string strOtnWave="";
	int nFirstLabel = 0;
	tmpThis->AddPathToMongoTable(*(XC_CIRCUIT*)(tmpData.Data), nIndex, strOtnWave, nFirstLabel);
	tmpThis->GetOneCircuitsSetToMongoDB(*(XC_CIRCUIT*)(tmpData.Data), nIndex, nTypeIndex, strOtnWave, nFirstLabel);
	tmpThis->GetRingBandDataToMap(*(XC_CIRCUIT*)(tmpData.Data), nTypeIndex);

	return 0;
}

void OTNM2000GetNeconfigService::ThreadReladySetCircusToMongoDB(int nThreadNum, FuncCallToDB pFun)
{
#if 1
	if (nThreadNum <=0){
		return ;
	}
	int nPw=0,nTunnel=0,nOch=0,nClient=0,nOduk=0,nAllType=0,nOther=0,nOms=0,nOts=0,i;
	stNeconfigService *stTmpNeconfigService = new stNeconfigService[nThreadNum];
	if (stTmpNeconfigService == NULL){
		WriteLog("ThreadReladySetCircusToMongoDB mem lost Failure");
		return;
	}

#if IfDealSingleThread
	for (i = 0; i < nThreadNum; ++i){
		stTmpNeconfigService[i].tmpThis = this;
		stTmpNeconfigService[i].nIndex = i; // 合表ID

		// 分表ID
		if(m_tmpThreadUseData[i].eType == eTunnel){// tunnel
			stTmpNeconfigService[i].nTypeIndex = nTunnel++;
		}
		else if(m_tmpThreadUseData[i].eType == ePw){// pw
			stTmpNeconfigService[i].nTypeIndex = nPw++;
		}
		else if(m_tmpThreadUseData[i].eType == eOts){// pw
			stTmpNeconfigService[i].nTypeIndex = nOts++;
		}
		else if(m_tmpThreadUseData[i].eType == eOms){// pw
			stTmpNeconfigService[i].nTypeIndex = nOms++;
		}
		else if(m_tmpThreadUseData[i].eType == eOch){// pw
			stTmpNeconfigService[i].nTypeIndex = nOch++;
		}
		else if(m_tmpThreadUseData[i].eType == eOduk){// pw
			stTmpNeconfigService[i].nTypeIndex = nOduk++;
		}
		else if(m_tmpThreadUseData[i].eType == eClient){// pw
			stTmpNeconfigService[i].nTypeIndex = nClient++;
		}
		else{// 除了tunnel,pw,oclient,och,oduk以外的所有电路，不会写入数据库；
			stTmpNeconfigService[i].nTypeIndex=nOther++; //
		}

		pFun((void*)&stTmpNeconfigService[i]);
	}

#else

	HANDLE  hThreadArray[nDealArrayThreadNum]; 
	for (i = 0; i < nThreadNum; i++){
		stTmpNeconfigService[i].tmpThis = this;
		stTmpNeconfigService[i].nIndex = i;		
		if(m_tmpThreadUseData[i].eType == eTunnel){// tunnel
			stTmpNeconfigService[i].nTypeIndex = nTunnel++;
		}
		else if(m_tmpThreadUseData[i].eType == ePw){// pw
			stTmpNeconfigService[i].nTypeIndex = nPw++;
		}
		else if(m_tmpThreadUseData[i].eType == eOch){// pw
			stTmpNeconfigService[i].nTypeIndex = nOch++;
		}
		else if(m_tmpThreadUseData[i].eType == eOduk){// pw
			stTmpNeconfigService[i].nTypeIndex = nOduk++;
		}
		else if(m_tmpThreadUseData[i].eType == eClient){// pw
			stTmpNeconfigService[i].nTypeIndex = nClient++;
		}
		else{
			stTmpNeconfigService[i].nTypeIndex=nOther++;
		}

		hThreadArray[i] = CreateThread( 
			NULL,                   // default security attributes
			nThreadSize,                    // use default stack size  
			(LPTHREAD_START_ROUTINE)pFun,       // thread function name
			(void*)&stTmpNeconfigService[i],          // argument to thread function 
			0,                      // use default creation flags 
			0); // returns the thread identifier 

		if (hThreadArray[i] == NULL)
		{// 连续创建200个以上线程，会导致某些线程创建失败，导致insertMany有空的值,插入数据崩溃；
			hThreadArray[i] = CreateThread( 
				NULL,                   // default security attributes
				nThreadSize,                      // use default stack size  
				(LPTHREAD_START_ROUTINE)pFun,       // thread function name
				(void*)&stTmpNeconfigService[i],          // argument to thread function 
				0,                      // use default creation flags 
				0); // returns the thread identifier 			
		}					
	}

	::WaitForMultipleObjects(nThreadNum, hThreadArray, TRUE, INFINITE);
	for(int i=0; i<nThreadNum; i++){
		CloseHandle(hThreadArray[i]);	
	}
#endif

#if DEFINE_MONGO_INSERT
	if(!m_MongoDBOperator.InsertMany(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_PATH.c_str(), m_pKey, nThreadNum)){		
		bIfTableUpdateRight = false;  // 进度设置为-1；
		g_bStopMongoDBTheard = true;  // 如果有数据缺少，则中断此次任务 ；
		char bufLog[512]="";			
		sprintf(bufLog, "ThreadReladySetCircusToMongoDB Insert path %s Failure\n", strTABLE_PATH.c_str());
		WriteLog(bufLog);	
	}

	//###############	
	mapTotalCount[neCircuits].mapDetailCount[nePw].nGetLen += nPw;
	mapTotalCount[neCircuits].mapDetailCount[neTunnel].nGetLen += nTunnel;
	mapTotalCount[neCircuits].mapDetailCount[neOts].nGetLen += nOts;
	mapTotalCount[neCircuits].mapDetailCount[neOms].nGetLen += nOms;
	mapTotalCount[neCircuits].mapDetailCount[neOch].nGetLen += nOch;
	mapTotalCount[neCircuits].mapDetailCount[neClient].nGetLen += nClient;
	mapTotalCount[neCircuits].mapDetailCount[neOduk].nGetLen += nOduk;
	mapTotalCount[neCircuits].mapDetailCount[neCircuits_other].nGetLen += nOther;
	//###############

	if (nPw != 0){
		int nRet = SetCircusToMongoDB(strTABLE_Pw_data, m_pKeyDataPwRef, strTABLE_Pw, m_pKeyPwRef, nPw);	
		if ((nRet & 1) != 1){// ref表	
			mapTotalCount[neCircuits].mapDetailCount[nePw].nDBMongoRefLen += nPw;
		}
		if ((nRet & 2) != 2){// 数据表
			mapTotalCount[neCircuits].mapDetailCount[nePw].nDBMongoLen += nPw;
		}
	}

	if (nTunnel != 0){
		int nRet = SetCircusToMongoDB(strTABLE_Tunnel, m_pKeyTunnelRef, strTABLE_Tunnel_data, m_pKeyRef, nTunnel);			
		if ((nRet & 1) != 1){// ref表	
			mapTotalCount[neCircuits].mapDetailCount[neTunnel].nDBMongoRefLen += nTunnel;
		}
		if ((nRet & 2) != 2){// 数据表
			mapTotalCount[neCircuits].mapDetailCount[neTunnel].nDBMongoLen += nTunnel;
		}
	}

	if (nOts != 0){
		int nRet = SetCircusToMongoDB(strTABLE_Ots, m_pKeyOTSRef, strTABLE_Ots_data, m_pKeyDataOTSRef, nOts);			
		if ((nRet & 1) != 1){// ref表	
			mapTotalCount[neCircuits].mapDetailCount[neOts].nDBMongoRefLen += nOts;
		}
		if ((nRet & 2) != 2){// 数据表
			mapTotalCount[neCircuits].mapDetailCount[neOts].nDBMongoLen += nOts;
		}
	}
	if (nOms != 0){
		int nRet = SetCircusToMongoDB(strTABLE_Oms, m_pKeyOmsRef, strTABLE_Oms_data, m_pKeyDataOmsRef, nOms);			
		if ((nRet & 1) != 1){// ref表	
			mapTotalCount[neCircuits].mapDetailCount[neOms].nDBMongoRefLen += nOms;
		}
		if ((nRet & 2) != 2){// 数据表
			mapTotalCount[neCircuits].mapDetailCount[neOms].nDBMongoLen += nOms;
		}
	}

	if (nOch != 0){
		int nRet = SetCircusToMongoDB(strTABLE_Och, m_pKeyOchRef, strTABLE_Och_data, m_pKeyDataOchRef, nOch);								
		if ((nRet & 1) != 1){// ref表	
			mapTotalCount[neCircuits].mapDetailCount[neOch].nDBMongoRefLen += nOch;
		}
		if ((nRet & 2) != 2){// 数据表
			mapTotalCount[neCircuits].mapDetailCount[neOch].nDBMongoLen += nOch;
		}
	}

	if (nOduk != 0){
		int nRet = SetCircusToMongoDB(strTABLE_oduk, m_pKeyOdukRef, strTABLE_oduk_data, m_pKeyDataOdukRef, nOduk);					
		if ((nRet & 1) != 1){// ref表	
			mapTotalCount[neCircuits].mapDetailCount[neOduk].nDBMongoRefLen += nOduk;
		}
		if ((nRet & 2) != 2){// 数据表
			mapTotalCount[neCircuits].mapDetailCount[neOduk].nDBMongoLen += nOduk;
		}
	}

	if (nClient != 0){
		int nRet = SetCircusToMongoDB(strTABLE_client, m_pKeyClientRef, strTABLE_client_data, m_pKeyDataClientRef, nClient);		
		if ((nRet & 1) != 1){// ref表	
			mapTotalCount[neCircuits].mapDetailCount[neClient].nDBMongoRefLen += nClient;
		}
		if ((nRet & 2) != 2){// 数据表
			mapTotalCount[neCircuits].mapDetailCount[neClient].nDBMongoLen += nClient;
		}
	}

	for (i=0;i<nThreadNum;i++){

		if (i<nPw){
			bson_destroy(m_pKeyPwRef[i]);
			bson_destroy(m_pKeyDataPwRef[i]);
		}
		if (i<nTunnel){
			bson_destroy(m_pKeyRef[i]);	
			bson_destroy(m_pKeyTunnelRef[i]);
		}

		if (i<nOts){
			bson_destroy(m_pKeyOTSRef[i]);	
			bson_destroy(m_pKeyDataOTSRef[i]);
		}
		if (i<nOms){
			bson_destroy(m_pKeyOmsRef[i]);	
			bson_destroy(m_pKeyDataOmsRef[i]);
		}

		if (i<nOch){
			bson_destroy(m_pKeyOchRef[i]);	
			bson_destroy(m_pKeyDataOchRef[i]);
		}
		if (i<nClient){
			bson_destroy(m_pKeyDataClientRef[i]);
			bson_destroy(m_pKeyClientRef[i]);
		}
		if (i<nOduk){
			bson_destroy(m_pKeyDataOdukRef[i]);
			bson_destroy(m_pKeyOdukRef[i]);
		}

		bson_destroy(m_pKey[i]);	
	}

#endif

	delete [] stTmpNeconfigService;
	stTmpNeconfigService = NULL;
#endif

}

void OTNM2000GetNeconfigService::SetRingMapToMongoDB()
{
	int nRouteSize = mapFromRinglIDGetTunnel.size();
	char bufLog[256]="";
	sprintf(bufLog, "RingMap size:%d\n", nRouteSize);
	WriteLog(bufLog);
	if (nRouteSize == 0){
		return ;
	}

	pBson*childSrcPathInfo = new pBson[nRouteSize];
	if (childSrcPathInfo == NULL){
		return;
	}

	int i = 0;
	char tmpBuf[20]="";
	for (map<int, map<int, char>>::iterator iter = mapFromRinglIDGetTunnel.begin(); iter != mapFromRinglIDGetTunnel.end(); iter++,++i){

		childSrcPathInfo[i] = BCON_NEW("ringId", BCON_INT32(iter->first));
		BCON_APPEND(childSrcPathInfo[i], "tableType", TABLE_RINGBAND);

		int j = 0;
		bson_t childdoc;
		bson_init(&childdoc);
		map<int, char> &tmpMapTunnel = iter->second;
		for (map<int, char>::iterator iterTunnel = tmpMapTunnel.begin(); iterTunnel != tmpMapTunnel.end(); iterTunnel++,j++){

			sprintf(tmpBuf,"%d", j);
			BCON_APPEND(&childdoc, tmpBuf, BCON_INT32(iterTunnel->first));
		}	
		//	bson_append_document (childSrcPathInfo[i], "tunnelList", -1, &childdoc);
		bson_append_array(childSrcPathInfo[i], "tunnels", -1, &childdoc);
		bson_destroy(&childdoc);
	}


#if DEFINE_MONGO_INSERT
	if(!m_MongoDBOperator.InsertMany(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_RingBandingTunnel.c_str(), childSrcPathInfo, nRouteSize)){
		// log新增数据失败；
		bIfTableUpdateRight = false;
		g_bStopMongoDBTheard = true;  // 如果有数据缺少，则中断此次任务 ；
		WriteLog("Insert SetRingMapToMongoDB Failure");	
	}
#endif	

	for (i=0;i<nRouteSize;++i){
		bson_destroy(childSrcPathInfo[i]);
	}
	delete [] childSrcPathInfo;
	childSrcPathInfo = NULL;
}

//void OTNM2000GetNeconfigService::SetCircusToMongoDB(const string &strTableRef, bson_t *m_pKeyRef[nDealArrayThreadNum], const string &strTableData, bson_t *m_pKeyDataRef[nDealArrayThreadNum],int nNum)
//{
//	if(!m_MongoDBOperator.InsertMany(m_MongoDBOperator.m_strTableName.c_str(), strTableRef.c_str(), m_pKeyRef, nNum)){		
//		bIfTableUpdateRight = false;  // path
//		char bufLog[512]="";			
//		sprintf(bufLog, "ThreadReladySetCircusToMongoDB Insert %s Failure\n", strTableRef.c_str());
//		WriteLog(bufLog);		
//	}
//	if(!m_MongoDBOperator.InsertMany(m_MongoDBOperator.m_strTableName.c_str(), strTableData.c_str(), m_pKeyDataRef, nNum)){		
//		bIfTableUpdateRight = false;  // data
//
//		char bufLog[512]="";			
//		sprintf(bufLog, "ThreadReladySetCircusToMongoDB Insert %s Failure\n", strTableData.c_str());
//		WriteLog(bufLog);
//	}
//}

int  OTNM2000GetNeconfigService::SetCircusToMongoDB(const string &strTableRef, bson_t *m_pKeyRef[nDealArrayThreadNum], const string &strTableData, bson_t *m_pKeyDataRef[nDealArrayThreadNum],int nNum)
{
	int nRet = 0;
	if(!m_MongoDBOperator.InsertMany(m_MongoDBOperator.m_strTableName.c_str(), strTableRef.c_str(), m_pKeyRef, nNum)){		
		bIfTableUpdateRight = false;  // path
		g_bStopMongoDBTheard = true;  // 如果有数据缺少，则中断此次任务 ；

		char bufLog[512]="";			
		sprintf(bufLog, "ThreadReladySetCircusToMongoDB Insert %s Failure\n", strTableRef.c_str());
		WriteLog(bufLog);	
		nRet |= 1;
	}
	if(!m_MongoDBOperator.InsertMany(m_MongoDBOperator.m_strTableName.c_str(), strTableData.c_str(), m_pKeyDataRef, nNum)){		
		bIfTableUpdateRight = false;  // data
		g_bStopMongoDBTheard = true;  // 如果有数据缺少，则中断此次任务 ；

		char bufLog[512]="";			
		sprintf(bufLog, "ThreadReladySetCircusToMongoDB Insert %s Failure\n", strTableData.c_str());
		WriteLog(bufLog);
		nRet |= 2;
	}

	return nRet;
}

void OTNM2000GetNeconfigService::ThreadReladySetToMongoDB(int nThreadNum, FuncCallToDB pFun)
{
#if 1
	if (nThreadNum <=0){
		return ;
	}

	stNeconfigService *stTmpNeconfigService = new stNeconfigService[nThreadNum];
	if (stTmpNeconfigService == NULL){
		WriteLog("ThreadReladySetToMongoDB mem lost Failure");

		return;
	}

	//	nThreadNum -= 20; // 测试缺失的情况；

#if IfDealSingleThread
	for (int i = 0; i < nThreadNum; i++){
		stTmpNeconfigService[i].tmpThis = this;
		stTmpNeconfigService[i].nIndex = i;

		pFun((void*)&stTmpNeconfigService[i]);
	}	
#else

	HANDLE  hThreadArray[nDealArrayThreadNum]; 
	for (int i = 0; i < nThreadNum; i++){  
		stTmpNeconfigService[i].tmpThis = this;
		stTmpNeconfigService[i].nIndex = i;

		hThreadArray[i] = CreateThread( 
			NULL,                   // default security attributes
			nThreadSize,                      // use default stack size  
			(LPTHREAD_START_ROUTINE)pFun,       // thread function name
			(void*)&stTmpNeconfigService[i],          // argument to thread function 
			0,                      // use default creation flags 
			0); // returns the thread identifier 
		if (hThreadArray[i] == NULL)
		{// 连续创建800个线程，会导致某些线程创建成功，但是未执行或是执行会失败，导致insertMany有空的值,插入数据崩溃；
			hThreadArray[i] = CreateThread( 
				NULL,                   // default security attributes
				nThreadSize,                      // use default stack size  
				(LPTHREAD_START_ROUTINE)pFun,       // thread function name
				(void*)&stTmpNeconfigService[i],          // argument to thread function 
				0,                      // use default creation flags 
				0); // returns the thread identifier
		}
	}

	::WaitForMultipleObjects(nThreadNum, hThreadArray, TRUE, INFINITE);
	for(int i=0; i<nThreadNum; i++){
		CloseHandle(hThreadArray[i]);	
	}

#endif

	string strBaseMainTable = "",strTABLE_BizDataInfos="";
	switch (m_tmpThreadUseData[0].eType){

	case eL3vpn:
		strBaseMainTable=strTABLE_L3vpn;
		strTABLE_BizDataInfos=strTABLE_L3vpn_data;
		break;
	case eL2vpn:
		strBaseMainTable=strTABLE_L2vpn;
		strTABLE_BizDataInfos=strTABLE_L2vpn_data;
		break;
	case eRing:
		strBaseMainTable=strTABLE_Ring;
		strTABLE_BizDataInfos=strTABLE_Ring_data;
		break;
	case eProtect:
		strBaseMainTable=strTABLE_ProtectPair;
		strTABLE_BizDataInfos=strTABLE_ProtectPair_data;
		break;
	}

#if DEFINE_MONGO_INSERT
	bool bMongoRefRight = true, bMongoRight = true;
	if(!m_MongoDBOperator.InsertMany(m_MongoDBOperator.m_strTableName.c_str(), strBaseMainTable.c_str(), m_pKeyRef, nThreadNum)){
		// log新增数据失败；
		bIfTableUpdateRight = false;
		g_bStopMongoDBTheard = true;  // 如果有数据缺少，则中断此次任务 ；

		char bufLog[512]="";			
		sprintf(bufLog, "Insert %s ref Failure\n", strBaseMainTable.c_str());
		WriteLog(bufLog);
		bMongoRefRight = false; // mongo ref表数据异常；
	}

	if(!m_MongoDBOperator.InsertMany(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_BizDataInfos.c_str(), m_pKey, nThreadNum)){
		// log新增数据失败；
		bIfTableUpdateRight = false;	
		g_bStopMongoDBTheard = true;  // 如果有数据缺少，则中断此次任务 ；

		char bufLog[512]="";			
		sprintf(bufLog, "Insert ThreadReladySetToMongoDB Failure:%s\n", strTABLE_BizDataInfos.c_str());
		WriteLog(bufLog);
		bMongoRight = false; // mongo 数据异常； 
	}

	switch (m_tmpThreadUseData[0].eType){
	case eL2vpn:
		{
			map<TypeAll,  stDetailCount> &mapCurrentDetailCount = mapTotalCount[neL2vpn].mapDetailCount;
			mapCurrentDetailCount[neL2vpn].nGetLen += nThreadNum;

			if (bMongoRefRight){
				mapCurrentDetailCount[neL2vpn].nDBMongoRefLen += nThreadNum;
			}
			if(bMongoRight){
				mapCurrentDetailCount[neL2vpn].nDBMongoLen += nThreadNum;
			}
		}
		break;
	case eL3vpn:
		{
			map<TypeAll,  stDetailCount> &mapCurrentDetailCount = mapTotalCount[neL3vpn].mapDetailCount;			
			mapCurrentDetailCount[neL3vpn].nGetLen += nThreadNum;

			if (bMongoRefRight){
				mapCurrentDetailCount[neL3vpn].nDBMongoRefLen += nThreadNum;
			}
			if(bMongoRight){
				mapCurrentDetailCount[neL3vpn].nDBMongoLen += nThreadNum;
			}
		}
		break;	
	case eRing:
		{			
			map<TypeAll,  stDetailCount> &mapCurrentDetailCount = mapTotalCount[neRing].mapDetailCount;		
			mapCurrentDetailCount[neRing].nGetLen += nThreadNum;

			if (bMongoRefRight){
				mapCurrentDetailCount[neRing].nDBMongoRefLen += nThreadNum;
			}
			if(bMongoRight){
				mapCurrentDetailCount[neRing].nDBMongoLen += nThreadNum;
			}
		}
		break;
	case eProtect:
		{
			map<TypeAll,  stDetailCount> &mapCurrentDetailCount = mapTotalCount[neProtect].mapDetailCount;			
			mapCurrentDetailCount[neProtect].nGetLen += nThreadNum;

			if (bMongoRefRight){
				mapCurrentDetailCount[neProtect].nDBMongoRefLen += nThreadNum;
			}
			if(bMongoRight){
				mapCurrentDetailCount[neProtect].nDBMongoLen += nThreadNum;
			}
		}
		break;
	}
#endif

	for (int i=0;i<nThreadNum;++i){
		bson_destroy(m_pKeyRef[i]);	
		bson_destroy(m_pKey[i]);	
	}
	delete [] stTmpNeconfigService;
	stTmpNeconfigService = NULL;
#endif
}


void OTNM2000GetNeconfigService::GetAllProtectSetToMongoDB(double fBegin, double fAdd,const std::string &strLogDir)
{	
	try{
		string strDetail = "";
		double fProgess = 0;
		char bufProgess[200]="";
		HSESSION hSession = -1;
		ERROR_CODE_EX eCode = 0;
		Json::Value valcontext;
		vector<XC_PROTECT_RELATION> vectEthService;

		FuncCallToDB pFun = DealThreadProtectFunction;

		///// 登录获取session;
		ERROR_CODE iRet = ConnectNetClient(2, strLogDir);
		if (iRet == -1){
			WriteLog("GetAllProtectSetToMongoDB InitMSMPClient Failure");		
			UpdateTaskID(-1);	
			strCloseLog = "GetAllProtectSetToMongoDB InitMSMPClient Failure\n";	
			goto endLast;
		}
		else if (iRet == -2){
			WriteLog("GetAllProtectSetToMongoDB Opensession Failure");
		//	SendMongoDBResultState(g_strPipNoFunInterFace.c_str(), "2002");
			UpdateTaskID(-1);
			strCloseLog = "GetAllProtectSetToMongoDB Opensession Failure\n";	
			goto endInitClient;
		} 
		///// 登录获取session; end;	
	//	SendMongoDBResultState(g_strPipNoFunInterFace.c_str(), "1");

		eCode = SNC_GetAllProtectRelation(m_hSess, vectEthService); // 获得所有的业务数据；
		if (ERR_OK == eCode){

			//###############
			mapTotalCount[neProtect].nTotalLen = vectEthService.size();									
			//###############

			printf("XC_PROTECT_RELATION size:%d\n", vectEthService.size());
			char bufLog[512]="";			
			sprintf(bufLog, "XC_PROTECT_RELATION size:%d\n", vectEthService.size());
			WriteLog(bufLog);

			int nAllSrcNum = vectEthService.size();
			int ik=0,nTmpBegin = 0;	
			for(int ij=0; ij<nAllSrcNum;++ij){

				if (g_bStopMongoDBTheard){
					break;
				}

				if (ij!=0 && (ij%(nAllSrcNum/50+1)==0)){

					fProgess = ((double)ij/nAllSrcNum)*fAdd+fBegin;
					sprintf(bufProgess, "PROTECT_RELATION Progess:%f", fProgess);
					strDetail = bufProgess;
					UpdateTaskID(fProgess, strDetail);
				}

				if (ik == (nDealArrayThreadNum-1)) {

					m_tmpThreadUseData[ik].eType = eProtect;
					m_tmpThreadUseData[ik].Data = &vectEthService[ij];
					ThreadReladySetToMongoDB(nDealArrayThreadNum, pFun);									
					ik=0;
					nTmpBegin+=nDealArrayThreadNum;
				}
				else if ((nTmpBegin+nDealArrayThreadNum ) >= nAllSrcNum && (nTmpBegin<nAllSrcNum)){

					int nCntLess = nAllSrcNum - nTmpBegin;
					for (ik=0; ik<nCntLess; ++ik){
						m_tmpThreadUseData[ik].eType = eProtect;
						m_tmpThreadUseData[ik].Data = &vectEthService[ij++];
					}
					ThreadReladySetToMongoDB(nCntLess, pFun);									
					break;
				}
				else{
					m_tmpThreadUseData[ik].eType = eProtect;
					m_tmpThreadUseData[ik].Data = &vectEthService[ij];
					++ik;
				}
			}
		}
		else{
			strCloseLog = "SNC_GetAllProtectRelation Get Null data!";
		}

endCloseSession:
		MutiServPlatform::SNC_CloseSession(m_hSess);  

endInitClient:
		MutiServPlatform::DeInitMSMPClient();    

endLast:
		return ;
	}
	catch(...){
		WriteLog("GetAllProtectSetToMongoDB catch error!\n");
	}
	return ;
}

void OTNM2000GetNeconfigService::GetOneSrvL3vpnSetToMongoDB(XC_IPRAN_L3VPN_SERVICE &xcEthSvc, int nIndex)
{
	m_pKey[nIndex] = BCON_NEW("_id", BCON_INT32(xcEthSvc.m_iId));

	BCON_APPEND(m_pKey[nIndex], "tableType", TABLE_L3VPN);
	BCON_APPEND(m_pKey[nIndex], "rdValue", xcEthSvc.m_sRDValue.c_str());
	BCON_APPEND(m_pKey[nIndex], "activeState", BCON_INT32(xcEthSvc.m_eState));	
	string strCurName = string_To_UTF8(xcEthSvc.m_sName);
	BCON_APPEND(m_pKey[nIndex], "name", strCurName.c_str());
	BCON_APPEND(m_pKey[nIndex], "createTime", BCON_INT64(xcEthSvc.m_tmCreateTime));		
	strCurName = string_To_UTF8(xcEthSvc.m_sCreateUserName);
	BCON_APPEND(m_pKey[nIndex], "createUserName", strCurName.c_str());
	BCON_APPEND(m_pKey[nIndex], "modifyTime", BCON_INT64(xcEthSvc.m_tmModifyTime));	
	strCurName = string_To_UTF8(xcEthSvc.m_sModifyUserName);
	BCON_APPEND(m_pKey[nIndex], "modifyUserName", strCurName.c_str());
	strCurName = string_To_UTF8(xcEthSvc.m_sUserLabel);
	BCON_APPEND(m_pKey[nIndex], "userLabel",  strCurName.c_str());//用户标签		
	strCurName = string_To_UTF8(xcEthSvc.m_sServiceName);
	BCON_APPEND(m_pKey[nIndex], "serviceName", strCurName.c_str()); //业务名称
	BCON_APPEND(m_pKey[nIndex], "serviceClass", BCON_INT32(xcEthSvc.m_iServiceClass));//业务分类


	/////////// l3vpn ref;
	// xcEthSvc.m_iId = 587221461;				 
	m_pKeyRef[nIndex] = BCON_NEW("_id", BCON_INT32(xcEthSvc.m_iId));

	///// 设置pw，tunnel，l2vpn的关联关系； => l2,l3,pw,tunnel,可以合并这部分的代码；		
	GetMongoBusinessLayerRelation(m_pKeyRef[nIndex], OT_L3VPN, IPRAN_LAYER_L3VPN, xcEthSvc.m_iId);					
	///// 设置pw，tunnel，l2vpn的关联关系；

	if (xcEthSvc.m_lstPE.size() > 0){

		char buf[20]="";
		int iz=0, iPe=0, iUni=0, iTunnel=0;	
		bson_t peList;
		bson_init(&peList);

		for (list<XC_IPRAN_L3VPN_PE>::iterator iter=xcEthSvc.m_lstPE.begin(); iter!=xcEthSvc.m_lstPE.end(); iter++){
			if (g_bStopMongoDBTheard){
				break;
			}

			//	string &L2L3RelateListName = iter->m_sL2L3RelateListName; // => 怎么跟l2的关联

			XC_IPRAN_L3VPN_PE_BASIC &stBasic=iter->m_stBasic;
			bson_t onePeList;
			bson_init(&onePeList);
			//	BCON_APPEND(&onePeList, "neId", BCON_INT32(iter->m_iNeId));

			bson_t childPeNeDataRef;
			bson_init(&childPeNeDataRef);  //对端PE 网元id
			BCON_APPEND(&childPeNeDataRef, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(iter->m_iNeId));					
			bson_append_document (&onePeList, "neNameRef", -1, &childPeNeDataRef);
			bson_destroy(&childPeNeDataRef);

			BCON_APPEND(&onePeList, "VrfId", BCON_INT32(stBasic.m_iVrfId));
			BCON_APPEND(&onePeList, "ActiveState", BCON_INT32((int)stBasic.m_eActiveState));
			strCurName = string_To_UTF8(stBasic.m_sRTImport);
			BCON_APPEND(&onePeList, "RTImport", strCurName.c_str());
			strCurName = string_To_UTF8(stBasic.m_sRTExport);
			BCON_APPEND(&onePeList, "RTExport", strCurName.c_str());
			strCurName = string_To_UTF8(stBasic.m_sRDValue);
			BCON_APPEND(&onePeList, "RDValue", strCurName.c_str());

			if(iter->m_lstUNIs.size() > 0){

				bson_t uniList;
				bson_init(&uniList);
				iUni=0;
				list<XC_IPRAN_L3VPN_UNI> &lstUNIs=iter->m_lstUNIs;
				for(list<XC_IPRAN_L3VPN_UNI>::iterator iterUni = lstUNIs.begin(); iterUni != lstUNIs.end(); iterUni++){
					bson_t uniOne;
					bson_init(&uniOne);
					//	BCON_APPEND(&uniOne, "neId", BCON_INT32(iter->m_iNeId));
					BCON_APPEND(&uniOne, "ActiveState", BCON_INT32((int)iterUni->m_eActiveState));
					strCurName = string_To_UTF8(iterUni->m_sUNI);
					BCON_APPEND(&uniOne, "RTImport", strCurName.c_str());

					sprintf(buf, "%d", iUni++);
					bson_append_document(&uniList, buf, -1, &uniOne);
					bson_destroy(&uniOne);
				}
				bson_append_array(&onePeList, "uniList", -1, &uniList);
				bson_destroy(&uniList);
			}

			if (iter->m_lstCircuit.size() > 0){

				//lsp电路id和策略列表，只在此PE节点的lsp
				bson_t tunnelList;
				bson_init(&tunnelList);
				iTunnel=0;
				list<XC_IPRAN_L3VPN_TUNNEL> &lstCircuit=iter->m_lstCircuit;
				for (list<XC_IPRAN_L3VPN_TUNNEL>::iterator iterTunnel = lstCircuit.begin(); iterTunnel != lstCircuit.end(); iterTunnel++){

					XC_IPRAN_L3VPN_TUNNEL &tmpOneTunnel = *iterTunnel;
					bson_t tunnelOne;
					bson_init(&tunnelOne);
					BCON_APPEND(&tunnelOne, "ActiveState", BCON_INT32((int)tmpOneTunnel.m_eActiveState));				
					BCON_APPEND(&tunnelOne, "Policy", BCON_INT32((int)tmpOneTunnel.m_ePolicy));  //LSP策略

					bson_t childDataRefTunnel;
					bson_init(&childDataRefTunnel);
					BCON_APPEND(&childDataRefTunnel, "$ref", strTABLE_Tunnel_data.c_str(), "$id", BCON_INT32(tmpOneTunnel.m_iCircuitId));					
					bson_append_document (&tunnelOne, "tunnelIdRef", -1, &childDataRefTunnel);
					bson_destroy(&childDataRefTunnel);

					bson_t childDataRef;
					bson_init(&childDataRef);  //对端PE 网元id
					BCON_APPEND(&childDataRef, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(tmpOneTunnel.m_iPeerPEId));					
					bson_append_document (&tunnelOne, "PeerPEneIdRef", -1, &childDataRef);
					bson_destroy(&childDataRef);

					//	BCON_APPEND(&tunnelOne, "TunnelCalcTransitRoute", BCON_INT32(tmpOneTunnel.m_bTunnelCalcTransitRoute?1:0));  //该tunnel是否计算中转路由						
					//	strCurName = string_To_UTF8(iterTunnel->m_sPolicy); //隧道策略
					//	BCON_APPEND(&tunnelOne, "Policy", strCurName.c_str());
					//	strCurName = string_To_UTF8(iterTunnel->m_sFQTrafficPolicy); //流队列QoS流量策略
					//	BCON_APPEND(&tunnelOne, "FQTrafficPolicy", strCurName.c_str());
					//	strCurName = string_To_UTF8(iterTunnel->m_sSQTrafficPolicy);//用户队列QoS流量策略
					//	BCON_APPEND(&tunnelOne, "SQTrafficPolicy", strCurName.c_str());
					//	strCurName = string_To_UTF8(iterTunnel->m_sDiffServProfile);//DS模板
					//	BCON_APPEND(&tunnelOne, "DiffServProfile", strCurName.c_str());

					sprintf(buf, "%d", iTunnel++);
					bson_append_document(&tunnelList, buf, -1, &tunnelOne);
					bson_destroy(&tunnelOne);
				}
				bson_append_array(&onePeList, "tunnelList", -1, &tunnelList);
				bson_destroy(&tunnelList);
			}

			sprintf(buf, "%d", iPe++);
			bson_append_document(&peList, buf, -1, &onePeList);
			bson_destroy(&onePeList);		
		}

		bson_append_array(m_pKeyRef[nIndex], "peList", -1, &peList);		
		bson_destroy(&peList);	
	}

	bson_t childDataRef;
	bson_init(&childDataRef);
	BCON_APPEND(&childDataRef, "$ref", strTABLE_L3vpn_data.c_str(), "$id", BCON_INT32(xcEthSvc.m_iId));					
	bson_append_document (m_pKeyRef[nIndex], "dataRef", -1, &childDataRef);
	bson_destroy(&childDataRef);
	/////////// l3vpn ref; end

}

void OTNM2000GetNeconfigService::GetAllSrvL3vpnSetToMongoDB(double fBegin, double fAdd,const std::string &strLogDir)
{	
	try{
		string strDetail = "";
		double fProgess = 0;
		char bufProgess[200]="";

		HSESSION hSession = -1;
		ERROR_CODE_EX eCode = 0;
		Json::Value valcontext;
		vector<XC_IPRAN_L3VPN_SERVICE> vectEthService;
		FuncCallToDB pFun = DealThreadL3Function;

		///// 登录获取session;
		ERROR_CODE iRet = ConnectNetClient(2, strLogDir);
		if (iRet == -1){
			WriteLog("GetAllSrvL3vpnSetToMongoDB InitMSMPClient Failure");

			strCloseLog += "GetAllSrvL3vpnSetToMongoDB InitMSMPClient Failure\n";	
			goto endLast;
		}
		else if (iRet == -2){
			WriteLog("GetAllSrvL3vpnSetToMongoDB Opensession Failure");

			strCloseLog += "GetAllSrvL3vpnSetToMongoDB Opensession Failure\n";	
			goto endInitClient;
		} 
		///// 登录获取session; end;	

		eCode = SNC_GetAllL3VPNServices(m_hSess, vectEthService); // 获得所有的业务数据；
		if (ERR_OK == eCode){

			//#############		
			mapTotalCount[neL3vpn].nTotalLen = vectEthService.size();			
			//#############

			printf("L3EthService size:%d\n", vectEthService.size());
			char bufLog[512]="";			
			sprintf(bufLog, "L3EthService size:%d\n", vectEthService.size());
			WriteLog(bufLog);

			int nAllSrcNum = vectEthService.size();
			int ik=0,nTmpBegin = 0;	
			for(int ij=0; ij<nAllSrcNum;++ij){

				if (g_bStopMongoDBTheard){
					break;
				}
				if (ij!=0 && (ij%(nAllSrcNum/50+1)==0)){

					fProgess = ((double)ij/nAllSrcNum)*fAdd+fBegin;
					sprintf(bufProgess, "L3EthService Progess:%f", fProgess);
					strDetail = bufProgess;
					UpdateTaskID(fProgess, strDetail);
				}

				if (ik == (nDealArrayThreadNum-1)) {

					m_tmpThreadUseData[ik].eType = eL3vpn;
					m_tmpThreadUseData[ik].Data = &vectEthService[ij];
					ThreadReladySetToMongoDB(nDealArrayThreadNum, pFun);									
					ik=0;
					nTmpBegin+=nDealArrayThreadNum;
				}
				else if ((nTmpBegin+nDealArrayThreadNum ) >= nAllSrcNum && (nTmpBegin<nAllSrcNum)){

					int nCntLess = nAllSrcNum - nTmpBegin;
					for (ik=0; ik<nCntLess; ++ik){
						m_tmpThreadUseData[ik].eType = eL3vpn;
						m_tmpThreadUseData[ik].Data = &vectEthService[ij++];
					}
					ThreadReladySetToMongoDB(nCntLess,pFun);									
					break;
				}
				else{
					m_tmpThreadUseData[ik].eType = eL3vpn;
					m_tmpThreadUseData[ik].Data = &vectEthService[ij];
					++ik;
				}	
			}
		}
		else{
			strCloseLog += "SNC_Get3ETHService Get Null data!\n";	
		}

endCloseSession:
		MutiServPlatform::SNC_CloseSession(m_hSess);

endInitClient:
		MutiServPlatform::DeInitMSMPClient();

endLast:
		return ;
	}
	catch(...){
		WriteLog("GetAllSrvL3vpnSetToMongoDB catch error!");
	}
	return ;
}

void OTNM2000GetNeconfigService::GetOneRingSetToMongoDB(XC_RING &xcEthSvc, int nIndex)
{
	m_pKey[nIndex] = BCON_NEW("_id", BCON_INT32(xcEthSvc.m_iId));

	//if (xcEthSvc.m_iId == 536871060)
	//{
	//	int xx = 0;
	//}

	BCON_APPEND(m_pKey[nIndex], "tableType", TABLE_RING);
	BCON_APPEND(m_pKey[nIndex], "operateMode", BCON_INT32(xcEthSvc.m_eOperMode));
	BCON_APPEND(m_pKey[nIndex], "activeState", BCON_INT32(xcEthSvc.m_eState));
	BCON_APPEND(m_pKey[nIndex], "brokenRepairStatus", BCON_INT32(xcEthSvc.m_eRepairStatus));	
	string strCurName = string_To_UTF8(xcEthSvc.m_sName);
	BCON_APPEND(m_pKey[nIndex], "name", strCurName.c_str());
	BCON_APPEND(m_pKey[nIndex], "createTime", BCON_INT64(xcEthSvc.m_tmCreateTime));		
	strCurName = string_To_UTF8(xcEthSvc.m_sCreateUserName);
	BCON_APPEND(m_pKey[nIndex], "createUserName", strCurName.c_str());
	BCON_APPEND(m_pKey[nIndex], "modifyTime", BCON_INT64(xcEthSvc.m_tmModifyTime));	
	strCurName = string_To_UTF8(xcEthSvc.m_sModifyUserName);
	BCON_APPEND(m_pKey[nIndex], "modifyUserName", strCurName.c_str());
	BCON_APPEND(m_pKey[nIndex], "RingType", BCON_INT32(xcEthSvc.m_eType));//业务类型
	strCurName = string_To_UTF8(xcEthSvc.m_sUserLabel);
	BCON_APPEND(m_pKey[nIndex], "userLabel", strCurName.c_str());//用户标签								
	BCON_APPEND(m_pKey[nIndex], "bRingFinish", BCON_INT32(xcEthSvc.m_bRingFinish?1:0));//环是否完整			
	BCON_APPEND(m_pKey[nIndex], "holdOffTime", BCON_INT32((int)xcEthSvc.m_shHoldOffTime));//WTR	恢复时间(单位：分钟)
	BCON_APPEND(m_pKey[nIndex], "waitToRestoreTime", BCON_INT32((int)xcEthSvc.m_shWaitToRestoreTime));//延迟时间
	BCON_APPEND(m_pKey[nIndex], "protectMonitorType", BCON_INT32(xcEthSvc.m_eProtectMonitorType));//保护监测类型(OTN)
	BCON_APPEND(m_pKey[nIndex], "ringRate", BCON_INT32(xcEthSvc.m_eRingRate));//环速率；
	BCON_APPEND(m_pKey[nIndex], "switchStatus", BCON_INT32(xcEthSvc.m_eSwitchStatus));//倒换状态；
	BCON_APPEND(m_pKey[nIndex], "startNodeNo", BCON_INT32(xcEthSvc.m_iStartNodeNo));//总共节点数目
	BCON_APPEND(m_pKey[nIndex], "totalNodeNum", BCON_INT32(xcEthSvc.m_iTotalNodeNum));//起始节点号					
	strCurName = string_To_UTF8(xcEthSvc.m_sReserve);
	BCON_APPEND(m_pKey[nIndex], "reserve", strCurName.c_str()); //业务名称
	BCON_APPEND(m_pKey[nIndex], "ringId", BCON_INT32(xcEthSvc.m_iRingId));//逻辑环id
	BCON_APPEND(m_pKey[nIndex], "ringStmNum", BCON_INT32(xcEthSvc.m_iRingStmNum));//环参与保护的STM1数目，

	BCON_APPEND(m_pKey[nIndex], "attributeType", BCON_INT32(xcEthSvc.m_eAttributeType));//属性类型
	BCON_APPEND(m_pKey[nIndex], "returnType", BCON_INT32(xcEthSvc.m_eReturnType)); // 返回类型


	///////////////   ring ref:  => 取不到环的关联关系；
	//if (xcEthSvc.m_iId == 536871045)
	//{
	//	int xxxxx=0;
	//}
	//if (xcEthSvc.m_iId == 536871050)
	//{
	//	int xxxxx=0;
	//}
	//if (xcEthSvc.m_iId == 587219782)
	//{
	//	int xxxxx=0;
	//}
	//		xcEthSvc.m_iId = 587219782;
	m_pKeyRef[nIndex] = BCON_NEW("_id", BCON_INT32(xcEthSvc.m_iId));

	///// 设置pw，tunnel，l2vpn的关联关系；
	GetMongoBusinessLayerRelation(m_pKeyRef[nIndex], OT_RING, PTN_LAYER_RING, xcEthSvc.m_iId);
	///// 设置pw，tunnel，l2vpn的关联关系；

	// 环路由信息；
	char buf[30]="",bufPort[30]="";
	bson_t ringNodeList;
	bson_init(&ringNodeList);
	int iz=0;
	vector<XC_RING_NODE> &vectRingNode = xcEthSvc.m_vectRingNode;
	for (int iN=0; iN<vectRingNode.size(); ++iN){
		XC_RING_NODE &tmpNode = vectRingNode[iN];

		bson_t ringNode;
		bson_init(&ringNode);
		BCON_APPEND(&ringNode, "NodeId", BCON_INT32(tmpNode.m_iNodeId));
		BCON_APPEND(&ringNode, "AStartTsIndex", BCON_INT32(tmpNode.m_iAStartTsIndex));

		bson_t child1;
		bson_init(&child1);
		BCON_APPEND(&child1, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(tmpNode.m_iNodeId));		
		bson_append_document (&ringNode, "NeRef", -1, &child1);
		bson_destroy(&child1);

		bson_t child2;
		bson_init(&child2);
		BCON_APPEND(&child2, "$ref", strBoardNameRef.c_str(), "$id", BCON_INT32(tmpNode.m_stAPortKey.m_iBoardId));		
		bson_append_document (&ringNode, "aBoardRef", -1, &child2);
		bson_destroy(&child2);
		sprintf(bufPort, "%d_%d", tmpNode.m_stAPortKey.m_iBoardId,tmpNode.m_stAPortKey.m_iPortNo);

		std::string strPortName = GetOneSelfPortName(tmpNode.m_iNodeId, tmpNode.m_stAPortKey.m_iBoardId, tmpNode.m_stAPortKey.m_iPortLevel, tmpNode.m_stAPortKey.m_iPortNo);
		strCurName = string_To_UTF8(strPortName);
		BCON_APPEND(&ringNode, "aportName", strCurName.c_str());

		BCON_APPEND(&ringNode, "aPortLevel", BCON_INT32(tmpNode.m_stAPortKey.m_iPortLevel));
		BCON_APPEND(&ringNode, "aPortNo", BCON_INT32(tmpNode.m_stAPortKey.m_iPortNo));
		BCON_APPEND(&ringNode, "aBoardId", BCON_INT32(tmpNode.m_stAPortKey.m_iBoardId));

		/////////////////////////////
		bson_t child4;
		bson_init(&child4);
		BCON_APPEND(&child4, "$ref", strBoardNameRef.c_str(), "$id", BCON_INT32(tmpNode.m_stZPortKey.m_iBoardId));		
		bson_append_document (&ringNode, "zBoardRef", -1, &child4);
		bson_destroy(&child4);
		sprintf(bufPort, "%d_%d", tmpNode.m_stZPortKey.m_iBoardId,tmpNode.m_stZPortKey.m_iPortNo);

		strPortName = GetOneSelfPortName(tmpNode.m_iNodeId, tmpNode.m_stZPortKey.m_iBoardId, tmpNode.m_stZPortKey.m_iPortLevel, tmpNode.m_stZPortKey.m_iPortNo);
		strCurName = string_To_UTF8(strPortName);
		BCON_APPEND(&ringNode, "zportName", strCurName.c_str());

		BCON_APPEND(&ringNode, "zPortLevel", BCON_INT32(tmpNode.m_stZPortKey.m_iPortLevel));
		BCON_APPEND(&ringNode, "zPortNo", BCON_INT32(tmpNode.m_stZPortKey.m_iPortNo));
		BCON_APPEND(&ringNode, "zBoardId", BCON_INT32(tmpNode.m_stZPortKey.m_iBoardId));

		itoa(iz++,buf,10);
		bson_append_document (&ringNodeList, buf, -1, &ringNode);
		bson_destroy(&ringNode);
	}
	bson_append_array(m_pKeyRef[nIndex], "ringNodeList", -1, &ringNodeList);
	bson_destroy(&ringNodeList);

	// 环路由信息； end

	bson_t childDataRef;
	bson_init(&childDataRef);
	BCON_APPEND(&childDataRef, "$ref", strTABLE_Ring_data.c_str(), "$id", BCON_INT32(xcEthSvc.m_iId));					
	bson_append_document (m_pKeyRef[nIndex], "dataRef", -1, &childDataRef);
	bson_destroy(&childDataRef);
}


void OTNM2000GetNeconfigService::GetAllRingSetToMongoDB(double fBegin, double fAdd,const std::string &strLogDir)
{
	try{
		if (g_bStopMongoDBTheard){
			WriteLog("GetAllRingSetToMongoDB StopMongoDBTheard");
			return ;
		}
		string strDetail = "";
		double fProgess = 0;
		char bufProgess[200]="";

		HSESSION hSession = -1;
		ERROR_CODE_EX eCode = 0;
		Json::Value valcontext;
		vector<XC_RING> vectEthService;
		FuncCallToDB pFun = DealThreadRingFunction;

		///// 登录获取session;
		ERROR_CODE iRet = ConnectNetClient(2, strLogDir);
		if (iRet == -1){
			WriteLog("GetAllRingSetToMongoDB InitMSMPClient Failure");

			strCloseLog += "GetAllRingSetToMongoDB InitMSMPClient Failure\n";	
			goto endLast;
		}
		else if (iRet == -2){
			WriteLog("GetAllRingSetToMongoDB Opensession Failure");

			strCloseLog += "GetAllRingSetToMongoDB Opensession Failure\n";	
			goto endInitClient;
		} 
		///// 登录获取session; end;	

		eCode = SNC_GetAllRings(m_hSess, vectEthService); // 获得所有的业务数据；
		if (ERR_OK == eCode){

			//################	
			mapTotalCount[neRing].nTotalLen = vectEthService.size();					
			//################

			printf("Ring size:%d\n", vectEthService.size());
			char bufLog[512]="";			
			sprintf(bufLog, "Ring size:%d\n", vectEthService.size());
			WriteLog(bufLog);

			int nAllSrcNum = vectEthService.size();
			int ik=0,nTmpBegin = 0;		
			for(int ij=0; ij<nAllSrcNum;++ij){

				if (g_bStopMongoDBTheard){
					break;
				}
				if (ij!=0 && (ij%(nAllSrcNum/50+1)==0)){

					fProgess = ((double)ij/nAllSrcNum)*fAdd+fBegin;
					sprintf(bufProgess, "Ring Progess:%f", fProgess);
					strDetail = bufProgess;
					UpdateTaskID(fProgess, strDetail);
				}

				if (ik == (nDealArrayThreadNum-1)) {

					m_tmpThreadUseData[ik].eType = eRing;
					m_tmpThreadUseData[ik].Data = &vectEthService[ij];
					ThreadReladySetToMongoDB(nDealArrayThreadNum,pFun);									
					ik=0;
					nTmpBegin+=nDealArrayThreadNum;
				}
				else if ((nTmpBegin+nDealArrayThreadNum ) >= nAllSrcNum && (nTmpBegin<nAllSrcNum)){

					int nCntLess = nAllSrcNum - nTmpBegin;
					for (ik=0; ik<nCntLess; ++ik){
						m_tmpThreadUseData[ik].eType = eRing;
						m_tmpThreadUseData[ik].Data = &vectEthService[ij++];
					}
					ThreadReladySetToMongoDB(nCntLess,pFun);									
					break;
				}
				else{
					m_tmpThreadUseData[ik].eType = eRing;
					m_tmpThreadUseData[ik].Data = &vectEthService[ij];
					++ik;
				}	
			}
		}
		else{
			strCloseLog += "SNC_GetRing Get Null data!\n";	
		}


endCloseSession:
		MutiServPlatform::SNC_CloseSession(m_hSess);

endInitClient:
		MutiServPlatform::DeInitMSMPClient();

endLast:
		return ;
	}
	catch(...){
		WriteLog("GetAllRingSetToMongoDB catch error!");
	}
	return ;
}

void OTNM2000GetNeconfigService::GetMongoBusinessLayerRelation(bson_t *pKeyRef, EObjectType m_eType, EServiceLayer m_eLayer, int m_iObjId)
{
	vector<int> vctRelationPwID, vctRelationTunnelID, vctL2vpnRelationID, vctL3vpnRelationID, vctProtect, vctRoms, vctRots; // ptn
	vector<int> vctRoduk,vctRclient,vctRoch;
	vector<XC_OBJ_KEY> objKey;
	XC_OBJ_KEY tmp;
	tmp.m_eType = m_eType;					
	tmp.m_iObjId = m_iObjId;
	/*if (OT_RING == m_eType){
	tmp.m_iSubObjId=-1;
	}*/
	objKey.push_back(tmp);
	if (!GetBusinessLayerRelation(m_iObjId, vctRelationPwID,vctRelationTunnelID,vctL2vpnRelationID,vctL3vpnRelationID,vctProtect,vctRoduk,vctRclient,vctRoch,vctRoms,vctRots,m_eLayer,objKey)){
		// 调用一段时间后，会连接失败,导致部分的关联关系失败。 ==> 重新登录session；
		ERROR_CODE iRet = ConnectNetClient(1);
		if (iRet == 0){
			if(!GetBusinessLayerRelation(m_iObjId, vctRelationPwID,vctRelationTunnelID,vctL2vpnRelationID,vctL3vpnRelationID,vctProtect,vctRoduk,vctRclient,vctRoch,vctRoms,vctRots,m_eLayer,objKey)){		
				char bufLog[512]="";			
				sprintf(bufLog, "GetBusinessLayerRelation Failure:%d\n", m_iObjId);
				WriteLog(bufLog);
			}
		}	
		else{		
			char bufLog[512]="";			
			sprintf(bufLog, "GetBusinessLayerRelation ReConnectNetClient Failure:%d\n", m_iObjId);
			WriteLog(bufLog);
		}
	}

	char buf[10]="";
	int index=0,i;
	if((int)vctL2vpnRelationID.size() >= 1){
		bson_t child;
		bson_init(&child);
		for (i=0;i<(int)vctL2vpnRelationID.size();++i){//关联l2vpn关系
			bson_t child1;
			bson_init(&child1);

			BCON_APPEND(&child1, "$ref", strTABLE_L2vpn_data.c_str(), "$id", BCON_INT32(vctL2vpnRelationID[i]));

			itoa(index++,buf, 10);
			bson_append_document (&child, buf, -1, &child1);
			bson_destroy(&child1);
		}	
		bson_append_array(pKeyRef, "dependenciesL2vpnRef", -1, &child);
		bson_destroy(&child);
	}

	if((int)vctL3vpnRelationID.size() >= 1){
		index=0;
		bson_t child;
		bson_init(&child);
		for (i=0;i<(int)vctL3vpnRelationID.size();++i){//关联l2vpn关系
			bson_t child1;
			bson_init(&child1);

			BCON_APPEND(&child1, "$ref", strTABLE_L3vpn_data.c_str(), "$id", BCON_INT32(vctL3vpnRelationID[i]));

			itoa(index++,buf, 10);
			bson_append_document (&child, buf, -1, &child1);
			bson_destroy(&child1);
		}	
		bson_append_array(pKeyRef, "dependenciesL3vpnRef", -1, &child);
		bson_destroy(&child);
	}

	if((int)vctRelationPwID.size() >= 1){
		index=0;
		bson_t child;
		bson_init(&child);
		for (i=0;i<(int)vctRelationPwID.size();++i){//关联关系 => pw,tunnel等
			if (g_bStopMongoDBTheard){
				break;
			}
			bson_t child1;
			bson_init(&child1);
			BCON_APPEND(&child1, "$ref", strTABLE_Pw_data.c_str(), "$id", BCON_INT32(vctRelationPwID[i]));

			itoa(index++,buf, 10);
			bson_append_document (&child, buf, -1, &child1);
			bson_destroy(&child1);
		}
		bson_append_array(pKeyRef, "dependenciesPwRef", -1, &child);
		bson_destroy(&child);
	}

	if((int)vctRelationTunnelID.size() >= 1){
		index=0;
		bson_t child;
		bson_init(&child);
		for (i=0;i<(int)vctRelationTunnelID.size();++i){//关联关系 => pw,tunnel等
			if (g_bStopMongoDBTheard){
				break;
			}
			bson_t child1;
			bson_init(&child1);
			BCON_APPEND(&child1, "$ref", strTABLE_Tunnel_data.c_str(), "$id", BCON_INT32(vctRelationTunnelID[i]));

			itoa(index++,buf, 10);
			bson_append_document (&child, buf, -1, &child1);

			bson_destroy(&child1);
		}

		bson_append_array(pKeyRef, "dependenciesTunnelRef", -1, &child);
		bson_destroy(&child);
	}

	if((int)vctProtect.size() >= 1){
		index=0;
		bson_t childProtect; // pw,tunnel关联保护关系；
		bson_init(&childProtect);
		for(i=0;i<(int)vctProtect.size();++i){
			bson_t child1;
			bson_init(&child1);
			BCON_APPEND(&child1, "$ref", strTABLE_ProtectPair_data.c_str(), "$id", BCON_INT32(vctProtect[i]));

			itoa(index++,buf, 10);
			bson_append_document (&childProtect, buf, -1, &child1);
			bson_destroy(&child1);
		}

		bson_append_array(pKeyRef, "dependenciesProtectRef", -1, &childProtect);
		bson_destroy(&childProtect);
	}

	if((int)vctRoduk.size() >= 1){
		index=0;
		bson_t childProtect; // pw,tunnel关联保护关系；
		bson_init(&childProtect);
		for(i=0;i<(int)vctRoduk.size();++i){
			bson_t child1;
			bson_init(&child1);
			BCON_APPEND(&child1, "$ref", strTABLE_oduk_data.c_str(), "$id", BCON_INT32(vctRoduk[i]));

			itoa(index++,buf, 10);
			bson_append_document (&childProtect, buf, -1, &child1);
			bson_destroy(&child1);
		}

		bson_append_array(pKeyRef, "dependenciesOdukRef", -1, &childProtect);
		bson_destroy(&childProtect);
	}
	if((int)vctRclient.size() >= 1){
		index=0;
		bson_t childProtect; // pw,tunnel关联保护关系；
		bson_init(&childProtect);
		for(i=0;i<(int)vctRclient.size();++i){
			bson_t child1;
			bson_init(&child1);
			BCON_APPEND(&child1, "$ref", strTABLE_client_data.c_str(), "$id", BCON_INT32(vctRclient[i]));

			itoa(index++,buf, 10);
			bson_append_document (&childProtect, buf, -1, &child1);
			bson_destroy(&child1);
		}

		bson_append_array(pKeyRef, "dependenciesOClientRef", -1, &childProtect);
		bson_destroy(&childProtect);
	}
	if((int)vctRoch.size() >= 1){
		index=0;
		bson_t childProtect; // pw,tunnel关联保护关系；
		bson_init(&childProtect);
		for(i=0;i<(int)vctRoch.size();++i){
			bson_t child1;
			bson_init(&child1);
			BCON_APPEND(&child1, "$ref", strTABLE_Och_data.c_str(), "$id", BCON_INT32(vctRoch[i]));

			itoa(index++,buf, 10);
			bson_append_document (&childProtect, buf, -1, &child1);
			bson_destroy(&child1);
		}

		bson_append_array(pKeyRef, "dependenciesOchRef", -1, &childProtect);
		bson_destroy(&childProtect);
	}

	if((int)vctRoms.size() >= 1){
		index=0;
		bson_t childProtect; // pw,tunnel关联保护关系；
		bson_init(&childProtect);
		for(i=0;i<(int)vctRoms.size();++i){
			bson_t child1;
			bson_init(&child1);
			BCON_APPEND(&child1, "$ref", strTABLE_Oms_data.c_str(), "$id", BCON_INT32(vctRoms[i]));

			itoa(index++,buf, 10);
			bson_append_document (&childProtect, buf, -1, &child1);
			bson_destroy(&child1);
		}

		bson_append_array(pKeyRef, "dependenciesOmsRef", -1, &childProtect);
		bson_destroy(&childProtect);
	}
	if((int)vctRots.size() >= 1){
		index=0;
		bson_t childProtect; // pw,tunnel关联保护关系；
		bson_init(&childProtect);
		for(i=0;i<(int)vctRots.size();++i){
			bson_t child1;
			bson_init(&child1);
			BCON_APPEND(&child1, "$ref", strTABLE_Ots_data.c_str(), "$id", BCON_INT32(vctRots[i]));

			itoa(index++,buf, 10);
			bson_append_document (&childProtect, buf, -1, &child1);
			bson_destroy(&child1);
		}

		bson_append_array(pKeyRef, "dependenciesOtsRef", -1, &childProtect);
		bson_destroy(&childProtect);
	}
}

std::string OTNM2000GetNeconfigService::GetOneSelfPortName(int iNeId, int iBoardId, int iPortLevel, int iPortNo)
{
	char bufID[50]="";
	sprintf(bufID, "ne_%d_bd%d_pl%d_pno_%d", iNeId,iBoardId,iPortLevel,iPortNo);
	if (mapPortName.find(bufID) != mapPortName.end()){
		return mapPortName[bufID];
	}

	std::string strPortName = "";
	std::vector<XC_NEID_PORTKEY> vectXCNeIdPortKey;
	XC_NEID_PORTKEY stNePort;
	stNePort.m_iNeId = iNeId;
	stNePort.m_stPortKey.m_iBoardId = iBoardId;
	stNePort.m_stPortKey.m_iPortLevel = iPortLevel;
	stNePort.m_stPortKey.m_iPortNo = iPortNo;
	vectXCNeIdPortKey.push_back(stNePort);
	std::vector<XC_PORT> vectXCPort;
	ERROR_CODE eCode = SNC_GetXCPortByKey(m_hSess, vectXCNeIdPortKey, vectXCPort);//=> m_hSess=-1,无法获取名称；
	if (ERR_OK == eCode){// 调用一段时间后，会连接失败,导致部分的端口名称失败。
		if(vectXCPort.size() >= 1){
			XC_PORT &tmpPort = vectXCPort[0];
			strPortName = vectXCPort.at(0).m_sPortName;
		}/*else{// boardid 0, 查不到			
		 char buflog[512] = "";
		 sprintf(buflog,"GetXCPortByKey portName Failure:nodeid=%d;boardid:%d;portNo:%d\n", iter->m_iNeId, iterUni->m_stPort.m_iBoardId,iterUni->m_stPort.m_iPortNo);
		 WriteLog(buflog);
		 }*/
	}else{
		if(ConnectNetClient()==0){
			eCode = SNC_GetXCPortByKey(m_hSess, vectXCNeIdPortKey, vectXCPort);//=> m_hSess=-1,无法获取名称；
			if (ERR_OK == eCode){// 调用一段时间后，会连接失败,导致部分的端口名称失败。
				if(vectXCPort.size() >= 1){
					XC_PORT &tmpPort = vectXCPort[0];
					strPortName = vectXCPort.at(0).m_sPortName;		
				}
				/*else{			
				char buflog[512] = "";
				sprintf(buflog,"GetXCPortByKey portName Failure:nodeid=%d;boardid:%d;portNo:%d\n", iter->m_iNeId, iterUni->m_stPort.m_iBoardId,iterUni->m_stPort.m_iPortNo);
				WriteLog(buflog);
				}*/
			}
			else{
				char buflog[512] = "";
				sprintf(buflog,"Insert pathinfo portName Failure:nodeid=%d;boardid:%d;portNo:%d; ReConnectNetClient GetXCPortByKey fail!\n", iNeId, iBoardId,iPortNo);
				WriteLog(buflog);
			}
		}else{
			char buflog[512] = "";
			sprintf(buflog, "Insert pathinfo portName Failure:nodeid=%d;boardid:%d;portNo:%d; ReConnectNetClient fail!\n", iNeId, iBoardId,iPortNo);
			WriteLog(buflog);
		}
	}

	mapPortName[bufID] = strPortName;
	return strPortName;
}


void OTNM2000GetNeconfigService::GetOneSrvL2vpnSetToMongoDB(XC_ETH_SERVICE &xcEthSvc, int nIndex)
{
	if((nIndex%50) == 0){// 防止太卡，进度不能及时写入；
		char bufIndex[256] = "";
		sprintf(bufIndex, "SrvL2vpn:%.3f, SrvL2vpn index:%d; rand:%d\n", m_fCircuitProgess, xcEthSvc.m_iId, rand());
		UpdateTaskID(m_fCircuitProgess, bufIndex);
	}

	char buf[100]="",bufPort[100]="";
	m_pKey[nIndex] = BCON_NEW("_id", BCON_INT32(xcEthSvc.m_iId));

	BCON_APPEND(m_pKey[nIndex], "tableType", TABLE_L2VPN);
	BCON_APPEND(m_pKey[nIndex], "operateMode", BCON_INT32(xcEthSvc.m_eOperMode));
	BCON_APPEND(m_pKey[nIndex], "activeState", BCON_INT32(xcEthSvc.m_eState));
	BCON_APPEND(m_pKey[nIndex], "brokenRepairStatus", BCON_INT32(xcEthSvc.m_eRepairStatus));	
	string strCurName = string_To_UTF8(xcEthSvc.m_sName);
	BCON_APPEND(m_pKey[nIndex], "name", strCurName.c_str());
	BCON_APPEND(m_pKey[nIndex], "createTime", BCON_INT64(xcEthSvc.m_tmCreateTime));		
	strCurName = string_To_UTF8(xcEthSvc.m_sCreateUserName);
	BCON_APPEND(m_pKey[nIndex], "createUserName", strCurName.c_str());
	BCON_APPEND(m_pKey[nIndex], "modifyTime", BCON_INT64(xcEthSvc.m_tmModifyTime));	
	strCurName = string_To_UTF8(xcEthSvc.m_sModifyUserName);
	BCON_APPEND(m_pKey[nIndex], "modifyUserName", strCurName.c_str());
	BCON_APPEND(m_pKey[nIndex], "eTHServiceType", BCON_INT32(xcEthSvc.m_eType));//业务类型
	BCON_APPEND(m_pKey[nIndex], "netType", BCON_INT32(xcEthSvc.m_eNetType));//网络类型
	BCON_APPEND(m_pKey[nIndex], "serviceDirection", BCON_INT32(xcEthSvc.m_eServiceDirection));//业务方向
	BCON_APPEND(m_pKey[nIndex], "attibuteObjectId", BCON_INT32(xcEthSvc.m_iAttibuteObjectId));//属性对象Id
	BCON_APPEND(m_pKey[nIndex], "protectType", BCON_INT32(xcEthSvc.m_eProtType));//保护类型
	strCurName = string_To_UTF8(xcEthSvc.m_sUserLabel);
	BCON_APPEND(m_pKey[nIndex], "userLabel", strCurName.c_str());//用户标签		
	strCurName = string_To_UTF8(xcEthSvc.m_sServiceName);
	BCON_APPEND(m_pKey[nIndex], "serviceName", strCurName.c_str()); //业务名称
	BCON_APPEND(m_pKey[nIndex], "attributeType", BCON_INT32(xcEthSvc.m_eAttributeType));//属性类型
	BCON_APPEND(m_pKey[nIndex], "returnType", BCON_INT32(xcEthSvc.m_eReturnType)); // 返回类型
	BCON_APPEND(m_pKey[nIndex], "WTRTime", BCON_INT32((int)xcEthSvc.m_shWTRTime)); // 延迟时间

	//if (xcEthSvc.m_iId == 587221455)
	//{// .
	//	int xxx = 0;
	//}

	//if (xcEthSvc.m_iId == 587221457)
	//{
	//	int xxx = 0;
	//}

	///////////////   l2vpn ref:
	//		xcEthSvc.m_iId = 587221459;	
	m_pKeyRef[nIndex] = BCON_NEW("_id", BCON_INT32(xcEthSvc.m_iId));

	///// 设置pw，tunnel，l2vpn的关联关系；
	GetMongoBusinessLayerRelation(m_pKeyRef[nIndex], OT_PTN_ETH_SERVICE, PTN_LAYER_CLIENT, xcEthSvc.m_iId);
	///// 设置pw，tunnel，l2vpn的关联关系；

	// list<int> m_lstTransLayerIds; //传输层电路id列表 => 全部是pw的id；
	int iz=0,iy,ix;
	if(xcEthSvc.m_lstTransLayerIds.size() > 0){
		bson_t childTunnellayer;		
		bson_init(&childTunnellayer);
		for (list<int>::iterator iter=xcEthSvc.m_lstTransLayerIds.begin(); iter!=xcEthSvc.m_lstTransLayerIds.end(); iter++,++iz){
			if (g_bStopMongoDBTheard){
				break;
			}
			bson_t child1;
			bson_init(&child1);
			BCON_APPEND(&child1, "$ref", strTABLE_Pw_data.c_str(), "$id", BCON_INT32(*iter));		
			itoa(iz,buf,10);
			bson_append_document (&childTunnellayer, buf, -1, &child1);
			bson_destroy(&child1);
		}
		bson_append_array(m_pKeyRef[nIndex], "transCircusList", -1, &childTunnellayer);
		bson_destroy(&childTunnellayer);
	}
	// list<int> m_lstTransLayerIds; //传输层电路id列表 end;

	////  ref  flow表；
	bson_t peList;
	bson_init(&peList);
	iz=0;
	char xcEthSvcFlowID[100]="";
	for(list<XC_ETH_NODE>::iterator iter=xcEthSvc.m_lstPE.begin(); iter!=xcEthSvc.m_lstPE.end(); iter++,iz++){
		if (g_bStopMongoDBTheard){
			break;
		}
		bson_t childDataNameRef,uniList,peListOne;
		bson_init(&peListOne);
		bson_init(&uniList);
		BCON_APPEND(&peListOne, "ServiceIndex", BCON_INT32((int)iter->m_iServiceIndex));
		BCON_APPEND(&peListOne, "VsiMTU", BCON_INT32((int)iter->m_shVsiMTU));
		BCON_APPEND(&peListOne, "MacLearning", BCON_INT32(iter->m_bVsiMacLearning?1:0));
		BCON_APPEND(&peListOne, "VPWS", BCON_INT32(iter->m_bVPWS?1:0));
		BCON_APPEND(&peListOne, "NodeType", BCON_INT32(iter->m_eNodeType));
		BCON_APPEND(&peListOne, "VsiId", BCON_INT32(iter->m_iVsiId));
		strCurName = string_To_UTF8(iter->m_sVsiDescription);
		BCON_APPEND(&peListOne, "VsiDescription", strCurName.c_str());
		strCurName = string_To_UTF8(iter->m_sName);
		BCON_APPEND(&peListOne, "Name", strCurName.c_str());

		bson_init(&childDataNameRef);
		BCON_APPEND(&childDataNameRef, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(iter->m_iNeId));					
		bson_append_document(&peListOne, "neNameRef", -1, &childDataNameRef);
		bson_destroy(&childDataNameRef);

		list<XC_ETH_UNI> &lstUNIs = iter->m_lstUNIs;
		iy=0;
		for (list<XC_ETH_UNI>::iterator iterUni=lstUNIs.begin(); iterUni!=lstUNIs.end(); iterUni++,iy++){
			if (g_bStopMongoDBTheard){
				break;
			}

			XC_ETH_UNI &oneUnist = *iterUni;
			bson_t uniOne,childDataNameRef1;
			bson_init(&uniOne);	
			bson_init(&childDataNameRef1);
			BCON_APPEND(&childDataNameRef1, "$ref", strBoardNameRef.c_str(), "$id", BCON_INT32(iterUni->m_stPort.m_iBoardId));					
			bson_append_document(&uniOne, "boardNameRef", -1, &childDataNameRef1);
			bson_destroy(&childDataNameRef1);

			if (iterUni->m_lstVirtualPorts.size() >= 1){
				list<string>::iterator iterStr=iterUni->m_lstVirtualPorts.begin();
				string  strVirtualPort = *iterStr;
				strCurName = string_To_UTF8(strVirtualPort);
			}
			else{
				std::string strPortName = GetOneSelfPortName(iter->m_iNeId, iterUni->m_stPort.m_iBoardId, iterUni->m_stPort.m_iPortLevel, iterUni->m_stPort.m_iPortNo);
				strCurName = string_To_UTF8(strPortName);
			}
			BCON_APPEND(&uniOne, "portName", strCurName.c_str());

			BCON_APPEND(&uniOne, "PortLevel", BCON_INT32(iterUni->m_stPort.m_iPortLevel));
			BCON_APPEND(&uniOne, "PortNo", BCON_INT32(iterUni->m_stPort.m_iPortNo));
			BCON_APPEND(&uniOne, "UpTagRecognise", BCON_INT32(iterUni->m_stUNIAttr.m_iUpTagRecognise)); //上话TAG识别
			BCON_APPEND(&uniOne, "DownTagBehavior", BCON_INT32(iterUni->m_stUNIAttr.m_iDownTagBehavior)); //下话TAG行为
			BCON_APPEND(&uniOne, "DownAddVlanId", BCON_INT32(iterUni->m_stUNIAttr.m_iDownAddVlanId)); //下话增加VLAN ID
			BCON_APPEND(&uniOne, "DownAddVlanPRI", BCON_INT32(iterUni->m_stUNIAttr.m_iDownAddVlanPRI)); //下话增加VLAN PRI
			BCON_APPEND(&uniOne, "VlanSwap", BCON_INT32(iterUni->m_stUNIAttr.m_iVlanSwap));

			bson_t childflow;
			bson_init(&childflow);
			list<XC_ETH_FLOW> &ethFlowList=iterUni->m_lstFlow;
			ix=0;		
			for (list<XC_ETH_FLOW>::iterator iterFlow=ethFlowList.begin(); iterFlow!=ethFlowList.end(); iterFlow++, ix++){
				sprintf(xcEthSvcFlowID, "EthSvcid_%d_Node_%d_UNIs_%d_Flows_%d",xcEthSvc.m_iId,iz,iy,ix);

				bson_t child1;
				bson_init(&child1);
				BCON_APPEND(&child1, "$ref", strTABLE_FLOW.c_str(), "$id", BCON_UTF8(xcEthSvcFlowID));				
				itoa(ix,buf,10);
				bson_append_document (&childflow, buf, -1, &child1);
				bson_destroy(&child1);

				XC_ETH_FLOW &oneFlowSt = *iterFlow;

				// add flow table;
				bson_t *pFlowID = BCON_NEW ("_id", BCON_UTF8(xcEthSvcFlowID));
				BCON_APPEND(pFlowID, "flowid", BCON_INT32(iterFlow->m_iId));
				BCON_APPEND(pFlowID, "portNo", BCON_INT32(iterUni->m_stPort.m_iPortNo));
				BCON_APPEND(pFlowID, "boardId", BCON_INT32(iterUni->m_stPort.m_iBoardId));
				BCON_APPEND(pFlowID, "portLevel", BCON_INT32(iterUni->m_stPort.m_iPortLevel));
				BCON_APPEND(pFlowID, "neId", BCON_INT32(iter->m_iNeId));

				bson_t childDataNameRefNe; // 合在一起，不停的初始化，可能会引起异常；
				bson_init(&childDataNameRefNe);
				BCON_APPEND(&childDataNameRefNe, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(iter->m_iNeId));					
				bson_append_document(pFlowID, "neNameRef", -1, &childDataNameRefNe);
				bson_destroy(&childDataNameRefNe);

				bson_t childDataNameRefBoard;
				bson_init(&childDataNameRefBoard);
				BCON_APPEND(&childDataNameRefBoard, "$ref", strBoardNameRef.c_str(), "$id", BCON_INT32(iterUni->m_stPort.m_iBoardId));					
				bson_append_document(pFlowID, "boardNameRef", -1, &childDataNameRefBoard);
				bson_destroy(&childDataNameRefBoard);

				int neType =  m_MongoDBOperator.GetNeIDType(iter->m_iNeId, strNeTableName.c_str());
				string strPortName = strCurName;
				//	GetPortFullName(strPortName, neType, xcEthSvc.m_eType, xcEthSvc.m_eAttributeType, 
				//		iterFlow->m_iVlanId, iterFlow->m_iId,iterFlow->m_iPWLabel);
				BCON_APPEND(pFlowID, "portName", strPortName.c_str());
				BCON_APPEND(pFlowID, "pwLabel", BCON_INT32(iterFlow->m_iPWLabel));
				BCON_APPEND(pFlowID, "vlanId", BCON_INT32(iterFlow->m_iVlanId));
				BCON_APPEND(pFlowID, "srcMacAddress", BCON_UTF8(iterFlow->m_sSrcMacAddress.c_str()));
				BCON_APPEND(pFlowID, "dstMacAddress", BCON_UTF8(iterFlow->m_sDstMacAddress.c_str()));
				BCON_APPEND(pFlowID, "802_1P", BCON_INT32(iterFlow->m_i802_1P));
				BCON_APPEND(pFlowID, "srcIpAddress", BCON_UTF8(iterFlow->m_sSrcIpAddress.c_str()));
				BCON_APPEND(pFlowID, "dstIpAddress", BCON_UTF8(iterFlow->m_sDstIpAddress.c_str()));
				BCON_APPEND(pFlowID, "IP_DSCP", BCON_INT32(iterFlow->m_iIP_DSCP));
				BCON_APPEND(pFlowID, "enable", BCON_INT32(iterFlow->m_bEnable==true?1:0));
				BCON_APPEND(pFlowID, "color", BCON_INT32(iterFlow->m_iColor));//着色
				BCON_APPEND(pFlowID, "ovlan", BCON_INT32(iterFlow->m_iOvlan));//外层vlan
				BCON_APPEND(pFlowID, "ivlan", BCON_INT32(iterFlow->m_iIvlan)); //内层vlan
				BCON_APPEND(pFlowID, "srcPort", BCON_INT32(iterFlow->m_iSrcPort));
				BCON_APPEND(pFlowID, "dstPort", BCON_INT32(iterFlow->m_iDstPort));
				BCON_APPEND(pFlowID, "ovlan_End", BCON_INT32(iterFlow->m_iOvlan_End));//VLAN RANGE OVLAN_END

				XC_ETH_UNI_POLICER_PROFILE& stQos = iterFlow->m_stQos;
				BCON_APPEND(pFlowID, "Mode", BCON_INT32(stQos.m_iMode));
				BCON_APPEND(pFlowID, "CIR", BCON_INT32(stQos.m_iCIR));
				BCON_APPEND(pFlowID, "PIR", BCON_INT32(stQos.m_iPIR));
				BCON_APPEND(pFlowID, "CM", BCON_INT32(stQos.m_iCM));
				BCON_APPEND(pFlowID, "CBS", BCON_INT32(stQos.m_iCBS));
				BCON_APPEND(pFlowID, "PBS", BCON_INT32(stQos.m_iPBS));
				BCON_APPEND(pFlowID, "m_bFlowMonitorEnable", BCON_INT32(stQos.m_bFlowMonitorEnable?1:0));//流量监管使能

#if DEFINE_MONGO_INSERT
				if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_FLOW.c_str(), pFlowID)){
					// log新增数据失败；
					bIfTableUpdateRight = false;
					g_bStopMongoDBTheard = true;  // 如果有数据缺少，则中断此次任务 ；

					char bufLog[512]="";			
					sprintf(bufLog, "Insert L2VPN flow Failure:%s\n", xcEthSvcFlowID);
					WriteLog(bufLog);
				}
#endif
				bson_destroy(pFlowID);

				// add flow table; end
			}

			bson_append_array(&uniOne, "flowList", -1, &childflow);
			bson_destroy(&childflow);

			sprintf(buf, "%d", iy);
			bson_append_document(&uniList, buf, -1, &uniOne);
			bson_destroy(&uniOne);
		}	
		bson_append_array(&peListOne, "uniList", -1, &uniList);
		bson_destroy(&uniList);

		sprintf(buf, "%d", iz);
		bson_append_document(&peList, buf, -1, &peListOne);
		bson_destroy(&peListOne);
	}
	////  ref  flow表；end
	bson_append_array(m_pKeyRef[nIndex], "peList", -1, &peList);
	bson_destroy(&peList);

	bson_t childDataRef;
	bson_init(&childDataRef);
	BCON_APPEND(&childDataRef, "$ref", strTABLE_L2vpn_data.c_str(), "$id", BCON_INT32(xcEthSvc.m_iId));					
	bson_append_document (m_pKeyRef[nIndex], "dataRef", -1, &childDataRef);
	bson_destroy(&childDataRef);
}

void OTNM2000GetNeconfigService::GetAllSrvL2vpnSetToMongoDB(double fBegin, double fAdd,const std::string &strLogDir)
{
	try{
		if (g_bStopMongoDBTheard){
			WriteLog("GetAllSrvL2vpnSetToMongoDB StopMongoDBTheard");
			return ;
		}

		string strDetail = "";
		char bufProgess[200]="";
		int i = 0, iStart,iEnd, nAllSrcNum,ik,nTmpBegin,j,nCntLess;
		int nMaxCircuitPice = g_nOneTimeMaxDataCnt; //长度太多，可能会超时；
		vector<int> vectCircuitId;
		vector<XC_ETH_SERVICE> vectSnapshot;
		ERROR_CODE_EX eCode = 0;
		FuncCallToDB pFun = DealThreadL2Function;

		///// 登录获取session;
		ERROR_CODE iRet = ConnectNetClient(1, strLogDir);// 登陆的账号，密码可能是无效的。
		if (iRet == -1){
			char bufLog[512]="";
			sprintf(bufLog, "GetAllSrvL2vpnSetToMongoDB InitMSMPClient Failure\n");
			WriteLog(bufLog);

			strCloseLog += "GetAllSrvL2vpnSetToMongoDB InitMSMPClient Failure\n";	
			goto endLast;
		}
		else if (iRet == -2){
			char bufLog[512]="";
			sprintf(bufLog, "GetAllSrvL2vpnSetToMongoDB Opensession Failure\n");
			WriteLog(bufLog);

			strCloseLog += "GetAllSrvL2vpnSetToMongoDB Opensession Failure\n";	
			goto endInitClient;
		} 

		iRet = SNC_GetETHServiceSnapshot(m_hSess, vectCircuitId, vectSnapshot);
		if (ERR_OK != iRet){
			WriteLog("SNC_GetETHServiceSnapshot fail!");
			strCloseLog += "SNC_GetETHServiceSnapshot Get Null data!\n";		

			goto endCloseSession;
		}

		//##########
		mapTotalCount[neL2vpn].nTotalLen = vectCircuitId.size();
		//#############

		printf("l2vpn size:%d\n", vectCircuitId.size());
		char bufLog[512]="";			
		sprintf(bufLog, "l2vpn size:%d\n", vectCircuitId.size());
		WriteLog(bufLog);

		//批量取一次
		if (vectCircuitId.size() > nMaxCircuitPice){

			int iStep = (vectCircuitId.size() / nMaxCircuitPice) + 1;
			for (i = 0; i < iStep; ++i){

				if (g_bStopMongoDBTheard){				
					break;
				}

				/*if (i!=0 && ((i%(iStep/50+1))==0))*/{ // 每一个step写一次进度；

					m_fCircuitProgess = (double)i/iStep*fAdd+fBegin;
					sprintf(bufProgess, "l2vpn Progess:%f", m_fCircuitProgess);
					strDetail = bufProgess;
					UpdateTaskID(m_fCircuitProgess, strDetail);
				}

				vector<XC_ETH_SERVICE> vecCircuits;
				vector<int> vectIds;
				iStart = i * nMaxCircuitPice;
				iEnd = (i + 1) * nMaxCircuitPice;
				if (i == iStep - 1){
					iEnd = vectCircuitId.size();
				}
				vectIds.insert(vectIds.end(), vectCircuitId.begin() + iStart, vectCircuitId.begin() + iEnd);

				//	int nS = clock();
				iRet = SNC_GetMutiETHServices(m_hSess, vectIds, vecCircuits); // 远程获取到的数据 => 版本不匹配时，可以获取总条数，但是获取不到数据；
				if (vectIds.size() != vecCircuits.size()){
					//	bIfTableUpdateRight = false;// 版本不匹配或？原因时，取出的数据会缺少，总条数有个容错度,这时任务结束后进度设置为-1。 
					//	g_bStopMongoDBTheard = true;  // 如果有数据缺少，则中断此次任务 ；

					WriteLog("SNC_GetMutiETHServices get data: lost data!");
				}

				//##########
				map<TypeAll,  stDetailCount> &mapCurrentDetailCount = mapTotalCount[neL2vpn].mapDetailCount;									
				//##########

				if (ERR_OK != iRet){// 一次50s左右,本机30s					

					WriteLog("SNC_GetMutiETHServices fail!");	
					iRet = ConnectNetClient(1, strLogDir);
					if ((iRet == -1) || (iRet == -2)){
						WriteLog("SNC_GetMutiETHServices reconnect fail!");	
						continue;
					}
					iRet = SNC_GetMutiETHServices(m_hSess, vectIds, vecCircuits); // 远程获取到的数据
					if (ERR_OK != iRet){
						WriteLog("SNC_GetMutiETHServices reGet fail!");	
						continue;
					}
				}
				//	int nE=clock();
				//	printf("GetAllCircuitsSetToMongoDB:%.3f; Step:%d/%d\n", (double)(nE-nS)/1000, i, iStep);

				nAllSrcNum = vecCircuits.size();				
				ik=0;	
				for (j=0; j<nAllSrcNum; ++j){
					if (g_bStopMongoDBTheard){

						goto endCloseSession;
					}

					if (ik == (nDealArrayThreadNum-1)) {
						m_tmpThreadUseData[ik].eType = eL2vpn;
						m_tmpThreadUseData[ik].Data = &vecCircuits[j];
						ThreadReladySetToMongoDB(nDealArrayThreadNum, pFun);									
						ik=0;			
					}				
					else{					
						m_tmpThreadUseData[ik].eType = eL2vpn;
						m_tmpThreadUseData[ik].Data = &vecCircuits[j];
						++ik;
					}	
				}

				ThreadReladySetToMongoDB(ik, pFun);									
			}
		}
		else{						
			//	int nS=clock();
			vector<XC_ETH_SERVICE> vecOldCirt;
			eCode = SNC_GetAllETHServices(m_hSess, vecOldCirt);
			if (ERR_OK != eCode){
				WriteLog("SNC_GetAllETHServices fail!");				
				goto endCloseSession;
			}
			//	int nE=clock();
			//	printf("GetAllCircuitsSetToMongoDB:%.3f;\n", (double)(nE-nS)/1000);

			int nAllCiruit = vecOldCirt.size();
			ik=0;	
			for (j = 0; j < nAllCiruit; ++j){
				if (g_bStopMongoDBTheard){

					goto endCloseSession;
				}

				if (j!=0 && (j%(nAllCiruit/50+1)==0)){

					m_fCircuitProgess = (double)j/nAllCiruit*fAdd+fBegin;
					sprintf(bufProgess, "l2vpn Progess:%f", m_fCircuitProgess);
					strDetail = bufProgess;
					UpdateTaskID(m_fCircuitProgess, strDetail);
				}

				if (ik == (nDealArrayThreadNum-1)) {
					m_tmpThreadUseData[ik].eType = eL2vpn;
					m_tmpThreadUseData[ik].Data = &vecOldCirt[j];
					ThreadReladySetToMongoDB(nDealArrayThreadNum, pFun);									
					ik=0;
				}			
				else{				
					m_tmpThreadUseData[ik].eType = eL2vpn;
					m_tmpThreadUseData[ik].Data = &vecOldCirt[j];
					++ik;
				}	
			}
			ThreadReladySetToMongoDB(ik, pFun);
		}

endCloseSession:
		MutiServPlatform::SNC_CloseSession(m_hSess);

endInitClient:
		MutiServPlatform::DeInitMSMPClient();

endLast:		
		return;
	}
	catch(...){

		WriteLog("GetAllSrvL2vpnSetToMongoDB catch error!");
	}
	return ;
}

void OTNM2000GetNeconfigService::MakeNEStatusTableName()
{
	time_t rawtime;    
	struct tm *ptminfo;     
	time(&rawtime);    
	ptminfo = localtime(&rawtime); 
	char bufTime[100]="";
	sprintf(bufTime,"_%02d-%02d-%02d_%02d-%02d-%02d",            
		ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday,
		ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);

	strTABLE_NeStatus=TABLE_NeStatus_Name;
	strTABLE_NeStatus+=bufTime;

}


void OTNM2000GetNeconfigService::MakeConfigTableName()
{
	time_t rawtime;    
	struct tm *ptminfo;     
	time(&rawtime);    
	ptminfo = localtime(&rawtime); 
	char bufTime[100]="";
	sprintf(bufTime,"_%02d-%02d-%02d_%02d-%02d-%02d",            
		ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday,
		ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);

	strTABLE_clock=TABLE_CLOCK_Name;
	strTABLE_clock+=bufTime;
	strTABLE_lag=TABLE_LAG_Name; 
	strTABLE_lag+=bufTime;
	strTABLE_ether=TABLE_ETHER_Name;
	strTABLE_ether+=bufTime;
	strTABLE_ve=TABLE_VE_Name; 
	strTABLE_ve+=bufTime;
	strTableConfigNetWarning = TABLE_NeWarning_Name;
	strTableConfigNetWarning += bufTime;
}

void OTNM2000GetNeconfigService::MakeBoardStrTableName()
{
	time_t rawtime;    
	struct tm *ptminfo;     
	time(&rawtime);    
	ptminfo = localtime(&rawtime); 
	char bufTime[100]="";
	sprintf(bufTime,"_%02d-%02d-%02d_%02d-%02d-%02d",            
		ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday,
		ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);

	strTABLE_BoardStrPingBi=TABLE_BoardStrPingbi_Name;
	strTABLE_BoardStrPingBi+=bufTime;

	nTotalNumCnt = 0;
	nCurNumCnt = 0;
	m_mapBoardTypeLineNo.clear();
}

void OTNM2000GetNeconfigService::MakeTableName()
{
	bIsOtnCircus = false;
	bIfTableUpdateRight=true;

	time_t rawtime;    
	struct tm *ptminfo;     
	time(&rawtime);    
	ptminfo = localtime(&rawtime); 
	char bufTime[100]="";
	sprintf(bufTime,"_%02d-%02d-%02d_%02d-%02d-%02d",            
		ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday,
		ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);

	//strTABLE_BizDataInfos=TABLE_BizData_Name;
	//strTABLE_BizDataInfos+=bufTime;

	strTABLE_PATH=TABLE_PATH_Name; 
	strTABLE_PATH+=bufTime;
	strTABLE_PATHINFO=TABLE_PATHINFO_Name; 
	strTABLE_PATHINFO+=bufTime;
	strTABLE_FLOW=TABLE_FLOW_Name;
	strTABLE_FLOW+=bufTime;

	strTABLE_L2vpn=TABLE_L2VPN_Name;
	strTABLE_L2vpn+="_ref";
	strTABLE_L2vpn+=bufTime;
	strTABLE_L2vpn_data = strTABLE_L2vpn + "_data";

	strTABLE_L3vpn=TABLE_L3VPN_Name;
	strTABLE_L3vpn+="_ref";
	strTABLE_L3vpn+=bufTime;
	strTABLE_L3vpn_data = strTABLE_L3vpn + "_data";

	strTABLE_ProtectPair=TABLE_PROTECT_Name;
	strTABLE_ProtectPair+="_ref";
	strTABLE_ProtectPair+=bufTime;
	strTABLE_ProtectPair_data = strTABLE_ProtectPair + "_data";

	strTABLE_Pw=TABLE_PW_Name;
	strTABLE_Pw+="_ref";
	strTABLE_Pw+=bufTime;
	strTABLE_Pw_data = strTABLE_Pw + "_data";

	strTABLE_Tunnel=TABLE_TUNNEL_Name;
	strTABLE_Tunnel+="_ref";
	strTABLE_Tunnel+=bufTime;	
	strTABLE_Tunnel_data = strTABLE_Tunnel + "_data";

	strTABLE_Och=TABLE_OCH_Name;
	strTABLE_Och+="_ref";
	strTABLE_Och+=bufTime;	
	strTABLE_Och_data = strTABLE_Och + "_data";

	strTABLE_Ots=TABLE_OTS_Name;
	strTABLE_Ots+="_ref";
	strTABLE_Ots+=bufTime;	
	strTABLE_Ots_data = strTABLE_Ots + "_data";
	strTABLE_Oms=TABLE_OMS_Name;
	strTABLE_Oms+="_ref";
	strTABLE_Oms+=bufTime;	
	strTABLE_Oms_data = strTABLE_Oms + "_data";


	strTABLE_oduk=TABLE_ODUK_Name;
	strTABLE_oduk+="_ref";
	strTABLE_oduk+=bufTime;	
	strTABLE_oduk_data = strTABLE_oduk + "_data";

	strTABLE_client=TABLE_CLIENT_Name;
	strTABLE_client+="_ref";
	strTABLE_client+=bufTime;	
	strTABLE_client_data = strTABLE_client + "_data";

	strTABLE_Ring=TABLE_RING_Name;
	strTABLE_Ring+="_ref";
	strTABLE_Ring+=bufTime;	
	strTABLE_Ring_data = strTABLE_Ring + "_data";

	strNeNameRef=TABLE_NE_IDNAME;
	strNeNameRef+=bufTime;		
	strBoardNameRef=TABLE_BOARD_IDNAME;
	strBoardNameRef+=bufTime;			

	strTABLE_RingBandingTunnel=TABLE_RINGBAND_Name;
	strTABLE_RingBandingTunnel+=bufTime;

	strTABLESPCRes=TABLE_SPC_RESOURCE_Name;
	strTABLESPCRes+=bufTime;

	GetNeAndBoardNameID();
}

void OTNM2000GetNeconfigService::AddCircuitsPathInfoResource(bson_t *child1, XC_CROSS_ITEM &tmpRoute, XC_RESOURCE	&tmpReSrc, int nSrcOrDst, string &strWaveNameParm, int &nFirstLabel, bool bIfFirst)
{
	if (g_bStopMongoDBTheard){
		return;
	}
	BCON_APPEND(child1, "neId", BCON_INT32(tmpRoute.m_iNodeId));
	BCON_APPEND(child1, "bizType", BCON_INT32(tmpReSrc.m_iServiceType));//业务类型 => enum EServiceType => MSMPStruct.h => java 给的string
	BCON_APPEND(child1, "portNo", BCON_INT32(tmpReSrc.m_iPortNo));
	BCON_APPEND(child1, "srcOrdst", BCON_UTF8((nSrcOrDst==0)?"src":"dst"));
	BCON_APPEND(child1, "label", BCON_INT32(tmpReSrc.m_iLabel));	
	string strWaveName="";
	GetWaveName(strWaveName, tmpReSrc.m_stWaveCodeKey);
	BCON_APPEND(child1, "otnWave", strWaveName.c_str()); // //PTN的 Tunnel标签; //SDH的VC4Index //OCH电路的波长	

	if (bIfFirst){
		if (nSrcOrDst == 0){
			nFirstLabel = tmpReSrc.m_iLabel; //第一label；
		}
		else{
			strWaveNameParm = strWaveName;  // 波长在dst中；
		}
	}

	BCON_APPEND(child1, "index", BCON_INT32(tmpReSrc.m_iTunnelId)); //PW,TUNNEL序号	

	bson_t childDataNameRef;
	bson_init(&childDataNameRef);
	BCON_APPEND(&childDataNameRef, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(tmpRoute.m_iNodeId));					
	bson_append_document(child1, "neNameRef", -1, &childDataNameRef);
	bson_destroy(&childDataNameRef);

	if(((tmpReSrc.m_iBoardId>>24)&0xf) == 0x6){// 单板类型；
		BCON_APPEND(child1, "boardId", BCON_INT32(tmpReSrc.m_iBoardId));

		bson_init(&childDataNameRef);
		BCON_APPEND(&childDataNameRef, "$ref", strBoardNameRef.c_str(), "$id", BCON_INT32(tmpReSrc.m_iBoardId));					
		bson_append_document(child1, "boardNameRef", -1, &childDataNameRef);
		bson_destroy(&childDataNameRef);
	}
	else{// 可能是网元类型;
		BCON_APPEND(child1, "boardId", BCON_INT32(-1));
	}

	// 从数据库获取端口名称
	std::string strPortName = GetOneSelfPortName(tmpRoute.m_iNodeId, tmpReSrc.m_iBoardId, tmpReSrc.m_iPortLevel, tmpReSrc.m_iPortNo);
	string strCurName = string_To_UTF8(strPortName);
	BCON_APPEND(child1, "portName", strCurName.c_str());
}

bool OTNM2000GetNeconfigService::InsertTaskID()
{
	bool bRet = true;
	bson_t *pKey = BCON_NEW("_id", BCON_UTF8(m_strTaskID.c_str()));
	BCON_APPEND(pKey, "state", BCON_INT32(0));

#if DEFINE_MONGO_INSERT
	if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), m_strTaskTable.c_str(), pKey)){
		// log新增数据失败；
		bRet = false;

		char bufLog[512]="";			
		sprintf(bufLog, "InsertTaskID Failure:%s\n", m_strTaskID.c_str());
		WriteLog(bufLog);
	}
#endif

	char bufLog[512]="";			
	sprintf(bufLog, "InsertTaskID:%s\n", m_strTaskID.c_str());
	WriteLog(bufLog);

	bson_destroy(pKey);
	return bRet;
}

bool OTNM2000GetNeconfigService::UpdateTaskID(double fProgress, const string &strDetail)
{
	bool bRet = true;
	try{
		bson_t *pKey = BCON_NEW("_id", BCON_UTF8(m_strTaskID.c_str()));
		bson_t *pKeyChange = BCON_NEW("_id", BCON_UTF8(m_strTaskID.c_str()));

		__time64_t long_time;
		_time64(&long_time); 
		BCON_APPEND(pKeyChange, "timeSpan", BCON_INT64(long_time));
		BCON_APPEND(pKeyChange, "progressDetail",strDetail.c_str());

		if (emClassType == EM_TYPE_CIRCUS)
		{
			if (!bIfTableUpdateRight){
				bRet = false;
				DropAllTable();
				BCON_APPEND(pKeyChange, "progress", BCON_DOUBLE(-1));
			}
			else{
				BCON_APPEND(pKeyChange, "progress", BCON_DOUBLE(fProgress));
				char bufResult[2048]="";	
				sprintf_s(bufResult, 2048, 
					"\"{\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\"}\"", 
					TABLE_L2VPN, strTABLE_L2vpn.c_str(), TABLE_FLOW, strTABLE_FLOW.c_str(),
					TABLE_L3VPN, strTABLE_L3vpn.c_str(),TABLE_PW, strTABLE_Pw.c_str(),TABLE_TUNNEL, strTABLE_Tunnel.c_str(),
					TABLE_OCH, strTABLE_Och.c_str(), TABLE_ODUK, strTABLE_oduk.c_str(),TABLE_CLIENT, strTABLE_client.c_str(),
					TABLE_PROTECT, strTABLE_ProtectPair.c_str(),TABLE_PATH, strTABLE_PATH.c_str(),
					TABLE_PATHINFO, strTABLE_PATHINFO.c_str(),TABLE_RING,strTABLE_Ring.c_str(), 
					TABLE_OMS,strTABLE_Oms.c_str(),TABLE_OTS,strTABLE_Ots.c_str(),
					TABLE_RINGBAND,strTABLE_RingBandingTunnel.c_str(), TABLE_SPC_RESOURCE, strTABLESPCRes.c_str());

				BCON_APPEND(pKeyChange, "result",bufResult);
			}			
		}
		else if (emClassType == EM_TYPE_CONFIG)
		{
			//	DropAllTable();
			BCON_APPEND(pKeyChange, "progress", BCON_DOUBLE(fProgress));
			char bufResult[1024]="";	
			sprintf_s(bufResult, 1024, 
				"\"{\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\"}\"", 
				TABLE_LAG, strTABLE_lag.c_str(), TABLE_ETHER, strTABLE_ether.c_str(),
				TABLE_CLOCK, strTABLE_clock.c_str(),TABLE_VE, strTABLE_ve.c_str(), TABLE_NeWarning,strTableConfigNetWarning.c_str());

			BCON_APPEND(pKeyChange, "result",bufResult);
		}
		else if (emClassType == EM_TYPE_NESTATUS)
		{
			//	DropAllTable();
			BCON_APPEND(pKeyChange, "progress", BCON_DOUBLE(fProgress));
			char bufResult[1024]="";	
			sprintf_s(bufResult, 1024, 
				"\"{\"%s\":\"%s\"}\"", 
				TABLE_NeStatus, strTABLE_NeStatus.c_str());

			BCON_APPEND(pKeyChange, "result", bufResult);
		}
		else if (emClassType == EM_TYPE_BOARDSTR_PINGBI)
		{
			BCON_APPEND(pKeyChange, "progress", BCON_DOUBLE(fProgress));
			char bufResult[1024]="";	
			sprintf_s(bufResult, 1024, 
				"\"{\"%s\":\"%s\"}\"", 
				TABLE_BoardStrPingbi, strTABLE_BoardStrPingBi.c_str());

			BCON_APPEND(pKeyChange, "result", bufResult);
		}

#if DEFINE_MONGO_INSERT
		if(!m_MongoDBOperator.Update(m_MongoDBOperator.m_strTableName.c_str(), m_strTaskTable.c_str(), pKey, pKeyChange)){
			// log新增数据失败；
			bRet = false;

			char bufLog[512]="";			
			sprintf(bufLog, "UpdateTaskID Failure:%s\n", m_strTaskID.c_str());
			WriteLog(bufLog);	
		}
#endif

		bson_destroy(pKey);
		bson_destroy(pKeyChange);
	}
	catch(...){
		printf("UpdateTaskID error!\n");
	}
	return bRet;
}

void OTNM2000GetNeconfigService::GetVctConifgFromXMLAndMongo(map<int, EM_TypeConifGet> &mapType)
{
	map<int,int> mapIDConfig;
	m_MongoDBOperator.QueryAndGetTableIDandName(mapIDConfig, m_MongoDBOperator.m_strTableName.c_str(), 
		strNeTableName.c_str(), "_id", strNeTableKey.c_str());

	for (map<int,int>::iterator iter = mapIDConfig.begin(); 
		iter != mapIDConfig.end(); iter++)
	{// <neID, neTypeID>
		if (g_bStopConfigMongoDBTheard){
			break;
		}
		if (mapType.find(iter->second) != mapType.end()){

			stConfigGet stTmp;
			stTmp.id = iter->first;
			stTmp.eFunType = mapType[iter->second];
			vctGetConifg.push_back(stTmp);
		}
	}

#if 0
	////  =>  单盘表里面，找出关联的网元id；  
	map<int,int> mapIDClock;
	m_MongoDBOperator.QueryAndGetTableIDandName(mapIDClock, m_MongoDBOperator.m_strTableName.c_str(), 
		strBoardName.c_str(), "_id", strBoardKey.c_str());

	for (map<int,int>::iterator iter = mapIDClock.begin(); 
		iter != mapIDClock.end(); iter++){

			if (g_bStopConfigMongoDBTheard){
				break;
			}

			if (mapIDConfig.find(iter->second) != mapIDConfig.end())
			{// <boardID, neId>; => <neID, neTypeID>
				int nNeTypeID = mapIDConfig[iter->second];
				if (mapType.find(nNeTypeID) != mapType.end()){

					bool bIfAddNew = true; // 去除重复id；
					for(int j=0; j<(int)vctGetConifg.size();j++){
						if (vctGetConifg[j].id == iter->second){
							bIfAddNew = false;
							break;
						}
					}
					if (bIfAddNew){  // 单盘是关联网元信息的，这种情况，正常时，不会出现； 造数据才会出现；
						stConfigGet stTmp;
						stTmp.id = iter->second;
						stTmp.eFunType = mapType[nNeTypeID];
						vctGetConifg.push_back(stTmp);
					}		
				}
			}	
	}
#endif
}

void OTNM2000GetNeconfigService::GetVctFromMongo()
{
	map<int,int> mapIDConfig;
	m_MongoDBOperator.QueryAndGetTableIDandName(mapIDConfig, m_MongoDBOperator.m_strTableName.c_str(), 
		strNeTableName.c_str(), "_id", strNeTableKey.c_str());

	for (map<int,int>::iterator iter = mapIDConfig.begin(); 
		iter != mapIDConfig.end(); iter++)
	{// <neID, neTypeID>
		if (g_bStopMongoDBNeStatusTheard){
			break;
		}

		stConfigGet stTmp;
		stTmp.id = iter->first;
		if ((iter->second == 266) || (iter->second == 276) || (iter->second == 246)  //690
			|| (iter->second == 292) || (iter->second == 293) || (iter->second == 294))  // 650
		{// 690 或 650？		
			stTmp.eFunType = EM_STATUS_NE_MCC;
		}
		else {
			stTmp.eFunType = EM_STATUS_NE_NORMAL;
		}
		vctGetConifg.push_back(stTmp);
	}
}

void OTNM2000GetNeconfigService::GetWaveName(string &strWaveName, const XC_WAVE_CODE_KEY &stWaveCodeKey){

	int waveBand = stWaveCodeKey.m_shWaveBand;
	char buf[10]="";
	switch (waveBand) {
		case 6:
			strWaveName = "CO";
			sprintf(buf, "%d", stWaveCodeKey.m_shWaveCode - 64);
			strWaveName += buf;
			break;
		case 8:
			strWaveName = "CE";
			sprintf(buf, "%d", stWaveCodeKey.m_shWaveCode);
			strWaveName += buf;//stlpd不支持+=整数
			break;
	}	
}

void OTNM2000GetNeconfigService::GetWaveName(string &strWaveName, int waveBand, int waveCode){

	char buf[10]="";
	switch (waveBand) {
		case 6:
			strWaveName = "CO";
			sprintf(buf, "%d", waveCode - 64);
			strWaveName += buf;
			break;
		case 8:
			strWaveName = "CE";
			sprintf(buf, "%d", waveCode);
			strWaveName += buf;//stlpd不支持+=整数
			break;
	}	
}


void OTNM2000GetNeconfigService::GetRefCircusFromJsonString(vector<string> &vctTunnelRefId, const string &strJsonResult, int nProtect, int nDirect)
{
#if 0
	//// stlpd不支持解析；
	Json::Reader reader;  
	Json::Value pRoot;
	if (reader.parse(strJsonResult.c_str(), pRoot))  // reader将Json字符串解析到root，root将包含Json里所有子元素  
	{
		Json::Value pRootPath;
		if (nProtect == 0) {// 工作路径  // 当前是正向的工作路径，嵌套的tunnel也要取出工作路径的正向；
			pRootPath = pRoot["workPath"];
		}
		else if (nProtect == 1){// 保护路径
			pRootPath = pRoot["protectPath"];
		}

		if (!pRootPath.isNull()){

			Json::Value pRootPathList;
			for (int j=0; j<pRootPath.size();++j){
				Json::Value pRootPathOne = pRootPath[j];
				if(!pRootPathOne["pathDirection"].isNull()){

					if (nDirect == 0){
						if(strncmp(pRootPathOne["pathDirection"].asCString(), "forward work", strlen("forward work")) == 0){
							pRootPathList = pRootPathOne["pathList"];
							break;
						}
					}
					else if (nDirect == 1){
						if(strncmp(pRootPathOne["pathDirection"].asCString(), "backward work", strlen("backward work")) == 0){
							pRootPathList = pRootPathOne["pathList"];
							break;
						}
					}
				}
			}

			if (!pRootPathList.isNull()){
				for (int k=0; k<pRootPathList.size();++k){
					Json::Value pPathInfoListRef = pRootPathList[k]["pathInfoListRef"];
					if (!pPathInfoListRef.isNull()){

						for(int m=0;m<pPathInfoListRef.size();++m){
							Json::Value pPathInfoListDBRef = pPathInfoListRef[m]["$id"];							
							if (!pPathInfoListDBRef.isNull()){

								vctTunnelRefId.push_back(pPathInfoListDBRef.asCString());
							}
						}
					}
				}
			}
		}
	}
#endif

}

void OTNM2000GetNeconfigService::SetRouteIDRefTable(bson_t *pKey, int nPathID, vector<XC_CROSS_ITEM> &oRoute, int nProtect, int nDirect, string &strWaveName,int &nFirstLabel, bool bIfFirst)
{// nProtect:0是工作路径，1是保护路径；  nDirect:0是前向路由，1是反向路由；  
	int nRouteSize = oRoute.size();
	if (nRouteSize == 0){
		return ;
	}

	int nPathInfo2D = nRouteSize*2;
	pBson*childSrcPathInfo = new pBson[nPathInfo2D];
	if (childSrcPathInfo == NULL){
		return;
	}

	//if (nPathID == 520174441){// pw路径中有tunnel的情况；
	//	int xx = 0; // 504415235 pathID =>134219122(网元id) =>  504415233(TUNNEL id)
	//}  

	int nSrcLen, nDst, i;
	char bufPathOrc[20]="",bufPathDst[20]="",tmpBuf[20]="";
	bson_t childdocs;	
	bson_init(&childdocs);
	for (i=0;i<nRouteSize;++i){

		XC_CROSS_ITEM &tmpWorkRoute=oRoute[i];

		///////////// TABLE_PATHINFO ///////////
		GetPathInfoTableID(bufPathOrc,nPathID, nDirect, i);
		GetPathInfoTableID(bufPathDst,nPathID, nDirect, i);
		strcat(bufPathDst, "_dst");
		strcat(bufPathOrc, "_orc");

		nSrcLen = (i<<1);
		nDst=nSrcLen+1;
		childSrcPathInfo[nSrcLen] = BCON_NEW("_id", bufPathOrc);
		childSrcPathInfo[nDst] = BCON_NEW("_id", bufPathDst);

		if (i==0 && bIfFirst){// 获取第一条路由的波长和pw标签；
			AddCircuitsPathInfoResource(childSrcPathInfo[nSrcLen], tmpWorkRoute, tmpWorkRoute.m_oSrc, 0, strWaveName, nFirstLabel, true); // pw,第一条label在第一条路由的src；
			AddCircuitsPathInfoResource(childSrcPathInfo[nDst], tmpWorkRoute, tmpWorkRoute.m_oDst, 1, strWaveName, nFirstLabel, true);	// 波长，在第一条的dst和后面的路由信息携带；		
		}
		else{
			AddCircuitsPathInfoResource(childSrcPathInfo[nSrcLen], tmpWorkRoute, tmpWorkRoute.m_oSrc, 0, strWaveName, nFirstLabel);
			AddCircuitsPathInfoResource(childSrcPathInfo[nDst], tmpWorkRoute, tmpWorkRoute.m_oDst, 1, strWaveName, nFirstLabel);			
		}
		///////////// TABLE_PATHINFO  end ////////

		bson_t childdoc;
		bson_init(&childdoc);
		if (tmpWorkRoute.m_iNodeId > 500000000){
#if 0
			//// 循环查询；=>ok;
			bson_t *child1,childList;			
			bson_init(&childList);
			child1 = BCON_NEW("$ref", strTABLE_PATH.c_str(), "$id", BCON_INT32(tmpWorkRoute.m_iNodeId));		
			bson_append_document(&childList, "0", -1, child1);	
			bson_append_array(&childdoc, "pathInfoListRef", -1, &childList);
			BCON_APPEND(&childdoc, "key", BCON_INT32(tmpWorkRoute.m_iNodeId)); // 电路id

			bson_destroy(child1);
			bson_destroy(&childdoc);
			bson_destroy(&childList);
#else
			//// 拆开嵌套路由；			
			bson_t childList;
			bson_init(&childList);
			bson_t *child1 = BCON_NEW("_id", BCON_INT32(tmpWorkRoute.m_iNodeId));	
			if(m_MongoDBOperator.QueryIDAndGetPathInfoContext(&childList, m_MongoDBOperator.m_strTableName.c_str(), strTABLE_PATH.c_str(), child1, nProtect, nDirect)){

				bson_append_array(&childdoc, "pathInfoListRef", -1, &childList);
				BCON_APPEND(&childdoc, "key", BCON_INT32(tmpWorkRoute.m_iNodeId));				
			}
			else{
				int xx = 0;
			}
			bson_destroy(child1);
			bson_destroy(&childList);
#endif
		}
		else{

			bson_t *child1,*child2,childList;	
			bson_init(&childList);
			child1 = BCON_NEW("$ref", strTABLE_PATHINFO.c_str(), "$id", bufPathOrc);
			child2 = BCON_NEW("$ref", strTABLE_PATHINFO.c_str(), "$id", bufPathDst);	
			bson_append_document(&childList, "0", -1, child1);
			bson_append_document(&childList, "1", -1, child2);

			bson_append_array(&childdoc, "pathInfoListRef", -1, &childList);
			BCON_APPEND(&childdoc, "key", BCON_INT32(tmpWorkRoute.m_iNodeId));

			bson_destroy(child1);
			bson_destroy(child2);		
			bson_destroy(&childList);
		}

		itoa(i,tmpBuf,10);
		bson_append_document (&childdocs, tmpBuf, -1, &childdoc);
		bson_destroy(&childdoc);
	}

	bson_append_array(pKey, "pathList", -1, &childdocs);
	BCON_APPEND(pKey, "pathDirection", BCON_UTF8(nDirect==0?"forward work":"backward work"));
	BCON_APPEND(pKey, "pathId", BCON_INT32(nPathID));
	bson_destroy(&childdocs);


#if DEFINE_MONGO_INSERT
	if(!m_MongoDBOperator.InsertMany(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_PATHINFO.c_str(), childSrcPathInfo, nPathInfo2D)){
		// log新增数据失败；
		//	bIfTableUpdateRight = false;

		char bufLog[512]="";			
		sprintf(bufLog, "Insert SetRouteIDRefTable PATHINFO Failure:%d\n", nPathID);
		WriteLog(bufLog);	
	}
#endif	

	for (i=0;i<nPathInfo2D;++i){
		bson_destroy(childSrcPathInfo[i]);
	}
	delete [] childSrcPathInfo;
	childSrcPathInfo = NULL;
}


void OTNM2000GetNeconfigService::SetPathIDRefTable(bson_t *pKey, vector<XC_PATH> &m_vectPath, const char *pPathListName)
{
	//int nTest = m_vectPath.size();
	/*if (nTest >= 2)
	{
	int xxx = 0;
	}*/
	char buf[10]="";
	bson_t child,child1;
	bson_init(&child);
	for (int i=0;i<(int)m_vectPath.size();++i){

		bson_init(&child1);

		XC_PATH &tmpWorkPath=m_vectPath[i];
		BCON_APPEND(&child1, "$ref", strTABLE_PATH.c_str(), "$id", BCON_INT32(tmpWorkPath.m_iId));

		itoa(i,buf, 10);
		bson_append_document (&child, buf, -1, &child1);

		bson_destroy(&child1);
	}
	bson_append_array(pKey, pPathListName, -1, &child);
	bson_destroy(&child);

}

bool OTNM2000GetNeconfigService::GetBusinessLayerRelation(int m_iObjId, vector<int> &vctRelationPwID, vector<int> &vctRelationTunnelID, vector<int> &vctL2vpnRelationID, vector<int> &vctL3vpnRelationID, vector<int> &vctProtect, vector<int> &vctRoduk,vector<int> &vctRclient,vector<int> &vctRoch, vector<int> &vctRoms, vector<int> &vctRots, EServiceLayer m_eServiceLayer, vector<XC_OBJ_KEY> &objKey)
{
	int i,j,nId;
	std::vector<XC_BUSINESS_LAYER_RELATION_INFO> vectRelations;
	ERROR_CODE eCode = SNC_GetBusinessLayerRelationByObjKey(m_hSess, objKey, vectRelations);// 调用一段时间后，会连接失败,导致部分的关联关系失败。
	if(ERR_OK == eCode){
		for (i =0; i<(int)vectRelations.size(); ++i){

			if (g_bStopMongoDBTheard){
				return true;
			}

			XC_BUSINESS_LAYER_RELATION_INFO &tmpBusinessLayer = vectRelations[i];

			if((m_eServiceLayer == PTN_LAYER_TMP) || (m_eServiceLayer == PTN_LAYER_TMC) || (m_eServiceLayer == OTN_LAYER_CLIENT)
				|| (m_eServiceLayer == OTN_LAYER_ODUK) || (m_eServiceLayer == OTN_LAYER_OTS)
				|| (m_eServiceLayer == OTN_LAYER_OMS) || (m_eServiceLayer == OTN_LAYER_OCH))
			{// pw或tunnel的关联关系；

				if(tmpBusinessLayer.m_eObjectLayer == OTN_LAYER_ODUK){ //oTN 
					for (j = 0; j < (int)tmpBusinessLayer.vecObjId.size(); ++j){
						nId = tmpBusinessLayer.vecObjId[j];
						if (nId == m_iObjId){// 跳过自身id一样的引用；
							continue;
						}
						vctRoduk.push_back(nId);					
					}
				}	
				else if(tmpBusinessLayer.m_eObjectLayer == OTN_LAYER_OMS){ //oTN
					for (j = 0; j < (int)tmpBusinessLayer.vecObjId.size(); ++j){
						nId = tmpBusinessLayer.vecObjId[j];
						if (nId == m_iObjId){// 跳过自身id一样的引用；
							continue;
						}
						vctRoms.push_back(nId);					
					}
				}	
				else if(tmpBusinessLayer.m_eObjectLayer == OTN_LAYER_OTS){ //oTN
					for (j = 0; j < (int)tmpBusinessLayer.vecObjId.size(); ++j){
						nId = tmpBusinessLayer.vecObjId[j];
						if (nId == m_iObjId){// 跳过自身id一样的引用；
							continue;
						}
						vctRots.push_back(nId);					
					}
				}	
				else if(tmpBusinessLayer.m_eObjectLayer == OTN_LAYER_OCH){ //oTN
					for (j = 0; j < (int)tmpBusinessLayer.vecObjId.size(); ++j){
						nId = tmpBusinessLayer.vecObjId[j];
						if (nId == m_iObjId){// 跳过自身id一样的引用；
							continue;
						}
						vctRoch.push_back(nId);					
					}
				}	
				else if(tmpBusinessLayer.m_eObjectLayer == OTN_LAYER_CLIENT){//oTN
					for (j = 0; j < (int)tmpBusinessLayer.vecObjId.size(); ++j){
						nId = tmpBusinessLayer.vecObjId[j];
						if (nId == m_iObjId){// 跳过自身id一样的引用；
							continue;
						}
						vctRclient.push_back(nId);					
					}
				}	
				else if(tmpBusinessLayer.m_eObjectLayer == PTN_LAYER_TMC){ //PTN PW层
					if(tmpBusinessLayer.m_eObjectType == OT_CIRCUIT){//// 电路类型；
						for (j = 0; j < (int)tmpBusinessLayer.vecObjId.size(); ++j){
							nId = tmpBusinessLayer.vecObjId[j];
							if (nId == m_iObjId){// 跳过自身id一样的引用；
								continue;
							}
							vctRelationPwID.push_back(nId);					
						}
					}
				}							
				else if(tmpBusinessLayer.m_eObjectLayer == PTN_LAYER_TMP){ //PTN Tunnel层
					if(tmpBusinessLayer.m_eObjectType == OT_CIRCUIT){//// 电路类型；
						for (j = 0; j < (int)tmpBusinessLayer.vecObjId.size(); j++){
							nId = tmpBusinessLayer.vecObjId[j];
							if (nId == m_iObjId){// 跳过自身id一样的引用；
								continue;
							}
							vctRelationTunnelID.push_back(nId);					
						}
					}				
				}

				if(tmpBusinessLayer.m_eObjectLayer == PTN_LAYER_CLIENT){//ptn 

					if (OT_L3VPN == tmpBusinessLayer.m_eObjectType){// l3vpn
						for (j = 0; j < (int)tmpBusinessLayer.vecObjId.size(); j++){
							nId = tmpBusinessLayer.vecObjId[j];
							if (nId == m_iObjId){// 跳过自身id一样的引用；
								continue;
							}
							vctL3vpnRelationID.push_back(nId);					
						}
					}else{// l2vpn
						for (j = 0; j < (int)tmpBusinessLayer.vecObjId.size(); j++){
							nId = tmpBusinessLayer.vecObjId[j];
							if (nId == m_iObjId){// 跳过自身id一样的引用；
								continue;
							}
							vctL2vpnRelationID.push_back(nId);					
						}
					}				
				}
				else if(tmpBusinessLayer.m_eObjectType == OT_PROTECT_RELATION){//// 保护关系；				

					for (j = 0; j < (int)tmpBusinessLayer.vecObjId.size(); j++){
						nId = tmpBusinessLayer.vecObjId[j];
						if (nId == m_iObjId){// 跳过自身id一样的引用；
							continue;
						}
						vctProtect.push_back(nId);					
					}
				}				
			}
			else if ((m_eServiceLayer == IPRAN_LAYER_L3VPN)||(m_eServiceLayer == PTN_LAYER_CLIENT))
			{// l2和l3的业务只会关联pw或是tunnel; => otn不用支持l2的业务；
				if(tmpBusinessLayer.m_eObjectType == OT_CIRCUIT){//// 电路类型；

					if(tmpBusinessLayer.m_eObjectLayer == PTN_LAYER_TMC){// pw
						for (j = 0; j < (int)tmpBusinessLayer.vecObjId.size(); j++){
							nId = tmpBusinessLayer.vecObjId[j];
							if (nId == m_iObjId){// 跳过自身id一样的引用；
								continue;
							}
							vctRelationPwID.push_back(nId);					
						}
					}
					else if(tmpBusinessLayer.m_eObjectLayer == PTN_LAYER_TMP){// tunnel
						for (j = 0; j < (int)tmpBusinessLayer.vecObjId.size(); j++){
							nId = tmpBusinessLayer.vecObjId[j];
							if (nId == m_iObjId){// 跳过自身id一样的引用；
								continue;
							}
							vctRelationTunnelID.push_back(nId);					
						}
					}
				}				
				else if(tmpBusinessLayer.m_eObjectType == OT_PROTECT_RELATION){//// 保护关系；

					if((tmpBusinessLayer.m_eObjectLayer == PTN_LAYER_TMC)// pw
						|| (tmpBusinessLayer.m_eObjectLayer == PTN_LAYER_TMP)) // tunnel
					{
						for (j = 0; j < (int)tmpBusinessLayer.vecObjId.size(); j++){
							nId = tmpBusinessLayer.vecObjId[j];
							if (nId == m_iObjId){// 跳过自身id一样的引用；
								continue;
							}
							vctProtect.push_back(nId);					
						}
					}
				}
			}
			else if(m_eServiceLayer ==PTN_LAYER_RING){

				if(tmpBusinessLayer.m_eObjectLayer == PTN_LAYER_CLIENT){// l2vpn

					if (OT_L3VPN == tmpBusinessLayer.m_eObjectType){
						for (j = 0; j < (int)tmpBusinessLayer.vecObjId.size(); j++){
							nId = tmpBusinessLayer.vecObjId[j];
							if (nId == m_iObjId){// 跳过自身id一样的引用；
								continue;
							}
							vctL3vpnRelationID.push_back(nId);					
						}
					}
					else{// 不是l3，就算是l2；
						for (j = 0; j < (int)tmpBusinessLayer.vecObjId.size(); j++){
							nId = tmpBusinessLayer.vecObjId[j];
							if (nId == m_iObjId){// 跳过自身id一样的引用；
								continue;
							}
							vctL2vpnRelationID.push_back(nId);					
						}
					}			
				}
			}
		}	
	}
	else{
		return false;
	}

	return true;
}


void OTNM2000GetNeconfigService::GetNeAndBoardNameID()
{	
	m_MongoDBOperator.QueryAndGetTableIDandName(mapIDName, m_MongoDBOperator.m_strTableName.c_str(), 
		strNeTableName.c_str(), "_id", strNeTableKey.c_str());
	for(map<int,string>::iterator iter = mapIDName.begin(); iter != mapIDName.end(); iter++){

		bson_t *pKey = BCON_NEW("_id", BCON_INT32(iter->first));
		string strCurName = UTF8_To_string(iter->second); // java中返回的utf-8，先转成asii，再转出utf-8存进数据库；
		string strCurName2 = string_To_UTF8(strCurName);	
		BCON_APPEND(pKey, "NeName", strCurName2.c_str());

#if DEFINE_MONGO_INSERT
		if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strNeNameRef.c_str(), pKey)){
			// log新增数据失败；			
			char bufLog[512]="";			
			sprintf(bufLog, "Insert GetNeNameID Failure:%d\n", iter->first);
			WriteLog(bufLog);	
		}
#endif
		bson_destroy(pKey);
	}
	mapIDName.clear();

	m_MongoDBOperator.QueryAndGetTableIDandName(mapIDName, m_MongoDBOperator.m_strTableName.c_str(), 
		strBoardName.c_str(), "_id",strBoardKey.c_str());
	for(map<int,string>::iterator iter = mapIDName.begin(); iter != mapIDName.end(); iter++){

		bson_t *pKey = BCON_NEW("_id", BCON_INT32(iter->first));
		string strCurName = UTF8_To_string(iter->second); // java中返回的utf-8，先转成asii，再转出utf-8存进数据库；
		string strCurName2 = string_To_UTF8(strCurName);	
		BCON_APPEND(pKey, "boardName", strCurName2.c_str());

#if DEFINE_MONGO_INSERT
		if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strBoardNameRef.c_str(), pKey)){
			// log新增数据失败；
			char bufLog[512]="";			
			sprintf(bufLog, "Insert GetBoardNameID Failure:%d\n", iter->first);
			WriteLog(bufLog);		
		}
#endif
		bson_destroy(pKey);
	}
	mapIDName.clear();
}


void OTNM2000GetNeconfigService::GetOneCircuitsSetToMongoDB(XC_CIRCUIT &tmpOneCircuit, int nIndex, int nTypeIndex, const string &strWaveName, int nFirstLabel)
{
	//	tmpOneCircuit.m_iId = 504389480;// 								 
	//BCON_UTF8   BCON_INT64   BCON_INT32
	//if (tmpOneCircuit.m_iId == 504412637){
	//	int xx = 0;
	//}

//	WriteLog("GetOneCircuitsSetToMongoDB test");

	if(tmpOneCircuit.m_eServiceLayer == PTN_LAYER_TMP){// tunnel

		m_pKeyRef[nTypeIndex] = BCON_NEW("_id", BCON_INT32(tmpOneCircuit.m_iId));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "tableType", TABLE_TUNNEL);

		BCON_APPEND(m_pKeyRef[nTypeIndex], "aperateMode", BCON_INT32(tmpOneCircuit.m_eOperMode));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "activeState", BCON_INT32(tmpOneCircuit.m_eState));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "brokenRepairStatus", BCON_INT32(tmpOneCircuit.m_eRepairStatus));
		//  XC_OBJ_BROKEN_REASON m_stBrokenReason;
		string strCurName = string_To_UTF8(tmpOneCircuit.m_sName);
		BCON_APPEND(m_pKeyRef[nTypeIndex], "name", strCurName.c_str());
		BCON_APPEND(m_pKeyRef[nTypeIndex], "createTime", BCON_INT64(tmpOneCircuit.m_tmCreateTime));
		strCurName = string_To_UTF8(tmpOneCircuit.m_sCreateUserName);
		BCON_APPEND(m_pKeyRef[nTypeIndex], "createUserName", strCurName.c_str());
		BCON_APPEND(m_pKeyRef[nTypeIndex], "modifyTime", BCON_INT64(tmpOneCircuit.m_tmModifyTime));
		strCurName = string_To_UTF8(tmpOneCircuit.m_sModifyUserName);
		BCON_APPEND(m_pKeyRef[nTypeIndex], "modifyUserName", strCurName.c_str());
		BCON_APPEND(m_pKeyRef[nTypeIndex], "circuitDirection", BCON_INT32(tmpOneCircuit.m_eDirection));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "netType", BCON_INT32(tmpOneCircuit.m_eNetType));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "connectionType", BCON_INT32(tmpOneCircuit.m_eConnectionType));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "switchStatus", BCON_INT32(tmpOneCircuit.m_eSwitchStatus));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "alarmLevel", BCON_INT32(tmpOneCircuit.m_eAlarmLevel));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "alarmMoniter", BCON_UTF8(tmpOneCircuit.m_eAlarmMoniter.c_str()));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "performanceMoniter", BCON_UTF8(tmpOneCircuit.m_ePerformanceMoniter.c_str()));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "srcPortRate", BCON_INT32(tmpOneCircuit.m_eSrcPortRate));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "dstPortRate", BCON_INT32(tmpOneCircuit.m_eDstPortRate));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "serviceLayer", BCON_INT32(tmpOneCircuit.m_eServiceLayer));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "bandWidthType", BCON_INT32(tmpOneCircuit.m_eBandWidthType)); //业务带宽类型 (*通道速率类型)
		BCON_APPEND(m_pKeyRef[nTypeIndex], "concatenationType", BCON_INT32(tmpOneCircuit.m_eConcatenationType));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "protectType", BCON_INT32(tmpOneCircuit.m_eProtectType));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "serviceClass", BCON_INT32(tmpOneCircuit.m_eServiceClass));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "srcNeId", BCON_INT32(tmpOneCircuit.m_iNeId[0]));

		bson_t childDataNameRef;
		bson_init(&childDataNameRef);
		BCON_APPEND(&childDataNameRef, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iNeId[0]));					
		bson_append_document (m_pKeyRef[nTypeIndex], "srcNameRef", -1, &childDataNameRef);
		bson_destroy(&childDataNameRef);

		bson_t childDataNameRefdst;
		BCON_APPEND(m_pKeyRef[nTypeIndex], "dstNeId", BCON_INT32(tmpOneCircuit.m_iNeId[1]));
		bson_init(&childDataNameRefdst);
		BCON_APPEND(&childDataNameRefdst, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iNeId[1]));					
		bson_append_document (m_pKeyRef[nTypeIndex], "dstNameRef", -1, &childDataNameRefdst);
		bson_destroy(&childDataNameRefdst);

		string strBussinessType ="BusinessType_";
		if(tmpOneCircuit.m_mapExtendAttribute.find(BUSINESS_TYPE) != tmpOneCircuit.m_mapExtendAttribute.end()){
			strBussinessType += tmpOneCircuit.m_mapExtendAttribute[BUSINESS_TYPE];
		}
		bson_t childDataNameReftype;
		bson_init(&childDataNameReftype);
		BCON_APPEND(&childDataNameReftype, "$ref", m_strCommonRefTable.c_str(), "$id", BCON_UTF8(strBussinessType.c_str()));					
		bson_append_document (m_pKeyRef[nTypeIndex], "businessType", -1, &childDataNameReftype);
		bson_destroy(&childDataNameReftype);

		BCON_APPEND(m_pKeyRef[nTypeIndex], "returnType", BCON_INT32(tmpOneCircuit.m_eReturnType));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "waitToRestoreTime", BCON_INT32((int)tmpOneCircuit.m_shWaitToRestoreTime));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "holdOffTime", BCON_INT32((int)tmpOneCircuit.m_shHoldOffTime));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "protectMonitorType", BCON_INT32(tmpOneCircuit.m_eProtectMonitorType));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "protectMode", BCON_INT32((int)tmpOneCircuit.m_eProtectMode)); // 单向或双向
		BCON_APPEND(m_pKeyRef[nTypeIndex], "usedCir", BCON_INT32(tmpOneCircuit.m_iUsedCir));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "labelDiffRvsWithFwd", BCON_INT32(tmpOneCircuit.m_iLabelDiffRvsWithFwd));	
		strCurName = string_To_UTF8(tmpOneCircuit.m_sClientName);
		BCON_APPEND(m_pKeyRef[nTypeIndex], "ClientName", strCurName.c_str());
		strCurName = string_To_UTF8(tmpOneCircuit.m_sUserLabel); // 用户标签
		BCON_APPEND(m_pKeyRef[nTypeIndex], "userLabel", strCurName.c_str());		
		strCurName = string_To_UTF8(tmpOneCircuit.m_sCircuitAlias); // 乱码
		BCON_APPEND(m_pKeyRef[nTypeIndex], "circuitAlias", BCON_UTF8(strCurName.c_str()));

		// vector<string>		m_vectReserve;
		// map<EExtendAttributeType, string> m_mapExtendAttribute;
		BCON_APPEND(m_pKeyRef[nTypeIndex], "tunnelRouteAdjustStatus", BCON_INT32(tmpOneCircuit.m_eEmTunnelRouteAdjustStatus));
		BCON_APPEND(m_pKeyRef[nTypeIndex], "oduflexEncapType", BCON_INT32(tmpOneCircuit.m_eOduflexEncapType));

		////////////////////////		
		m_pKeyTunnelRef[nTypeIndex] = BCON_NEW("_id", BCON_INT32(tmpOneCircuit.m_iId));

		//	tmpOneCircuit.m_iId = 504412625;
		GetMongoBusinessLayerRelation(m_pKeyTunnelRef[nTypeIndex], OT_CIRCUIT, tmpOneCircuit.m_eServiceLayer, tmpOneCircuit.m_iId);					

		bson_t childDataRouteRef;
		bson_init(&childDataRouteRef);
		BCON_APPEND(&childDataRouteRef, "$ref", strTABLE_PATH.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iId));					
		bson_append_document (m_pKeyTunnelRef[nTypeIndex], "routeRef", -1, &childDataRouteRef);
		bson_destroy(&childDataRouteRef);

		bson_t childDataRef;
		bson_init(&childDataRef);
		BCON_APPEND(&childDataRef, "$ref", strTABLE_Tunnel_data.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iId));					
		bson_append_document (m_pKeyTunnelRef[nTypeIndex], "dataRef", -1, &childDataRef);
		bson_destroy(&childDataRef);
	}
	else if(tmpOneCircuit.m_eServiceLayer == PTN_LAYER_TMC){// pw

		m_pKeyDataPwRef[nTypeIndex] = BCON_NEW("_id", BCON_INT32(tmpOneCircuit.m_iId));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "tableType", TABLE_PW);
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "aperateMode", BCON_INT32(tmpOneCircuit.m_eOperMode));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "activeState", BCON_INT32(tmpOneCircuit.m_eState));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "brokenRepairStatus", BCON_INT32(tmpOneCircuit.m_eRepairStatus));
		//  XC_OBJ_BROKEN_REASON m_stBrokenReason;
		string strCurName = string_To_UTF8(tmpOneCircuit.m_sName);
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "name", strCurName.c_str());
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "createTime", BCON_INT64(tmpOneCircuit.m_tmCreateTime));
		strCurName = string_To_UTF8(tmpOneCircuit.m_sCreateUserName);
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "createUserName", strCurName.c_str());
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "modifyTime", BCON_INT64(tmpOneCircuit.m_tmModifyTime));
		strCurName = string_To_UTF8(tmpOneCircuit.m_sModifyUserName);
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "modifyUserName", strCurName.c_str());
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "circuitDirection", BCON_INT32(tmpOneCircuit.m_eDirection));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "netType", BCON_INT32(tmpOneCircuit.m_eNetType));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "connectionType", BCON_INT32(tmpOneCircuit.m_eConnectionType));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "switchStatus", BCON_INT32(tmpOneCircuit.m_eSwitchStatus));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "alarmLevel", BCON_INT32(tmpOneCircuit.m_eAlarmLevel));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "alarmMoniter", BCON_UTF8(tmpOneCircuit.m_eAlarmMoniter.c_str()));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "performanceMoniter", BCON_UTF8(tmpOneCircuit.m_ePerformanceMoniter.c_str()));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "srcPortRate", BCON_INT32(tmpOneCircuit.m_eSrcPortRate));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "dstPortRate", BCON_INT32(tmpOneCircuit.m_eDstPortRate));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "serviceLayer", BCON_INT32(tmpOneCircuit.m_eServiceLayer));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "bandWidthType", BCON_INT32(tmpOneCircuit.m_eBandWidthType));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "concatenationType", BCON_INT32(tmpOneCircuit.m_eConcatenationType));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "protectType", BCON_INT32(tmpOneCircuit.m_eProtectType));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "serviceClass", BCON_INT32(tmpOneCircuit.m_eServiceClass));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "srcNeId", BCON_INT32(tmpOneCircuit.m_iNeId[0]));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "pwFirstLabel", BCON_INT32(nFirstLabel));// pw独有字段；

		bson_t childDataNameRef;
		bson_init(&childDataNameRef);
		BCON_APPEND(&childDataNameRef, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iNeId[0]));					
		bson_append_document (m_pKeyDataPwRef[nTypeIndex], "srcNameRef", -1, &childDataNameRef);
		bson_destroy(&childDataNameRef);

		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "dstNeId", BCON_INT32(tmpOneCircuit.m_iNeId[1]));	
		bson_t childDataNameRefdst;
		bson_init(&childDataNameRefdst);
		BCON_APPEND(&childDataNameRefdst, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iNeId[1]));					
		bson_append_document (m_pKeyDataPwRef[nTypeIndex], "dstNameRef", -1, &childDataNameRefdst);
		bson_destroy(&childDataNameRefdst);

		string strBussinessType ="BusinessType_";
		if(tmpOneCircuit.m_mapExtendAttribute.find(BUSINESS_TYPE) != tmpOneCircuit.m_mapExtendAttribute.end()){
			strBussinessType += tmpOneCircuit.m_mapExtendAttribute[BUSINESS_TYPE];
		}
		bson_t childDataNameReftype;
		bson_init(&childDataNameReftype);
		BCON_APPEND(&childDataNameReftype, "$ref", m_strCommonRefTable.c_str(), "$id", BCON_UTF8(strBussinessType.c_str()));					
		bson_append_document (m_pKeyDataPwRef[nTypeIndex], "businessType", -1, &childDataNameReftype);
		bson_destroy(&childDataNameReftype);

		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "returnType", BCON_INT32(tmpOneCircuit.m_eReturnType));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "waitToRestoreTime", BCON_INT32((int)tmpOneCircuit.m_shWaitToRestoreTime));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "holdOffTime", BCON_INT32((int)tmpOneCircuit.m_shHoldOffTime));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "protectMonitorType", BCON_INT32(tmpOneCircuit.m_eProtectMonitorType));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "protectMode", BCON_INT32((int)tmpOneCircuit.m_eProtectMode)); // 单向或双向
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "usedCir", BCON_INT32(tmpOneCircuit.m_iUsedCir));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "labelDiffRvsWithFwd", BCON_INT32(tmpOneCircuit.m_iLabelDiffRvsWithFwd));	
		strCurName = string_To_UTF8(tmpOneCircuit.m_sClientName);
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "ClientName", strCurName.c_str());
		strCurName = string_To_UTF8(tmpOneCircuit.m_sUserLabel);
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "userLabel", strCurName.c_str());

		strCurName = string_To_UTF8(tmpOneCircuit.m_sCircuitAlias); // 乱码
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "circuitAlias", BCON_UTF8(strCurName.c_str()));
		// vector<string>		m_vectReserve;
		// map<EExtendAttributeType, string> m_mapExtendAttribute;
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "tunnelRouteAdjustStatus", BCON_INT32(tmpOneCircuit.m_eEmTunnelRouteAdjustStatus));
		BCON_APPEND(m_pKeyDataPwRef[nTypeIndex], "oduflexEncapType", BCON_INT32(tmpOneCircuit.m_eOduflexEncapType));

		/////////////////////////// 
		m_pKeyPwRef[nTypeIndex] = BCON_NEW("_id", BCON_INT32(tmpOneCircuit.m_iId));	
		GetMongoBusinessLayerRelation(m_pKeyPwRef[nTypeIndex], OT_CIRCUIT, tmpOneCircuit.m_eServiceLayer, tmpOneCircuit.m_iId);					

		bson_t childDataRouteRef;
		bson_init(&childDataRouteRef);
		BCON_APPEND(&childDataRouteRef, "$ref", strTABLE_PATH.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iId));					
		bson_append_document (m_pKeyPwRef[nTypeIndex], "routeRef", -1, &childDataRouteRef);
		bson_destroy(&childDataRouteRef);

		bson_t childDataRef;
		bson_init(&childDataRef);
		BCON_APPEND(&childDataRef, "$ref", strTABLE_Pw_data.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iId));					
		bson_append_document (m_pKeyPwRef[nTypeIndex], "dataRef", -1, &childDataRef);
		bson_destroy(&childDataRef);
	}	
	else if(tmpOneCircuit.m_eServiceLayer == OTN_LAYER_OCH){// OTN_LAYER_OCH
		bIsOtnCircus = true;

		m_pKeyDataOchRef[nTypeIndex] = BCON_NEW("_id", BCON_INT32(tmpOneCircuit.m_iId));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "tableType", TABLE_OCH);
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "aperateMode", BCON_INT32(tmpOneCircuit.m_eOperMode));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "activeState", BCON_INT32(tmpOneCircuit.m_eState));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "brokenRepairStatus", BCON_INT32(tmpOneCircuit.m_eRepairStatus));
		//  XC_OBJ_BROKEN_REASON m_stBrokenReason;
		string strCurName = string_To_UTF8(tmpOneCircuit.m_sName);
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "name", strCurName.c_str());
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "createTime", BCON_INT64(tmpOneCircuit.m_tmCreateTime));
		strCurName = string_To_UTF8(tmpOneCircuit.m_sCreateUserName);
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "createUserName", strCurName.c_str());
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "modifyTime", BCON_INT64(tmpOneCircuit.m_tmModifyTime));
		strCurName = string_To_UTF8(tmpOneCircuit.m_sModifyUserName);
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "modifyUserName", strCurName.c_str());
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "circuitDirection", BCON_INT32(tmpOneCircuit.m_eDirection));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "netType", BCON_INT32(tmpOneCircuit.m_eNetType));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "connectionType", BCON_INT32(tmpOneCircuit.m_eConnectionType));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "switchStatus", BCON_INT32(tmpOneCircuit.m_eSwitchStatus));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "alarmLevel", BCON_INT32(tmpOneCircuit.m_eAlarmLevel));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "alarmMoniter", BCON_UTF8(tmpOneCircuit.m_eAlarmMoniter.c_str()));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "performanceMoniter", BCON_UTF8(tmpOneCircuit.m_ePerformanceMoniter.c_str()));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "srcPortRate", BCON_INT32(tmpOneCircuit.m_eSrcPortRate));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "dstPortRate", BCON_INT32(tmpOneCircuit.m_eDstPortRate));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "serviceLayer", BCON_INT32(tmpOneCircuit.m_eServiceLayer));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "bandWidthType", BCON_INT32(tmpOneCircuit.m_eBandWidthType));
		GetBandWidthStr(strCurName, tmpOneCircuit.m_eBandWidthType);
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "bandWidthTypeName", strCurName.c_str());

		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "concatenationType", BCON_INT32(tmpOneCircuit.m_eConcatenationType));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "protectType", BCON_INT32(tmpOneCircuit.m_eProtectType));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "serviceClass", BCON_INT32(tmpOneCircuit.m_eServiceClass));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "srcNeId", BCON_INT32(tmpOneCircuit.m_iNeId[0]));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "otnWave", strWaveName.c_str()); // //PTN的 Tunnel标签; //SDH的VC4Index //OCH电路的波长	


		bson_t childDataNameRef;
		bson_init(&childDataNameRef);
		BCON_APPEND(&childDataNameRef, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iNeId[0]));					
		bson_append_document (m_pKeyDataOchRef[nTypeIndex], "srcNameRef", -1, &childDataNameRef);
		bson_destroy(&childDataNameRef);

		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "dstNeId", BCON_INT32(tmpOneCircuit.m_iNeId[1]));	
		bson_t childDataNameRefdst;
		bson_init(&childDataNameRefdst);
		BCON_APPEND(&childDataNameRefdst, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iNeId[1]));					
		bson_append_document (m_pKeyDataOchRef[nTypeIndex], "dstNameRef", -1, &childDataNameRefdst);
		bson_destroy(&childDataNameRefdst);

		string strBussinessType ="BusinessType_";
		if(tmpOneCircuit.m_mapExtendAttribute.find(BUSINESS_TYPE) != tmpOneCircuit.m_mapExtendAttribute.end()){
			strBussinessType += tmpOneCircuit.m_mapExtendAttribute[BUSINESS_TYPE];
		}
		bson_t childDataNameReftype;
		bson_init(&childDataNameReftype);
		BCON_APPEND(&childDataNameReftype, "$ref", m_strCommonRefTable.c_str(), "$id", BCON_UTF8(strBussinessType.c_str()));					
		bson_append_document (m_pKeyDataOchRef[nTypeIndex], "businessType", -1, &childDataNameReftype);
		bson_destroy(&childDataNameReftype);

		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "returnType", BCON_INT32(tmpOneCircuit.m_eReturnType));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "waitToRestoreTime", BCON_INT32((int)tmpOneCircuit.m_shWaitToRestoreTime));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "holdOffTime", BCON_INT32((int)tmpOneCircuit.m_shHoldOffTime));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "protectMonitorType", BCON_INT32(tmpOneCircuit.m_eProtectMonitorType));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "protectMode", BCON_INT32((int)tmpOneCircuit.m_eProtectMode)); // 单向或双向
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "usedCir", BCON_INT32(tmpOneCircuit.m_iUsedCir));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "labelDiffRvsWithFwd", BCON_INT32(tmpOneCircuit.m_iLabelDiffRvsWithFwd));	
		strCurName = string_To_UTF8(tmpOneCircuit.m_sClientName);
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "ClientName", strCurName.c_str());
		strCurName = string_To_UTF8(tmpOneCircuit.m_sUserLabel);
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "userLabel", strCurName.c_str());
		strCurName = string_To_UTF8(tmpOneCircuit.m_sCircuitAlias); // 乱码
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "circuitAlias", BCON_UTF8(strCurName.c_str()));
		// vector<string>		m_vectReserve;
		// map<EExtendAttributeType, string> m_mapExtendAttribute;
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "tunnelRouteAdjustStatus", BCON_INT32(tmpOneCircuit.m_eEmTunnelRouteAdjustStatus));
		BCON_APPEND(m_pKeyDataOchRef[nTypeIndex], "oduflexEncapType", BCON_INT32(tmpOneCircuit.m_eOduflexEncapType));

		/////////////////////////// 
		m_pKeyOchRef[nTypeIndex] = BCON_NEW("_id", BCON_INT32(tmpOneCircuit.m_iId));	
		GetMongoBusinessLayerRelation(m_pKeyOchRef[nTypeIndex], OT_CIRCUIT, tmpOneCircuit.m_eServiceLayer, tmpOneCircuit.m_iId);					

		bson_t childDataRouteRef;
		bson_init(&childDataRouteRef);
		BCON_APPEND(&childDataRouteRef, "$ref", strTABLE_PATH.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iId));					
		bson_append_document (m_pKeyOchRef[nTypeIndex], "routeRef", -1, &childDataRouteRef);
		bson_destroy(&childDataRouteRef);

		bson_t childDataRef;
		bson_init(&childDataRef);
		BCON_APPEND(&childDataRef, "$ref", strTABLE_Och_data.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iId));					
		bson_append_document (m_pKeyOchRef[nTypeIndex], "dataRef", -1, &childDataRef);
		bson_destroy(&childDataRef);
	}
	else if(tmpOneCircuit.m_eServiceLayer == OTN_LAYER_ODUK){// OTN_LAYER_OCH
		bIsOtnCircus = true;

		m_pKeyDataOdukRef[nTypeIndex] = BCON_NEW("_id", BCON_INT32(tmpOneCircuit.m_iId));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "tableType", TABLE_ODUK);
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "aperateMode", BCON_INT32(tmpOneCircuit.m_eOperMode));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "activeState", BCON_INT32(tmpOneCircuit.m_eState));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "brokenRepairStatus", BCON_INT32(tmpOneCircuit.m_eRepairStatus));
		//  XC_OBJ_BROKEN_REASON m_stBrokenReason;
		string strCurName = string_To_UTF8(tmpOneCircuit.m_sName);
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "name", strCurName.c_str());
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "createTime", BCON_INT64(tmpOneCircuit.m_tmCreateTime));
		strCurName = string_To_UTF8(tmpOneCircuit.m_sCreateUserName);
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "createUserName", strCurName.c_str());
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "modifyTime", BCON_INT64(tmpOneCircuit.m_tmModifyTime));
		strCurName = string_To_UTF8(tmpOneCircuit.m_sModifyUserName);
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "modifyUserName", strCurName.c_str());
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "circuitDirection", BCON_INT32(tmpOneCircuit.m_eDirection));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "netType", BCON_INT32(tmpOneCircuit.m_eNetType));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "connectionType", BCON_INT32(tmpOneCircuit.m_eConnectionType));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "switchStatus", BCON_INT32(tmpOneCircuit.m_eSwitchStatus));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "alarmLevel", BCON_INT32(tmpOneCircuit.m_eAlarmLevel));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "alarmMoniter", BCON_UTF8(tmpOneCircuit.m_eAlarmMoniter.c_str()));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "performanceMoniter", BCON_UTF8(tmpOneCircuit.m_ePerformanceMoniter.c_str()));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "srcPortRate", BCON_INT32(tmpOneCircuit.m_eSrcPortRate));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "dstPortRate", BCON_INT32(tmpOneCircuit.m_eDstPortRate));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "serviceLayer", BCON_INT32(tmpOneCircuit.m_eServiceLayer));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "bandWidthType", BCON_INT32(tmpOneCircuit.m_eBandWidthType));
		GetBandWidthStr(strCurName, tmpOneCircuit.m_eBandWidthType);
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "bandWidthTypeName", strCurName.c_str());

		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "concatenationType", BCON_INT32(tmpOneCircuit.m_eConcatenationType));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "protectType", BCON_INT32(tmpOneCircuit.m_eProtectType));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "serviceClass", BCON_INT32(tmpOneCircuit.m_eServiceClass));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "srcNeId", BCON_INT32(tmpOneCircuit.m_iNeId[0]));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "otnWave", strWaveName.c_str()); // //PTN的 Tunnel标签; //SDH的VC4Index //OCH电路的波长	


		bson_t childDataNameRef;
		bson_init(&childDataNameRef);
		BCON_APPEND(&childDataNameRef, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iNeId[0]));					
		bson_append_document (m_pKeyDataOdukRef[nTypeIndex], "srcNameRef", -1, &childDataNameRef);
		bson_destroy(&childDataNameRef);

		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "dstNeId", BCON_INT32(tmpOneCircuit.m_iNeId[1]));	
		bson_t childDataNameRefdst;
		bson_init(&childDataNameRefdst);
		BCON_APPEND(&childDataNameRefdst, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iNeId[1]));					
		bson_append_document (m_pKeyDataOdukRef[nTypeIndex], "dstNameRef", -1, &childDataNameRefdst);
		bson_destroy(&childDataNameRefdst);

		string strBussinessType ="BusinessType_";
		if(tmpOneCircuit.m_mapExtendAttribute.find(BUSINESS_TYPE) != tmpOneCircuit.m_mapExtendAttribute.end()){
			strBussinessType += tmpOneCircuit.m_mapExtendAttribute[BUSINESS_TYPE];
		}
		bson_t childDataNameReftype;
		bson_init(&childDataNameReftype);
		BCON_APPEND(&childDataNameReftype, "$ref", m_strCommonRefTable.c_str(), "$id", BCON_UTF8(strBussinessType.c_str()));					
		bson_append_document (m_pKeyDataOdukRef[nTypeIndex], "businessType", -1, &childDataNameReftype);
		bson_destroy(&childDataNameReftype);

		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "returnType", BCON_INT32(tmpOneCircuit.m_eReturnType));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "waitToRestoreTime", BCON_INT32((int)tmpOneCircuit.m_shWaitToRestoreTime));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "holdOffTime", BCON_INT32((int)tmpOneCircuit.m_shHoldOffTime));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "protectMonitorType", BCON_INT32(tmpOneCircuit.m_eProtectMonitorType));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "protectMode", BCON_INT32((int)tmpOneCircuit.m_eProtectMode)); // 单向或双向
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "usedCir", BCON_INT32(tmpOneCircuit.m_iUsedCir));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "labelDiffRvsWithFwd", BCON_INT32(tmpOneCircuit.m_iLabelDiffRvsWithFwd));	
		strCurName = string_To_UTF8(tmpOneCircuit.m_sClientName);
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "ClientName", strCurName.c_str());
		strCurName = string_To_UTF8(tmpOneCircuit.m_sUserLabel);
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "userLabel", strCurName.c_str());
		strCurName = string_To_UTF8(tmpOneCircuit.m_sCircuitAlias); // 乱码
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "circuitAlias", BCON_UTF8(strCurName.c_str()));
		// vector<string>		m_vectReserve;
		// map<EExtendAttributeType, string> m_mapExtendAttribute;
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "tunnelRouteAdjustStatus", BCON_INT32(tmpOneCircuit.m_eEmTunnelRouteAdjustStatus));
		BCON_APPEND(m_pKeyDataOdukRef[nTypeIndex], "oduflexEncapType", BCON_INT32(tmpOneCircuit.m_eOduflexEncapType));

		/////////////////////////// 
		m_pKeyOdukRef[nTypeIndex] = BCON_NEW("_id", BCON_INT32(tmpOneCircuit.m_iId));	
		GetMongoBusinessLayerRelation(m_pKeyOdukRef[nTypeIndex], OT_CIRCUIT, tmpOneCircuit.m_eServiceLayer, tmpOneCircuit.m_iId);					

		bson_t childDataRouteRef;
		bson_init(&childDataRouteRef);
		BCON_APPEND(&childDataRouteRef, "$ref", strTABLE_PATH.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iId));					
		bson_append_document (m_pKeyOdukRef[nTypeIndex], "routeRef", -1, &childDataRouteRef);
		bson_destroy(&childDataRouteRef);

		bson_t childDataRef;
		bson_init(&childDataRef);
		BCON_APPEND(&childDataRef, "$ref", strTABLE_oduk_data.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iId));					
		bson_append_document (m_pKeyOdukRef[nTypeIndex], "dataRef", -1, &childDataRef);
		bson_destroy(&childDataRef);
	}
	else if(tmpOneCircuit.m_eServiceLayer == OTN_LAYER_CLIENT){// OTN_LAYER_CLIENT
		bIsOtnCircus = true;

		m_pKeyDataClientRef[nTypeIndex] = BCON_NEW("_id", BCON_INT32(tmpOneCircuit.m_iId));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "tableType", TABLE_CLIENT);
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "aperateMode", BCON_INT32(tmpOneCircuit.m_eOperMode));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "activeState", BCON_INT32(tmpOneCircuit.m_eState));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "brokenRepairStatus", BCON_INT32(tmpOneCircuit.m_eRepairStatus));
		//  XC_OBJ_BROKEN_REASON m_stBrokenReason;
		string strCurName = string_To_UTF8(tmpOneCircuit.m_sName);
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "name", strCurName.c_str());
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "createTime", BCON_INT64(tmpOneCircuit.m_tmCreateTime));
		strCurName = string_To_UTF8(tmpOneCircuit.m_sCreateUserName);
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "createUserName", strCurName.c_str());
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "modifyTime", BCON_INT64(tmpOneCircuit.m_tmModifyTime));
		strCurName = string_To_UTF8(tmpOneCircuit.m_sModifyUserName);
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "modifyUserName", strCurName.c_str());
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "circuitDirection", BCON_INT32(tmpOneCircuit.m_eDirection));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "netType", BCON_INT32(tmpOneCircuit.m_eNetType));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "connectionType", BCON_INT32(tmpOneCircuit.m_eConnectionType));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "switchStatus", BCON_INT32(tmpOneCircuit.m_eSwitchStatus));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "alarmLevel", BCON_INT32(tmpOneCircuit.m_eAlarmLevel));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "alarmMoniter", BCON_UTF8(tmpOneCircuit.m_eAlarmMoniter.c_str()));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "performanceMoniter", BCON_UTF8(tmpOneCircuit.m_ePerformanceMoniter.c_str()));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "srcPortRate", BCON_INT32(tmpOneCircuit.m_eSrcPortRate));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "dstPortRate", BCON_INT32(tmpOneCircuit.m_eDstPortRate));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "serviceLayer", BCON_INT32(tmpOneCircuit.m_eServiceLayer));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "bandWidthType", BCON_INT32(tmpOneCircuit.m_eBandWidthType));
		GetBandWidthStr(strCurName, tmpOneCircuit.m_eBandWidthType);
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "bandWidthTypeName", strCurName.c_str());

		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "concatenationType", BCON_INT32(tmpOneCircuit.m_eConcatenationType));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "protectType", BCON_INT32(tmpOneCircuit.m_eProtectType));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "serviceClass", BCON_INT32(tmpOneCircuit.m_eServiceClass));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "srcNeId", BCON_INT32(tmpOneCircuit.m_iNeId[0]));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "otnWave", strWaveName.c_str()); // //PTN的 Tunnel标签; //SDH的VC4Index //OCH电路的波长	

		bson_t childDataNameRef;
		bson_init(&childDataNameRef);
		BCON_APPEND(&childDataNameRef, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iNeId[0]));					
		bson_append_document (m_pKeyDataClientRef[nTypeIndex], "srcNameRef", -1, &childDataNameRef);
		bson_destroy(&childDataNameRef);

		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "dstNeId", BCON_INT32(tmpOneCircuit.m_iNeId[1]));	
		bson_t childDataNameRefdst;
		bson_init(&childDataNameRefdst);
		BCON_APPEND(&childDataNameRefdst, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iNeId[1]));					
		bson_append_document (m_pKeyDataClientRef[nTypeIndex], "dstNameRef", -1, &childDataNameRefdst);
		bson_destroy(&childDataNameRefdst);

		string strBussinessType ="BusinessType_";
		if(tmpOneCircuit.m_mapExtendAttribute.find(BUSINESS_TYPE) != tmpOneCircuit.m_mapExtendAttribute.end()){
			strBussinessType += tmpOneCircuit.m_mapExtendAttribute[BUSINESS_TYPE];
		}
		bson_t childDataNameReftype;
		bson_init(&childDataNameReftype);
		BCON_APPEND(&childDataNameReftype, "$ref", m_strCommonRefTable.c_str(), "$id", BCON_UTF8(strBussinessType.c_str()));					
		bson_append_document (m_pKeyDataClientRef[nTypeIndex], "businessType", -1, &childDataNameReftype);
		bson_destroy(&childDataNameReftype);

		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "returnType", BCON_INT32(tmpOneCircuit.m_eReturnType));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "waitToRestoreTime", BCON_INT32((int)tmpOneCircuit.m_shWaitToRestoreTime));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "holdOffTime", BCON_INT32((int)tmpOneCircuit.m_shHoldOffTime));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "protectMonitorType", BCON_INT32(tmpOneCircuit.m_eProtectMonitorType));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "protectMode", BCON_INT32((int)tmpOneCircuit.m_eProtectMode)); // 单向或双向
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "usedCir", BCON_INT32(tmpOneCircuit.m_iUsedCir));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "labelDiffRvsWithFwd", BCON_INT32(tmpOneCircuit.m_iLabelDiffRvsWithFwd));	
		strCurName = string_To_UTF8(tmpOneCircuit.m_sClientName);
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "ClientName", strCurName.c_str());
		strCurName = string_To_UTF8(tmpOneCircuit.m_sUserLabel);
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "userLabel", strCurName.c_str());
		strCurName = string_To_UTF8(tmpOneCircuit.m_sCircuitAlias); // 乱码
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "circuitAlias", BCON_UTF8(strCurName.c_str()));
		// vector<string>		m_vectReserve;
		// map<EExtendAttributeType, string> m_mapExtendAttribute;
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "tunnelRouteAdjustStatus", BCON_INT32(tmpOneCircuit.m_eEmTunnelRouteAdjustStatus));
		BCON_APPEND(m_pKeyDataClientRef[nTypeIndex], "oduflexEncapType", BCON_INT32(tmpOneCircuit.m_eOduflexEncapType));

		/////////////////////////// 
		m_pKeyClientRef[nTypeIndex] = BCON_NEW("_id", BCON_INT32(tmpOneCircuit.m_iId));	
		GetMongoBusinessLayerRelation(m_pKeyClientRef[nTypeIndex], OT_CIRCUIT, tmpOneCircuit.m_eServiceLayer, tmpOneCircuit.m_iId);					

		bson_t childDataRouteRef;
		bson_init(&childDataRouteRef);
		BCON_APPEND(&childDataRouteRef, "$ref", strTABLE_PATH.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iId));					
		bson_append_document (m_pKeyClientRef[nTypeIndex], "routeRef", -1, &childDataRouteRef);
		bson_destroy(&childDataRouteRef);

		bson_t childDataRef;
		bson_init(&childDataRef);
		BCON_APPEND(&childDataRef, "$ref", strTABLE_client_data.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iId));					
		bson_append_document (m_pKeyClientRef[nTypeIndex], "dataRef", -1, &childDataRef);
		bson_destroy(&childDataRef);
	}
	else if(tmpOneCircuit.m_eServiceLayer == OTN_LAYER_OMS){// OTN_LAYER_OCH

		m_pKeyDataOmsRef[nTypeIndex] = BCON_NEW("_id", BCON_INT32(tmpOneCircuit.m_iId));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "tableType", TABLE_OMS);
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "aperateMode", BCON_INT32(tmpOneCircuit.m_eOperMode));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "activeState", BCON_INT32(tmpOneCircuit.m_eState));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "brokenRepairStatus", BCON_INT32(tmpOneCircuit.m_eRepairStatus));
		//  XC_OBJ_BROKEN_REASON m_stBrokenReason;
		string strCurName = string_To_UTF8(tmpOneCircuit.m_sName);
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "name", strCurName.c_str());
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "createTime", BCON_INT64(tmpOneCircuit.m_tmCreateTime));
		strCurName = string_To_UTF8(tmpOneCircuit.m_sCreateUserName);
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "createUserName", strCurName.c_str());
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "modifyTime", BCON_INT64(tmpOneCircuit.m_tmModifyTime));
		strCurName = string_To_UTF8(tmpOneCircuit.m_sModifyUserName);
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "modifyUserName", strCurName.c_str());
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "circuitDirection", BCON_INT32(tmpOneCircuit.m_eDirection));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "netType", BCON_INT32(tmpOneCircuit.m_eNetType));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "connectionType", BCON_INT32(tmpOneCircuit.m_eConnectionType));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "switchStatus", BCON_INT32(tmpOneCircuit.m_eSwitchStatus));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "alarmLevel", BCON_INT32(tmpOneCircuit.m_eAlarmLevel));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "alarmMoniter", BCON_UTF8(tmpOneCircuit.m_eAlarmMoniter.c_str()));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "performanceMoniter", BCON_UTF8(tmpOneCircuit.m_ePerformanceMoniter.c_str()));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "srcPortRate", BCON_INT32(tmpOneCircuit.m_eSrcPortRate));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "dstPortRate", BCON_INT32(tmpOneCircuit.m_eDstPortRate));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "serviceLayer", BCON_INT32(tmpOneCircuit.m_eServiceLayer));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "bandWidthType", BCON_INT32(tmpOneCircuit.m_eBandWidthType));	
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "concatenationType", BCON_INT32(tmpOneCircuit.m_eConcatenationType));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "protectType", BCON_INT32(tmpOneCircuit.m_eProtectType));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "serviceClass", BCON_INT32(tmpOneCircuit.m_eServiceClass));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "srcNeId", BCON_INT32(tmpOneCircuit.m_iNeId[0]));

		bson_t childDataNameRef;
		bson_init(&childDataNameRef);
		BCON_APPEND(&childDataNameRef, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iNeId[0]));					
		bson_append_document (m_pKeyDataOmsRef[nTypeIndex], "srcNameRef", -1, &childDataNameRef);
		bson_destroy(&childDataNameRef);

		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "dstNeId", BCON_INT32(tmpOneCircuit.m_iNeId[1]));	
		bson_t childDataNameRefdst;
		bson_init(&childDataNameRefdst);
		BCON_APPEND(&childDataNameRefdst, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iNeId[1]));					
		bson_append_document (m_pKeyDataOmsRef[nTypeIndex], "dstNameRef", -1, &childDataNameRefdst);
		bson_destroy(&childDataNameRefdst);

		string strBussinessType ="BusinessType_";
		if(tmpOneCircuit.m_mapExtendAttribute.find(BUSINESS_TYPE) != tmpOneCircuit.m_mapExtendAttribute.end()){
			strBussinessType += tmpOneCircuit.m_mapExtendAttribute[BUSINESS_TYPE];
		}
		bson_t childDataNameReftype;
		bson_init(&childDataNameReftype);
		BCON_APPEND(&childDataNameReftype, "$ref", m_strCommonRefTable.c_str(), "$id", BCON_UTF8(strBussinessType.c_str()));					
		bson_append_document (m_pKeyDataOmsRef[nTypeIndex], "businessType", -1, &childDataNameReftype);
		bson_destroy(&childDataNameReftype);

		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "returnType", BCON_INT32(tmpOneCircuit.m_eReturnType));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "waitToRestoreTime", BCON_INT32((int)tmpOneCircuit.m_shWaitToRestoreTime));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "holdOffTime", BCON_INT32((int)tmpOneCircuit.m_shHoldOffTime));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "protectMonitorType", BCON_INT32(tmpOneCircuit.m_eProtectMonitorType));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "protectMode", BCON_INT32((int)tmpOneCircuit.m_eProtectMode)); // 单向或双向
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "usedCir", BCON_INT32(tmpOneCircuit.m_iUsedCir));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "labelDiffRvsWithFwd", BCON_INT32(tmpOneCircuit.m_iLabelDiffRvsWithFwd));	
		strCurName = string_To_UTF8(tmpOneCircuit.m_sClientName);
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "ClientName", strCurName.c_str());
		strCurName = string_To_UTF8(tmpOneCircuit.m_sUserLabel);
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "userLabel", strCurName.c_str());
		strCurName = string_To_UTF8(tmpOneCircuit.m_sCircuitAlias); // 乱码
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "circuitAlias", BCON_UTF8(strCurName.c_str()));
		// vector<string>		m_vectReserve;
		// map<EExtendAttributeType, string> m_mapExtendAttribute;
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "tunnelRouteAdjustStatus", BCON_INT32(tmpOneCircuit.m_eEmTunnelRouteAdjustStatus));
		BCON_APPEND(m_pKeyDataOmsRef[nTypeIndex], "oduflexEncapType", BCON_INT32(tmpOneCircuit.m_eOduflexEncapType));

		///////////////////////////
		m_pKeyOmsRef[nTypeIndex] = BCON_NEW("_id", BCON_INT32(tmpOneCircuit.m_iId));	
		GetMongoBusinessLayerRelation(m_pKeyOmsRef[nTypeIndex], OT_CIRCUIT, tmpOneCircuit.m_eServiceLayer, tmpOneCircuit.m_iId);					

		bson_t childDataRouteRef;
		bson_init(&childDataRouteRef);
		BCON_APPEND(&childDataRouteRef, "$ref", strTABLE_PATH.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iId));					
		bson_append_document (m_pKeyOmsRef[nTypeIndex], "routeRef", -1, &childDataRouteRef);
		bson_destroy(&childDataRouteRef);

		bson_t childDataRef;
		bson_init(&childDataRef);
		BCON_APPEND(&childDataRef, "$ref", strTABLE_Och_data.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iId));					
		bson_append_document (m_pKeyOmsRef[nTypeIndex], "dataRef", -1, &childDataRef);
		bson_destroy(&childDataRef);
	}
	else if(tmpOneCircuit.m_eServiceLayer == OTN_LAYER_OTS){// OTN_LAYER_OCH

		m_pKeyDataOTSRef[nTypeIndex] = BCON_NEW("_id", BCON_INT32(tmpOneCircuit.m_iId));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "tableType", TABLE_OTS);
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "aperateMode", BCON_INT32(tmpOneCircuit.m_eOperMode));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "activeState", BCON_INT32(tmpOneCircuit.m_eState));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "brokenRepairStatus", BCON_INT32(tmpOneCircuit.m_eRepairStatus));
		//  XC_OBJ_BROKEN_REASON m_stBrokenReason;
		string strCurName = string_To_UTF8(tmpOneCircuit.m_sName);
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "name", strCurName.c_str());
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "createTime", BCON_INT64(tmpOneCircuit.m_tmCreateTime));
		strCurName = string_To_UTF8(tmpOneCircuit.m_sCreateUserName);
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "createUserName", strCurName.c_str());
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "modifyTime", BCON_INT64(tmpOneCircuit.m_tmModifyTime));
		strCurName = string_To_UTF8(tmpOneCircuit.m_sModifyUserName);
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "modifyUserName", strCurName.c_str());
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "circuitDirection", BCON_INT32(tmpOneCircuit.m_eDirection));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "netType", BCON_INT32(tmpOneCircuit.m_eNetType));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "connectionType", BCON_INT32(tmpOneCircuit.m_eConnectionType));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "switchStatus", BCON_INT32(tmpOneCircuit.m_eSwitchStatus));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "alarmLevel", BCON_INT32(tmpOneCircuit.m_eAlarmLevel));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "alarmMoniter", BCON_UTF8(tmpOneCircuit.m_eAlarmMoniter.c_str()));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "performanceMoniter", BCON_UTF8(tmpOneCircuit.m_ePerformanceMoniter.c_str()));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "srcPortRate", BCON_INT32(tmpOneCircuit.m_eSrcPortRate));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "dstPortRate", BCON_INT32(tmpOneCircuit.m_eDstPortRate));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "serviceLayer", BCON_INT32(tmpOneCircuit.m_eServiceLayer));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "bandWidthType", BCON_INT32(tmpOneCircuit.m_eBandWidthType));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "concatenationType", BCON_INT32(tmpOneCircuit.m_eConcatenationType));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "protectType", BCON_INT32(tmpOneCircuit.m_eProtectType));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "serviceClass", BCON_INT32(tmpOneCircuit.m_eServiceClass));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "srcNeId", BCON_INT32(tmpOneCircuit.m_iNeId[0]));

		bson_t childDataNameRef;
		bson_init(&childDataNameRef);
		BCON_APPEND(&childDataNameRef, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iNeId[0]));					
		bson_append_document (m_pKeyDataOTSRef[nTypeIndex], "srcNameRef", -1, &childDataNameRef);
		bson_destroy(&childDataNameRef);

		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "dstNeId", BCON_INT32(tmpOneCircuit.m_iNeId[1]));	
		bson_t childDataNameRefdst;
		bson_init(&childDataNameRefdst);
		BCON_APPEND(&childDataNameRefdst, "$ref", strNeNameRef.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iNeId[1]));					
		bson_append_document (m_pKeyDataOTSRef[nTypeIndex], "dstNameRef", -1, &childDataNameRefdst);
		bson_destroy(&childDataNameRefdst);

		string strBussinessType ="BusinessType_";
		if(tmpOneCircuit.m_mapExtendAttribute.find(BUSINESS_TYPE) != tmpOneCircuit.m_mapExtendAttribute.end()){
			strBussinessType += tmpOneCircuit.m_mapExtendAttribute[BUSINESS_TYPE];
		}
		bson_t childDataNameReftype;
		bson_init(&childDataNameReftype);
		BCON_APPEND(&childDataNameReftype, "$ref", m_strCommonRefTable.c_str(), "$id", BCON_UTF8(strBussinessType.c_str()));					
		bson_append_document (m_pKeyDataOTSRef[nTypeIndex], "businessType", -1, &childDataNameReftype);
		bson_destroy(&childDataNameReftype);

		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "returnType", BCON_INT32(tmpOneCircuit.m_eReturnType));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "waitToRestoreTime", BCON_INT32((int)tmpOneCircuit.m_shWaitToRestoreTime));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "holdOffTime", BCON_INT32((int)tmpOneCircuit.m_shHoldOffTime));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "protectMonitorType", BCON_INT32(tmpOneCircuit.m_eProtectMonitorType));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "protectMode", BCON_INT32((int)tmpOneCircuit.m_eProtectMode)); // 单向或双向
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "usedCir", BCON_INT32(tmpOneCircuit.m_iUsedCir));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "labelDiffRvsWithFwd", BCON_INT32(tmpOneCircuit.m_iLabelDiffRvsWithFwd));	
		strCurName = string_To_UTF8(tmpOneCircuit.m_sClientName);
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "ClientName", strCurName.c_str());
		strCurName = string_To_UTF8(tmpOneCircuit.m_sUserLabel);
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "userLabel", strCurName.c_str());
		strCurName = string_To_UTF8(tmpOneCircuit.m_sCircuitAlias); // 乱码
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "circuitAlias", BCON_UTF8(strCurName.c_str()));
		// vector<string>		m_vectReserve;
		// map<EExtendAttributeType, string> m_mapExtendAttribute;
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "tunnelRouteAdjustStatus", BCON_INT32(tmpOneCircuit.m_eEmTunnelRouteAdjustStatus));
		BCON_APPEND(m_pKeyDataOTSRef[nTypeIndex], "oduflexEncapType", BCON_INT32(tmpOneCircuit.m_eOduflexEncapType));

		/////////////////////////// 
		m_pKeyOTSRef[nTypeIndex] = BCON_NEW("_id", BCON_INT32(tmpOneCircuit.m_iId));	
		GetMongoBusinessLayerRelation(m_pKeyOTSRef[nTypeIndex], OT_CIRCUIT, tmpOneCircuit.m_eServiceLayer, tmpOneCircuit.m_iId);					

		bson_t childDataRouteRef;
		bson_init(&childDataRouteRef);
		BCON_APPEND(&childDataRouteRef, "$ref", strTABLE_PATH.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iId));					
		bson_append_document (m_pKeyOTSRef[nTypeIndex], "routeRef", -1, &childDataRouteRef);
		bson_destroy(&childDataRouteRef);

		bson_t childDataRef;
		bson_init(&childDataRef);
		BCON_APPEND(&childDataRef, "$ref", strTABLE_Och_data.c_str(), "$id", BCON_INT32(tmpOneCircuit.m_iId));					
		bson_append_document (m_pKeyOTSRef[nTypeIndex], "dataRef", -1, &childDataRef);
		bson_destroy(&childDataRef);
	}
}

bool OTNM2000GetNeconfigService::IfAddReCntCircusPath(XC_PATH &tmpPath){

	int i = 0;
	for(; i < tmpPath.m_oForwardRoute.size(); ++i){

		XC_CROSS_ITEM &tmpWorkRoute=tmpPath.m_oForwardRoute[i];
		if (tmpWorkRoute.m_iNodeId > 500000000){
			return true;
		}
	}
	for(i=0; i < tmpPath.m_oReverseRoute.size(); ++i){

		XC_CROSS_ITEM &tmpWorkRoute=tmpPath.m_oReverseRoute[i];
		if (tmpWorkRoute.m_iNodeId > 500000000){
			return true;
		}
	}

	return false;
}


bool OTNM2000GetNeconfigService::IfAddReCntCircusToMap(XC_CIRCUIT &srcTunnelCircuits)
{
	if((srcTunnelCircuits.m_eServiceLayer == PTN_LAYER_TMC) // PW层
		|| (srcTunnelCircuits.m_eServiceLayer == OTN_LAYER_ODUK))
	{		
		int jz=0;
		for (;jz<(int)srcTunnelCircuits.m_vectWorkPath.size();jz++){

			XC_PATH &tmpPath = srcTunnelCircuits.m_vectWorkPath[jz];
			if(IfAddReCntCircusPath(tmpPath)){
				mapCircusNeedReCntPath[srcTunnelCircuits.m_iId] = srcTunnelCircuits;
				return true;
			}
		}

		for (jz=0;jz<(int)srcTunnelCircuits.m_vectProtectPath.size();jz++){

			XC_PATH &tmpPath = srcTunnelCircuits.m_vectProtectPath[jz];
			if(IfAddReCntCircusPath(tmpPath)){
				mapCircusNeedReCntPath[srcTunnelCircuits.m_iId] = srcTunnelCircuits;
				return true;
			}
		}
	}
	else if(srcTunnelCircuits.m_eServiceLayer == OTN_LAYER_CLIENT)
	{
		int jz=0;
		for (;jz<(int)srcTunnelCircuits.m_vectWorkPath.size();jz++){

			XC_PATH &tmpPath = srcTunnelCircuits.m_vectWorkPath[jz];
			if(IfAddReCntCircusPath(tmpPath)){
				mapCircusNeedReCntPathClient[srcTunnelCircuits.m_iId] = srcTunnelCircuits;
				return true;
			}
		}

		for (jz=0;jz<(int)srcTunnelCircuits.m_vectProtectPath.size();jz++){

			XC_PATH &tmpPath = srcTunnelCircuits.m_vectProtectPath[jz];
			if(IfAddReCntCircusPath(tmpPath)){
				mapCircusNeedReCntPathClient[srcTunnelCircuits.m_iId] = srcTunnelCircuits;
				return true;
			}
		}
	}
	else if(srcTunnelCircuits.m_eServiceLayer == OTN_LAYER_OCH)  //=>oms;
	{
		int jz=0;
		for (;jz<(int)srcTunnelCircuits.m_vectWorkPath.size();jz++){

			XC_PATH &tmpPath = srcTunnelCircuits.m_vectWorkPath[jz];
			if(IfAddReCntCircusPath(tmpPath)){
				mapCircusNeedReCntOchPath[srcTunnelCircuits.m_iId] = srcTunnelCircuits;
				return true;
			}
		}

		for (jz=0;jz<(int)srcTunnelCircuits.m_vectProtectPath.size();jz++){

			XC_PATH &tmpPath = srcTunnelCircuits.m_vectProtectPath[jz];
			if(IfAddReCntCircusPath(tmpPath)){
				mapCircusNeedReCntOchPath[srcTunnelCircuits.m_iId] = srcTunnelCircuits;
				return true;
			}
		}
	}
	else if(srcTunnelCircuits.m_eServiceLayer == OTN_LAYER_OMS)  //=>oms;
	{
		int jz=0;
		for (;jz<(int)srcTunnelCircuits.m_vectWorkPath.size();jz++){

			XC_PATH &tmpPath = srcTunnelCircuits.m_vectWorkPath[jz];
			if(IfAddReCntCircusPath(tmpPath)){
				mapCircusNeedReCntOmsPath[srcTunnelCircuits.m_iId] = srcTunnelCircuits;
				return true;
			}
		}

		for (jz=0;jz<(int)srcTunnelCircuits.m_vectProtectPath.size();jz++){

			XC_PATH &tmpPath = srcTunnelCircuits.m_vectProtectPath[jz];
			if(IfAddReCntCircusPath(tmpPath)){
				mapCircusNeedReCntOmsPath[srcTunnelCircuits.m_iId] = srcTunnelCircuits;
				return true;
			}
		}
	}

	return false;
}

void OTNM2000GetNeconfigService::AddPathToMongoTable(XC_CIRCUIT &srcTunnelCircuits, int nIndex, string &strWaveName, int &nFirstLabel)
{
	if((nIndex%50) == 0){// 防止太卡，进度不能及时写入；  
		char bufIndex[256] = "";
		sprintf(bufIndex, "CircuitProgess:%.3f, Circuit index:%d; rand:%d\n", m_fCircuitProgess, nIndex, rand());
		UpdateTaskID(m_fCircuitProgess, bufIndex);
	}

	m_pKey[nIndex] = BCON_NEW("_id", BCON_INT32(srcTunnelCircuits.m_iId));
	string strCurName = string_To_UTF8(srcTunnelCircuits.m_sName);
	BCON_APPEND(m_pKey[nIndex], "routeName", strCurName.c_str());
	BCON_APPEND(m_pKey[nIndex], "tableType", TABLE_PATH);

	int jz;
	char buf[10]="";
	bson_t childWorkPath;
	bson_init(&childWorkPath);
	for (jz=0;jz<(int)srcTunnelCircuits.m_vectWorkPath.size();jz++){// 只有1条；

		if (g_bStopMongoDBTheard){
			break;
		}

		XC_PATH &tmpPath = srcTunnelCircuits.m_vectWorkPath[jz];

		if (tmpPath.m_oForwardRoute.size() > 0){

			bson_t childArrayForRoute;
			bson_init(&childArrayForRoute);	
			SetRouteIDRefTable(&childArrayForRoute, tmpPath.m_iId,tmpPath.m_oForwardRoute, 0,0, strWaveName, nFirstLabel, true);
			itoa(jz,buf, 10);
			bson_append_document(&childWorkPath, buf, -1, &childArrayForRoute);
			bson_destroy(&childArrayForRoute);
		}
		if (tmpPath.m_oReverseRoute.size() > 0){

			bson_t childArrayRevRoute;
			bson_init(&childArrayRevRoute);
			SetRouteIDRefTable(&childArrayRevRoute, tmpPath.m_iId,tmpPath.m_oReverseRoute, 0,1, strWaveName, nFirstLabel);
			itoa(jz,buf, 10);
			bson_append_document(&childWorkPath, buf, -1, &childArrayRevRoute);
			bson_destroy(&childArrayRevRoute);
		}
	}
	if (srcTunnelCircuits.m_vectWorkPath.size() >=1 ){
		bson_append_array(m_pKey[nIndex], "workPath", -1, &childWorkPath);
	}
	bson_destroy(&childWorkPath);

	bson_t childProtectPath;
	bson_init(&childProtectPath);
	for (jz=0;jz<(int)srcTunnelCircuits.m_vectProtectPath.size();jz++){// 只有1条；

		if (g_bStopMongoDBTheard){
			break;
		}

		XC_PATH &tmpPath = srcTunnelCircuits.m_vectProtectPath[jz];	
		if (tmpPath.m_oForwardRoute.size() > 0){

			bson_t childArrayForRoute;
			bson_init(&childArrayForRoute);
			SetRouteIDRefTable(&childArrayForRoute, tmpPath.m_iId,tmpPath.m_oForwardRoute, 1,0, strWaveName, nFirstLabel);
			itoa(jz,buf, 10);
			bson_append_document(&childProtectPath, buf, -1, &childArrayForRoute);
			bson_destroy(&childArrayForRoute);
		}
		if (tmpPath.m_oReverseRoute.size() > 0){

			bson_t childArrayRevRoute;
			bson_init(&childArrayRevRoute);
			SetRouteIDRefTable(&childArrayRevRoute, tmpPath.m_iId,tmpPath.m_oReverseRoute, 1, 1, strWaveName, nFirstLabel);
			itoa(jz,buf, 10);
			bson_append_document(&childProtectPath, buf, -1, &childArrayRevRoute);
			bson_destroy(&childArrayRevRoute);
		}
	}
	if (srcTunnelCircuits.m_vectProtectPath.size() >= 1){
		bson_append_array(m_pKey[nIndex], "protectPath", -1, &childProtectPath);
	}
	bson_destroy(&childProtectPath);
}



int OTNM2000GetNeconfigService::ConnectNetClient(int nTimes, const std::string &strLogDir)
{
	MutiServPlatform::DeInitMSMPClient();

	HSESSION hSession = -1;
	ERROR_CODE_EX eCode = 0;

	MutiServPlatform::SESSION_INFO stInfo;
	stInfo.m_sUserName = strSrvUsr; // 默认是"admin"；
	stInfo.m_sPassword = strSrvPassword; // 默认是"admin"；

	int i = 0;
	for (; i < nTimes; ++i){
		eCode = MutiServPlatform::InitMSMPClient(strLogDir, 5, strSrvIP, nSrvPort);
		if (ERR_OK == eCode.iCode){
			break;
		}
		else{
			if ((nTimes-1)>i){
				Sleep(10);
			}
		}
	}
	if (nTimes == i){
		return -1;
	}

	eCode = MutiServPlatform::SNC_OpenSession(stInfo, hSession);
	if (ERR_OK != eCode.iCode){
		MutiServPlatform::DeInitMSMPClient();

		char bufResult[256]="";
		sprintf(bufResult, "MutiServPlatform::SNC_OpenSession: errorCode=%d", eCode.iCode);
		WriteLog(bufResult);
		return -2;
	}

	m_hSess = hSession;
	return 0;
}

int OTNM2000GetNeconfigService::GetAllCircuitsSetToMongoDB(double fBegin, double fAdd,const std::string &strLogDir){

	try{
		mapFromRinglIDGetTunnel.clear(); // 环绑定中勾选的信息；
		mapCircusNeedReCntPathClient.clear(); // client;
		mapCircusNeedReCntPath.clear(); // pw和oduk;
		mapCircusNeedReCntOchPath.clear();
		mapCircusNeedReCntOmsPath.clear();

		if (g_bStopMongoDBTheard){
			WriteLog("GetAllCircuitsSetToMongoDB StopMongoDBTheard");
			return 0;
		}

		string strDetail = "";
		m_fCircuitProgess = 0;
		char bufProgess[200]="";
		int i = 0, iStart,iEnd, nAllSrcNum,ik,nTmpBegin,j;
		int nMaxCircuitPice = g_nOneTimeMaxDataCnt; //长度太多，可能会超时；太少，取数据慢;
		vector<int> vectCircuitId;
		vector<XC_CIRCUIT> vectSnapshot;
		ERROR_CODE_EX eCode = 0;
		FuncCallToDB pFun = DealThreadeCircuitsFunction;

		///// 登录获取session;
		ERROR_CODE iRet = ConnectNetClient(1, strLogDir);// 登陆的账号，密码可能是无效的。
		if (iRet == -1){
			char bufLog[512]="";
			sprintf(bufLog, "GetAllCircuitsSetToMongoDB InitMSMPClient Failure\n");
			WriteLog(bufLog);

			strCloseLog += "GetAllCircuitsSetToMongoDB InitMSMPClient Failure\n";	
			goto endLast;
		}
		else if (iRet == -2){
			char bufLog[512]="";
			sprintf(bufLog, "GetAllCircuitsSetToMongoDB Opensession Failure\n");
			WriteLog(bufLog);

			strCloseLog += "GetAllCircuitsSetToMongoDB Opensession Failure\n";	
			goto endInitClient;
		} 

		iRet = SNC_GetCircuitSnapshot(m_hSess, vectCircuitId, vectSnapshot);
		if (ERR_OK != iRet){
			WriteLog("GetMutiCircuits Snap shot fail!");
			strCloseLog += "\nSNC_GetCircuitSnapshot Get Null data!\n";		
			goto endCloseSession;
		}

		//##############
		mapTotalCount[neCircuits].nTotalLen = vectCircuitId.size();
		//################

		printf("CircuitID size:%d\n", vectCircuitId.size());
		char bufLog[512]="";			
		sprintf(bufLog, "CircuitID size:%d\n", vectCircuitId.size());
		WriteLog(bufLog);
		//批量取一次
		if (vectCircuitId.size() > nMaxCircuitPice){
			int iStep = vectCircuitId.size() / nMaxCircuitPice + 1;
			for (i = 0; i < iStep; ++i){

				if (g_bStopMongoDBTheard){
					break;
				}

				/*if (i!=0 && ((i%(iStep/50+1))==0))*/{// 加快进度，防止进度不及时更新；
					m_fCircuitProgess = (double)i/iStep*fAdd+fBegin;
					sprintf(bufProgess, "Circuit Progess:%f", m_fCircuitProgess);
					strDetail = bufProgess;
					UpdateTaskID(m_fCircuitProgess, strDetail);
				}

				vector<XC_CIRCUIT> vecCircuits;
				vector<int> vectIds;
				iStart = i * nMaxCircuitPice;
				iEnd = (i + 1) * nMaxCircuitPice;
				if (i == iStep - 1){
					iEnd = vectCircuitId.size();
				}
				vectIds.insert(vectIds.end(), vectCircuitId.begin() + iStart, vectCircuitId.begin() + iEnd);

				//	int nS = clock();
				iRet = SNC_GetMutiCircuits(m_hSess, vectIds, vecCircuits); // 远程获取到的数据
				if (vectIds.size() != vecCircuits.size()){
					//		bIfTableUpdateRight = false;// 版本不匹配或？原因时，取出的数据会缺少，这时任务结束后进度设置为-1。 
					//		g_bStopMongoDBTheard = true;  // 如果有数据缺少，则中断此次任务 ；
					WriteLog("SNC_GetMutiCircuits get data: lost data!");
				}
		
				if (ERR_OK != iRet){// 一次50s左右,本机30s
					WriteLog("SNC_GetMutiCircuits fail!");	
					iRet = ConnectNetClient(1, strLogDir);
					if ((iRet == -1) || (iRet == -2)){
						WriteLog("SNC_GetMutiCircuits reconnect fail!");	
						continue;
					}
					iRet = SNC_GetMutiCircuits(m_hSess, vectIds, vecCircuits); // 远程获取到的数据
					if (ERR_OK != iRet){
						WriteLog("SNC_GetMutiCircuits reGet fail!");	

						//	strCloseLog += "SNC_GetMutiCircuits reGet Null data!\n";		
						continue;
					}
				}
				//	int nE=clock();
				//	printf("GetAllCircuitsSetToMongoDB:%.3f; Step:%d/%d\n", (double)(nE-nS)/1000, i, iStep);

				nAllSrcNum = vecCircuits.size();
				ik=0;	
				for (j=0; j<nAllSrcNum; ++j){
					if (g_bStopMongoDBTheard){
						goto endCloseSession;
					}

					if(IfAddReCntCircusToMap(vecCircuits[j])){
						continue;
					}

					if (ik == (nDealArrayThreadNum-1)) {

						if(vecCircuits[j].m_eServiceLayer == PTN_LAYER_TMP){// tunnel
							m_tmpThreadUseData[ik].eType = eTunnel;
						}
						else if(vecCircuits[j].m_eServiceLayer == PTN_LAYER_TMC){// pw
							m_tmpThreadUseData[ik].eType = ePw;				
						}
						else if(vecCircuits[j].m_eServiceLayer == OTN_LAYER_OTS){// 新增och;
							m_tmpThreadUseData[ik].eType = eOts;
						}
						else if(vecCircuits[j].m_eServiceLayer == OTN_LAYER_OMS){// 新增och;
							m_tmpThreadUseData[ik].eType = eOms;
						}
						else if(vecCircuits[j].m_eServiceLayer == OTN_LAYER_OCH){// 新增och;
							m_tmpThreadUseData[ik].eType = eOch;
						}
						else if(vecCircuits[j].m_eServiceLayer == OTN_LAYER_CLIENT){// 新增och;
							m_tmpThreadUseData[ik].eType = eClient;
						}
						else if(vecCircuits[j].m_eServiceLayer == OTN_LAYER_ODUK){// 新增och;
							m_tmpThreadUseData[ik].eType = eOduk;
						}
						else {
							m_tmpThreadUseData[ik].eType = eCircuits_other;

							char bufOther[50]="";
							sprintf(bufOther, "otherType circusID:%d\n", vecCircuits[j].m_iId);
							WriteLog(bufOther); // 打印没有写入mongo的其他类型的电路id；
						}
						m_tmpThreadUseData[ik].Data = &vecCircuits[j];
						ThreadReladySetCircusToMongoDB(nDealArrayThreadNum, pFun);									
						ik=0;			
					}				
					else{
						if(vecCircuits[j].m_eServiceLayer == PTN_LAYER_TMP){// tunnel
							m_tmpThreadUseData[ik].eType = eTunnel;
						}
						else if(vecCircuits[j].m_eServiceLayer == PTN_LAYER_TMC){// pw
							m_tmpThreadUseData[ik].eType = ePw;
						}
						else if(vecCircuits[j].m_eServiceLayer == OTN_LAYER_OTS){// 新增och;
							m_tmpThreadUseData[ik].eType = eOts;
						}
						else if(vecCircuits[j].m_eServiceLayer == OTN_LAYER_OMS){// 新增och;
							m_tmpThreadUseData[ik].eType = eOms;
						}
						else if(vecCircuits[j].m_eServiceLayer == OTN_LAYER_OCH){// 新增och;
							m_tmpThreadUseData[ik].eType = eOch;
						}
						else if(vecCircuits[j].m_eServiceLayer == OTN_LAYER_CLIENT){// 新增och;
							m_tmpThreadUseData[ik].eType = eClient;
						}
						else if(vecCircuits[j].m_eServiceLayer == OTN_LAYER_ODUK){// 新增och;
							m_tmpThreadUseData[ik].eType = eOduk;
						}
						else {
							m_tmpThreadUseData[ik].eType = eCircuits_other;

							char bufOther[50]="";
							sprintf(bufOther, "otherType circusID:%d\n", vecCircuits[j].m_iId);
							WriteLog(bufOther);
						}
						m_tmpThreadUseData[ik].Data = &vecCircuits[j];
						++ik;
					}	
				}

				ThreadReladySetCircusToMongoDB(ik, pFun);									
			}
		}
		else{			
			//	int nS=clock();
			vector<XC_CIRCUIT> vecOldCirt;
			eCode = SNC_GetAllCircuits(m_hSess, vecOldCirt);
			if (ERR_OK != eCode){
				WriteLog("GetAllCircuits fail!");

				strCloseLog += "SNC_GetAllCircuits Get Null data!\n";		

				goto endCloseSession;
			}
			//	int nE=clock();
			//	printf("GetAllCircuitsSetToMongoDB:%.3f;\n", (double)(nE-nS)/1000);

			int nAllCiruit = vecOldCirt.size();  // <= 5000;
			ik=0;	
			for (j = 0; j < nAllCiruit; ++j){
				if (g_bStopMongoDBTheard){
					goto endCloseSession;
				}

				if (j!=0 && (j%(nAllCiruit/100+1)==0)){
					//	UpdateTaskID((double)j/nAllCiruit*fAdd+fBegin);

					m_fCircuitProgess = (double)j/nAllCiruit*fAdd+fBegin;
					sprintf(bufProgess, "Circuit Progess:%f", m_fCircuitProgess);
					strDetail = bufProgess;
					UpdateTaskID(m_fCircuitProgess, strDetail);
				}

				if(IfAddReCntCircusToMap(vecOldCirt[j])){
					continue;
				}

				if (ik == (nDealArrayThreadNum-1)) {

					if(vecOldCirt[j].m_eServiceLayer == PTN_LAYER_TMP){// tunnel
						m_tmpThreadUseData[ik].eType = eTunnel;
					}
					else if(vecOldCirt[j].m_eServiceLayer == PTN_LAYER_TMC){// pw
						m_tmpThreadUseData[ik].eType = ePw;
					}
					else if(vecOldCirt[j].m_eServiceLayer == OTN_LAYER_OTS){// 新增och;
						m_tmpThreadUseData[ik].eType = eOts;
					}
					else if(vecOldCirt[j].m_eServiceLayer == OTN_LAYER_OMS){// 新增och;
						m_tmpThreadUseData[ik].eType = eOms;
					}
					else if(vecOldCirt[j].m_eServiceLayer == OTN_LAYER_OCH){// 新增och;
						m_tmpThreadUseData[ik].eType = eOch;
					}
					else if(vecOldCirt[j].m_eServiceLayer == OTN_LAYER_CLIENT){// 新增och;
						m_tmpThreadUseData[ik].eType = eClient;
					}
					else if(vecOldCirt[j].m_eServiceLayer == OTN_LAYER_ODUK){// 新增och;
						m_tmpThreadUseData[ik].eType = eOduk;				
					}
					else {
						m_tmpThreadUseData[ik].eType = eCircuits_other;
					}
					m_tmpThreadUseData[ik].Data = &vecOldCirt[j];
					ThreadReladySetCircusToMongoDB(nDealArrayThreadNum, pFun);									
					ik=0;
				}			
				else{
					if(vecOldCirt[j].m_eServiceLayer == PTN_LAYER_TMP){// tunnel
						m_tmpThreadUseData[ik].eType = eTunnel;
					}
					else if(vecOldCirt[j].m_eServiceLayer == PTN_LAYER_TMC){// pw
						m_tmpThreadUseData[ik].eType = ePw;
					}
					else if(vecOldCirt[j].m_eServiceLayer == OTN_LAYER_OTS){// 新增och;
						m_tmpThreadUseData[ik].eType = eOts;
					}
					else if(vecOldCirt[j].m_eServiceLayer == OTN_LAYER_OMS){// 新增och;
						m_tmpThreadUseData[ik].eType = eOms;
					}
					else if(vecOldCirt[j].m_eServiceLayer == OTN_LAYER_OCH){// 新增och;
						m_tmpThreadUseData[ik].eType = eOch;
					}
					else if(vecOldCirt[j].m_eServiceLayer == OTN_LAYER_CLIENT){// 新增och;
						m_tmpThreadUseData[ik].eType = eClient;
					}
					else if(vecOldCirt[j].m_eServiceLayer == OTN_LAYER_ODUK){// 新增och;
						m_tmpThreadUseData[ik].eType = eOduk;
					}
					else {
						m_tmpThreadUseData[ik].eType = eCircuits_other;
					}
					m_tmpThreadUseData[ik].Data = &vecOldCirt[j];
					++ik;
				}	
			}
			ThreadReladySetCircusToMongoDB(ik, pFun);
		}

		/////// ===>  client-oduk-och-oms-ots
		// oms:	
		strDetail = "circus begin oms";
		UpdateTaskID(0.90*(fBegin+fAdd), strDetail);

		j = 0, ik=0;
		int nAllCiruit = mapCircusNeedReCntOmsPath.size();
		for (map<int, XC_CIRCUIT>::iterator iter = mapCircusNeedReCntOmsPath.begin(); iter != mapCircusNeedReCntOmsPath.end(); iter++, j++)
		{
			if (g_bStopMongoDBTheard){
				goto endCloseSession;
			}
			XC_CIRCUIT &tmpReCnt = iter->second;

			if ((j%900) == 0){
				m_fCircuitProgess = (double)j/nAllCiruit*0.02 + 0.90*(fBegin+fAdd);
				sprintf(bufProgess, "circus begin oms Progess:%f", m_fCircuitProgess);
				strDetail = bufProgess;
				UpdateTaskID(m_fCircuitProgess, strDetail);
			}

			if (ik == (nDealArrayThreadNum-1)) {

				if(tmpReCnt.m_eServiceLayer == OTN_LAYER_OMS){// pw
					m_tmpThreadUseData[ik].eType = eOms;
				}			
				else {
					m_tmpThreadUseData[ik].eType = eCircuits_other;
				}
				m_tmpThreadUseData[ik].Data = &tmpReCnt;
				ThreadReladySetCircusToMongoDB(nDealArrayThreadNum, pFun);									
				ik=0;
			}
			else{
				if(tmpReCnt.m_eServiceLayer == OTN_LAYER_OMS){// tunnel
					m_tmpThreadUseData[ik].eType = eOms;
				}				
				else {
					m_tmpThreadUseData[ik].eType = eCircuits_other;
				}
				m_tmpThreadUseData[ik].Data = &tmpReCnt;
				++ik;
			}	
		}
		ThreadReladySetCircusToMongoDB(ik, pFun);

		/////  och;
		strDetail = "circus begin och";
		UpdateTaskID(0.92*(fBegin+fAdd), strDetail);
		j = 0, ik=0;
		nAllCiruit = mapCircusNeedReCntOchPath.size();
		for (map<int, XC_CIRCUIT>::iterator iter = mapCircusNeedReCntOchPath.begin(); iter != mapCircusNeedReCntOchPath.end(); iter++, j++)
		{
			if (g_bStopMongoDBTheard){
				goto endCloseSession;
			}
			XC_CIRCUIT &tmpReCnt = iter->second;

			if ((j%900) == 0){
				m_fCircuitProgess = (double)j/nAllCiruit*0.02 + 0.92*(fBegin+fAdd);
				sprintf(bufProgess, "circus begin och Progess:%f", m_fCircuitProgess);
				strDetail = bufProgess;
				UpdateTaskID(m_fCircuitProgess, strDetail);
			}

			if (ik == (nDealArrayThreadNum-1)) {

				if(tmpReCnt.m_eServiceLayer == OTN_LAYER_OCH){// pw
					m_tmpThreadUseData[ik].eType = eOch;
				}			
				else {
					m_tmpThreadUseData[ik].eType = eCircuits_other;
				}
				m_tmpThreadUseData[ik].Data = &tmpReCnt;
				ThreadReladySetCircusToMongoDB(nDealArrayThreadNum, pFun);									
				ik=0;
			}
			else{
				if(tmpReCnt.m_eServiceLayer == OTN_LAYER_OCH){// tunnel
					m_tmpThreadUseData[ik].eType = eOch;
				}				
				else {
					m_tmpThreadUseData[ik].eType = eCircuits_other;
				}
				m_tmpThreadUseData[ik].Data = &tmpReCnt;
				++ik;
			}	
		}
		ThreadReladySetCircusToMongoDB(ik, pFun);

		//// 展开路由信息； => 从所有电路信息中，把需要展开的电路挑选出来，重新计算；
		strDetail = "circus begin pw or oduk";
		UpdateTaskID(0.94*(fBegin+fAdd), strDetail);
		j = 0, ik=0;  // pw/oduk;
		nAllCiruit = mapCircusNeedReCntPath.size();
		for (map<int, XC_CIRCUIT>::iterator iter = mapCircusNeedReCntPath.begin(); iter != mapCircusNeedReCntPath.end(); iter++, j++)
		{
			if (g_bStopMongoDBTheard){
				goto endCloseSession;
			}
			XC_CIRCUIT &tmpReCnt = iter->second;

			if ((j%900) == 0){
				m_fCircuitProgess = (double)j/nAllCiruit*0.02 + 0.94*(fBegin+fAdd);
				sprintf(bufProgess, "circus begin pw or oduk Progess:%f", m_fCircuitProgess);
				strDetail = bufProgess;
				UpdateTaskID(m_fCircuitProgess, strDetail);
			}

			if (ik == (nDealArrayThreadNum-1)) {

				if(tmpReCnt.m_eServiceLayer == PTN_LAYER_TMC){// pw
					m_tmpThreadUseData[ik].eType = ePw;
				}
				else if(tmpReCnt.m_eServiceLayer == OTN_LAYER_OCH){// 新增och;
					m_tmpThreadUseData[ik].eType = eOch;
				}
				else if(tmpReCnt.m_eServiceLayer == OTN_LAYER_CLIENT){// 新增och;
					m_tmpThreadUseData[ik].eType = eClient;
				}
				else if(tmpReCnt.m_eServiceLayer == OTN_LAYER_ODUK){// 新增och;
					m_tmpThreadUseData[ik].eType = eOduk;				
				}
				else {
					m_tmpThreadUseData[ik].eType = eCircuits_other;
				}
				m_tmpThreadUseData[ik].Data = &tmpReCnt;
				ThreadReladySetCircusToMongoDB(nDealArrayThreadNum, pFun);									
				ik=0;
			}
			else{
				if(tmpReCnt.m_eServiceLayer == PTN_LAYER_TMP){// tunnel
					m_tmpThreadUseData[ik].eType = eTunnel;
				}
				else if(tmpReCnt.m_eServiceLayer == PTN_LAYER_TMC){// pw
					m_tmpThreadUseData[ik].eType = ePw;
				}
				else if(tmpReCnt.m_eServiceLayer == OTN_LAYER_OCH){// 新增och;
					m_tmpThreadUseData[ik].eType = eOch;
				}
				else if(tmpReCnt.m_eServiceLayer == OTN_LAYER_CLIENT){// 新增och;
					m_tmpThreadUseData[ik].eType = eClient;
				}
				else if(tmpReCnt.m_eServiceLayer == OTN_LAYER_ODUK){// 新增och;
					m_tmpThreadUseData[ik].eType = eOduk;
				}
				else {
					m_tmpThreadUseData[ik].eType = eCircuits_other;
				}
				m_tmpThreadUseData[ik].Data = &tmpReCnt;
				++ik;
			}	
		}
		ThreadReladySetCircusToMongoDB(ik, pFun);								

		///// oclient 包含oduk;
		strDetail = "circus begin oclient";
		UpdateTaskID(0.96*(fBegin+fAdd), strDetail);
		j = 0, ik=0;
		nAllCiruit = mapCircusNeedReCntPathClient.size(); // oclient;
		for (map<int, XC_CIRCUIT>::iterator iter = mapCircusNeedReCntPathClient.begin(); iter != mapCircusNeedReCntPathClient.end(); iter++, j++)
		{
			if (g_bStopMongoDBTheard){
				goto endCloseSession;
			}
			XC_CIRCUIT &tmpReCnt = iter->second;

			if ((j%900) == 0){
				m_fCircuitProgess = (double)j/nAllCiruit*0.02 + 0.96*(fBegin+fAdd);
				sprintf(bufProgess, "circus begin oclient Progess:%f", m_fCircuitProgess);
				strDetail = bufProgess;
				UpdateTaskID(m_fCircuitProgess, strDetail);
			}

			if (ik == (nDealArrayThreadNum-1)) {

				if(tmpReCnt.m_eServiceLayer == PTN_LAYER_TMC){// pw
					m_tmpThreadUseData[ik].eType = ePw;
				}
				else if(tmpReCnt.m_eServiceLayer == OTN_LAYER_OCH){// 新增och;
					m_tmpThreadUseData[ik].eType = eOch;
				}
				else if(tmpReCnt.m_eServiceLayer == OTN_LAYER_CLIENT){// 新增och;
					m_tmpThreadUseData[ik].eType = eClient;
				}
				else if(tmpReCnt.m_eServiceLayer == OTN_LAYER_ODUK){// 新增och;
					m_tmpThreadUseData[ik].eType = eOduk;				
				}
				else {
					m_tmpThreadUseData[ik].eType = eCircuits_other;
				}
				m_tmpThreadUseData[ik].Data = &tmpReCnt;
				ThreadReladySetCircusToMongoDB(nDealArrayThreadNum, pFun);									
				ik=0;
			}
			else{
				if(tmpReCnt.m_eServiceLayer == PTN_LAYER_TMP){// tunnel
					m_tmpThreadUseData[ik].eType = eTunnel;
				}
				else if(tmpReCnt.m_eServiceLayer == PTN_LAYER_TMC){// pw
					m_tmpThreadUseData[ik].eType = ePw;
				}
				else if(tmpReCnt.m_eServiceLayer == OTN_LAYER_OCH){// 新增och;
					m_tmpThreadUseData[ik].eType = eOch;
				}
				else if(tmpReCnt.m_eServiceLayer == OTN_LAYER_CLIENT){// 新增och;
					m_tmpThreadUseData[ik].eType = eClient;
				}
				else if(tmpReCnt.m_eServiceLayer == OTN_LAYER_ODUK){// 新增och;
					m_tmpThreadUseData[ik].eType = eOduk;
				}
				else {
					m_tmpThreadUseData[ik].eType = eCircuits_other;
				}
				m_tmpThreadUseData[ik].Data = &tmpReCnt;
				++ik;
			}	
		}
		ThreadReladySetCircusToMongoDB(ik, pFun);

		SetRingMapToMongoDB();

endCloseSession:
		MutiServPlatform::SNC_CloseSession(m_hSess);

endInitClient:
		MutiServPlatform::DeInitMSMPClient();

endLast:
		mapCircusNeedReCntPath.clear();
		mapCircusNeedReCntPathClient.clear();
		mapCircusNeedReCntOchPath.clear();
		mapCircusNeedReCntOmsPath.clear();
	}
	catch(...){
		WriteLog("GetAllCircuitsSetToMongoDB catch error!");
	}

	return 0;
}

void OTNM2000GetNeconfigService::CloseInitMSMPClient()
{
	MutiServPlatform::SNC_CloseSession(m_hSess);
	MutiServPlatform::DeInitMSMPClient();
}


#if 1

//
char * OTNM2000GetNeconfigService::GetL2orL3Attr(int iType)
{
	switch (iType)
	{
	case 0:
		return "L2";
	case 1:
		return "L3";
	default:
		return "none";
	}
}
//
char * OTNM2000GetNeconfigService::GetLoadGroupingMode(int iType)
{
	switch (iType)
	{
	case 0:
		return "close";
	case 1:
		return "Manual_Load_Sharing";
	case 2:
		return "LACP_Static_Load_Sharing";
	case 3:
		return "LACP_Static_No_Load_Sharing";
	case 4:
		return "Manual_None_Load_Share";
	default:
		return "none";
	}
}
//
char * OTNM2000GetNeconfigService::GetLoadGroupingAlgorithm(int iType)
{
	switch (iType)
	{
	case 0:
		return "Close";
	case 1:
		return "DMAC";
	case 2:
		return "SMAC";
	case 3:
		return "Both_DMAC_SMAC";
	case 4:
		return "D_IP";
	case 5:
		return "S_IP";
	case 6:
		return "Both_D_IP_S_IP";
	default:
		return "none";
	}
}

// 取得lag接口配置
bool OTNM2000GetNeconfigService::GetLagInterfaceConfig(const std::string &strPipeName, int iNeId, bool bMongo)
{
	try{
		// TODO: 在此添加额外的初始化代码
#if NOT_LONG_CONNECT
		if (bIfNeedInit)
		{
			if (!neconfig::client::IsInitialize()){
				if (!neconfig::client::Initialize()){

					if (bMongo){				
						bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));
						BCON_APPEND(pKey, "errorCode", BCON_INT32(104));
#if DEFINE_MONGO_INSERT
						if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_lag.c_str(), pKey)){
							// log新增数据失败；					
							char bufLog[512]="";			
							sprintf(bufLog, "Insert lag 104 Failure:%d\n", iNeId);
							WriteLog(bufLog);
						}
#endif	
						bson_free (pKey);
					}
					else{
						OTNM2000PipeClient oPipeClient(strPipeName);
						char* pTempJson = "{\"errorCode\":\"104\"}";
						oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));	
					}

					return false;
				}
			}
		}
#endif

#if 1
		neconfig::CNeCmdInfo oNeCmd;
		oNeCmd.m_iUserId = -2;
		oNeCmd.m_iCmdId = neconfig::NECFG_CMD_QUERY_CONFIG;
		oNeCmd.m_iVer = 1;
		oNeCmd.m_iNeID = iNeId;
		oNeCmd.m_oLogInfo.m_byFlag = neconfig::ETYPE_NECMDLOG_NOLOG;

		int iNeType = irit::GetNeTypeOfNeFromBoardType(iNeId);
		if (irit::IsIPRAN8000Ne(iNeType))
		{
			R8000PARSE::CTrunk oTrunkBlock;
			DWORD dwRet  = neconfig::client::SyncReadBlockFromDB(oNeCmd, oTrunkBlock);
			if (0 == dwRet)
			{
				Json::Value rRoot;
				std::vector<R8000PARSE::CTrunk_Item>::iterator it = oTrunkBlock.m_arTrunk_Item.begin();
				int i = 1;
				char arItemName[50];
				if (it != oTrunkBlock.m_arTrunk_Item.end())
				{
					while (it != oTrunkBlock.m_arTrunk_Item.end())
					{
						Json::Value tempItemValue;
						if (it->m_wSubindex == 0){
							sprintf(arItemName, "lag%d\0", it->m_byLag_id);
						}
						else{
							int nSubIndex = it->m_wSubindex;
							sprintf(arItemName, "lag%d.%d\0", it->m_byLag_id,nSubIndex);
						}										
						tempItemValue["LagName"] = arItemName;

						//m_arMAC
						sprintf(arItemName, "%02X-%02X-%02X-%02X-%02X-%02X\0", 
							it->m_arMAC[0], it->m_arMAC[1], it->m_arMAC[2],
							it->m_arMAC[3], it->m_arMAC[4], it->m_arMAC[5]);
						tempItemValue["Mac"] = arItemName;
						//m_byL2L3
						tempItemValue["L2orL3Attr"] = GetL2orL3Attr(it->m_byL2L3);
						//m_byOperating_mode
						tempItemValue["LoadGroupingMode"] = GetLoadGroupingMode(it->m_byOperating_mode);
						//m_byHash_alg
						tempItemValue["LoadGroupingAlgorithm"] = GetLoadGroupingAlgorithm(it->m_byHash_alg);
						//
						int iPortIndex = 1;
						if (it->m_oMember_1.m_bySlot_no > 0)
						{
							sprintf(arItemName, "Slot%d/%d\0", it->m_oMember_1.m_bySlot_no, it->m_oMember_1.m_byPort_no);
							char arPortName[10];
							sprintf(arPortName, "PORT%d\0", iPortIndex);
							tempItemValue["ChoosedMemberInterface"][arPortName] = arItemName;
							iPortIndex++;
						}
						if (it->m_oMember_2.m_bySlot_no > 0)
						{
							sprintf(arItemName, "Slot%d/%d\0", it->m_oMember_2.m_bySlot_no, it->m_oMember_2.m_byPort_no);
							char arPortName[10];
							sprintf(arPortName, "PORT%d\0", iPortIndex);
							tempItemValue["ChoosedMemberInterface"][arPortName] = arItemName;
							iPortIndex++;
						}
						if (it->m_oMember_3.m_bySlot_no > 0)
						{
							sprintf(arItemName, "Slot%d/%d\0", it->m_oMember_3.m_bySlot_no, it->m_oMember_3.m_byPort_no);
							char arPortName[10];
							sprintf(arPortName, "PORT%d\0", iPortIndex);
							tempItemValue["ChoosedMemberInterface"][arPortName] = arItemName;
							iPortIndex++;
						}
						if (it->m_oMember_4.m_bySlot_no > 0)
						{
							sprintf(arItemName, "Slot%d/%d\0", it->m_oMember_4.m_bySlot_no, it->m_oMember_4.m_byPort_no);
							char arPortName[10];
							sprintf(arPortName, "PORT%d\0", iPortIndex);
							tempItemValue["ChoosedMemberInterface"][arPortName] = arItemName;
							iPortIndex++;
						}
						//
						if (it->m_oMember_5.m_bySlot_no > 0)
						{
							sprintf(arItemName, "Slot%d/%d\0", it->m_oMember_5.m_bySlot_no, it->m_oMember_5.m_byPort_no);
							char arPortName[10];
							sprintf(arPortName, "PORT%d\0", iPortIndex);
							tempItemValue["ChoosedMemberInterface"][arPortName] = arItemName;
							iPortIndex++;
						}
						if (it->m_oMember_6.m_bySlot_no > 0)
						{
							sprintf(arItemName, "Slot%d/%d\0", it->m_oMember_6.m_bySlot_no, it->m_oMember_6.m_byPort_no);
							char arPortName[10];
							sprintf(arPortName, "PORT%d\0", iPortIndex);
							tempItemValue["ChoosedMemberInterface"][arPortName] = arItemName;
							iPortIndex++;
						}
						if (it->m_oMember_7.m_bySlot_no > 0)
						{
							sprintf(arItemName, "Slot%d/%d\0", it->m_oMember_7.m_bySlot_no, it->m_oMember_7.m_byPort_no);
							char arPortName[10];
							sprintf(arPortName, "PORT%d\0", iPortIndex);
							tempItemValue["ChoosedMemberInterface"][arPortName] = arItemName;
							iPortIndex++;
						}
						if (it->m_oMember_8.m_bySlot_no > 0)
						{
							sprintf(arItemName, "Slot%d/%d\0", it->m_oMember_8.m_bySlot_no, it->m_oMember_8.m_byPort_no);
							char arPortName[10];
							sprintf(arPortName, "PORT%d\0", iPortIndex);
							tempItemValue["ChoosedMemberInterface"][arPortName] = arItemName;
							iPortIndex++;
						}
						sprintf(arItemName, "ITEM%d\0", i);
						rRoot[arItemName] = tempItemValue;
						i++;
						it++;
					}
					char* pTempJson = GetJsonStringByJsonValue(&rRoot);
					if (bMongo){
						bson_error_t error;
						bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));
						bson_t *bson = bson_new_from_json ((const uint8_t *)pTempJson, -1, &error);
						if (!bson) {
							BCON_APPEND(pKey, "errorCode", BCON_INT32(106));
						}
						else{
							BCON_APPEND(pKey, "errorCode", BCON_INT32(0));
							//		bson_append_array(pKey, "context", -1, bson);
							bson_append_document (pKey, "context", -1, bson);
						}

#if DEFINE_MONGO_INSERT
						if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_lag.c_str(), pKey)){
							// log新增数据失败；					
							char bufLog[512]="";			
							sprintf(bufLog, "Insert lag flow Failure:%d\n", iNeId);
							WriteLog(bufLog);
						}
#endif									
						bson_free (pKey);
						if (bson){
							bson_free (bson); //
						}
					}
					else{
						OTNM2000PipeClient oPipeClient(strPipeName);
						oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));
						//		printf(pTempJson);
					}

					delete [] pTempJson;
					pTempJson=NULL;
				}

				if (oTrunkBlock.m_arTrunk_Item.size() == 0)
				{					
					if (bMongo){			
						bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));						
						BCON_APPEND(pKey, "errorCode", BCON_INT32(106));					
#if DEFINE_MONGO_INSERT
						if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_lag.c_str(), pKey)){
							// log新增数据失败；					
							char bufLog[512]="";			
							sprintf(bufLog, "Insert lag flow Failure:%d\n", iNeId);
							WriteLog(bufLog);
						}
#endif									
						bson_free (pKey);					
					}
					else{
						OTNM2000PipeClient oPipeClient(strPipeName);
						char* pTempJson = "{\"errorCode\":\"106\"}";
						oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));					
					}					
				}
			}
		}
		else if (irit::IsIPRANNe(iNeType))
		{
			IPRANPARSE::CTrunk oTrunkBlock;
			DWORD dwRet  = neconfig::client::SyncReadBlockFromDB(oNeCmd, oTrunkBlock);
			if (0 == dwRet)
			{
				Json::Value rRoot;
				std::vector<IPRANPARSE::CTrunk_Item>::iterator it = oTrunkBlock.m_arTrunk_Item.begin();
				int i = 1;
				char arItemName[50];
				if (it != oTrunkBlock.m_arTrunk_Item.end())
				{
					while (it != oTrunkBlock.m_arTrunk_Item.end())
					{
						Json::Value tempItemValue;
						if (it->m_wVLAN == 0)
						{
							sprintf(arItemName, "lag%d\0", it->m_byLag_id);
						}else{

							sprintf(arItemName, "lag%d.%d\0", it->m_byLag_id, it->m_wVLAN);
						}

						tempItemValue["LagName"] = arItemName;
						//m_arMAC
						sprintf(arItemName, "%02X-%02X-%02X-%02X-%02X-%02X\0", 
							it->m_arMAC[0], it->m_arMAC[1], it->m_arMAC[2],
							it->m_arMAC[3], it->m_arMAC[4], it->m_arMAC[5]);
						tempItemValue["Mac"] = arItemName;
						//m_byL2L3
						tempItemValue["L2orL3Attr"] = GetL2orL3Attr(it->m_byL2L3);
						//m_byOperating_mode
						tempItemValue["LoadGroupingMode"] = GetLoadGroupingMode(it->m_byOperating_mode);
						//m_byHash_alg
						tempItemValue["LoadGroupingAlgorithm"] = GetLoadGroupingAlgorithm(it->m_byHash_alg);
						//
						int iPortIndex = 1;
						if (it->m_oMember_1.m_bySlot_no > 0)
						{
							sprintf(arItemName, "Slot%d/%d\0", it->m_oMember_1.m_bySlot_no, it->m_oMember_1.m_byPort_no);
							char arPortName[10];
							sprintf(arPortName, "PORT%d\0", iPortIndex);
							tempItemValue["ChoosedMemberInterface"][arPortName] = arItemName;
							iPortIndex++;
						}
						if (it->m_oMember_2.m_bySlot_no > 0)
						{
							sprintf(arItemName, "Slot%d/%d\0", it->m_oMember_2.m_bySlot_no, it->m_oMember_2.m_byPort_no);
							char arPortName[10];
							sprintf(arPortName, "PORT%d\0", iPortIndex);
							tempItemValue["ChoosedMemberInterface"][arPortName] = arItemName;
							iPortIndex++;
						}
						if (it->m_oMember_3.m_bySlot_no > 0)
						{
							sprintf(arItemName, "Slot%d/%d\0", it->m_oMember_3.m_bySlot_no, it->m_oMember_3.m_byPort_no);
							char arPortName[10];
							sprintf(arPortName, "PORT%d\0", iPortIndex);
							tempItemValue["ChoosedMemberInterface"][arPortName] = arItemName;
							iPortIndex++;
						}
						if (it->m_oMember_4.m_bySlot_no > 0)
						{
							sprintf(arItemName, "Slot%d/%d\0", it->m_oMember_4.m_bySlot_no, it->m_oMember_4.m_byPort_no);
							char arPortName[10];
							sprintf(arPortName, "PORT%d\0", iPortIndex);
							tempItemValue["ChoosedMemberInterface"][arPortName] = arItemName;
							iPortIndex++;
						}
						//
						if (it->m_oMember_5.m_bySlot_no > 0)
						{
							sprintf(arItemName, "Slot%d/%d\0", it->m_oMember_5.m_bySlot_no, it->m_oMember_5.m_byPort_no);
							char arPortName[10];
							sprintf(arPortName, "PORT%d\0", iPortIndex);
							tempItemValue["ChoosedMemberInterface"][arPortName] = arItemName;
							iPortIndex++;
						}
						if (it->m_oMember_6.m_bySlot_no > 0)
						{
							sprintf(arItemName, "Slot%d/%d\0", it->m_oMember_6.m_bySlot_no, it->m_oMember_6.m_byPort_no);
							char arPortName[10];
							sprintf(arPortName, "PORT%d\0", iPortIndex);
							tempItemValue["ChoosedMemberInterface"][arPortName] = arItemName;
							iPortIndex++;
						}
						if (it->m_oMember_7.m_bySlot_no > 0)
						{
							sprintf(arItemName, "Slot%d/%d\0", it->m_oMember_7.m_bySlot_no, it->m_oMember_7.m_byPort_no);
							char arPortName[10];
							sprintf(arPortName, "PORT%d\0", iPortIndex);
							tempItemValue["ChoosedMemberInterface"][arPortName] = arItemName;
							iPortIndex++;
						}
						if (it->m_oMember_8.m_bySlot_no > 0)
						{
							sprintf(arItemName, "Slot%d/%d\0", it->m_oMember_8.m_bySlot_no, it->m_oMember_8.m_byPort_no);
							char arPortName[10];
							sprintf(arPortName, "PORT%d\0", iPortIndex);
							tempItemValue["ChoosedMemberInterface"][arPortName] = arItemName;
							iPortIndex++;
						}
						sprintf(arItemName, "ITEM%d\0", i);
						rRoot[arItemName] = tempItemValue;
						i++;
						it++;
					}

					char* pTempJson = GetJsonStringByJsonValue(&rRoot);
					if (bMongo){
						bson_error_t error;
						bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));
						bson_t *bson = bson_new_from_json ((const uint8_t *)pTempJson, -1, &error);
						if (!bson) {
							BCON_APPEND(pKey, "errorCode", BCON_INT32(106));
						}
						else{
							BCON_APPEND(pKey, "errorCode", BCON_INT32(0));
							//		bson_append_array(pKey, "context", -1, bson);
							bson_append_document (pKey, "context", -1, bson);
						}

#if DEFINE_MONGO_INSERT
						if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_lag.c_str(), pKey)){
							// log新增数据失败；					
							char bufLog[512]="";			
							sprintf(bufLog, "Insert lag Failure:%d\n", iNeId);
							WriteLog(bufLog);
						}
#endif
						//char *string = bson_as_json(pKey, NULL);
						//printf ("%s\n", string);
						//bson_free (string);
						bson_free (pKey);
						if(bson){
							bson_free (bson);
						}//
					}
					else{
						OTNM2000PipeClient oPipeClient(strPipeName);
						oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));
						//		printf(pTempJson);
					}

					delete [] pTempJson;
					pTempJson=NULL;				
				}

				if (oTrunkBlock.m_arTrunk_Item.size() == 0)
				{					
					if (bMongo){
						bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));
						BCON_APPEND(pKey, "errorCode", BCON_INT32(106));					
#if DEFINE_MONGO_INSERT
						if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_lag.c_str(), pKey)){
							// log新增数据失败；					
							char bufLog[512]="";			
							sprintf(bufLog, "Insert lag flow Failure:%d\n", iNeId);
							WriteLog(bufLog);
						}
#endif									
						bson_free (pKey);					
					}
					else{
						OTNM2000PipeClient oPipeClient(strPipeName);
						char* pTempJson = "{\"errorCode\":\"106\"}";
						oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));					
					}					
				}
			}
		}
		else if (irit::IsPOTSNe(iNeType))
		{
			POTSPARSE::CTrunk_cfg oTrunkBlock;
			DWORD dwRet  = neconfig::client::SyncReadBlockFromDB(oNeCmd, oTrunkBlock);
			if (0 == dwRet)
			{
				Json::Value rRoot;
				std::vector<POTSPARSE::CTrunk_cfg_item>::iterator it = oTrunkBlock.m_arTrunk_cfg_item.begin();
				int i = 1;
				char arItemName[50];
				if (it != oTrunkBlock.m_arTrunk_cfg_item.end())
				{
					while (it != oTrunkBlock.m_arTrunk_cfg_item.end())
					{
						Json::Value tempItemValue;
						sprintf(arItemName, "Lag%d\0", it->m_oLag_cfg_info.m_wLag_id);
						tempItemValue["LagName"] = arItemName;
						//m_arMAC
						sprintf(arItemName, "%02X-%02X-%02X-%02X-%02X-%02X\0", 
							it->m_oLag_cfg_info.m_arMACAdress[0], it->m_oLag_cfg_info.m_arMACAdress[1], it->m_oLag_cfg_info.m_arMACAdress[2],
							it->m_oLag_cfg_info.m_arMACAdress[3], it->m_oLag_cfg_info.m_arMACAdress[4], it->m_oLag_cfg_info.m_arMACAdress[5]);
						tempItemValue["Mac"] = arItemName;
						//m_byL2L3
						tempItemValue["L2orL3Attr"] = "none";
						//m_byOperating_mode
						tempItemValue["LoadGroupingMode"] = GetLoadGroupingMode(it->m_oLag_cfg_info.m_byLag_model);
						//m_byHash_alg
						tempItemValue["LoadGroupingAlgorithm"] = GetLoadGroupingAlgorithm(it->m_oLag_cfg_info.m_byPartake_algorithm);
						sprintf(arItemName, "ITEM%d\0", i);
						rRoot[arItemName] = tempItemValue;
						i++;
						it++;
					}

					char* pTempJson = GetJsonStringByJsonValue(&rRoot);
					if (bMongo){
						bson_error_t error;
						bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));
						bson_t *bson = bson_new_from_json ((const uint8_t *)pTempJson, -1, &error);
						if (!bson) {
							BCON_APPEND(pKey, "errorCode", BCON_INT32(106));					
						}
						else{
							BCON_APPEND(pKey, "errorCode", BCON_INT32(0));
							//		bson_append_array(pKey, "context", -1, bson);
							bson_append_document (pKey, "context", -1, bson);
						}

#if DEFINE_MONGO_INSERT
						if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_lag.c_str(), pKey)){
							// log新增数据失败；					
							char bufLog[512]="";			
							sprintf(bufLog, "Insert lag Failure:%d\n", iNeId);
							WriteLog(bufLog);
						}
#endif
						//char *string = bson_as_json(pKey, NULL);
						//printf ("%s\n", string);
						//bson_free (string);
						bson_free (pKey);
						if(bson){
							bson_free(bson); //
						}
					}
					else{
						OTNM2000PipeClient oPipeClient(strPipeName);
						oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));	
					}
					delete [] pTempJson;
					pTempJson=NULL;
				}

				if (oTrunkBlock.m_arTrunk_cfg_item.size() == 0)
				{					
					if (bMongo){
						bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));
						BCON_APPEND(pKey, "errorCode", BCON_INT32(106));					
#if DEFINE_MONGO_INSERT
						if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_lag.c_str(), pKey)){
							// log新增数据失败；					
							char bufLog[512]="";			
							sprintf(bufLog, "Insert lag flow Failure:%d\n", iNeId);
							WriteLog(bufLog);
						}
#endif									
						bson_free (pKey);					
					}
					else{
						OTNM2000PipeClient oPipeClient(strPipeName);
						char* pTempJson = "{\"errorCode\":\"106\"}";
						oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));					
					}					
				}
			}
		}
		else{

			if (bMongo){
				bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));
				BCON_APPEND(pKey, "errorCode", BCON_INT32(105));					
#if DEFINE_MONGO_INSERT
				if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_lag.c_str(), pKey)){
					// log新增数据失败；					
					char bufLog[512]="";			
					sprintf(bufLog, "Insert lag flow Failure:%d\n", iNeId);
					WriteLog(bufLog);
				}
#endif									
				bson_free (pKey);					
			}
			else{
				OTNM2000PipeClient oPipeClient(strPipeName);
				char* pTempJson = "{\"errorCode\":\"105\"}";
				oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));					
			}
		}
#endif

#if NOT_LONG_CONNECT
		if (bIfNeedInit){
			if (neconfig::client::IsInitialize()){
				neconfig::client::UnInitialize();
			}
		}
#endif
	}
	catch(...)
	{
		WriteLog("GetLagInterfaceConfig catch error!");
		if(m_nCatchErrorCnt++ >= 3){
			g_bRestartNeedRestart = true;
			g_bErrorCatchOrHandle = true;
			g_bStopConfigMongoDBTheard = true;   //取状态和配置数据时catch到异常或是句柄超标，重启并不会影响取业务数据；
			g_bRestart = true;
		}
	}

	return false;
}

void OTNM2000GetNeconfigService::VEOutData(Json::Value &valOneCirId, BYTE m_byVlan_stacking_en, BYTE m_arMAC[6], BYTE m_arVport_name[32], unsigned long m_dwPrim_ip_addr, BYTE m_byPrim_ip_mask){

	char arItemName[50] = "";
	sprintf(arItemName, "%02X-%02X-%02X-%02X-%02X-%02X\0", 
		m_arMAC[0], m_arMAC[1], m_arMAC[2],
		m_arMAC[3], m_arMAC[4], m_arMAC[5]);

	char arIP[50] = "";
	sprintf(arIP, "%d.%d.%d.%d", (m_dwPrim_ip_addr>>24)&0xff, (m_dwPrim_ip_addr>>16)&0xff, (m_dwPrim_ip_addr>>8)&0xff, m_dwPrim_ip_addr&0xff);

	valOneCirId["Mac"] = Json::Value(arItemName);
	valOneCirId["IP"] = Json::Value(arIP);
	valOneCirId["IP Mask"] = Json::Value(m_byPrim_ip_mask);
	valOneCirId["VE-name"] = Json::Value((char*)m_arVport_name);  
	valOneCirId["Vlan_Stacking"] = Json::Value(m_byVlan_stacking_en?1:0);
}


bool OTNM2000GetNeconfigService::GetInterfaceConfigVEPARSE(std::string strPipeName, int iNeId, EM_TYPE_FUNCTION emType, bool bMongo)
{
	// TODO: 在此添加额外的初始化代码
	neconfig::CNeCmdInfo oNeCmd;
	oNeCmd.m_iUserId = -2;
	oNeCmd.m_iCmdId = neconfig::NECFG_CMD_QUERY_CONFIG;
	oNeCmd.m_iVer = 1;
	oNeCmd.m_iNeID = iNeId;
	oNeCmd.m_oLogInfo.m_byFlag = neconfig::ETYPE_NECMDLOG_NOLOG;

	Json::Value rRoot;
	if (emType == EM_TYPE_IPRAN8000Ne){

		R8000PARSE::CVe oVeBlock;
		DWORD dwRet  = neconfig::client::SyncReadBlockFromDB(oNeCmd, oVeBlock);
		if (0 == dwRet){	

			for(int i=0; i<(int)oVeBlock.m_arVe_Item.size(); ++i){

				char strItem[20] = "";
				sprintf(strItem, "ITEM%d\0", i);
				Json::Value valOneCirId;
				VEOutData(valOneCirId, oVeBlock.m_arVe_Item[i].m_byVlan_stacking_en, 
					oVeBlock.m_arVe_Item[i].m_arMAC, oVeBlock.m_arVe_Item[i].m_arVport_name, 
					oVeBlock.m_arVe_Item[i].m_dwPrim_ip_addr, oVeBlock.m_arVe_Item[i].m_byPrim_ip_mask);
				rRoot[strItem] = valOneCirId;
			}
		}
	}
	else if (emType == EM_TYPE_IPRANNe){

		IPRANPARSE::CVe oVeBlock;
		DWORD dwRet  = neconfig::client::SyncReadBlockFromDB(oNeCmd, oVeBlock);
		if (0 == dwRet){

			for(int i=0; i<(int)oVeBlock.m_arVe_Item.size(); ++i){//  没有m_byVlan_stacking_en信息；		

				char strItem[20] = "";
				sprintf(strItem, "ITEM%d\0", i);
				Json::Value valOneCirId;
				VEOutData(valOneCirId, /*oVeBlock.m_arVe_Item[i].m_byVlan_stacking_en*/0, 
					oVeBlock.m_arVe_Item[i].m_arMAC, oVeBlock.m_arVe_Item[i].m_arVport_name, oVeBlock.m_arVe_Item[i].m_dwPrim_ip_addr, oVeBlock.m_arVe_Item[i].m_byIp_mode);
				rRoot[strItem] = valOneCirId;
			}			
		}
	}
	else if (emType == EM_TYPE_POTSNe){

		//		POTSPARSE::CTrunk_cfg oTrunkBlock;
		if (bMongo){				
			bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));
			BCON_APPEND(pKey, "errorCode", BCON_INT32(105));
#if DEFINE_MONGO_INSERT
			if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_ve.c_str(), pKey)){
				// log新增数据失败；					
				char bufLog[512]="";			
				sprintf(bufLog, "Insert ve 105 Failure:%d\n", iNeId);
				WriteLog(bufLog);
			}
#endif
			bson_free (pKey);		
		}
		else{
			OTNM2000PipeClient oPipeClient(strPipeName);
			char* pTempJson = "{\"errorCode\":\"105\"}";
			oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));	
		}
		return false;
	}

	char* pTempJson = GetJsonStringByJsonValue(&rRoot);
	if (bMongo){
		bson_error_t error;
		bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));

		bson_t *bson = bson_new_from_json ((const uint8_t *)pTempJson, -1, &error);
		if (!bson) {
			BCON_APPEND(pKey, "errorCode", BCON_INT32(106));	
		}
		else{
			BCON_APPEND(pKey, "errorCode", BCON_INT32(0));
			//		bson_append_array(pKey, "context", -1, bson);
			bson_append_document (pKey, "context", -1, bson);
		}

#if DEFINE_MONGO_INSERT
		if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_ve.c_str(), pKey)){
			// log新增数据失败；					
			char bufLog[512]="";			
			sprintf(bufLog, "Insert ve Failure:%d\n", iNeId);
			WriteLog(bufLog);
		}
#endif	
		//	char *string = bson_as_json(pKey, NULL);
		//	printf ("%s\n", string);
		//	bson_free (string);
		bson_free (pKey);
		if(bson){
			bson_free(bson); //
		}
	}
	else{
		OTNM2000PipeClient oPipeClient(strPipeName);
		oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));	
	}
	delete [] pTempJson;
	pTempJson=NULL;

	return false;
}


void OTNM2000GetNeconfigService::GetInterfaceConfigEtherNetPARSEMsgUsual(Json::Value &valOneCirId, BYTE m_byPort_rate_type,
																		 BYTE m_arPort_desc[64], BYTE m_byUrpf_en, int m_nMtu, BYTE m_byEndIf, BYTE m_byShut, BYTE m_arVport_name[32]){

																			 // 端口速率类型;
																			 // 接口描述;
																			 // urpf使能;
																			 // 端口开关;
																			 // mtu和终结使能;
																			 // 虚端口名称；
																			 valOneCirId["PortRate"] = Json::Value(m_byPort_rate_type);
																			 //	 valOneCirId["PortDescription"] = Json::Value((char*)m_arPort_desc);
																			 valOneCirId["urpf_If"] = Json::Value(m_byUrpf_en);

																			 valOneCirId["MTU"] = Json::Value(m_nMtu);  
																			 valOneCirId["PortKaiGuan"] = Json::Value(m_byShut);
																			 valOneCirId["End_If"] = Json::Value(m_byEndIf);

																			 valOneCirId["Vport_name"] = Json::Value((char*)m_arVport_name);

}

void OTNM2000GetNeconfigService::GetInterfaceConfigEtherNetPARSEMsgEthNet(Json::Value &valOneCirId,BYTE m_byPort_mode, BYTE m_byIp_mode, unsigned long m_dwPrim_ip_addr,
																		  BYTE m_byPrim_ip_mask, BYTE m_byRsvp_en, BYTE m_byLdp_en, BYTE m_byMpls_en, BYTE m_byArp_proxy_en) {

																			  //端口模式 
																			  //IP指定形式 ;
																			  //PrimIP地址 ;

																			  //PrimIP掩码 ;
																			  //RSVP协议使能 ;
																			  //LDP协议使能 ;
																			  //MPLS使能 ;
																			  //arp代理使能 ;

																			  valOneCirId["PortMode"] = Json::Value(m_byPort_mode);
																			  valOneCirId["IPMode"] = Json::Value(m_byIp_mode);

																			  char arIP[50] = "";
																			  sprintf(arIP, "%d.%d.%d.%d", (m_dwPrim_ip_addr>>24)&0xff, (m_dwPrim_ip_addr>>16)&0xff, (m_dwPrim_ip_addr>>8)&0xff, m_dwPrim_ip_addr&0xff);
																			  valOneCirId["PrimIP"] = Json::Value(arIP);

																			  valOneCirId["PrimIPMask"] = Json::Value(m_byPrim_ip_mask);  
																			  valOneCirId["RSVP_If"] = Json::Value(m_byRsvp_en);
																			  valOneCirId["LDP_If"] = Json::Value(m_byLdp_en);
																			  valOneCirId["MPLS_If"] = Json::Value(m_byMpls_en);
																			  valOneCirId["Arp_If"] = Json::Value(m_byArp_proxy_en);
}

bool OTNM2000GetNeconfigService::GetInterfaceConfigEtherNetPARSE(std::string strPipeName, int iNeId, EM_TYPE_FUNCTION emType, bool bMongo)
{
	// TODO: 在此添加额外的初始化代码
	neconfig::CNeCmdInfo oNeCmd;
	oNeCmd.m_iUserId = -2;
	oNeCmd.m_iCmdId = neconfig::NECFG_CMD_QUERY_CONFIG;
	oNeCmd.m_iVer = 1;
	oNeCmd.m_iNeID = iNeId;
	oNeCmd.m_oLogInfo.m_byFlag = neconfig::ETYPE_NECMDLOG_NOLOG;

	Json::Value rRoot;
	if (emType == EM_TYPE_IPRAN8000Ne){

		R8000PARSE::CEthinterface oVeBlock;
		DWORD dwRet  = neconfig::client::SyncReadBlockFromDB(oNeCmd, oVeBlock);
		if (0 == dwRet){// ok

			for(int i=0; i<(int)oVeBlock.m_arEthinterface_Item.size(); ++i){
#if 1				
				char strItem[20] = "";
				sprintf(strItem, "ITEM%d\0", i);
				Json::Value valOneCirId;
				GetInterfaceConfigEtherNetPARSEMsgUsual(valOneCirId, oVeBlock.m_arEthinterface_Item[i].m_byPort_rate_type, 
					oVeBlock.m_arEthinterface_Item[i].m_arPort_desc, oVeBlock.m_arEthinterface_Item[i].m_byUrpf_en, 
					oVeBlock.m_arEthinterface_Item[i].m_wMtu, oVeBlock.m_arEthinterface_Item[i].m_byInterface_type, oVeBlock.m_arEthinterface_Item[i].m_byShut,oVeBlock.m_arEthinterface_Item[i].m_arVport_name);

				GetInterfaceConfigEtherNetPARSEMsgEthNet(valOneCirId, oVeBlock.m_arEthinterface_Item[i].m_byPort_mode, oVeBlock.m_arEthinterface_Item[i].m_byIp_mode, 
					oVeBlock.m_arEthinterface_Item[i].m_dwPrim_ip_addr, oVeBlock.m_arEthinterface_Item[i].m_byPrim_ip_mask, oVeBlock.m_arEthinterface_Item[i].m_byRsvp_en, 
					oVeBlock.m_arEthinterface_Item[i].m_byLdp_en, oVeBlock.m_arEthinterface_Item[i].m_byMpls_en, oVeBlock.m_arEthinterface_Item[i].m_byArp_proxy_en);

				rRoot[strItem] = valOneCirId;
#endif			
			}
		}		
	}
	else if (emType == EM_TYPE_IPRANNe){

		IPRANPARSE::CEthinterface oVeBlock;
		DWORD dwRet  = neconfig::client::SyncReadBlockFromDB(oNeCmd, oVeBlock);
		if (0 == dwRet){

			for(int i=0; i<(int)oVeBlock.m_arEthinterface_Item.size(); ++i){// 待测试；m_byOperating_mode参数？

				char strItem[20] = "";
				sprintf(strItem, "ITEM%d\0", i);
				Json::Value valOneCirId;
				GetInterfaceConfigEtherNetPARSEMsgUsual(valOneCirId, oVeBlock.m_arEthinterface_Item[i].m_byPort_rate_type, 
					oVeBlock.m_arEthinterface_Item[i].m_arPort_desc, oVeBlock.m_arEthinterface_Item[i].m_byUrpf_en, 
					oVeBlock.m_arEthinterface_Item[i].m_wMtu, oVeBlock.m_arEthinterface_Item[i].m_byOperating_mode/*不一定*/, oVeBlock.m_arEthinterface_Item[i].m_byShut,oVeBlock.m_arEthinterface_Item[i].m_arVport_name);

				GetInterfaceConfigEtherNetPARSEMsgEthNet(valOneCirId, oVeBlock.m_arEthinterface_Item[i].m_byPort_mode, oVeBlock.m_arEthinterface_Item[i].m_byIp_mode, 
					oVeBlock.m_arEthinterface_Item[i].m_dwPrim_ip_addr, oVeBlock.m_arEthinterface_Item[i].m_byPrim_ip_mask, oVeBlock.m_arEthinterface_Item[i].m_byRsvp_en, 
					oVeBlock.m_arEthinterface_Item[i].m_byLdp_en, oVeBlock.m_arEthinterface_Item[i].m_byMpls_en, oVeBlock.m_arEthinterface_Item[i].m_byArp_proxy_en);

				rRoot[strItem] = valOneCirId;
			}
		}
	}
	else if (emType == EM_TYPE_POTSNe){
		if (bMongo){				
			bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));
			BCON_APPEND(pKey, "errorCode", BCON_INT32(105));
#if DEFINE_MONGO_INSERT
			if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_ether.c_str(), pKey)){
				// log新增数据失败；					
				char bufLog[512]="";			
				sprintf(bufLog, "Insert eth 105 Failure:%d\n", iNeId);
				WriteLog(bufLog);
			}
#endif
			bson_free(pKey);
			return false;
		}
		else{
			OTNM2000PipeClient oPipeClient(strPipeName);
			char* pTempJson = "{\"errorCode\":\"105\"}";
			oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));	
		}
	}

	char* pTempJson = GetJsonStringByJsonValue(&rRoot);
	if (bMongo){

		//if (iNeId == 134219348)
		//{
		//	if (pTempJson != NULL){
		//		WriteLog(pTempJson); //
		//	}
		//	else{
		//		WriteLog("134219348 str null!!!");
		//	}
		//}

		bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));	
		bson_error_t error;
		bson_t *bson = bson_new_from_json ((const uint8_t *)pTempJson, -1, &error);
		if (!bson) {
			BCON_APPEND(pKey, "errorCode", BCON_INT32(106));		
		}else{
			BCON_APPEND(pKey, "errorCode", BCON_INT32(0));
			//		bson_append_array(pKey, "context", -1, bson);
			bson_append_document (pKey, "context", -1, bson);
		}

#if DEFINE_MONGO_INSERT
		if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_ether.c_str(), pKey)){
			// log新增数据失败；					
			char bufLog[512]="";			
			sprintf(bufLog, "Insert eth Failure:%d\n", iNeId);
			WriteLog(bufLog);
		}
#endif
		//	char *string = bson_as_json(pKey, NULL);
		//	printf ("%s\n", string);
		//	bson_free (string);
		bson_free (pKey);
		if (bson){
			bson_free (bson); //
		}
	}
	else{
		OTNM2000PipeClient oPipeClient(strPipeName);
		oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));	
	}
	delete [] pTempJson;
	pTempJson=NULL;

	return false;
}

void OTNM2000GetNeconfigService::GetClockConfigInterfaceConfigJson(Json::Value &valOneCirId, BYTE m_byClock_Work_Mode, BYTE m_byQL_Enable_Select,
																   BYTE m_byCLK1_Input_Type, BYTE m_byCLK2_Input_Type,BYTE m_byCLK3_Input_Type){

																	   valOneCirId["Clock_Work_Mode"] = Json::Value(m_byClock_Work_Mode);
																	   valOneCirId["QL_enable"] = Json::Value(m_byQL_Enable_Select);
																	   valOneCirId["CLK1_Input_Type"] = Json::Value(m_byCLK1_Input_Type);
																	   valOneCirId["CLK2_Input_Type"] = Json::Value(m_byCLK2_Input_Type);
																	   valOneCirId["CLK3_Input_Type"] = Json::Value(m_byCLK3_Input_Type);
}

bool OTNM2000GetNeconfigService::GetClockConfigInterfaceConfig(std::string strPipeName, int iNeId, EM_TYPE_FUNCTION emType, bool bMongo)
{
	// TODO: 在此添加额外的初始化代码
	neconfig::CNeCmdInfo oNeCmd;
	oNeCmd.m_iUserId = -2;
	oNeCmd.m_iCmdId = neconfig::NECFG_CMD_QUERY_CONFIG;
	oNeCmd.m_iVer = 1;
	oNeCmd.m_iNeID = iNeId;
	oNeCmd.m_oLogInfo.m_byFlag = neconfig::ETYPE_NECMDLOG_NOLOG;

	Json::Value rRoot;
	if (emType == EM_TYPE_IPRAN8000Ne){

		R8000PARSE::CClock_Conf oVeBlock;
		DWORD dwRet  = neconfig::client::SyncReadBlockFromDB(oNeCmd, oVeBlock);
		if (0 == dwRet){// ok

			for(int i=0; i<(int)oVeBlock.m_arClock_Conf_Item.size(); ++i){

				R8000PARSE::CClock_Conf_Item &TMP = oVeBlock.m_arClock_Conf_Item[i];

				char strItem[20] = "";
				sprintf(strItem, "ITEM%d\0", i);
				Json::Value valOneCirId;
				GetClockConfigInterfaceConfigJson(valOneCirId, oVeBlock.m_arClock_Conf_Item[i].m_byClock_Work_Mode, 
					oVeBlock.m_arClock_Conf_Item[i].m_byQL_Enable_Select, oVeBlock.m_arClock_Conf_Item[i].m_byCLK1_Input_Type, 
					oVeBlock.m_arClock_Conf_Item[i].m_byCLK2_Input_Type,oVeBlock.m_arClock_Conf_Item[i].m_byCLK3_Input_Type);

				// 输入定时源时钟
				Json::Value valNum1_type;
				for(int j = 0; j < (int)TMP.m_arNum1_type.size(); ++j){

					R8000PARSE::CNum1_type &tmpInputClock = TMP.m_arNum1_type[j];					
					//输入定时源时钟选择 ; //输入时钟优先级 ;//输入源QL选择 ;//输入源等待恢复定时开关 ;
					char strItem[20] = "";
					sprintf(strItem, "ITEM_INPUT_CLOCK%d\0", j);
					Json::Value valOneInput;
					valOneInput["Input_clock_select"] = Json::Value((char*)tmpInputClock.m_arInput_clock_select);
					valOneInput["Input_clock_priority"] = Json::Value(tmpInputClock.m_byInput_clock_priority);
					valOneInput["SRC_QL_Value_Input"] = Json::Value(tmpInputClock.m_bySRC_QL_Value_Input);
					valOneInput["Input_Waiting_Restore_Timer_Switch"] = Json::Value(tmpInputClock.m_byInput_Waiting_Restore_Timer_Switch);					
					valNum1_type[strItem] = valOneInput;
				}
				valOneCirId["Input_Src_Clock"] = valNum1_type;
				// 输入定时源时钟 end;

				rRoot[strItem] = valOneCirId;			
			}
		}		
	}
	else if (emType == EM_TYPE_IPRANNe){

		//	rRoot["NetType"] = Json::Value("IPRANNe");
		if (bMongo){				
			bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));
			BCON_APPEND(pKey, "errorCode", BCON_INT32(105));
#if DEFINE_MONGO_INSERT
			if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_clock.c_str(), pKey)){
				// log新增数据失败；					
				char bufLog[512]="";			
				sprintf(bufLog, "Insert clock 105 Failure:%d\n", iNeId);
				WriteLog(bufLog);
			}
#endif
			bson_free(pKey);
		}
		else{
			OTNM2000PipeClient oPipeClient(strPipeName);
			char* pTempJson = "{\"errorCode\":\"105\"}";
			oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));	
		}
		return false;
	}
	else if (emType == EM_TYPE_POTSNe){

		//		rRoot["NetType"] = Json::Value("POTSNe");
		if (bMongo){				
			bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));
			BCON_APPEND(pKey, "errorCode", BCON_INT32(105));
#if DEFINE_MONGO_INSERT
			if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_clock.c_str(), pKey)){
				// log新增数据失败；					
				char bufLog[512]="";			
				sprintf(bufLog, "Insert clock 105 Failure:%d\n", iNeId);
				WriteLog(bufLog);
			}
#endif
			bson_free (pKey);
		}
		else{
			OTNM2000PipeClient oPipeClient(strPipeName);
			char* pTempJson = "{\"errorCode\":\"105\"}";
			oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));	
		}
		return false;
	}

	char* pTempJson = GetJsonStringByJsonValue(&rRoot);
	if (bMongo){
		bson_error_t error;
		bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));
		bson_t *bson = bson_new_from_json ((const uint8_t *)pTempJson, -1, &error);
		if (!bson) {
			BCON_APPEND(pKey, "errorCode", BCON_INT32(106));
		}
		else{
			BCON_APPEND(pKey, "errorCode", BCON_INT32(0));
			//		bson_append_array(pKey, "context", -1, bson);
			bson_append_document (pKey, "context", -1, bson);
		}

#if DEFINE_MONGO_INSERT
		if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_clock.c_str(), pKey)){
			// log新增数据失败；					
			char bufLog[512]="";			
			sprintf(bufLog, "Insert clock Failure:%d\n", iNeId);
			WriteLog(bufLog);
		}
#endif
		//		char *string = bson_as_json(pKey, NULL);
		//		printf ("%s\n", string);
		//		bson_free (string);
		bson_free (pKey);
		if (bson){
			bson_free (bson); //
		}
	}
	else{
		OTNM2000PipeClient oPipeClient(strPipeName);
		oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));	
	}
	delete [] pTempJson;
	pTempJson=NULL;

	return false;
}

bool OTNM2000GetNeconfigService::GetClockConfigInterfaceConfig(Json::Value &rRoot, int iNeId, EM_TYPE_FUNCTION emType)
{
	// TODO: 在此添加额外的初始化代码
	neconfig::CNeCmdInfo oNeCmd;
	oNeCmd.m_iUserId = -2;
	oNeCmd.m_iCmdId = neconfig::NECFG_CMD_QUERY_CONFIG;
	oNeCmd.m_iVer = 1;
	oNeCmd.m_iNeID = iNeId;
	oNeCmd.m_oLogInfo.m_byFlag = neconfig::ETYPE_NECMDLOG_NOLOG;

	if (emType == EM_TYPE_IPRAN8000Ne){

		R8000PARSE::CClock_Conf oVeBlock;
		DWORD dwRet  = neconfig::client::SyncReadBlockFromDB(oNeCmd, oVeBlock);
		if (0 == dwRet){// ok

			for(int i=0; i<(int)oVeBlock.m_arClock_Conf_Item.size(); ++i){

				R8000PARSE::CClock_Conf_Item &TMP = oVeBlock.m_arClock_Conf_Item[i];

				char strItem[20] = "";
				sprintf(strItem, "ITEM%d\0", i);
				Json::Value valOneCirId;
				GetClockConfigInterfaceConfigJson(valOneCirId, oVeBlock.m_arClock_Conf_Item[i].m_byClock_Work_Mode, 
					oVeBlock.m_arClock_Conf_Item[i].m_byQL_Enable_Select, oVeBlock.m_arClock_Conf_Item[i].m_byCLK1_Input_Type, 
					oVeBlock.m_arClock_Conf_Item[i].m_byCLK2_Input_Type,oVeBlock.m_arClock_Conf_Item[i].m_byCLK3_Input_Type);

				// 输入定时源时钟
				Json::Value valNum1_type;
				for(int j = 0; j < (int)TMP.m_arNum1_type.size(); ++j){

					R8000PARSE::CNum1_type &tmpInputClock = TMP.m_arNum1_type[j];					
					//输入定时源时钟选择 ; //输入时钟优先级 ;//输入源QL选择 ;//输入源等待恢复定时开关 ;
					char strItem[20] = "";
					sprintf(strItem, "ITEM_INPUT_CLOCK%d\0", j);
					Json::Value valOneInput;
					valOneInput["Input_clock_select"] = Json::Value((char*)tmpInputClock.m_arInput_clock_select);
					valOneInput["Input_clock_priority"] = Json::Value(tmpInputClock.m_byInput_clock_priority);
					valOneInput["SRC_QL_Value_Input"] = Json::Value(tmpInputClock.m_bySRC_QL_Value_Input);
					valOneInput["Input_Waiting_Restore_Timer_Switch"] = Json::Value(tmpInputClock.m_byInput_Waiting_Restore_Timer_Switch);					
					valNum1_type[strItem] = valOneInput;
				}
				valOneCirId["Input_Src_Clock"] = valNum1_type;
				// 输入定时源时钟 end;

				rRoot[strItem] = valOneCirId;			
			}
		}		
	}
	else if (emType == EM_TYPE_IPRANNe){

		rRoot["NetType"] = Json::Value("IPRANNe");
	}
	else if (emType == EM_TYPE_POTSNe){

		rRoot["NetType"] = Json::Value("POTSNe");
	}

	return false;
}

bool OTNM2000GetNeconfigService::GetAllTypeInterfaceConfig(const std::string &strPipeName, const vector<string> &vctFunParam, EM_TYPE_FUNCTION emType)
{//  只写pipe，不写mongo;
	try{
		// TODO: 在此添加额外的初始化代码
#if NOT_LONG_CONNECT
		if (!neconfig::client::IsInitialize()){
			if (!neconfig::client::Initialize()){		

				OTNM2000PipeClient oPipeClient(strPipeName);
				char* pTempJson = "{\"errorCode\":\"104\"}";
				oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));			
				return 0;
			}
		}
#endif

		Json::Value rRoot;
		for (int i = 2; i < (int)vctFunParam.size(); ++i){

			int iNeId = atoi(vctFunParam[i].c_str());
			char strItem[20] = "";
			sprintf(strItem, "%d\0", iNeId);
			Json::Value valOneCirId;

			int iNeType = irit::GetNeTypeOfNeFromBoardType(iNeId);
			if (irit::IsIPRAN8000Ne(iNeType)){// ok

				if(emType == EM_GETCLOCKCONFIGINTERFACECONFIG){
					GetClockConfigInterfaceConfig(valOneCirId, iNeId, EM_TYPE_IPRAN8000Ne);
				}
			}
			else if (irit::IsIPRANNe(iNeType)){// 没有使能的参数

				if(emType == EM_GETCLOCKCONFIGINTERFACECONFIG){
					GetClockConfigInterfaceConfig(valOneCirId, iNeId, EM_TYPE_IPRANNe);
				}
			}
			else if (irit::IsPOTSNe(iNeType)){ 

				if(emType == EM_GETCLOCKCONFIGINTERFACECONFIG){
					GetClockConfigInterfaceConfig(valOneCirId, iNeId, EM_TYPE_POTSNe);
				}
			}

			rRoot[strItem] = valOneCirId;
		}

		char* pTempJson = GetJsonStringByJsonValue(&rRoot);	
		OTNM2000PipeClient oPipeClient(strPipeName);
		oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));		
		delete [] pTempJson;
		pTempJson=NULL;

#if NOT_LONG_CONNECT
		if (neconfig::client::IsInitialize()){
			neconfig::client::UnInitialize();
		}
#endif
	}catch(...)
	{
		WriteLog("GetAllTypeInterfaceConfig vct catch error!");
		if(m_nCatchErrorCnt++ >= 3){
			g_bRestartNeedRestart = true;
			g_bErrorCatchOrHandle = true;
			g_bStopConfigMongoDBTheard = true;
			g_bRestart = true;
		}
	}
	return false;
}

void OTNM2000GetNeconfigService::GetOtnm2000ConnectState(const std::string &strPipeName)
{
	OTNM2000PipeClient oPipeClient(strPipeName);
	char* pTempJson = "{\"errorCode\":\"0\"}";
	oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));
	printf(pTempJson);
}

static void CopyDOMString2String(std::string &strDest, const DLL_DOM::STRING &strSrc)
{
	if (strSrc.isnull())
	{
		strDest.erase();
		return;
	}

	char *pcSrc = strSrc.WChar2Ansi();
	strDest = pcSrc;
	DLL_DOM::SysFree(pcSrc);
}

static std::string CopyDOMString2String(const DLL_DOM::STRING &strSrc)
{
	std::string strRet;
	CopyDOMString2String(strRet, strSrc);
	return strRet;
}

static void CopyDOMString2CString(CString &strDest, const DLL_DOM::STRING &strSrc)
{
	if (strSrc.isnull())
	{
		strDest.Empty();
		return;
	}

	strDest = CString((wchar_t *)strSrc.GetData(), strSrc.GetDataSize());
}

static CString CopyDOMString2CString(const DLL_DOM::STRING &strSrc)
{
	CString strRet;
	CopyDOMString2CString(strRet, strSrc);
	return strRet;
}


#if 1

class CNeStatusCBmcc :public CNeStatusCB
{
public:
	CNeStatusCBmcc()
	{
		g_arOutTmp.RemoveAll();
		g_mccInCallBack = false;
	}

	~CNeStatusCBmcc()
	{
		//	g_arOutTmp.RemoveAll();
		//	g_mccInCallBack = false;
	}

public:
	virtual void Response(const otnm::bus::ErrorCode &oEC, int iNeId, NeStatusDataPtr pData, std::string strErrInf = std::string())
	{	
		if (oEC && pData && (pData->GetDataType() == TYPE_STATUS_MCC_CONFIG) && !g_mccInCallBack)
		{
			std::list<MccConfig> &tmpMccConfigList = ((CMccConfigData *)pData.get())->m_lstData;
			for (std::list<MccConfig>::iterator iter=tmpMccConfigList.begin(); iter!=tmpMccConfigList.end(); iter++)
			{
				g_arOutTmp.Add(iter->m_strArea.c_str());
				g_arOutTmp.Add(iter->m_strMcc.c_str());
			}
			g_mccInCallBack = true;
		}
	}
};

#endif

void OTNM2000GetNeconfigService::GetNetMccStaticStatue(const std::string &strPipeName, int iNeId, int iTimeOut, bool bSetMongoDB)
{
	try{
#if NOT_LONG_CONNECT
		/*
		if (!neconfig::client::IsInitialize()){
		if (!neconfig::client::Initialize()){
		OTNM2000PipeClient oPipeClient(strPipeName);
		char* pTempJson = "{\"errorCode\":\"104\"}";						
		oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));
		return ;
		}
		}
		*/
#endif

		Json::Value valOneCirId, rTmpContext;
		valOneCirId["_id"] = Json::Value(iNeId);
#if 0
		MccConfigList lstMccConfigData;
		ErrorCode tmpError = otnm::busclient::COtnmApiProvider::Instance()->GetNEStatusApiProvider()->SynGetMccConfig(
			lstMccConfigData, iNeId, iTimeOut); // => xxx 接口有问题。

		char buf[256]="";
		if(tmpError.IsSuccess()){

			valOneCirId["errorCode"] = Json::Value("0");		

			int i=0;
			for (std::list<MccConfig>::iterator iter = lstMccConfigData.begin(); iter != lstMccConfigData.end(); iter++, i++){
				Json::Value rTmpContextOne;
				MccConfig &tmpMccConfig = *iter;

				rTmpContextOne["Area"]=Json::Value(tmpMccConfig.m_strArea.c_str());
				rTmpContextOne["Mcc"]=Json::Value(tmpMccConfig.m_strMcc.c_str());
				sprintf(buf, "item%d", i);
				rTmpContext[buf]=rTmpContextOne;
			}

			valOneCirId["context"]= rTmpContext;			
		}
		else{
			valOneCirId["errorCode"] = Json::Value("109");	
		}
#else
		NeStatusCBPtr m_pCallback = NeStatusCBPtr(new CNeStatusCBmcc());
		bool bInCallBack = false;   // 回调函数是否取到结果了；
		int  nCntNotInCallBack = 0;	// 回调函数没有得到结果的次数；	
		otnm::busclient::COtnmApiProvider::Instance()->GetNEStatusApiProvider()->AsynGetMccConfig(
			iNeId, m_pCallback); // => 异步的回调函数，没有接上；xxx
#if 1
		/////=> 异步一次返回所有结果的情况；
		int nOneWaitTime = 200;
		int nMaxWaitCnt = iTimeOut/nOneWaitTime + 1;
		do{
			Sleep(nOneWaitTime);
		}while((!g_mccInCallBack)  && (nCntNotInCallBack++ < nMaxWaitCnt));
		bInCallBack = g_mccInCallBack;

#else	
		do{/////=> 异步多次返回结果的情况；
			if (g_mccInCallBack){
				nCntNotInCallBack = 0;
				bInCallBack = true;
				g_mccInCallBack = false;
			}

			if (!g_mccInCallBack){
				Sleep(200);
			}
		}while(!g_mccInCallBack && (nCntNotInCallBack++ == 10));
#endif	

		m_pCallback.reset();

		if (!bInCallBack){
			valOneCirId["errorCode"] = Json::Value("109");
		}
		else{
			valOneCirId["errorCode"] = Json::Value("0");
			int size=g_arOutTmp.GetSize();   //得长度
			for(int i=0;i < size/2; i++)
			{ 
				CString strTmpArea=g_arOutTmp.GetAt(i*2);   
				CString strTmpMcc=g_arOutTmp.GetAt(i*2 + 1); 

				Json::Value rTmpContextOne;			
				rTmpContextOne["Area"]=Json::Value(strTmpArea.GetBuffer(0));
				rTmpContextOne["Mcc"]=Json::Value(strTmpMcc.GetBuffer(0));
				//		char buf[20] = "";
				//		sprintf(buf, "item%d", i);
				//		rTmpContext[buf]=rTmpContextOne;
				rTmpContext.append(rTmpContextOne);
			} 
			valOneCirId["context"]= rTmpContext;
		}		
#endif

		char* pTempJson = GetJsonStringByJsonValue(&valOneCirId);
		if (bSetMongoDB){
			bson_error_t error;		
			bson_t *pKey = bson_new_from_json ((const uint8_t *)pTempJson, -1, &error);
			if (!pKey) {
				pKey = BCON_NEW("_id", BCON_INT32(iNeId));
				BCON_APPEND(pKey, "errorCode", BCON_INT32(106));
			}

#if DEFINE_MONGO_INSERT
			if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_NeStatus.c_str(), pKey)){
				// log新增数据失败；					
				char bufLog[512]="";			
				sprintf(bufLog, "Insert NeStatus Failure:%d\n", iNeId);
				WriteLog(bufLog);
			}
#endif		
			bson_free (pKey);	
		}
		else{
			OTNM2000PipeClient oPipeClient(strPipeName);
			oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));	
		}
		delete [] pTempJson;
		pTempJson=NULL;

#if NOT_LONG_CONNECT
		/*
		if (neconfig::client::IsInitialize()){
		neconfig::client::UnInitialize();
		}
		*/
#endif
	}  
	catch(...)  {  

		WriteLog("GetNetMccStaticStatue catch error!");  
		if(m_nCatchErrorCnt++ >= 3){
			//		g_bRestartNeedRestart = true;
			//		g_bErrorCatchOrHandle = true;
			//		g_bStopConfigMongoDBTheard = true;
			//		g_bRestart = true;
		}
	}  
}

void OTNM2000GetNeconfigService::GetNetBoardStatue(const std::string &strPipeName, int iNeId, int iTimeOut)
{
	try{
#if NOT_LONG_CONNECT
		if (!neconfig::client::IsInitialize()){ // 初始化判断没有用，总是会执行；
			if (!neconfig::client::Initialize()){
				OTNM2000PipeClient oPipeClient(strPipeName);
				char* pTempJson = "{\"errorCode\":\"104\"}";						
				oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));
				return ;
			}
		}
#endif
		BoardState stBoardStateData;
		std::vector<int> vctBoardId;
		std::vector<std::string> vctStrSlots;
		GetBoardNeSlots(vctStrSlots, vctBoardId, iNeId);

		if (vctStrSlots.size() != 0)
		{
			iTimeOut = iTimeOut/vctStrSlots.size() + (iTimeOut%vctStrSlots.size()==0?0:1);
		}

		Json::Value rRoot;
		for (int i=0;i<(int)vctStrSlots.size();++i){

			char bufTmp[20]="";
			sprintf(bufTmp, "%d", i);
			ErrorCode tmpError = otnm::busclient::COtnmApiProvider::Instance()->GetNEStatusApiProvider()->SynGetBoardState(
				stBoardStateData,iNeId, /*vctStrSlots[i]*/bufTmp, iTimeOut);

			Json::Value rTmp;
			if(tmpError.IsSuccess())
			{
				Json::Value rTmpContext;
				rTmpContext["BoardTemp"] = Json::Value(stBoardStateData.m_strBoardTemp.c_str());
				rTmpContext["BoardVersion"] = Json::Value(stBoardStateData.m_strBoardVersion.c_str());
				rTmpContext["PCBVersion"] = Json::Value(stBoardStateData.m_strPCBVersion.c_str());
				rTmpContext["PowerOnTime"] = Json::Value(stBoardStateData.m_strPowerOnTime.c_str());
				rTmpContext["SoftwareVersion"] = Json::Value(stBoardStateData.m_strSoftwareVersion.c_str());
				rTmpContext["Register"] = Json::Value(stBoardStateData.m_iRegister);
				rTmpContext["Active"] = Json::Value(stBoardStateData.m_iActive);

				rTmp["context"]= rTmpContext;
				rTmp["statue"] = Json::Value("ok");
			}
			else{

				Json::Value rTmpContext;
				rTmp["context"]= rTmpContext;
				rTmp["statue"] = Json::Value("error");
			}

			rTmp["StrSlots"] = Json::Value(vctStrSlots[i].c_str());
			rTmp["BoardID"] = Json::Value(vctBoardId[i]);

			char buf[20]="";
			sprintf(buf, "item%d",i);
			rRoot[buf] = rTmp;			
		}

		char* pTempJson = GetJsonStringByJsonValue(&rRoot);
		OTNM2000PipeClient oPipeClient(strPipeName);
		oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));
		//	printf(pTempJson);
		delete [] pTempJson;	
		pTempJson = NULL;
#if NOT_LONG_CONNECT
		if (neconfig::client::IsInitialize()){
			neconfig::client::UnInitialize();   //卸载时，句柄有问题。
		}
#endif
	}  
	catch(...)  
	{  
		WriteLog("GetNetBoardStatue catch error!");  
		if(m_nCatchErrorCnt++ >= 3){
			g_bRestartNeedRestart = true;
			g_bErrorCatchOrHandle = true;
			g_bStopConfigMongoDBTheard = true;
			g_bRestart = true;
		}
	}  
}

bool OTNM2000GetNeconfigService::GetAllTypeInterfaceConfig(const std::string &strPipeName, int iNeId, EM_TYPE_FUNCTION emType, bool bMongo)
{
	try{
		// TODO: 在此添加额外的初始化代码
#if NOT_LONG_CONNECT
		if (bIfNeedInit)
		{
			if (!neconfig::client::IsInitialize()){
				if (!neconfig::client::Initialize()){

					if(!bMongo){
						OTNM2000PipeClient oPipeClient(strPipeName);
						char* pTempJson = "{\"errorCode\":\"104\"}";
						oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));	
					}			
					WriteLog("GetAllTypeInterfaceConfig Initialize 104");
					return 0;
				}
			}
		}
#endif

		int iNeType = irit::GetNeTypeOfNeFromBoardType(iNeId);
		if (irit::IsIPRAN8000Ne(iNeType)){// ok

			if (emType == EM_CONFIG_VE){

				GetInterfaceConfigVEPARSE(strPipeName, iNeId, EM_TYPE_IPRAN8000Ne, bMongo);
			}
			else if (emType == EM_CONFIG_ETHER_NET){

				GetInterfaceConfigEtherNetPARSE(strPipeName, iNeId, EM_TYPE_IPRAN8000Ne, bMongo);
			}
			else if(emType == EM_GETCLOCKCONFIGINTERFACECONFIG){
				GetClockConfigInterfaceConfig(strPipeName, iNeId, EM_TYPE_IPRAN8000Ne, bMongo);
			}
		}
		else if (irit::IsIPRANNe(iNeType)){// 没有使能的参数

			if (emType == EM_CONFIG_VE){// VE,没有找到这种类型的VLAN_TRACKING;

				GetInterfaceConfigVEPARSE(strPipeName, iNeId, EM_TYPE_IPRANNe, bMongo);
			}
			else if (emType == EM_CONFIG_ETHER_NET){

				GetInterfaceConfigEtherNetPARSE(strPipeName, iNeId, EM_TYPE_IPRANNe, bMongo);
			}
			else if(emType == EM_GETCLOCKCONFIGINTERFACECONFIG){
				GetClockConfigInterfaceConfig(strPipeName, iNeId, EM_TYPE_IPRANNe, bMongo);
			}
		}
		else if (irit::IsPOTSNe(iNeType)){ 

			if (emType == EM_CONFIG_VE){// VE,暂时没找到这种类型;

				GetInterfaceConfigVEPARSE(strPipeName, iNeId, EM_TYPE_POTSNe, bMongo);
			}
			else if (emType == EM_CONFIG_ETHER_NET){

				GetInterfaceConfigEtherNetPARSE(strPipeName, iNeId, EM_TYPE_POTSNe, bMongo);
			}
			else if(emType == EM_GETCLOCKCONFIGINTERFACECONFIG){
				GetClockConfigInterfaceConfig(strPipeName, iNeId, EM_TYPE_POTSNe, bMongo);
			}
		}
		else{

			if(!bMongo){
				OTNM2000PipeClient oPipeClient(strPipeName);
				char* pTempJson = "{\"errorCode\":\"105\"}";
				oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));
			}
			else{

				bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));	
				BCON_APPEND(pKey, "errorCode", BCON_INT32(105));	
				string strTableName = "";
				if (emType == EM_CONFIG_VE){// VE,暂时没找到这种类型;

					strTableName = strTABLE_ve;
				}
				else if (emType == EM_CONFIG_ETHER_NET){

					strTableName = strTABLE_ether;
				}
				else if(emType == EM_GETCLOCKCONFIGINTERFACECONFIG){
					strTableName = strTABLE_clock;
				}

#if DEFINE_MONGO_INSERT
				if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTableName.c_str(), pKey)){
					// log新增数据失败；					
					char bufLog[512]="";			
					sprintf(bufLog, "GetAllTypeInterfaceConfig Failure:%d;table:%s\n", iNeId, strTableName.c_str());
					WriteLog(bufLog);
				}
#endif
				bson_free (pKey);
			}
		}
#if NOT_LONG_CONNECT
		if (bIfNeedInit)
		{
			if (neconfig::client::IsInitialize()){
				neconfig::client::UnInitialize();
			}
		}
#endif
	}catch(...){
		WriteLog("GetAllTypeInterfaceConfig catch error!");
		if(m_nCatchErrorCnt++ >= 3){
			g_bRestartNeedRestart = true;
			g_bErrorCatchOrHandle = true;
			g_bStopConfigMongoDBTheard = true;
			g_bRestart = true;
		}
	}
	return false;
}

void OTNM2000GetNeconfigService::DropAllTable()
{ 
	if (emClassType == EM_TYPE_CONFIG){

		if (strTABLE_lag.empty()){// 删除数据库;
			m_MongoDBOperator.DropPipDBTable(m_MongoDBOperator.m_strTableName.c_str());
		}
		else{	
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_lag.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_ether.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_ve.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_clock.c_str());
		}
	}
	else if (emClassType == EM_TYPE_NESTATUS){

		if (strTABLE_NeStatus.empty()){// 删除数据库;
			m_MongoDBOperator.DropPipDBTable(m_MongoDBOperator.m_strTableName.c_str());
		}
		else{	
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_NeStatus.c_str());			
		}
	}
	else if(emClassType == EM_TYPE_CIRCUS){

		if (strTABLE_ProtectPair_data.empty()){// 删除数据库;

			m_MongoDBOperator.DropPipDBTable(m_MongoDBOperator.m_strTableName.c_str());
		}else{// 删除数据库表；

			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_Pw.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_Tunnel.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_ProtectPair.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_L2vpn.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_L3vpn.c_str());	
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_RingBandingTunnel.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_PATH.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_PATHINFO.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_FLOW.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_Ring.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_Ring_data.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_Pw_data.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_Tunnel_data.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_ProtectPair_data.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_L2vpn_data.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_L3vpn_data.c_str());	
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strNeNameRef.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strBoardNameRef.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_Och.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_Och_data.c_str());

			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_Oms.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_Oms_data.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_Ots.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_Ots_data.c_str());

			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_oduk.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_oduk_data.c_str());

			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_client.c_str());
			m_MongoDBOperator.DropTable(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_client_data.c_str());
		}
	}
}

bool OTNM2000GetNeconfigService::GetClockStatueInterfaceConfig(std::string strPipeName, int iNeId)
{
	OTNM2000PipeClient oPipeClient(strPipeName);
	try{
#if NOT_LONG_CONNECT
		if (!neconfig::client::IsInitialize()){ // 初始化判断没有用，总是会执行；
			if (!neconfig::client::Initialize()){
				OTNM2000PipeClient oPipeClient(strPipeName);
				char* pTempJson = "{\"errorCode\":\"104\"}";						
				oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));
				return false;
			}
		}
#endif
		ClockState stClockState;
		if (0 == otnm::busclient::COtnmApiProvider::Instance()->GetNEStatusApiProvider()->SynGetClockState(stClockState, iNeId, 10)){
			// 默认是60s超时时间；
			Json::Value rRoot;

			rRoot["SRCSlotAddr"] = Json::Value(stClockState.m_strSRCSlotAddr.c_str());
			rRoot["WorkState"] = Json::Value(stClockState.m_iWorkState);
			rRoot["ExtClk1OutputState"] = Json::Value(stClockState.m_iExtClk1OutputState);
			rRoot["ExtClk2OutputState"] = Json::Value(stClockState.m_iExtClk2OutputState);
			rRoot["ExtClk3OutputState"] = Json::Value(stClockState.m_iExtClk3OutputState);
			rRoot["CurrentSlot"] = Json::Value(stClockState.m_strCurrentSlot.c_str());
			rRoot["CurrentCard"] = Json::Value(stClockState.m_strCurrentCard.c_str());
			rRoot["CurrentPort"] = Json::Value(stClockState.m_strCurrentPort.c_str());
			rRoot["SourceType"] = Json::Value(stClockState.m_iSourceType);
			rRoot["SourceState"] = Json::Value(stClockState.m_iSourceState);
			rRoot["ClockOutputSlot"] = Json::Value(stClockState.m_strClockOutputSlot.c_str());
			rRoot["ClockOutputCard"] = Json::Value(stClockState.m_strClockOutputCard.c_str());
			rRoot["ClockOutputPort"] = Json::Value(stClockState.m_strClockOutputPort.c_str());
			rRoot["ClockSourceSSM"] = Json::Value(stClockState.m_iClockSourceSSM);

			char* pTempJson = GetJsonStringByJsonValue(&rRoot);
			if (pTempJson != NULL){
				OTNM2000PipeClient oPipeClient(strPipeName);
				oPipeClient.SendByteByPipe(pTempJson, strlen(pTempJson));
				//		printf(pTempJson);
				delete [] pTempJson;	
				pTempJson = NULL;
			}		
		}
#if NOT_LONG_CONNECT
		if (neconfig::client::IsInitialize()){
			neconfig::client::UnInitialize();   //卸载时，句柄有问题。
		}
#endif
	}catch(...){
		WriteLog("GetClockStatueInterfaceConfig SynGet catch error!");
		if(m_nCatchErrorCnt++ >= 3){
			g_bRestartNeedRestart = true;
			g_bErrorCatchOrHandle = true;
			g_bStopConfigMongoDBTheard = true;
			g_bRestart = true;
		}
	}

	return true;
}

void OTNM2000GetNeconfigService::GetConfigToMongoDB(const string &strPipName)
{/// 写mongo的分支；
	try{	
		int nTimes = 0;
		int nLen = vctGetConifg.size();
		for (int i = 0; i <nLen; ++i){

#if 0
			if (i == 1){ // 测试重启,继续接上一次job；
				g_bRestartNeedRestart = true;
				g_bErrorCatchOrHandle = true;
				g_bStopConfigMongoDBTheard = true;
				g_bRestart = true;
			}

#else
			if (IfHandleOutOfRange()){
				WriteLog("restartoutputotnm2000 cause HandleCount >= 650 from GetConfigToMongoDB");
				g_bRestartNeedRestart = true;
				g_bErrorCatchOrHandle = true;
				g_bRestart = true;// 接收重启指令；		
				g_bStopConfigMongoDBTheard = true;		
			}
#endif

			if (g_bErrorCatchOrHandle){//且非正常结束配置任务； 
				if (g_bStopConfigMongoDBTheard){// 结束某次任务；
					// 把剩余的任务保存在表中，方便下次继续；
					EasySaveAllTmpConfigFile(vctGetConifg, i, true);
					break;
				}
			}
			else{
				if (g_bStopConfigMongoDBTheard){// 结束某次任务；
					break;
				}
			}

			if (i==0){
				bIfNeedInit = true; // 第一次调用，始终初始化；
			}
			else{// 每nFreqInit次，调用一次初始化；
				bIfNeedInit = ((i%nFreqInit) == 0); // 每nFreqInit个网元，调用一次初始化； bug:每初始化一次，句柄泄漏一次；
			}
			if (bIfNeedInit){
				if(nTimes++ >= 5){
					double fProcess = 0;
					char bufProcess[100] = "";

					if((nJobVctGetConfigLen > 0) && (nJobVctGetConfigLen >= nLen)){
						fProcess = (double)(nJobVctGetConfigLen - (nLen - i - 1))/nJobVctGetConfigLen;					
						sprintf(bufProcess, "Config len=%d; process:%f", nLen, fProcess);								
					}
					else{
						fProcess = (double)(i)/nLen;						
						sprintf(bufProcess, "Config len=%d; process:%f", nLen, fProcess);						
					}

					string strDetail = bufProcess;
					UpdateTaskID(fProcess, bufProcess);	

					nTimes = 0;
				}
			}

			stConfigGet &tmpOne = vctGetConifg[i];
#if 1
			if (tmpOne.eFunType == EM_CONFIG_ALL){// 只取配置；

				GetLagInterfaceConfig(strPipName, tmpOne.id, true);
				//		bIfNeedInit = false; // 防止连续初始化多次； =》 省略后面几次初始化，会导致数据取不出来；
				GetAllTypeInterfaceConfig(strPipName, tmpOne.id, EM_CONFIG_VE, true);
				GetAllTypeInterfaceConfig(strPipName, tmpOne.id, EM_CONFIG_ETHER_NET, true);
			}		
			else if (tmpOne.eFunType == EM_CONFIG_CLOCK){// 只取clock配置；

				GetAllTypeInterfaceConfig(strPipName, tmpOne.id, EM_GETCLOCKCONFIGINTERFACECONFIG, true);
			}
			else if (tmpOne.eFunType == EM_CONFIG_CLOCK_AND_ALL){// 两者都取；

				GetLagInterfaceConfig(strPipName, tmpOne.id, true);
				//		bIfNeedInit = false; // 防止连续初始化多次； =》 省略后面几次初始化，会导致数据取不出来；
				GetAllTypeInterfaceConfig(strPipName, tmpOne.id, EM_CONFIG_VE, true);
				GetAllTypeInterfaceConfig(strPipName, tmpOne.id, EM_CONFIG_ETHER_NET, true);
				GetAllTypeInterfaceConfig(strPipName, tmpOne.id, EM_GETCLOCKCONFIGINTERFACECONFIG, true);
			}
#endif
			GetWarningPingBi(strPipName, tmpOne.id);
		}

		if (g_bStopConfigMongoDBTheard && g_bErrorCatchOrHandle){// 结束某次任务；  //且非正常结束配置任务；
			IfContinueRestartLastJob(1);	
		}
		else{
			IfContinueRestartLastJob(0);
			EasySaveAllTmpConfigFile(vctGetConifg, vctGetConifg.size(), true);
		}

		vctGetConifg.clear();
		// 批量取之后，bIfNeedInit的值总是false； =》 导致单独接口取不出来；
		bIfNeedInit = true;   // 防止测试时，单独取不出来；

		if (nLen == 0){
			IfContinueRestartLastJob(2);
		}

	}
	catch(...){
		WriteLog("OTNM2000GetNeconfigService::GetConfigToMongoDB catch error!");
	}
}

///////////////////   各种版本网管 这段必须一致，否则数据错误 /////////////////////
enum NESET_TYPE					//类型：告警屏蔽，性能屏蔽
{	
	NESET_NULL_TYPE = 0,
	NESET_ALARM_MASK, 
	NESET_PM_MASK, 
	NESET_ALARM_INHIBIT, 
};

enum NESETDEVICETYPE				//网元配置类型，IPRAN，POTS
{	
	NESETDEVICE_OTHER = 0, 
	NESETDEVICE_IPRAN,  
	NESETDEVICE_POTS, 
};

WORD GetNeBlockIDByType(int iDeviceType, int iNeSetType)
{
	if (NESETDEVICE_IPRAN == iDeviceType)
	{
		if (NESET_ALARM_MASK == iNeSetType)
		{
			return IPRAN_ALARM_MASK_BLOCK_ID;
		}
		else if (NESET_PM_MASK == iNeSetType)
		{
			return IPRAN_PM_MASK_BLOCK_ID;
		}
		else 
		{
			return 0;
		}
	}
	else if (NESETDEVICE_POTS == iDeviceType)
	{
		if (NESET_ALARM_MASK == iNeSetType)
		{
			return POTS_ALARM_MASK_BLOCK_ID;
		}
		else if (NESET_PM_MASK == iNeSetType)
		{
			return POTS_PM_MASK_BLOCK_ID;
		}
		else if (NESET_ALARM_INHIBIT == iNeSetType)
		{
			return POTS_ALARM_INHIBIT_BLOCK_ID;
		}
		else 
		{
			return 0;
		}
	}
	return 0;
}

struct NeSetBoardCodeStr
{
	WORD wSetCode;
	CString strCodeCName;
	CString strCodeEName;
	NeSetBoardCodeStr()
	{
		wSetCode = 0;
		strCodeCName = "";
		strCodeEName = "";
	}

	NeSetBoardCodeStr& operator = (const NeSetBoardCodeStr& stCopy)
	{
		wSetCode = stCopy.wSetCode;
		strCodeCName = stCopy.strCodeCName;
		strCodeEName = stCopy.strCodeEName;
		return *this;
	}
};

typedef map<WORD, NeSetBoardCodeStr> NeMaskBoardCodeStrMap;
map<int, NeMaskBoardCodeStrMap> m_oBoardAlarmCodeStrMap;
map<int, NeMaskBoardCodeStrMap> m_oBoardPmCodeStrMap;

void GetBoardCodeStrMap(DWORD dwBoardID, int iCodeType, NeMaskBoardCodeStrMap &oBoardCodeStrMap)
{
	XBOARD_PTR pBoard = GET_XBOARD(dwBoardID);
	if (NULL == pBoard)
	{
		return;
	}

	int iBoardType = pBoard->GetBoardType();

	map<int, NeMaskBoardCodeStrMap>::iterator iterator;

	if (NESET_PM_MASK == iCodeType)
	{
		iterator = m_oBoardAlarmCodeStrMap.find(iBoardType);
		if (iterator == m_oBoardAlarmCodeStrMap.end())
		{
			XPMTYPETABLE oPmTypes;
			irit::GetPMTypes(irit::GetCurrentProjectId(), dwBoardID, oPmTypes);

			for (int i = 0; i < oPmTypes.GetSize(); ++i)
			{
				XPMTYPE stPmType = oPmTypes.GetAt(i);

				NeSetBoardCodeStr stNeSetBoardCodeStr;
				stNeSetBoardCodeStr.wSetCode = stPmType.shProtocolCode;
				stNeSetBoardCodeStr.strCodeCName = CString(stPmType.cname);
				stNeSetBoardCodeStr.strCodeEName = CString(stPmType.ename);

				oBoardCodeStrMap.insert(make_pair(stNeSetBoardCodeStr.wSetCode, 
					stNeSetBoardCodeStr));
			}
			m_oBoardAlarmCodeStrMap.insert(make_pair(iBoardType, oBoardCodeStrMap));
		}
		else 
		{
			oBoardCodeStrMap.clear();
			oBoardCodeStrMap = iterator->second;
		}
	}
	else if (NESET_ALARM_MASK == iCodeType)
	{
		iterator = m_oBoardPmCodeStrMap.find(iBoardType);
		if (iterator == m_oBoardPmCodeStrMap.end())
		{
			XALARMTYPETABLE oAlarmTypes;
			irit::GetAlarmTypes(irit::GetCurrentProjectId(), dwBoardID, oAlarmTypes);

			for (int i = 0; i < oAlarmTypes.GetSize(); ++i)
			{
				XALARMTYPE stAlarmType = oAlarmTypes.GetAt(i);


				NeSetBoardCodeStr stNeSetBoardCodeStr;
				stNeSetBoardCodeStr.wSetCode = stAlarmType.shProtocolCode;
				stNeSetBoardCodeStr.strCodeCName = CString(stAlarmType.cname);
				stNeSetBoardCodeStr.strCodeEName = CString(stAlarmType.ename);

				oBoardCodeStrMap.insert(make_pair(stNeSetBoardCodeStr.wSetCode, 
					stNeSetBoardCodeStr));
			}
			m_oBoardPmCodeStrMap.insert(make_pair(iBoardType, oBoardCodeStrMap));
		}
		else 
		{
			oBoardCodeStrMap.clear();
			oBoardCodeStrMap = iterator->second;
		}
	}
}

///////////////////   各种版本网管 这段 必须一致，否则数据错误 end /////////////////////

void OTNM2000GetNeconfigService::GetXMLVaule(string &strVaule, int nId, bool bType)
{
	try{
		char szPath[MAX_PATH]="";  
		GetModuleFileNameA(NULL, szPath, MAX_PATH);
		string tempPath = szPath;
		int iIndex = tempPath.find_last_of('\\');
		string str_MoudlePath = tempPath.substr(0, iIndex + 1);
#if 0
		GetprocessPath();
		string str_MoudlePath = g_strProcessPath;
#endif
		if (bType){
			str_MoudlePath += "..\\ini\\ObjectGroupRule.xml";
		}
		else{
			str_MoudlePath += "..\\ini\\LayerRateManagement.xml";
		}

		DLL_DOM::CXmlDom oDom;
		if (oDom.Load(DLL_DOM::STRING(str_MoudlePath.c_str())))
		{	
			//		int iId = strtol(("0x2f"), NULL, 16);
			DLL_DOM::CXmlNode rowNode = oDom.GetElementById(nId);
			if (!rowNode.Exist()){
				return;
			}

			DLL_DOM::STRING strAttr;
			rowNode.GetAttribute("sub_cname", strAttr);

			char *pstrVaule = strAttr.WChar2Ansi();
			strVaule = pstrVaule;
			delete [] pstrVaule;
		}
	}catch(...){
		WriteLog("DLL_DOM::CXmlDom catch error!");
	}
}

void OTNM2000GetNeconfigService::GetWarningPingBi(const string &strPipName, int iNeId)
{
	try{
		int m_iNeCommondType = 1;   // => D:\OTNM\ui\ini\nemask.ini 
		int iDeviceType = 0;

		int iNeSetType = NESET_ALARM_MASK;  // =>  D:\OTNM\src\Client\MANS\NeSetStruct.h

		////////  根据网元id，确定网元类型，再确定设备类型；
		int nNeType = irit::GetNeTypeOfNeFromBoardType(iNeId);
		if(irit::IsIPRANNe(nNeType)){
			iDeviceType = TransDeviceType_IPRAN;
		}
		else if(irit::IsPOTSNe(nNeType)
			|| irit::IsOnlyIPRAN690Ne(nNeType))
		{
			iDeviceType = TransDeviceType_POTS;
		}
		else{
			iDeviceType = TransDeviceType_NULL;
		}
		////////  根据网元id，确定网元类型，再确定设备类型；  end；

		// 根据设备类型，确定以什么方式读取数据。
		char szPath[MAX_PATH]="";  
		GetModuleFileNameA(NULL, szPath, MAX_PATH);
		string tempPath = szPath;
		int iIndex = tempPath.find_last_of('\\');
		string oStrIniFile = tempPath.substr(0, iIndex + 1);
		oStrIniFile += "..\\ini\\NeMask.ini";  // D:\OTNM\ui\ini\NeMask.ini
#if 0
		GetprocessPath();
		string oStrIniFile = g_strProcessPath + "..\\ini\\NeMask.ini";
#endif
		if (NESETDEVICE_IPRAN == iDeviceType)
		{
			m_iNeCommondType = GetPrivateProfileInt("NEMASK", "IPRANNEMASKTYPE",  
				1, oStrIniFile.c_str());
		}
		else if (NESETDEVICE_POTS == iDeviceType)
		{
			m_iNeCommondType = GetPrivateProfileInt("NEMASK", "POTSNEMASKTYPE",  
				1, oStrIniFile.c_str());
		}
		// 根据设备类型，确定以什么方式独读取数据。 end;

		WORD wBlockID = GetNeBlockIDByType(iDeviceType, iNeSetType);  // D:\OTNM\src\Client\MANS\NeSetCommondProcess.h

		bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));		
		if (NESET_ALARM_MASK == iNeSetType || NESET_PM_MASK == iNeSetType)
		{
			vector<NeSetMask_Board_PBProtocol> arNeSetMask_Board;  // 获取网元告警的结构数据；
			if(ReadNeMaskFromDB(iNeId, iDeviceType, wBlockID, iNeSetType, arNeSetMask_Board, m_iNeCommondType)){
				BCON_APPEND(pKey, "errorCode", BCON_INT32(0));
				BCON_APPEND(pKey, "errorMsg", "ok");

				char buf[100] = "";
				bson_t childSlotsDoc;
				bson_init(&childSlotsDoc);
				for(int i=0; i < arNeSetMask_Board.size(); i++){ // 解析结构数据；

					NeSetMask_Board_PBProtocol &tmpNeSetMask = arNeSetMask_Board[i];

					bson_t onechildSlots, onechildSlotsDoc;
					bson_init(&onechildSlots);
					bson_init(&onechildSlotsDoc); // boardName   boardId  

					BCON_APPEND(&onechildSlots, "slotNo", BCON_INT32((int)tmpNeSetMask.wBoatdSlot)); // 槽id

					/*		
					printf("### %d,%d,%d,%d\n", tmpNeSetMask.wBoatdSlot, tmpNeSetMask.wBoardGroupNo, 
					tmpNeSetMask.dwMaskItemNumber, tmpNeSetMask.dwBoardType, (int)tmpNeSetMask.bMaskBoardAll);
					*/
					int nTmpBoardId = 0;
					string strTmpSlotName = "";  
					if(!GetBoardFromKnowMsg(nTmpBoardId, strTmpSlotName, 
						iNeId, tmpNeSetMask.wBoardGroupNo, tmpNeSetMask.dwBoardType, tmpNeSetMask.wBoatdSlot)){
							// 没找到指定的单盘id；  =》 根据已知的网元/组id/槽位等信息，获取对应的单盘id；
						//	continue;
					}

					string strCurName = string_To_UTF8(strTmpSlotName);	 // 槽 名称；									
					BCON_APPEND(&onechildSlots, "slotName", strCurName.c_str());
					BCON_APPEND(&onechildSlots, "boardId", BCON_INT32(nTmpBoardId)); // 槽id

					m_oBoardAlarmCodeStrMap.clear();
					m_oBoardPmCodeStrMap.clear();

					NeMaskBoardCodeStrMap oBoardCodeStrMap;  // 根据单板id，获取netmask等的中英文告警说明信息；
					GetBoardCodeStrMap(nTmpBoardId, iNeSetType, oBoardCodeStrMap);

					bson_t SlotsItems, SlotsItemsDoc;
					bson_init(&SlotsItemsDoc);
					bson_init(&SlotsItems);
					for (int j=0; j < tmpNeSetMask.arMaskItem.size(); j++)
					{// 解析告警屏蔽的子项信息；
						bson_t oneSlotsItems;
						bson_init(&oneSlotsItems);

						NeSetMask_Board_Item_PBProtocol &tmpNeSetMaskItemMsg = tmpNeSetMask.arMaskItem[j];													

						BCON_APPEND(&oneSlotsItems, "bMaskAllCode", BCON_INT32(tmpNeSetMaskItemMsg.bMaskAllCode));

						/*	printf("**** %d,%d,%d,%d,%d,%d\n",  tmpNeSetMaskItemMsg.dwItemID,tmpNeSetMaskItemMsg.bMaskAllLineNo,
						tmpNeSetMaskItemMsg.bMaskAllLineNo,
						tmpNeSetMaskItemMsg.dwLineNoNumber,tmpNeSetMaskItemMsg.bMaskAllCode,tmpNeSetMaskItemMsg.dwMaskCodeNumber);*/

						//char bufTmp[256]="";
						if(tmpNeSetMaskItemMsg.arNeSetLineNo.size() > 0) // size == 1;
						{
							NeSet_LineNo_PBProtocol &tmpNeSet = tmpNeSetMaskItemMsg.arNeSetLineNo[0];

							/*char testBuf[256]="";
							sprintf(testBuf, "(min:%s max:%s) ", tmpNeSet.strMin.c_str(), tmpNeSet.strMax.c_str());
							strcat(bufTmp, testBuf);*/

							// 0006 002f 01 01   0006 002f 01 04
							if ((tmpNeSet.strMin.length() == 12)
								&& (tmpNeSet.strMax.length() == 12))
							{
								string strMin(tmpNeSet.strMin, tmpNeSet.strMin.length()-2, 2);
								string strMax(tmpNeSet.strMax, tmpNeSet.strMax.length()-2, 2);
								int nMin = strtol(strMin.c_str(), NULL, 10);
								int nMax = strtol(strMax.c_str(), NULL, 10);
								BCON_APPEND(&oneSlotsItems, "maskMinCode", BCON_INT32(nMin));
								BCON_APPEND(&oneSlotsItems, "maskMaxCode", BCON_INT32(nMax));

								string strLineFirstNum(tmpNeSet.strMin, 0, 4), strLineMidNum(tmpNeSet.strMin, 4, 4);
								string strLineFirst="", strLineMid="";
								int nLineFirst = strtol(strLineFirstNum.c_str(), NULL, 16); // ObjectGroupRule.xml        0006 => 面板口
								int nLineMid= strtol(strLineMidNum.c_str(), NULL, 16); // LayerRateManagement.xml;   002f => phy_o
								GetXMLVaule(strLineFirst, nLineFirst, true);
								GetXMLVaule(strLineMid, nLineMid, false);

								string strLineMsg = strLineFirst + "--" + strLineMid;
								string strCurName = string_To_UTF8(strLineMsg);										
								BCON_APPEND(&oneSlotsItems, "lineType", strCurName.c_str());									
							}
							else{
								BCON_APPEND(&oneSlotsItems, "maskMinCode", tmpNeSet.strMin.c_str());
								BCON_APPEND(&oneSlotsItems, "maskMaxCode", tmpNeSet.strMax.c_str());
								BCON_APPEND(&oneSlotsItems, "lineType", tmpNeSet.strMin.c_str());
							}			
						}
						//	printf("\t%s\n", bufTmp);

						bson_t lineTypeBson;
						bson_init(&lineTypeBson);
						bson_t lineTypeBsonDoc;
						bson_init(&lineTypeBsonDoc);

						if(tmpNeSetMaskItemMsg.bMaskAllCode  == 1){// 全部屏蔽代码

							bson_t tmpOnelineTypeBson;
							bson_init(&tmpOnelineTypeBson);

							string strTmp = "全部代码";
							string strCurName = string_To_UTF8(strTmp);	
							BCON_APPEND(&tmpOnelineTypeBson, "cName", strCurName.c_str());
							BCON_APPEND(&tmpOnelineTypeBson, "eName", "All Code");
							BCON_APPEND(&tmpOnelineTypeBson, "code", BCON_INT32(0));
							bson_append_document(&lineTypeBsonDoc, "0", -1, &tmpOnelineTypeBson);
							bson_destroy(&tmpOnelineTypeBson);
							bson_destroy(&tmpOnelineTypeBson);								
						}
						else{ // 部分屏蔽代码；  eName / cName

							for (int z=0; z<tmpNeSetMaskItemMsg.arNeMaskCode.size(); z++) // size >= 1;
							{// vector<WORD> arNeMaskCode;  => 和数据库不是一一对应； =》 GetBoardCodeStrMap  里面获取对应关系；
								//		char testBuf[256]="";
								//		sprintf(testBuf, "(%d-%d) ", z, (int)tmpNeSetMaskItemMsg.arNeMaskCode[z]);
								//		strcat(bufTmp2, testBuf);
								bson_t tmpOnelineTypeBson;
								bson_init(&tmpOnelineTypeBson);

								WORD tmpOneCode = tmpNeSetMaskItemMsg.arNeMaskCode[z];
								NeMaskBoardCodeStrMap::iterator iterCodeStrMap = oBoardCodeStrMap.find(tmpOneCode);
								if (iterCodeStrMap != oBoardCodeStrMap.end())
								{
									CString &strTmpName = oBoardCodeStrMap[tmpOneCode].strCodeCName;
									CString &strTmpName2 = oBoardCodeStrMap[tmpOneCode].strCodeEName;

									string strTmp = strTmpName.GetBuffer(0);
									string strCurName = string_To_UTF8(strTmp);	
									BCON_APPEND(&tmpOnelineTypeBson, "cName", strCurName.c_str());
									BCON_APPEND(&tmpOnelineTypeBson, "eName", strTmpName2.GetBuffer(0));									
								}
								else{
									BCON_APPEND(&tmpOnelineTypeBson, "cName", "");
									BCON_APPEND(&tmpOnelineTypeBson, "eName", "");
								}
								BCON_APPEND(&tmpOnelineTypeBson, "code", BCON_INT32((int)tmpOneCode));

								itoa(z, buf, 10);
								bson_append_document(&lineTypeBsonDoc, buf, -1, &tmpOnelineTypeBson);
								bson_destroy(&tmpOnelineTypeBson);
							}
						}

						bson_append_array(&lineTypeBson, "lineTypeCodeArray", -1, &lineTypeBsonDoc);
						bson_destroy(&lineTypeBsonDoc);

						bson_append_document(&oneSlotsItems, "lineTypeCode", -1, &lineTypeBson);
						bson_destroy(&lineTypeBson);		

						itoa(j, buf, 10);
						bson_append_document(&SlotsItemsDoc, buf, -1, &oneSlotsItems);
						bson_destroy(&oneSlotsItems);												
					}

					bson_append_array(&SlotsItems, "slotsitemsarray", -1, &SlotsItemsDoc);
					bson_destroy(&SlotsItemsDoc);

					bson_append_document(&onechildSlots, "slotsItems", -1, &SlotsItems);
					//	BCON_APPEND(&onechildSlots, "SlotsItems", &SlotsItems);
					bson_destroy(&SlotsItems);

					itoa(i,buf, 10);
					bson_append_document(&childSlotsDoc, buf, -1, &onechildSlots);
					bson_destroy(&onechildSlots);
				}

				bson_append_array(pKey, "slotNum", -1, &childSlotsDoc);
				bson_destroy(&childSlotsDoc);
			}
			else{// ReadNeMaskFromDB fail!;
				BCON_APPEND(pKey, "errorCode", BCON_INT32(110));
				BCON_APPEND(pKey, "errorMsg", "ReadNeMaskFromDB fail");
			}				
		}
		else{// type fail!
			BCON_APPEND(pKey, "errorCode", BCON_INT32(111));
			BCON_APPEND(pKey, "errorMsg", "Get NeSetType fail");
		}

#if DEFINE_MONGO_INSERT
		if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTableConfigNetWarning.c_str(), pKey)){

			char bufLog[512]="";			
			sprintf(bufLog, "OTNM2000GetNeconfigService::GetWarningPingBi neID:%d;", iNeId);
			WriteLog(bufLog);	
		}
#endif	
		bson_destroy(pKey);

	}catch(...){
		char buf[256] = "";
		sprintf(buf, "OTNM2000GetNeconfigService::GetWarningPingBi neID:%d; catch error", iNeId);
		WriteLog(buf);
	}
}



void OTNM2000GetNeconfigService::GetPortNameFromSNC(string &strOutPortName,int iNeId, int iBoardId, int nInPortNo, int nInPortLevel)
{
	try{
	
		char buf2Cmp[200] = "";
		sprintf(buf2Cmp, "%d-%d-%d-%d", iNeId, iBoardId, nInPortNo, nInPortLevel);  // 组合起来，可能会有几百M内存。

		map<string, string>::iterator iterResult = mapNeBoardPortName.find(buf2Cmp);
		if (iterResult != mapNeBoardPortName.end()){
		//	int xx = mapNeBoardPortName.size();
			strOutPortName = mapNeBoardPortName[buf2Cmp];		
			mapNeBoardPortName.erase(iterResult); // 去掉已经存在的，防止内存超标。
		//	int xxx = mapNeBoardPortName.size();
			return ;
		}

		int bAPIStateRight = 0;
		std::list<XC_PORT> lstPort;  // 从设备中查出所有的port信息；
		ERROR_CODE_EX eCode = SNC_GetBoardPorts(m_hSess, iNeId, iBoardId, PortRate_All/* EPortRate ePortRate */, lstPort);
		if (ERR_OK == eCode){
			// ok

		}else{
			if(ConnectNetClient()==0){
				ERROR_CODE_EX eCode = SNC_GetBoardPorts(m_hSess, iNeId, iBoardId, PortRate_All/* EPortRate ePortRate */, lstPort);
				if (ERR_OK == eCode){
					// ok
				}
				else{ 
					bAPIStateRight = -1;			
				}
			}
			else{
				bAPIStateRight = -2;
			}
		}

		if (bAPIStateRight == -1){
			char buflog[512] = "";
			sprintf(buflog,"GetAsonPOtnSrcManage Failure:nodeid=%d;boardid:%d; ReSNC_GetBoardPorts fail!\n", iNeId, iBoardId);
			WriteLog(buflog);
			strOutPortName="";
			return;
		}
		else if (bAPIStateRight == -2){
			char buflog[512] = "";
			sprintf(buflog,"GetAsonPOtnSrcManage Failure:nodeid=%d;boardid:%d; ReConnectNetClient fail!\n", iNeId, iBoardId);
			WriteLog(buflog);
			strOutPortName = "";
			return ;
		}

		for(std::list<XC_PORT>::iterator iter = lstPort.begin(); iter != lstPort.end(); iter++){

			if (g_bStopMongoDBTheard){ // 发新任务时，快速结束旧任务；
				WriteLog("GetAsonPOtnSrcManage StopMongoDBTheard => GetPortNameFromSNC");
				break;
			}

			XC_PORT &TmpPort = *iter;
			string strPortName = TmpPort.m_sPortName;  // L_PORT1

			int iPortLevel = TmpPort.m_iPortLevel;
			int iPortNo = TmpPort.m_iPortNo;
			if((iPortLevel == nInPortLevel) && (iPortNo == nInPortNo)){
				strOutPortName = TmpPort.m_sPortName;			
				// return ;
			}else{ // 去掉已经存在的，防止内存超标。
				sprintf(buf2Cmp, "%d-%d-%d-%d", iNeId, iBoardId, iPortNo, iPortLevel);
				mapNeBoardPortName[buf2Cmp] = TmpPort.m_sPortName;
			}
		}
	}catch(...){
		WriteLog("OTNM2000GetNeconfigService::GetPortNameFromSNC catch error");
	}
}

void OTNM2000GetNeconfigService::GetAsonPOtnSrcManage(double fBegin, double fAdd)
{
	try{
		if (g_bStopMongoDBTheard){ // 发新任务时，快速结束旧任务；
			WriteLog("GetAsonPOtnSrcManage StopMongoDBTheard begin");
			return ;
		}

		mapNeBoardPortName.clear();
		if(ConnectNetClient()!=0){
			WriteLog("GetAsonPOtnSrcManage connect client fail");
			return ;
		}

		XPROJECT_PTR pProj = irit::GetXProject(irit::GetCurrentProjectId());
		if (NULL == pProj){
			WriteLog("GetAsonPOtnSrcManage get ne id fail");
			return ;
		}
		WriteLog("GetAsonPOtnSrcManage deal data");

		irit::CSmartPartList lstParts;
		pProj->GetParts(lstParts);
		for (POSITION posPart = lstParts.GetHeadPosition(); posPart != NULL;)
		{
			if (g_bStopMongoDBTheard){  // 发新任务时，快速结束旧任务；
				WriteLog("GetAsonPOtnSrcManage StopMongoDBTheard in parts");
				break;
			}

			XPART_PTR pPart = lstParts.GetNext(posPart);
			if (NULL == pPart){
				continue;
			}
			irit::CSmartNeList lstNes;
			pPart->GetNes(lstNes);
			for (POSITION posNe = lstNes.GetHeadPosition(); posNe != NULL;)
			{
				if (g_bStopMongoDBTheard){  // 发新任务时，快速结束旧任务；
					WriteLog("GetAsonPOtnSrcManage StopMongoDBTheard in nes");
					break;
				}

				XNE_PTR poNe = lstNes.GetNext(posNe);  // 从设备中查出所有ne信息； 
				if (NULL == poNe){
					continue;
				}

				int iNeId = poNe->GetNeId();
			//	int nTmpNeType = poNe->GetNeType();  // 260等标识网元是680还是690等信息；
				CString strNeName = poNe->GetName();  // 网元名称；
				bool bGetData = true;

				bson_t *pKey = BCON_NEW("_id", BCON_INT32(iNeId));
			//	BCON_APPEND(pKey, "NeType", BCON_INT32(nTmpNeType));

				list<XC_OTN_PORT_STATE> lstXCRes;
			
				ERROR_CODE_EX eCode = SNC_PartitionOTNPortRes(m_hSess,iNeId,lstXCRes);
				if (ERR_OK != eCode.iCode){// ptn这个接口容易返回失败。

					char bufErrorLog[256] = "";
					sprintf(bufErrorLog, "neid:%d; MBMPSRV::SNC_PartitionOTNPortRes fail!", iNeId);
					WriteLog(bufErrorLog);
					if(ConnectNetClient()!=0){

						sprintf(bufErrorLog, "neid:%d; MBMPSRV::SNC_PartitionOTNPortRes connect client fail!", iNeId);
						WriteLog(bufErrorLog);
						bGetData = false;
					}
					else{
						eCode = SNC_PartitionOTNPortRes(m_hSess,iNeId,lstXCRes);
						if (ERR_OK != eCode.iCode){

							sprintf(bufErrorLog, "neid:%d; MBMPSRV::SNC_PartitionOTNPortRes ReTry fail!", iNeId);
							WriteLog(bufErrorLog);
							bGetData = false;
						}
					}	
				}

				if (bGetData){

					// 单板名称；
					map<int, string> tmpNeBoardName;
					XDWORDTABLE arBoardId;
					poNe->GetBoards(arBoardId); // 从设备中查出所有单盘信息；
					for (int i = 0; i < arBoardId.GetCount(); ++i){

						if (g_bStopMongoDBTheard){  // 发新任务时，快速结束旧任务；
							WriteLog("GetAsonPOtnSrcManage StopMongoDBTheard in nes board");
							break;
						}

						XBOARD_PTR poBoard = GET_XBOARD(arBoardId[i]);
						if (NULL == poBoard){
							continue;
						}

						int nTmpBoardID = poBoard->GetBoardId();
						CString strBoard = poBoard->GetName(); // 单板名称；
						string strBoardName = strBoard.GetBuffer(0);
						tmpNeBoardName[nTmpBoardID] = strBoardName;
					}
					// 单板名称； end

					BCON_APPEND(pKey, "errorCode", BCON_INT32(0));
					BCON_APPEND(pKey, "errorMsg", "ok");

					bson_t bsonNePortMainDoc; 
					bson_init(&bsonNePortMainDoc); 
					int nIndex = 0;
					int nAllSrcNum = lstXCRes.size();
					for(list<XC_OTN_PORT_STATE>::iterator iter = lstXCRes.begin(); iter != lstXCRes.end(); iter++)
					{
						if (g_bStopMongoDBTheard){  // 发新任务时，快速结束旧任务；
							WriteLog("GetAsonPOtnSrcManage StopMongoDBTheard in list<XC_OTN_PORT_STATE>");
							break;
						}

						if ((nIndex%5) == 0){
							char bufProgess[50] = "";
							double fProgess = ((double)nIndex/nAllSrcNum)*fAdd+fBegin;
							sprintf(bufProgess, "Get SPC resource Progess:%.3f", fProgess);
							string strDetail = bufProgess;
							UpdateTaskID(fProgess, strDetail);
						}

						XC_OTN_PORT_STATE &tmpPortState = *iter;

						bson_t bsonPort; 
						bson_init(&bsonPort);

						string strPortName = "";
						//	string strPortName = TmpPort.m_sPortName;  // L_PORT1
						int iBoardNo = tmpPortState.m_iBoardId;
						int iPortLevel = tmpPortState.m_iPortLevel;
						int iPortNo = tmpPortState.m_iPortNo;						
						GetPortNameFromSNC(strPortName, iNeId, iBoardNo, iPortNo, iPortLevel);  // 查找端口名称；

						int iPortTsIndex = tmpPortState.m_iTSIndex;
						ETSCtrlState eTSCtrlState = tmpPortState.m_eCtrlState;//控制状态
						ETSState	eInState = tmpPortState.m_eInState;//入方向占用状态
						int  nIsOptical = tmpPortState.m_bOptical;
						short shWaveBand = tmpPortState.m_stWaveCodeKey.m_shWaveBand; 
						short shWaveCode = tmpPortState.m_stWaveCodeKey.m_shWaveCode;   

						CString strResName = _T("");
						if (nIsOptical && shWaveBand != 0 && shWaveCode != 0)
						{// XC_CIRCUIT => vector<XC_PATH> => vector<XC_CROSS_ITEM> => XC_RESOURCE（shWaveCode，shWaveBand） => WaveName
							string strWaveName = "";
							GetWaveName(strWaveName, shWaveBand, shWaveCode);

							if (iPortNo <= 0){
								strResName.Format("%s", strWaveName.c_str());
							}
							else{
								strResName.Format("%s-%s", strPortName.c_str(), strWaveName.c_str());
							}
						}
						else if (iPortTsIndex > 0){
							strResName.Format("ODUO_%d", iPortTsIndex);
						}
						else{
							strResName = strPortName.c_str();
						}	

						if (TS_STATE_IDLE == eInState){
							if (TS_CTRL_NMS == eTSCtrlState){
								int xx = 0;
							}
							else if (TS_CTRL_CP == eTSCtrlState){
								int xx = 0;
							}
						}
						else if (TS_STATE_LOCKED == eInState)
						{
							if (TS_CTRL_NMS == eTSCtrlState)
							{
								strResName += "  NMS locked";
							}
							else if (TS_CTRL_CP == eTSCtrlState)
							{
								strResName += "  CP locked";							
							}					
						}
						else if (TS_STATE_WHOLE == eInState
							|| TS_STATE_PART == eInState
							)
						{
							if (TS_CTRL_NMS == eTSCtrlState)
							{
								strResName += "  NMS used";
							}
							else if (TS_CTRL_CP == eTSCtrlState)
							{
								strResName += "  CP used";							
							}
						}
						else if (TS_CP_SHARED == eInState)
						{
							strResName += _T("(Wavelength conflict)");	
						}
						else{

						}

						if(tmpNeBoardName.find(iBoardNo) != tmpNeBoardName.end()){

							BCON_APPEND(&bsonPort, "BoardName", tmpNeBoardName[iBoardNo].c_str());
						}
						else{
							BCON_APPEND(&bsonPort, "BoardName", "");
						}

						BCON_APPEND(&bsonPort, "BoardNo", BCON_INT32(iBoardNo));
						BCON_APPEND(&bsonPort, "PortLevel", BCON_INT32(iPortLevel));
						BCON_APPEND(&bsonPort, "PortNo", BCON_INT32(iPortNo));
						BCON_APPEND(&bsonPort, "PortTsIndex", BCON_INT32(iPortTsIndex));					
						BCON_APPEND(&bsonPort, "PortName", strPortName.c_str());
						BCON_APPEND(&bsonPort, "PortResName", strResName.GetBuffer(0));

						char bufOnePort[20] = "";
						sprintf(bufOnePort, "ITEM_%d", nIndex++);
						bson_append_document(&bsonNePortMainDoc, bufOnePort, -1, &bsonPort);
						bson_destroy(&bsonPort);
					}

					bson_append_array(pKey, "portResArray", -1, &bsonNePortMainDoc);	
					bson_destroy(&bsonNePortMainDoc);
				}
				else{
					BCON_APPEND(pKey, "errorCode", BCON_INT32(112));
					BCON_APPEND(pKey, "errorMsg", "Get ne port spc res msg fail");
				}

#if DEFINE_MONGO_INSERT
				if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLESPCRes.c_str(), pKey)){
					// log新增数据失败；
					//	bIfTableUpdateRight = false;
					//	g_bStopMongoDBTheard = true;  // 如果有数据缺少，则中断此次任务 ；

					WriteLog("Insert spc resource Failure");
				}
#endif
				bson_destroy(pKey);


#if 0
				XDWORDTABLE arBoardId;
				poNe->GetBoards(arBoardId); // 从设备中查出所有单盘信息；
				for (int i = 0; i < arBoardId.GetCount(); ++i){
					XBOARD_PTR poBoard = GET_XBOARD(arBoardId[i]);
					if (NULL == poBoard){
						continue;
					}					
					CString strBoard = poBoard->GetName(); // 单板名称；
					//CString strCTmp = irit::GetXObjectFullName(arBoardId[i]);  // 槽位名称；

					int iBoardId = poBoard->GetBoardId();
					//poBoard->GetBoardType()		

					int bAPIStateRight = 0;
					std::list<XC_PORT> lstPort;  // 从设备中查出所有的port信息；
					ERROR_CODE_EX eCode = SNC_GetBoardPorts(m_hSess, iNeId, iBoardId, PortRate_All/* EPortRate ePortRate */, lstPort);

					for(std::list<XC_PORT>::iterator iter = lstPort.begin(); iter != lstPort.end(); iter++){

						XC_PORT &TmpPort = *iter;
						string strPortName = TmpPort.m_sPortName;  // L_PORT1

					}
				}
#endif
			} // end irit::CSmartNeList lstNes;
		} // end irit::CSmartPartList lstParts;

	//	int xx = mapNeBoardPortName.size();
		mapNeBoardPortName.clear();

		MutiServPlatform::SNC_CloseSession(m_hSess);
		MutiServPlatform::DeInitMSMPClient();

	}catch(...){
		WriteLog("Get SPC Resource fail");
	}
}

void OTNM2000GetNeconfigService::GetLineNoExplain(string &strRetResult, const stBoardStrType &tmpSTBoard, int dwLineNo)
{// => CBoardMaskTreeView::GetLineNoExplain(CString &strRet, DWORD dwLineNo)

	CString strRet = irit::GetPmValueStringEx(irit::GetCurrentProjectId(),
			0, 0, tmpSTBoard.nBoardType, (short)dwLineNo, tmpSTBoard.nBoardID, 1, 0, 0);
	strRetResult = strRet.GetBuffer(0);
}

XALARMTYPETABLE g_oAlarmTypes;  // => OTNM2000GetNeconfigService::GetAlarmCodeString
int g_ndwBoardID = 0;

void OTNM2000GetNeconfigService::GetAlarmCodeString(std::string &strCName, std::string &strEName, int dwBoardID, int alarmCode)
{
	try{
		
		if (dwBoardID != g_ndwBoardID){
			g_oAlarmTypes.RemoveAll();
			if(irit::GetAlarmTypes(irit::GetCurrentProjectId(), dwBoardID, g_oAlarmTypes) < 0){
				strCName = "";
				strEName="";
				return ;
			}
			g_ndwBoardID = dwBoardID;
		}
		
		bool tmpBFindMaskCode = false;
		for (int i = 0; i < g_oAlarmTypes.GetSize(); ++i){
			XALARMTYPE stAlarmType = g_oAlarmTypes.GetAt(i);    // stAlarmType.alarmgrade

	//		printf("code:%d, enname:%s cnname:%s nBoardType:%d shProtocolCode:%d\n", stAlarmType.alarmcode, stAlarmType.ename, stAlarmType.cname,
	//			stAlarmType.nBoardType, (int)stAlarmType.shProtocolCode);

			if (stAlarmType.shProtocolCode == alarmCode){
				strCName = stAlarmType.cname;
				strEName = stAlarmType.ename;
				tmpBFindMaskCode = true;
				break;
			}
		}
		if (!tmpBFindMaskCode){
			strCName = "";
			strEName="";
		}
	}catch(...){
		char buf[100] = "";
		sprintf(buf, "GetAlarmCodeString get name fail: boardId=%d, maskId=%d",dwBoardID,alarmCode);
		WriteLog(buf);
	}
}

void OTNM2000GetNeconfigService::BoardStr2MongoDB()
{
	try{
		for (int i=0; i<m_vctBoardStrType.size(); i++, nCurNumCnt++)
		{
			if (g_bStopMongoDBBoardStrTheard){	 // 加快结束任务时，程序退出。
				WriteLog("BoardStr2MongoDB self stop job\n");
				break;	
			}

			if (nCurNumCnt%5 == 0){
				char bufLog[200] ="";
				sprintf(bufLog, "BoardStr2MongoDB Process: nTotalNumCnt=%d, nCurNumCnt=%d, nRandCnt=%d", nTotalNumCnt, nCurNumCnt, rand());
				if (nTotalNumCnt > 0){
					UpdateTaskID((double)nCurNumCnt/nTotalNumCnt, bufLog);
				}
				else{
					UpdateTaskID((double)nCurNumCnt/(nCurNumCnt+1), bufLog);
				}
			}
			
			bson_t *pKey = BCON_NEW("_id", BCON_INT32(m_vctBoardStrType[i].nBoardID));
			BCON_APPEND(pKey, "callType", BCON_INT32(m_vctBoardStrType[i].nCallType));

			//  GetMyNeedData函数,单盘id如果不存在，函数里面会卡30s左右，并在GetMyNeedData里面抛异常；
			GetMyNeedData(m_vctBoardStrType[i], pKey);

#if DEFINE_MONGO_INSERT
			if(!m_MongoDBOperator.Insert(m_MongoDBOperator.m_strTableName.c_str(), strTABLE_BoardStrPingBi.c_str(), pKey)){
				// log新增数据失败；
				//	bIfTableUpdateRight = false;
				//	g_bStopMongoDBTheard = true;  // 如果有数据缺少，则中断此次任务 ；

				WriteLog("Insert BoardStrPingBi Failure");
			}
#endif
			bson_destroy(pKey);	
		}
		m_vctBoardStrType.clear();
	}catch(...){

		WriteLog("Insert BoardStrPingBi catch error!");
	}
}


#endif
