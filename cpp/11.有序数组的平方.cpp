class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int>result(nums.size(), 0);
        int k = nums.size() - 1;
        for (int i = 0, j = nums.size() - 1; i <= j;) {
            if (nums[i] * nums[i] > nums[j] * nums[j]) {
                result[k--] = nums[i] * nums[i];
                i++;
            }
            else {
                result[k--] = nums[j] * nums[j];
                j--;
            }
        }
        return result;
    }
};
/*
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        for(auto it=nums.begin();it!=nums.end();it++){
            *it=(*it)*(*it);
        }
        sort(nums.begin(),nums.end());
        return nums;
    }
};
*/