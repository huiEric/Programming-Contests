#include <stdio.h>
#include <iostream>

using namespace std;
const int MAX = 100000 + 10;
int colors[MAX << 2], setv[MAX << 2];
int l, t, o, a, b, c, _color;

void printb(int x)
{
    int a[32];
    for(int i = 0; i < 32; ++i)
    {
        a[i] = x & 1;
        x >>= 1;
    }
    for(int i = 31; i >=0; --i) printf("%d", a[i]);
}
void build()
{
    for (int i = 4 * l - 1; i >= 1; --i)
    {
        setv[i] = 0;
        colors[i] = 1 << 1;
    }
}
void maintain(int o, int L, int R)
{
    //colors[o] = 0;
    if (R > L)
    {
        colors[o] = colors[o * 2] | colors[o * 2 + 1];
    }
    if (setv[o] > 0)
        colors[o] = setv[o];
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
    if (a <= L && b >= R)
    {
        setv[o] = 1 << c;
    }
    else
    {
        pushdown(o);
        int M = L + (R - L) / 2;
        if (a <= M)
            update(lc, L, M);
        else
            maintain(lc, L, M);
        if (b > M)
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
        _color |= setv[o];
        // printf("%d %d ", L, R);
        // printb(setv[o]);
        // printf("\n");
    }
    else if (a <= L && b >= R)
    {
        _color |= colors[o];
        // printf("%d %d ", L, R);
        // printb(colors[o]);
        // printf("\n");
    }
    else
    {
        int M = L + (R - L) / 2;
        if (a <= M)
            query(o * 2, L, M);
        if (b > M)
            query(o * 2 + 1, M + 1, R);
    }
}

int main()
{
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    while (scanf("%d%d%d", &l, &t, &o) == 3)
    {
        build();
        for (int i = 0; i < o; ++i)
        {
            char op[2];
            scanf("%s", op);
            if (op[0] == 'C')
            {
                scanf("%d%d%d", &a, &b, &c);
                if(a > b) swap(a, b); 
                update(1, 1, l);
            }
            else
            {
                scanf("%d%d", &a, &b);
                if(a > b) swap(a, b);
                _color = 0;
                query(1, 1, l);
                int cnt = 0;
                while (_color != 0)
                {
                    if (_color & 1)
                        cnt++;
                    _color >>= 1;
                }
                printf("%d\n", cnt);
            }
        }
    }
    return 0;
}