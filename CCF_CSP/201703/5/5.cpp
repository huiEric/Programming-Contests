#include <bits/stdc++.h>
#define Crow(s,t) (x[(n-1)*m+((s)-2)*(m-1)+(t)])
#define Ccol(s,t) (x[((s)-1)*m+(t)])
#define Pos(i,j) (((i)-1)*m+(j))

using namespace std;
typedef long long ll;

const int mxn=1000+6;
const int mxm=1000+6;
const int mxx=1e9+6;
const ll inf=numeric_limits<ll>::max();

int n,m,t;
ll a,b,q,x0;
ll x[mxn*mxm];
struct Edge
{
	int u,v,next;
	ll c;
}E[mxn*mxm*2];
int r[mxn*mxm*2];
int head[mxn*mxm];
bool visited[mxn*mxm];

void addEdge(int u,int v,ll c) {
	//printf("%d %d %lld\n", u,v,c);
	E[t].u=u,E[t].v=v,E[t].c=c;
	E[t].next=head[u];
	head[u]=t++;
}

void build_graph() {
	memset(head,-1,sizeof(head));
	for(int i=1;i<=m;++i) {
		for(int j=1;j<n;++j) {
			addEdge(Pos(j,i),Pos(j+1,i),Ccol(j,i));
			r[t-1]=t;
			addEdge(Pos(j+1,i),Pos(j,i),inf);
			r[t-1]=t-2;
		}
	}
	for(int i=2;i<n;++i) {
		for(int j=1;j<m;++j) {
			addEdge(Pos(i,j),Pos(i,j+1),Crow(i,j));
			r[t-1]=t;
			addEdge(Pos(i,j+1),Pos(i,j),Crow(i,j));
			r[t-1]=t-2;
		}
	}
	for(int i=1;i<=m;++i) {
		addEdge(0,Pos(1,i),inf);
		r[t-1]=t;
		addEdge(Pos(1,i),0,0);
		r[t-1]=t-2;
		addEdge(Pos(n,i),n*m+1,inf);
		r[t-1]=t;
		addEdge(n*m+1,Pos(n,i),0);
		r[t-1]=t-2;
	}
}

ll dfs(int u,int t,ll f) {
	if(u==t)
		return f;
	visited[u]=true;
	for(int i=head[u];i!=-1;i=E[i].next) {
		int v=E[i].v;
		ll &c=E[i].c;
		// printf("%d %d %lld\n", u,v,c);
		if(!visited[v] && c>0) {			
			ll d=dfs(v,t,min(f,c));
			if(d>0) {
				c-=d;
				E[r[i]].c+=d;
				return d;
			}
		}
	}
	return 0;
}

ll max_flow() {
	ll flow=0;
	while(1) {
		memset(visited,false,sizeof(visited));
		ll f=dfs(0,n*m+1,inf);
		if(f==0)
			return flow;
		flow+=f;
	}
}

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	scanf("%d%d%lld%lld%lld%lld",&n,&m,&a,&b,&q,&x0);
	x[0]=x0;
	for(int i=1;i<=(n-1)*m+(n-2)*(m-1);++i) 
		x[i]=(a*x[i-1]+b)%q;
	build_graph();
	printf("%lld\n", max_flow());
	return 0;
}