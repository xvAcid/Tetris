/*------------------------------------------
* File: Signleton.h
* Author: xvAcid
* Copyright: (c) WSG 2012
* Date: 09.11.2012
*-----------------------------------------*/

#pragma once

#define SINGLETON_DECLARATION(Class_Name)	\
	Class_Name(void);						\
	virtual ~Class_Name(void);				\
	friend class Singleton<Class_Name>;



template<class Type> class Singleton
{
protected:
	Singleton(void) {}
	Singleton(const Type &_self) {}
	virtual ~Singleton(void) {}

public:
	static Type *getSingleton(void)
	{
		if(self == 0)
		{
			self = new Type();
		}

		return self;
	}

	static bool isAvailable(void)
	{
		return (self != 0) ? true: false;
	}

	static bool deleteSingleton(void)
	{
		if(self != 0)
		{
			delete self;
			self = 0;
			return true;
		}
		
		return false;
	}

protected:
	static Type *self;
};

template <class Type> Type *Singleton<Type>::self = 0;
