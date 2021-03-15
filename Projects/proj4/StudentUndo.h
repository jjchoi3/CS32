#ifndef STUDENTUNDO_H_
#define STUDENTUNDO_H_

#include "Undo.h"

// Added includes

#include <stack>
class StudentUndo : public Undo {
public:

	void submit(Action action, int row, int col, char ch = 0);
	Action get(int& row, int& col, int& count, std::string& text);
	void clear();

private:
	struct UndoInfo {
		UndoInfo(int row, int col, Action act, char c):
		_row(row), _col(col), _action(act), _ch(c), _batch(""), _count(1){
			if(_action == DELETE){
				_batch += _ch;
			}
		}
		int _row, _col, _count;
		char _ch;
		std::string _batch;
		Action _action;
	};
	std::stack<UndoInfo> _undoStack;
	void getUndoBatch(std::string& text, int& r, int& c, int& count, UndoInfo undoInfo);
};

#endif // STUDENTUNDO_H_
