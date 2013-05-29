/*
 * SingletonT.h
 *
 *  Created on: June 23, 2012
 *      Author: hongxiaoqiang
 */

#ifndef SINGLETONT_H
#define SINGLETONT_H

template<typename T>
class SingletonT
{
public:
	virtual ~SingletonT(){}

	//获取单体指针;
	static T* getSingletonPtr()
	{
		static T instance;
		return &instance;
	}

	//获取单体引用;
	static T& getSingleton()
	{
		return *getSingletonPtr();
	}

protected:
	SingletonT(){}
	SingletonT(const SingletonT&);
	SingletonT& operator=(const SingletonT&);
};

//定义单体类为友元的宏;
#define SINGLETON_DEFINE(classname) friend class SingletonT<classname>;

#endif