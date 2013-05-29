/*
-----------------------------------------------------------------------------
This source file is part of SuperRacing (A Car Racing Game)

Copyright (c) 2009-2010 Kenshin

Usage of this program is free for non-commercial use and licensed under the
the terms of the MIT License.

for more info please visit 

http://superacing.sourceforge.net/forum
-----------------------------------------------------------------------------
*/

#pragma once
#include "stdafx.h"

/// GameService Protcol class,for Service which need update per frame

class IGameService
{
public:
	virtual void update(float dTime) = 0;
};