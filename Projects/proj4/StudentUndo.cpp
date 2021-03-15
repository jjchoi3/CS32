#include "StudentUndo.h"

Undo* createUndo(){
	return new StudentUndo;
}
// Time Complexity : O(1)
void StudentUndo::submit(const Action action, int row, int col, char ch) {
	// Create UndoInfo object
	
	if(action == INSERT){
		if(	!_undoStack.empty() && _undoStack.top()._action == INSERT &&
			_undoStack.top()._row == row && _undoStack.top()._col == col - 1){ // Potential consecutive inserts

			_undoStack.top()._count++;
			_undoStack.top()._col++;
		}else{
			UndoInfo undoInfo(row, col, action, ch);
			_undoStack.push(undoInfo);
		}
	}else if (action == DELETE){
		if(	!_undoStack.empty() && _undoStack.top()._action == DELETE &&
			_undoStack.top()._row == row && _undoStack.top()._col == col){ // Potential consecutive deletes

			_undoStack.top()._batch += ch; // Batch
		}else if( !_undoStack.empty() && _undoStack.top()._action == DELETE &&
				_undoStack.top()._row == row && _undoStack.top()._col == col + 1){ // Potential consecutive backspaces

			_undoStack.top()._batch = ch + _undoStack.top()._batch; // Batch
			_undoStack.top()._col--;
		}else{
			UndoInfo undoInfo(row, col, action, ch);
			_undoStack.push(undoInfo);
		}
	}else{
		UndoInfo undoInfo(row, col, action, ch);
		_undoStack.push(undoInfo); // Push undo onto stack
	}

}
// Time Complexity : O(1) (but can go up to O(length of char to restore))
StudentUndo::Action StudentUndo::get(int& row, int& col, int& count, std::string& text) {
	if(_undoStack.empty()) // If there is nothing to undo
    	return ERROR;
	UndoInfo undoInfo = _undoStack.top();
	_undoStack.pop();

	switch(undoInfo._action){ // Return value depends on UndoInfo on top of stack
		case INSERT:
			row = undoInfo._row;
			col = undoInfo._col;
			text = "";
			count = undoInfo._count;
			return DELETE;
			break;
		case DELETE:
			row = undoInfo._row;
			col = undoInfo._col;
			text = undoInfo._batch;
			count = 1;
			return INSERT;
			break;
		case SPLIT: 
			row = undoInfo._row;
			col = undoInfo._col;
			text = "";
			count = 1;
			return JOIN;
			break;
		case JOIN:
			row = undoInfo._row;
			col = undoInfo._col;
			text = "";
			count = 1;
			return SPLIT;
			break;
        case ERROR:
            return ERROR;
            break;
	}
    return ERROR;

}
// Time Complexity : O(N) where N is the number of elements in the stack
void StudentUndo::clear() {
	while(!_undoStack.empty())
		_undoStack.pop();
}
