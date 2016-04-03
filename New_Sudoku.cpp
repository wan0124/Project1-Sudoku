#include"New_Sudoku.h"
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>


using namespace std;

void Sudoku::giveQuestion()
{
	int myQ[9][9] = 
	{
		{0,4,0,2,1,0,0,0,0},
		{8,0,7,0,0,0,0,9,0},
		{2,0,0,8,0,0,4,0,1},
		{3,0,0,0,0,2,9,0,5},
		{0,0,5,7,0,8,6,0,0},
		{7,0,6,5,0,0,0,0,4},
		{5,0,1,0,0,4,0,0,9},
		{0,6,0,0,0,0,7,0,8},
		{0,0,0,0,2,7,0,5,0}
	};
	
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
			printf("%d ",myQ[i][j]);
			
		printf("\n");
	}
}
void Sudoku::readIn()
{
	for( i = 0 ; i < 9 ; i++)
	{
		scanf("%d %d %d %d %d %d %d %d %d",&question[i][0],&question[i][1],&question[i][2],&question[i][3],&question[i][4],&question[i][5],&question[i][6],&question[i][7],&question[i][8]);	
	}

}
void Sudoku::solve()
{
	ansnum = 0;
	for(j = 0 ; j < 9 ; j++)
	{
		if(!checkRow(j))
		{
			printf("0\n");
			exit(1);
		}
		if(!checkCol(j))
		{
			printf("0\n");
			exit(1);
		}
		if(!checkCell(j+1))
		{
			printf("0\n");
			exit(1);
		}
	}
	recur();
	if(ansnum==0)
	{
		printf("0\n");
		exit(1);
	}

	printf("1\n");	
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
			printf("%d ",answer[i][j]);
		printf("\n");
	}

}
bool Sudoku::recur()
{
	int cell;
	int num;
	int colIndex=0;
	int rowIndex=0;
	int a=0;
	
    for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(question[i][j] == 0)
			{	
				a=1;
				rowIndex=i;
				colIndex=j;
				cell=3*(rowIndex/3)+(colIndex/3)+1;
				break;
			}
		}
	}
	if(a==0)
	{
		if(checkCol(8) && checkCell(9) && checkRow(8))
		{
			ansnum++;
			if(ansnum>1)
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
	
	for(num =1;num <10;num++)
	{
		if(checkall(rowIndex,colIndex,cell,num))
		{			
			question[rowIndex][colIndex] = num;
	  		if(recur())
				return true;
			else
				question[rowIndex][colIndex] = 0;
		}
	}
	return false;
}
void Sudoku::changeNum(int a , int b)
{
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
		{
			if(question[i][j]==a)
				question[i][j] = b;
			else if(question[i][j] == b)
				question[i][j] = a;
		}
}
void Sudoku::changeCol(int a , int b)
{
	int temp[9][3];
	int row=0;
	int t=3*a;
	int m=3*b;
	for(m;m<3*b+3;m++)
	{
		for(i=0;i<9;i++)
		{
			temp[i][row] = question[i][t];
			question[i][t] = question[i][m];
			question[i][m] = temp[i][row];
		}
		t++;
		row++;
	}
}
void Sudoku::changeRow(int a , int b)
{
	int col=0;
	int temp[3][9];
	int t=3*a;
	int m=3*b;
	
	for(m;m<3*b+3; m++)
	{
		for(i=0;i<9;i++)
		{
			temp[col][i]=question[t][i];
			question[t][i]=question[m][i];
			question[m][i]=temp[col][i];
		}
		t++;
		col++;
	}

}
void Sudoku::rotate(int n)
{
	int temp[9][9];
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
			temp[i][j]=question[i][j];
	}
	
	if(n%4==1)
	{
		for(i=0;i<9;i++)
			for(j=0;j<9;j++)
				question[i][j]=temp[8-j][i];
				
		return;
	}

	if(n%4==2)
	{
		for(i=0;i<9;i++)
			for(j=0;j<9;j++)
				question[i][j]=temp[8-i][8-j];
		return;
	}

	if(n%4==3)
	{
		for(i=0;i<9;i++)
			for(j=0;j<9;j++)
				question[i][j]=temp[j][8-i];
		return;
	}
}
void Sudoku::flip(int n)
{
	int temp[9][9];

	for(i=0;i<9;i++)
		for(j=0;j<9;j ++)
			temp[i][j] = question[i][j];
			
	if(n==0)
	{
		for(i=0;i<9;i++)
			for(j=0;j<9;j++)
				question[i][j]=temp[8-i][j];
		return;
	}

	if(n==1)
	{
		for(i=0;i<9;i++)
			for(j=0;j<9;j++)
				question[i][j]=temp[i][8-j];
		return;
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
			printf("%d ",question[i][j]);
			
		printf("\n");
	}
}

bool Sudoku::checkRow(int n)
{
	int check[9] = {0,0,0,0,0,0,0,0,0};	
	for(i=0;i<9;i++)
	{
		if(question[n][i] > 0)
		{
			check[question[n][i]-1]++;
			if(check[question[n][i]-1] != 1)
				return false;
		}
	}

	return true;
}


bool Sudoku::checkCol(int n)
{
	int check[9]={0,0,0,0,0,0,0,0,0};
	for(i=0;i<9;i++)
	{
		if(question[i][n] > 0)
		{
			check[question[i][n]-1]++;
			if(check[question[i][n]-1] != 1)
				return false;
		}
	}
	return true;
}

bool Sudoku::checkCell(int n)
{
	int check[9]={0,0,0,0,0,0,0,0,0};
	int col;
	int row;
	
	for(i=0;i<9;i++)
	{
		col=3*((n-1)/3)+(i/3);
		row=(i%3)+3*((n-1)%3);
		if(question[col][row] > 0)
		{
			check[question[col][row]-1]++;
			if(check[question[col][row]-1] != 1)
				return false;
		}
	}
	return true;
}
int  Sudoku::checkall(int col,int row,int cell,int num)
{
	int c;
	int r;
	for(i=0;i<9;i++)
	{	
		c=3*((cell-1)/3)+(i/3);
		r=(i%3)+3*((cell-1)%3);

		if((question[col][i] == num)||question[i][row] == num||question[c][r] == num)
			return 0;
	}
	return 1;
}







