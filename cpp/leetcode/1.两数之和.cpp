#include <iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<string>
class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		int n = nums.size();
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				if (nums[i] + nums[j] == target) {
					return{ i,j };
				}
			}
		}
		return {};
	}
};
int main()
{
	vector<int> nums = { 1,5,7,9 };
	int target = 14;
	Solution s1;
	vector<int> result = s1.twoSum(nums, target);
	cout << result[0] << result[1] << endl;
}