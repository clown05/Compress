#pragma once

#include <vector>
#include <assert.h>
template<class T>
struct Less
{
	bool operator() (const T& l, const T& r)
	{
		return l < r;
	}
};

template<class T>
struct Greater
{
	bool operator() (const T& l, const T& r)
	{
		return l > r;
	}
};

template<class T, class Compare = Less<T>>
class Heap
{
public:
	Heap()
	{}

	Heap(const T* a, size_t size)
	{
		_a.reserve(size);
		for (size_t i = 0; i < size; ++i)
		{
			_a.push_back(a[i]);
		}

		// 建堆
		for (int i = (_a.size() - 2) / 2; i >= 0; --i)
		{
			_AdjustDown(i);
		}
	}

	Heap(vector<T>& a)
	{
		_a.swap(a);

		// 建堆
		for (int i = (_a.size() - 2) / 2; i >= 0; --i)
		{
			_AdjustDown(i);
		}
	}

	void Push(const T& x)
	{
		_a.push_back(x);

		_AdjustUp(_a.size() - 1);
	}

	void Pop()
	{
		size_t size = _a.size();
		assert(size > 0);

		swap(_a[0], _a[size - 1]);
		_a.pop_back();
		_AdjustDown(0);
	}

	T& Top()
	{
		assert(!_a.empty());
		return _a[0];
	}
	bool Empty()
	{
		return _a.size() == 0;
	}

	size_t Size()
	{
		return _a.size();
	}

	void Print()
	{
		for (int i = 0; i < _a.size(); i++)
		{
			cout << _a[i] << " ";
		}
		cout << endl;
	}

protected:
	void _AdjustUp(int child)
	{
		int parent = (child - 1) / 2;
		while (child > 0)
		{
			Compare com;
			if (com(_a[child], _a[parent]))
			{
				swap(_a[child], _a[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	void _AdjustDown(size_t parent)
	{
		size_t child = parent * 2 + 1;
		while (child < _a.size())
		{
			// 选出孩子里面大的那一个
			Compare com;
			if (child + 1 < _a.size()
				&& com(_a[child + 1], _a[child]))
			{
				++child;
			}

			// 如果父亲小于孩子，则交换并继续往下调整
			// 否则调堆完成
			if (com(_a[child], _a[parent]))
			{
				swap(_a[parent], _a[child]);
				parent = child;
				child = 2 * parent + 1;
			}
			else
			{
				break;
			}
		}
	}

protected:
	vector<T> _a;
};
