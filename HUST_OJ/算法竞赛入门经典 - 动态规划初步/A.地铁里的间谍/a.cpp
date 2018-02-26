#include <bits/stdc++.h>

using namespace std;

const int mxn = 60;
const int mxt = 3000;
const int mxm = 300;
const int inf = 0x3f3f3f3f;

int N, T, m1, m2;
int t[mxn], d[mxm], e[mxm];
bool has_train[mxt][mxn][2];
int f[mxt][mxn];

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
    int kase = 0;
    while(1) {
        scanf("%d", &N);
        if(N == 0) break;
        scanf("%d", &T);
        for (int i = 1; i <= N - 1; ++i)
            scanf("%d", &t[i]);

        memset(has_train, false, sizeof(has_train));
        scanf("%d", &m1);
        for (int i = 1; i <= m1; ++i)
        {
            scanf("%d", &d[i]);
            int temp = d[i];
            has_train[temp][1][0] = true;
            for (int j = 1; j <= N - 1; ++j)
            {
                temp += t[j];
                has_train[temp][j + 1][0] = true;
            }
        }
        scanf("%d", &m2);
        for (int i = 1; i <= m2; ++i)
        {
            scanf("%d", &e[i]);
            int temp = e[i];
            has_train[temp][N][1] = true;
            for (int j = N - 1; j >= 1; --j)
            {
                temp += t[j];
                has_train[temp][j][1] = true;
            }
        }

        memset(f, inf, sizeof(f));
        for (int i = 1; i <= N - 1; ++i)
            f[T][i] = inf;
        f[T][N] = 0;
        for (int i = T - 1; i >= 0; --i)
            for (int j = 1; j <= N; ++j)
            {
                f[i][j] = min(f[i][j], f[i + 1][j] + 1); // 等待1个单位时间
                if (j < N && has_train[i][j][0] && i + t[j] <= T)
                    f[i][j] = min(f[i][j], f[i + t[j]][j + 1]); // 右
                if (j > 1 && has_train[i][j][1] && i + t[j - 1] <= T)
                    f[i][j] = min(f[i][j], f[i + t[j - 1]][j - 1]); // 左
            }

        printf("Case Number %d: ", ++kase);
        if (f[0][1] >= inf)
            printf("impossible\n");
        else
            printf("%d\n", f[0][1]);
    }

    return 0;
}