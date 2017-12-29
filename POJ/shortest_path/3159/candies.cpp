#include <stdio.h>
#include <string.h>
#include <iostream>
#define INF 0x3f3f3f3f

using namespace std;
const int maxn = 30000 + 10;
const int maxm = 15e4 + 10;
struct Edge
{
    int v, w, next;
} E[maxm];
int head[maxn];     //链式前向星
int d[maxn];        //每个点的最短路径长
int Q[maxn];        //数组实现栈
bool inqueue[maxn]; //记录是否在栈中
int n, m, cnt, top;

inline void init()
{
    memset(head, -1, sizeof(head));
    memset(inqueue, false, sizeof(inqueue));
    memset(d, INF, sizeof(d));
    top = 0;
    cnt = 0;
}
inline void addEdge(int u, int v, int w)
{
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
            if(d[u] + E[i].w < d[v])
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
    while (scanf("%d%d", &n, &m) == 2)
    {
        int u, v, w;
        init();
        for (int i = 1; i <= m; ++i)
        {
            scanf("%d%d%d", &u, &v, &w);
            addEdge(u, v, w);
        }
        spfa(1);
        printf("%d\n", d[n]);
    }
}