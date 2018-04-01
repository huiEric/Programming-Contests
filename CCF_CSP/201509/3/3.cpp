#include <bits/stdc++.h>

using namespace std;

const int mxm=100+6;
const int mxn=100+6;

struct Varible
{
	char name[20];
	char val[128];
}var[mxn];
char temp[mxm][128];
int n,m;

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	scanf("%d%d\n",&m,&n);
	for(int i=0;i<m;++i) {
		fgets(temp[i],sizeof(temp),stdin);
	}
	for(int i=0;i<n;++i) {
		scanf("%s ",var[i].name);
		fgets(var[i].val,sizeof(var[i].val),stdin);
		// printf("%s", var[i].val);
	}		
	for(int i=0;i<m;++i) {
		int p=0;
		while(p<strlen(temp[i])) {
			if(temp[i][p]=='{' && temp[i][p+1]=='{' && temp[i][p+2]==' ') {
				p+=3;
				for(int j=0;j<n;++j) {
					if(strncmp(temp[i]+p,var[j].name,strlen(var[j].name))==0) {
						char v[100];
						int ns=var[j].val[strlen(var[j].val)-1]=='\n'?strlen(var[j].val)-3:strlen(var[j].val)-2;
						strncpy(v,var[j].val+1,ns);
						v[ns]='\0';
						printf("%s", v);					
						break;
					}
				}
				while(temp[i][p]!=' ')
					p++;
				p+=3;
			}
			else {
				putchar(temp[i][p]);
				p++;
			}
		}
	}
	return 0;
}