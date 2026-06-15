// Delete a node from a linked list
// Question Link : https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/

// Time Complexity: O(n)
// Space Complexity: O(1)

// approach, fast and slow pointer

#include<bits/stdc++.h>
using namespace std;

struct ListNode{
    int val;
    ListNode * next;
    ListNode(): val(0), next(nullptr){}
    ListNode(int x): val(x), next(nullptr){}
};

class Solution{
    public: 
        ListNode* deleteMiddle(ListNode * head){
            if( head == NULL || head->next == NULL){
                return NULL;
            }
            ListNode * slow = head;
            ListNode * fast = head->next->next;
            while(fast != NULL && fast->next != NULL){
                slow = slow->next;
                fast = fast->next->next;
            }
            slow->next = slow->next->next;
            return head;
        }
};

int main(){
    Solution s;
    ListNode * head = new ListNode(1);
    head->next = new ListNode(3);
    head->next->next = new ListNode(4);
    head->next->next->next = new ListNode(7);
    head->next->next->next->next = new ListNode(1);
    head->next->next->next->next->next = new ListNode(2);

    head = s.deleteMiddle(head);
    while(head != NULL){
        cout<<head->val<<" ";
        head = head->next;
    }

    return 0;
}