#include <bits/stdc++.h>

using namespace std;

const int mxn = 1000 + 6;
const int inf = 0x3f3f3f3f;

int kase;
char s[mxn];
int f[mxn];
bool isPal[mxn][mxn];

int main()
{
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d", &kase);
    for (int i = 0; i < kase; ++i)
    {
        scanf("%s", s);
        memset(f, inf, sizeof(f));
        memset(isPal, false, sizeof(isPal));
        for (size_t j = 0; j < strlen(s); ++j)
        {
            size_t head, tail;
            head = tail = j;
            while (head >= 0 && tail < strlen(s) && s[head] == s[tail])
            {
                isPal[head][tail] = true;
                head--;
                tail++;
            }
            head = j;
            tail = j + 1;
            while (head >= 0 && tail < strlen(s) && s[head] == s[tail])
            {
                isPal[head][tail] = true;
                head--;
                tail++;
            }
        }
        f[0] = 1;
        for (size_t j = 1; j < strlen(s); ++j)
        {
            f[j] = isPal[0][j] ? 1 : inf;
            for (size_t k = 0; k < j; ++k)
            {
                if (isPal[k + 1][j] && f[k] + 1 < f[j])
                    f[j] = f[k] + 1;
            }
        }
        printf("%d\n", f[strlen(s) - 1]);
    }
}