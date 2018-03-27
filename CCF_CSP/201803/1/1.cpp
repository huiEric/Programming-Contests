#include <stdio.h>
#include <iostream>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	int state;
	int center=0;
	int score=0;
	while(1) {
		scanf("%d",&state);
		if(!state)
			break;
		if(state==2) {
			center+=1;
			score+=2*center;
		}
		else {
			center=0;
			score+=1;
		}
	}
	printf("%d\n",score);
	return 0;
}