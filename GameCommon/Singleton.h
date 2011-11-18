#pragma once

#include <cassert>

template<typename T>
class Singleton
{
public:
	Singleton(void);
	virtual ~Singleton();

	static T &instance(void);
	static T *instancePtr(void);

	static void destroySingleton(void);

private:
	static T*& getInnerPtr(void);
};

template<typename T>
inline Singleton<T>::Singleton(void)
{
}

template<typename T>
inline Singleton<T>::~Singleton(void)
{
}

template<typename T>
inline T &Singleton<T>::instance(void)
{
	return *instancePtr();
}

template<typename T>
inline T * Singleton<T>::instancePtr(void)
{
	T*& innerPtr = getInnerPtr();
	if (innerPtr == NULL) {
		innerPtr = new T;
	}

	innerPtr = getInnerPtr();
	assert(innerPtr != NULL);
	return innerPtr;
}

template<typename T>
inline void Singleton<T>::destroySingleton(void)
{
	T*& innerPtr = getInnerPtr();
	delete (innerPtr);
}

template<typename T>
inline T*& Singleton<T>::getInnerPtr(void)
{
	static T* innerPtr = NULL;
	return innerPtr;
}

