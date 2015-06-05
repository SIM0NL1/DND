//
//	GameChallengeMission.cpp
//	Author:Simon
//	Date:  2015.5.21
//	本类作为特殊关卡节点父类
//	定义关卡基本属性：继承layout 坐标，状态，动画，按钮，图片，数字
//

#include "GameChallengeMission.h"
#include "GameUIData.h"

GameChallengeMission::GameChallengeMission()
{
	m_btnCandle = nullptr;
	m_labMissionId = nullptr;
	missionStartNum = 0;
	m_size = Size::ZERO;

}

GameChallengeMission::~GameChallengeMission()
{

}

bool GameChallengeMission::init()
{
	do 
	{
		CC_BREAK_IF(!Layout::init());

		initMission();

		return true;
	} while (false);
	CCLOG("Fun GameChallengeMission init ERROR");
	return false;
}

void GameChallengeMission::initMission()
{
	m_btnCandle = Button::create(RESOURCE("zhutai_01.png"),RESOURCE("zhutai_03.png"),RESOURCE("zhutai_02.png"));
	m_btnCandle->setTag(T_First);
	m_btnCandle->addTouchEventListener(CC_CALLBACK_2(GameChallengeMission::BtnCall,this));
	m_btnCandle->setAnchorPoint(Vec2(0.5f,0.5f));
	m_size = m_btnCandle->getContentSize();
	m_btnCandle->setPosition(Vec2(m_size.width*0.5,m_size.height*0.5));
	this->addChild(m_btnCandle,Z_First);

	m_labMissionId = Label :: createWithCharMap(RESOURCE("jindu_number.png"),16,25,'0');
	m_labMissionId->setAnchorPoint(Vec2(0.5f,0.5f));
	m_labMissionId->setPosition(Vec2(m_size.width*0.5,m_size.height*0.5));
	m_btnCandle->addChild(m_labMissionId);

}

void GameChallengeMission::setMissionState(GameMissionState state)
{
	switch (state)
	{
	case GameMissionState::MISSION_NOW:
		{
			missionNow();
			missionOpen();
			break;
		}
	case GameMissionState::MISSION_OPEN:
		{
			missionOpen();
			break;
		}
	case GameMissionState::MISSION_CLOSE:
		{
			m_btnCandle->setBright(false);
			m_btnCandle->setEnabled(false);
			break;
		}
	default:
		break;
	}
}

void GameChallengeMission::missionOpen()
{
	m_btnCandle->setBright(true);
	m_btnCandle->setEnabled(true);

	// 	ArmatureDataManager::getInstance()->addArmatureFileInfo("animature/");
	// 	Armature* candle = Armature::create("");
	// 	candle->setAnchorPoint(Vec2(0.5f,0.5f));
	// 	candle->setPosition(Vec2(m_size.width*0.5,m_size.height));
	// 	m_btnCandle->addChild(candle,Z_First);
	// 	candle->getAnimation()->playWithIndex(0);
}

void GameChallengeMission::missionNow()
{

}

void GameChallengeMission::BtnCall(Ref* pSender,Widget::TouchEventType type)
{
	int tag = ((Button*)pSender)->getTag();
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
	case Widget::TouchEventType::MOVED:
		GameFunctions::getInstance()->g_bFlagForMission = false;
		break;
	case Widget::TouchEventType::ENDED:
		{
			GameFunctions::getInstance()->g_bFlagForMission = true;
			if (tag)
			{
				onBtnCandle();
			}
			break;
		}
	case Widget::TouchEventType::CANCELED:
		GameFunctions::getInstance()->g_bFlagForMission = true;
		break;
	default:
		break;
	}
}

void GameChallengeMission::setBtnTouch(bool flag)
{
	m_btnCandle->setEnabled(flag);
}

void GameChallengeMission::onBtnCandle()
{
	int id = this->getTag();
	log(" %d GameChallengeMission :: onBtnCandle",id);
}

void GameChallengeMission::setMissionPorperty(int id)
{
	m_labMissionId->setString(StringUtils::format("%d",id));
	int challengeProgress = GameUIData::getInstance()->getChallengeMissionProgress();
	if (id < challengeProgress)
	{
		setMissionState(GameMissionState::MISSION_OPEN);
	} 
	else if (id == challengeProgress)
	{
		setMissionState(GameMissionState::MISSION_NOW);
	}
	else
	{
		setMissionState(GameMissionState::MISSION_CLOSE);
	}

}

void GameChallengeMission::setMissionStartNum(int missionId,int startNum)
{

}

void GameChallengeMission::missionShow(int missionId)
{
	//根据ID获取星星数量

	//设置星星显示
	static int startNum=1;
	for (int i=1;i<=startNum;++i)
	{
		Sprite* start = Sprite::create(RESOURCE(StringUtils::format("baoshi_00%d.png",i)));
		start->setAnchorPoint(Vec2::ZERO);
		start->setPosition(Vec2::ZERO);
		m_btnCandle->addChild(start,Z_First);
	}
	++startNum;
	if (startNum>3)
	{
		startNum=1;
	}
}
