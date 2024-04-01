### *常用位运算与双指针*
---

位运算：异或 - 相同为0不同为1

结合律： $a \oplus (b \oplus c) = (a \oplus b) \oplus c$

交换律：$a \oplus b = b \oplus a$

- 位运算常用操作

  - 找出一个数字的最后一位1： $target = num \ \& \ (num - 1)$

  - 找出一个数的lowbit：$lowbit = x \  \& \ (-x)$

- 双指针在判环，链表中的常用技巧

  - 判断一个图中的第一个环的入口 (https://leetcode.cn/problems/find-the-duplicate-number/description/)

  ```c++
  class Solution {
  public:
      int findDuplicate(vector<int>& nums) {
          //把nums中看为以下标向值做一条边，值向下表做边，两个相同数字的值必然与一个下表重合
          //并且一定构成环，环的入口与最后一个数必然就是重复数字
          int low = 0, fast = 0;
          do {
              low = nums[low];
              fast = nums[nums[fast]];
          } while (low != fast);
  
          low = 0;
          while (low != fast) {
              low = nums[low];
              fast = nums[fast];
          }
  
          return low;
      }
  };
  ```

  设置快指针slow = 0, fast = 0，一定从0出发，慢指针每次走一步，快指针每次走两步，当他们第一次相遇，快慢指针在环中，此时设置慢指针为0，快指针慢指针速度都为1，直到相遇，此时指针到达环的入点。

  - 寻找链表的中点 (https://leetcode.cn/problems/middle-of-the-linked-list/description/)

  ```c++
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
      ListNode* middleNode(ListNode* head) {
          ListNode* low = head;
          ListNode* fast = head;
          do {
              if (fast)
              fast = fast->next;
              if (fast)
              low = low->next;
              if (fast)
              fast = fast->next;
          } while (fast != nullptr);
  
          cout << low->val << '\n';
          return low;
      }
  };
  ```

  