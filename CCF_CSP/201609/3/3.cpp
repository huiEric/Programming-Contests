#include <bits/stdc++.h>

using namespace std;

struct Follower {
    int attack,health;
};

list<Follower> follower[2];
int hero[2];

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.txt","r",stdin);
#endif
    int n,t=0;
    hero[0]=hero[1]=30;
    scanf("%d",&n);
    for(int i=0;i<n;++i) {
        char op[10];
        scanf("%s",op);
        if(op[0]=='s') {
            int pos,attack,health;
            scanf("%d%d%d",&pos,&attack,&health);
            list<Follower>::iterator it=follower[t].begin();
            for(int j=1;j<pos;++j) {
                ++it;
            }
            Follower temp={attack,health};
            follower[t].insert(it,temp);
        }
        else if(op[0]=='a') {
            int attacker,defender;
            scanf("%d%d",&attacker,&defender);
            list<Follower>::iterator it1,it2;
            it1=follower[t].begin();
            it2=follower[!t].begin();            
            for(int j=1;j<attacker;++j) {
                ++it1;
            }
            for(int j=1;j<defender;++j) {
                ++it2;
            }
            // printf("%d %d\n", it1->attack,it2->attack);
            if(defender) {
                it2->health-=it1->attack;
                it1->health-=it2->attack;
            }
            else {
                hero[!t]-=it1->attack;
            }
            if(it1!=follower[t].end() && it1->health<=0)
                follower[t].erase(it1);
            if(it2!=follower[!t].end() && it2->health<=0)
                follower[!t].erase(it2);
        }
        else {
            t=!t;
        }
    }
    
    printf("%d\n", hero[0]<=0?-1:(hero[1]<=0?1:0));
    int d=0;
    printf("%d\n", hero[d]);
    printf("%d", follower[d].size());
    for(list<Follower>::iterator it=follower[d].begin();it!=follower[d].end();++it) {
        printf(" %d", it->health);
    }
        
    d=!d;
    printf("\n%d\n", hero[d]);
    printf("%d", follower[d].size());
    for(list<Follower>::iterator it=follower[d].begin();it!=follower[d].end();++it)
        printf(" %d", it->health);
    return 0;
}