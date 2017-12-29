#include <stdio.h>
#include <string.h>
#include <iostream>
#define INF 0x3f3f3f3f

using namespace std;
const int max = 1000 + 10;
struct Edge
{
    int u, v, w, next;
} E[25];
int head[25];
int r[25], t[25]; //r[i]为i时刻需要的出纳员的数目，t[i]为i时刻应征的申请者数目
int cases, n, cnt, top;
int Q[25], d[25], inqueue[25];

inline void init()
{
    memset(head, -1, sizeof(head));
    memset(d, INF, sizeof(d));
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
void build(int sum)
{
    init();
    addEdge(24, 0, -sum);
    for (int i = 1; i <= 24; ++i)
    {
        addEdge(i, i - 1, 0);
        addEdge(i - 1, i, t[i]);
    }
    for (int i = 1; i <= 16; ++i)
        addEdge(i + 8, i, -r[i + 8]);
    for (int i = 17; i <= 24; ++i)
        addEdge(i - 16, i, -r[i - 16] + sum);
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
            if (d[u] + E[i].w < d[v])
                d[v] = d[u] + E[i].w;
            printf("%d %d %d %d\n", u, v, temp, d[v]);
            if (temp != d[v] && !inqueue[v])
            {
                Q[top++] = v;
                inqueue[v] = true;
            }
        }
    }
}
bool isFeasible(int sum)
{
    build(sum);
    spfa(0);
    bool hasCycle = false;
    for (int i = 0; i < 25; ++i)
        if (d[E[i].u] + E[i].w < d[E[i].v])
            hasCycle = true;
    if (!hasCycle && d[24] == sum)
        return true;
    return false;
}
int main()
{
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
    while (scanf("%d", &cases) == 1)
    {
        while (cases--)
        {
            memset(t, 0, sizeof(t));
            bool feasible = false;
            for (int i = 1; i <= 24; ++i)
                scanf("%d", &r[i]);
            scanf("%d", &n);
            for (int i = 1; i <= n; ++i)
            {
                int a;
                scanf("%d", &a);
                t[a + 1]++;
            }
            int low = 0, high = n, mid;
            while (low < high)
            {
                //printf("%d %d\n", low, high);
                mid = (low + high) / 2;
                if (isFeasible(mid))
                    high = mid;
                else
                    low = mid + 1;
            }
            if (low > n)
                printf("No Solution\n");
            else
                printf("%d\n", low);
        }
    }
    return 0;
}