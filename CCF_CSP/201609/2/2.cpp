#include <bits/stdc++.h>

using namespace std;

struct Seat
{
	int left;
	bool s[5];
} seat[20];

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	int n;
	Seat temp={5,{0,0,0,0,0}};
	for(int i=0;i<20;++i)
		seat[i]=temp;
	scanf("%d",&n);
	for(int i=0;i<n;++i) {
		int p;
		scanf("%d",&p);
		for(int j=0;j<20;++j) {
			if(!p) break;
			if(seat[j].left>=p) {
				for(int k=0;k<5;++k) {
					if(!seat[j].s[k]) {
						seat[j].s[k]=true;
						p--;
						seat[j].left--;
						if(p) {
							printf("%d ", j*5+k+1);
						}
						else {
							printf("%d\n", j*5+k+1);
							break;
						}
					}
				}				
			}
		}
		if(p) {
			for(int j=0;j<20;++j) {
				if(!p) break;
				for(int k=0;k<5;++k) {
					if(!seat[j].s[k]) {
						seat[j].s[k]=true;
						p--;
						seat[j].left--;
						if(p) {
							printf("%d ", j*5+k+1);
						}
						else {
							printf("%d\n", j*5+k+1);
							break;
						}
					}
				}		
			}
		}
	}
	return 0;
}