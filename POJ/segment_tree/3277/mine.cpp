#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long INT;
const int MAX = 40000 * 2 + 10;
struct Building {
    INT a, b, h;
} buildings[MAX];
INT temp[MAX], sumv[MAX * 4], setv[MAX * 4], v, a, b;
int n, cnt;

bool comp(Building b1, Building b2)
{
    return b1.h < b2.h;
}
inline void build()
{
    for (int i = cnt << 2 - 1; i >= 1; --i)
    {
        setv[i] = 0;
        sumv[i] = 0;
    }
}
void maintain(int o, int L, int R)
{
    if(setv[o] > 0) 
    {
        sumv[o] = setv[o] * (temp[R] - temp[L]);
        return;
    }
    sumv[o] = sumv[o * 2] + sumv[o * 2 + 1];
}
void pushdown(int o)
{
    if (setv[o] > 0)
    {
        setv[o * 2] = setv[o * 2 + 1] = setv[o];
        setv[o] = 0;
    }
}
void update(int o, int L, int R)
{
    //printf("%d %d %d %ld %ld %ld %ld\n", o, L, R, temp[L], temp[R], a, b);
    int lc = o * 2, rc = o * 2 + 1;
    if (a <= temp[L] && temp[R] <= b)
    {
        setv[o] = max(setv[o], v);
        //printf("%ld %ld %ld %ld\n", temp[L], temp[R], setv[o], v);
    }
    else
    {
        pushdown(o);
        int M = L + (R - L) / 2;
        //printf("%ld\n", temp[M]);
        if (a < temp[M] || b == temp[M])
            update(lc, L, M);
        else
            maintain(lc, L, M);
        if (b > temp[M] || a == temp[M])
            update(rc, M, R);
        else
            maintain(rc, M, R);
    }
    maintain(o, L, R);
}
// void dfs(int o, int L, int R)
// {
//     //printf("%ld %ld %ld\n", temp[L], temp[R], sumv[o]);
//     printf("%ld %ld %ld\n", temp[L], temp[R], setv[o]);
//     int M = (L + R) / 2;
//     if(M == L) return;
//     dfs(o * 2, L, M);
//     dfs(o * 2 + 1, M, R);
// }

int main()
{
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    while(scanf("%d", &n) == 1)
    {
        for (int i = 1; i <= n; ++i)
        {
            scanf("%lld%lld%lld", &buildings[i].a, &buildings[i].b, &buildings[i].h);
            temp[2 * i - 1] = buildings[i].a;
            temp[2 * i] = buildings[i].b;
        }
        sort(buildings + 1, buildings + 1 + n, comp);
        sort(temp + 1, temp + 2 * n + 1);
        cnt = unique(temp + 1, temp + 2 * n + 1) - (temp + 1);
        //for(int i = 1; i <= cnt; ++i) printf("%ld ", temp[i]);
        //printf("\n");
        build();
        for (int i = 1; i <= n; ++i)
        {
            a = buildings[i].a;
            b = buildings[i].b;
            v = buildings[i].h;
            update(1, 1, cnt);
        }
        //dfs(1, 1, cnt);
        printf("%lld\n", sumv[1]);
    }
    return 0;
}