#include <iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head || !head->next)   return head;
        ListNode* first = head;
        ListNode* second = head->next;
        head = second;
        first->next = swapPairs(second->next);
        second->next = first;
        return head;

    }

    ListNode* reverseList(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        else
        {
            ListNode *p1 = head;
            ListNode *p2 = p1->next;
            ListNode *p3 = p2->next;
            while(p2)
            {
                p3 = p2->next;
                p2->next = p1;
                p1 = p2;
                p2 = p3;
            }
            head->next = NULL;
            head = p1;
            return head;
        }
        
    }
};

int main()
{
    ListNode a1(1);
    ListNode a2(2);
    a1.next = &a2;
    ListNode a3(3);
    a2.next = &a3;
    ListNode a4(4);
    a3.next = &a4;
    a4.next = NULL;
    Solution t;
    t.reverseList(&a1);
    ListNode *a = &a1;
    while (a!=NULL)
    {   
        cout << a->val;
        a = a->next;
    }
}