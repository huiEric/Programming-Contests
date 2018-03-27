#include <bits/stdc++.h>

using namespace std;

const int mxn = 1000;

int n, d, x[mxn];

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
    int a;
    memset(x, 0, sizeof(x));
    scanf("%d%d", &n, &d);
    for(int i = 0; i < n; ++i) {
        scanf("%d", &a);
        x[a]++;
    }
    
    int ans = 0;
    for(int i = 1; i <= 100; ++i) {
        int s = 0;
        for(int j = i; j <= i + d; ++j)
            s += x[j];
        ans = max(ans, s);
    }
    printf("%d\n", n - ans);
    
    return 0;
}