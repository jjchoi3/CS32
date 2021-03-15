#ifndef STUDENTSPELLCHECK_H_
#define STUDENTSPELLCHECK_H_

#include "SpellCheck.h"

#include <string>
#include <vector>

class StudentSpellCheck : public SpellCheck {
public:
    StudentSpellCheck(){
		_head = new TrieNode; // Dummie "head" node that points to all letters
	}
	virtual ~StudentSpellCheck();
	bool load(std::string dict_file);
	bool spellCheck(std::string word, int maxSuggestions, std::vector<std::string>& suggestions);
	void spellCheckLine(const std::string& line, std::vector<Position>& problems);

private:
	struct TrieNode{
		TrieNode(char c='\0'):
		_c(c), _branches(27), _endOfWord(false){}
		char _c;
		std::vector<TrieNode*> _branches; // Holds pointer to up to 27 TrieNodes--all lowercase letters + apohstrophe
		bool _endOfWord; // Flags end of a word
	};
	TrieNode* _head; // Points to "dummy node" which holds all trees

    int mapChar(char c) const;
	char decodeChar(int i) const;
	void insertWord(std::string word);
	bool isValidSpelling(const std::string word) const;
	void deleteTree(TrieNode* curNode);
};

#endif  // STUDENTSPELLCHECK_H_
