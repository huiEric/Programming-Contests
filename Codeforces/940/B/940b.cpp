#include <bits/stdc++.h>

using namespace std;
using ll = long long;
ll n, k, a, b;

ll dp(ll x) {
    if(x < k || k == 1) return (x - 1) * a;
    if(x % k) return dp(x - x % k) + x % k * a;
    return dp(x / k) + min(b, (x - x / k) * a);
}

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
    scanf("%lld%lld%lld%lld", &n, &k, &a, &b);
    printf("%lld\n", dp(n));
    return 0;
}