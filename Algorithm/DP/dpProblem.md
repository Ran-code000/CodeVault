# dp 经典好题

[建议先阅读 DP 算法入门](https://blog.csdn.net/2301_81373791/article/details/144489803?spm=1001.2014.3001.5502)

## 00001 最长递增子序列（Longest Increasing Subsequence，简写 LIS）


提要：本文介绍两种算法实现

一种是动态规划（算法复杂度 O（n ^ 2））：通过本题了解设计动态规划的通用技巧 ————> 数学归纳思想


一种是二分查找（算法复杂度 O（n log n））：由 patience game 的纸牌游戏（甚至有一种排序方法就叫做 patience sorting（耐心排序））的思想衍生的算法

---

### 01 动态规划

    假设这个结论在 k < n 时成立，然后想办法证明 k = n 的时候此结论也成立。如果能够证明出来，那么就说明这个结论对于 k 等于任何数都成立

    类似的，我们设计动态规划算法，不是需要一个 dp 数组吗？我们可以假设 dp[0...i - 1] 都已经被算出来了，怎么通过这些结果算出 dp[i]？

首先要定义清楚 dp 数组的含义，即 dp[i] 的值到底代表着什么？

***我们的定义是这样的：dp[i] 表示以 nums[i] 这个数结尾的最长递增子序列的长度***


重申一遍 DP 框架 

    明确状态 -> 定义 dp 数组/函数的含义 -> 明确选择-> 明确 base case

```cpp
int lengthOfLIS(vector<int> &nums)
{
    if (nums.empty())
        return 0;

    int n = nums.size();
    //dp 数组应该全部初始化为 1，因为子序列最少也要包含自己，所以长度最小为 1
    vector<int> dp(n, 1); 

    // 填充 dp 数组
    for (int i = 1; i < n; ++i)
    {
        //找到前面那些结尾比 i 小的子序列，然后把 i 接到最后，就可以形成一个新的递增子序列，而且这个新的子序列长度加 1
        for (int j = 0; j < i; ++j)
        {
            if (nums[i] > nums[j])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    // 寻找 dp 数组中的最大值即找最长递增子序列
    int res = 0;
    for (int i = 0; i < n; ++i)
    {
        res = max(res, dp[i]);
    }
    return res;
}

```

### 10  二分查找

首先我们玩下叫 patience game 的纸牌游戏

    规则：他的实现原理就是首先使用数组中的第一个数字创建一个纸牌堆，然后逐个读取数组中的剩余数字，如果当前数字比所有纸牌堆中最上面的数字都大，就新建一个纸牌堆，把当前数字放到该堆中。否则找到一个最上面数字不小于当前数字的纸牌堆，把当前数字放到该纸牌堆中

![1](https://mmbiz.qpic.cn/sz_mmbiz_png/PGmTibd8KQBF0dnhicyPlXXtSmKmufa5rib0l3OqSWqN1qHKwyj96ZqwuhUc3vOHsIeHj2QE2Cs4OibPSdfbxFocUQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

![1](https://mmbiz.qpic.cn/sz_mmbiz_png/PGmTibd8KQBF0dnhicyPlXXtSmKmufa5ribOtpYvQicSToKfKLAxCdgNnWk6hWCVBiaM4SXZtRZhHvD8Tiaowia7FELSA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

![1](https://mmbiz.qpic.cn/sz_mmbiz_png/PGmTibd8KQBF0dnhicyPlXXtSmKmufa5ribHTf2jbpeFRagfBXHSGrZUQ46icVFeVThA2ZLmlGx4S5qdxBlBz9A8eA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

![1](https://mmbiz.qpic.cn/sz_mmbiz_png/PGmTibd8KQBF0dnhicyPlXXtSmKmufa5ribIU5Zy222LeDbgL3We1MjNSXt96cuJj6MGkWeUiacRicmmoZTG0RoVkJw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

![1](https://mmbiz.qpic.cn/sz_mmbiz_png/PGmTibd8KQBF0dnhicyPlXXtSmKmufa5riboLpjibM4n2vfrGbcYibRzOpUhg4fhW99RicQdRBaGWNicFibzHag0qcsuyA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

![1](https://mmbiz.qpic.cn/sz_mmbiz_png/PGmTibd8KQBF0dnhicyPlXXtSmKmufa5ribY369DS3mGiaiaiaAYcZmibibia5iaJKTczQfRzqm02DcG0Rzfrv4mQ4JWHAIQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

![1](https://mmbiz.qpic.cn/sz_mmbiz_png/PGmTibd8KQBF0dnhicyPlXXtSmKmufa5rib6xHS4rvfOj9tkARMMmQWK04TkBMYg04U28wkFozouZlic4adUHKyp7g/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

---

我们只要把处理扑克牌的过程编程写出来即可。每次处理一张扑克牌不是要找一个合适的牌堆顶来放吗？牌堆顶的牌不是有序吗？

———> 用到二分查找了：搜索当前牌应放置的位置

---

```cpp

int LIS(vector<int> &nums)
{
    if (nums.empty())
        return 0;

    vector<int> top; // 用于存储牌堆的顶端元素
    for (int poker : nums)
    {
        // 二分查找，找到比 poker 大的最小位置
        auto it = lower_bound(top.begin(), top.end(), poker);

        // 如果没有找到合适的位置，说明 poker 应该作为新的牌堆加入
        if (it == top.end())
        {
            top.push_back(poker);
        }
        else
        {
            // 否则，更新找到的位置
            *it = poker;
        }
    }

    // 牌堆数即为 LIS 长度
    return top.size();
}

```

---
这里的二分查找直接用了 STL 算法库中的 lower_bound （因为lower_bound 底层实现使用二分查找）

想要了解二分查找的实现的参考

```cpp
template <typename ForwardIterator, typename T>
ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& val) {
    while (first < last) {
        ForwardIterator mid = first + (last - first) / 2;  // 计算中点
        if (*mid < val) {
            first = mid + 1;  // 如果 mid 小于 val，则搜索右半部分
        } else {
            last = mid;  // 如果 mid 大于或等于 val，则搜索左半部分
        }
    }
    return first;  // 返回第一个不小于 val 的元素
}
```
---

## 000010 股票买卖问题（leecode 6道股票买卖问题打包解决）

原题链接：为节省篇幅，这里不展开题目描述

---
[买卖股票的最佳时机](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/description/)

[买卖股票的最佳时机 Ⅱ](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/description/)

[买卖股票的最佳时机 Ⅲ](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii/)

[买卖股票的最佳时机 Ⅳ](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iv/)

[买卖股票的最佳时机含手续费](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/)

[买卖股票的最佳时机含冷冻期](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/)

---
第一题是只进行一次交易，相当于 k = 1；

第二题是不限交易次数，相当于 k = +infinity（正无穷）；

第三题是只进行 2 次交易，相当于 k = 2；

第四题是进行 k 次交易，相当于前三道题的模板题

剩下两道也是不限次数，但是加了 交易冷冻期 和 手续费 的额外条件，其实就是第二题的变种，都很容易处理

---

首先，还是一样的思路：***穷举***

那我们怎么穷举？穷举什么？

答：
    利用状态进行穷举。
    
    我们具体到每一天，看看总共有几种可能的状态，再找出每个状态对应的选择。

省流：

穷举所有 ***状态***，根据对应的 ***选择***更新状态

（记住关键词 ***状态***， ***选择***）

---

伪代码实现
```cpp
for 状态1 in 状态1的所有取值：
    for 状态2 in 状态2的所有取值：
        for ...
            dp[状态1][状态2][...] = 择优(选择1，选择2...)
```

    比如说这个问题，每天都有三种选择：买入、卖出、无操作，我们用 buy, sell, rest 表示这三种选择。

    但问题是，并不是每天都可以任意选择这三种选择的，因为 sell 必须在 buy 之后，buy 必须在 sell 之后。

    那么 rest 操作还应该分两种状态，一种是 buy 之后的 rest（持有了股票），一种是 sell 之后的 rest（没有持有股票）。

    而且别忘了，我们还有交易次数 k 的限制，就是说你 buy 还只能在 k > 0 的前提下操作。

很复杂对吧，不要怕！我们现在的目的只是穷举，你有再多的状态，要做的就是一股脑全列举出来。

如果仔细阅读上面的分析我们可以发现，这个问题的状态有三个：

***天数，允许交易的最大次数，当前的持有状态***（即之前说的 rest 的状态，我们不妨用 1 表示持有，0 表示没有持有）

然后我们用一个三维数组就可以装下这几种状态的全部组合：`dp[i][k][0 or 1]`

0 <= i <= n - 1, 1 <= k <= K (n 为天数，大 K 为最多交易数)

---

此问题共 n × K × 2 种状态，全部穷举就能搞定。

```cpp
for 0 <= i < n:
    for 1 <= k <= K:
        for s in {0, 1}:
            dp[i][k][s] = max(buy, sell, rest)
```

---

***用自然语言描述出每一个状态的含义***

dp[3][2][1]：今天是第三天，我现在手上持有着股票，至今最多进行 2 次交易。

dp[2][3][0]：今天是第二天，我现在手上没有持有股票，至今最多进行 3 次交易。

我们想求的最终答案是 dp[n - 1][K][0]：即最后一天，最多允许 K 次交易，最多获得多少利润。

（读者可能问为什么不是 dp[n - 1][K][1]？因为 [1] 代表手上还持有股票，[0] 表示手上的股票已经卖出去了，很显然后者得到的利润一定大于前者）

ps：记住如何解释状态，一旦你觉得哪里不好理解，把它翻译成自然语言就容易理解了

---

到这里我们可以来写一下状态转移方程：

```txt
    dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
                        选择 rest            选择 sell      


    解释：今天我没有持有股票，有两种可能：

    要么是我昨天就没有持有，然后今天选择 rest，所以我今天还是没有持有；

    要么是我昨天持有股票，但是今天我 sell 了，所以我今天没有持有股票了。

    今天的最大利润就是这两种可能选择中较大的那个
```

```txt
    dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
                        选择 rest            选择 buy         

    解释：今天我持有着股票，有两种可能：

    要么我昨天就持有着股票，然后今天选择 rest，所以我今天还持有着股票；

    要么我昨天本没有持有，但今天我选择 buy，所以今天我就持有股票了。

    今天的最大利润就是这两种可能选择中较大的那个
    
```

这个解释应该很清楚了，如果 buy，就要从利润中减去 prices[i]，如果 sell，就要给利润增加 prices[i]

而且注意 k 的限制，我们在选择 buy 的时候，把 k 减小了 1，很好理解吧，当然你也可以在 sell 的时候减 1，一样的。

---

现在，我们已经完成了动态规划中最困难的一步：状态转移方程。如果之前的内容你都可以理解，那么你已经可以秒杀所有问题了，只要套这个框架就行了。不过还差最后一点点，就是定义 base case，即最简单的情况

    dp[-1][k][0] = 0
    解释：因为 i 是从 0 开始的，所以 i = -1 意味着还没有开始，这时候的利润当然是 0 

    dp[-1][k][1] = -infinity
    解释：还没开始的时候，是不可能持有股票的，用负无穷表示这种不可能

    dp[i][0][0] = 0
    解释：因为 k 是从 1 开始的，所以 k = 0 意味着根本不允许交易，这时候利润当然是 0 

    dp[i][0][1] = -infinity
    解释：不允许交易的情况下，是不可能持有股票的，用负无穷表示这种不可能

把上面的状态转移方程总结一下：

    base case：
    dp[-1][k][0] = dp[i][0][0] = 0
    dp[-1][k][1] = dp[i][0][1] = -infinity

    状态转移方程：
    dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
    dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])

读者可能会问，这个数组索引是 -1 怎么编程表示出来呢，负无穷怎么表示呢？这都是细节问题，有很多方法实现。现在完整的框架已经完成，下面开始具体化。

---

### 001 买卖股票的最佳时机

第一题，k = 1

直接套状态转移方程，根据 base case，可以做一些化简：
（解释：k = 0 的 base case，所以 dp[i-1][0][0] = 0）

    dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + prices[i])

    dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][0] - prices[i]) 
                = max(dp[i-1][1][1], -prices[i])
                

现在发现 k 都是 1，不会改变，即 k 对状态转移已经没有影响了

可以进行进一步化简去掉所有 k：

    dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
    dp[i][1] = max(dp[i-1][1], -prices[i])

---

至此我们得到了状态转移方程，直接写出代码：
***我们思考这段代码完全正确吗？***

```cpp
int maxProfit(vector<int> &prices)
{
    int n = prices.size();
    // 初始化 dp 数组大小为 n * 2
    vector<vector<int>> dp(n, vector<int>(2));

    for (int i = 0; i < n; i++)
    {
        // 计算 dp[i][0]
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
        // 计算 dp[i][1]
        dp[i][1] = max(dp[i - 1][1], -prices[i]);
    }

    // 返回 dp[n - 1][0]
    return dp[n - 1][0];
}
```

显然 i = 0 时 dp[i-1] 是不合法的。这是因为我们没有对 i 的 base case 进行处理。可以这样处理：

```cpp
int maxProfit(const vector<int> &prices)
{
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2));

    // 初始化第一天的状态
    dp[0][0] = 0;          // 如果没有交易，第一天不持有股票的利润是 0
    /*
    解释：
      dp[0][0] 
    = max(dp[-1][0], dp[-1][1] + prices[i])
    = max(0, -infinity + prices[i]) = 0
    */
    dp[0][1] = -prices[0]; // 第一天购买股票的成本是第一天的价格
    /*
      dp[0][1] 
    = max(dp[-1][1], dp[-1][0] - prices[i])
    = max(-infinity, 0 - prices[i]) 
    = -prices[i]
    */

    // 从第二天开始计算状态
    for (int i = 1; i < n; i++)
    {
        // 在第 i 天结束时，不持有股票的最大利润
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
        // 在第 i 天结束时，持有股票的最大利润
        dp[i][1] = max(dp[i - 1][1], -prices[i]);
    }

    // 返回最后一天不持有股票时的最大利润
    return dp[n - 1][0];
}
```

第一题就解决了，但是这样处理 base case 很麻烦，而且注意一下状态转移方程，新状态只和相邻的一个状态有关，其实不用整个 dp 数组，只需要一个变量储存相邻的那个状态就足够了，这样可以把空间复杂度降到 O(1):

```cpp
int maxProfit_k_1(const vector<int> &prices)
{
    int n = prices.size();
    if (n == 0)
        return 0;

    int dp_i_0 = 0;       // 在第 i 天结束时，不持有股票的最大利润
    int dp_i_1 = INT_MIN; // 在第 i 天结束时，持有股票的最大利润（初始为INT_MIN，代表负无穷）

    for (int price : prices)
    {
        dp_i_0 = max(dp_i_0, dp_i_1 + price);         // 从持有变为不持有
        dp_i_1 = max(dp_i_1, -price);                 // 从不持有变为持有
    }

    return dp_i_0;
}
```

两种方式都是一样的，不过这种编程方法简洁很多。但是如果没有前面状态转移方程的引导，是肯定看不懂的。后续的题目，我主要写这种空间复杂度 O(1) 的解法。

---

### 010 买卖股票的最佳时机 Ⅱ

第二题，k = +infinity

如果 k 为正无穷，那么就可以认为 k 和 k - 1 是一样的。可以这样改写框架

    dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])

    dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
                = max(dp[i-1][k][1], dp[i-1][k][0] - prices[i])

我们发现数组中的 k 已经不会改变了，也就是说不需要记录 k 这个状态了：

    dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
    dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])

---

到这我们发现当 k = 1 和 k = +inf 时，k（允许交易的最大次数） 状态都可以化简掉，但是这两者实现细节上有区别：

这里 k = +inf 与 k = 1 的情况相比，不同点在：

    k = 1 时 dp[i][1] = max(dp[i-1][1], - prices[i])

    k = +infinity 时 dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])

    因为在 dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i]) 中，当 k = 1 时 dp[i-1][k-1][0] = dp[i-1][0][0] = 0；

    而当 k = +inf 时 dp[i-1][k-1][0] = dp[i-1][k][0] ≠ 0；

---

直接翻译成代码：

```cpp
int maxProfit_k_inf(const vector<int> &prices)
{
    int n = prices.size();
    if (n <= 1)
        return 0;

    int dp_i_0 = 0;
    int dp_i_1 = INT_MIN;

    for (int price : prices)
    {
        dp_i_0 = max(dp_i_0, dp_i_1 + price);         // 从持有变为不持有
        dp_i_1 = max(dp_i_1, dp_i_0 - price);                 // 从不持有变为持有
    }
    return dp_i_0;
}
```

---
类似的我们解决第5，6题

---

[第五题](#101-买卖股票的最佳时机含手续费)
[第六题](#100-买卖股票的最佳时机含冷冻期)

---

### 011 买卖股票的最佳时机 Ⅲ

k = 2

k = 2 和前面题目的情况稍微不同，因为上面的情况都和 k 的关系不太大。

    要么 k 是正无穷，由于 k - 1 等于 k，状态转移和 k 没关系了；
    要么 k = 1，跟 k = 0 这个 base case 挨得近（dp[i - 1][0][0] = 0），最后状态转移也和 k 没关系了

这道题 k = 2 和题目四要讲的 k 是任意正整数的情况中，对 k 的处理就凸显出来了。

我们直接写代码，边写边分析原因。

原始的动态转移方程，没有可化简的地方

    dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])

    dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])

按照之前的代码，我们可能想当然这样写代码是 ***错误的***：

```cpp

int maxProfit_k_2(const vector<int> &prices, int k)
{
    int n = prices.size();
    if (n == 0)
        return 0;

    // 初始化三维动态规划数组
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(k + 1, vector<int>(2, 0)));

    // 从第二天开始计算状态
    for (int i = 1; i < n; i++)
    {
        if (i - 1 == -1)
        { 
          /* 处理一下 base case*/
        }
        dp[i][k][0] = max(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i]);
        // 为了更新第 k 层的持有股票状态，需要从第 k-1 层的状态前移一位
        dp[i][k][1] = max(dp[i - 1][max(k - 1, 0)][1], dp[i - 1][k - 1][0] - prices[i]);
    }

    // 返回最后一天进行 k 次交易完成后不持有股票的最大利润
    return dp[n - 1][k][0];
}
```

---

为什么错误？我这不是照着状态转移方程写的吗？

还记得前面总结的穷举框架吗？就是说我们必须穷举所有状态。其实我们之前的解法，都在穷举所有状态，只是之前的题目中 k 在等于正无穷和 1 时都被化简掉了

---

让我们快速回忆一下最开始给出的状态穷举框架

```cpp
for 0 <= i < n:
    for 1 <= k <= K:
        for s in {0, 1}:
            dp[i][k][s] = max(buy, sell, rest)
```

这道题由于没有消掉 k 的影响，所以必须要对 k 进行穷举：

```cpp
int maxProfit_with_k_transactions(const vector<int> &prices, int max_k)
{
    int n = prices.size();

    // 特殊情况处理，如果价格数组为空或最多交易次数为0，则直接返回0
    if (n == 0 || max_k == 0)
        return 0;

    // 初始化三维dp数组
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(max_k + 1, vector<int>(2, 0)));

    // 动态规划计算每个状态
    for (int i = 0; i < n; i++)
    {
        for (int k = max_k; k >= 1; k--)
        {
            if (i == 0)
            {                             // base case
                dp[i][k][0] = 0;          // 第0天不持有股票的利润为0
                dp[i][k][1] = -prices[i]; // 第0天持有股票的最大利润为-价格[0]
            }
            else
            {
                // 状态转移方程
                dp[i][k][0] = max(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i]);
                dp[i][k][1] = max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i]);
            }
        }
    }

    // 返回最后一天，不持有股票时的最大利润
    return dp[n - 1][max_k][0];
}
```

---

    由于这里 k 取值范围比较小（k = 2），所以可以不用 for 循环，直接把 k = 1 和 2 的情况全部列举出来也可以：

    dp[i][2][0] = max(dp[i-1][2][0], dp[i-1][2][1] + prices[i])

    dp[i][2][1] = max(dp[i-1][2][1], dp[i-1][1][0] - prices[i])

    dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + prices[i])

    dp[i][1][1] = max(dp[i-1][1][1], -prices[i])

---

```cpp
int maxProfit_k_2(const vector<int> &prices)
{
    int dp_i10 = 0, dp_i11 = INT_MIN; // dp_i10 表示不持有股票时的最大利润，dp_i11 表示持有股票时的最大利润
    int dp_i20 = 0, dp_i21 = INT_MIN; // dp_i20 表示第二次交易后不持有股票时的最大利润，dp_i21 表示第二次交易后持有股票时的最大利润

    for (int price : prices)
    {
        dp_i20 = max(dp_i20, dp_i21 + price); // 卖出股票后不持有股票的最大利润
        dp_i21 = max(dp_i21, dp_i10 - price); // 买入第二次股票后的最大利润
        dp_i10 = max(dp_i10, dp_i11 + price); // 卖出第一次股票后的最大利润
        dp_i11 = max(dp_i11, -price);         // 买入第一次股票后的最大利润（负的价格，因为是买入操作）
    }

    return dp_i20; // 最终的最大利润是两次交易完成后不持有股票时的最大利润
}
```

（有状态转移方程和含义明确的变量名指导，相信你很容易看懂。其实我们可以故弄玄虚，把上述四个变量换成 a, b, c, d。这样当别人看到你的代码时就会大惊失色，对你肃然起敬）

---

### 100 买卖股票的最佳时机 Ⅳ

k = any integer

有了上一题 k = 2 的铺垫，这题应该和上一题的第一个解法没啥区别。

***但是出现了一个超内存的错误！！！***，why？

原来是传入的 k 值会非常大，dp 数组太大了。现在想想，交易次数 k 最多有多大呢？

一次交易由买入和卖出构成，至少需要两天。所以说有效的限制 k 应该不超过 n / 2，如果超过，就没有约束作用了，相当于 k = +infinity。这种情况是之前解决过的。

直接把之前的代码重用：

```cpp
#include <vector>
#include <algorithm> // For max function

using namespace std;

int maxProfit_k_inf(const vector<int> &prices)
{
    int n = prices.size();

    int dp_i_0 = 0；
    int dp_i_1 = INT_MIN;

    for (int price : prices)
    {
        dp_i_0 = max(dp_i_0, dp_i_1 + price); 
        dp_i_1 = max(dp_i_1, dp_i_0 - price);         
    }
    return dp_i_0;
}

int maxProfit_k_any(int max_k, const vector<int> &prices)
{
    int n = prices.size();

    //如果超过 n / 2，就没有约束作用了，相当于 k = +infinity
    if (max_k >= n / 2)
    {
        return maxProfit_k_inf(prices);
    }

    vector<vector<vector<int>>> dp(n, vector<vector<int>>(max_k + 1, vector<int>(2, 0)));

    for (int i = 0; i < n; i++)
    {
        for (int k = max_k; k >= 1; k--)
        {
            //Base case处理
            if (i == 0)
            {                           
                dp[i][k][0] = 0;          
                dp[i][k][1] = -prices[i];
            }
            else
            {
                dp[i][k][0] = max(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i]);     
                dp[i][k][1] = max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i]); 
            }
        }
    }

    return dp[n - 1][max_k][0]; 
}
```

---

4，5 两题为第 2 题的变体，建议这三道放一起理解

---

### 101 买卖股票的最佳时机含手续费

k = +infinity with fee

每次交易要支付手续费，只要把手续费从利润中减去即可。改写方程：

    dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])

    dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i] - fee)

    解释：相当于买入股票的价格升高了。
    在第一个式子里减也是一样的，相当于卖出股票的价格减小了。

直接翻译成代码：

```cpp
int maxProfit_with_fee(const vector<int> &prices, int fee)
{
    int n = prices.size();
    if (n <= 1)
        return 0;

    int dp_i_0 = 0;
    int dp_i_1 = INT_MIN;

    for (int price : prices)
    {
        int temp = dp_i_0;
        dp_i_0 = max(dp_i_0, dp_i_1 + price);     // Either hold the stock or sell it
        dp_i_1 = max(dp_i_1, temp - price - fee); // Either hold the stock or buy it, considering the fee
    }
    return dp_i_0;
}
```

### 110 买卖股票的最佳时机含冷冻期

k = +infinity with cooldown

每次 sell 之后要等一天才能继续交易。只要把这个特点融入上一题的状态转移方程即可：

    dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])

    dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i])
    解释：第 i 天选择 buy 的时候，要从 i-2 的状态转移，而不是 i-1 。
    翻译成代码：

```cpp
int maxProfit_with_cool(const vector<int> &prices)
{
    int n = prices.size();
    if (n <= 1)
        return 0;

    int dp_pre_0 = 0; // dp[i-2][0], 代表两天前不持有股票的最大利润
    int dp_i_0 = 0;
    int dp_i_1 = INT_MIN;
    

    for (int price : prices)
    {
        int temp = dp_i_0;

        dp_i_0 = max(dp_i_0, dp_i_1 + price);   // 不持有股票，或者卖出股票
        dp_i_1 = max(dp_i_1, dp_pre_0 - price); // 持有股票，或者买入股票
        dp_pre_0 = temp;                        // 更新 dp_pre_0 为前一天的 dp_i_0
    }

    return dp_i_0; // 返回最后一天不持有股票时的最大利润
}
```

***完结撒花：至此，6 道题目通过一个状态转移方程全部解决！***

---

## 000011 最大食物链计数（拓扑排序）

***拓扑排序结合动态规划***

首先我们回忆一下拓扑排序，见[图的三种遍历算法](https://blog.csdn.net/2301_81373791/article/details/144214124?spm=1001.2014.3001.5502)

### 题目描述
```txt

最大食物链计数（拓扑排序）

最大食物链计数
题目背景
你知道食物链吗？Delia 生物考试的时候，数食物链条数的题目全都错了，因为她总是重复数了几条或漏掉了几条。于是她来就来求助你，然而你也不会啊！写一个程序来帮帮她吧。

题目描述
给你一个食物网，你要求出这个食物网中最大食物链的数量。

（这里的“最大食物链”，指的是生物学意义上的食物链，即最左端是不会捕食其他生物的生产者，最右端是不会被其他生物捕食的消费者。）
也就是说，你需要去找到所有从没有入边的节点到没有出边的节点的路径数量。

Delia 非常急，所以你只有 1 秒的时间。

由于这个结果可能过大，你只需要输出总数模上 80112002 的结果。

输入格式
第一行，两个正整数 n、m，表示生物种类 n 和吃与被吃的关系数 m。

接下来 m 行，每行两个正整数，表示被吃的生物A和吃A的生物B。

输出格式
一行一个整数，为最大食物链数量模上 80112002 的结果。

样例 #1
样例输入 #1
5 7
1 2
1 3
2 3
3 5
2 5
4 5
3 4
​
样例输出 #1
5
​
提示
n小于等于5000
m小于等于500000

数据中不会出现环，满足生物学的要求。


```

---

### 题目分析

首先我们拿出我们的 ***基于入度的拓扑排序***框架（这个框架只输出 一种拓扑排序的顺序 或者 有环排序失败的信息）

拓扑排序框架：

```cpp
void topoSortAndCountPaths()
{
  queue<int> q;
  vector<int> result; // 储存排序得到的数据

  // 1. 将所有入度为 0 的节点入队
  for (int i = 1; i <= n; i++)
  {
    if (indegree[i] == 0)
    {
      q.push(i);
    }
  }

  vector<int> ind = indegree;//不改变原入度数组

  while (!q.empty())
  {
    int u = q.front();
    q.pop();
    result.push_back(u);

    // 遍历 u 的所有邻接节点 v
    for (int v : adj[u])
    {
      // 如果 v 的入度减为 0，则加入队列
      if (ind[v] == 0)
      {
        q.push(v);
      }
    }
  }

  // 如果最后拓扑排序中的节点数小于图中的节点数，则图中存在环。
  if (result.size() != n)
  {
    cout << "has cycle\n";
    return;
  }
  else
  {
    for(int i = 0; i < result.size(); i++)
    {
      cout << result[i] << " ";
    }
  }
}
```

---

框架中是 ***找到一个符合条件的路径*** 

我们这道题需要的是 ***统计所有的符合条件的路径的数量*** 

！！条件：从没有入边的节点 到 没有出边的节点

---

例如一个有向无环图：

        A → B → C
        D → E → F

```txt

（1）初始时，入度为0的点是：A, D（它们没有任何入边指向它们）

（2）可以先选择 A 或者 D 作为拓扑排序的第一个点，假设选择 A

（3）选择 A 后，更新图中其他点的入度。B 的入度减少1，变为0，加入候选队列

（4）现在，入度为0的点是：D, B。你可以选择其中一个来继续排序

（5）假设选择 D，接下来 E 的入度变为0，加入候选队列

（6）继续选择入度为0的点并更新图，直到所有点都被处理

    结果之一可能是：A, D, B, E, C, F。

    另一种可能的排序结果是：D, A, B, E, C, F

```

***框架输出的可能为 A, D, B, E, C, F 或者 D, A, B, E, C, F***


***本题要求输出 路径数 2***

---

那么怎么统计路径数？

不难想到当路过一个出现在交叉路口的节点时：到达这个节点的路径总数 等于 到达这个节点的前驱节点路径总数之和

轻而易举我们就可以确定状态 dp[i] 为：从入度为 0 的节点到节点 i 的路径数

状态转移方程为 `dp[v] = dp[v] + dp[u]`;

因此我们只需在框架中 遍历 u 的所有邻接节点 v 时，添加到达邻接节点 v 的路径数的更新即可

---

```cpp
void topoSortAndCountPaths()
{
  queue<int> q;
  vector<int> result;

  for (int i = 1; i <= n; i++)
  {
    if (indegree[i] == 0)
    {
      q.push(i);

      dp[i] = 1; // 入度为0的节点的路径数初始化为1
    }
  }

  vector<int> ind = indegree;

  while (!q.empty())
  {
    int u = q.front();
    q.pop();
    result.push_back(u);

    for (int v : adj[u])
    {
      dp[v] = (dp[v] + dp[u]) % MOD; // 将u的路径数加到v的路径数上（题目要求 数量模上 MOD）

      ind[v]--;
      if (ind[v] == 0)
      {
        q.push(v);
      }
    }
  }

  // 计算所有从入度为 0 的节点到出度为 0 的节点的路径数量
  int result = 0;
  for (int i = 1; i <= n; i++)
  {
    if (adj[i].empty() && indegree[i] != 0)
    { // 如果是出度为 0 且不孤立的节点
      result = (result + dp[i]) % MOD;
    }
  }

  cout << result << endl;
}
```

---
讲解完毕：附完整代码

---

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define MOD 80112002
using namespace std;

class Graph
{
public:
  int n, m;
  vector<vector<int>> adj; // 邻接表
  vector<int> indegree;    // 入度数组
  vector<int> dp;          // dp[i]表示从入度为0的节点到节点i的路径数

  Graph(int n, int m) : n(n), m(m), adj(n + 1), indegree(n + 1), dp(n + 1, 0) {}

  // 添加边
  void addEdge(int u, int v)
  {
    adj[u].push_back(v);
    indegree[v]++;
  }

  // 拓扑排序和路径计数
  void topoSortAndCountPaths()
  {
    queue<int> q;

    // 将所有入度为0的节点入队
    for (int i = 1; i <= n; i++)
    {
      if (indegree[i] == 0)
      {
        q.push(i);
        dp[i] = 1; // 入度为0的节点的路径数初始化为1
      }
    }

    vector<int> ind = indegree;
    // 拓扑排序，并计算路径数
    while (!q.empty())
    {
      int u = q.front();
      q.pop();

      // 遍历u的所有邻接节点v
      for (int v : adj[u])
      {
        dp[v] = (dp[v] + dp[u]) % MOD; // 将u的路径数加到v的路径数上
        ind[v]--;
        // 如果v的入度减为0，则加入队列
        if (ind[v] == 0)
        {
          q.push(v);
        }
      }
    }

    // 计算所有从入度为0的节点到出度为0的节点的路径数量
    int result = 0;
    for (int i = 1; i <= n; i++)
    {
      if (adj[i].empty() && indegree[i] != 0)
      { // 如果是出度为0的节点
        result = (result + dp[i]) % MOD;
      }
    }

    cout << result << endl;
  }
};

int main()
{
  int n, m;
  cin >> n >> m;
  Graph g(n, m);

  // 读取图的边
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    g.addEdge(u, v);
  }
  if (m == 0)
  {
    cout << 0;
    return 0;
  }
  // 拓扑排序并计算路径数
  g.topoSortAndCountPaths();

  return 0;
}
```