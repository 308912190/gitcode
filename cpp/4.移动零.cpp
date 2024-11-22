class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int index = 0;
        int indexnum = 0;
        while (indexnum < nums.size())
        {
            if (nums[indexnum] != 0)
            {
                nums[index] = nums[indexnum];
                index++;
            }
            indexnum++;
        }
        while (index < nums.size())
        {
            nums[index] = 0;
            index++;
        }
    }
};