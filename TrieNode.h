#ifndef _TRIENODE_H
#define _TRIENODE_H
#define ALPHABETS 26

using namespace std;
#include <iostream>
#include <string>

typedef char KeyType;
typedef int DataType;

class TrieNode
{
private:
	KeyType key; //character from a-z
	DataType data; //number of times the word appears
	TrieNode *parent;
	TrieNode *children[ALPHABETS];
	int minFullIndex;
	int NumOfChildren;

public:
	//*Constructor*
	TrieNode(KeyType key, DataType data, TrieNode *parent);
	//*Destructor*
	~TrieNode();

	friend class Trie;
};



#endif