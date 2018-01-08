#include <stdio.h>
#include <string.h>
#include <iostream>
#define INF 0x3f3f3f3f

using namespace std;
const int maxn = 50000 + 10;
struct Edge
{
    int u, v, w, next;
} E[maxn * 3];
int head[maxn];
int Q[maxn], d[maxn];
bool inqueue[maxn];
int n, cnt, top;

inline void init()
{
    memset(head, -1, sizeof(head));
    memset(d, -INF, sizeof(d));
    memset(inqueue, false, sizeof(inqueue));
    cnt = 0;
    top = 0;
}
inline void addEdge(int u, int v, int w)
{
    E[cnt].u = u;
    E[cnt].v = v;
    E[cnt].w = w;
    E[cnt].next = head[u];
    head[u] = cnt++;
}
void spfa(int s)
{
    Q[top++] = s;
    inqueue[s] = true;
    d[s] = 0;
    while (top > 0)
    {
        int u = Q[--top];
        inqueue[u] = false;
        for (int i = head[u]; i != -1; i = E[i].next)
        {
            int v = E[i].v;
            int temp = d[v];
            if (d[u] + E[i].w > d[v])
                d[v] = d[u] + E[i].w;
            if (temp != d[v] && !inqueue[v])
            {
                Q[top++] = v;
                inqueue[v] = true;
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
    while (scanf("%d", &n) == 1)
    {
        init();
        int bmax = 0, amin = maxn;
        for(int i = 1; i <= n; ++i)
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            bmax = max(bmax, b);
            amin = min(amin, a);
            addEdge(a, b + 1, c);
        }
        for(int i = 1; i <= bmax + 1; ++i)
        {
            addEdge(i - 1, i, 0);
            addEdge(i, i - 1, -1);
        }
        spfa(0);
        printf("%d\n", d[bmax + 1]);
    }
    return 0;
}