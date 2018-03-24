#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include "Trie.h"
#include "TrieNode.h"
#include <string>
#include <iostream>
#include <ctype.h>
#define MAX_WORD_LEN 65
#define CHARACTER 'a'

int main()
{
	Trie tr;
	string str;
	char line[256];
	char *word;
	int length, occurences;
	//preventing resize temp every time
	str.reserve(MAX_WORD_LEN);
	cout << "Please enter your input, enter '.' to end input" << endl;
	//input loop
	while (true) {
		cin.getline(line, 256);
		//checks for end of input
		if (line[0] == '.' && line[1] == '\0')
			break;
		//returns a word from the line, space is replaced by a '\0'
		word = strtok(line, " ");
		while (word) {
			str = word;
			str = tr.checkAndUpdateWord(str);
			length = str.length();
			//make sure that the word is not too long
			if (length > MAX_WORD_LEN)
				str.erase(MAX_WORD_LEN, length);
			tr.insert(str);
			//getting next word
			word = strtok(NULL, " ");
		}
	}
		//second level loop
		while (true) {
			cin.getline(line, 256);
			//checks for end of input
			if (line[0] == '.' && line[1] == '\0')
				break;
			//returns a word from the line, space is replaced by a '\0'
			word = strtok(line, " ");
			while (word) {
				str = word;
				length = str.length();
				//make sure that the word is not too long
				if (length > MAX_WORD_LEN)
					str.erase(MAX_WORD_LEN, length);
				occurences = tr.find(str);
				//the word appears in the dictionary
				if (occurences > 0)
				{
					cout << occurences << "\n";
					//delete the word
					tr.deleteWord(str);
				}
				//the word is not appear in the dictionary
				else
					cout << "Did you mean " << tr.approxFind(str) << "?\n";
				//getting next word
				word = strtok(NULL, " ");
			}
		}


}