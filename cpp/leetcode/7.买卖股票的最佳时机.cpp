class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minprice=INT_MAX;
        int n=(int)prices.size();
        int maxprofit=0;
        for(int i=0;i<n;i++){
            minprice=min(minprice,prices[i]);
            maxprofit=max(maxprofit,prices[i]-minprice);
            }
        return maxprofit;
    }
};
