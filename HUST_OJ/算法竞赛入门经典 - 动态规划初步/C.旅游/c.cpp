#include <bits/stdc++.h>

using namespace std;

const int mxn = 1e3;
const int inf = 0x3f3f3f3f;

int n;
double x[mxn], y[mxn];
double f[mxn][mxn];

inline double dist(int i, int j) {
    return sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
}

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d", &n) == 1) {
        for(int i = 1; i <= n; ++i)
            scanf("%lf%lf", &x[i], &y[i]);
        memset(f, inf, sizeof(f));
        for(int i = 1; i < n - 1; ++i)
            f[n - 1][i] = dist(n - 1, n) + dist(i, n); //已经走到n-1，两个人都走到终点即可
        for(int i = n - 2; i >= 1; --i)
            for (int j = 1; j < i; ++j)                                      //x<max(i,j)都被走过
                f[i][j] = min(f[i+1][j]+dist(i,i+1), f[i+1][i]+dist(j,i+1)); //i>j,第一个人或第二个人走到i+1
        double ans = f[2][1] + dist(2, 1); // 其中一个人走到第二个点
        printf("%.2lf\n", ans);
    }
    return 0;
}