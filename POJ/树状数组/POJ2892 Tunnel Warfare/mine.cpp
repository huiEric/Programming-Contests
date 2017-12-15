#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <set>
#include <stack>

#define MAX_N 50010
#define MAX_M 50010

using namespace std;

int n, m;
set<int> des_set;
stack<int> des_stack;
bool destroyed[MAX_N];

int main(int argc, char const *argv[])
{
	scanf("%d%d", &n, &m);
	memset(destroyed, false, sizeof(destroyed));
	des_set.insert(0);
	des_set.insert(n + 1);
	for(int i = 0; i < m; ++i)
	{
		char cmd[2];
		scanf("%s", cmd);
		if(cmd[0] == 'D')
		{
			int x;
			scanf("%d", &x);
			des_set.insert(x);
			des_stack.push(x);
			destroyed[x] = true;
		}
		else if(cmd[0] == 'Q')
		{
			int x;
			scanf("%d", &x);
			if(destroyed[x]) printf("0\n");
			else
			{
				//找到x后面第一个被破坏的村庄
				set<int>::iterator pSet = des_set.lower_bound(x);
				int next = *pSet;
				//前一个被破坏的村庄
				int pre = *(--pSet);
				printf("%d\n", next - pre - 1);
			}
		}
		else
		{
			int last = des_stack.top();
			des_set.erase(last);
			des_stack.pop();
			destroyed[last] = false;
		}
	}
	return 0;
}