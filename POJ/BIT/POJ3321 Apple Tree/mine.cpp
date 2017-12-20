#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define MAX_N 100010
#define MAX_M 100010

using namespace std;

int N, M;
vector<vector<int> > G(MAX_N);
int L[MAX_N], R[MAX_N], bit[MAX_N];
bool picked[MAX_N];

int dfn = 1;
void dfs(int u, int p)
{
	L[u] = dfn++;
	for(int i = 0; i < G[u].size(); ++i)
	{
		int v = G[u][i];
		if(v == p) continue;
		dfs(v, u);
	}
	R[u] = dfn;
}

int lowbit(int i)
{
	return i & (-i);
}

void add(int i, int w)
{
	for(int j = i; j <= N; j += lowbit(j))
		bit[j] += w;
}

int sum(int i)
{
	int ans = 0;
	for(int j = i; j > 0; j -= lowbit(j))
		ans += bit[j];
	return ans;
}

int main(int argc, char const *argv[])
{
	scanf("%d", &N);
	for(int i = 0; i < N - 1; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}

	dfs(1, 0);

	for(int i = 1; i <= N; ++i)
	{
		add(L[i], +1);
		picked[i] = false;
	}

	scanf("%d", &M);
	for(int i = 0; i < M; ++i)
	{
		char cmd[2];
		int x;
		scanf("%s%d", cmd, &x);
		if(cmd[0] == 'C')
		{
			if(picked[x]) add(L[x], +1);
			else add(L[x], -1);
			picked[x] = !picked[x];
		}
		else printf("%d\n", sum(R[x] - 1) - sum(L[x] - 1));
	}
	return 0;
}