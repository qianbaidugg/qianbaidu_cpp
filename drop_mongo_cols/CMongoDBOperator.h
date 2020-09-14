#pragma once

#include <stdio.h>
#include <string>
#include <map>
#include "./mongoDB/mongoDBFile/src/libbson/src/bson/bson.h"
#include "./mongoDB/mongoDBFile/src/libmongoc/src/mongoc/mongoc.h"

#define SYSTEM_ERROR_LOG 0

#define  TABLE_PATH    "biz_routeinfos"
#define  TABLE_PATHINFO "biz_pathinfos"
#define  TABLE_BizData   "biz_datainfos"
#define  TABLE_TUNNEL   "biz_tunnel"
#define  TABLE_PW       "biz_pw"

#define  TABLE_OTS       "biz_ots"
#define  TABLE_OMS       "biz_oms"

#define  TABLE_OCH		"biz_och"
#define  TABLE_ODUK		"biz_oduk"
#define  TABLE_CLIENT	"biz_circuit_client"

#define  TABLE_RING      "biz_ring"
#define  TABLE_L2VPN    "biz_l2vpn"
#define  TABLE_FLOW     "biz_flow"
#define  TABLE_L3VPN    "biz_l3vpn"
#define  TABLE_PROTECT  "biz_protect"
#define  TABLE_RINGBAND  "biz_ringbang"
#define  TABLE_LAG      "biz_lag"
#define  TABLE_ETHER      "biz_ether"
#define  TABLE_VE      "biz_ve"
#define  TABLE_CLOCK      "biz_clock"
#define  TABLE_NeStatus  "biz_nestatus"
#define  TABLE_NeWarning  "biz_warning"              //  网元告警屏蔽
#define  TABLE_SPC_RESOURCE  "biz_spcres"
#define  TABLE_BoardStrPingbi  "biz_boardstrpingbi"  //  单盘告警屏蔽

#define  TABLE_NE_IDNAME      "Biz_Ne_IdName"
#define  TABLE_BOARD_IDNAME   "Biz_Board_IdName"

// 实体表：
#define  TABLE_TEST_a_Name    "a"
#define  TABLE_PATH_Name      "Biz_RouteInfos"
#define  TABLE_PATHINFO_Name  "Biz_PathInfos"
#define  TABLE_TUNNEL_Name    "Biz_Tunnel"
#define  TABLE_PW_Name        "Biz_Pw"
#define  TABLE_OCH_Name		  "Biz_Och"
#define  TABLE_RING_Name      "Biz_Ring"
#define  TABLE_L2VPN_Name     "Biz_L2vpn"
#define  TABLE_FLOW_Name      "Biz_Flow"
#define  TABLE_L3VPN_Name     "Biz_L3vpn"
#define  TABLE_PROTECT_Name   "Biz_Protect"
#define  TABLE_ODUK_Name	  "Biz_Oduk"
#define  TABLE_CLIENT_Name	  "Biz_Circuit_Client"
#define  TABLE_RINGBAND_Name  "Biz_Ringbang"
#define  TABLE_OTS_Name       "Biz_Ots"
#define  TABLE_OMS_Name       "Biz_Oms"
#define  TABLE_LAG_Name       "Biz_Truck"
#define  TABLE_ETHER_Name     "Biz_Ether"
#define  TABLE_VE_Name		  "Biz_Ve"
#define  TABLE_CLOCK_Name     "Biz_Clock"
#define  TABLE_NeStatus_Name  "Biz_NeStatus"
#define  TABLE_NeWarning_Name  "Biz_Warning"              //  网元告警屏蔽 表
#define  TABLE_SPC_RESOURCE_Name  "Biz_SPCRES"
#define  TABLE_BoardStrPingbi_Name  "Biz_BoardStrPingBi"  // 单盘告警屏蔽  表

//#define  TABLE_BizData_Name   "Biz_DataInfos"


// 数据写入的开关；
#define  DEFINE_MONGO_INSERT 1

//#define  nDealArrayThreadNum 64 

#define  nDealArrayThreadNum  800
//#define  nDealArrayThreadNum  1


// 1单线程；
#define  IfDealSingleThread  1

#define  nThreadSize  256

typedef bson_t* pBson;

class CCMongoDBOperator
{
public:
	mongoc_client_t *m_pClient;
	std::string  m_strTableName;

private:
	HANDLE  m_hMutex;
	CRITICAL_SECTION m_critclSection;

public:
	CCMongoDBOperator():m_hMutex(NULL)
	{	
		m_pClient = NULL;
	}

	CCMongoDBOperator(
		const char * pDBIP,
		const char * pDBPort,
		const char * pUserName = NULL,
		const char * pPassword = NULL,
		const char * pAppName = NULL);

	void InitMongoDBData(
		const char * pDBIP,
		const char * pDBPort,
		const char * pUserName = NULL,
		const char * pPassword = NULL,
		const char * pAppName = NULL);

	void ClearConnect();

	virtual ~CCMongoDBOperator(void);

	bool DropPipDBTableCmpCollName(const char* pCollName){
		if (strncmp(pCollName, TABLE_TEST_a_Name, strlen(TABLE_TEST_a_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_FLOW_Name, strlen(TABLE_FLOW_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_L3VPN_Name, strlen(TABLE_L3VPN_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_NeStatus_Name, strlen(TABLE_NeStatus_Name)) == 0){
			return true;
		}
		///////////////
		else if (strncmp(pCollName, TABLE_LAG_Name, strlen(TABLE_LAG_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_VE_Name, strlen(TABLE_VE_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_ETHER_Name, strlen(TABLE_ETHER_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_CLOCK_Name, strlen(TABLE_CLOCK_Name)) == 0){
			return true;
		}
		///////////////
		else if (strncmp(pCollName, TABLE_OMS_Name, strlen(TABLE_OMS_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_OCH_Name, strlen(TABLE_OCH_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_L2VPN_Name, strlen(TABLE_L2VPN_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_PATHINFO_Name, strlen(TABLE_PATHINFO_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_PATH_Name, strlen(TABLE_PATH_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_PROTECT_Name, strlen(TABLE_PROTECT_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_RING_Name, strlen(TABLE_RING_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_PW_Name, strlen(TABLE_PW_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_TUNNEL_Name, strlen(TABLE_TUNNEL_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_RINGBAND_Name, strlen(TABLE_RINGBAND_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_NE_IDNAME, strlen(TABLE_NE_IDNAME)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_BOARD_IDNAME, strlen(TABLE_BOARD_IDNAME)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_OCH_Name, strlen(TABLE_OCH_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_ODUK_Name, strlen(TABLE_ODUK_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_CLIENT_Name, strlen(TABLE_CLIENT_Name)) == 0){
			return true;
		}
		else if (strncmp(pCollName, TABLE_NeWarning_Name, strlen(TABLE_NeWarning_Name)) == 0){
			return true;
		}
				
		return false;
	}

	// 添加  mutex
	bool Insert(mongoc_collection_t **pMutextCollection, const char* pDbName, const char* pCollName, bson_t * pDoc);
	// 添加  mutex end

	bool QueryAndGetTableIDandName(std::map<int,int> &mapIDName,const char* pDbName, const char* pCollName, const char *strMainID,const char *strMainName);
	bool QueryAndGetTableIDandName(std::map<int,std::string> &mapIDName,const char* pDbName, const char* pCollName, const char *strMainID, const char *strMainName);
	bool QueryAndGetTableIDandName(std::map<std::string,std::string> &mapIDName,const char* pDbName, const char* pCollName, const char *strMainID, const char *strMainName);
	// 查询，并处理单板信息数据；
	bool QueryAndGetBoardStrTableMsg(void *pOtnmObject, const char* pDbName, const char* pCollName,const char *strMainID, const char *strTypeName, const char *strBoardType, const char *strBinHexName);


public:
	int GetNeIDType(int neID, const char *pNeTable);

	bool Insert(const char* pDbName, const char* pCollName, bson_t * pDoc);

	bool InsertMany(const char* pDbName, const char* pCollName, bson_t *pDoc[nDealArrayThreadNum], int nNum);

	// 更新
	bool Update(const char* pDbName, const char* pCollName, bson_t * pKey, bson_t * pDoc);
	// 删除
	bool Delete(const char* pDbName, const char* pCollName, bson_t * pKey);

	bool DeleteAll(const char* pDbName, const char* pCollName);

	bool QueryIDAndGetPathInfoContext(bson_t *pResult, const char* pDbName, const char* pCollName, bson_t * pKey,int nProtect, int nDirect);

	// 查询某个ID是否存在；
	bool QueryIDContext(std::string &strContext, const char* pDbName, const char* pCollName, bson_t * pKey);

	// 查询某个ID是否存在；
	bool QueryTableIDExist(const char* pDbName, const char* pCollName, bson_t * pKey);

	// 查询某个ID存在,且获取其唯一标示;
	bool QueryAndGetTableOnlyID(char *strOnlyID, const char* pDbName, const char* pCollName, bson_t * pKey, const char *strMainID="_id");

	// 删除表；
	bool DropTable(const char* pDbName, const char* pCollName);

	// 删除数据库的所有的表；
	bool DropPipDBTable(const char* pDbName);

	// 删除数据库; =》 // 删库 => 会导致数据库无法登陆了。 xxxx 必须得重新创建连接；
	bool DropPipDB(const char* pDbName);

};

enum EM_TypeConifGet{
	EM_TYPE_ALL,
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
