//**************************************************************
//@创建者:   Simon;
//@创建时间: 2015/05/29;
//@功能描述①: ;
//@功能描述②: ;
//@功能描述③: ;
//**************************************************************

#include "GameMain.h"
#include "GameUIData.h"

const float _GAP = 0;
const int _COUNT = 2;

extern GameMain* g_pGameMain=nullptr;
GameMain :: GameMain()
{
	m_pPageView = nullptr;
	m_vStartPoint = Point::ZERO;
	m_vEndPoint = Point::ZERO;
	m_btnShop = nullptr;
	m_btnAchievement = nullptr;
	m_btnMagicBox = nullptr;
	m_btnRole = nullptr;
	tSize = Size::ZERO;
	m_btnHP = nullptr;
	m_btnLongBi = nullptr;
	m_btnDiamond = nullptr;
	m_labHP = nullptr;
	m_labLongBi = nullptr;
	m_labDiamond = nullptr;
	g_pGameMain = this;
	normallayer = nullptr;
	challengelayer = nullptr;
}

GameMain :: ~GameMain()
{
}

Scene* GameMain :: createScene()
{
    do {
        Scene* scene = Scene :: create();
        CC_BREAK_IF(!scene);
        GameMain* pLayer = GameMain :: create();
        CC_BREAK_IF(!pLayer);
        scene->addChild(pLayer);
        return scene;
    } while (false);
    log("Fun GameMain :: createScene ERROR");
    return nullptr;
}

bool GameMain :: init()
{
    do{
        CC_BREAK_IF(!Layer::init());
        showUI();
		initMap();

		//Label* pName = Label::createWithSystemFont(GameFunctions::getInstance()->g_sChineseName,"Arial",30.f);
// 		string text = StringUtils::format( "%d",GameUIData::getInstance()->vec_Role.at(20)->m_aUnlockCondition.at(2) );
// 		Label* pName = Label::createWithSystemFont(text,"Arial",30.f);
// 		pName->setPosition(Vec2(GLB_SIZE.width*0.5,GLB_SIZE.height*0.5));
// 		this->addChild(pName,Z_Third);
// 		pName->setColor(Color3B(0,0,0));

        return true;
    } while (false);
    log("Fun GameMain :: init ERROR");
    return false;
}

//
void GameMain :: showUI()
{
    log("------GameMain :: showUI------");
	Sprite* tiliRect = Sprite :: create(RESOURCE("tili_01.png"));
	tiliRect->setAnchorPoint(Vec2(0.5f,0.5f));
	tSize = tiliRect->getContentSize();
	tiliRect->setPosition(Vec2(tSize.width*0.5,GLB_SIZE.height-tSize.height*0.5));
    this->addChild(tiliRect,Z_Second);

	Sprite* tiliBack = Sprite :: create(RESOURCE("tili_02.png"));
	tiliBack->setAnchorPoint(Vec2(0.5,0.5));
	tiliBack->setPosition(Vec2(tSize.width*0.5,tSize.height*0.5));
	tiliRect->addChild(tiliBack);

	Size dibanSize;
	for (int i=0;i<3;++i)
	{
		Sprite* diban = Sprite :: create(RESOURCE("diban01.png"));
		diban->setTag(100+i*100);
		dibanSize = diban->getContentSize();
		diban->setAnchorPoint(Vec2(0.5f,0.5f));
		diban->setPosition(Vec2(tSize.width+dibanSize.width*0.5-40.f+i*(55.f+dibanSize.width),GLB_SIZE.height-dibanSize.height));
		this->addChild(diban,Z_First);
	}
	
	topBtnTemplate(m_btnHP,dibanSize,0);
	topBtnTemplate(m_btnLongBi,dibanSize,1);
	topBtnTemplate(m_btnHP,dibanSize,2);

	m_btnShop = Button :: create(RESOURCE("shangdian_01.png"),RESOURCE("shangdian_02.png"));
	m_btnShop->setAnchorPoint(Vec2(0.5f,0.5f));
	m_btnShop->setTag(BtnShop);
	Size btnSize = m_btnShop->getContentSize();
	m_btnShop->setPosition(Vec2(btnSize.width*0.5+10.f,btnSize.height*0.5));
	this->addChild(m_btnShop,Z_First);
	m_btnShop->addTouchEventListener(CC_CALLBACK_2(GameMain::BtnCall,this));

	m_btnAchievement = Button :: create(RESOURCE("chengjiu_01.png"),RESOURCE("chengjiu_02.png"));
	m_btnAchievement->setAnchorPoint(Vec2(0.5f,0.5f));
	m_btnAchievement->setTag(BtnAchievement);
	m_btnAchievement->setPosition(Vec2(btnSize.width*1.5+10.f,btnSize.height*0.5));
	this->addChild(m_btnAchievement,Z_First);
	m_btnAchievement->addTouchEventListener(CC_CALLBACK_2(GameMain::BtnCall,this));

	m_btnMagicBox = Button :: create(RESOURCE("moxiang_01.png"),RESOURCE("moxiang_02.png"));
	m_btnMagicBox->setAnchorPoint(Vec2(0.5f,0.5f));
	m_btnMagicBox->setTag(BtnMagicBox);
	m_btnMagicBox->setPosition(Vec2(btnSize.width*2.5+10.f,btnSize.height*0.5));
	this->addChild(m_btnMagicBox,Z_First);
	m_btnMagicBox->addTouchEventListener(CC_CALLBACK_2(GameMain::BtnCall,this));

	m_btnRole = Button :: create(RESOURCE("juese_01.png"),RESOURCE("juese_02.png"));
	m_btnRole->setAnchorPoint(Vec2(0.5f,0.5f));
	m_btnRole->setTag(BtnRole);
	m_btnRole->setPosition(Vec2(btnSize.width*3.5+10.f,btnSize.height*0.5));
	this->addChild(m_btnRole,Z_First);
	m_btnRole->addTouchEventListener(CC_CALLBACK_2(GameMain::BtnCall,this));

	//
	m_btnEndless = Button :: create(RESOURCE("wujin_01.png"),RESOURCE("wujin_02.png"));
	m_btnEndless->setAnchorPoint(Vec2(0.5f,0.5f));
	m_btnEndless->setTag(BtnEndless);
	Size btnSize2 = m_btnEndless->getContentSize();
	m_btnEndless->setPosition(Vec2(btnSize2.width*0.5-10.f,GLB_SIZE.height-tSize.height-35.f));
	this->addChild(m_btnEndless,Z_First);
	m_btnEndless->addTouchEventListener(CC_CALLBACK_2(GameMain::BtnCall,this));
	m_btnEndless->setEnabled(true);
	m_btnEndless->setOpacity(255);

	m_btnRegisterLeft = Button :: create(RESOURCE("qiandao_01.png"),RESOURCE("qiandao_02.png"));
	m_btnRegisterLeft->setAnchorPoint(Vec2(0.5f,0.5f));
	m_btnRegisterLeft->setTag(BtnRegisterLeft);
	m_btnRegisterLeft->setPosition(Vec2(btnSize2.width*0.5-10.f,GLB_SIZE.height-tSize.height*1.5-50.f));
	this->addChild(m_btnRegisterLeft,Z_First);
	m_btnRegisterLeft->addTouchEventListener(CC_CALLBACK_2(GameMain::BtnCall,this));
	m_btnRegisterLeft->setEnabled(true);
	m_btnRegisterLeft->setOpacity(255);

	m_btnNewManGift = Button :: create(RESOURCE("xinshou_01.png"),RESOURCE("xinshou_02.png"));
	m_btnNewManGift->setAnchorPoint(Vec2(0.5f,0.5f));
	m_btnNewManGift->setTag(BtnNewManGift);
	m_btnNewManGift->setPosition(Vec2(btnSize2.width*0.5-10.f,GLB_SIZE.height-tSize.height*2-60.f));
	this->addChild(m_btnNewManGift,Z_First);
	m_btnNewManGift->addTouchEventListener(CC_CALLBACK_2(GameMain::BtnCall,this));
	m_btnNewManGift->setEnabled(true);
	m_btnNewManGift->setOpacity(255);

	m_btnMagicBook = Button :: create(RESOURCE("mofashu_01.png"),RESOURCE("mofashu_02.png"));
	m_btnMagicBook->setAnchorPoint(Vec2(0.5f,0.5f));
	m_btnMagicBook->setTag(BtnMagicBook);
	m_btnMagicBook->setPosition(Vec2(GLB_SIZE.width-btnSize2.width*0.5,GLB_SIZE.height-tSize.height-35.f));
	this->addChild(m_btnMagicBook,Z_First);
	m_btnMagicBook->addTouchEventListener(CC_CALLBACK_2(GameMain::BtnCall,this));
	m_btnMagicBook->setEnabled(false);
	m_btnMagicBook->setOpacity(0);

	m_btnRegisterRight = Button :: create(RESOURCE("qiandao_01.png"),RESOURCE("qiandao_02.png"));
	m_btnRegisterRight->setAnchorPoint(Vec2(0.5f,0.5f));
	m_btnRegisterRight->setTag(BtnRegisterRight);
	m_btnRegisterRight->setPosition(Vec2(GLB_SIZE.width-btnSize2.width*0.5,GLB_SIZE.height-tSize.height*1.5-60.f));
	this->addChild(m_btnRegisterRight,Z_First);
	m_btnRegisterRight->addTouchEventListener(CC_CALLBACK_2(GameMain::BtnCall,this));
	m_btnRegisterRight->setEnabled(false);
	m_btnRegisterRight->setOpacity(0);
}

void GameMain::topBtnTemplate(Button* pSender,Size temp,int fatherId)
{
	pSender = Button::create(RESOURCE("add_01.png"),RESOURCE("add_02.png"));
	pSender->setAnchorPoint(Vec2(0.5f,0.5f));
	pSender->setPosition(Vec2(temp.width,temp.height*0.5));
	pSender->addTouchEventListener(CC_CALLBACK_2(GameMain::BtnCall,this));
	(this->getChildByTag(100+fatherId*100))->addChild(pSender);
	Sprite* Icon=nullptr;
	switch (fatherId)
	{
	case 0:
		{
			pSender->setTag(BtnHP);
			//(RESOURCE("shuliang_number.png"),18,27,'0');
			m_labHP = Label::createWithCharMap(RESOURCE("shuliang_number.png"),16,27,'0');//(RESOURCE("jindu_number.png"),16,25,'0');
			m_labHP->setAnchorPoint(Vec2(1.f,0.5f));
			m_labHP->setPosition(Vec2(temp.width-20.f,temp.height*0.5));
			m_labHP->setString("99:99");
			(this->getChildByTag(100+fatherId*100))->addChild(m_labHP);

			break;
		}
	case 1:
		{
			pSender->setTag(BtnLongBi);
			Icon = Sprite::create(RESOURCE("longbi_icon.png"));

			m_labLongBi = Label::createWithCharMap(RESOURCE("shuliang_number.png"),16,27,'0');
			m_labLongBi->setAnchorPoint(Vec2(1.f,0.5f));
			m_labLongBi->setPosition(Vec2(temp.width-20.f,temp.height*0.5));
			m_labLongBi->setString("9999");
			(this->getChildByTag(100+fatherId*100))->addChild(m_labLongBi);

			break;
		}
		
	case 2:
		{
			pSender->setTag(BtnDiamond);
			Icon = Sprite::create(RESOURCE("shuijing_icon.png"));

			m_labDiamond = Label::createWithCharMap(RESOURCE("shuliang_number.png"),16,27,'0');
			m_labDiamond->setAnchorPoint(Vec2(1.f,0.5f));
			m_labDiamond->setPosition(Vec2(temp.width-20.f,temp.height*0.5));
			m_labDiamond->setString("99999");
			(this->getChildByTag(100+fatherId*100))->addChild(m_labDiamond);

			break;
		}
	default:
		break;
	}
	if (fatherId)
	{
		Icon->setAnchorPoint(Vec2(0.5f,0.5f));
		Icon->setPosition(Vec2(0.f,temp.height*0.5));
		(this->getChildByTag(100+fatherId*100))->addChild(Icon);
	}
}

void GameMain::initMap()
{
	m_pPageView = OverPageView::create(GLB_SIZE,this);
	m_pPageView->setDirection(extension::ScrollView::Direction::HORIZONTAL);
	m_pPageView->setAnchorPoint(Vec2::ZERO);
	m_pPageView->setPosition(Vec2::ZERO);

	normallayer = GameNormalMap :: create();
	normallayer->setAnchorPoint(Vec2::ZERO);
	normallayer->setPosition(Vec2::ZERO);
	challengelayer = GameChallengeMap :: create();
	challengelayer->setAnchorPoint(Vec2::ZERO);
	challengelayer->setPosition(Vec2(0,0));
	for (int i=1;i<=2;++i)
	{
		Layout* layout = Layout :: create();
		layout->setAnchorPoint(Vec2::ZERO);
		layout->setPosition(Vec2::ZERO);
		layout->setContentSize(Size(GLB_SIZE));
		if (i&1)
		{
			layout->addChild(normallayer,Z_First);
			
		}
		else
		{
			layout->addChild(challengelayer,Z_First);
			ArmatureDataManager::getInstance()->addArmatureFileInfo(RESOURCE("animature/qiehuan_map/qiehuan_map0.png"),RESOURCE("animature/qiehuan_map/qiehuan_map0.plist"),RESOURCE("animature/qiehuan_map/qiehuan_map.ExportJson"));
			//
			Armature* qiehuan = Armature::create("qiehuan_map");
			qiehuan->setAnchorPoint(Vec2(0.5f,0.5f));
			qiehuan->setPosition(Vec2(0.f,GLB_SIZE.height*0.5+80.f));
			layout->addChild(qiehuan,Z_First);
			//
			qiehuan->getAnimation()->playWithIndex(0);
			Button* pChmap = Button :: create(RESOURCE("CloseNormal.png"),RESOURCE("CloseSelected.png"));
			pChmap->setAnchorPoint(Vec2(0.5f,0.5f));
			pChmap->setPosition(Vec2(0.f,GLB_SIZE.height*0.5+80.f));
			layout->addChild(pChmap,Z_Second);
			pChmap->addTouchEventListener(CC_CALLBACK_2(GameMain::onBtnChmap,this));

		}
		m_pPageView->addPage(layout);
	}
	
	m_pPageView->setClippingToBounds(false);
	m_pPageView->setBounceable(false);
	this->addChild(m_pPageView);

	slide = GameSlide::create();
	slide->setAnchorPoint(Vec2::ZERO);
	slide->setPosition(Vec2::ZERO);
	this->addChild(slide,Z_Third);

	slide->listener->setEnabled(false);
	controlPageView(false);
}

void GameMain::onBtnChmap(Ref* pSender,Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		slide->listener->setEnabled(true);
		controlPageView(true);
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		//slide->listener->setEnabled(false);
		//controlPageView(false);
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		//slide->listener->setEnabled(false);
		//controlPageView(false);
		break;
	default:
		break;
	}
}

Size GameMain::sizeForPerPage()
{
	return Size(GLB_SIZE.width+_GAP,GLB_SIZE.height);
}

void GameMain::pageViewDidScroll(OverPageView* pageView)
{
	//监听滚动事件，滚动时的操作;
	CCLOG("GameMain OverPageView pageViewDidScroll");
// 	if(!m_pPageView->getTurning())
// 	{
// 		int id = m_pPageView->getCurPageIndex();
// 		ensureBtnFade(id);
// 	}
}

void GameMain::setBtnTouch(bool flag)
{
// 	m_btnShop->setEnabled(flag);
// 	m_btnAchievement->setEnabled(flag);
// 	m_btnMagicBox->setEnabled(flag);
// 	m_btnRole->setEnabled(flag);
	m_btnEndless->setEnabled(flag);
	m_btnRegisterLeft->setEnabled(flag);
	m_btnNewManGift->setEnabled(flag);
// 	m_btnHP->setEnabled(flag);
// 	m_btnLongBi->setEnabled(flag);
// 	m_btnDiamond->setEnabled(flag);
	m_btnMagicBook->setEnabled(flag);
	m_btnRegisterRight->setEnabled(flag);
}

void GameMain::BtnCall(Ref* pSender,Widget::TouchEventType type)
{
	int tag = ((Button*)pSender)->getTag();
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		switch(tag)
		{
		case BtnShop:
			onBtnShop();
			break;
		case BtnAchievement:
			onBtnAchievement();
			break;
		case BtnMagicBox:
			onBtnMagicBox();
			break;
		case BtnRole:
			onBtnRole();
			break;
		case BtnEndless:
			onBtnEndless();
			break;
		case BtnRegisterLeft:
			onBtnRegisterLeft();
			break;
		case BtnRegisterRight:
			onBtnRegisterRight();
			break;
		case BtnNewManGift:
			onBtnNewManGift();
			break;
		case BtnMagicBook:
			onBtnMagicBook();
			break;
		case BtnHP:
			onBtnHP();
			break;
		case BtnLongBi:
			onBtnLongBi();
			break;
		case BtnDiamond:
			onBtnDiamond();
			break;
		}
		break;
	default:
		break;
	}
}

void GameMain::setLeftBtnFadeInterface(int opacity)
{
	log(" left opacity = %d",opacity);
	m_btnEndless->setOpacity(opacity);
	m_btnRegisterLeft->setOpacity(opacity);
	m_btnNewManGift->setOpacity(opacity);
	m_btnMagicBook->setOpacity(0);
	m_btnRegisterRight->setOpacity(0);
}

void GameMain::setRightBtnFadeInterface(int opacity)
{
	log(" right opacity = %d",opacity);
	m_btnEndless->setOpacity(0);
	m_btnRegisterLeft->setOpacity(0);
	m_btnNewManGift->setOpacity(0);
	m_btnMagicBook->setOpacity(opacity);
	m_btnRegisterRight->setOpacity(opacity);
}

int GameMain::getPageViewId()
{
	return m_pPageView->getCurPageIndex();
}

void GameMain::controlPageView(bool flag)
{
	m_pPageView->listener->setEnabled(flag);
}

void GameMain::controlTableView(bool flag)
{
	normallayer->tableView->setTouchEnabled(flag);		
	challengelayer->tableView->setTouchEnabled(flag);
}

//
void GameMain::ensureBtnFade(int id)
{
	if (id)
	{
		m_btnEndless->setEnabled(false);
		m_btnEndless->setOpacity(0);
		m_btnRegisterLeft->setEnabled(false);
		m_btnRegisterLeft->setOpacity(0);
		m_btnNewManGift->setEnabled(false);
		m_btnNewManGift->setOpacity(0);
		m_btnMagicBook->setEnabled(true);
		m_btnMagicBook->setOpacity(255);
		m_btnRegisterRight->setEnabled(true);
		m_btnRegisterRight->setOpacity(255);
	}
	else
	{
		m_btnEndless->setEnabled(true);
		m_btnEndless->setOpacity(255);
		m_btnRegisterLeft->setEnabled(true);
		m_btnRegisterLeft->setOpacity(255);
		m_btnNewManGift->setEnabled(true);
		m_btnNewManGift->setOpacity(255);
		m_btnMagicBook->setEnabled(false);
		m_btnMagicBook->setOpacity(0);
		m_btnRegisterRight->setEnabled(false);
		m_btnRegisterRight->setOpacity(0);
	}
}

void GameMain::onBtnShop()
{
	log("********GameMain::onBtnShop**********");

}

void GameMain::onBtnAchievement()
{
	log("********GameMain::onBtnAchievement**********");
}

void GameMain::onBtnMagicBox()
{
	log("********GameMain::onBtnMagicBox**********");
}

void GameMain::onBtnRole()
{
	log("********GameMain::onBtnRole**********");
}

void GameMain::onBtnEndless()
{
	log("********GameMain::onBtnEndless**********");
}

void GameMain::onBtnRegisterLeft()
{
	log("********GameMain::onBtnRegisterLeft**********");
}

void GameMain::onBtnNewManGift()
{
	log("********GameMain::onBtnNewManGift**********");
}

void GameMain::onBtnRegisterRight()
{
	log("********GameMain::onBtnRegisterRight**********");
}

void GameMain::onBtnMagicBook()
{
	log("********GameMain::onBtnMagicBook**********");
}

void GameMain::onBtnHP()
{
	log("********GameMain::onBtnHP**********");
}

void GameMain::onBtnLongBi()
{
	log("********GameMain::onBtnLongBi**********");
}

void GameMain::onBtnDiamond()
{
	log("********GameMain::onBtnDiamond**********");
}
