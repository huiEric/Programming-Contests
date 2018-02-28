#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int mxn = 30 + 6;

int n;
bool G[3 * mxn][3 * mxn];
ll w[3 * mxn], f[3 * mxn];

void trans(ll &a, ll &b, int x)
{
    if (x % 3 == 0)
        a = w[x + 1], b = w[x + 2];
    else if (x % 3 == 1)
        a = w[x - 1], b = w[x + 1];
    else
        a = w[x - 2], b = w[x - 1];
}

ll dp(int i) {
    ll& ans = f[i];
    if(ans > 0) return ans;
    ans = w[i];
    for(int j = 0; j < 3 * n; ++j)
        if(G[i][j]) ans = max(ans, dp(j) + w[i]);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
    int kase = 0;
    while(1) {
        scanf("%d", &n);
        if(n == 0) break;
        ll x, y, z;
        for(int i = 0; i < n; ++i) {
            scanf("%lld%lld%lld", &x, &y, &z);
            w[3 * i] = x; w[3 * i + 1] = y; w[3 * i + 2] = z;            
        }
        memset(G, false, sizeof(G));
        for(int i = 0; i < 3 * n; ++i)
            for(int j = 0; j < 3 * n; ++j) {                
                ll a, b, c, d;
                trans(a, b, i);
                trans(c, d, j);
                if((a<c && b<d) || (a<d && b<c))
                    G[i][j] = true;
            }               
        memset(f, 0, sizeof(f));
        for(int i = 0; i < 3 * n; ++i) dp(i);
        ll maxh = 0;
        for(int i = 0; i < 3 * n; ++i) 
            maxh = max(maxh, f[i]);
        printf("Case %d: maximum height = %lld\n", ++kase, maxh);
    }
    return 0;
}