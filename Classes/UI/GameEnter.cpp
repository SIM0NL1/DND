//**************************************************************
//@创建者:   Simon;
//@创建时间: 2015/05/29;
//@功能描述①: ;
//@功能描述②: ;
//@功能描述③: ;
//**************************************************************

#include "GameEnter.h"
#include "GameUIData.h"
#include "GameMain.h"
#include "GameSceneState.h"

GameEnter :: GameEnter()
{
}

GameEnter :: ~GameEnter()
{
}

Scene* GameEnter :: createScene()
{
    do {
        Scene* scene = Scene :: create();
        CC_BREAK_IF(!scene);
        GameEnter* pLayer = GameEnter :: create();
        CC_BREAK_IF(!pLayer);
        scene->addChild(pLayer);
        
        return scene;
    } while (false);
    log("Fun GameEnter :: createScene() ERROR ");
    return nullptr;
}

bool GameEnter :: init()
{
    do {
        CC_BREAK_IF(!Layer::init());
        Sprite* bg = Sprite :: create(RESOURCE("map_001.png"));
		bg->setAnchorPoint(Vec2::ZERO);
		bg->setPosition(Vec2::ZERO);
		this->addChild(bg);
		//
		CallFunc* loadData = CallFunc::create(CC_CALLBACK_0(GameEnter::loadJsonData,this));
        CallFunc* loadarmature = CallFunc::create(CC_CALLBACK_0(GameEnter::loadArmature,this));
		CallFunc* pEnter = CallFunc::create(CC_CALLBACK_0(GameEnter::enterGame,this));
		this->runAction(Sequence::create(loadData,loadarmature,pEnter,nullptr));
        
        return true;
    } while (false);
    log("Fun GameEnter :: init ERROR");
    return false;
}

void GameEnter :: enterGame()
{
	log("GameEnter :: enterGame ***********");
	SCENE_CHANGE_NORMAL(SceneState::UIGameMain);
}

void GameEnter::loadJsonData()
{
	GameUIData::getInstance()->setNormalMissionProgress(18);
	GameUIData::getInstance()->setChallengeMissionProgress(5);
	GameUIData::getInstance()->readPosData(JsonFileType::NORMALMISSIONPOS);
	for (int i=1;i<=MissionNum;++i)
	{
		Vec2 temp=GameUIData::getInstance()->getMissionPos(i);
		CCLOG("mission %d position x = %f,y = %f",i,temp.x,temp.y);
	}
	log("* >->->D * >->->D * >->->D * >->->D * >->->D *");
	GameUIData::getInstance()->readRoleData();
}

void GameEnter :: loadArmature()
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Anemoi0.png" , "Anemoi0.plist" , "Anemoi.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Apollo0.png" , "Apollo0.plist" , "Apollo.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Asteria0.png" , "Asteria0.plist" , "Asteria.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Cronus0.png" , "Cronus0.plist" , "Cronus.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Doris0.png" , "Doris0.plist" , "Doris.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Gaea0.png" , "Gaea0.plist" , "Gaea.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Hecate0.png" , "Hecate0.plist" , "Hecate.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("hephaestus0.png" , "hephaestus0.plist" , "hephaestus.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Hades0.png" , "Hades0.plist" , "Hades.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Hades_20.png" , "Hades_20.plist" , "Hades_2.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("nice_effect0.png" , "nice_effect0.plist" , "nice_effect.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("excellent_effect0.png" , "excellent_effect0.plist" , "excellent_effect.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("unbelievable_effect0.png" , "unbelievable_effect0.plist" , "unbelievable_effect.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("effect_xuanzhong0.png" , "effect_xuanzhong0.plist" , "effect_xuanzhong.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("effect_chuizi0.png" , "effect_chuizi0.plist" , "effect_chuizi.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("chuizi_icon0.png" , "chuizi_icon0.plist" , "chuizi_icon.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("jiawu_icon0.png" , "jiawu_icon0.plist" , "jiawu_icon.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("lingxing_icon0.png" , "lingxing_icon0.plist" , "lingxing_icon.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("mobang_icon0.png" , "mobang_icon0.plist" , "mobang_icon.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("nuqi_icon0.png" , "nuqi_icon0.plist" , "nuqi_icon.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("shizi_icon0.png" , "shizi_icon0.plist" , "shizi_icon.ExportJson");
    
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("effect_suilie0.png" , "effect_suilie0.plist" , "effect_suilie.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("effect_suilie1.png" , "effect_suilie1.plist" , "effect_suilie.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("effect_bingkuaisui0.png" , "effect_bingkuaisui0.plist" , "effect_bingkuaisui.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("effect_bingkuaisui1.png" , "effect_bingkuaisui1.plist" , "effect_bingkuaisui.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("effect_tiechuangsui0.png" , "effect_tiechuangsui0.plist" , "effect_tiechuangsui.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("tongsexiao0.png" , "tongsexiao0.plist" , "tongsexiao.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("blue_liang0.png" , "blue_liang0.plist" , "blue_liang.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("green_liang0.png" , "green_liang0.plist" , "green_liang.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("purple_liang0.png" , "purple_liang0.plist" , "purple_liang.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("red_liang0.png" , "red_liang0.plist" , "red_liang.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("white_liang0.png" , "white_liang0.plist" , "white_liang.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("yellow_liang0.png" , "yellow_liang0.plist" , "yellow_liang.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("hengxiao_effect0.png" , "hengxiao_effect0.plist" , "hengxiao_effect.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("jiugong01_effect0.png" , "jiugong01_effect0.plist" , "jiugong01_effect.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("jiugong02_effect0.png" , "jiugong02_effect0.plist" , "jiugong02_effect.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("bushu_ui0.png" , "bushu_ui0.plist" , "bushu_ui.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("guanqiamubiao_ui0.png" , "guanqiamubiao_ui0.plist" , "guanqiamubiao_ui.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("xialuojiantou0.png" , "xialuojiantou0.plist" , "xialuojiantou.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("hudun_effect0.png" , "hudun_effect0.plist" , "hudun_effect.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("buju_effect0.png" , "buju_effect0.plist" , "buju_effect.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("xialuojiantou0.png" , "xialuojiantou0.plist" , "xialuojiantou.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("tsx_eff0.png" , "tsx_eff0.plist" , "tsx_eff.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("jvqi_effect0.png" , "jvqi_effect0.plist" , "jvqi_effect.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("map01_line0.png" , "map01_line0.plist" , "map01_line.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("map01_yun0.png" , "map01_yun0.plist" , "map01_yun.ExportJson");
}


