#include "StudentSpellCheck.h"
#include <string>
#include <vector>

// Added includes
#include <fstream>
#include <iostream>

SpellCheck* createSpellCheck(){
	return new StudentSpellCheck;
}

StudentSpellCheck::~StudentSpellCheck() {
	deleteTree(_head);
	_head = nullptr;
}

// Recursive function that deletes all nodes of the tree
// Post-order traversal
// Time Complexity : O(N) where N is the number of nodes.
void StudentSpellCheck::deleteTree(TrieNode* curNode){
	if(curNode == nullptr) // Return if nullptr
		return;
	for(int i = 0; i < 27; ++i){deleteTree(curNode->_branches[i]);}
	delete curNode;
}
// Time Complexity : O(N) where N is the number of lines in the dictionary file
bool StudentSpellCheck::load(std::string dictionaryFile) {
	// Clear contents of original tree (Carey said I can do this please don't hurt me)
	deleteTree(_head);
	_head = new TrieNode;
	// Get external file
	std::ifstream infile(dictionaryFile);
	if(!infile) // If in failure state, return
		return false;
	std::string word;
	while(getline(infile, word)){
		insertWord(word);
	}
	return true;
}
// Time Complexity : O(L^2 + maxSuggestions) where L is the length of the word being searched for
bool StudentSpellCheck::spellCheck(std::string word, int max_suggestions, std::vector<std::string>& suggestions) {
	if(isValidSpelling(word)) // If the word is valid, return true
		return true;
	suggestions.clear(); // Reset suggestions vector
	
	for(int i = 0; i < word.length() && suggestions.size() <= max_suggestions; ++i){
		std::string possibleWord = word;
		for(int j = 0; j < 27 && suggestions.size() <= max_suggestions; ++j){
			possibleWord[i] = decodeChar(j);
			if(isValidSpelling(possibleWord))
				suggestions.push_back(possibleWord);
		}
	}
	return false; 
}


// Time Complexity : O(S + W*L) where S is the length of the line passed in, W is the number of words in the line, and L is the maximum length of the checked word
void StudentSpellCheck::spellCheckLine(const std::string& line, std::vector<SpellCheck::Position>& problems) {
	std::string word;
		int i = 0;
		while(i < line.length()){
			word = "";
			if(isalpha(line[i]) || line[i] == '\''){ // If char is alphabet or '
				int j = i; // Starting position of word
				while(isalpha(line[i]) || line[i] == '\''){
					word += tolower(line[i]);
					++i;
				}
				if(!isValidSpelling(word)){ // If word isn't valid spelling, 
					SpellCheck::Position pos;
					pos.start = j;
					pos.end = i - 1;
					problems.push_back(pos);
				}
			}
			++i;
		}
}

// Helper Functions

// Hashing Function ; maps a-z  and   '  to...
//                        0-25 and   26, inclusive
// Time Complexity : O(1)
int StudentSpellCheck::mapChar(char c) const{
	if(c == '\'') // Special case for '
		return 26;
	return (int)c - 97;
}
// Time Complexity : O(1)
char StudentSpellCheck::decodeChar(int i) const{
	if(i == 26) // Special case for '
		return '\'';
	return (char) i + 97;
}
// Time Complexity : O(N) where N is the number of chars in line
void StudentSpellCheck::insertWord(std::string word){
	TrieNode* lastNode = _head;

	for(int i = 0; i < word.length(); ++i){ // Enter every letter at a time into Trie
		char curChar = tolower(word[i]);
		int bucket = mapChar(curChar);
		if(bucket < 0 || bucket >=27){continue;} // If it's a non-valid char, skip
		if(lastNode->_branches[bucket] == nullptr){ // If that letter doesn't exist yet (in order)
			lastNode->_branches[bucket] = new TrieNode(curChar);
		}
		lastNode = lastNode->_branches[bucket];
	}
	lastNode->_endOfWord = true; // At the end of the word, flag the node
}
// Time Complexity : O(N) where N is the number of chars in word
bool StudentSpellCheck::isValidSpelling(const std::string word) const{
	TrieNode* lastNode = _head;

	for(int i = 0; i < word.length(); ++i){
		int bucket = mapChar(tolower(word[i]));
		if(bucket < 0 || bucket >= 27)
			return false;
		if(lastNode->_branches[bucket] == nullptr) // Word doesn't exist in dictionary
			return false;
		lastNode = lastNode->_branches[bucket];
	}
	if(lastNode->_endOfWord)
		return true;
	else // If not the end of the word 
		return false; 
}
