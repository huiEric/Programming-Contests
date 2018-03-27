#include <bits/stdc++.h>

using namespace std;

int n,m;
list<int> Q;

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	scanf("%d%d",&n,&m);
	int p,q;
	for(int i=1;i<=n;++i)
		Q.push_back(i);
	for(int i=0;i<m;++i) {
		scanf("%d%d",&p,&q);
		q=(q<0)?q:q+1;
		list<int>::iterator it1,it2;
		for(it1=Q.begin();it1!=Q.end();++it1) {
			if(*it1==p) {
				it2=it1;
				if(q>0) {
					for(int i=0;i<q;++i) {
						++it1;
					}
					Q.insert(it1,p);
				}
				else {
					for(int i=0;i<-q;++i) {
						--it1;
					}
					Q.insert(it1,p);
				}			
				break;				
			}
		}
		Q.erase(it2);
	}
	printf("%d",*Q.begin());
	for(list<int>::iterator it=++Q.begin();it!=Q.end();++it)
		printf(" %d",*it);
	return 0;
}