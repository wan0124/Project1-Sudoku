#include<iostream>
#include<cstdio>
#include<cstdlib>


using namespace std;
class Sudoku
{
	public:
		void giveQuestion()
		void readIn();
		void solve();
		bool recur();
		void changeNum(int a , int b);
		void changeCol(int a , int b);
		void changeRow(int a , int b);
		void rotate(int n);
		void flip(int n);
		void transform();
		void change();
		void print();
		bool checkRow(int n);
		bool checkCol(int n);
		bool checkCell(int n);
		int  checkall(int col ,int row ,int cell , int num);
	private:
		int myQ[9][9];	
		int question[9][9];
		int answer[9][9];
		int ans;
		int i;
		int j;
};
