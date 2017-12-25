#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>

#define MAX_N 1000

using namespace std;

int n, m;
vector<int> G[MAX_N]; //G[i]为节点i的所有子孙
int parent[MAX_N];
vector<int> Q[MAX_N];
bool visited[MAX_N];
int cnt[MAX_N];
int p[MAX_N]; //并查集

void makeSets() {
	for(int i = 1; i <= n; ++i) {
		p[i] = i;
	}
}

int find(int u) {
	if(p[u] != u) {
		p[u] = find(p[u]);
	}
	return p[u];
}

void Union(int u, int pa) {
	p[u] = pa;
}

void dfs(int u) {
	p[u] = u;
	for(int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i];
		dfs(v);
	}
	for(int i = 0; i < Q[u].size(); ++i) {
		int v = Q[u][i];
		if(visited[v]) cnt[find(v)]++;
	}
	visited[u] = true;
	p[u] = parent[u];
}

int main(int argc, char const *argv[]) {	
	std::ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
	while(scanf("%d", &n) == 1) {
		memset(visited, false, (n + 1) * sizeof(bool));
		memset(cnt, 0, (n + 1) * sizeof(int));
		makeSets();
		for(int i = 1; i <= n; ++i) {
			int u, num;
			scanf("%d:(%d)", &u, &num);
			for(int j = 0; j < num; ++j) {
				int v;
				scanf("%d", &v);
				G[u].push_back(v);
				parent[v] = u;
			}
		}

		int root;
		for(int i = 1; i <= n; ++i) {
			if(parent[i] == 0) {
				parent[i] = i;
				root = i;
				break;
			}
		}

		scanf("%d", &m);
		for(int i = 0; i < m; ++i) {
			int u, v;
			scanf(" (%d %d)", &u, &v);
			if(u == v) {
				cnt[u]++;
				continue;
			}
			Q[u].push_back(v);
			Q[v].push_back(u);
		}

		dfs(root);

		for(int i = 1; i <= n; ++i) {
			if(cnt[i] > 0) printf("%d:%d\n", i, cnt[i]);
		}

		for(int i = 1; i <= n; ++i) {
			G[i].clear();
			Q[i].clear();
		}
	}
	return 0;
}