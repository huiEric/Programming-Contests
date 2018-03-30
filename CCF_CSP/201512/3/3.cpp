#include <bits/stdc++.h>

using namespace std;

const int mxn=100+6;
const int mxm=100+6;

char pic[mxn][mxm];
int m,n,q;

void fill(int x,int y,char c) {
	pic[x][y]=c;
	//向上扩展
	if(x+1<n && pic[x+1][y]!='-' && pic[x+1][y]!='|' && pic[x+1][y]!='+' && pic[x+1][y]!=c)
		fill(x+1,y,c);
	//向下扩展
	if(x-1>=0 && pic[x-1][y]!='-' && pic[x-1][y]!='|' && pic[x-1][y]!='+' && pic[x-1][y]!=c)
		fill(x-1,y,c);
	//向右扩展
	if(y+1<m && pic[x][y+1]!='-' && pic[x][y+1]!='|' && pic[x][y+1]!='+' && pic[x][y+1]!=c)
		fill(x,y+1,c);
	//向左扩展
	if(y-1>=0 && pic[x][y-1]!='-' && pic[x][y-1]!='|' && pic[x][y-1]!='+' && pic[x][y-1]!=c)
		fill(x,y-1,c);
}

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif	
	memset(pic,'.',sizeof(pic));	
	scanf("%d%d%d",&m,&n,&q);
	for(int i=0;i<q;++i) {
		int op;
		scanf("%d",&op);
		// printf("%d\n", op);
		if(op) {
			int x,y;
			char c;
			scanf("%d %d %c",&x,&y,&c);
			fill(y,x,c);
		}
		else {
			int x1,y1,x2,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			// printf("%d %d %d %d\n", x1,x2,y1,y2);
			if(x1==x2) {
				for(int j=min(y1,y2);j<=max(y1,y2);++j) {
					pic[j][x1]=pic[j][x1]=='-'?'+':'|';
				}
			}
			else {
				for(int j=min(x1,x2);j<=max(x1,x2);++j) {
					pic[y1][j]=pic[y1][j]=='|'?'+':'-';
				}
			}
		}
	}
	for(int i=n-1;i>=0;--i) {		
		for(int j=0;j<m;++j)
			putchar(pic[i][j]);
		printf("\n");
	}
	return 0;
}