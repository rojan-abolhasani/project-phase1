#include<stdio.h>
#include<windows.h>
#define N 4
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X=x;
	coord.Y=y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleCursorPosition( handle, coord);
}
void move(int X, int Y, int currentx, int currenty)
{
	int i, x, y;
	x=(X-currentx)/2;
	y=Y-currenty;
	if (x>0)
	{
		for (i=0;i<x;i++)
		{
			sleep(1);
			gotoxy(currentx+2,currenty);
			printf("\b\b%s", "1 0");
			currentx+=2;
		}
	}
	else if (x<0)
	{
		x=-x;
		for (i=0;i<x;i++)
		{
			sleep(1);
			gotoxy(currentx-2,currenty);
			printf("%s", "0 1");
			currentx-=2;
		}
	}
	if (y>0)
	{
		for (i=0;i<y;i++)
		{
			sleep(1);
			gotoxy(currentx,currenty);
			printf("1");
			gotoxy(currentx,currenty+1);
			printf("0");
			currenty++;
		}
	}
	else if (y<0)
	{
		y=-y;
		for (i=0;i<y;i++)
		{
			sleep(1);
			gotoxy(currentx,currenty);
			printf("1");
			gotoxy(currentx,currenty-1);
			printf("0");
			currenty--;
		}
	}
}
int main()
{
	FILE *fp=fopen("testcase01.txt","w");
	fprintf(fp,"0 1 * 1\n1 1 1 *\n1 1 1 1\n1 1 * 1\n");
	fclose(fp);
	char Matrix[N][N], ch;
	int i, j, food[N][N]={0}, x=0, y=0, foodx, foody;
	fp=fopen("testcase01.txt","r");
	for (i=0;i<N;i++)
	{
		for (j=0;j<N;j++)
		{
			fscanf(fp,"%c", &Matrix[i][j]);
			ch=getc(fp);
			if (Matrix[i][j]=='*')
				food[i][j]=1;
			printf("%c ", Matrix[i][j]);	
		}
		printf("\n");
	}
	for (i=0;i<N;i++)
		for (j=0;j<N;j++)
		{
			if (food[i][j]==1)
			{
				gotoxy(x,y);
				foodx=j;
				foody=i;
				move(foodx*2,foody,x,y);
				x=2*foodx;
				y=foody;
			}
		}
}
