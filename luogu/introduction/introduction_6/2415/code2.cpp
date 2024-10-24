1. 位运算法
位运算法利用了一个事实：一个集合中的每个元素在任何子集中都有两种可能性——存在或不存在。因此，如果集合有n个元素，那么总共会有2^n个子集。使用位运算，我们可以遍历所有2^n种可能性。

每一种可能性都对应于一个从0到2^n - 1的整数，其中每个整数的二进制表示指示了原集合中哪些元素应该被选入子集中（二进制位为1）哪些不应该（二进制位为0）。

#include <iostream>
#include <vector>

void printSubsetsUsingBits(const std::vector<int>& set) {
    int n = set.size();
    // 总共2^n种可能
    for (int i = 0; i < (1 << n); ++i) {
        std::cout << "{ ";
        for (int j = 0; j < n; ++j) {
            // 检查j位是否为1
            if (i & (1 << j)) {
                std::cout << set[j] << " ";
            }
        }
        std::cout << "}\n";
    }
}

int main() {
    std::vector<int> set = {1, 2, 3};
    printSubsetsUsingBits(set);
    return 0;
}
逐行解释:

int n = set.size();: 计算原集合的大小。
for (int i = 0; i < (1 << n); ++i): 遍历所有2^n种可能性。(1 << n)是2^n的位表示。
for (int j = 0; j < n; ++j): 对于每种可能性，遍历集合的每个元素。
if (i & (1 << j)): 检查第j位是否为1，即原集合中的第j个元素是否应该包括在当前子集中。
std::cout << set[j] << " ": 如果上述条件为真，打印该元素。
2. 递归回溯法
递归回溯法通过逐步构建子集，并在构建过程中探索所有可能的分支来找到所有子集。每一步都决定是否将当前元素添加到正在构建的子集中。

cpp
复制
#include <iostream>
#include <vector>

void generateSubsets(int i, std::vector<int>& subset, const std::vector<int>& set) {
    if (i == set.size()) { // 基本情况：已处理完所有元素
        std::cout << "{ ";
        for (int num : subset) {
            std::cout << num << " ";
        }
        std::cout << "}\n";
        return;
    }
    // 不包含当前元素
    generateSubsets(i + 1, subset, set);
    
    // 包含当前元素
    subset.push_back(set[i]);
    generateSubsets(i + 1, subset, set);
    subset.pop_back(); // 回溯
}

int main() {
    std::vector<int> set = {1, 2, 3}, subset;
    generateSubsets(0, subset, set);
    return 0;
}
逐行解释:

if (i == set.size()): 基本情况，如果已处理完所有元素，则打印当前子集。
generateSubsets(i + 1, subset, set);: 递归调用，处理下一个元素，当前元素不包含在子集中。
subset.push_back(set[i]);: 包含当前元素到子集中。
generateSubsets(i + 1, subset, set);: 再次递归调用，处理下一个元素，当前元素包含在子集中。
subset.pop_back();: 回溯，移除当前元素，为下一次递归调用恢复子集状态。
通过这两种方法，你可以高效地找到集合中的所有子集。每种方法都有其用例和优势，位运算法非常快且直接，适合于元素数量较少的情况；而递归回溯法更灵活，适合于需要更复杂决策过程的情况。