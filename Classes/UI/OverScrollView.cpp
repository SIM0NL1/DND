//
//  OverScrollView.cpp
//  XXL
//
//  Created by 5agame on 15/5/14.
//
//

#include "OverScrollView.h"

OverScrollView::OverScrollView()
{
	m_pScrollView = nullptr;
	m_startPoint = Point::ZERO;
	m_endPoint = Point :: ZERO;
}

OverScrollView::~OverScrollView()
{
}

bool OverScrollView::init()
{
	do
	{
		CC_BREAK_IF( !Layer::init() );      
		Layer *pLayer = Layer::create();

		for (int i=0; i<12; ++i)
		{
			Sprite* bg = Sprite :: create("map_001.png");
			bg->setAnchorPoint(Vec2::ZERO);
			bg->setPosition(Vec2(0.f,1136*i));
			pLayer->addChild(bg);
		}

		m_pScrollView = ScrollView::create(Size(640,1136), pLayer);
		m_pScrollView->setContentSize(Size(640.f,1136.f));
		m_pScrollView->setContentOffset(Point::ZERO);
		m_pScrollView->setTouchEnabled(true);
		m_pScrollView->setDelegate(this);
		m_pScrollView->setBounceable(false);
		m_pScrollView->setDirection(ScrollView::Direction::VERTICAL);
		pLayer->setContentSize(Size(640,1136*12));
		this->addChild(m_pScrollView);

		auto listener = EventListenerTouchOneByOne :: create();     //创建单点触摸监听
		//listener->setSwallowTouches(true);
		listener->onTouchBegan = CC_CALLBACK_2(OverScrollView::onTouchBegan,this);
		listener->onTouchMoved = CC_CALLBACK_2(OverScrollView::onTouchMoved,this);
		listener->onTouchEnded = CC_CALLBACK_2(OverScrollView::onTouchEnded,this);
		listener->onTouchCancelled = CC_CALLBACK_2(OverScrollView::onTouchCancelled,this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

		return true;

	}while(false);

	return false;

}


void OverScrollView::scrollViewDidScroll(cocos2d::extension::ScrollView *view)
{
	log(" now is scrolling ");
}

void OverScrollView::scrollViewDidZoom(cocos2d::extension::ScrollView *view)
{
	log(" now is zoom");
}

void OverScrollView::onEnter()
{
	Layer::onEnter();
	//Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
}

void OverScrollView::onExit()
{
	//Director::getInstance()->getTouchDispatcher()->removeDelegate(this);
	Layer::onExit();
}

bool OverScrollView::onTouchBegan(Touch* touch,Event* unused_event)
{
	//log("OverScrollView::TouchBegan------");
	// m_startPoint = Director::getInstance()->convertToGL(touch->getLocationInView

	m_startPoint = m_pScrollView->getContentOffset();

	log(" start x = %f",m_startPoint.x);
	log(" start y = %f",m_startPoint.y);

	return true;
}

void OverScrollView::onTouchMoved(Touch* touch,Event* unused_event)
{
	log("OverScrollView::TouchMoved------");
}

void OverScrollView::onTouchEnded(Touch* touch,Event* unused_event)
{
	log("OverScrollView::TouchEnded------");
	//  m_endPoint = Director::getInstance()->convertToGL(touch->getLocationInView());

	m_endPoint = m_pScrollView->getContentOffset();

	//log(" end x = %f",m_endPoint.x);
	//log(" end y = %f",m_endPoint.y);
	float distance_y = m_endPoint.y - m_startPoint.y;

	adjustScrollView(distance_y);

	//log(" distance y = %f",distance_y);
	//    if(fabs(distance) > 50)
	//    {
	//        adjustScrollView(distance);
	//    }

}

void OverScrollView::onTouchCancelled(Touch* touch,Event* unused_event)
{
	//    Point endPoint = Director::getInstance()->convertToGL(pTouch->getLocationInView());
	//    float distance = endPoint.x - m_touchPoint.x;
	//    if(fabs(distance) > 50)
	//    {
	//        adjustScrollView(distance);
	//    }
	log("OverScrollView::TouchCancelled------");
}

void OverScrollView::adjustScrollView(float offset)
{
	//Point origin = Director::getInstance()->getVisibleOrigin();


	//偏移量>0说明起点>终点,地图下移
	Vec2 now = m_pScrollView->getContentOffset();
	if (now.y<0 && now.y>-1136*11)
	{
		if (offset>0)
		{
			m_pScrollView->setContentOffsetInDuration(Vec2(0,now.y+100),0.5f);
		}
		else
		{
			m_pScrollView->setContentOffsetInDuration(Vec2(0,now.y-100),0.5f);
		}
	}

}

