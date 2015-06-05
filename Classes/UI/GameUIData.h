//**************************************************************
//@创建者:   Simon;
//@创建时间: 2015/05/29;
//@功能描述①:UI数据单例;
//@功能描述②:Json读取，存储;
//@功能描述③:数据汇总;
//**************************************************************

#ifndef __GameUIData_H__ 
#define __GameUIData_H__

#include <iostream>
#include "cocos/platform/CCStdC.h"
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"


using namespace std;
using namespace rapidjson;
USING_NS_CC;
#include "GameDragonBase.h"
#include "GameDefine.h"

class GameDragonBase;
class GameUIData
{
public:
	GameUIData();
	~GameUIData();

	static GameUIData* m_self;
	static GameUIData* getInstance();
	void deleteInstance();
	void writeData();
	void readPosData(JsonFileType fileType);
	void readRoleData();
	void setIntegerForKey(string key,int data);
	void setBooleanForKey(string key,bool data);
	void setStringForKey(string key,string data);
	void setFloatForKey(string key,float data);
	Vec2 getMissionPos(int id);
	
	CC_SYNTHESIZE(int,normalMissionProgress,NormalMissionProgress);
	
	CC_SYNTHESIZE(int,challengeMissionProgress,ChallengeMissionProgress);
	vector<string> split(string str,string pattern);
	vector<GameDragonBase*> vec_Role;
private:
	vector<Vec2> missionpos;
};

#endif
