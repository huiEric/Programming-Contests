#include <stdio.h>
#include <stdlib.h>

#define PRICE 10
#define ONEMORE 3
#define TWOMORE 5

int N;

int main()
{
	int total = 0;
	scanf("%d", &N);
	int bought = N / PRICE;
	total += bought;
	while(bought >= TWOMORE)
	{
		total += bought / TWOMORE * 2;
		bought = bought % TWOMORE;
	}
	while(bought >= ONEMORE)
	{
		total += bought / ONEMORE * 1;
		bought = bought % ONEMORE;
	}
	printf("%d", total);
	return 0;
}