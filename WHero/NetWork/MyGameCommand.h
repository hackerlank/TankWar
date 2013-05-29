
/*保存相应游戏场景的配置*/

#pragma once

#include "stdafx.h"
class MyGameCommand
{
	DECLARE_SINGLETON(MyGameCommand)
public:
	MyGameCommand(void);
	~MyGameCommand(void);

public:

	//UPG06000
	std::string mSelfTankName;
	bool	isServerOwner;
	int		mTankIndex;

	//map_index
	// 	int mMapIndex;
	// 	std::string mWeather;
	// 	std::string mLevel;
	// 	int mOpponentAmount;
	// 	int mCircle;
	// 	bool mN2O;
	// 	bool isMultiPlayMode;
	// 	//镜面反射更新率
	// 	float mReflexFrequency;

public :
	void SetMyInfomation(std::string playername ,std::string tankname ,int tankindex);


};
