#include <bits/stdc++.h>

using namespace std;

struct Privi
{
	char name[33];
	int level;
};

struct Role
{
	char name[33];
	int num_pri;
	Privi pri[100];
} role[100];

struct User
{
	char name[33];
	int num_pri;
	Privi pri[100];
}user[100];

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
#endif
	int p,r,u,q;
	scanf("%d", &p);
	getchar();
	// printf("%d\n", p);
	char category[33];
	for(int i=0;i<p;++i) {
		fgets(category, sizeof(category), stdin);
		// printf("%s\n", category);
	}
	scanf("%d",&r);
	// printf("%d\n", r);
	for(int i=0;i<r;++i) {
		scanf("%s",role[i].name);
		int num;
		scanf("%d",&num);
		for(int j=0;j<num;++j) {
			char pr[33];
			scanf("%s",pr);
			char *pt=strchr(pr,':');
			int ns=pt?pt-pr:strlen(pr);
			bool existed=false;
			for(int k=0;k<role[i].num_pri;++k) {
				if(strncmp(pr,role[i].pri[k].name,ns)==0) {
					existed=true;
					if(pt)
						role[i].pri[k].level=max(role[i].pri[k].level,*(pt+1)-'0');
					break;
				}
			}
			if(!existed) {
				int t=role[i].num_pri++;
				strncpy(role[i].pri[t].name,pr,ns);
				if(pt)
					role[i].pri[t].level=*(pt+1)-'0';
				else
					role[i].pri[t].level=-1;
			}
		}
	}
	scanf("%d",&u);
	// printf("%d\n", u);
	for(int i=0;i<u;++i) {
		User &_user=user[i];
		scanf("%s",_user.name);
		int num;
		scanf("%d",&num);
		for(int j=0;j<num;++j) {
			char pu[33];
			scanf("%s",pu);
			Role *pr;
			for(int k=0;k<r;++k) {
				if(strcmp(pu,role[k].name)==0) {
					pr=&role[k];
					break;
				}
			}			
			for(int k=0;k<pr->num_pri;++k) {
				bool existed=false;
				for(int l=0;l<_user.num_pri;++l) {
					if(strcmp(pr->pri[k].name,_user.pri[l].name)==0) {
						existed=true;
						_user.pri[l].level=max(_user.pri[l].level,pr->pri[k].level);
						break;
					}
				}
				if(!existed) {
					int t=_user.num_pri++;
					strcpy(_user.pri[t].name,pr->pri[k].name);
					_user.pri[t].level=pr->pri[k].level;
				}
			}
		}
	}
	scanf("%d",&q);
	// printf("%d\n", q);
	for(int i=0;i<q;++i) {
		User *pu=0;
		char u_name[33];
		scanf("%s",u_name);
		for(int j=0;j<u;++j) {
			if(strcmp(user[j].name,u_name)==0) {
				pu=&user[j];
				break;
			}
		}
		if(!pu) {
			printf("false\n");
			continue;
		}
		char p_name[33];
		scanf("%s",p_name);
		char *pt=strchr(p_name,':');
		int ns=pt?pt-p_name:strlen(p_name);
		bool found=false;
		for(int j=0;j<pu->num_pri;++j) {
			if(strncmp(pu->pri[j].name,p_name,ns)==0) {
				found=true;
				if(pt) {
					if(pu->pri[j].level==*(pt+1)-'0') {
						printf("true\n");
					}
					else {
						printf("false\n");
					}					
				}
				else {
					if(pu->pri[j].level==-1)
						printf("true\n");
					else
						printf("%d\n", pu->pri[j].level);
				}
				break;
			}
		}
		if(!found)
			printf("false\n");
	}
	return 0;
}