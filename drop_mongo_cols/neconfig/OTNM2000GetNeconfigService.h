#pragma once
#include <string>
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "mongoc/mongoc.h"

#include "..\\CMongoDBOperator.h"
#include "..\OTNM2000PipeClient.h"

#define  NOT_LONG_CONNECT   1
#define  LONG_CONNECT   0

using namespace std;

#include "MSMPClientAPI.h"

#include "json/json.h"

enum EM_TYPE_FUNCTION{

	EM_CONFIG_NONE,
	EM_CONFIG_VE,
	EM_CONFIG_ETHER_NET,
	EM_GETCLOCKCONFIGINTERFACECONFIG,

	EM_TYPE_IPRAN8000Ne,
	EM_TYPE_IPRANNe,
	EM_TYPE_POTSNe,
};

enum EM_TypeConifGet{
	EM_TYPE_CONFIG, // 
	EM_TYPE_CIRCUS,
	EM_TYPE_NESTATUS,
	EM_CONFIG_ALL, // VE/LAG/TRUCK,
	EM_CONFIG_CLOCK,
	EM_CONFIG_CLOCK_AND_ALL,// EM_CONFIG_CLOCK + EM_CONFIG_CLOCK
	EM_STATUS_NE_MCC,
	EM_STATUS_NE_NORMAL,
	EM_TYPE_BOARDSTR_PINGBI,

};

// 获取端口名称的开关；
#define  PathInfoResource_GetPortName  0


enum eThreadType{

	eProtect=0,
	eL2vpn,
	eL3vpn,
	eRing,
	ePw,
	eTunnel,
	eOts, // oms-ots
	eOms,
	eOch,
	eClient,
	eOduk,
	eCircuits,
	eCircuits_other,
};

struct stThreadUse{

	void *Data;
	eThreadType eType;
};

struct stConfigGet{
	int id;
	EM_TypeConifGet eFunType;
};


typedef DWORD (*FuncCallToDB)( LPVOID lpParam);

enum
{
   PTN_PW,
   PTN_TUNNEL,
   PTN_L2VPN,
};
enum TypeAll
{
	neProtect=0,
	neL2vpn,
	neL3vpn,
	neRing,
	neCircuits,
	nePw,
	neTunnel,
	neOts, 
	neOms,
	neOch,
	neClient,
	neOduk,
	neCircuits_other,
};

struct  stBoardStrType
{
	std::string strHexData;
	int nCallType;
	int nBoardID;
	int nBoardType;
};

struct  stDetailCount
{	
	int  nGetLen;    // => vecCircuits size;
	int  nDBMongoLen;     // 写入mongo的长度；
	int  nDBMongoRefLen;  // 写入mongo的Ref表长度； 
	stDetailCount():nGetLen(0),nDBMongoLen(0),nDBMongoRefLen(0){}
};

struct stDataTotalCount
{
	int  nTotalLen;           // 总条数；
	int  nTotalSendMongo;    //得到的条数
	int  nDBMongoLen;  // 写入了mongo的总条数；
	int  nDBMongoRefLen;  // 写入mongo的Ref表长度；

	// 小类型； =》 （pw/tunnel/oclient/oduk等7个小类型中的某一个）
	//每次分组，获取到的条数和获取结果不一致的情况；
	map<TypeAll,  stDetailCount> mapDetailCount;   // 汇总结果；
	//map<enum,  vector<stDetailCount>> mapDetailCount ; // 每组详情；

	stDataTotalCount():nTotalLen(0),nTotalSendMongo(0),nDBMongoLen(0),nDBMongoRefLen(0){}
};

//
class OTNM2000GetNeconfigService
{
public:
	OTNM2000GetNeconfigService(void);
	OTNM2000GetNeconfigService(const string &pipName, const std::string &strUserName, const std::string &strPassword, const std::string &strIp, unsigned int nPort,const string &strTaskTable, const string &strTaskID);
	
	~OTNM2000GetNeconfigService(void);
	
	void InitLoginNetWork(const string &pipName, const std::string &strUserName, const std::string &strPassword, const std::string &strIp, unsigned int nPort,const string &strTaskTable, const string &strTaskID);

	void GetAllSrvL3vpnSetToMongoDB(double fBegin, double fAdd,const std::string &strLogDir=".\\");
	void GetAllSrvL2vpnSetToMongoDB(double fBegin, double fAdd,const std::string &strLogDir=".\\");
	int GetAllCircuitsSetToMongoDB(double fBegin, double fAdd,const std::string &strLogDir=".\\");
	void GetAllProtectSetToMongoDB(double fBegin, double fAdd,const std::string &strLogDir=".\\");
	void GetAllRingSetToMongoDB(double fBegin, double fAdd,const std::string &strLogDir=".\\");

	// 获取一条数据，写入mongodb;
	void GetOneRingSetToMongoDB(XC_RING &xcEthSvc, int nIndex);
	void GetOneCircuitsSetToMongoDB(XC_CIRCUIT &tmpOneCircuit, int nIndex, int nTypeIndex,const string &strWaveName, int nFirstLabel);// 电路数据包含pw，tunnel;
	void GetOneProtectSetToMongoDB(XC_PROTECT_RELATION &xcEthSvc, int nIndex);
	void GetOneSrvL2vpnSetToMongoDB(XC_ETH_SERVICE &xcEthSvc, int nIndex);
	void GetOneSrvL3vpnSetToMongoDB(XC_IPRAN_L3VPN_SERVICE &xcEthSvc, int nIndex);
	void AddPathToMongoTable(XC_CIRCUIT &srcTunnelCircuits, int nIndex, string &strWaveName, int &nFirstLabel); // 某一条电路的path数据；
	void GetRingBandDataToMap(XC_CIRCUIT &tmpOneCircuit, int nTypeIndex);

	void MakeTableName();
	void DropAllTable();
	bool UpdateTaskID(double fProgress, const string &strDetail = "");
	bool InsertTaskID();

	void SendMongoDBResultState(const char*pipName, const char*pState);
	void InitNetClient();

	void GetWarningPingBi(const string &strPipName, int iNeId);
//	void GetAsonPOtnSrcManage(const string &strPipName);
	void GetAsonPOtnSrcManage(double fBegin, double fAdd);


public:
	CCMongoDBOperator m_MongoDBOperator;
	stThreadUse m_tmpThreadUseData[nDealArrayThreadNum];
	bool m_bIsGloab;
	int m_nCatchErrorCnt;
	double m_fCircuitProgess;
	static bool m_bFirstInClass;

	string strNeTableName,strNeTableKey,strBoardName,strBoardKey,m_strCommonRefTable,strPortTable;
	string strNeNameRef,strBoardNameRef;
	string strCloseLog;

	map<string,string> mapPortName; // ne_board_port_portlevel
	map<int, map<int, char>> mapFromRinglIDGetTunnel;// 环绑定，写入mongo表；

	// 重构。。
	bson_t *m_pKey[nDealArrayThreadNum];
	bson_t *m_pKeyRef[nDealArrayThreadNum];
	bson_t *m_pKeyDataPwRef[nDealArrayThreadNum];
	bson_t *m_pKeyPwRef[nDealArrayThreadNum];
	bson_t *m_pKeyTunnelRef[nDealArrayThreadNum];
	bson_t *m_pKeyDataOchRef[nDealArrayThreadNum];
	bson_t *m_pKeyOchRef[nDealArrayThreadNum];

	bson_t *m_pKeyDataOdukRef[nDealArrayThreadNum];
	bson_t *m_pKeyOdukRef[nDealArrayThreadNum];
	bson_t *m_pKeyDataClientRef[nDealArrayThreadNum];
	bson_t *m_pKeyClientRef[nDealArrayThreadNum];

	bson_t *m_pKeyDataOmsRef[nDealArrayThreadNum];
	bson_t *m_pKeyOmsRef[nDealArrayThreadNum];
	bson_t *m_pKeyDataOTSRef[nDealArrayThreadNum];
	bson_t *m_pKeyOTSRef[nDealArrayThreadNum];

	//// 展开路由信息；
	map<int, XC_CIRCUIT> mapCircusNeedReCntOchPath;
	map<int, XC_CIRCUIT> mapCircusNeedReCntOmsPath;

	map<int, XC_CIRCUIT> mapCircusNeedReCntPath; // pw等路由path，包含tunnel，改成展开模式；线程不安全变量；
	map<int, XC_CIRCUIT> mapCircusNeedReCntPathClient; // pw等路由path，包含tunnel，改成展开模式；线程不安全变量；

	bool IfAddReCntCircusPath(XC_PATH &tmpPath);
	bool IfAddReCntCircusToMap(XC_CIRCUIT &srcTunnelCircuits);
	void GetRefCircusFromJsonString(vector<string> &vctTunnelRefId, const string &strJsonResult, int nProtect, int nDirect);

	//// 展开路由信息； end

	string m_strTaskTable, m_strTaskID;

	map<TypeAll,  stDataTotalCount> mapTotalCount; // 总共的输出结果；
	bool   bIfTableUpdateRight;
	bool bIsOtnCircus;
	void CloseInitMSMPClient();

	string  strTableConfigNetWarning;

private:
	map<string, string> mapNeBoardPortName;  // neid+boardid+portno+portLevel, portName
	string strSrvUsr,strSrvPassword,strSrvIP;
	int nSrvPort; 
	HSESSION m_hSess;
	string m_strPipeName;
	
	map<int,string> mapIDName;
//	string  strTABLE_O2KClientInfos; // 合表改成分表；
//	string  strTABLE_BizDataInfos; // 合data表，改成分表；ok
	
	string  strTABLE_FLOW;
	string  strTABLE_PATH;     
	string  strTABLE_PATHINFO; 
	string  strTABLE_RingBandingTunnel;

	string  strTABLE_Ring;
	string  strTABLE_L2vpn;
	string  strTABLE_L3vpn;
	string  strTABLE_ProtectPair;
	string  strTABLE_Pw;
	string  strTABLE_Tunnel;
	string  strTABLE_Och;
	string  strTABLE_Ots;
	string  strTABLE_Oms;

	string  strTABLE_Ring_data;
	string  strTABLE_L2vpn_data;
	string  strTABLE_L3vpn_data;
	string  strTABLE_ProtectPair_data;
	string  strTABLE_Pw_data;
	string  strTABLE_Tunnel_data;
	string  strTABLE_Och_data;
	string  strTABLE_Ots_data;
	string  strTABLE_Oms_data;

	string  strTABLE_oduk;
	string  strTABLE_oduk_data;
	string  strTABLE_client;
	string  strTABLE_client_data;
	string  strTABLESPCRes;

	void SetRingMapToMongoDB();
	int SetCircusToMongoDB(const string &strTableRef, bson_t *m_pKeyRef[nDealArrayThreadNum], const string &strTableData, bson_t *m_pKeyDataRef[nDealArrayThreadNum],int nNum);

	void ThreadReladySetToMongoDB(int nThreadNum, FuncCallToDB pFun);
	void ThreadReladySetCircusToMongoDB(int nThreadNum, FuncCallToDB pFun);

	int ConnectNetClient(int nTimes=1, const std::string &strLogDir=".\\");
	
	void GetMongoBusinessLayerRelation(bson_t *pKeyRef, EObjectType m_eType, EServiceLayer m_eLayer, int m_iObjId);

	void SetPathIDRefTable(bson_t *pKey, vector<XC_PATH> &m_vectPath, const char *pPathListName);  // pathID ref表；
	void SetRouteIDRefTable(bson_t *pKey, int nPathID, vector<XC_CROSS_ITEM> &oRoute, int nProtect,int nDirect, string &strWaveName, int &nFirstLabel, bool bIfFirst=false);// routeID ref表；
	void AddCircuitsPathInfoResource(bson_t *child1, XC_CROSS_ITEM &tmpRoute, XC_RESOURCE &tmpReSrc, int nSrcOrDst, string &strWaveName, int &nFirstLabel, bool bIfFirst=false);// 增加一条电路的路由信息到mongo数据库；

	void GetWaveName(string &strWaveName, const XC_WAVE_CODE_KEY &stWaveCodeKey);
	void GetNeAndBoardNameID();// 获取java从mysql表中，写入到mongo的网元和单板信息；

	inline void GetPathInfoTableID(char *buf, int nPathID, int nDirect, int nIndex){
		sprintf(buf, "%d_%d_%d",nPathID,nDirect,nIndex);
	}
	inline int64 GetFlowTableID(int nSrvID, int nIndex){
		return (nSrvID*10000+nIndex);
	}
	
	bool GetBusinessLayerRelation(int m_iObjId, vector<int> &vctRelationPwID, vector<int> &vctRelationTunnelID, vector<int> &vctL2vpnRelationID, vector<int> &vctL3vpnRelationID
		,vector<int> &vctProtect, vector<int> &vctRoduk,vector<int> &vctRclient,vector<int> &vctRoch, vector<int> &vctRoms, vector<int> &vctRots, EServiceLayer m_eServiceLayer, vector<XC_OBJ_KEY> &objKey);

	std::string GetOneSelfPortName(int iNeId, int iBoardId, int iPortLevel, int iPortNo);

	void GetXMLVaule(string &strVaule,int nId, bool bType);
	void GetWaveName(string &strWaveName, int waveBand, int waveCode);

	void GetPortNameFromSNC(string &strOutPortName, int iNeId, int iBoardId, int nInPortNo, int nInPortLevel);

#if 1

public:
	///  获取网元状态的信息的信息；
	int nSendCMDType;
	int iTimeOut;
	string strO2000Ip;
	int nO2000Port;
	string strTABLE_NeStatus;

	void GetVctFromMongo();
	void MakeNEStatusTableName();

	/// 获取网元状态的信息；end

	// 获取网元告警屏蔽
	int nTotalNumCnt;
	int nCurNumCnt;
	void GetLineNoExplain(string &strRetResult, const stBoardStrType &tmpSTBoard, int dwLineNo);
	void BoardStr2MongoDB();
	void MakeBoardStrTableName();
	vector<stBoardStrType> m_vctBoardStrType;
	string strTABLE_BoardStrPingBi;
	string m_strBoardStrDataTable;  // 单盘表名称
	map<int, string> m_mapBoardTypeLineNo;
	void GetAlarmCodeString(std::string &strCName, std::string &strEName, int dwBoardID, int nMaskCode);
	// 获取网元告警屏蔽； end

public:
	///  获取配置Otnm2000OutputDataToNmosp.ini的信息； =>句柄超标之后，重启继续之前的job;
	string strIp,strUserName, strPassword;
	int nPort,nRestartFlag/*重启标志*/, nFreqInit/*重启频率*/, nJobVctGetConfigLen/*任务长度*/;
	vector <stConfigGet> vctGetConifg;
	bool bIfNeedInit;
	EM_TypeConifGet emClassType;
	string  strTABLE_lag;
	string  strTABLE_ether;
	string  strTABLE_ve;
	string  strTABLE_clock;
	void MakeConfigTableName();
	void GetVctConifgFromXMLAndMongo(map<int, EM_TypeConifGet> &mapType);
	
	void GetConfigToMongoDB(const string &strPipName);
	///  获取配置Otnm2000OutputDataToNmosp.ini的信息； end;


	// 取得lag接口配置；
	bool GetLagInterfaceConfig(const std::string &strPipeName, int iNeId, bool bMongo = false);
	// 取得ve接口配置；
	bool GetAllTypeInterfaceConfig(const std::string &strPipeName, int iNeId, EM_TYPE_FUNCTION emType, bool bMongo = false);
	bool GetAllTypeInterfaceConfig(const std::string &strPipeName, const vector<string> &vctFunParam, EM_TYPE_FUNCTION emType);
	// 取得时钟配置的接口；
	bool GetClockConfigInterfaceConfig(std::string strPipeName, int iNeId, EM_TYPE_FUNCTION emType, bool bMongo = false);

	// 获取连接状态；
	void GetOtnm2000ConnectState(const std::string &strPipeName);
	
	// 取得时钟状态的接口；
	bool GetClockStatueInterfaceConfig(std::string strPipeName, int iNeId);
	// 获取单盘状态信息;
	void GetNetBoardStatue(const std::string &strPipeName, int iNeId, int iTimeOut);
	// 获取网元的mcc静态配置；
	void GetNetMccStaticStatue(const std::string &strPipeName, int iNeId, int iTimeOut, bool bSetMongoDB = false);

private:
	char * GetL2orL3Attr(int iType);
	char * GetLoadGroupingMode(int iType);
	char * GetLoadGroupingAlgorithm(int iType);	
	/////////////////
	void VEOutData(Json::Value &rRoot, BYTE m_byVlan_stacking_en, BYTE m_arMAC[6], BYTE m_arVport_name[32], unsigned long m_dwPrim_ip_addr, BYTE);
	
	bool GetInterfaceConfigVEPARSE(std::string strPipeName, int iNeId, EM_TYPE_FUNCTION emType, bool bMongo = false);	
	bool GetInterfaceConfigEtherNetPARSE(std::string strPipeName, int iNeId, EM_TYPE_FUNCTION emType, bool bMongo = false);
	void GetInterfaceConfigEtherNetPARSEMsgUsual(Json::Value &rRoot, BYTE m_byPort_rate_type,
		BYTE m_arPort_desc[64], BYTE m_byUrpf_en, int m_nMtu, BYTE m_byEndIf,BYTE m_byShut, BYTE m_arVport_name[32]);
	void GetInterfaceConfigEtherNetPARSEMsgEthNet(Json::Value &rRoot,BYTE m_byPort_mode, BYTE m_byIp_mode, unsigned long m_dwPrim_ip_addr,
		BYTE m_byPrim_ip_mask, BYTE m_byRsvp_en, BYTE m_byLdp_en, BYTE m_byMpls_en, BYTE m_byArp_proxy_en);

	bool GetClockConfigInterfaceConfig(Json::Value &rRoot, int iNeId, EM_TYPE_FUNCTION emType);
	void GetClockConfigInterfaceConfigJson(Json::Value &valOneCirId, BYTE m_byClock_Work_Mode, BYTE m_byQL_Enable_Select,
		BYTE m_byCLK1_Input_Type, BYTE m_byCLK2_Input_Type,BYTE m_byCLK3_Input_Type);
	void GetNeSlots(std::vector<std::string> &vctStrSlots, DWORD dwNeId);
#endif		
		
};

extern OTNM2000GetNeconfigService  g_MongoNeStatusGetNeconfigService;
extern OTNM2000GetNeconfigService  g_MongoBoardStrGetNeconfigService;
extern bool g_bStopMongoDBBoardStrTheard;
extern bool g_bStopMongoDBTheard;
extern bool g_bStopMongoDBNeStatusTheard;
extern void GetMyNeedData(stBoardStrType &tmpSTBoard, bson_t *pKey);
extern string g_strPipNo;
extern string g_strPipNoFunInterFace;
extern bool g_bRestartNeedRestart;
extern bool g_bRestart;
extern bool g_bErrorCatchOrHandle;
extern bool g_bStopConfigMongoDBTheard;
extern int  g_nOneTimeMaxDataCnt;
extern void EasyGetAllTmpConfigFile(vector <stConfigGet> &vctGetConifg, bool bType);
extern void EasySaveAllTmpConfigFile(vector <stConfigGet> &vctGetConifg, int index, bool bType);
extern void IfContinueRestartLastJob(int  nType);
extern bool IfHandleOutOfRange();

void GetOnlyRecordID(char *buf);
void GetNeName(string &strNeName, int dwNeId);
void GetBoardNeSlots(std::vector<std::string> &vctStrSlots, std::vector<int> &vctBoardId, DWORD dwNeId);
void GetMsgFromNeBoardID(CString &strNeName, CString &strBoardName, CString &strSlots,int BoardId, DWORD dwNeId);
DWORD WINAPI DealThreadFunction( LPVOID lpParam);

DWORD DealThreadeCircuitsFunction( LPVOID lpParam);
DWORD DealThreadRingFunction( LPVOID lpParam);
DWORD DealThreadL3Function( LPVOID lpParam);
DWORD DealThreadL2Function( LPVOID lpParam);
DWORD DealThreadProtectFunction( LPVOID lpParam);