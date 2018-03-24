#include "TrieNode.h"

TrieNode::TrieNode(KeyType key, DataType data, TrieNode *parent)
{
	this->key = key;
	this->data = data;
	this->parent = parent;
	this->NumOfChildren = 0;
	this->minFullIndex = 0;
	for (int i = 0; i < ALPHABETS; i++)
	{
		children[i] = nullptr;
	}
}

TrieNode::~TrieNode()
{
	if (NumOfChildren > 0)
	{
		for (int i = 0; i < ALPHABETS; i++)
		{
			if (children[i] != nullptr)
			{
				delete children[i];
			}
		}
	}
}
