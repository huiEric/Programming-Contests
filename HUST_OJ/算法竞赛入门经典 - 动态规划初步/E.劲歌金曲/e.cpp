#include <bits/stdc++.h>

using namespace std;

const int mxn = 50 + 6;
const int mxt = 180 * mxn + 678;

int kase, n, t;
int songs[mxn];
int f[mxt], pre[mxt];

int main()
{
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d", &kase);
    for (int i = 1; i <= kase; ++i)
    {
        int seconds = 0;
        memset(f, 0, sizeof(f));
        memset(pre, 0, sizeof(pre));
        scanf("%d%d", &n, &t);
        for (int j = 1; j <= n; ++j)
            scanf("%d", &songs[j]);
        sort(songs + 1, songs + 1 + n);
        for (int j = 1; j <= n; ++j)
        {
            for (int k = t; k > 0; --k)
                if (k > songs[j] && f[k - songs[j]] + 1 >= f[k])
                {
                    f[k] = f[k - songs[j]] + 1;
                    pre[k] = songs[j];
                }
        }
        for (int k = t; f[k] != 0; k -= pre[k])
            seconds += pre[k];
        printf("Case %d: %d %d\n", i, f[t] + 1, seconds + 678);
    }
    return 0;
}