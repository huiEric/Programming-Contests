#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<list>
#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<vector>

using namespace std;

/**************************************************************/
#define MAX_N 505
const int INF = 0x3f3f3f3f;
int parent[MAX_N * 3];

struct node
{
    int a, b;
    char s;
} t[MAX_N];

inline void init(int n)
{
    for(int i = 0 ; i < n * 3 + 1 ; i++)
    {
        parent[i] = i;
    }
}

int find(int a)
{
    if(parent[a] != a)
    {
        parent[a] = find(parent[a]);
    }
    return parent[a];
}

void unite(int a, int b)
{
    int fa = find(a);
    int fb = find(b);
    if(fa != fb)
    {
        parent[fb] = fa;
    }
    return;
}

bool same(int a, int b)
{
    return find(a) == find(b);
}

int main()
{
    int n, m;
    FILE *in, *out;
    in = fopen("in.txt", "r");
    out = fopen("out-AC.txt", "w");
    while(~fscanf(in, "%d%d", &n , &m))
    {
        init(n);
        for(int i = 0 ; i < m ; i++)
        {
            fscanf(in, "%d%c%d", &t[i].a, &t[i].s, &t[i].b);
            //cout << t[i].a << " " << t[i].b << endl;
        }
        int cnt = 0;
        int num = 0;

        int player = 0;
        for(int k = 0 ; k < n ; k++)
        {
            int flag = 0;
            init(n);
            for(int i = 0 ; i < m ; i++)
            {
                if(t[i].a == k || t[i].b == k) continue;
                int a = t[i].a;
                int b = t[i].b;
                if(t[i].s == '=')
                {
                    if(same(a, b + n) || same(a, b + 2 * n))
                    {
                        flag = 1;
//                        cout<<1<<endl;
                        num = max(num, i);
                        break;
                    }
                    unite(a, b);
                    unite(a + n , b + n);
                    unite(a + 2 * n, b + 2 * n);
                }
                else if(t[i].s == '<')//
                {
                    if(same(a, b) || same(a, b + 2 * n))
                    {
                        flag = 1;
//                        cout<<2<<endl;
                        num = max(num, i);
                        break;
                    }
                    unite(a, b + n);
                    unite(a + n, b + 2 * n);
                    unite(a + 2 * n, b);
                }
                else
                {
                    if(same(a, b) || same(a, b + n))
                    {
                        flag = 1;
//                        cout<<3<<endl;
//                        cout<<"k"<<" "<<k<<endl;
                        num = max(num, i);
                        break;
                    }
                    unite(a, b + 2 * n);
                    unite(a + n, b);
                    unite(a + 2 * n, b + n);
                }
            }
            if(!flag)
            {
                cnt++;
                player = k;
            }
        }
        if(cnt == 1)
            fprintf(out, "Player %d can be determined to be the judge after %d lines\n", player, num + 1);
        else if(cnt > 1)
            fprintf(out,"Can not determine\n");
        else
            fprintf(out, "Impossible\n");
//        printf("%d\n", cnt);
    }
    fclose(in);
    fclose(out);
    return 0;
}