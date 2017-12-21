#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>

#define MAX_N 100
#define MAX_M 100

using namespace std;

int n, m;
string json;
string query[MAX_M];
map<string, string> dict;

int main(int argc, char const *argv[])
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++)
	{
		string temp;
		getline(cin, temp);
		json += temp;
	}
	for(int i = 0; i < m; i++)
	{
		getline(cin, query[i]); 
	}
	parseObject(json, )
	return 0;
}