#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    /**
     * @param nums: A list of integers
     * @return: the median of numbers
     */
    vector<int> medianII(vector<int> &nums) {
        // write your code here
        priority_queue<int> maxheap;
        priority_queue<int,vector<int>,greater<int>> minheap;
        vector<int> ans;
        int n=nums.size();
        for(int i=1;i<=n;++i) {
            maxheap.push(nums[i-1]);
            if(i%2==0) {
                minheap.push(maxheap.top());
                maxheap.pop();
            }
            if(maxheap.size() && minheap.size()) {
                int max=maxheap.top(), min=minheap.top();
                printf("%d %d\n", max, min);
                if(max>min) {
                    maxheap.pop();
                    minheap.pop();
                    maxheap.push(min);
                    minheap.push(max);
                }
            }
            ans.push_back(maxheap.top());
        }
        return ans;
    }
};

int main() {
    Solution ans;
    //int a[]={1,2,3,4,5};
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(4);
    nums.push_back(5);
    vector<int> res=ans.medianII(nums);
    return 0;
}