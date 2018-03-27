#include <stdio.h>
#include <iostream>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

int T;
int pad[3][3];

void decide(int &res,bool &done) {			
	int who;
	for(int i=0;i<3;++i) {
		if(pad[i][0]==pad[i][1] && pad[i][0]==pad[i][2] && pad[i][0]!=0) {
			done=true;
			who=pad[i][0];
		}
	}
	for(int i=0;i<3;++i) {
		if(pad[0][i]==pad[1][i] && pad[0][i]==pad[2][i] && pad[0][i]!=0) {
			done=true;
			who=pad[0][i];
		}
	}
	if(pad[0][0]==pad[1][1] && pad[0][0]==pad[2][2] && pad[0][0]!=0) {
			done=true;
			who=pad[0][0];
		}
		if(pad[0][2]==pad[1][1] && pad[0][2]==pad[2][0] && pad[0][2]!=0) {
			done=true;
			who=pad[0][2];
		}
		int blank=0;
	for(int j=0;j<3;++j)
			for(int k=0;k<3;++k) {
				if(pad[j][k]==0)
					blank++;
			}			
			if(blank==9) {
				done=true;
				res=0;
				return;
			}
			if(who==1)
				res=blank+1;
			else
				res=-(blank+1);	
}

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	scanf("%d",&T);
	for(int i=0;i<T;++i) {
		for(int j=0;j<3;++j)
			for(int k=0;k<3;++k)
				scanf("%d",&pad[j][k]);
		int res;
		bool done=false;
		decide(res,done);
		if(done) {
			printf("%d\n", res);			
		}
		else {
			printf("0\n");
		}
		//printf("%d\n", res);
	}
	return 0;
}