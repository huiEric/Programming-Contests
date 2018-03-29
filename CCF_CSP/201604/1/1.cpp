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
	int ans=0;
	for(int i=1;i<n-1;++i) {
		if(a[i-1]<a[i] && a[i]>a[i+1])
			ans++;
		if(a[i-1]>a[i] && a[i]<a[i+1])
			ans++;
	}
	printf("%d\n",ans);
	return 0;
}