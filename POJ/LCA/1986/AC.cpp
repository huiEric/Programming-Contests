#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define N 40010
#define M 20010

int head[N];
struct edge
{
    int u, v, w, next;
} e[2 * N];
int __head[N];
struct ask
{
    int u, v, lca, next;
} ea[M];
int fa[N], ance[N], dir[N];
bool vis[N];

inline void add_edge(int u, int v, int w, int &k)
{
    e[k].u = u;
    e[k].v = v;
    e[k].w = w;
    e[k].next = head[u];
    head[u] = k++;
    u = u ^ v;
    v = u ^ v;
    u = u ^ v;
    e[k].u = u;
    e[k].v = v;
    e[k].w = w;
    e[k].next = head[u];
    head[u] = k++;
}

inline void add_ask(int u, int v, int &k)
{
    ea[k].u = u;
    ea[k].v = v;
    ea[k].lca = -1;
    ea[k].next = __head[u];
    __head[u] = k++;
    u = u ^ v;
    v = u ^ v;
    u = u ^ v;
    ea[k].u = u;
    ea[k].v = v;
    ea[k].lca = -1;
    ea[k].next = __head[u];
    __head[u] = k++;
}

int find(int x)
{
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void Tarjan(int u)
{
    vis[u] = true;
    ance[u] = fa[u] = u;
    for (int k = head[u]; k != -1; k = e[k].next)
        if (!vis[e[k].v])
        {
            int v = e[k].v, w = e[k].w;
            dir[v] = dir[u] + w;
            Tarjan(v);
            fa[v] = u;
        }
    for (int k = __head[u]; k != -1; k = ea[k].next)
        if (vis[ea[k].v])
            ea[k].lca = ea[k ^ 1].lca = ance[find(ea[k].v)];
}

int main()
{
    std::ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    int n, m, q, k;
    char str[10];
    while (scanf("%d%d", &n, &m) != EOF)
    {
        memset(head, -1, sizeof(head));
        memset(__head, -1, sizeof(__head));
        memset(vis, false, sizeof(vis));
        k = 0;
        while (m--)
        {
            int u, v, w;
            scanf("%d%d%d%s", &u, &v, &w, str);
            add_edge(u, v, w, k);
        }
        scanf("%d", &q);
        k = 0;
        for (int i = 0; i < q; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            add_ask(u, v, k);
        }
        dir[1] = 0;
        Tarjan(1);
        for (int i = 0; i < q; i++)
        {
            int s = i * 2, u = ea[s].u, v = ea[s].v, lca = ea[s].lca;
            printf("%d\n", dir[u] + dir[v] - 2 * dir[lca]);
        }
    }
    return 0;
}
