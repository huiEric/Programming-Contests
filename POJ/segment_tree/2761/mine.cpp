#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 6;
//root记录所有线段树的根节点，temp为离散化后的数组
int n, m, cnt, root[maxn], a[maxn], temp[maxn], total, x, y, k;
//线段树上每个节点维护的数据，左右节点索引和在区间内的元素个数
struct node {int l, r, sum;} T[maxn * 40];

int getid(int x)
{
    return lower_bound(temp, temp + total, x) - temp + 1;
}
void update(int l, int r, int &x, int y, int pos)
{
    //每次迭代新增一个节点，其中一个子节点只保留索引，另一个子节点递归延伸增加子孙节点，同时自增本区间内的元素个数
    T[++cnt] = T[y]; T[cnt].sum++; x = cnt;
    if(l == r) return;
    int mid = (l + r) / 2;
    if(mid >= pos) update(l, mid, T[x].l, T[y].l, pos);
    else update(mid + 1, r, T[x].r, T[y].r, pos);
}
int query(int l, int r, int x, int y, int k)
{
    //[1..y]区间中元素的个数-[1..x]区间中元素的个数 为[x+1..y]区间中元素的个数，而区间已事先排好序
    if(l == r) return l;
    int mid = (l + r) / 2;
    int sum = T[T[y].l].sum - T[T[x].l].sum;
    if(sum >= k) return query(l, mid, T[x].l, T[y].l, k);
    else return query(mid + 1, r, T[x].r, T[y].r, k - sum);
}

int main()
{
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    while (scanf("%d%d", &n, &m) == 2)
    {
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &a[i]);
            temp[i - 1] = a[i];
        }
        sort(temp, temp + n);
        total = unique(temp, temp + n) - temp;
        for (int i = 1; i <= n; ++i)
            update(1, n, root[i], root[i - 1], getid(a[i]));
        for (int i = 1; i <= m; ++i)
        {
            scanf("%d%d%d", &x, &y, &k);
            printf("%d\n", temp[query(1, n, root[x - 1], root[y], k) - 1]);
        }
        printf("\n");
    }
    return 0;
}