#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_K 9

int n, k;
int kids[MAX_N];

int main(int argc, char const *argv[])
{
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n; i++)
		kids[i] = i + 1;
	int left = n;
	int cur_k = 1;
	while(left > 1)
	{
		for(int i = 0; i < n; i++)
		{
			if(kids[i] == 0) continue;
			if(cur_k % k == 0 || cur_k % 10 == k)
			{
				kids[i] = 0;
				left--;
			}
			cur_k++;
		}
	}
	for(int i = 0; i < n; i++)
	{
		if(kids[i] != 0)
		{
			printf("%d", i + 1);
			break;
		}
	}
	return 0;
}