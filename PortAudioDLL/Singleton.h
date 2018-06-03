#pragma once

#include <cassert>
#include<string>
#include<mutex>

class SingletonFinalizer
{
public:
	typedef void(*FinalizerFunc)();

	static void addFinalizer(FinalizerFunc func);
	static void finalize();
};

template <typename T>
class Singleton
{
public:
	static T& get_instance()
	{
		std::call_once(initFlag, create);
		assert(instance);
		return *instance;
	}

private:
	static void create() {
		instance = new T;
		SingletonFinalizer::addFinalizer(&Singleton<T>::destroy);
	}

	static void destroy() {
		delete instance;
		instance = nullptr;
	}

	static std::once_flag initFlag;
	static T* instance;
};

template <typename T> std::once_flag Singleton<T>::initFlag;
template <typename T> T* Singleton<T>::instance = nullptr;

