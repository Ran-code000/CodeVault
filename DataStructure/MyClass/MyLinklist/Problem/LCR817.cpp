#include <iostream>
using namespace std;
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int val) : val(val){}
};
//链表组件 ———— LCR817
int numComponents(ListNode* head, vector<int>& nums){
    //用哈希表
    unordered_set<int> us;
    //emplace 方法用于在容器中直接构造元素，通常用于提升性能，因为它避免了不必要的拷贝
    /* 比如
        #include <unordered_set>
        #include <iostream>
        using namespace std;
        struct CustomType {
            int x;
            CustomType(int val) : x(val) {}
        };
        int main() {
            unordered_set<CustomType> us;
            us.emplace(1); // 直接用 1 构造 CustomType(1)
            us.emplace(2); // 直接用 2 构造 CustomType(2)

            // 遍历输出
            for (const auto& item : us) cout << item.x << " ";
            return 0;
        }
    */
    for(int num : nums) us.emplace(num);
    bool inset = false;
    int res = 0;
    while(head){
        if(us.count(head->val)) {if(!inset) inset = true, res++;}
        else inset = false;
        head = head->next;
    }
    return res;
}
