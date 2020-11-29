#pragma once
#ifndef __OBJECTPOOL_H__
#define __OBJECTPOOL_H__
#include <cassert>
#include <iostream>
#include <list>

template <class T>
struct PoolObject
{
	T* object;
	bool inUse;
	bool used;
};

template <class T>
class ObjectPool
{
public:
	ObjectPool() : pool(nullptr), m_size(0) {}
	ObjectPool(int size, bool deactivate(T*));
	
	void Update();
	void Draw();
	void Clean();
	
	void UnbindUsage(PoolObject<T>* object);

	T* GetFreeObject();
	PoolObject<T>* GetObjectsPool() { return pool; }

	int GetSize() { return m_size; }
	
private:

	bool (*deactivate_test)(T*);
	
	std::list<PoolObject<T>*> free_objects;
	PoolObject<T>* pool;
	int m_size;
};

#endif
