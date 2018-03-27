#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

class MinStack {
    vector<int> s,sm;
public:
    MinStack() {
        // do intialization if necessary
        s.clear();
        sm.clear();
    }

    /*
     * @param number: An integer
     * @return: nothing
     */
    void push(int number) {
        // write your code here
        s.push_back(number);
        int m;        
        if(sm.empty())
            m=number;
        else
            m=std::min(sm.back(),number);
        sm.push_back(m);
    }

    /*
     * @return: An integer
     */
    int pop() {
        // write your code here        
        int m=s.back();
        s.pop_back();
        sm.pop_back();
        return m;
    }

    /*
     * @return: An integer
     */
    int min() {
        // write your code here
        return sm.back();
    }
};

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif    
    char buf[10];
    int x;
    while(1) {
        fgets(buf, sizeof(buf), stdin);
        if(buf[0]!='p' && buf[0]!='m')
            break;    
        MinStack s;    
        if(buf[1]=='u') {
            x=buf[5]-'0';
            s.push(x);
        }
        else if(buf[1]=='o') {
            printf("%d\n", s.pop());
        }
        else {
            printf("%d\n", s.min());
        }
    }
    return 0;
}