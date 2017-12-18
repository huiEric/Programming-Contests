#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const int MAXN = 100001 + 10;
const int MAXQ = 100001 + 10;
const int MAXW = 10000 + 10;
struct Edge {
    int v, id, next;
} E[MAXN << 1];
int n, q, s, cnt, dfn;
int head[MAXN], val[MAXN], in[MAXN], out[MAXN], idn[MAXN], plca[MAXN][20], dep[MAXN];
ll bit[MAXN << 1];

inline void init()
{
    cnt = 0;
    dfn = 0;
    memset(head, -1, sizeof(head));
    memset(bit, 0, sizeof(bit));
}
inline void addEdge(int u, int v, int id)
{
    E[cnt].v = v; E[cnt].id = id; E[cnt].next = head[u]; head[u] = cnt++;
}
void dfs(int u, int p, int depth)
{
    dep[u] = depth;
    plca[u][0] = p;
    for(int i = 1; i < 20; ++i)
        plca[u][i] = plca[u][i - 1] == -1? -1 : plca[plca[u][i - 1]][i - 1];
    for(int i = head[u]; i != -1; i = E[i].next)
    {
        Edge &e = E[i];
        if(e.v == p) continue;
        in[e.id] = idn[e.v] = ++dfn;
        dfs(e.v, u, depth + 1);
        out[e.id] = ++dfn;
    }
}
int lca(int u, int v)
{
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 0; i < 20; ++i)
        if(dep[u] - dep[v] >> i & 1) u = plca[u][i];
    if(u != v)
    {
        for(int i = 19; i >= 0; --i)
            if(plca[u][i] != plca[v][i])
            {
                u = plca[u][i];
                v = plca[v][i];
            }
        u = plca[u][0];
    }
    return u;
}
ll sum(int pos)
{
    ll ans = 0;
    for(int i = pos; i > 0; i -= i & -i)
        ans += bit[i];
    return ans;
}
void add(int pos, ll w)
{
    for(int i = pos; i < (n << 1); i += i & -i)
        bit[i] += w;
}
int main()
{
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    while(scanf("%d%d%d", &n, &q, &s) == 3)
    {
        init();
        for(int i = 1; i <= n - 1; ++i)
        {
            int a, b, w;
            scanf("%d%d%d", &a, &b, &w);
            addEdge(a, b, i);
            addEdge(b, a, i);
            val[i] = w;
        }

        dfs(1, -1, 0);
        for(int i = 1; i <= n - 1; ++i)
        {
            add(in[i], val[i]);
            add(out[i], -val[i]);
        }

        for(int i = 0; i < q; ++i)
        {
            int op;
            scanf("%d", &op);
            if(op == 0)
            {
                int u;
                scanf("%d", &u);
                printf("%lld\n", sum(idn[u]) + sum(idn[s]) - sum(idn[lca(u, s)]) * 2);
                s = u;
            }
            else
            {
                int i, w;
                scanf("%d%d", &i, &w);
                int delta = w - val[i];
                add(in[i], delta);
                add(out[i], -delta);
                val[i] = w;
            }
        }
    }
    return 0;
}