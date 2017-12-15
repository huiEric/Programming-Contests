#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>

#define NUM_CASES 10

#define MAX_N 500
#define MIN_N 1
#define MAX_M 2000
#define MIN_M 0

using namespace std;

ofstream fo("in.txt");
int group[MAX_N];

void genCase()
{
    int n = rand() % (MAX_N - MIN_N + 1) + MIN_N;
    int m = rand() % (MAX_M - MIN_M + 1) + MIN_M;
    fo << n << ' ' << m << endl;
    for(int i = 0; i < n; ++i) group[i] = rand() % (3 - 0) + 0;
    for(int i = 0; i < m; ++i)
    {
        int x = rand() % (n - 0) + 0;
        int y = rand() % (n - 0) + 0;
        if(x == y)
        {
            --i;
            continue;
        }
        if(group[x] == group[y]) fo << x << '=' << y << endl;
        if(group[y] == (group[x] + 1) % 3) fo << x << '>' << y << endl;
        if(group[x] == (group[y] + 1) % 3) fo << x << '<' << y << endl;
    }
}

int main(int argc, char const *argv[])
{
    srand((unsigned) time(0));
    for(int i = 0; i < NUM_CASES; ++i) genCase();
    return 0;
}