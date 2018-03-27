#include <stdio.h>
#include <iostream>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

const int mxn=100+6;

int n,l,t;
int a[mxn];
map<int,int> v; //1,-1,表方向
int ordered[mxn];
map<int,int> final;

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	scanf("%d%d%d",&n,&l,&t);
	for(int i=0;i<mxn;++i)
		v[i]=1;
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		ordered[i]=a[i];
		final[a[i]]=a[i];	
		v[a[i]]=1;
	}
	sort(ordered+1,ordered+1+n);
	for(int i=1;i<=t;++i) {
		for(int j=1;j<=n;++j) {
			final[ordered[j]]+=v[ordered[j]]*1;
			if(final[ordered[j]]==0)
				v[ordered[j]]=1;
			if(final[ordered[j]]==l)
				v[ordered[j]]=-1;		
		}
		for(int j=1;j<n;++j) {
			if(final[ordered[j]]==final[ordered[j+1]]) {
				v[ordered[j]]=-v[ordered[j]];
				v[ordered[j+1]]=-v[ordered[j+1]];
			}
		}
	}
	printf("%d",final[a[1]]);
	for(int i=2;i<=n;++i)
		printf(" %d",final[a[i]]);
	return 0;
}