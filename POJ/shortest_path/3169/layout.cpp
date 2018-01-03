#include <stdio.h>
#include <string.h>
#include <iostream>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long ll;
const int maxn = 1000 + 10;
const int maxm = 10000 + 10;
struct Edge
{
    int u, v, w, next;
} E[maxm * 3];
int head[maxn];
int Q[maxn], count[maxn];
ll d[maxn];
bool inqueue[maxn];
int cnt, top;
int n, ml, md;

inline void init()
{
    memset(head, -1, sizeof(head));
    memset(d, INF, sizeof(d));
    memset(count, 0, sizeof(count));
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
void spfa(int s, bool &hasCycle)
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
            if (d[u] + E[i].w < d[v])
                d[v] = d[u] + E[i].w;
            if (temp != d[v] && !inqueue[v])
            {
                count[v]++;
                if(count[v] > n)
                {
                    hasCycle = true;
                    return;
                }
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
    while (scanf("%d%d%d", &n, &ml, &md) == 3)
    {
        init();
        int a, b, D;
        bool hasCycle = false;
        for(int i = 1; i <= ml; ++i)
        {
            scanf("%d%d%d", &a, &b, &D);
            addEdge(a, b, D);
        }
        for(int i = 1; i <= md; ++i)
        {
            scanf("%d%d%d", &a, &b, &D);
            addEdge(b, a, -D);
        }
        for(int i = 1; i <= n; ++i)
            addEdge(i + 1, i, 0);
        spfa(1, hasCycle);
        if(hasCycle) printf("-1\n");
        else if(d[n] == d[0]) printf("-2\n");
        else printf("%lld\n", d[n]);
    }
    return 0;
}