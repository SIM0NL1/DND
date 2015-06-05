//
//  OverView.cpp
//  authorr:Simon
//
//  Created by 5agame on 15/5/14.
//
//

#include "OverView.h"

OverView::OverView()
{
	//屏幕大小默认值
	window_size = Size(640.f,1136.f);
	//单元个数默认值
	cellNum = 12;
	//地图镜像
	fileMap = false;
}

OverView::~OverView()
{

}

// on "init" you need to initialize your instance
bool OverView::init()
{
	//初期化
	if ( !Layer::init() ) return false;

	tableView = TableView::create(this,window_size);
	//展开方向
	tableView->setDirection(TableView::Direction::VERTICAL);
	//表示上下顺序
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);

	//追加 托管
	tableView->setDelegate(this);
	addChild(tableView);
	tableView->reloadData();
	tableView->setBounceable(true);

	return true;
}

//设定单元格大小，宽，高
Size OverView::cellSizeForTable(TableView *table){
	return window_size;
}

//设计单元格内容
TableViewCell* OverView::tableCellAtIndex(TableView *table,ssize_t idx)
{    
	return nullptr;
}

// 单元格数量
ssize_t OverView::numberOfCellsInTableView(TableView *table)
{
	return cellNum;
}

// 触摸事件
void OverView::tableCellTouched(TableView* table, TableViewCell* cell)
{
	//log("第%zi个单元格", cell->getIdx());
	//tableView->setContentOffset(Vec2(0,tableView->getContentOffset().y-20.f));
}

void OverView::scrollViewDidScroll(extension::ScrollView* view)
{
	//log("now is scrolling");
	Point now = tableView->getContentOffset();
	if (now.y<-window_size.height*(cellNum-1))
	{
		tableView->setContentOffset(Vec2(0,-window_size.height*(cellNum-1)));
	}
	else if (now.y>0)
	{
		tableView->setContentOffset(Vec2(0,0));
	}
}

void OverView::scrollViewForDistance( float distance /*= -1*/ )
{
	if (distance==-1)
	{
		tableView->setContentOffset(Vec2(0,tableView->getContentSize().height));
	}
	else
	{
		tableView->setContentOffset(Vec2(0,tableView->getContentOffset().y+distance));	// 地图上移
	}
}

