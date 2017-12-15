#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <algorithm>

#define MAX_N 20016
#define MAX_V 20016
#define MAX_X 20016

using namespace std;
typedef long long LL;

int N;
pair<int, int> cow[MAX_N]; //(v, x)
LL bit_n[MAX_N], bit_x[MAX_N]; //都以奶牛坐标为下标，分别对奶牛数量和坐标计算前缀和

int lowbit(int pos)
{
	return pos & (-pos);
}

void add(LL *bit, int pos, LL w)
{
	for(int i = pos; i <= MAX_X; i += lowbit(i))
		bit[i] += w;
}

LL sum(LL *bit, int pos)
{
	LL ans = 0;
	for(int i = pos; i > 0; i -= lowbit(i))
		ans += bit[i];
	return ans;
}

//重载函数sum返回a[start, end)
LL sum(LL *bit, int start, int end)
{
	return sum(bit, end - 1) - sum(bit, start - 1);
}

int main(int argc, char const *argv[])
{
	scanf("%d", &N);
	for(int i = 0; i < N; ++i)
	{
		scanf("%d%d", &cow[i].first, &cow[i].second);
	}

	sort(cow, cow + N);
	LL total = 0;

	for(int i = 0; i < N; ++i)
	{
		//v为当前最大权值
		int v = cow[i].first, x = cow[i].second;
		//x坐标左边奶牛数量和右边奶牛数量
		LL nleft = sum(bit_n, 1, x), nright = sum(bit_n, x + 1, MAX_X);
		//v与到剩下所有奶牛的距离之和相乘
		total += v * ((nleft * x - sum(bit_x, 1, x)) + (sum(bit_x, x + 1, MAX_X) - nright * x));
		add(bit_n, x, 1);
		add(bit_x, x, x);
	}
	//！！！ long long一定要用lld，否则会WA！！！
	printf("%lld\n", total);
	return 0;
}