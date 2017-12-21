#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define RST(N) memset(N, 0, sizeof(N))
using namespace std;

typedef int64_t INT;

typedef struct Building_
{
    INT x1, x2, height;
} Building;

struct Trie
{
    INT left, right, hi;
} trie[1000000];

Building N[50000];
INT Node[100000]; //表示离散化后的端点个数；

bool cmp(Building a, Building b) { return a.height < b.height; }

void Init(int n) //初始化；
{
    RST(N), RST(trie), RST(Node);
    for (int i = 1; i <= n; i++)
    {
        scanf("%I64d %I64d %I64d", &N[i].x1, &N[i].x2, &N[i].height);
        Node[i * 2 - 1] = N[i].x1, Node[i * 2] = N[i].x2;
    }
    sort(N + 1, N + n + 1, cmp); //端点排序；
    sort(Node + 1, Node + 2 * n + 1);
    int j = 1;
    for (int i = 1; i <= 2 * n; i++)
    { //离散化；
        if (Node[i] != Node[j])
            Node[++j] = Node[i];
    }
    Node[0] = j;
    return;
}

void build(INT L, INT R, INT p)
{
    trie[p].left = Node[L];
    trie[p].right = Node[R];
    if (L + 1 == R)
        return;
    int mid = (L + R) / 2;
    build(L, mid, p * 2);
    build(mid, R, p * 2 + 1);
    return;
}

void update(INT L, INT R, INT value, INT p)
{
    if (L <= trie[p].left && trie[p].right <= R)
    { //当前线段被包含与插入的线段；
        trie[p].hi = value;
        return;
    }
    if (trie[p].hi > 0)
        trie[p * 2].hi = trie[p * 2 + 1].hi = trie[p].hi;
    trie[p].hi = -1;
    if (R > trie[p * 2].right)
        update(L, R, value, p * 2 + 1);
    if (L < trie[p * 2].right)
        update(L, R, value, p * 2);
    return;
}

INT Query(INT p)
{
    if (trie[p].hi > 0)
        return trie[p].hi * (trie[p].right - trie[p].left);
    if (trie[p].hi == 0)
        return 0;
    return (Query(p * 2) + Query(p * 2 + 1));
}

int main()
{
#ifdef LOCAL
        freopen("input.txt", "r", stdin);
#endif
    int n;
    scanf("%d", &n);
    Init(n);
    build(1, Node[0], 1);
    for (int i = 1; i <= n; i++)
        update(N[i].x1, N[i].x2, N[i].height, 1);
    printf("%I64d\n", Query(1));
}