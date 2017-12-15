#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 2000

using namespace std;

int n, m;
int p[MAX_N], ranks[MAX_N], r[MAX_N];

void makeSets()
{
	for (int i = 0; i < n; ++i)
	{
		p[i] = i;
		ranks[i] = 0;
		r[i] = 0;
	}
}

int find(int x)
{
	if(p[x] != x)
	{
		int t = p[x];
		p[x] = find(p[x]);
		r[x] = (r[x] + r[t]) % 3;
	}
	return p[x];
}

void Union(int x, int y, int res)
{
	//x对y ： res
	int xp = find(x);
	int yp = find(y);
	if(ranks[xp] < ranks[yp])
	{
		p[xp] = yp;
		r[xp] = (3 - r[x] + res + r[y]) % 3;
	}
	else
	{
		p[yp] = xp;
		r[yp] = (3 - r[y] + (3 - res) + r[x]) % 3;
		if(ranks[xp] == ranks[yp]) ranks[xp]++;
	}
}

int main(int argc, char const *argv[])
{
	char str[4];
	FILE *in, *out;
	in = fopen("in.txt", "r");
	out = fopen("out-mine.txt", "w");
	while(~fscanf(in, "%d%d", &n, &m))
	{
		if(n == 1) 
		{
			printf("Player 0 can be determined to be the judge after 0 lines\n");
			return 0;
		}
		makeSets();
		bool flag = false, impossible = false;
		int cand1, cand2, judge = -1, line;
		for(int i = 0; i < m; ++i)
		{
			int x, y, res;
			char s;
			fscanf(in, "%d%c%d", &x, &s, &y);
			//printf("%d %d\n", x, y);
			if(impossible) continue;
			if(s == '=') res = 0;
			else if(s == '<') res = 1;
			else res = 2;
			if(find(x) == find(y))
			{			
				if((res == 0 && r[x] != r[y]) || (res == 1 && (r[y] + 1) % 3 != r[x]) || (res == 2 && (r[x] + 1) % 3 != r[y]))
				{				
					if(!flag)
					{
						cand1 = x; 
						cand2 = y;
						flag = true;
					}
					//printf("%d %d\n", cand1, cand2);
					//printf("%d %d\n", x, y);
					if((x == cand1 && y == cand2) || (x == cand2 && y == cand1)) continue;
					else if(x == cand1 || x == cand2)
					{
						if(judge == -1)
						{
							judge = x;
							line = i + 1;
						}
					}
					else if(y == cand1 || y == cand2)
					{
						if(judge == -1)
						{
							judge = y;
							line = i + 1;
						}
					}
					else
					{
						impossible = true;
						//break;
					}
				}
			}
			else Union(x, y, res);
		}
		if(impossible) fprintf(out, "Impossible\n");
		else if(judge == -1) fprintf(out, "Can not determine\n");
		else fprintf(out, "Player %d can be determined to be the judge after %d lines\n", judge, line);
	}
	fclose(in);
	fclose(out);
	return 0;
}