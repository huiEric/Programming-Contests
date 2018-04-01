#include <bits/stdc++.h>

using namespace std;

int month[]={31,28,31,30,31,30,31,31,30,31,30,31};

int day_of_a_1(int a,int y) {
	int days=0;
	for(int i=1850;i<y;++i)
		if((i%4==0 && i%100) || (i%400==0))
			days+=366;
		else 
			days+=365;
	for(int i=1;i<a;++i)
		days+=month[i-1];
	return 2+(days%7);
}

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	int a,b,c,y1,y2;
	scanf("%d%d%d%d%d",&a,&b,&c,&y1,&y2);
	for(int y=y1;y<=y2;++y) {
		if((y%4==0 && y%100) || (y%400==0))
			month[1]=29;
		else
			month[1]=28;
		int day=day_of_a_1(a,y);
		int date=1+(day<=c?c-day:c-day+7)+7*(b-1);
		if(date>month[a-1])
			printf("none\n");
		else {
			if(a<10 && date<10)
				printf("%d/0%d/0%d\n", y,a,date);
			else if(a<10)
				printf("%d/0%d/%d\n", y,a,date);
			else if(date<10)
				printf("%d/%d/0%d\n", y,a,date);
			else
				printf("%d/%d/%d\n", y,a,date);
		}
	}
	return 0;
}