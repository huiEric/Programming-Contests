#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int mxn=500+6;
const int mxm=1e5+6;
const int inf=0x3f3f3f3f;
int n,m,k;
struct Edge
{
    int u,v,t,c,next;
}E[mxm];
int head[mxn];
vector<int> paths[]

void addEdge(int u,int v,int t,int c) {
    E[k].u=u, E[k].v=v, E[k].t=t, E[k].c=c;
    E[k].next=head[u];
    head[u]=k++;
}



int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.txt","r",stdin);    
#endif
    scanf("%d%d",&n,&m);
    memset(head,-1,sizeof(head));
    int u,v,t,c;
    for(int i=0;i<m;++i) {
        scanf("%d%d%d%d",&t,&u,&v,&c);
        addEdge(u,v,t,c);
        addEdge(v,u,t,c);
    }
    
    return 0;
}