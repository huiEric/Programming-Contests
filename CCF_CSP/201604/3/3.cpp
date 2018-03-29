#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	int p;
	scanf("%d",&p);
	char cur_dir[1024];
	scanf("%s\n",cur_dir);
	deque<string> cur;
	for(int i=0;i<p;++i) {
		char path[1024];
		fgets(path,sizeof(path),stdin);
		if(path[strlen(path)-1]=='\n')
			path[strlen(path)-1]='\0';
		if(strlen(path)==0) {
			printf("%s\n",cur_dir);
			continue;
		}
		int p=0;
		if(path[0]=='/') { //绝对路径
			while(p<strlen(path)) {
				while(path[p]=='/')
					p++;
				if(path[p]=='\0')
					break;
				if(strncmp(path+p,"./",2)==0 || (strncmp(path+p,".",1)==0 && !path[p+1])) {
					p++;
				}
				else if(strncmp(path+p,"../",3)==0 || (strncmp(path+p,"..",2)==0 && !path[p+2])) {
					if(cur.size())
						cur.pop_back();
					p+=2;
				}
				else {
					char temp[1024];
					char *p1=strchr(path+p,'/');
					int ns=p1?p1-path-p:strlen(path)-p;
					strncpy(temp,path+p,ns);
					temp[ns]='\0';
					cur.push_back(string(temp));
					p+=ns;
					// printf("%s\n", temp);
					// return 0;
				}
			}
			cout << "/";
			while(cur.size()) {
				if(cur.size()>1)
					cout << cur.front() << "/";
				else 
					cout << cur.front();
				cur.pop_front();
			}
			cout << endl;
		}
		else { // 相对路径
			int p1=0;
			while(p1<strlen(cur_dir)) {
				p1++;
				char *pt=strchr(cur_dir+p1,'/');
				int ns=pt?pt-cur_dir-p1:strlen(cur_dir)-p1;
				char temp[1024];
				strncpy(temp,cur_dir+p1,ns);
				temp[ns]='\0';
				cur.push_back(string(temp));
				p1+=ns;
			}
			while(p<strlen(path)) {
				while(path[p]=='/')
					p++;
				if(path[p]=='\0')
					break;
				if(strncmp(path+p,"./",2)==0 || (strncmp(path+p,".",1)==0 && !path[p+1])) {
					p++;
				}
				else if(strncmp(path+p,"../",3)==0 || (strncmp(path+p,"..",2)==0 && !path[p+2])) {
					if(cur.size())
						cur.pop_back();
					p+=2;
				}
				else {
					char temp[1024];
					char *p1=strchr(path+p,'/');
					int ns=p1?p1-path-p:strlen(path)-p;
					strncpy(temp,path+p,ns);
					temp[ns]='\0';
					cur.push_back(string(temp));
					p+=ns;
				}
			}
			cout << "/";
			while(cur.size()) {
				if(cur.size()>1)
					cout << cur.front() << "/";
				else 
					cout << cur.front();
				cur.pop_front();
			}
			cout << endl;
		}		
	}
	return 0;
}