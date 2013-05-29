/*
 * RocketBullet.h
 *
 *  Created on: June 28, 2012
 *      Author: xujie
 */
#include "BaseBullet.h"

class RocketBullet:public BaseBullet
{
public:
	RocketBullet();
	virtual ~RocketBullet();

	void Update();
	void Destroy();
};