/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode* fast = head;
        ListNode* low = head;
        while (fast != NULL && fast->next != NULL)
        {
            fast = fast->next->next;
            low = low->next;
            if (fast == low)
            {
                return true;
            }
        }
        return false;
    }
};