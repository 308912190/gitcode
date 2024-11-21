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
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        int lena = 0;
        int lenb = 0;
        int lendiff = 0;
        for (ListNode* na = headA; na != NULL; na = na->next)
        {
            lena++;
        }
        for (ListNode* nb = headB; nb != NULL; nb = nb->next)
        {
            lenb++;
        }
        if (lena > lenb)
        {
            lendiff = lena - lenb;
            ListNode* pa = headA;
            ListNode* pb = headB;
            for (int i = 0; i < lendiff; i++)
            {
                pa = pa->next;
            }
            while (pa && pb && pa != pb)
            {
                pa = pa->next;
                pb = pb->next;
            }
            return pa;
        }
        else if (lena < lenb)
        {
            lendiff = lenb - lena;
            ListNode* pa = headA;
            ListNode* pb = headB;
            for (int i = 0; i < lendiff; i++)
            {
                pb = pb->next;
            }
            while (pa && pb && pa != pb)
            {
                pa = pa->next;
                pb = pb->next;
            }
            return pb;
        }
        else if (lena == lenb)
        {
            ListNode* pa = headA;
            ListNode* pb = headB;
            while (pa && pb && pa != pb)
            {
                pa = pa->next;
                pb = pb->next;
            }
            return pb;
        }
        return NULL;
    }
};