class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        set<int>s1;
        set<int>s2;
        for (int i = 0; i < nums1.size(); i++) {
            s1.insert(nums1[i]);
        }
        for (int i = 0; i < nums2.size(); i++) {
            s2.insert(nums2[i]);
        }
        vector<int>result;
        for (auto t1 = s1.begin(), t2 = s2.begin(); t1 != s1.end() && t2 != s2.end();) {
            if (*t1 < *t2) {
                t1++;
            }
            else if (*t1 > *t2) {
                t2++;
            }
            else {
                result.push_back(*t1);
                t1++;
                t2++;
            }
        }
        return result;
    }
};