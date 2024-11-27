class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slowindex=0;
        for(int fastindex=0;fastindex<nums.size();fastindex++){
            if(nums[fastindex]!=val){
                nums[slowindex]=nums[fastindex];
                slowindex++;
            }
        }
        nums.resize(slowindex);
        for(auto it=nums.begin();it!=nums.end();it++){
            cout<<*it;
        }
        return slowindex;
    }
};

/*class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        auto it = nums.begin();
        while (it != nums.end()) {
            if (*it == val) {
                it = nums.erase(it);
            }
            else {
                it++;
            }
        }
        for (auto it = nums.begin(); it != nums.end(); it++) {
            cout << *it << " ";
        }
        return nums.size();
    }
};
*/