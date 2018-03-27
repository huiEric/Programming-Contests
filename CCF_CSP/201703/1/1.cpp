#include <bits/stdc++.h>

using namespace std;

const int mxn=1000+6;

int n,k;
int a[mxn];

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;++i)
		scanf("%d",&a[i]);
	int num=0,get=0;
	for(int i=0;i<n;++i) {
		get+=a[i];
		if(get>=k) {
			get=0;
			num++;
		}
	}
	if(get>0)
		num++;
	printf("%d\n",num);
	return 0;
}