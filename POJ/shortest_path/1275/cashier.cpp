#include <stdio.h>
#include <string.h>
#include <iostream>
#define INF 0x3f3f3f3f

using namespace std;
const int max = 1000 + 10;
struct Edge
{
    int u, v, w, next;
} E[25 * 3 + 1];
int head[25];
int r[25], t[25]; //r[i]为i时刻需要的出纳员的数目，t[i]为i时刻应征的申请者数目
int cases, n, cnt, top;
int Q[25], d[25], inqueue[25], count[25];

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
void build(int sum)
{
    init();
    addEdge(0, 24, -sum);
    //printf("%d\n", -sum);
    for (int i = 1; i <= 24; ++i)
    {
        addEdge(i - 1, i, 0);
        addEdge(i, i - 1, t[i]);
        //printf("%d %d %d\n", i, i - 1, t[i]);
    }
    //printf("\n");
    for (int i = 1; i <= 16; ++i)
    {
        addEdge(i, i + 8, -r[i + 8]);
        //printf("%d %d %d\n",i, i + 8, -r[i + 8]);
    }
    //printf("\n");
    for (int i = 17; i <= 24; ++i)
    {
        addEdge(i, i - 16, -r[i - 16] + sum);
        //printf("%d %d %d\n",i, i - 16, -r[i - 16] + sum);
    }
    //printf("\n");
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
                if(count[v] > 24)
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
bool isFeasible(int sum)
{
    bool hasCycle = false;
    build(sum);
    spfa(0, hasCycle);
    if (!hasCycle && d[24] == -sum)
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
                mid = (low + high) / 2;
                if (isFeasible(mid))
                    high = mid;
                else
                    low = mid + 1;
            }
            if (low == n && !isFeasible(high))
                printf("No Solution\n");
            else
                printf("%d\n", low);
        }
    }
    return 0;
}