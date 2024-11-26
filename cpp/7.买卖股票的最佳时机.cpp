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
//�Ż���̰�Ĳ��ԣ�ֻ��Ҫһ�α��������浱ǰ��͵Ĺ�Ʊ�۸�Ȼ����ÿ���۸�������ܵ��������
/*������
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