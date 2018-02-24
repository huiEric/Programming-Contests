#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vi = vector<int>;

const int mxn = 100006;
const int mxk = 106;
const int MXL = 0x3f3f3f3f;

int n, k;
int l[mxk];
int r[mxk];
int f[mxk][mxn];

void minto(int &a, int b) { a = min(a, b); }

void trans(int *f, int *g, int right, int len) {
    //i为当前面烤的时间，f[i]为达到两面都烤了i时间这个状态所需要的最小翻面次数
    //0，不翻面，跟没有这个区间时是一样的
    for(int i = 0; i <= n; ++i) minto(f[i], g[i]);
    //用双端队列求i-len~i的最小
    deque<int> d;
    auto push = [&](int x){ while(d.size() && g[d.back()] >= g[x]) d.pop_back(); d.push_back(x); };
    auto pop = [&](int x){ if(d.front() == x) d.pop_front(); };
    auto top = [&](){ return d.front(); };
    //+1,+2
    for(int i = 0; i <= n; ++i) {
        push(i); 
        // 翻1次面，right - i为另一面烤的时间，也就是最终两面都要烤的时间
        // g[top()]为k=i-len~i的最少翻面次数，i-k即为当前面还需要继续烤的时间
        if(0 <= right - i && right - i <= n) minto(f[right - i], g[top()] + 1);
        // 翻2次面
        minto(f[i], g[top()] + 2);
        pop(i - len); // 删除队列中掉出范围的最小值
    }
}

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d%d", &n, &k);

    l[0] = r[0] = 0;
    for(int i = 1; i <= k; ++i) 
        scanf("%d%d", &l[i], &r[i]);

    for(int i = 0; i <= k; ++i)
        for(int j = 0; j <= n; ++j)
            f[i][j] = MXL;

    f[0][0] = 0;
    for(int i = 1; i <= k; ++i) 
        trans(f[i], f[i - 1], r[i], r[i] - l[i]);

    int ans = f[k][n];
    if(ans != MXL)
        printf("Full\n%d\n", ans);
    else
        printf("Hungry\n");
    
    return 0;
}