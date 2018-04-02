#include <bits/stdc++.h>

using namespace std;

const int mxn=500+6;

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	int n;
	short a[mxn][mxn];
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			scanf("%hd",&a[i][j]);
	int i,j;
	i=j=1;
	int d=1;
	while(!(i==n && j==n)) {
		printf("%hd ", a[i][j]);
		if(d) {
			if(i==1 && j<n) {
				j++;
				d=!d;				
			}
			else if(j==n) {
				i++;
				d=!d;
			}
			else {
				i--;
				j++;
			}
		}
		else {
			if(j==1 && i<n) {
				i++;
				d=!d;
			}
			else if(i==n) {
				j++;
				d=!d;
			}
			else {
				i++;
				j--;
			}			
		}
	}
	printf("%hd\n",a[n][n]);
	return 0;
}