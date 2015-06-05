/*
    Author:Simon
    Date:  2015.5.13
    本类是一个公共头文件类,包含一些公共宏定义,枚举类型;
 */

#ifndef __GameDefine_H__
#define __GameDefine_H__

#include <iostream>
#include <vector>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
using namespace cocostudio;

const float PI = (3.1415926f);
const int MissionNum = 20;

//取到屏幕大小;
//const Size WIN_SIZE = Director::getInstance()->getWinSize();	//不知道为什么，总是0

//逻辑大小;
const Size GLB_SIZE = Size(640.f,1136.f);
//坐标比例;
//const float GLBX = WIN_SIZE.width/GLB_SIZE.width;
//const float GLBY = WIN_SIZE.height/GLB_SIZE.height;

//ZOrder
enum GameZOrder
{
	Z_Back = -1,
	Z_First = 3,
	Z_Second = 6,
	Z_Third = 9,
	Z_Fourth = 12,
	Z_Fifth = 15,
};
//Tag
enum GameTag
{
	T_Zero,
	T_First,
	T_Second,
	T_Third,
	T_Fourth,
	T_Fifth,
	T_Sixth,
};
//场景切换状态;
enum class SceneState
{
	UIGameNone,
	UIGameEnter,
	UIGameMain,
	UIGameMissionSet,
};
//关卡状态;
enum class GameMissionState
{
	MISSION_NOW,	//目前关卡;
	MISSION_OPEN,	//已开启卡;
	MISSION_CLOSE,	//未开启卡;
};
//关卡星级;
enum class GameMissionStart
{
	START_ZERO,
	START_ONE,
	START_TWO,
	START_THREE,
};
//Json文件;
enum class JsonFileType
{
	NORMALMISSIONPOS,
};
#endif