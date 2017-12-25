#include"cstdio"
#include"cstring"
#include"vector"
using namespace std;
const int MAXN=1005;
int V;
vector<int> G[MAXN];
int par[MAXN];
void prep()
{
	for(int i=0;i<=MAXN;i++)
	{
		par[i]=i;
	}
}
int fnd(int x)
{
	if(par[x]==x)
		return x;
	return par[x]=fnd(par[x]);
}
void unite(int father,int son)
{
	par[son]=fnd(father);
}
int fa[MAXN],dep[MAXN];
void dfs(int u,int father,int d)
{
	fa[u]=father,dep[u]=d;
	for(int i=0;i<G[u].size();i++)
		 dfs(G[u][i],u,d+1);
}
int lca[MAXN];
int LCA(int u,int v)
{
	while(dep[u]>dep[v])	u=fa[u];
	while(dep[v]>dep[u])	v=fa[v];
	while(u!=v)
	{
		u=fa[u];
		v=fa[v];
	}
	return u;
}
int main()
{
	while(scanf("%d",&V)!=EOF)
	{
		for(int i=0;i<=V;i++)	G[i].clear();
		prep();
		memset(lca,0,sizeof(lca));
		memset(dep,0,sizeof(dep));
		memset(fa,0,sizeof(fa));
		for(int i=0;i<V;i++)
		{
			int u,t;
			scanf("%d:(%d)",&u,&t);
			while(t--)
			{
				int v;
				scanf("%d",&v);
				G[u].push_back(v);
				unite(u,v);
			}
		}
		int root=fnd(1);
		dfs(root,-1,0);
		int Q;
		scanf("%d",&Q);
		while(true)
		{
			char ch=getchar();
			if(ch=='(')
			{
				int u,v;
				scanf("%d %d",&u,&v);
				int a=LCA(u,v);
				lca[a]++;
				getchar();
				Q--;
			}
			if(Q==0)	break;
		}
		for(int i=0;i<=V;i++)
		{
			if(lca[i]!=0)	printf("%d:%d\n",i,lca[i]);
		}
	}
	return 0;
}