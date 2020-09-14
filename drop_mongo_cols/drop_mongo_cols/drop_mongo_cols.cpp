// drop_mongo_cols.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <conio.h>
#include "../CMongoDBOperator.h"


int _tmain(int argc, _TCHAR* argv[])
{
	bool bRet = false;
	printf("this program will drop local mongodb's collections...\n");
	printf("who likes Biz_* and a\n");
	printf("y continue, and n to exit!!!\n");
	char ch = getchar();
	if (ch != 'y' && ch != 'Y')
	{
		return 0;
	}
	printf("\n\n");


	CCMongoDBOperator smg_db;
	std::string strIp("127.0.0.1"), bufPort("27017");
	std::string strUserName("admin"), strpasswd("admin");
	std::string strPipMongo("PiPeSuffix");
	smg_db.InitMongoDBData(strIp.c_str(), bufPort.c_str(), strUserName.c_str(), strpasswd.c_str(), strPipMongo.c_str());
	while (1)
	{
	 //  153 handles 4 threads
		bRet = smg_db.DropPipDBTable(strPipMongo.c_str());
		if (!bRet)
		{
			printf("DropPipDBTable failed, dbname=%s\n", strPipMongo.c_str());
			return 0;
		}

		Sleep(10);
	}

//	smg_db.ClearConnect(); //����ʱ�Զ��ͷ�
	
//	printf("DropPipDBTable succeed, dbname=%s\n", strPipMongo.c_str());

	getch();


	return 0;
}

