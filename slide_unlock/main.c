#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG

int used[3][3];
int move[16][2] = { {-1,0}, {1,0}, {0,-1}, {0,1},		//left,right,up,down
					{-1,-1}, {1,-1}, {-1,1}, {1,1}, 	//u-l,u-r,d-r,d-l
					{-2,-1}, {2,-1}, {-2,1}, {2,1}, 	//ll-u,rr-u,ll-d,rr-d
					{-1,-2}, {1,-2}, {-1,2}, {1,2}};	//uu-l,uu-r,dd-l,dd-r

#define isInBetween(n, lower, upper) ( (lower) <= (n) && (n) <= (upper) )

int isOutSide(int x, int y)
{
	return !isInBetween(x, 0, 2) || !isInBetween(y, 0, 2);
}

int slipUnlock(int x, int y)
{
	/*
	static int test;
	test++;
	if (test == 20)
		exit(0);
	*/

	used[x][y] = 1;

	int cnt = 0;
	int i;
	for (i = 0; i < 15; i++)
	{
		int new_x = x + move[i][0];
		int new_y = y + move[i][1];
		if (!isOutSide(new_x, new_y) && !used[new_x][new_y]) 
		{
#ifdef DEBUG
			printf("%d,%d->%d,%d\n",x,y,new_x, new_y);
#endif
			cnt++;
			cnt += slipUnlock(new_x, new_y);
		}
	}
	used[x][y] = 0;
#ifdef DEBUG
	printf("point[%d][%d]=%d\n",x,y,cnt);
#endif
	return cnt;
}

int main(void)
{
	int totalCnt = 0;
	int onePointCnt = 0;

	//point[0,0]
	memset(used, 0, 9*sizeof(int));
	onePointCnt = slipUnlock(0, 0);
	totalCnt += onePointCnt * 4;
	printf("start from [0,0]: %d\n", onePointCnt);
	//point[1,0]
	memset(used, 0, 9*sizeof(int));
	onePointCnt = slipUnlock(1, 0);
	totalCnt += onePointCnt * 4;
	printf("start from [0,1]: %d\n", onePointCnt);
	//point[1,1]
	memset(used, 0, 9*sizeof(int));
	onePointCnt = slipUnlock(1, 1);
	totalCnt += onePointCnt;
	printf("start from [1,1]: %d\n", onePointCnt);

	printf("total solutions: %d\n", totalCnt);
	
}
