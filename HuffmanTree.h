#pragma once

#include "Heap.h"

template<class T>
struct BinaryTreeNode
{
	T _value;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;

	BinaryTreeNode(const T& value)
		:_value(value)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class T>
class Huffman
{
	typedef BinaryTreeNode<T> Node;
public:
	Huffman(T* a, size_t size, T invalid)
	{
		_root = CreateHT(a, size, invalid);
	}

	struct CLess
	{
		bool operator() (Node*& l, Node*& r)
		{
			return l->_value < r->_value;
		}
	};

	Node* GetRoot()
	{
		return _root;
	}

protected:
	//利用小堆建Huffman树，使出现频率最小的做叶子节点
	Node* CreateHT(T* a, size_t size, T invalid)
	{
		Heap<Node*, CLess> lh;

		for (int i = 0;i < size;++i)
		{
			if (a[i] != invalid)
			{
				Node* cur = new Node(a[i]);
				lh.Push(cur);
			}
		}

		Node* parent = NULL;
		while (lh.Size() > 1)
		{
			//取第一小和第二小的作为叶子节点
			Node* minF = lh.Top();
			lh.Pop();
			Node* minS = lh.Top();
			lh.Pop();

			parent = new Node(minF->_value + minS->_value);
			parent->_left = minF;
			parent->_right = minS;

			//父节点要插入到小堆中再找第一小和第二小的作为叶子节点
			lh.Push(parent);
		}
		return parent;
	}

protected:
	Node* _root;
};
