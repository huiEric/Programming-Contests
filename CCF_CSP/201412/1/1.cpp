#include <bits/stdc++.h>

using namespace std;

const int mxn=1000+6;

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	int n,j;
	int a[mxn];
	memset(a,0,sizeof(a));
	scanf("%d%d",&n,&j);
	printf("%d", ++a[j]);
	for(int i=2;i<=n;++i) {
		scanf("%d",&j);
		printf(" %d", ++a[j]);
	}
	printf("\n");
	return 0;
}