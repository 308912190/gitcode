class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int result = INT_MAX;
        int i = 0, sum = 0;
        for (int j = 0; j < nums.size(); j++) {
            sum += nums[j];
            while (sum >= target) {
                result = min(result, j - i + 1);
                sum -= nums[i];
                i++;
            }
        }
        return result == INT_MAX ? 0 : result;
    }
};
/* ±©Á¦½â
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int length = 0;
        int result = INT_MAX;
        for (int i = 0; i < nums.size(); i++) {
            int sums = 0;
            for (int j = i; j < nums.size(); j++) {
                sums = sums + nums[j];
                if (sums >= target) {
                    length = j - i + 1;
                    result = min(result, length);
                    break;
                }
            }
        }
        return result == INT_MAX ? 0 : result;
    }
};
*/