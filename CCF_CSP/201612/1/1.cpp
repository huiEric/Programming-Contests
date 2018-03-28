#include <bits/stdc++.h>

using namespace std;

const int mxn=1000+6;

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	int n;
	int a[mxn];
	scanf("%d",&n);
	for(int i=0;i<n;++i) {
		scanf("%d",&a[i]);
	}
	sort(a,a+n);
	for(int i=0;i<n;++i) {
		int l,r;
		l=r=i;
		while(l>=0 && a[l]==a[i])
			l--;
		while(r<n && a[r]==a[i])
			r++;
		if(l+1==n-r) {
			printf("%d\n", a[i]);
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}