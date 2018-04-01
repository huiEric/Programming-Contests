#include <bits/stdc++.h>

using namespace std;

const int mxn=1000+6;
struct Num
{
	int x,f;
}num[mxn];

bool comp(Num&a,Num&b) {
	return (a.f>b.f) || (a.f==b.f && a.x<b.x);
}

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	int n;
	int a[mxn];
	int t=0;
	scanf("%d",&n);
	for(int i=0;i<n;++i) 
		scanf("%d",&a[i]);
	sort(a,a+n);
	for(int i=0;i<n;) {
		int x=a[i];
		num[t].x=x;
		num[t].f=0;
		while(a[i]==x) {
			num[t].f++;
			i++;
		}
		t++;
	}
	sort(num,num+t,comp);
	for(int i=0;i<t;++i)
		printf("%d %d\n", num[i].x,num[i].f);
	return 0;	
}