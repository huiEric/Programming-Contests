#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50000
#define MAX_K 100000

using namespace std;

int n, k;
int parents[MAX_N];
int ranks[MAX_N];
int r[MAX_N];

void makeSets()
{
	for(int i = 1; i <= n; i++)
	{
		parents[i] = i;
		ranks[i] = 0;
		r[i] = 0; //0 represents similar
	}
}

int find(int x)
{
	if(parents[x] != x) 
	{
		int p = parents[x];
		parents[x] = find(parents[x]);
		r[x] = (r[x] + r[p]) % 3;
	}
	return parents[x];
}

void Union(int x, int y, int d)
{
	int x_parent = find(x);
	int y_parent = find(y);
	if(ranks[x_parent] < ranks[y_parent])
	{
		parents[x_parent] = y_parent;
		if(d == 1) r[x_parent] = (3 - r[x] + r[y]) % 3;
		if(d == 2) r[x_parent] = (3 - r[x] + 2 + r[y]) % 3;
	}
	else
	{
		parents[y_parent] = x_parent;
		if(d == 1) r[y_parent] = (3 - r[y] + r[x]) % 3;
		if(d == 2) r[y_parent] = (3 - r[y] + 1 + r[x]) % 3;
		if(ranks[x_parent] == ranks[y_parent]) ranks[x_parent]++;
	}
}

int main(int argc, char const *argv[])
{
	scanf("%d%d", &n, &k);
	makeSets();
	int d, x, y;
	int fake = 0;
	for(int i = 0; i < k; i++)
	{
		scanf("%d%d%d", &d, &x, &y);
		if(x > n || y > n || (d == 2 && x == y)) fake++;
		else if(find(x) == find(y))
		{
			if(d == 1 && r[x] != r[y]) fake++;
			if(d == 2 && (r[x] + 1) % 3 != r[y]) fake++;
		}
		else Union(x, y, d);
	}
	printf("%d", fake);
	return 0;
}