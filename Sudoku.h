#include <iostream>
class Sudoku{
public:
	giveQuestion();
	readIn();
	solve();
	changeNum(int a,int b);
	changeRow(int a,int b);
	changeCol(int a,int b);
	rotate(int n);
	flip(int n);
	transform();
	change();
	print();
	backtrace(int count);
	
private:
	int question[9][9];
	bool 	check(int row,int col);

};
