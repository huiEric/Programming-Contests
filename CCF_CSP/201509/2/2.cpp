#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	int year,num;
	int month[]={31,28,31,30,31,30,31,31,30,31,30,31};
	scanf("%d%d",&year,&num);
	if((year%4==0 && year%100) || year%400==0)
		month[1]=29;
	for(int i=0;i<12;++i) {
		if(num<=month[i]) {
			printf("%d\n%d\n", i+1,num);
			return 0;
		}
		num-=month[i];
	}
}