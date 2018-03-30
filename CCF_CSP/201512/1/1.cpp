#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	char num[15];
	int ans=0;
	scanf("%s",num);
	for(int i=0;i<(int)strlen(num);++i) 
		ans+=num[i]-'0';
	printf("%d\n", ans);
	return 0;
}