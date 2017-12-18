#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 101000, INF = 0x3f3f3f3f;
int n, nq, s, head[N], etot, dep[N], plca[N][20], in[N], out[N], val[N], C[N << 1], tim, idn[N];
struct edge
{
    int v, id, next;
} g[N << 1];
void add_edge(int u, int v, int id)
{
    g[etot].v = v, g[etot].id = id, g[etot].next = head[u], head[u] = etot++;
}
void dfs(int u, int fa, int deep)
{
    dep[u] = deep;
    plca[u][0] = fa;
    for (int i = 1; i < 20; i++)
        plca[u][i] = plca[u][i - 1] == -1 ? -1 : plca[plca[u][i - 1]][i - 1];
    for (int i = head[u]; i != -1; i = g[i].next)
    {
        edge &e = g[i];
        if (e.v == fa)
            continue;
        in[e.id] = idn[e.v] = ++tim;
        dfs(e.v, u, deep + 1);
        out[e.id] = ++tim;
    }
}
int lca(int a, int b)
{
    if (dep[a] < dep[b])
        swap(a, b);
    for (int i = 0; i < 20; i++)
        if (dep[a] - dep[b] >> i & 1)
            a = plca[a][i];
    if (a != b)
    {
        for (int i = 19; i >= 0; i--)
            if (plca[a][i] != plca[b][i])
                a = plca[a][i], b = plca[b][i];
        a = plca[a][0];
    }
    return a;
}
void modify(int p, int dt)
{
    for (int i = p; i <= tim; i += i & -i)
        C[i] += dt;
}
int query(int p)
{
    int ret = 0;
    for (int i = p; i > 0; i -= i & -i)
        ret += C[i];
    return ret;
}
int main()
{
    while (~scanf("%d%d%d", &n, &nq, &s))
    {
        memset(head, -1, sizeof(head));
        etot = 0;
        tim = 0;
        for (int i = 1; i <= n - 1; i++)
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add_edge(a, b, i);
            add_edge(b, a, i);
            val[i] = c;
        }
        dfs(1, -1, 0);
        memset(C, 0, sizeof(C));
        for (int i = 1; i <= n - 1; i++)
        {
            modify(in[i], val[i]);
            modify(out[i], -val[i]);
        }
        while (nq--)
        {
            int op, a, b;
            scanf("%d", &op);
            if (op == 0)
            {
                scanf("%d", &a);
                printf("%d\n", query(idn[a]) + query(idn[s]) - query(idn[lca(a, s)]) * 2);
                s = a;
            }
            else
            {
                scanf("%d%d", &a, &b);
                int dt = b - val[a];
                modify(in[a], dt);
                modify(out[a], -dt);
                val[a] = b;
            }
        }
    }
    return 0;
}
