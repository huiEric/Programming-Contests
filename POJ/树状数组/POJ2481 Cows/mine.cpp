#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <utility>

#define MAX_N 100100
#define MAX_S 100100
#define MAX_E 100100

using namespace std;

int N;
pair<int, int> range[MAX_N];
int idx[MAX_N]; //排序时仅对区间的下标进行移动
int bit[MAX_N]; //下标为range的end，值为1或0
int ans[MAX_N]; //存储最终的答案

bool comp(int i1, int i2)
{
	return (range[i1].first < range[i2].first) || 
		   (range[i1].first == range[i2].first && range[i1].second > range[i2].second);
}

int lowbit(int pos)
{
	return pos & (-pos);
}

void add(int pos, int w)
{
	for(int i = pos; i < MAX_E; i += lowbit(i))
		bit[i] += w;
}

int sum(int pos)
{
	int ans = 0;
	for(int i = pos; i > 0; i -= lowbit(i))
		ans += bit[i];
	return ans;
}

int sum(int from, int to)
{
	if(from == 0) return sum(to - 1);
	return sum(to - 1) - sum(from - 1);
}

int main(int argc, char const *argv[])
{
	while(1)
	{
		scanf("%d", &N);
		if(N == 0) break;
		memset(bit, 0, sizeof(bit)); //！！！初始化
		memset(ans, 0, sizeof(ans));
		for(int i = 0; i < N; ++i)
		{
			scanf("%d%d", &range[i].first, &range[i].second);
			idx[i] = i;
		}

		sort(idx, idx + N, comp);

		for(int i = 0; i < N; ++i)
		{
			int j = idx[i]; //按range的start从小到大遍历
			int end = range[j].second;
			int nright = sum(end, MAX_E);
			int k = i;
			while(k >= 0 && range[idx[i]] == range[idx[k]]) k--;
			ans[j] = nright - (i - k - 1);
			add(end, 1);
		}

		for(int i = 0; i < N; ++i)
		{
			if(i == N - 1) printf("%d\n", ans[i]);
			else printf("%d ", ans[i]);
		}
	}
	return 0;
}