/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyhead = new ListNode(0);
        dummyhead->next = head;
        ListNode* low = dummyhead;
        ListNode* fast = dummyhead;
        for (int i = 0; i < n + 1; i++) {
            fast = fast->next;
        }
        while (fast != nullptr) {
            fast = fast->next;
            low = low->next;
        }
        ListNode* temp = low->next;
        low->next = low->next->next;
        delete temp;
        ListNode* result = dummyhead->next;
        delete dummyhead;
        return result;
    }
};
/*
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyhead = new ListNode(0);
        dummyhead->next = head;
        ListNode* l = dummyhead;
        int length = 0;
        for (ListNode* p = dummyhead; p != nullptr; p = p->next) {
            length++;
        }
        for (int i = 0; i < length - n - 1; i++) {
            l = l->next;
        }
        ListNode* temp = l->next;
        l->next = l->next->next;
        delete temp;
        head = dummyhead->next;
        delete dummyhead;
        return head;
    }
};
*/