void Sudoku::changeCol(int a , int b)
{
	int temp[3];
	int tmp1=a/3*3;
	int tmp2=b/3*3;
	
	for(int i=0;i<9;i++)
		for(int j=0;j<3;j++)
		{
		temp[j]=question[i][tmp1+j];
		question[i][tmp1+j]=question[i][tmp2+j];
		question[i][tmp2+j]=temp[j];
		}
}
void Sudoku::changeRow(int a , int b)
{
	int temp[9];
	int tmp1=a/3*3;
	int tmp2=b/3*3;
	
	for(int i=0;i<3;i++)
		for(int j=0;j<9;j++)
		{
		temp[j]=question[i+tmp1][j];
		question[tmp1+i][j]=question[tmp2+i][j];
		question[tmp2+i][j]=temp[j];
		}
}
