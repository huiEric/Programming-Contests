#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int mxn = 5e5 + 6;

int n, t = 0;
ll a[mxn], sum[mxn];

double binary_search(ll an) {
    a[t++] = an;
    sum[t] = sum[t - 1] + an; //sum[i]：前i个数的和
    auto f = [&](int i){ return an + sum[i] - a[i] * (i + 1); };
    int l = 0, r = t, mid;
    while(l < r) {
        mid = (l + r) / 2;  
        if(f(mid) > 0) l = mid + 1; // !!!必须+1，因为(1+0)/2=0，会导致死循环
        else r = mid;
    }
    l = f(l)>0 ? l+1 : l;
    return an - (an + sum[l]) / (l + 1.0);
}

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
    int type;
    ll an;
    double ans;
    sum[0] = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {        
        scanf("%d", &type);
        if(type == 1) {
            scanf("%lld", &an);
            ans = binary_search(an);
        }
        else
            printf("%.10lf\n", ans);
    }
    return 0;
}