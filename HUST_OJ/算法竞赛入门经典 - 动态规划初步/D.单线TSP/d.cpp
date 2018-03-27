#include <bits/stdc++.h>
#define min3(a, b, c) (min(a, min(b, c)))

using namespace std;
using ll = long long;

const int mxn = 10 + 6;
const int mxm = 100 + 6;
const int inf = 0x3f3f3f3f;

int n, m, t;
ll mat[mxn][mxm];
ll f[mxm][mxn];
int nexti[mxm][mxn];

int main()
{
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif    
    while (scanf("%d%d", &n, &m) == 2)
    {
        int first;
        ll ans = inf;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                scanf("%lld", &mat[i][j]);
        for (int i = 1; i <= n; ++i)
            f[m][i] = mat[i][m];
        for (int i = m - 1; i >= 1; --i)
            for (int j = 1; j <= n; ++j)
            {
                int rows[3] = {j - 1, j, j + 1};
                if (j == 1)
                    rows[0] = n;
                if (j == n)
                    rows[2] = 1;
                sort(rows, rows + 3);
                f[i][j] = inf;
                for (int k = 0; k < 3; ++k)
                {
                    int v = f[i + 1][rows[k]] + mat[j][i];
                    if (v < f[i][j])
                    {
                        f[i][j] = v;
                        nexti[i][j] = rows[k];
                    }
                }
                if (i == 1 && f[i][j] < ans)
                {
                    ans = f[i][j];
                    first = j;
                }
            }
        printf("%d", first);
        for (int i = nexti[1][first], j = 2; j <= m; i = nexti[j][i], ++j)
            printf(" %d", i);
        printf("\n%lld\n", ans);
    }
    return 0;
}