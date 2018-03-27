#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int mxn=1e5+6;
const int mxm=2e5+6;
const int inf=0x3f3f3f3f;
int n,m,t;
struct Edge
{
	int u,v,c,next;
}E[mxm];
int head[mxn];
int d[mxn];
deque<int> Q;

void addEdge(int u,int v, int c) {
	E[t].u=u, E[t].v=v, E[t].c=c;
	E[t].next=head[u];
	head[u]=t++;
}

void spfa(int s) {
	d[s]=0;
	Q.push_back(s);
	while(!Q.empty()) {
		int u=Q.front();
		Q.pop_front();
		for(int i=head[u];i!=-1;i=E[i].next) {
			int v=E[i].v;
			int c=E[i].c;
			if(d[v]>max(d[u],c)) {
				d[v]=max(d[u],c);
				Q.push_back(v);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);	
#endif
	scanf("%d%d",&n,&m);
	memset(head,-1,sizeof(head));
	int u,v,c;
	for(int i=0;i<m;++i) {
		scanf("%d%d%d",&u,&v,&c);
		addEdge(u,v,c);
		addEdge(v,u,c);
	}
	memset(d,inf,sizeof(d));
	spfa(1);
	printf("%d\n", d[n]);
	return 0;
}