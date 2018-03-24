#include "TrieNode.h"
#include "Trie.h"
#include <string>
#define CHARACTER 'a'
#define MAX_WORD_LEN 64
#define ALPHABETS 26

Trie::Trie()
{
	root = new TrieNode ('.', 0, nullptr);
}

Trie::~Trie()
{
		delete root;
}

bool Trie::isEmpty()
{
	if (root->NumOfChildren == 0)
		return true;
	return false;
}

void Trie::insert(string &word)
{
	TrieNode *current = root;
	int i = 0;
	//we want to save the last character for updating the number of word ocurrences
	while (i+1!=word.length())
	{
		//there is no suitable TrieNode for this character
		if (current->children[word.at(i) - CHARACTER] == nullptr)
		{
			if(current->NumOfChildren==0)
				current->minFullIndex = word.at(i) - CHARACTER;
			else if (word.at(i) - CHARACTER < current->minFullIndex)
				current->minFullIndex = word.at(i) - CHARACTER;
			current->children[word.at(i) - CHARACTER] = new TrieNode(word.at(i), 0, current);	
			++current->NumOfChildren;
		}
		//we check if the index of the character is smaller than the index of the previous min - used for approxFind
		else
		{
			if (word.at(i) - CHARACTER < current->minFullIndex)
				current->minFullIndex = word.at(i) - CHARACTER;
		}
		current = current->children[word[i] - CHARACTER];
		++i;
	}
	//increasing word ocurrences
	if (current->children[word.at(i) - CHARACTER] == nullptr)
	{
		if (current->NumOfChildren == 0)
			current->minFullIndex = word.at(i) - CHARACTER;
		else if (word.at(i) - CHARACTER < current->minFullIndex)
			current->minFullIndex = word.at(i) - CHARACTER;
		current->children[word.at(i) - CHARACTER] = new TrieNode(word.at(i), 1, current);
	}
	else
	{
		++current->children[word.at(i) - CHARACTER]->data;
		if (word.at(i) - CHARACTER < current->minFullIndex)
			current->minFullIndex = word.at(i) - CHARACTER;
	}
	//for the parent of the last node
	if (current->NumOfChildren == 0)
		++current->NumOfChildren;
}

string Trie::checkAndUpdateWord(string &word)
{
	//move all over the word
	for (int i = 0; i < word.length(); i++)
	{
		//if a character is not a lower letter
		if (word[i]<'a' || word[i]>'z')
			//if it's a big letter, change it to lower
			if (word[i] >= 'A' && word[i] <= 'Z')
				word[i] = tolower(word[i]);
		//the character is not a letter 
			else
			{
				word.erase(i, 1);
				//to check the next character (will be in the previous index)
				i--;
			}
	}
		return word;
}

string Trie::approxFind(string & Str)
{
	int read = 0; //the index to read from the string
	TrieNode *current = root;
	//check if the word is full a full word and in the length of Str
	bool isWordLength = false;
	//check if the word is as same to Str till this character
	bool isFullWord = true;
	string result="";
	int length = Str.length();
	//we reserve the string-to-return size (preventing resize it every time)
	result.reserve(MAX_WORD_LEN);
	//if the tree is empty
	if (isEmpty())
		return "";
	else
	{
		//untill we get the approrx word
		while (current->NumOfChildren!=0)
		{
			if (!isWordLength && isFullWord)
			{
				//if the current has the char at the given string
				if (current->children[Str.at(read) - CHARACTER] != nullptr)
				{
						//we add the char to the string-to-return
						result = result + current->children[Str.at(read) - CHARACTER]->key;
						current = current->children[Str.at(read) - CHARACTER];
						++read;
						if (read == length)
							isWordLength = true;
				}
				else
					isFullWord = false;
			}
				//current has no char suits the given string
				else
				{
					//if we found a word, we are done
					if (current->data > 0)
						return result;
					////we add the first alphabets char to the string-to-return
					result = result + current->children[current->minFullIndex]->key;
					//we update that the word will not return as given
					if (isFullWord)
						isFullWord = false;
					current = current->children[current->minFullIndex];
				}
		}
	}
	return result;	
}

TrieNode * Trie::findLastTrieNode(string & word)
{
	TrieNode *current = root;
	int read = 0; //the index to read from the string
	string result = "";
	//untill we get the approrx word
	while (current->NumOfChildren != 0 && read < word.length())
	{
		//if the current has the char at the given string
		if (current->children[word.at(read) - CHARACTER] != nullptr)
		{
			//we add the char to the string-to-return
			result = result + current->children[word.at(read) - CHARACTER]->key;
			current = current->children[word.at(read) - CHARACTER];
		}
		++read;
	}
	//if the word exists, we'll return it's last node
	if (result.compare(word) == 0)
		return current;
	//the word is not exist
	return nullptr;
}

int Trie::find(string & Str)
{
	//find the last trie node of the given word
	TrieNode *current = findLastTrieNode(Str);
	//the word was found
	if (current != nullptr)
		return current->data;
	//the word wasn't found
	return 0;
}

void Trie::deleteWord(string & word)
{
	//if the tree is empty
	if (isEmpty())
		return;
	//the word not found
	TrieNode *current = findLastTrieNode(word);
	if (current == nullptr)
		return;
	//if the word appears more than once
	if (current->data > 1 || (current->NumOfChildren > 0 && current->data == 1))
		current->data--;
	//if the data is 1 and the node has no children, we need to delete it and update 
	else if (current->data == 1)
		deleteWordHelper(current, true);
}


void Trie::deleteWordHelper(TrieNode *current, bool isLastTrieNode)
{
	TrieNode *parent;
	//if the node is the last node of the word and it's data is 1
	//if the node is not the last node- so if it's data is 0
	if (current->data == 0 || (isLastTrieNode && current->data == 1))
	{
		//if the node has no children- we'll delete it
		if (current->NumOfChildren == 0 && current != root)
		{ 
			//updating the parent
			parent = current->parent;
			if (parent != nullptr)
			{
				parent->NumOfChildren--;
				parent->children[current->key - CHARACTER] = nullptr;
				//updating the minFullIndex- if the previous one was current's index
				if (parent->minFullIndex == (current->key - CHARACTER))
				{
					if (parent->NumOfChildren != 0)
					{
						for (int i = 0; i < ALPHABETS; i++)
							if (parent->children[i] != nullptr)
								parent->minFullIndex = i;
					}
					else
						parent->minFullIndex = 0;
				}
				delete current;
				deleteWordHelper(parent, false);
			}
		}
	}
}




