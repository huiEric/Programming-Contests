#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define MAX_N 1000
#define INF 10000

using namespace std;

int n;
int a[MAX_N];

int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}
	sort(a, a + n);
	int final_index = 0;
	int cur_diff = INF;
	for(int i = 0; i < n - 1; i++)
	{
		if(a[i + 1] - a[i] < cur_diff)
		{
			final_index = i;
			cur_diff = a[i + 1] - a[i];
		}
		if(cur_diff == 0) break;
	}
	printf("%d", cur_diff);
	return 0;
}