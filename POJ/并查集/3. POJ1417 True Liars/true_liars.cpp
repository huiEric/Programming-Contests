#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_P 600

using namespace std;

int n, p1, p2;
int p[MAX_P], ranks[MAX_P], r[MAX_P];
int a[MAX_P], total[MAX_P];
int cat[MAX_P], pa[MAX_P];
bool flag;
int dp[MAX_P][MAX_P];
int divine[MAX_P];

void makeSets()
{
	for(int i = 1; i <= p1 + p2; ++i)
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
		r[x] = (r[x] + r[t]) % 2;
	}
	return p[x];
}

void Union(int x, int y, int ans)
{
	int xp = find(x);
	int yp = find(y);
	if(ranks[xp] < ranks[yp])
	{
		p[xp] = yp;
		r[xp] = (r[x] + ans + r[y]) % 2;
	}
	else
	{
		p[yp] = xp;
		r[yp] = (r[y] + ans + r[x]) % 2;
		if(ranks[xp] == ranks[yp]) ranks[xp]++;
	}
}
int main(int argc, char const *argv[])
{
	while(1)
	{
		scanf("%d%d%d", &n, &p1, &p2);		
		if(n == 0 && p1 == 0 && p2 == 0) break;
		memset(p, 0, sizeof(p));
		memset(ranks, 0, sizeof(ranks));
		memset(r, 0, sizeof(r));
		memset(a, 0, sizeof(a));
		memset(total, 0, sizeof(total));
		memset(cat, 0, sizeof(cat));
		memset(pa, 0, sizeof(pa));
		memset(dp, 0, sizeof(dp));
		memset(divine, 0, sizeof(divine));
		makeSets();
		int m = p1 + p2;
		flag = true;
		for(int i = 0; i < n; ++i)
		{
			char str[4];
			int x, y, ans;
			scanf("%d%d%s", &x, &y, str);
			ans = (str[0] == 'n');
			if(find(x) == find(y)) continue;
			Union(x, y, ans);			
		}
		for(int i = 1; i <= m; ++i) find(i);
		int cnt = 0;
		for(int i = 1; i <= m; ++i)
		{
			int p = find(i);
			if(cat[p] == 0)
			{
				cat[p] = ++cnt;
				pa[cnt] = p;
			}
			total[cat[p]]++;
			if(r[i] == 0) a[cat[p]]++;
		}
		dp[0][0] = 1;
		for(int i = 1; i <= cnt; ++i)
		{
			int x = a[i], y = total[i] - a[i];
			if(x == y)
			{
				flag = false;
				break;
			}
			for(int j = m; j >= x; --j) dp[i][j] += dp[i - 1][j - x];
			for(int j = m; j >= y; --j) dp[i][j] += dp[i - 1][j - y];
		}
		if(dp[cnt][p1] != 1 || !flag) printf("no\n");
		else
		{
			int cur = p1;
			for(int i = cnt; i >= 1; --i)
			{
				int x = a[i], y = total[i] - a[i];
				if(dp[i - 1][cur - x] == 1)
				{
					divine[i] = 0;
					cur = cur - x;
				}
				else
				{
					divine[i] = 1;
					cur = cur - y;
				}				
			}
			for(int i = 1; i <= m; ++i)
			{
				int p = find(i);
				if(r[i] == divine[cat[p]]) printf("%d\n", i);
			}
			printf("end\n");
		}
	}	
	return 0;
}