/*
 * VerticalBullet.h 
 *
 *  Created on: June 28, 2012
 *      Author: xujie
 */
#include "BaseBullet.h"
class VerticalBullet:public BaseBullet
{
public:
	VerticalBullet();
	~VerticalBullet();

	void Update();
	void Destroy();
	void SetDistance(float Dis);
	
public:

private:
	               //垂直子弹要攻击的距离

};