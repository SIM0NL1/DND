//
//  GameUIData.cpp
//  author:Simon
//	
//  Created by 5agame on 15/5/18.
//	Json生成，读取;
//

#include "GameUIData.h"
#include "GameDragonBase.h"
#include "SupportTool.h"
#include "GameFunctions.h"

GameUIData* GameUIData::m_self = nullptr;
GameUIData::GameUIData()
{
	missionpos.clear();
	normalMissionProgress = 1;
	challengeMissionProgress = 1;
	vec_Role.clear();
}

GameUIData::~GameUIData()
{
}

GameUIData* GameUIData::getInstance()
{
	if (!m_self)
	{
		m_self = new GameUIData();
	}
	return m_self;
}

void GameUIData::deleteInstance()
{
	if (m_self)
	{
		delete(m_self);
	}
	m_self = nullptr;
}

void GameUIData::writeData()
{
	//生成Json文件，存储在getWriteablePath文件夹下;
	rapidjson::Document writedoc;
	writedoc.SetObject();
	rapidjson::Document::AllocatorType& allocator = writedoc.GetAllocator();
	// 	rapidjson::Value array(rapidjson::kArrayType);
	// 	rapidjson::Value object(rapidjson::kObjectType);
	// 	// json object 格式添加键值对;
	// 	object.AddMember("inttag", 1, allocator);  
	// 	object.AddMember("doubletag", 1.0, allocator);  
	// 	object.AddMember("booltag", true, allocator);  
	// 	object.AddMember("hellotag", "helloworld", allocator);
	// 	// json  
	// 	array.PushBack(object, allocator);  

	//json object  格式添加键值对;
	writedoc.AddMember("1_x",212,allocator);
	writedoc.AddMember("1_y",90,allocator);
	//	writedoc.AddMember("array", array, allocator);  

	StringBuffer buffer;  
	rapidjson::Writer<StringBuffer> writer(buffer);  
	writedoc.Accept(writer);

	auto path = FileUtils::getInstance()->getWritablePath();
	path.append("missionposition.json");
	FILE* file = fopen(path.c_str(), "wb");  
	if(file)  
	{  
		fputs(buffer.GetString(), file);  
		fclose(file);  
	}
	CCLOG("%s",buffer.GetString());  
}

void GameUIData::readPosData(JsonFileType fileType)
{

	rapidjson::Document readdoc;
	string load_str;

	//FileUtils::getInstance()->setWritablePath("E:\Project\XXL\Resources");
	//auto path = FileUtils::getInstance()->getWritablePath();
	//CCLOG("data path = %s",path.c_str());
	switch (fileType)
	{
	case JsonFileType::NORMALMISSIONPOS:
		//path.append("missionposition.json");
		//getFileData如果不指定，读取根目录是Resource文件夹;
		load_str = FileUtils::getInstance()->getStringFromFile(RESOURCE("uidata/missionposition.json"));
		break;
	default:
		break;
	}


	readdoc.Parse<0>(load_str.c_str());
	if(readdoc.HasParseError())
	{
		CCLOG("GetParseError%s\n",readdoc.GetParseError());
	}
	if(!readdoc.IsObject())
		return;

	switch (fileType)
	{
	case JsonFileType::NORMALMISSIONPOS:
		{
			missionpos.clear();
			for (int i=1;i<=MissionNum;++i)
			{
				string key_x = StringUtils::format("%d_x",i);
				string key_y = StringUtils::format("%d_y",i);
				rapidjson::Value& pos_x = readdoc[key_x.c_str()];
				rapidjson::Value& pos_y = readdoc[key_y.c_str()];
				if (pos_x.IsInt() && pos_y.IsInt())
				{
					Vec2 temp;
					temp.x=pos_x.GetInt();
					temp.y=pos_y.GetInt();
					missionpos.push_back(temp);
				}
			}
		}
	default:
		break;
	}
	return;  
}

void GameUIData::setIntegerForKey(string key,int data)
{

}

void GameUIData::setBooleanForKey(string key,bool data)
{

}

void GameUIData::setStringForKey(string key,string data)
{

}

void GameUIData::setFloatForKey(string key,float data)
{

}

cocos2d::Vec2 GameUIData::getMissionPos(int id)
{
	return missionpos.at(id-1);
}

void GameUIData::readRoleData()
{
	string filename = RESOURCE("uidata/roledata.json");
	rapidjson::Document doc;
	//判断文件是否存在;
	if (!FileUtils::getInstance()->isFileExist(filename))
	{
		CCLOG("roledata json file is not find [%s]",filename.c_str());
		return;
	}
	string data = FileUtils::getInstance()->getStringFromFile(filename);
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	//
	if (doc.HasParseError() || !doc.IsArray())
	{
		CCLOG("GetParseError%s\n",doc.GetParseError());
		return;
	}


	//
	for (unsigned int i=1;i<doc.Size();++i)
	{
		//
		rapidjson::Value &temp = doc[i];
		int j=0;		//
		GameDragonBase* pData = new GameDragonBase();
		pData->m_nDragonId = temp[j].GetInt();
		pData->m_sDragonChineseName = temp[++j].GetString();
		GameFunctions::getInstance()->g_sChineseName = pData->m_sDragonChineseName;
		pData->m_sEnglishName = temp[++j].GetString();
		//GameFunctions::getInstance()->g_sChineseName = pData->m_sEnglishName;
		pData->m_nDragonType = temp[++j].GetInt();
		pData->m_nUnlockType = temp[++j].GetInt();

		if (temp[++j].IsInt())
		{
			pData->m_aUnlockCondition.push_back(temp[j].GetInt());
			pData->m_aUnlockCondition.push_back(-7);
		}
		else if (temp[j].IsString())
		{
			string s = temp[j].GetString();
			string delim = "+";
			vector<string> str_temp = split(s,delim);
			for (size_t i=0;i<str_temp.size();++i)
			{
				pData->m_aUnlockCondition.push_back( atoi(str_temp.at(i).c_str()) );
			}
		}
		pData->m_nTrial = temp[++j].GetInt();
		pData->m_aPrice[0] = temp[++j].GetInt();
		pData->m_aPrice[1] = temp[++j].GetInt();
		pData->m_sAttribute = temp[++j].GetString();
		pData->m_nDragonLevel = temp[++j].GetInt();
		pData->m_sSkill	= temp[++j].GetString();
		pData->m_fImpair = temp[++j].GetDouble();
		pData->m_nSkillId = temp[++j].GetInt();
		pData->m_nSkillType = temp[++j].GetInt();
		pData->m_nCollect = temp[++j].GetInt();
		pData->m_sDescribe = temp[++j].GetString();
		pData->m_nSkillNum = temp[++j].GetInt();
		pData->m_nFeed = temp[++j].GetInt();
		pData->m_nUpGradeTotal = temp[++j].GetInt();
		pData->m_fDiscount = temp[++j].GetDouble();
		pData->m_sAnimate = temp[++j].GetString();
		pData->m_sImage = temp[++j].GetString();
		pData->m_sIcon = temp[++j].GetString();

		/*log(A2U("ID %d,中文名%s,英文名%s,角色类型%d,解锁类型%d,解锁条件%d,%d,试用关卡%d,召唤价格（解锁前）%d,（解锁后）%d,属性%s,角色等级%d,角色技能%s,伤害加成%f,技能ID%d,技能类型%d,发动技能收集元素%d,技能描述%s,技能值%d,单次喂养%d,升级总消耗%d,满级折扣%f,动作名%s,形象%s,角色Icon%s")
			,pData->m_nDragonId,pData->m_sDragonChineseName.c_str()
			,pData->m_sEnglishName.c_str()
			,pData->m_nDragonType
			,pData->m_nUnlockType
			,pData->m_aUnlockCondition[0]
		,pData->m_aUnlockCondition[1]
		,pData->m_nTrial,pData->m_aPrice[0]
		,pData->m_aPrice[1]
		,pData->m_sAttribute.c_str()
			,pData->m_nDragonLevel,pData->m_sSkill.c_str()
			,pData->m_fImpair,pData->m_nSkillId
			,pData->m_nSkillType
			,pData->m_nCollect
			,pData->m_sDescribe.c_str()
			,pData->m_nSkillNum
			,pData->m_nFeed
			,pData->m_nUpGradeTotal
			,pData->m_fDiscount
			,pData->m_sAnimate.c_str()
			,pData->m_sImage.c_str()
			,pData->m_sIcon.c_str()
			);
		//log(A2U("%d,中文名%s,英文名%s"),pData->m_nDragonId,pData->m_sDragonChineseName.c_str(),pData->m_sEnglishName.c_str());
        */

		vec_Role.push_back(pData);
	}

}

//
vector<string> GameUIData::split(string str,string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str+=pattern;
	//
	size_t size=str.size();
	for(size_t i=0; i<size; i++)
	{
		pos=str.find(pattern,i);
		if(pos<size)
		{
			std::string s=str.substr(i,pos-i);
			result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}
	return result;
}