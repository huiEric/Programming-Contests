#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;
typedef int64_t INT;
const int MAX = 40000 + 10;
struct Building {
    INT a, b, h;
} buildings[MAX];
INT temp[MAX << 1], sumv[MAX << 2], setv[MAX << 2], _sum, v;
int n, cnt, a, b;

void build()
{
    for (int i = cnt << 2 - 1; i >= 1; --i)
    {
        setv[i] = 0;
        sumv[i] = 0;
    }
}
void maintain(int o, int L, int R)
{
    if (R > L)
    {
        sumv[o] = sumv[o * 2] + sumv[o * 2 + 1];
    }
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
    int lc = o * 2, rc = o * 2 + 1;
    if (a <= temp[L] && temp[R] <= b)
    {
        setv[o] = max(setv[o], v);
    }
    else
    {
        pushdown(o);
        int M = L + (R - L) / 2;
        if (a <= temp[M])
            update(lc, L, M);
        else
            maintain(lc, L, M);
        if (b > temp[M])
            update(rc, M + 1, R);
        else
            maintain(rc, M + 1, R);
    }
    maintain(o, L, R);
}
void query(int o, int L, int R)
{
    if (setv[o] > 0)
    {
        _sum += setv[o] * (temp[R] - temp[L]);
    }
    else if (a <= temp[L] && b >= temp[R])
    {
        _sum += sumv[o];
    }
    else
    {
        int M = L + (R - L) / 2;
        if (a <= temp[M])
            query(o * 2, L, M);
        if (b > temp[M])
            query(o * 2 + 1, M + 1, R);
    }
}

int main()
{
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
    {
        scanf("%ld%ld%ld", &buildings[i].a, &buildings[i].b, &buildings[i].h);
        temp[2 * i - 1] = buildings[i].a;
        temp[2 * i] = buildings[i].b;   
    }
    sort(temp + 1, temp + 2 * n + 1);
    cnt = unique(temp + 1, temp + 2 * n + 1) - (temp + 1);
    build();
    for(int i = 1; i <= n; ++i)
    {
        a = buildings[i].a;
        b = buildings[i].b;
        v = buildings[i].h;
        update(1, 1, cnt);
    }
    _sum = 0;
    query(1, 1, cnt);
    printf("%ld\n", _sum);
    return 0;
}