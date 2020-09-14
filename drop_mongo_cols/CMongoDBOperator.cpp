#include "StdAfx.h"
#include "CMongoDBOperator.h"
#include <string>
#include <iostream>
//#include "./neconfig/OTNM2000GetNeconfigService.h"

using namespace std;

//
CCMongoDBOperator::CCMongoDBOperator(
									 const char * pDBIP,
									 const char * pDBPort,
									 const char * pUserName,
									 const char * pPassword,
									 const char * pAppName)
{
	m_pClient = NULL;
	m_hMutex = NULL;
	InitMongoDBData(pDBIP,pDBPort,pUserName,pPassword ,pAppName);
}

//
CCMongoDBOperator::~CCMongoDBOperator(void)
{
	if(m_pClient != NULL){
		mongoc_client_destroy(m_pClient);
		m_pClient = NULL;
	}
	mongoc_cleanup();

	if (m_hMutex != NULL){
		::ReleaseMutex(m_hMutex);//释放互斥量
		CloseHandle(m_hMutex);
		::DeleteCriticalSection(&m_critclSection);
	}
}

void CCMongoDBOperator::ClearConnect()
{
	if(m_pClient != NULL){
		mongoc_client_destroy(m_pClient);
		m_pClient = NULL;
		mongoc_cleanup();
	}
}

void CCMongoDBOperator::InitMongoDBData(
					 const char * pDBIP,
					 const char * pDBPort,
					 const char * pUserName,
					 const char * pPassword ,
					 const char * pAppName)
{
	if (m_hMutex == NULL){
		m_hMutex = CreateMutex(NULL,FALSE,NULL);
		::InitializeCriticalSection(&m_critclSection); 
	}	
	ClearConnect();

	mongoc_init();
	string strConnect = "mongodb://";
	if (pUserName != NULL && pPassword != NULL)
	{
		strConnect = strConnect + pUserName + ":" + pPassword + "@";
	}
	strConnect = strConnect + pDBIP + ":";
	strConnect = strConnect + pDBPort + "/";
	if (pAppName != NULL)
	{
		strConnect = strConnect + "?appname=" + pAppName;
	}
	m_pClient = mongoc_client_new(strConnect.c_str());

	m_strTableName = pAppName;
}

// 添加
bool CCMongoDBOperator::Insert(const char* pDbName, const char* pCollName, bson_t * pDoc)
{// 不支持同时操作； c drive 不是线程安全的。
	mongoc_collection_t *collection;
	collection = mongoc_client_get_collection (m_pClient, pDbName, pCollName);
	bson_error_t error;
	if (!mongoc_collection_insert(collection, MONGOC_INSERT_NONE, pDoc, NULL, &error)){
#if SYSTEM_ERROR_LOG
		fprintf(stderr, "Insert Failure:%s\n", error.message);
#else
		char bufLog[512]="";			
		sprintf(bufLog, "Insert Failure:%s\n", error.message);
		//WriteLog(bufLog);
		printf("%s\n",bufLog);
#endif
		return false;
	}
	mongoc_collection_destroy(collection);
	return true;
}
// 添加
bool CCMongoDBOperator::InsertMany(const char* pDbName, const char* pCollName, bson_t *pDoc[nDealArrayThreadNum], int nNum)
{// 不支持同时操作； c drive 不是线程安全的。
#if IfDealSingleThread

#else
	//	::WaitForSingleObject(m_hMutex, INFINITE);
	::EnterCriticalSection((LPCRITICAL_SECTION)&m_critclSection);
#endif
	mongoc_collection_t *collection;
	collection = mongoc_client_get_collection (m_pClient, pDbName, pCollName);
	bson_error_t error;

	if(!mongoc_collection_insert_many(collection,(const bson_t **)pDoc, nNum, NULL, NULL, NULL)){

#if SYSTEM_ERROR_LOG
		fprintf(stderr, "Insert many Failure:%s\n", error.message);
#else
		char bufLog[512]="";			
		sprintf(bufLog, "Insert many Failure:%s\n", error.message);
		//WriteLog(bufLog);
		printf("%s\n",bufLog);
#endif

#if IfDealSingleThread 

#else
		//		::ReleaseMutex(m_hMutex);//释放互斥量 
		::LeaveCriticalSection((LPCRITICAL_SECTION)&m_critclSection); 
#endif
		return false;
	}
	mongoc_collection_destroy(collection);
#if IfDealSingleThread 

#else
	//		::ReleaseMutex(m_hMutex);//释放互斥量 
	::LeaveCriticalSection((LPCRITICAL_SECTION)&m_critclSection); 
#endif
	return true;
}

bool CCMongoDBOperator::Insert(mongoc_collection_t **pMutextCollection, const char* pDbName, const char* pCollName, bson_t * pDoc)
{// 不支持同时操作； c drive 不是线程安全的。
#if IfDealSingleThread

#else
//	::WaitForSingleObject(m_hMutex, INFINITE);
	::EnterCriticalSection((LPCRITICAL_SECTION)&m_critclSection);
#endif
	if (*pMutextCollection == NULL){
		*pMutextCollection = mongoc_client_get_collection (m_pClient, pDbName, pCollName);
	}
	
	bson_error_t error;
	if (!mongoc_collection_insert(*pMutextCollection, MONGOC_INSERT_NONE, pDoc, NULL, &error)){

#if SYSTEM_ERROR_LOG
		fprintf(stderr, "Insert Failure:%s\n", error.message);
#else
		char bufLog[512]="";			
		sprintf(bufLog, "Insert Failure:%s\n", error.message);
		//WriteLog(bufLog);
		printf("%s\n",bufLog);
#endif

#if IfDealSingleThread 

#else
//		::ReleaseMutex(m_hMutex);//释放互斥量 
	::LeaveCriticalSection((LPCRITICAL_SECTION)&m_critclSection); 
#endif
		return false;
	}
#if IfDealSingleThread 

#else
//	::ReleaseMutex(m_hMutex);//释放互斥量 
	::LeaveCriticalSection((LPCRITICAL_SECTION)&m_critclSection); 
#endif
	return true;
}
// 添加 mutext; end

// 更新
bool CCMongoDBOperator::Update(const char* pDbName, const char* pCollName, bson_t * pKey, bson_t * pDoc)
{
	mongoc_collection_t *collection;
	collection = mongoc_client_get_collection (m_pClient, pDbName, pCollName);
	bson_error_t error;
	bool bResult = mongoc_collection_update(collection, MONGOC_UPDATE_NONE, pKey, pDoc, NULL, &error);
	if (!bResult)
	{
#if SYSTEM_ERROR_LOG
		fprintf(stderr, "Update Failure:%s\n", error.message);
#else
		char bufLog[512]="";			
		sprintf(bufLog, "Update Failure:%s\n", error.message);
		//WriteLog(bufLog);
		printf("%s\n",bufLog);
#endif
		return false;
	}
	mongoc_collection_destroy(collection);

	return true;

}

// 删除
bool CCMongoDBOperator::Delete(const char* pDbName, const char* pCollName, bson_t * pKey)
{
	mongoc_collection_t *collection;
	collection = mongoc_client_get_collection (m_pClient, pDbName, pCollName);
	bson_error_t error;
	bool bResult = mongoc_collection_delete(collection, MONGOC_DELETE_NONE, pKey, NULL, &error);
	if (!bResult)
	{
#if SYSTEM_ERROR_LOG
		fprintf(stderr, "Delete Failure:%s\n", error.message);
#else
		char bufLog[512]="";			
		sprintf(bufLog, "Delete Failure:%s\n", error.message);
		//WriteLog(bufLog);
		printf("%s\n",bufLog);
#endif
		return false;
	}
	mongoc_collection_destroy(collection);
	return true;
}

bool CCMongoDBOperator::DropPipDBTable(const char* pDbName)
{// ok
	bson_error_t error = {0};
	bson_iter_t col_iter;
	const bson_t *doc;
	const char *name;
	mongoc_database_t *database= mongoc_client_get_database (m_pClient, pDbName);

	bson_t *pKey = BCON_NEW("name", "{", "$ne", "", "}"); // "$lt","$lte","$gt","$gte",$ne分别对应<,<=,>,>=,不等于
	mongoc_cursor_t *cursor = mongoc_database_find_collections (database, pKey, &error);

	int cnt_drop = 0;
	int ctn_scan = 0;
	
	while (mongoc_cursor_next (cursor, &doc)){
		if (bson_iter_init (&col_iter, doc) &&
			bson_iter_find (&col_iter, "name") &&
			BSON_ITER_HOLDS_UTF8 (&col_iter) &&
			(name = bson_iter_utf8 (&col_iter, NULL))){

			if (DropPipDBTableCmpCollName(name)){
				++cnt_drop;
				printf("collection:%s, ---droped.\n", name);
				DropTable(pDbName, name);						
			}
			else {
				++ctn_scan;
				printf("collection:%s, ignored.\n", name);
			}
		} else {
			BSON_ASSERT (false);
		}
	}

	printf("succeed drop %d collections.\n", cnt_drop);
	printf("scan %d collections.\n", ctn_scan);

	mongoc_cursor_destroy (cursor);
	bson_destroy(pKey);
	mongoc_database_destroy (database);	

	return true;
}


bool CCMongoDBOperator::DropPipDB(const char* pDbName)
{// ok
	bson_error_t error = {0};
	mongoc_database_t *database= mongoc_client_get_database (m_pClient, pDbName);
	bool bResult = mongoc_database_drop(database, &error);
	if (!bResult){// 删库 => 会导致数据库无法登陆了。 xxxx 必须得重新创建连接；
	
#if SYSTEM_ERROR_LOG
		fprintf(stderr, "Drop Database Failure:%s\n", error.message);
#else
		char bufLog[512]="";			
		sprintf(bufLog, "Drop Database Failure:%s\n", error.message);
		//WriteLog(bufLog);
		printf("%s\n",bufLog);
#endif

		return false;
	}
	mongoc_database_destroy (database);
	
	return true;
}

#if 0
bool CCMongoDBOperator::AddPipDB(const char* pDbName)
{
	bson_error_t error = {0};
	mongoc_database_t *database= mongoc_client_get_database (m_pClient, pDbName);

//	db.createUser({user:"root",pwd:"123456",roles:[{"role":"root","db":"admin"}]})

	bson_t *pKey; //BCON_UTF8   BCON_INT64   BCON_INT32
	pKey = BCON_NEW ("user", "admin", "pwd","admin", "roles", 
		"[","{","role","userAdminAnyDatabase","db",pDbName,"}","]");
//	BCON_APPEND(pKey, "EOperateMode", BCON_INT32(xcEthSvc.m_eOperMode));

	bool bResult = mongoc_database_add_user(database, "admin","admin",pKey,NULL,&error);
	if (!bResult){// 删库 => 会导致数据库无法登陆了。
		fprintf(stderr, "Drop Database Failure:%s\n", error.message);
		bson_destroy(pKey);
		return false;
	}
	bson_destroy(pKey);

	mongoc_database_destroy (database);

	return true;
}
#endif

bool CCMongoDBOperator::DropTable(const char* pDbName, const char* pCollName)
{
	bson_error_t error = {0};
	mongoc_collection_t *collection;
	collection = mongoc_client_get_collection (m_pClient, pDbName, pCollName);
	bool bResult = mongoc_collection_drop(collection, &error);
	if (!bResult){
#if SYSTEM_ERROR_LOG
		fprintf(stderr, "Drop Table Failure:%s\n", error.message);
#else
		char bufLog[512]="";			
		sprintf(bufLog, "Drop Table Failure:%s\n", error.message);
		//WriteLog(bufLog);
		printf("%s\n",bufLog);
#endif
		return false;
	}
	mongoc_collection_destroy(collection);

	return true;
}

bool CCMongoDBOperator::QueryIDContext(std::string &strContext, const char* pDbName, const char* pCollName, bson_t * pKey)
{
#if IfDealSingleThread

#else
	//	::WaitForSingleObject(m_hMutex, INFINITE);
	::EnterCriticalSection((LPCRITICAL_SECTION)&m_critclSection);
#endif
	mongoc_collection_t *collection = mongoc_client_get_collection (m_pClient, pDbName, pCollName);

	bool bRet = false;
	const bson_t *doc;
	mongoc_cursor_t *cursor = mongoc_collection_find_with_opts (collection, pKey, NULL, NULL);
	while (mongoc_cursor_next (cursor, &doc)) {

		char *str = bson_as_json (doc, NULL);
		//printf ("%s\n", str);
		strContext = str;
		bson_free (str);

		////
		bson_iter_t iter;
		bson_iter_init_find (&iter, doc, "workPath");

		 bson_t bcon;
		bson_init (&bcon);
		BCON_APPEND (&bcon, "workPath", BCON_ITER (&iter));

		str = bson_as_json (&bcon, NULL);
		printf ("%s\n", str);
		bson_free (str);

		bson_destroy (&bcon);

		bRet = true;
		break;
	}

	mongoc_cursor_destroy (cursor);
	mongoc_collection_destroy(collection);

#if IfDealSingleThread 

#else
	//		::ReleaseMutex(m_hMutex);//释放互斥量 
	::LeaveCriticalSection((LPCRITICAL_SECTION)&m_critclSection); 
#endif
	return bRet;
}

bool CCMongoDBOperator::QueryIDAndGetPathInfoContext(bson_t *pResult, const char* pDbName, const char* pCollName, bson_t * pKey,int nProtect, int nDirect)
{
#if IfDealSingleThread

#else
	//	::WaitForSingleObject(m_hMutex, INFINITE);
	::EnterCriticalSection((LPCRITICAL_SECTION)&m_critclSection);
#endif
	mongoc_collection_t *collection = mongoc_client_get_collection (m_pClient, pDbName, pCollName);

	bool bRet = false;
	const bson_t *doc;
	mongoc_cursor_t *cursor = mongoc_collection_find_with_opts (collection, pKey, NULL, NULL);
	while (mongoc_cursor_next (cursor, &doc)) {

		bool bIfGetPath = false;
		bson_iter_t iter;
		if (nProtect == 0){
			bIfGetPath = bson_iter_init_find (&iter, doc, "workPath");
		}
		else if (nProtect == 1){
			bIfGetPath = bson_iter_init_find (&iter, doc, "protectPath");
		}
	//	BCON_APPEND (pResult, "childPath", BCON_ITER (&iter)); // 不区分，正反向；
	//	bRet = true;

	// 解析bson字串，子文档；
		int nListCnt = 0;
		bson_iter_t sub_iter;
		if (bIfGetPath &&
			(BSON_ITER_HOLDS_DOCUMENT (&iter) || BSON_ITER_HOLDS_ARRAY (&iter)) &&
			bson_iter_recurse (&iter, &sub_iter)) {// 每一个这个，获取一次[]内容；
				while (bson_iter_next (&sub_iter)) {
				//	printf ("Found key \"%s\" in sub document.\n", bson_iter_key (&sub_iter));

					/*bson_t childList;
					bson_init(&childList);
					BCON_APPEND (&childList, "childPath", BCON_ITER(&sub_iter));				
					char *str = bson_as_json (&childList, NULL);
					printf(str);
					bson_destroy(&childList);*/

					if (nDirect == nListCnt++){// 0是正向；1是反向；
						BCON_APPEND(pResult, "childPath", BCON_ITER (&sub_iter));
						bRet = true;
						break;
					}
					else{
						continue;
					}				
				}
		}

		break;
	}

	mongoc_cursor_destroy (cursor);
	mongoc_collection_destroy(collection);

#if IfDealSingleThread 

#else
	//		::ReleaseMutex(m_hMutex);//释放互斥量 
	::LeaveCriticalSection((LPCRITICAL_SECTION)&m_critclSection); 
#endif
	return bRet;
}

bool CCMongoDBOperator::QueryTableIDExist(const char* pDbName, const char* pCollName, bson_t * pKey)
{
	mongoc_collection_t *collection = mongoc_client_get_collection (m_pClient, pDbName, pCollName);

	bool bRet = false;
	const bson_t *doc;
	mongoc_cursor_t *cursor = mongoc_collection_find_with_opts (collection, pKey, NULL, NULL);
	while (mongoc_cursor_next (cursor, &doc)) {

	//	str = bson_as_json (doc, NULL);
	//	printf ("%s\n", str);
	//	bson_free (str);

		bRet = true;
		break;
	}

	mongoc_cursor_destroy (cursor);
	mongoc_collection_destroy(collection);
	return bRet;
}

bool CCMongoDBOperator::QueryAndGetBoardStrTableMsg(void *pOtnmObject, const char* pDbName, const char* pCollName, 
		const char *strMainID, const char *strTypeName, const char *strBoardType, const char *strBinHexName)
{
	int nCurIndex = 0;
	bool bRet = false;
/*	try{
		OTNM2000GetNeconfigService *pThis = (OTNM2000GetNeconfigService *)pOtnmObject;

		bson_t *pKey = BCON_NEW("_id", "{", "$ne", "", "}"); // "$lt","$lte","$gt","$gte",$ne分别对应<,<=,>,>=,不等于
		mongoc_collection_t *collection = mongoc_client_get_collection(m_pClient, pDbName, pCollName);
		pThis->nTotalNumCnt = mongoc_collection_count_documents (collection,pKey,NULL,NULL,NULL,NULL); // 获取mongo数据库的总数
		char strOnlyID[100]="", strOnlyName[100]="", strOnlyBoardType[100]="";
		string strBinHexData = "";
		const bson_t *doc;
		mongoc_cursor_t *cursor = mongoc_collection_find_with_opts (collection, pKey, NULL, NULL);
		while (mongoc_cursor_next (cursor, &doc)) {

			if (g_bStopMongoDBBoardStrTheard){// 加快结束任务时，程序退出。
			//	WriteLog("BoardStr2MongoDB self stop job from QueryAndGetBoardStrTableMsg");
				printf("BoardStr2MongoDB self stop job from QueryAndGetBoardStrTableMsg\n");
				break;	
			}

			bool b1=false,b2=false,b3=false,b4=false;
			char *str = bson_as_json (doc, NULL); // utf8的字串；
			// 取出json中的主键id；  => strMainID   => int
			char *pPos = strstr(str, strMainID);		
			if (pPos!=NULL){
				pPos += strlen(strMainID);

				char *pFirst = NULL;
				while(*pPos != 0){
					if(*pPos == ':'){
						pFirst = pPos+1;
					}	
					pPos++;

					if ((pFirst != NULL)&&(*pPos == ',')){
						*pPos=0;
						strcpy(strOnlyID, pFirst);
						*pPos=',';
						b1=true;
						break;
					}
				}
			}
		
			// 取出json中的主键id；  => strBoardType   => int
			pPos = strstr(str, strBoardType);		
			if (pPos!=NULL){
				pPos += strlen(strBoardType);

				char *pFirst = NULL;
				while(*pPos != 0){
					if(*pPos == ':'){
						pFirst = pPos+1;
					}	
					pPos++;

					if ((pFirst != NULL)&&(*pPos == ',')){
						*pPos=0;
						strcpy(strOnlyBoardType, pFirst);
						*pPos=',';
						b4=true;
						break;
					}
				}
			}

			// 取出json中的主键id；  =>  strTypeName  => string
			pPos = strstr(str, strTypeName);		
			if (pPos!=NULL){
				pPos += strlen(strTypeName);

				char *pFirst = NULL;
				char *pPosStart = NULL;
				while(*pPos != 0){
					if(*pPos == ':'){
						pFirst = pPos+1;
					}

					if((pFirst != NULL)&&(*pPos=='\"')){
						pPosStart = pPos+1;
					}
					pPos++;

					if ((pPosStart != NULL)&&(*pPos == '\"')){
						*pPos=0;
						strcpy(strOnlyName, pPosStart);						
						*pPos='\"';
						b2=true;
						break;
					}
				}
			}
		
			// strBinHexName  => 取string类型变量；
			pPos = strstr(str, strBinHexName);		
			if (pPos!=NULL){
				pPos += strlen(strBinHexName);

				char *pFirst = NULL;
				char *pPosStart = NULL;
				while(*pPos != 0){
					if(*pPos == ':'){
						pFirst = pPos+1;
					}

					if((pFirst != NULL)&&(*pPos=='\"')){
						pPosStart = pPos+1;
					}
					pPos++;

					if ((pPosStart != NULL)&&(*pPos == '\"')){
						*pPos=0;
						//strcpy(strOnlyName, pPosStart);	
						strBinHexData = pPosStart;
						*pPos='\"';
						b3=true;
						break;
					}
				}
			}
		
			// 取出json中的主键id；
			if (b1&&b2&&b3&&b4){
				stBoardStrType tmpOne;
				tmpOne.nBoardID = atoi(strOnlyID);
				//tmpOne.nCallType = atoi(strOnlyName);
				if(strncmp(strOnlyName, "old", strlen("old")) == 0){
					tmpOne.nCallType = 1;
				}
				else if(strncmp(strOnlyName, "new", strlen("new")) == 0){
					tmpOne.nCallType = 0;
				}
				else if(strncmp(strOnlyName, "middle", strlen("middle")) == 0){
					tmpOne.nCallType = 2;
				}else{ // "emu"
					tmpOne.nCallType = 0;
				}

				tmpOne.nBoardType = atoi(strOnlyBoardType);
				BinHex2String(tmpOne.strHexData, strBinHexData.c_str());	
				pThis->m_vctBoardStrType.push_back(tmpOne);
			}

			if (pThis->m_vctBoardStrType.size() >= 200){
				pThis->BoardStr2MongoDB(); // 结果写进mongo数据库；
			}
			nCurIndex++;
		}

		pThis->BoardStr2MongoDB(); // 结果写进mongo数据库；   不足500条的。

	}catch(...){
		char bufLog[100] = "";
		sprintf(bufLog, "QueryAndGetBoardStrTableMsg fail! curIndex=%d\n", nCurIndex);
		//WriteLog(bufLog);
		printf("%s\n",bufLog);
	}*/

	return bRet;
}




bool CCMongoDBOperator::QueryAndGetTableIDandName(map<int,int> &mapIDName,const char* pDbName, const char* pCollName, const char *strMainID,const char *strMainName)
{
	bool bRet = false;
	try{

		bson_t *pKey = BCON_NEW("_id", "{", "$ne", "", "}"); // "$lt","$lte","$gt","$gte",$ne分别对应<,<=,>,>=,不等于
		mongoc_collection_t *collection = mongoc_client_get_collection(m_pClient, pDbName, pCollName);

		char strOnlyID[512]="", strOnlyName[512]="";
		bool b1=false,b2=false;
		const bson_t *doc;
		mongoc_cursor_t *cursor = mongoc_collection_find_with_opts (collection, pKey, NULL, NULL);
		while (mongoc_cursor_next (cursor, &doc)) {

			char *str = bson_as_json (doc, NULL); // utf8的字串；
			// 取出json中的主键id；
			char *pPos = strstr(str, strMainID);		
			if (pPos!=NULL){
				pPos += strlen(strMainID);

				char *pFirst = NULL;
				while(*pPos != 0){
					if(*pPos == ':'){
						pFirst = pPos+1;
					}	
					pPos++;

					if ((pFirst != NULL)&&(*pPos == ',')){
						*pPos=0;
						strcpy(strOnlyID, pFirst);
						*pPos=',';
						b1=true;
						break;
					}
				}
			}

			// 取出json中的主键id；  =》 整数类型；
			pPos = strstr(str, strMainName);		
			if (pPos!=NULL){
				pPos += strlen(strMainName);

				char *pFirst = NULL;
				while(*pPos != 0){
					if(*pPos == ':'){
						pFirst = pPos+1;
					}	
					pPos++;

					if ((pFirst != NULL)&&(*pPos == ',')){
						*pPos=0;
						strcpy(strOnlyName, pFirst);
						*pPos=',';
						b2=true;
						break;
					}
				}
			}

			// 取出json中的主键id；
			if (b1&&b2){
				mapIDName[atoi(strOnlyID)]=atoi(strOnlyName);
			}
		}


	end:
		mongoc_cursor_destroy (cursor);
		mongoc_collection_destroy(collection);
		bson_destroy (pKey);
	}
	catch(...){
		//WriteLog("QueryAndGetTableIDandName map<int,int> &mapIDName; catch error!");
		printf("BoardStr2MongoDB self stop job from QueryAndGetBoardStrTableMsg\n");
	}
	return bRet;
}

bool CCMongoDBOperator::QueryAndGetTableIDandName(map<int,string> &mapIDName,const char* pDbName, const char* pCollName, const char *strMainID,const char *strMainName)
{
	bson_t *pKey = BCON_NEW("_id", "{", "$ne", "", "}"); // "$lt","$lte","$gt","$gte",$ne分别对应<,<=,>,>=,不等于
	mongoc_collection_t *collection = mongoc_client_get_collection(m_pClient, pDbName, pCollName);

	char strOnlyID[512]="", strOnlyName[512]="";
	bool bRet = false,b1=false,b2=false;
	const bson_t *doc;
	mongoc_cursor_t *cursor = mongoc_collection_find_with_opts (collection, pKey, NULL, NULL);
	while (mongoc_cursor_next (cursor, &doc)) {

		char *str = bson_as_json (doc, NULL); // utf8的字串；
		
		// 取出json中的主键id； =》 取整数类型；
		char *pPos = strstr(str, strMainID);		
		if (pPos!=NULL){
			pPos += strlen(strMainID);

			char *pFirst = NULL;
			while(*pPos != 0){
				if(*pPos == ':'){
					pFirst = pPos+1;
				}	
				pPos++;

				if ((pFirst != NULL)&&(*pPos == ',')){
					*pPos=0;
					strcpy(strOnlyID, pFirst);
					*pPos=',';
					b1=true;
					break;
				}
			}
		}

		// 取出json中的主键id；    =》  取string类型；
		pPos = strstr(str, strMainName);		
		if (pPos!=NULL){
			pPos += strlen(strMainName);

			char *pFirst = NULL;
			char *pPosStart = NULL;
			while(*pPos != 0){
				if(*pPos == ':'){
					pFirst = pPos+1;
				}

				if((pFirst != NULL)&&(*pPos=='\"')){
					pPosStart = pPos+1;
				}
				pPos++;

				if ((pPosStart != NULL)&&(*pPos == '\"')){
					*pPos=0;
					strcpy(strOnlyName, pPosStart);	
					*pPos='\"';
					b2=true;
					break;
				}
			}
		}

		if (b1&&b2){
			mapIDName[atoi(strOnlyID)]=strOnlyName;
		}
	}


end:
	mongoc_cursor_destroy (cursor);
	mongoc_collection_destroy(collection);
	bson_destroy (pKey);

	return bRet;
}

bool CCMongoDBOperator::QueryAndGetTableIDandName(map<string,string> &mapIDName,const char* pDbName, const char* pCollName, const char *strMainID,const char *strMainName)
{
	bson_t *pKey = BCON_NEW("_id", "{", "$ne", "", "}"); // "$lt","$lte","$gt","$gte",$ne分别对应<,<=,>,>=,不等于
	mongoc_collection_t *collection = mongoc_client_get_collection(m_pClient, pDbName, pCollName);

	char strOnlyID[512]="", strOnlyName[512]="";
	bool bRet = false,b1=false,b2=false;
	const bson_t *doc;
	mongoc_cursor_t *cursor = mongoc_collection_find_with_opts (collection, pKey, NULL, NULL);
	while (mongoc_cursor_next (cursor, &doc)) {

		char *str = bson_as_json (doc, NULL); // utf8的字串；

		// 取出json中的主键id；
#if 0
		char *pPos = strstr(str, strMainID);		
		if (pPos!=NULL){
			pPos += strlen(strMainID);

			char *pFirst = NULL;
			while(*pPos != 0){
				if(*pPos == ':'){
					pFirst = pPos+1;
				}	
				pPos++;

				if ((pFirst != NULL)&&(*pPos == ',')){
					*pPos=0;
					strcpy(strOnlyID, pFirst);
					*pPos=',';
					b1=true;
					break;
				}
			}
		}
#endif
		char *pPos = strstr(str, strMainID);		
		if (pPos!=NULL){
			pPos += strlen(strMainID);

			char *pFirst = NULL;
			char *pPosStart = NULL;
			while(*pPos != 0){
				if(*pPos == ':'){
					pFirst = pPos+1;
				}

				if((pFirst != NULL)&&(*pPos=='\"')){
					pPosStart = pPos+1;
				}
				pPos++;

				if ((pPosStart != NULL)&&(*pPos == '\"')){
					*pPos=0;
					strcpy(strOnlyID, pPosStart);	
					*pPos='\"';
					b1=true;
					break;
				}
			}
		}

		// 取出json中的主键id；
		pPos = strstr(str, strMainName);		
		if (pPos!=NULL){
			pPos += strlen(strMainName);

			char *pFirst = NULL;
			char *pPosStart = NULL;
			while(*pPos != 0){
				if(*pPos == ':'){
					pFirst = pPos+1;
				}

				if((pFirst != NULL)&&(*pPos=='\"')){
					pPosStart = pPos+1;
				}
				pPos++;

				if ((pPosStart != NULL)&&(*pPos == '\"')){
					*pPos=0;
					strcpy(strOnlyName, pPosStart);	
					*pPos='\"';
					b2=true;
					break;
				}
			}
		}

		if (b1&&b2){
			mapIDName[strOnlyID]=strOnlyName;
		}
	}

end:
	mongoc_cursor_destroy (cursor);
	mongoc_collection_destroy(collection);
	bson_destroy (pKey);

	return bRet;
}

int CCMongoDBOperator::GetNeIDType(int neID, const char *pNeTable)
{
	char strOnlyID[10] = "";
	bson_t *pKey = BCON_NEW ("_id", BCON_INT32(neID));
	QueryAndGetTableOnlyID(strOnlyID, m_strTableName.c_str(), pNeTable, pKey, "neTypeNo");
	bson_destroy(pKey);
	return atoi(strOnlyID);
}

bool CCMongoDBOperator::QueryAndGetTableOnlyID(char *strOnlyID, const char* pDbName, const char* pCollName, bson_t * pKey, const char *strMainID)
{//  mongoc_client_pool_pop(pool);   mongoc_client_pool_push(pool, client);
#if IfDealSingleThread

#else
	//	::WaitForSingleObject(m_hMutex, INFINITE);
	::EnterCriticalSection((LPCRITICAL_SECTION)&m_critclSection);
#endif

	strcpy(strOnlyID, "");
	mongoc_collection_t *collection = mongoc_client_get_collection (m_pClient, pDbName, pCollName);

	bool bRet = false;
	const bson_t *doc;
	mongoc_cursor_t *cursor = mongoc_collection_find_with_opts (collection, pKey, NULL, NULL);
	while (mongoc_cursor_next (cursor, &doc)) {

			char *str = bson_as_json (doc, NULL); // utf8的字串；
			// 取出json中的z主键id；
			char *pPos = strstr(str, strMainID);		
			if (pPos!=NULL){
				pPos += strlen(strMainID);

				char *pFirst = NULL;
				while(*pPos != 0){
					if(*pPos == ':'){
						pFirst = pPos+1;
					}	
					pPos++;

					if ((pFirst != NULL)&&(*pPos == ',')){
						*pPos=0;
						strcpy(strOnlyID, pFirst);
						*pPos=',';				
						break;
					}
				}
			}
						
		//	printf ("%s\n", str);
		//	bson_free (str);		
	}


end:
	mongoc_cursor_destroy (cursor);
	mongoc_collection_destroy(collection);

#if IfDealSingleThread 

#else
	//	::ReleaseMutex(m_hMutex);//释放互斥量 
	::LeaveCriticalSection((LPCRITICAL_SECTION)&m_critclSection); 
#endif

	return bRet;
}


bool CCMongoDBOperator::DeleteAll(const char* pDbName, const char* pCollName)
{
	bson_t *pKey = BCON_NEW("_id", "{", "$ne", "", "}"); // "$lt","$lte","$gt","$gte",$ne分别对应<,<=,>,>=,不等于

	bool bIfDelSucess = Delete(pDbName, pCollName, pKey);

	bson_destroy (pKey);

	return bIfDelSucess;
}
