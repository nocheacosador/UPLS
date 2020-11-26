/*
 * Singleton.h
 *
 * Created: 10/19/2020 11:55:25
 *  Author: lukas
 */ 


#ifndef SINGLETON_H_
#define SINGLETON_H_

template <class T>
class Singleton
{
public:
	static T& instance()
	{
		static T _instance;
		return _instance;
	}

private:
	//Singleton();					// only available through instance() method
	//Singleton(const Singleton&);			// non construction-copyable
	//Singleton& operator=(const Singleton&); // non copyable
};


#endif /* SINGLETON_H_ */