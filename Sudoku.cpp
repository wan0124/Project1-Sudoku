#include"Sudoku.h"
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
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
	{
		scanf("%d ",&question[i][j]);	
	}

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

void Sudoku::changeRow(int a,int b)
{
	int i,j,temp[3][9];
	
	for(i=0;i<3;i++)
		for(j=0;j<9;j++)
		{
			temp[i][j]=question[a*3+i][j];
			question[a*3+i][j] = question[b*3+i][j];
			question[b*3+i][j] = temp[i][j];
		}
}
	
void Sudoku::changeCol(int a,int b)
{
	int i,j,temp[3][9];
				
	for(i=0;i<3;i++)
		for(j=0;j<9;j++)
		{
			temp[i][j]=question[j][a*3+i];
 			question[j][a*3+i]=question[j][b*3+i];
 			question[j][b*3+i]=temp[i][j];
 		}
}
	

void Sudoku::rotate(int n)
{
	int i,j,k,temp[9][9];
	
	if(n>=4) 
		n=n%4;
		
	if(n==0) 
		return;
				
	for(k=0;k<n;k++)
	{
		for(i=0;i<9;i++)
			for(j=0;j<9;j++) 
				temp[i][j]=question[8-j][i];
		for(i=0;i<9;i++)
			for(j=0;j<9;j++) 
				question[i][j]=temp[i][j];
	}
}

void Sudoku::flip(int n)
{
   int temp;
   if (n==0)
   {
      for(i=0;i<4;i++)
	  {
         for(j=0;j<9;j++)
		 {
            temp=question[i][j];
            question[i][j]=question[8-i][j];
            question[8-i][j]=temp;
         }
      }  
   }
   
   if (n==1)
   {
      for(i=0;i<4;i++)
	  {
         for(j=0;j<9;j++)
		 {
            temp=question[j][i];
            question[j][i]=question[j][8-i];
            question[j][8-i]=temp;
         }
      } 
   }   
} 

void Sudoku::transform()
{
   srand(time(NULL));
   changeNum(rand()%9+1,rand()%9+1);
   changeRow(rand()%3,rand()%3);
   changeCol(rand()%3,rand()%3);
   rotate(rand()%4);
   flip(rand()%2);
   print();
}



void Sudoku::solve()
{
	ans =0;
	for(j=0;j<9;j++)
	{
		if(!checkRow(j)||!checkCol(j)||!checkCell(j+1))
		{
			printf("0\n");
			exit(1);
		}
	}
	
	backtrack();
	
	if(ans==0)
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
bool Sudoku::backtrack()
{
	int cell;
	int num;
	int col=0;
	int row=0;
	int a=0;
    for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(question[i][j]==0)
			{	
				a=1;
				col=i;
				row=j;
				break;
			}
		}
	}
	
	if(a==0)
	{
		if(checkCol(8) && checkCell(9) && checkRow(8))
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
		if(checkall(col,row,num))
		{			
			question[col][row]=num;
			
	  		if(backtrack())
				return true;
				
			else
				question[col][row] = 0;
		}
	}
	return false;
}

bool Sudoku::checkRow(int n)
{
	int check[9]={0};	
	
	for(i=0;i<9;i++)
	{
		if(question[n][i]>0)
		{
			check[question[n][i]-1]++;
			
			if(check[question[n][i]-1]!=1)
				return false;
		}
	}

	return true;
}


bool Sudoku::checkCol(int n)
{
	int check[9]={0};
	
	for(i=0;i<9;i++)
	{
		if(question[i][n]>0)
		{
			check[question[i][n]-1]++;
			
			if(check[question[i][n]-1]!=1)
				return false;
		}
	}
	return true;
}

bool Sudoku::checkCell(int n)
{
	int check[9]={0};
	int col;
	int row;
	
	for(i=0;i<9;i++)
	{
		col = 3*((n-1)/3)+(i/3);
		row = (i%3)+3*((n-1)%3);
		if(question[col][row]>0)
		{
			check[question[col][row]-1]++;
			
			if(check[question[col][row]-1]!=1)
				return false;
		}
	}
	return true;
}

bool  Sudoku::checkall(int col,int row,int num)
{
	int cell=3*(col/3)+(row/3)+1;
	int tmpCol,tmpRow;
	
	for(i=0;i<9;i++)
        if (question[col][i]==num)
			return false;
    
    for (i=0;i<9;i++){
        if (question[i][row]==num)
			return false;
    }
    
    for (i=0;i<9;i++)
	{
    	tmpCol=3*((cell-1)/3)+(i/3);
		tmpRow=(i%3)+3*((cell-1)%3);
		
        if(question[tmpCol][tmpRow]==num)
			return false;
    }
    return true;
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
