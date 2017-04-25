#pragma once

#include <iostream>
#include"Queue.h"

template<class T>
struct RBNode
{
	T data;
	RBNode<T>* left;
	RBNode<T>* right;
	RBNode<T>* parent;
	bool colour;
	RBNode<T>(T _data):data(_data),left(nullptr),right(nullptr),parent(nullptr),colour(false){};
	RBNode<T>(T _data,RBNode<T>* _blank):data(_data),left(_blank),right(_blank),parent(nullptr),colour(false){};
	RBNode<T>():left(nullptr),right(nullptr),parent(nullptr),colour(false){};
};

template<class T>
class CRBTree
{
public:
	CRBTree()
	{
		root = 0;
		blank = new RBNode<T>;
		blank->colour = true;
	}
	~CRBTree()
	{
		CQueue<RBNode<T>*> nodes;
		nodes.push_back(root);
        RBNode<T>* temp = 0;
		while(!nodes.IsEmpty())
		{
			temp = nodes.pop_front();
			if(exist(temp->left))
			{
				nodes.push_back(temp->left);
			}
			if(exist(temp->right))
			{
				nodes.push_back(temp->right);
			}
			delete temp;
		}
		delete blank;
	}
	bool Has(T data);
	bool Insert(T data);
	bool Delete (T data);
    void Dump(int k = 3)
    {
        Dump(root, k);
    }
private:
	RBNode<T>* root;
	RBNode<T>* blank;
	bool colour(RBNode<T>* node);
	void RotateLeft(RBNode<T>* node);
	void RotateRight(RBNode<T>* node);
    void Dump(RBNode<T>* root, int k);
	void InsertFix(RBNode<T>* node);
	void DeleteFix(RBNode<T>* node);
	void insert(T data);
	bool deleteNode(RBNode<T>* node);
	bool exist(RBNode<T>* node);
	RBNode<T>* findNode(T data);
};

template <class T>
void CRBTree<T>::Dump(RBNode<T>* root, int k)
{
    if (!root) return;

    Dump(root->right, k + 3);

    for (int i = 0; i < k; ++i) {
        std::cout << " ";
    }
    std::cout << "(" << root->data << ")" << std::endl;

    Dump(root->left, k + 3);
}

template<class T>
bool CRBTree<T>::exist(RBNode<T>* node)
{
	if(node == blank || node == 0)
		return false;
	return true;
}
template<class T>
bool CRBTree<T>::colour(RBNode<T>* node)
{
	return node == 0 ? true : node->colour;	
}
template<class T>
void CRBTree<T>::RotateLeft(RBNode<T>* node)
{
	RBNode<T>* temp = node->right;
	node->right = temp->left;
	if(exist(temp->left))
	{
		temp->left->parent = node;
	}
	if(exist(temp))
	{
		temp->parent = node->parent;
	}
	if(exist(node->parent))
	{
		if(node == node->parent->left)
		{
			node->parent->left = temp;
		} else
		{
			node->parent->right = temp;
		}
	} else
	{
		root = temp;
	}
	temp->left = node;
	if(exist(node)) node->parent = temp;
}
template<class T>
void CRBTree<T>::RotateRight(RBNode<T>* node)
{
	RBNode<T>* temp = node->left;
	node->right = temp->right;
	if(exist(temp->right))
	{
		temp->right->parent = node;
	}
	if(exist(temp))
	{
		temp->parent = node->parent;
	}
	if(exist(node->parent))
	{
		if(node == node->parent->right)
		{
			node->parent->right = temp;
		} else
		{
			node->parent->left = temp;
		}
	} else
	{
		root = temp;
	}
	temp->left = node;
	if(exist(node)) node->parent = temp;
}
template<class T>
void CRBTree<T>::InsertFix(RBNode<T>* node)
{
	while(node != root && colour(node->parent) == false)
	{
		if(node->parent == node->parent->left)
		{
			RBNode<T>* temp = node->parent->parent->right;
			if(colour(temp) == false)
			{
				//случай когда дядя красный
				node->parent->colour = true;
				temp->colour = true;
				node->parent->parent->colour = false;
				node = node->parent->parent;
			} else
			{
				// дядя черный
				if(node == node->parent->right)
				{
					node = node->parent;
					RotateLeft(node);
				}
				node->parent->colour = true;
				node->parent->parent->colour = false;
				RotateRight(node->parent->parent);
			}
		} else
		{
			RBNode<T>* temp = node->parent->parent->left;
			if(colour(temp) == false)
			{
				//случай когда дядя красный
				node->parent->colour = true;
				temp->colour = true;
				node->parent->parent->colour = false;
				node = node->parent->parent;
			} else
			{
				// дядя черный
				if(node == node->parent->left)
				{
					node = node->parent;
					RotateRight(node);
				}
				node->parent->colour = true;
				node->parent->parent->colour = false;
				RotateLeft(node->parent->parent);
			}
		}
	}
	root->colour = true;
}
template<class T>
void CRBTree<T>::DeleteFix(RBNode<T>* node)
{
	while(node != root && colour(node) == true)
	{
		if(node == node->parent->left)
		{
			RBNode<T>* temp = node->parent->right;
			if(colour(temp) == false)
			{
				temp->colour = true;
				node->parent->colour = false;
				RotateLeft(node->parent);
				temp  = node->parent->right;
			}
			if(colour(temp->left) == true && colour(temp->right) == true)
			{
				temp->colour = false;
				node = node->parent;
			} else
			{
				if(colour(temp->right) == true)
				{
					temp->left->colour = true;
					temp->colour = false;
					RotateRight(temp);
					temp = node->parent->right;
				}
				temp->colour = node->parent->colour;
				node->parent->colour = true;
				temp->right->colour = true;
				RotateLeft(node->parent);
				node = root;
			}
		} else
		{
			RBNode<T>* temp = node->parent->left;
			if(colour(temp) == false)
			{
				temp->colour = true;
				node->parent->colour = false;
				RotateRight(node->parent);
				temp  = node->parent->left;
			}
			if(colour(temp->right) == true && colour(temp->left) == true)
			{
				temp->colour = false;
				node = node->parent;
			} else
			{
				if(colour(temp->left) == true)
				{
					temp->right->colour = true;
					temp->colour = false;
					RotateLeft(temp);
					temp = node->parent->left;
				}
				temp->colour = node->parent->colour;
				node->parent->colour = true;
				temp->left->colour = true;
				RotateRight(node->parent);
				node = root;
			}
		}
    
	}
	node->colour = true;
}
template<class T>
void CRBTree<T>::insert(T data)
{
	RBNode<T>* current = root;
	RBNode<T>* parent = 0;
	RBNode<T>* node = 0;
	while(exist(current))
	{
		if(data == current->data) return;
		parent = current;
		current = data < current->data ? current->left : current->right;
	}
	node = new RBNode<T>(data,blank);
	node->parent = parent;
	if(parent != 0)
	{
		if( data < parent->data)
		{
			parent->left = node;
		} else
		{
			parent->right = node;
		} 
	}
	else {
			root = node;
		}
	InsertFix(node);
}
template<class T>
bool CRBTree<T>::deleteNode(RBNode<T>* node)
{
	RBNode<T>* temp1 = 0;
	RBNode<T>* temp2 = 0;
	if(!(exist(node))) return false;
	if(!(exist(node->left)) || !(exist(node->right)))
	{
		temp2 = node;
	} else
	{
		temp2 = node->right;
		while(exist(temp2->left)) temp2 = temp2->left;
	}
	if(exist(temp2->left))
	{
		temp1 = temp2->left;
	} else
	{
		temp1 = temp2->right;
	}
	temp1->parent = temp2->parent;
	if(exist(temp2->parent))
	{
		if(temp2 == temp2->parent->left)
		{
			temp2->parent->left = temp1;
		} else
		{
			temp2->parent->right = temp1;
		}
	} else
	{
		root = temp1;
	}
	if(temp2 != node) node->data = temp2->data;
	if(colour(temp2) == true)
		DeleteFix(node);
	delete node;
	return true;
}
template<class T>
RBNode<T>* CRBTree<T>::findNode(T data)
{
	RBNode<T>* current = root;
	while(exist(current))
	{
		if(data == current->data)
			return current;
		current = data < current->data ? current->left : current->right;
	}
	return 0;
}
template<class T>
bool CRBTree<T>::Has(T data)
{
	RBNode<T>* temp = findNode(data);
	if(temp!=0) return true;
	return false;
}
template<class T>
bool CRBTree<T>::Insert(T data)
{
	if(Has(data)) return false;
	insert(data);
	return true;
}
template<class T>
bool CRBTree<T>::Delete(T data)
{
	RBNode<T>* temp = findNode(data);
	return deleteNode(temp);
}