#include <iostream>
#include <vector>
#include <algorithm>  
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minprice = INT_MAX;
        int n = (int)prices.size();
        int maxprofit = 0;
        for (int i = 0; i < n; i++) {
            minprice = min(minprice, prices[i]);
            maxprofit = max(maxprofit, prices[i] - minprice);
        }
        return maxprofit;
    }
};
//优化：贪心策略：只需要一次遍历，保存当前最低的股票价格，然后在每个价格点计算可能的最大利润。
/*暴力解
int maxProfit(vector<int>& prices) {
    int n = prices.size(), ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ans = max(ans, prices[j] - prices[i]);
        }
    }
    return ans;
}
*/