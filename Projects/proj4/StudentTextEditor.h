#ifndef STUDENTTEXTEDITOR_H_
#define STUDENTTEXTEDITOR_H_

#include "TextEditor.h"
#include <list> // Added include

class Undo;

class StudentTextEditor : public TextEditor {
public:

	StudentTextEditor(Undo* undo);
	~StudentTextEditor();
	bool load(std::string file);
	bool save(std::string file);
	void reset();
	void move(Dir dir);
	void del();
	void backspace();
	void insert(char ch);
	void enter();
	void getPos(int& row, int& col) const;
	int getLines(int startRow, int numRows, std::vector<std::string>& lines) const;
	void undo();

private:
	std::list<std::string> _lines;
	std::list<std::string>::iterator _it;
	
	int _row, _col;
	bool _undo; // Used to track whether or not to submit undo information (i.g. to avoid undoing undos)

};

#endif // STUDENTTEXTEDITOR_H_
