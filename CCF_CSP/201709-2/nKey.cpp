#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <algorithm>

#define MAX_KEY 1000
#define MAX_COURSE 1000
#define MAX_COURSE_START 10000
#define MAX_COURSE_LEN 100

using namespace std;

struct CourseKey
{
	int key;
	int start;
	int len;
};

int keyNum, courseNum;
CourseKey cou_key[MAX_COURSE];
pair<int, int> lendList[MAX_COURSE], returnList[MAX_COURSE];
int *keys;

bool timeComp(pair<int, int> aPair, pair<int, int> bPair)
{
	return aPair.first < bPair.first;
}

void lendKey(int key)
{
	for(int i = 0; i < keyNum; i++)
		if(keys[i] == key)
		{
			keys[i] = 0;
			return;
		}
}

void returnKey(int key)
{
	for(int i = 0; i < keyNum; i++)
		if(keys[i] == 0)
		{
			keys[i] = key;
			return;
		}
}

int main(int argc, char const *argv[])
{
	scanf("%d%d", &keyNum, &courseNum);
	keys = new int[keyNum];
	for(int i = 0; i < keyNum; i++) keys[i] = i + 1;
	for (int i = 0; i < courseNum; ++i)
	{
		scanf("%d%d%d", &cou_key[i].key, &cou_key[i].start, &cou_key[i].len);
		lendList[i] = make_pair(cou_key[i].start, cou_key[i].key);
		returnList[i] = make_pair(cou_key[i].start + cou_key[i].len, cou_key[i].key);
	}
	sort(lendList, lendList + courseNum, timeComp);
	sort(returnList, returnList + courseNum, timeComp);
	for(int i = 0, j = 0; i < courseNum || j < courseNum;)
	{
		// 注意此处的判断条件！！！
		if((j != courseNum && returnList[j].first <= lendList[i].first) || i == courseNum)
		{
			int t = returnList[j].first;
			int *returnKeys = new int[keyNum];
			int k = 0;
			while(returnList[j].first == t) returnKeys[k++] = returnList[j++].second;
			sort(returnKeys, returnKeys + k);
			for(int l = 0; l < k; l++)
				returnKey(returnKeys[l]);
		}
		if((i != courseNum && returnList[j].first > lendList[i].first) || j == courseNum)
		{
			lendKey(lendList[i++].second);
		}
	}
	for(int i = 0; i < keyNum; i++) 
	{
		printf("%d", keys[i]);
		if(i != keyNum - 1) putchar(' ');
	}
	return 0;
}