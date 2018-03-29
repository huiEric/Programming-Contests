#include <bits/stdc++.h>

using namespace std;

int G[21][11];
int grid[4][4];

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	for(int i=1;i<=15;++i)
		for(int j=1;j<=10;++j) 
			scanf("%d",&G[i][j]);
	memset(G[16],1,sizeof(G[16]));
	for(int i=0;i<4;++i)
		for(int j=0;j<4;++j)
			scanf("%d",&grid[i][j]);
	int col;
	scanf("%d",&col);
	int line=5;
	while(line<20) {
		for(int i=0;i<4;++i)
			for(int j=0;j<4;++j)
				if(G[line-i][col+j] && grid[3-i][j]) {
					for(int k=0;k<4;++k)
						for(int l=0;l<4;++l)
							G[line-k-1][col+l]|=grid[3-k][l];
					for(int k=1;k<=15;++k) {
						printf("%d", G[k][1]);
						for(int l=2;l<=10;++l)
							printf(" %d",G[k][l]);
						printf("\n");
					}
					return 0;					
				}
		line++;
	}	
}