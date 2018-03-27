#include <stdio.h>
#include <iostream>
#include <cstring>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

const int mxn=100+6;
const int mxm=100+6;

int n,m,t;
struct Rule
{
	char pattern[128];
	char name[128];
}r[mxn];
char urls[mxm][128];
char params[mxm][128];

void match_int(char *url,int &p_url,bool &matched) {
	int i=0;
	while(url[p_url]=='0')
		p_url++;
	while(p_url<strlen(url)) {
		if(url[p_url]=='/') {
			params[t][i]='\0';
			t++;
			return;
		}
		if(!isdigit(url[p_url])) {
			matched=false;
			return;
		}
		params[t][i]=url[p_url];
		i++;
		p_url++;
	}
	params[t][i]='\0';
	t++;
}

void match_str(char *url,int &p_url,bool &matched) {
	int i=0;
	while(p_url<strlen(url)) {
		if(url[p_url]=='/') {
			params[t][i]='\0';
			t++;
			return;
		}
		if(!(isdigit(url[p_url]) || ('A'<=url[p_url] && url[p_url]<='Z') || ('a'<=url[p_url] && url[p_url]<='z') || url[p_url]=='-' || url[p_url]=='_' || url[p_url]=='.')) {
			matched=false;
			return;
		}
		params[t][i]=url[p_url];
		i++;
		p_url++;
	}
	params[t][i]='\0';
	t++;
}

void match_path(char *url,int &p_url,bool &matched) {
	int i=0;
	while(p_url<strlen(url)) {
		if(!(isdigit(url[p_url]) || ('A'<=url[p_url] && url[p_url]<='Z') || ('a'<=url[p_url] && url[p_url]<='z') || url[p_url]=='-' || url[p_url]=='_' || url[p_url]=='.' || url[p_url]=='/')) {
			matched=false;
			return;
		}
		params[t][i]=url[p_url];
		i++;
		p_url++;
	}
	params[t][i]='\0';
	t++;
}

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	bool matched;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%s%s",r[i].pattern,r[i].name);
	for(int i=1;i<=m;++i)
		scanf("%s",urls[i]);
	for(int i=1;i<=m;++i) {		
		t=0;		
		for(int j=1;j<=n;++j) {
			int p_url=0;
			int p_pat=0;
			matched=true;
			p_pat++;
			p_url++;
			while(p_pat<strlen(r[j].pattern)) {				
				// printf("%c %c\n", r[j].pattern[p_pat],urls[i][p_url]);
				if(r[j].pattern[p_pat]=='<' && r[j].pattern[p_pat+1]=='i') {
					match_int(urls[i],p_url,matched);
					while(r[j].pattern[p_pat]!='/' && r[j].pattern[p_pat]!='\0')
						p_pat++;
				}
				else if(r[j].pattern[p_pat]=='<' && r[j].pattern[p_pat+1]=='s') {
					match_str(urls[i],p_url,matched);
					while(r[j].pattern[p_pat]!='/' && r[j].pattern[p_pat]!='\0')
						p_pat++;
				}
				else if(r[j].pattern[p_pat]=='<' && r[j].pattern[p_pat+1]=='p') {
					match_path(urls[i],p_url,matched);
					while(r[j].pattern[p_pat]!='\0')
						p_pat++;
				}
				else {
					if(r[j].pattern[p_pat]!=urls[i][p_url])
						matched=false;
					p_pat++;
					p_url++;
				}
				if((p_pat<strlen(r[j].pattern) && p_url>=strlen(urls[i])) || (p_pat>=strlen(r[j].pattern) && p_url<strlen(urls[i]))) {
					matched=false;
				}
				if(!matched) {
					t=0;
					break;
				}
			}
			if(matched) {
				printf("%s", r[j].name);
				for(int k=0;k<t;++k) {
					printf(" %s", params[k]);
				}
				printf("\n");
				break;
			}
		}
		if(!matched)
			printf("404\n");
	}
	return 0;
}