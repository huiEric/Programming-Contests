#include <stdio.h>
#include <iostream>

using namespace std;
const int maxn = 5e4 + 6;
int n, m;
struct node {int setv, lsum, rsum, sum;} T[maxn * 4];

void pushup(int l, int r, int o)
{
    if(T[o].setv == 0)
    {
        T[o].lsum = T[o].rsum = T[o].sum = r - l + 1;
        return;
    }
    if (T[o].setv == 1)
    {
        T[o].lsum = T[o].rsum = T[o].sum = 0;
        return;
    }
    if(r > l) //非叶子节点
    {
        T[o].lsum = T[o * 2].lsum;
        T[o].rsum = T[o * 2 + 1].rsum;
        T[o].sum = max(T[o].lsum, T[o].rsum);
        int mid = (l + r) / 2;
        int len = r - l + 1;
        if (T[o].lsum == len - len / 2)
            T[o].lsum += T[o * 2 + 1].lsum;
        if (T[o].rsum == len / 2)
            T[o].rsum += T[o * 2].rsum;
        T[o].sum = max(T[o].sum, T[o * 2].rsum + T[o * 2 + 1].lsum);
    }
}
void pushdown(int o)
{
    if(T[o].setv != -1)
    {
        T[o * 2].setv = T[o * 2 + 1].setv = T[o].setv;
        T[o].setv = -1;
    }
}
void build(int l, int r, int o)
{
    T[o].setv = -1;
    if(l == r)
    {
        T[o].lsum = T[o].rsum = T[o].sum = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, o * 2);
    build(mid + 1, r, o * 2 + 1);
    pushup(l, r, o);
    //printf("%d %d %d\n", l, r, T[o].sum);
}
void update(int l, int r, int o, int x, int y, int v)
{
    //printf("%d %d\n", l, r);
    if(x <= l && r <= y)
    {
        T[o].setv = v;
        //printf("%d %d %d\n", l, r, v);
    }
    else
    {
        pushdown(o);
        int mid = (l + r) / 2;
        if(x <= mid) update(l, mid, o * 2, x, y, v);
        else pushup(l, mid, o * 2);
        if(mid < y) update(mid + 1, r, o * 2 + 1, x, y, v);
        else pushup(mid + 1, r, o * 2 + 1);
    }
    pushup(l, r, o);
    //printf("%d %d %d %d %d %d\n", l, r, T[o].sum, T[o].lsum, T[o].rsum, T[o].setv);
}
int query(int l, int r, int o, int len)
{
    //printf("%d %d %d  %d %d %d  %d %d %d\n", T[o].lsum, T[o].rsum, T[o].sum, T[o * 2].lsum, T[o * 2].rsum, T[o * 2].sum, T[o * 2 + 1].lsum, T[o * 2 + 1].rsum, T[o * 2 + 1].sum);
    if(T[o].sum < len) return 0;
    if(T[o].lsum >= len) return l;
    int mid = (l + r) / 2;
    if(T[o * 2].sum >= len) return query(l, mid, o * 2, len);
    else if(T[o * 2].rsum + T[o * 2 + 1].lsum >= len) return mid - T[o * 2].rsum + 1;
    else return query(mid + 1, r, o * 2 + 1, len);
}

int main()
{
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    while(scanf("%d%d", &n, &m) == 2)
    {
        build(1, n, 1);
        int op, x, d; 
        for(int i = 1; i <= m; ++i)
        {
            scanf("%d", &op);
            if (op == 1)
            {
                scanf("%d", &d);
                x = query(1, n, 1, d);
                if (x != 0)
                    update(1, n, 1, x, x + d - 1, 1);
                printf("%d\n", x);
            }
            else
            {
                scanf("%d%d", &x, &d);
                update(1, n, 1, x, x + d - 1, 0);
            }
        }
    }
    return 0;
}