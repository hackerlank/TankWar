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

	//��ȡ����ָ��;
	static T* getSingletonPtr()
	{
		static T instance;
		return &instance;
	}

	//��ȡ��������;
	static T& getSingleton()
	{
		return *getSingletonPtr();
	}

protected:
	SingletonT(){}
	SingletonT(const SingletonT&);
	SingletonT& operator=(const SingletonT&);
};

//���嵥����Ϊ��Ԫ�ĺ�;
#define SINGLETON_DEFINE(classname) friend class SingletonT<classname>;

#endif