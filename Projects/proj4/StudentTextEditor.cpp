#include "StudentTextEditor.h"
#include "Undo.h"
#include <string>
#include <vector>

// Added includes
#include <list>
#include <iostream>
#include <fstream>

TextEditor* createTextEditor(Undo* un){
	return new StudentTextEditor(un);
}

// Time Complexity : O(1)
StudentTextEditor::StudentTextEditor(Undo* undo):
TextEditor(undo), _row(0), _col(0), _undo(false){}

// Time Complexity : O(N) where N is the number of lines in the text editor
StudentTextEditor::~StudentTextEditor(){
	_lines.clear();
}

// Time Complexity : O(N + M) where N is the number of lines to be loaded, and M is the number of lines in text editor
bool StudentTextEditor::load(std::string file) {
	// Get external file
	std::ifstream infile(file);
	if(!infile) // If in failure state, return
		return false;
	reset(); // If file could be loaded, reset old contents (also sets _row, _col to 0, 0)

	std::string line;
	while(getline(infile, line)){ // Push lines from file into list and strip carriage returns
		if(line.size() != 0 && line[line.length() - 1] == '\r')
			line.pop_back(); // Remove carriage return
		_lines.push_back(line);	
	}
	_it = _lines.begin(); // Set pointer to first line
	return true;
}
// Time Complexity : O(M) where M is the number of lines in the editor
bool StudentTextEditor::save(std::string file) {
	// Get external file
	std::ofstream outfile(file);
	if(!outfile) // If in failure state, return
		return false;

	// Add each line in the editor to output file
	for(std::list<std::string>::iterator it = _lines.begin(); it != _lines.end(); ++it){
		outfile << (*it) << std::endl;
	}
	return true;
}
// Time Complexity : O(N) where N is the number of lines in text editor
void StudentTextEditor::reset() {
	// Reset Position
	_row = 0;
	_col = 0;
	// Clear list of lines
	_lines.clear();
	// Reset undo
	getUndo()->clear();
}
// Time Complexity : O(1)
void StudentTextEditor::move(Dir dir) {
	switch(dir){
		case UP:
			if(_row == 0)
				return;
			_it--; // Decrement iterator (point up one line)
			if(_col > (*_it).length())
				_col = (*_it).length(); // Adjust col depending on previous line
			_row--;
			break;
		case DOWN:
			if(_row == _lines.size() - 1)
				return;
			_it++; // Increment iterator (point down one line)
			if(_col > (*_it).length()) 
				_col = (*_it).length(); // Adjust col depending on next line
			_row++;
			break;
		case LEFT:
			if(_col == 0){
				if(_row == 0) // If at beginning of the file
					return;
				_it--; // Decrement iterator (point up one line)
				_row--;
				_col = (*_it).length();
			}else
				_col--;
			break;
		case RIGHT:
			if(_col == (*_it).length()){
				if(_row == _lines.size() - 1) // If at end of the file
					return;
				_it++; // Increment iterator (point up one line)
				_row++;
				_col = 0;
			}else
				_col++;
			
			break;
		case HOME:
			_col = 0; // Set col to first char on current line
			break;
		case END:
			_col = (*_it).length(); // Set col to after last char on current line
			break;
	}
}
// Time Complexity : O(L1 + L2) where L1 is the length of the current line (and sometimes, where L2 is the length of the next line)
void StudentTextEditor::del() {
	Undo* undoInfo = getUndo(); // Pointer to Undo instance
	if(_row == _lines.size() - 1 && _col == (*_it).length()) // If end of file
		return;
	else if(_col == (*_it).length()){ // If end of line
		std::string newLine = *_it;
		_it++;
		newLine += *_it;
		_it = _lines.erase(_it); // Remove line from vector
		_it--;
		*_it = newLine;
		if(!_undo)
			undoInfo->submit(Undo::JOIN, _row, _col, '\0'); // Submit Undo information
	}else{ // Elsewhere
		std::string newLine; 
		std::string curLine = *_it;
		char deletedChar;
		for(int i = 0; i < curLine.length(); ++i){
			if(_col == i){				
				deletedChar = curLine[i];
				continue;
			}
			newLine += curLine[i];
		}
		(*_it) = newLine;
		if(!_undo)
			undoInfo->submit(Undo::DELETE, _row, _col, deletedChar); // Submit Undo information
	}
}
// Time Complexity : O(L1 + L2) where L1 is the length of the current line (and sometimes, where L2 is the length of the next line)
void StudentTextEditor::backspace() {
	Undo* undoInfo = getUndo(); // Pointer to Undo instance
	if(_row == 0 && _col == 0) // If beginning of file
		return;
	else if(_col == 0){ // If beginning of line
		std::string nextLine = *_it;
		_it--;
		_row--;
		_col = (*_it).length();	// Set cursor to end of line before appending
		*_it += nextLine;
		_it++;
		_it = _lines.erase(_it);
		_it--;
		if(!_undo)
			undoInfo->submit(Undo::JOIN, _row, _col, '\0'); // Submit Undo information
	}else{ // Elsewhere
		std::string newLine;
		char deletedChar;
		for(int i = 0; i < (*_it).length(); ++i){ // Put all chars in newLine except deleted
			if(i == _col - 1){
				deletedChar = (*_it)[i];
				continue;
			}
			newLine += (*_it)[i];
		}
		(*_it) = newLine;
		_col--;
		if(!_undo)
			undoInfo->submit(Undo::DELETE, _row, _col, deletedChar); // Submit Undo information
	}
}
// Time Complexity : O(L) where L is the number of chars on the current line
void StudentTextEditor::insert(char ch) {
	Undo* undoInfo = getUndo(); // Pointer to Undo instance
	if(ch != '\t'){ // If char isn't a tab
		std::string newLine = *_it + " "; // Get current line with extra slot at end
		for(int i = newLine.length() - 1; i > _col; --i){ // Shift all chars right of inserted char
			newLine[i] = newLine[i - 1];
		}
		newLine[_col] = ch;
		_col++;
		*_it = newLine;
		if(!_undo)
			undoInfo->submit(Undo::INSERT, _row, _col, ch); // Submit undo information
	}else if(ch == '\t'){ // If char is tab
		std::string newLine = *_it + "    "; // Get current line with extra 4 slots at end
		for(int i = newLine.length() - 1; i >= _col + 4; --i){ // Shift all chars right of tab by 4
			newLine[i] = newLine[i - 4];
		}
		for(int i = _col; i < _col + 4; ++i){ // Set four slots starting from inserted position to space
			newLine[i] = ' ';
			if(!_undo)
				undoInfo->submit(Undo::INSERT, _row, i + 1, ' '); // Submit undo information
		}
		_col += 4;
		*_it = newLine;
	}
}

// Time Complexity : O(L) where L is the length of the line of text
void StudentTextEditor::enter(){
	Undo* undoInfo = getUndo(); // Pointer to Undo instance
	if(!_undo)
		undoInfo->submit(Undo::SPLIT, _row, _col, '\0'); // Submit undo information
	std::string firstLine, secondLine;
	for(int i = 0; i < (*_it).length(); ++i){ // Split line depending on current col position
		if(i < _col)
			firstLine += (*_it)[i];
		else
			secondLine += (*_it)[i];
	}
	_lines.insert(_it, firstLine); // Add first half
	(*_it) = secondLine; // Set current line to second half
	_row++; 
	_col = 0;
}
// Time Complexity : O(1)
void StudentTextEditor::getPos(int& row, int& col) const {
	row = _row;
	col = _col;
}
// Time Complexity : O(abs(current row num - startRow) + numRows*L) where L is the length of the line
int StudentTextEditor::getLines(int startRow, int numRows, std::vector<std::string>& lines) const {
	if(startRow < 0 || numRows < 0 ||
		startRow >= _lines.size())
		return -1;
	lines.clear(); // Clear passed in vector
	std::list<std::string>::const_iterator it = _it; // Set temp it to current position
	if(_row > startRow) // If startRow is below current row, decrement temp it to startRow
		for(int i = _row; i > startRow && it != _lines.begin(); --i){it--;}
	else if(_row < startRow) // If startRow is above current row, increment temp it to startRow
		for(int i = 0; i < startRow && it != _lines.end(); ++i){it++;}

	int numLines = 0; // Count how many lines added
	for(int i = 0; i < numRows && it != _lines.end(); ++i){
		lines.push_back(*it);
		it++;
		numLines++;
	}
	return numLines;
}
// Time Complexity : O(1) (but can go up to O(length of char to restore))
void StudentTextEditor::undo() {
	int row, col, count;
	std::string text;
	Undo::Action act = getUndo()->get(row, col, count, text);
	if(act == Undo::ERROR) // If there are no undos in the stack
		return;
	// Move iterator to appropriate position
	if(_row > row) // If line to undo is below current line
		for(int i = _row; i > row; --i) {_it--;}
	else if(_col < col) // If line to undo is above current line
		for(int i = _row; i < row; ++i){_it++;}

	_row = row;
	_col = col; 
	_undo = true; // Stop submitting undo information
	switch(act){
		case Undo::INSERT:
			// Insert text char by char
			for(int i = 0; i < text.length(); ++i){insert(text[i]);}
			_col -= text.length(); // Set col to first character inserted
			break;
		case Undo::DELETE:
			// Delete count spaces
			for(int i = 0; i < count; ++i){backspace();}
			break;
		case Undo::SPLIT:
			enter();
			_row--;
			_it--;
			_col = (*_it).length();
			break;
		case Undo::JOIN:
			del();
			break;
		default:
			return;
	}
	_undo = false; // Start submitting undo information again
}
