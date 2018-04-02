#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int mxn=5000+6;

struct Sell
{
	double p;
	ll s;
}sell[mxn],ts[mxn],buy[mxn];

bool comp(Sell&s1,Sell&s2) {
	return s1.p<s2.p;
}

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	int t=1;
	char record[mxn][30];
	while(1) {		
		if(fgets(record[t],sizeof(record[t]),stdin)==0)
			break;
		// printf("%s\n", record[t]);
		if(record[t][0]=='c') {
			char op[10];
			int line;
			sscanf(record[t],"%s%d",op,&line);
			record[line][0]='\0';
			record[t][0]='\0';
		}
		t++;
	}
	int pb,ps;
	pb=ps=0;
	for(int i=1;i<t;++i) {
		if(record[i][0]=='\0')
			continue;
		char op[10];
		double p;
		ll s;
		// printf("%s\n", record[i]);
		sscanf(record[i],"%s%lf%lld",op,&p,&s);
		// printf("%s\n", op);
		if(op[0]=='b') {			
			buy[pb].p=p;
			buy[pb].s=s;
			pb++;
		}
		else if(op[0]=='s') {
			// printf("%lf\n", p);
			sell[ps].p=p;
			sell[ps].s=s;
			ps++;
		}
	}
	sort(sell,sell+ps,comp);
	sort(buy,buy+pb,comp);
	double price,maxPrice;
	ll num,maxNum;
	price=maxPrice=0;
	num=maxNum=0;
	for(int i=0;i<ps;++i) {
		price=sell[i].p;		
		// for(int j=0;j<ps;++j)
		// 	ts[j]=sell[j];
		// for(int j=0;j<pb;++j) {
		// 	if(buy[j].p<price)
		// 		continue;
		// 	int p=0;
		// 	while(p<ps && ts[p].p>buy[j].p && ts[p].s)
		// 		p++;
		// 	ll need=buy[j].s;
		// 	ll bought=0;
		// 	while(p<ps && bought<need) {
		// 		if(ts[p].s>=buy[j].s) {
		// 			ts[p].s-=buy[j].s;
		// 			bought=need;
		// 		}
		// 		else {				
		// 			bought+=ts[p].s;
		// 			ts[p].s=0;
		// 			p++;
		// 		}
		// 	}
		// 	num+=bought;
		// }
		ll num_buy=0;
		for(int j=pb-1;j>=0;--j) {
			if(buy[j].p<price)
				break;
			num_buy+=buy[j].s;
		}
		ll num_sell=0;
		for(int j=0;j<ps;++j) {
			if(sell[j].p>price)
				break;
			num_sell+=sell[j].s;
		}
		num=min(num_sell,num_buy);
		if(num>maxNum || (num==maxNum && price>maxPrice)) {
			maxNum=num;
			maxPrice=price;
		}
	}
	printf("%.2lf %lld\n", maxPrice,maxNum);
	return 0;	
}