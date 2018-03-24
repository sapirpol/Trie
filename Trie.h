#ifndef _TRIE_H
#define _TRIEE_H
#define MAX_WORD_SIZE 64

using namespace std;
#include <iostream>
#include <string>
#include "TrieNode.h"

class Trie
{
private:
	TrieNode *root;

public:
	//*Constructor*
	Trie();
	//*Destructor*
	~Trie();
	//insert word to trie
	void insert(string &word);
	//check if the word is in the trie format- if not, transform it according to the format
	string checkAndUpdateWord(string &word);
	//find approx word in the trie (according to the word was given)
	string approxFind(string & Str);
	//returns the last trie node of the word
	TrieNode *findLastTrieNode(string &word);
	//returns the number of occurences of the word
	int find(string & Str);
	//deletes the word was given
	void deleteWord (string &word);
	//check if the trie is empty
	bool isEmpty();
private:
	void deleteWordHelper(TrieNode *current, bool isLastTrieNode);
};

#endif
