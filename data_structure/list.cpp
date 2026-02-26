#include <iostream>
#include <list>

// 反转链表:迭代
struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* reverseList(ListNode* head) {
  ListNode* prev = nullptr;
  ListNode* curr = head;
  while (curr) {
    ListNode* nextTemp = curr->next;
    curr->next = prev;
    prev = curr;
    curr = nextTemp;
  }
  return prev;
}

// 环形链表：双指针法
class Solution {
 public:
  bool hasCycle(ListNode* head) {
    if (!head || !head->next) return false;
    ListNode* slow = head;
    ListNode* fast = head->next;
    while (fast && fast->next) {
      if (slow == fast) return true;
      slow = slow->next;
      fast = fast->next->next;
    }
    return false;
  }
};

// 两两交换节点: 迭代法（最优，虚拟头节点 + 双指针）
ListNode* swapPairs(ListNode* head) {
  if (!head || !head->next) return head;
  ListNode* dummy = new ListNode(-1);
  dummy->next = head;
  ListNode* prev = dummy;
  ListNode* curr = head;
  while (curr && curr->next) {
    ListNode* nextTemp = curr->next->next;
    prev->next = curr->next; 
    curr->next->next = curr; 
    curr->next = nextTemp;
    prev = curr;
    curr = nextTemp;
  }
  return dummy->next;
}

int main(void) {
  // 测试反转链表
  ListNode* head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);
  head->next->next->next->next = new ListNode(5);

  ListNode* reversedHead = reverseList(head);
  ListNode* curr = reversedHead;
  while (curr) {
    std::cout << curr->val << " ";
    curr = curr->next;
  }
  std::cout << std::endl;

  // 两两交换节点测试
  ListNode* head2 = new ListNode(1);
  head2->next = new ListNode(2);
  head2->next->next = new ListNode(3);
  head2->next->next->next = new ListNode(4);
  head2->next->next->next->next = new ListNode(5);
  ListNode* swappedHead = swapPairs(head2);
  for (ListNode* curr = swappedHead; curr; curr = curr->next) {
    std::cout << curr->val << " ";
  }


  return 0;
}