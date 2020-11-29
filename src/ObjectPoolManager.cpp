#include "ObjectPoolManager.h"

template <class T>
ObjectPool<T>::ObjectPool(int size, bool deactivate(T*))
{
	assert(size > 0);

	pool = new PoolObject<T>[size];
	m_size = size;

	deactivate_test = deactivate;

	for (int i = 0; i < m_size; i++)
	{
		pool[i].object = new T();
		pool[i].inUse = false;
		pool[i].used = false;
		
		free_objects.push_back(&pool[i]);
	}
}

template <class T>
void ObjectPool<T>::Update()
{
	for (int i = 0; i < m_size; i++)
	{
		if (pool[i].inUse)
		{
			pool[i].object->update();
			if (deactivate_test(pool[i].object))
			{
				UnbindUsage(&pool[i]);
			}
		}
	}
}

template <class T>
void ObjectPool<T>::Draw()
{
	for (int i = 0; i < m_size; i++)
	{
		if (pool[i].inUse)
		{
			pool[i].object->draw();
		}
	}
}

template <class T>
void ObjectPool<T>::Clean()
{
	for (int i = 0; i < m_size; i++)
	{
		delete pool[i].object;
		pool[i].object = nullptr;
	}
}

template <class T>
void ObjectPool<T>::UnbindUsage(PoolObject<T>* object)
{
	object->inUse = false;
	free_objects.push_back(object);
}

template <class T>
T* ObjectPool<T>::GetFreeObject()
{
	if (!free_objects.empty())
	{
		PoolObject<T>* temp = free_objects.back();
		temp->inUse = true;
		temp->used = false;
		free_objects.pop_back();
		return temp->object;
	}
	else
	{
		std::cout << "Its empty\n";
	}

	return nullptr;
}
