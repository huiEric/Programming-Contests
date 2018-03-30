#include <bits/stdc++.h>

using namespace std;

const int mxn=30+6;
const int mxm=30+6;

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	int n,m;
	int a[mxn][mxm];
	bool kept[mxn][mxm];
	memset(kept,true,sizeof(kept));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			scanf("%d",&a[i][j]);
		}
	}
	int counter,color;
	for(int i=1;i<=n;++i) {
		color=a[i][1];
		counter=1;
		for(int j=2;j<=m;) {
			while(a[i][j]==color) {
				counter++;
				j++;	
			}
			if(counter>=3) {
				int k=j-1;
				while(counter) {
					kept[i][k]=false;
					counter--;
					k--;
				}
			}
			color=a[i][j];
			counter=0;
		}
	}
	for(int i=1;i<=m;++i) {
		color=a[1][i];
		counter=1;
		for(int j=2;j<=n;) {
			while(a[j][i]==color) {
				counter++;
				j++;	
			}
			if(counter>=3) {
				int k=j-1;
				while(counter) {
					kept[k][i]=false;
					counter--;
					k--;
				}
			}
			color=a[j][i];
			counter=0;
		}
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			a[i][j]=kept[i][j]?a[i][j]:0;
	for(int i=1;i<=n;++i) {
		printf("%d", a[i][1]);
		for(int j=2;j<=m;++j)
			printf(" %d", a[i][j]);
		printf("\n");
	}
	return 0;
}