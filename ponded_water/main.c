#include <stdio.h>
#include <stdlib.h>

int group;
int wallCnt[100];
int height[100][1000];

void getInput()
{
	FILE* fp;
	fp = fopen("input.txt", "r");

	fscanf(fp, "%d\n", &group);
	if (group < 1 || group > 100) {
		printf("group number must between 1~100\n");
		exit(-1);
	}

	int i,j;
	for (i = 0; i < group; i++) {
		fscanf(fp, "%d\n", &wallCnt[i]);
		if (wallCnt[i] < 1 || wallCnt[i] > 1000) {
			printf("group%d's wall number must between 1~1000\n", i);
			exit(-1);
		}
		for (j = 0; j < wallCnt[i]; j++) {
			if (fscanf(fp, "%d", &height[i][j]) == EOF) {
				printf("error while read group %d, wall %d\n", i, j);
				exit(-1);
			}
		}
	}

	fclose(fp);
}

int pondedWater(int groupId)
{
	int water = 0;
	int head = 0;
	int tail = wallCnt[groupId] - 1;
	int sideHeight;		//side wall height
	int dir;			//direction, 1:head to tail, -1:tail to head
	int *p;				//current wall

	if (head == tail)
		return 0;

	while (head != tail)
	{
		//search from the lower side
		if (height[groupId][head] < height[groupId][tail]) {
			dir = 1;
			p = &head;
		}
		else {
			dir = -1;
			p = &tail;
		}

		sideHeight = height[groupId][*p];
		*p += dir;//move to next wall

		//if meets a higher or same height wall, saves no water
		//if meets a lower wall, will saves some water
		while (sideHeight > height[groupId][*p]) {
			water += sideHeight - height[groupId][*p];
			*p += dir;//move to next wall
		}
	}

	return water;
}

int main(void)
{
	getInput();
	int i;
	for (i = 0; i < group; i++)
		printf("%d\n", pondedWater(i));
}
