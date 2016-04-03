#include "Sudoku.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
using namespace std;

int sum=0;

void Sudoku::giveQuestion()
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

void Sudoku::readIn()
{
for( i = 0 ; i < 9 ; i++)
	scanf("%d %d %d %d %d %d %d %d %d",&question[i][0],&question[i][1],&question[i][2],&question[i][3],&question[i][4],&question[i][5],&question[i][6],&question[i][7],&question[i][8]);	
}

void Sudoku::changeNum(int a, int b)
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

void Sudoku::changeCol(int a, int b)
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

void Sudoku::changeRow(int a, int b)
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

void Sudoku::rotate(int n)
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

void Sudoku::flip(int n)
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

void Sudoku::transform()
{
	change();
	print();
}

void Sudoku::change()
{
	srand(time(NULL));
	changeNum(rand()%9+1,rand()%9+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%3+1);
	flip(rand()%2);
}

void Sudoku::print()
{
	
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
			printf("%d ",answer[i][j]);	
			
	printf("\n");
	}
}

void Sudoku::solve()
{
	ans=0;
	backtrace();
	
	if(ans==0)
	{
		printf("0\n");
		exit(1);
	}
	
		printf("1\n");
		print();	
}

bool Sudoku::backtrace()
{
	int rowIndex=0;
	int colIndex=0;
	int num;
	int a;
	int sum;
	
    for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			if(question[i][j]==0)
			{	
				a=1;
				rowIndex=i;
				colIndex=j;
				break;
			}
	
	if(a==0)
	{	
		sum=0;
		for(i=0;i<9;i++)
			for(j=0;j<9;j++)
				if(question[i][j]!=0)
					sum++;
		if(sum==81)
		{
			ans++;
		
			if(ans>1)
			{
				printf("2\n");
				exit(1);
			}
		
			for(i=0;i<9;i++)
				for(j=0;j<9;j++)
					answer[i][j]=question[i][j];
		}
		return false;
	}
	
	for(num=1;num<10;num++)
	{
		if(check(rowIndex,colIndex))
		{
			question[rowIndex][colIndex]=num;
			if(backtrace())	
				return true;
			else	
				question[rowIndex][colIndex]=0;
		}
	}
	
	return false;
			
}	

bool Sudoku::check(int row,int col)
{
	for(i=0;i<9;i++)
		if(question[row][i]==question[row][col] && i!=col)
			return false;
	
	
	for(i=0;i<9;i++)
		if(question[i][col]==question[row][col] && i!=row)
			return false;
	
	
	int tmpRow=row/3*3;
	int tmpCol=col/3*3;
	
	for(i=tmpRow;i<tmpRow+3;i++)
		for(j=tmpCol;j<tmpCol+3;j++)
			if(question[i][j]==question[row][col] && i!=row && j!=col)
				return false;
	
	return true;
}

