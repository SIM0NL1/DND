//
//  OverScrollView.h
//  XXL
//
//  Created by 5agame on 15/5/14.
//
//

#ifndef __XXL__OverScrollView__
#define __XXL__OverScrollView__

#include <iostream>
#include "cocos2d.h"
#include <extensions/cocos-ext.h>

USING_NS_CC;
USING_NS_CC_EXT;

class OverScrollView : public Layer,public ScrollViewDelegate
{
public:

	CREATE_FUNC(OverScrollView);
	virtual bool init();

	//scrollView滚动的时候会调用
	void scrollViewDidScroll(extension::ScrollView* view);
	//缩放的时候会调用
	void scrollViewDidZoom(extension::ScrollView* view);

	virtual void onEnter();
	virtual void onExit();

	virtual bool onTouchBegan(Touch* touch,Event* unused_event);
	virtual void onTouchMoved(Touch* touch,Event* unused_event);
	virtual void onTouchEnded(Touch* touch,Event* unused_event);
	virtual void onTouchCancelled(Touch* touch,Event* unused_event);

protected:
	OverScrollView();
	~OverScrollView();

	//根据手势滑动的距离和方向滚动图层
	void adjustScrollView(float offset);
	extension::ScrollView* m_pScrollView;
	Point m_startPoint,m_endPoint;


};

#endif /* defined(__XXL__OverScrollView__) */