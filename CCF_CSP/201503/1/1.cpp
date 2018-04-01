#include <bits/stdc++.h>

using namespace std;

const int mxn=1000+6;
const int mxm=1000+6;

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	int n,m;	
	short a[mxn][mxm];
	scanf("%d%d",&n,&m);	
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%hd",&a[i][j]);
	for(int j=m;j>=1;--j) {
		printf("%hd", a[1][j]);
		for(int i=2;i<=n;++i)
			printf(" %hd", a[i][j]);
		printf("\n");
	}
	return 0;
}