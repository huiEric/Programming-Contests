#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

const int max_n = 2e4;

int cnt;
int start[max_n], end[max_n], odd[max_n], temp[max_n];
int p[max_n], ranks[max_n], r[max_n];

int findPos(int x)
{
	int s = 0, e = cnt;
	int mid;
	while(s < e)
	{
		mid = (s + e) / 2;
		if(temp[mid] == x) return mid;
		if(temp[mid] < x) s = mid + 1;
		else e = mid;
	}
	return -1;
}

void makeSets()
{
	for(int i = 0; i <= cnt; i++)
	{
		p[i] = i;
		ranks[i] = 0;
		r[i] = 0;
	}
}

int find(int x)
{
	if(p[x] != x)
	{
		int t = p[x];
		p[x] = find(p[x]);
		r[x] = r[x] ^ r[t];
	}
	return p[x];
}

void Union(int x, int y, int odd)
{
	int x_parent = find(x);
	int y_parent = find(y);
	if(ranks[x_parent] < ranks[y_parent])
	{
		p[x_parent] = y_parent;
		r[x_parent] = r[x] ^ odd ^ r[y];
	}
	else
	{
		p[y_parent] = x_parent;
		r[y_parent] = r[y] ^ odd ^ r[x];
		if(ranks[x_parent] == ranks[y_parent]) ranks[x_parent]++;
	}
}

int main(int argc, char const *argv[])
{
	int len, n, s, e;
	char str[5];
	cnt = 0;
	scanf("%d%d", &len, &n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d%d%s", &s, &e, str);
		start[i] = --s;
		end[i] = e;
		odd[i] = (str[0] == 'o');
		temp[cnt++] = s;
		temp[cnt++] = e;
	}
	sort(temp, temp + cnt);
	cnt = unique(temp, temp + cnt) - temp;
	makeSets();
	int X = 0;
	for(int i = 0; i < n; i++)
	{
		int left = findPos(start[i]), right = findPos(end[i]);
		//printf("%d %d\n%d %d\n", start[i], end[i], left, right);
		if(find(left) == find(right))
		{
			//printf("%d %d %d\n", r[left], r[right], odd[i]);
			if((r[left] ^ r[right]) != odd[i]) break;
		}
		else Union(left, right, odd[i]);
		X++;
	}
	printf("%d", X);
	return 0;
}