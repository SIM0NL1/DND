//
//  GameFunctions.h
//  author:Simon
//
//  Created by 5agame on 15/5/14.
//  实现项目中公共的方法，这是一个工具类;
//  单例实现;

#ifndef XXL_GameFunctions_h
#define XXL_GameFunctions_h

#include "GameDefine.h"
#include "GameSceneState.h"

//切换场景;
#define SCENE_CHANGE_NORMAL(myscene) GameSceneState :: getInstance()->switchScene(myscene);
#define SCENE_CHANGE_FADE(myscene) GameSceneState :: getInstance()->switchScene(myscene,0.5f);

//读取资源;
#define RESOURCE(_STR_PATH_) GameFunctions::getInstance()->readResourcesPath(_STR_PATH_)

class GameFunctions : public Ref
{
public:
	static GameFunctions* getInstance();
	static void deleteGameFunctions();
	const char* readResourcesPath(string fileName);
	bool g_bFlagForMission;		//关卡按钮的移动触摸干扰了地图的移动，特设此标记;
	string g_sChineseName;

private:
	GameFunctions();
	virtual ~GameFunctions();
	static GameFunctions* m_self;
	string m_sFilePath;
};
#endif
