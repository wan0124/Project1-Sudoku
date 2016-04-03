#include "Sudoku.h"
#include <ctime>
#include <cstdlib>
using namespace std;

int count=81;
int ans=0;
int sum=0;

Sudoku::giveQuestion()
{
	cout<<"0 4 0 2 1 0 0 0 0"<<"/n";
	cout<<"8 0 7 0 0 0 0 9 0"<<"/n";
	cout<<"2 0 0 8 0 0 4 0 1"<<"/n";
	cout<<"3 0 0 0 0 2 9 0 5"<<"/n";
	cout<<"0 0 5 7 0 8 6 0 0"<<"/n";
	cout<<"7 0 6 5 0 0 0 0 4"<<"/n";
	cout<<"5 0 1 0 0 4 0 0 9"<<"/n";
	cout<<"0 6 0 0 0 0 7 0 8"<<"/n";
	cout<<"0 0 0 0 2 7 0 5 0"<<"/n";
}

Sudoku::readIn()
{
	for(int i=0;i<9;i++)
		for(int j=0;i<9;j++)
			scanf("%d",question[i][j]);
	  
	printf("/n");
}

Sudoku::changeNum(int a, int b)
{
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
		{
			if(question[i][j]==a)
				question[i][j]=b;
			else if(question[i][j]==b)
				question[i][j]==a;
		}
			
}

Sudoku::changeCol(int a, int b)
{   
	int temp[3];
	
	for(int i=0;i<9;i++)
		for(int j=0;j<3;j++)
		{
		temp[j]=question[i][a+j];
		question[i][a+j]=question[i][b+j];
		question[i][b+j]=temp[j];
		}
}

Sudoku::changeRow(int a, int b)
{
	int temp[9];
	
	for(int i=0;i<3;i++)
		for(int j=0;j<9;j++)
		{
		temp[j]=question[i+a][j];
		question[a+i][j]=question[b+i][j];
		question[b+i][j]=temp[j];
		}
}

Sudoku::rotate(int n)
{
	int temp[9][9];
	
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			temp[i][j]=question[i][j];
			
	if(n%4==1)
	{
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				question[j][8-i]=temp[i][j];
	}
	
	else if(n%4==2)
	{
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				question[8-i][8-j]=temp[i][j];
	}
	
	else if (n%4==3)
	{
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				question[j][8-i]=temp[i][j];
	}
}

Sudoku::flip(int n)
{
	int temp[9][9];
	
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			temp[i][j]=question[i][j];
			
	if(n==0)
	{
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				question[i][j]=temp[8-i][j];
		
	}
	else if(n==1)
	{
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				question[i][j]=temp[i][8-j];
	}
}

Sudoku::transform()
{
	readIn();
	change();
	print();
}

Sudoku::change()
{
	srand(time(NULL));
	changeNum(rand()%9+1,rand()%9+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
}

Sudoku::print()
{
	for(int i = 0 ; i < 9 ; i++)
	{
		for(int j = 0 ; j < 9 ; j++)
			printf("%d ",question[i][j]);	
			
	printf("\n");
	}
}

Sudoku::solve()
{
	backtrace(count);
	
	if(ans==0)
	{
		printf("0\n");
	}
	
	if(ans==1)
	{
		printf("1\n");
		print();
		return 0;
	}	
	
	if(ans==2)
	{
		printf("2\n");
	}
}

Sudoku::backtrace(int count)
{
	int rowIndex=count/9;
	int colIndex=count%9;
	
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			if(question[i][j]!=0)
				sum++;
				
	if(sum==81)
	{
		ans++;
		
		if(ans>1)
			return 1;
		
	}
	
	if(question[rowIndex][colIndex]==0)
	{
		for(int i=1;i<=9;i++){
			question[rowIndex][colIndex]=i;
			if(check(rowIndex,colIndex))
				backtrace(count+1);
		}
	question[rowIndex][colIndex]=0;
	}
	
	else
	{
		backtrace(count+1);
	}
	
}

bool Sudoku::check(int row,int col)
{
	for(int i=0;i<9;i++)
		if(question[row][i]==question[row][col] && i!=col)
			return false;
	
	
	for(int i=0;i<9;i++)
		if(question[i][col]==question[row][col] && i!=row)
			return false;
	
	
	int tmpRow=row/3*3;
	int tmpCol=col/3*3;
	
	for(int i=tmpRow;i<tmpRow+3;i++)
		for(int j=tmpCol;j<tmpCol+3;j++)
			if(question[i][j]==question[row][col] && i!=row && j!=col)
				return false;
	
	return true;
}
