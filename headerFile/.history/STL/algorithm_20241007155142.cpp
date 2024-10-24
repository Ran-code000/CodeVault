<algorithm> 中部分常用算法的简要列表及其用法： 

1.非修改序列操作:
all_of, any_of, none_of: 检查序列中的元素是否满足特定条件
for_each: 对序列中每个元素执行函数
count, count_if: 计算满足特定条件的元素数量
mismatch: 返回第一个不匹配的元素对
find, find_if, find_if_not: 查找满足条件的元素

2.修改序列操作:
copy, copy_if, copy_n: 复制元素到另一个位置
move: 移动元素到另一个位置
transform: 对序列中的元素应用一个函数，并存放结果
swap, iter_swap: 交换两个元素
fill, fill_n: 用特定值填充序列
generate, generate_n: 用生成器函数填充序列
replace, replace_if: 替换序列中满足条件的元素

3.排序和相关操作:
sort: 对序列进行排序
stable_sort: 对序列进行稳定排序
partial_sort: 部分排序序列
nth_element: 重新排列序列，以使得第 n 个元素处于它最终排序完成后的位置

4.二分搜索操作（在有序序列上）:
lower_bound, upper_bound: 查找某个值的边界
binary_search: 检查某个值是否存在
equal_range: 同时获取lower_bound和upper_bound

5.集合操作（在有序序列上）:
merge: 合并两个有序序列
inplace_merge: 在原地合并两个有序序列
includes: 检查一个有序序列是否包含另一个序列
set_union, set_intersection, set_difference, set_symmetric_difference: 对两个集合执行集合操作

6.最小/最大操作:
max, min: 返回两个值中的最大值或最小值
max_element, min_element: 查找序列中的最大或最小元素
clamp: 将值限制在指定的范围内

7.比较操作:
equal: 检查两个序列是否相等
lexicographical_compare: 字典顺序比较两个序列

8.排列操作:
next_permutation, prev_permutation: 生成序列的下一个或上一个排列

9.数值算法(需要 <numeric> 头文件)
iota: 填充序列以生成连续的增量值
accumulate: 累加序列中的元素
inner_product: 计算两个序列的内积
adjacent_difference: 计算相邻元素之间的差
partial_sum: 计算序列的部分和
10.堆操作:

make_heap, push_heap, pop_heap, sort_heap: 创建和管理堆



用法:
1. next_permutation 和 prev_permutation
next_permutation和prev_permutation用于生成序列的下一个或上一个排列

字典序 (Lexicographical Order)
字典序是指按照字典中单词的排列顺序，即先比较第一个字符，如果相同再比较下一个字符，以此类推
对于数字序列来说，也是同样的比较规则

示例
假设我们有一个序列{1, 2, 3}

应用 next_permutation
初始序列：{1, 2, 3}，下一个序列：{1, 3, 2}
应用后：{1, 3, 2}，下一个序列：{2, 1, 3}
继续应用直至返回到最初序列，生成所有可能的排列

应用 prev_permutation
如果从序列{1, 2, 3}开始应用,首先会被重新排列为最大排列{3, 2, 1},然后依次产生前一个排列
#include <algorithm>
#include <iostream>
#include <vector>

int main(){
    vector<int> v = {1, 2, 3};

    next_permutation(v.begin(), v.end());

    for(int n : v) cout << n << ' '; // 输出: 1 3 2
    cout << '\n';

    prev_permutation(v.begin(), v.end());

    for(int n : v) cout << n << ' '; // 输出: 1 2 3
    return 0;
}

放进循环输出所有的排列方式
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <cstring>
using namespace std;
unsigned long long fac(int n);
bool is_Palindrome(string s);
int main(){
    string ss;
    unsigned long long ans = 0;
    int cnt = 0, cnt1 = 0;
    vector<string> v; //储存回文字符串
    int a[26];
    memset(a, 0, sizeof(int) * 26);
    cin >> ss;
    for(int i = 0; i < ss.length(); i++) a[tolower(ss[i]) - 'a']++;
    for(int i = 0; i < 26; i++) cout << a[i] << " ";
    cout << endl;
    for(int i = 0; i < 26; i++) if(a[i] > 1) cnt++;
    //循环输出所有的排列方式
    sort(ss.begin(), ss.end()); //先排序
    while(next_permutation(ss.begin(), ss.end())){
        ans++;
        cout << ss << " ";
        if(is_Palindrome(ss)) v.push_back(ss), cnt1++;
    }
    cout << endl;
    cout << "ways : " << ans << endl;
    cout << "fac : " << fac(ss.length()) << endl; //字符串种类数本质是fac(ss.length())阶乘————当字符串去重后
    for(string i : v) cout << i << " ";
    cout << endl;
    cout << "cnt : " << cnt1 << endl;
    cout << "is_palindrome_num : " << fac(cnt) << endl;
    cout << "is_Palindrome('abcdba') : " << is_Palindrome("abcdba") << endl; //验证回文数函数
    return 0;
}
unsigned long long fac(int n){
    if(n == 0) return 1;
    else return n * fac(n - 1);
}
bool is_Palindrome(string ss){
    stack<char> st;
    int len = (ss.length() % 2 ? (ss.length() / 2 + 1) : ss.length() / 2);
    for(int i = len; i < ss.length(); i++) st.push(ss[i]);
    for(int i = 0; i < len && !st.empty(); i++){
        if(ss[i] == st.top()) st.pop();
        else return false;
    }
    return true;
}

fac函数(用于计算阶乘):
#include <iostream>
unsigned long fac(int num){
    unsigned long sum = 1;
    if(num == 0) return 1;
    else return num*fac(num-1);  //递归
}

2. equal
equal检查两个序列是否相等

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {1, 2, 3};

    bool isEqual = equal(v1.begin(), v1.end(), v2.begin());
    //可控范围
    //需要 v1.size() 大于等于 v2.size(), 否则如果 v1 是 v2 的子序列，也会输出1(true)
    //为避免这种情况,还是写成标准形式equal(v1.begin(), v1.end(), v2.begin(), v2.end());

    cout << "Equal: " << boolalpha << isEqual << '\n';
    return 0;
}

equal 是一个标准库算法，用于比较两个范围内的元素是否相等, 它可以接受一个二元谓词作为参数，用于自定义比较方式
bool areEqual(int a, int b){return a == b;}// 二元谓词函数
bool result = equal(vec1.begin(), vec1.end(), vec2.begin(), areEqual);
equal_to 是一个标准库函数对象，用于比较两个对象是否相等, 通常用于需要函数对象的地方，例如 STL 容器的比较操作
bool result = equal(vec1.begin(), vec1.end(), vec2.begin(), equal_to<int>());

谓词, 是返回布尔值的可调用对象, 用于条件检查或比较
一元谓词, 接受一个参数; 二元谓词接受两个参数

3. lexicographical_compare
比较两个序列的字典顺序

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {1, 2, 4};

    bool result = lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());

    cout << "v1 < v2: " << result << '\n';
    //v1 < v2 返回 1；
    //v1 > v2 返回 0
    return 0;
}


4. max, min
返回两个值中的最大值或最小值

#include <iostream>
#include <algorithm>

int main() {
    cout << "Max: " << max(1, 2) << '\n';
    cout << "Min: " << min(1, 2) << '\n';

    return 0;
}


5. max_element, min_element
查找序列中的最大或最小元素

#include <iostream>
#include <algorithm>
#include <vector>

int main() 
{
    vector<int> v = {1, 5, 3};

    auto max_it = max_element(v.begin(), v.end());
    auto min_it = min_element(v.begin(), v.end());
    //注意无论是作用于 vector 还是 map，返回的都是一个迭代器

    cout << "Max element: " << *max_it << '\n';
    cout << "Min element: " << *min_it << '\n';
    //解引用迭代器（*iter）访问元素的值，而通过 -> 操作符可以直接访问元素的成员

    return 0;
}

例如(luogu/introduction_3/1598)
auto max_it = max_element(m.begin(), m.end(), 
    [](const pair<char, int> &a, const pair<char, int> &b){return a.second < b.second ;});

    max = max_it->second;
    //max_it 是一个指向 map 中元素的迭代器map 的元素类型是 pair<const Key, T>
    //所以 max_it 指向一个 pair要访问 pair 的 second 成员，你需要先解引用迭代器，这可以通过 -> 操作符实现

    /*for(auto &i : m)
    {
        max = max(max,i.second);
    }*/
实现相同目的,但 max_element 对 map 的处理需要多一个(第三个)参数,格式：[外部变量](待比较的参数){如何比较参数 ;}
注意得到的是指针,其他容器为 max = *max_it , map比较特殊为 max = max_it->second

6. clamp
将值限制在指定的范围内

#include <iostream>
#include <algorithm>

int main() {
    cout << "Clamped: " << clamp(5, 1, 10) << '\n'; // 5
    cout << "Clamped: " << clamp(-1, 1, 10) << '\n'; // 1
    return 0;
}

7. merge
合并两个有序序列

#include <iostream>
#include <algorithm>
#include <vector>

int main(){
    vector<int> v1 = {1, 3, 5};
    vector<int> v2 = {2, 4, 6};
    vector<int> result(v1.size() + v2.size());

    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), result.begin());
    //注意有5个参数
    //可以控制合并的范围，比如说merge(v1.begin() + 1, v1.end(), v2.begin() + 1, v2.end(), result.begin());
    //输出的就是3 4 5 6 0 0 

    for(int n : result) cout << n << ' ';
    //输出1 2 3 4 5 6 
    return 0;
}


8. inplace_merge
在原地合并两个有序序列

#include <iostream>
#include <algorithm>
#include <vector>

int main(){
    vector<int> v = {1, 3, 5, 2, 4, 6};
    // 假设前半部分和后半部分都已排序
    inplace_merge(v.begin(), v.begin() + 3, v.end());
    //注意有三个参数
    //只有3可以，因为只有以3为节点是两边的序列是有序的，写v.begin() + 2等等都不行
    for(int n : v) cout << n << ' ';
    //输出1 2 3 4 5 6 
    return 0;
}

9. includes
检查一个有序序列是否包含另一个序列

#include <iostream>
#include <algorithm>
#include <vector>

int main(){
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {2, 4};

    bool result = includes(v1.begin(), v1.end(), v2.begin(), v2.end());
    //注意是 includes 不是 include
    //可控范围

    cout << "Includes: " << result << '\n';
    //v1 包含 v2 输出 1, 否则输出 0

    return 0;
}

10. set_union, set_intersection, set_difference, set_symmetric_difference
对两个集合执行集合操作

#include <algorithm>
#include <iostream>
#include <vector>

int main(){
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {4, 5, 6, 7, 8};
    vector<int> result;

    // Union并集
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
    for(int &n : result) cout << n << " "; //输出1 2 3 4 5 6 7 8
    cout << "\n";
    result.clear();

    // Intersection交集
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
    for(int &n : result) cout << n << " "; //输出4 5
    cout << "\n";
    result.clear();

    // Difference差集(找出在 v1 中但不在 v2 中的元素)
    set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
    for(int &n : result) cout << n << " "; //输出1 2 3
    cout << "\n";
    result.clear();

    // Symmetric difference对称差集(找出仅出现在 v1 或 v2 中的元素)
    set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
    for(int &n : result) cout << n << " ";// //输出1 2 3 6 7 8
    cout << "\n";
    result.clear();

    // Result depends on the operation
    return 0;
}


11. lower_bound 和 upper_bound
这两个函数用于在已排序的序列中查找某个值的边界
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    vector<int> v = {1, 2, 4, 4, 5};
    auto lower = lower_bound(v.begin(), v.end(), 4);
    auto upper = upper_bound(v.begin(), v.end(), 4);
    //跟max_element 和 min_element 一样, 返回的是迭代器

    cout << "Lower bound for 4: " << (lower - v.begin()) << '\n';
    //2(下界是指不小于给定值的第一个元素的位置)

    cout << "Upper bound for 4: " << (upper - v.begin()) << '\n';
    //4(上界是指大于给定值的第一个元素的位置)

    return 0;
}


12. equal_range
同时获取 lower_bound 和 upper_bound
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    vector<int> v = {1, 2, 3, 3, 4, 5};
    auto range = equal_range(v.begin(), v.end(), 3);
    //不同于lower_bound()和upper_bound() 返回的是指针
    //range 是一个 pair 类型的对象，它包含两个成员：first 和 second，它们都是迭代器.
    //range 是一个 pair，其中 range.first 是指向第一个 3 的迭代器（lower_bound），
    //而 range.second 是指向第一个大于 3 的元素的迭代器（upper_bound）

    cout << "3 is found in the range [" << (range.first - v.begin()) << ", " << (range.second - v.begin()) << ")" << '\n';
    //因为 range 是一个对象，而不是指针，所以应该使用 . 操作符来访问这些成员

    return 0;
}

！！！！！总结：
使用 -> 当有一个指向对象的指针或类似于指针的迭代器，并且你需要访问该对象的成员
比如说 auto max_it = max_element(m.begin(), m.end(), 
    [](const pair<char, int> &a, const pair<char, int> &b){return a.second < b.second ;});

    max = max_it->second;
    //max_it 是一个指向 map 中元素的迭代器map 的元素类型是 pair<const Key, T>
    //所以 max_it 指向一个 pair要访问 pair 的 second 成员，你需要先解引用迭代器，这可以通过 -> 操作符实现
    //解引用迭代器（*iter）访问元素的值，而通过 -> 操作符可以直接访问元素的成员

使用 . 当你直接操作一个对象实例，并且需要访问它的成员
比如说 auto range = equal_range(v.begin(), v.end(), 3);
    //不同于lower_bound()和upper_bound() 返回的是指针
    //range 是一个 pair 类型的对象，它包含两个成员：first 和 second，它们都是迭代器.

    cout << "3 is found in the range [" << (range.first - v.begin()) << ", " << (range.second - v.begin()) << ")" << '\n';
    //因为 range 是一个对象，而不是指针，所以应该使用 . 操作符来访问这些成员


13. binary_search
检查序列中是否存在某个值

#include <iostream>
#include <vector>
#include <algorithm>
int main() {
    vector<int> v = {1, 2, 3, 4, 5};
    if (binary_search(v.begin(), v.end(), 3)) cout << "Found the element 3" << '\n';
    return 0;
}

关于 binary_search 和 find
binary_search 和 find 都可以用于查找元素，但它们的用法和效率有所不同

binary_search 用于有序序列
如果存在,则返回 true; 否则, 返回 false 
使用二分查找时间复杂度是 O(log n)

find 在无序或有序序列中都可以使用
如果找到,则返回一个指向该元素的迭代器;如果没有找到,则返回一个指向序列末尾的迭代器
时间复杂度是 O(n)

总的来说，
当序列是有序的，且你只需要检查元素是否存在（不需要知道具体位置）时，使用 binary_search 是更高效的选择
如果序列无序，或者需要元素的确切位置，应使用 find

14. sort 
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    vector<int> vec = {4, 2, 5, 1, 3};
    sort(vec.begin(), vec.end());
    for (int i : vec) cout << i << ' ';
    //输出 1 2 3 4 5
    return 0;
}

15. stable_sort
对序列进行稳定排序
#include <iostream>
#include <vector>
#include <algorithm>
int main(){
    vector<pair<int, char>> v = {{2, 'A'}, {1, 'B'}, {2, 'C'}, {1, 'D'}};
    // 使用自定义结构以展示稳定性
    stable_sort(v.begin(), v.end());
    //具有相等键值的元素在排序后将保持它们原始的顺序

    for (const auto &p : v) cout << p.second << ' ';
    //输出B D A C 
    return 0;
}

注意 vector<pair<int, char>> 和 map<int, char> 的区别

vector<pair<int, char>>
vector 是一个动态数组，可以存储任意类型的元素，包括 pair<int, char>
在这种用法中，每个 pair 存储一个整数和一个字符，类似于键值对，但没有任何内建的键到值的映射机制

适用场景:
当需要维护元素的插入顺序时
当可能有重复的键值时
当需要频繁地按序访问元素，而不是根据键查找时

#include <vector>
#include <utility> // for make_pair
#include <iostream>

int main(){
    vector<pair<int, char>> vec = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    // Adding a new pair
    vec.push_back(make_pair(4, 'd'));
    // Iterating over the vector and printing its content
    for (const auto& p : vec) cout << p.first << ": " << p.second << '\n';
}

map<int, char>
map 是一个基于红黑树实现的排序关联容器, 它存储的是键值对, 其中每个键唯一, 并且自动按键排序

适用场景:
当需要基于键快速查找、更新或删除元素时
当每个键必须是唯一的时
当你需要按键排序的键值对集合时

#include <map>
#include <iostream>

int main(){
    map<int, char> m = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    // Adding a new pair; if the key already exists, its value is updated
    m[4] = 'd'; // Inserting a new pair
    // Iterating over the map and printing its content (automatically sorted by key)
    for (const auto& p : m) cout << p.first << ": " << p.second << '\n';
}

!!比较和选择
选择 vector<pair<int, char>> 还是 map<int, char>，取决于你的具体需求：
如果需要保留元素的插入顺序，或者允许键重复，那么 vector<pair<int, char>> 可能是更好的选择
如果需要快速基于键的查找, 插入和删除，同时键是唯一且自动排序的，那么 map<int, char> 更适合

在性能方面,
map 的查找, 插入和删除操作通常是对数时间复杂度 O(log n)
vector 的查找是线性时间 O(n) ,

插入和删除(特别是在向量中间)可能需移动元素
map 也是线性时间复杂度
vector 的顺序访问速度更快,因为它在内存中连续存储

16. partial_sort
部分排序序列,使前n个元素为已排序的最小元素

#include <iostream>
#include <vector>
#include <algorithm>
int main(){
    vector<int> v = {5, 2, 3, 4, 1};

    partial_sort(v.begin(), v.begin() + 3, v.end());
    //第一个参数 v.begin() 指定要排序的范围的起始迭代器
    //第二个参数 v.begin() + 3 指定范围内要排序的最后一个元素的下一个位置也就是说，这个位置之前的元素将被排序
    //第三个参数 v.end() 指定要排序的范围的结束迭代器

    for (int n : v) cout << n << ' ';
    //输出1 2 3 5 4 
    return 0;
}

!!!!partial_sort 和 inplace_merge 比较

操作对象:
partial_sort 对原始序列的一部分进行排序,使之成为整个序列中最小的元素
inplace_merge 则假设你有两个已排序的序列，需要将它们合并成一个有序序列

用途:
partial_sort 适用于需要找到 "前 k 个 "最小元素的场景
而 inplace_merge 用于合并操作，特别是在归并排序中


17. nth_element
重新排列序列,以使得第n个元素处于其最终排序完成后的位置

#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    vector<int> v = {5, 2, 3, 4, 1, 6};
    nth_element(v.begin(), v.begin() + 3, v.end());
    cout << "The fourth smallest element is " << v[3] << '\n';
    return 0;
}


!!!partial_sort 和 nth_element比较 
目的和结果:
partial_sort 使得前 N 个元素按排序顺序排列，
而 nth_element 只保证第 N 个元素位于其在完全排序序列中的正确位置，不保证其他元素的顺序

性能:
对于其特定任务,nth_element 通常比 partial_sort 更高效，因为它不需要对除了第 N 个元素以外的任何元素进行排序
当只关心单个元素的最终位置时,nth_element 是更好的选择

选择指南：
如果你的目标是找到并排序序列中最小（或最大）的 N 个元素，使用 partial_sort
如果你只需要找到位于序列特定位置（如中位数）的元素，而不关心序列的其他部分是否有序，使用 nth_element

18. copy_n
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    vector<int> v = {1, 2, 3, 4, 5};
    vector<int> dest = {1, 3, 4, 6, 2, 4};
    copy_n(v.begin(), 3, dest.begin());
    for (int n : dest) cout << n << ' ';
    //输出1 2 3 6 2 4
    copy_n(v.begin(), 3, back_inserter(dest));
    //三个参数
    for (int n : dest) cout << n << ' ';
    //输出1 2 3 6 2 4 1 2 3
    return 0;
}

19. copy_if
从 C++11 开始,copy_if 允许从一个容器复制满足特定条件的元素到另一个容器

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
int main(){
    vector<int> src = {1, 2, 3, 4, 5, 6};
    vector<int> dest;
    copy_if(src.begin(), src.end(), back_inserter(dest),[](int x){ return x % 2 == 0; });// 四个参数, 复制偶数
    for (int val : dest) cout << val << " ";
    cout << endl;
    // 输出: 2 4 6
    copy_if(src.begin(), src.end(), inserter(dest, dest.begin()),[](int x){ return x % 2 == 0; });
    for (int val : dest) cout << val << " ";
    cout << endl;
    // 输出: 2 4 6 2 4 6
    //错误写法，vector不支持前端插入
    copy_if(src.begin(), src.end(), front_inserter(dest), [](int x){ return x % 2 == 1;});
    for(int val : dest) cout << val << " ";
    cout << endl;
    return 0;
}
!!!若正序复制用 back_inserter  若需要倒序复制另当别论

!!!!front_inserter 更适合 list 或 deque 这样的容器,这些容器支持高效的前端插入操作

而对于 vector 而言,
可以先 copy 或者 copy_if, 然后再使用 reverse 反转dest容器
或用 inserter(v, v.begin())

20. move
移动元素到另一个位置

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
int main(){
    vector<string> src = {"one", "two", "three"};
    vector<string> dest(3);
    move(src.begin(), src.end(), dest.begin());
    for (const auto& s : dest) cout << s << ' ';
    cout << endl;
    for (const auto& s : src) cout << s << ' '; //移动算法
    cout << endl;
    return 0;
}

21. transform 
transform 对容器中的每个元素应用给定的函数，并将结果存储在另一个容器中

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <string>
using namespace std;
int main(){
    vector<int> src = {1, 2, 3, 4, 5};
    vector<int> dest(src.size());
    transform(src.begin(), src.end(), dest.begin(),[](int x){ return pow(x, 2); }); 
    //transform 对容器中的每个元素应用给定的函数，并将结果存储在另一个容器中
    for (int val : dest) cout << val << " ";
    cout << endl;
    //输出: 1 4 9 16 25
    for (int val : src) cout << val << " "; //复制算法
    cout << endl;
    string s;
    cin >> s;
    transform(s.begin(), s.end(), s.begin(), [](char ch){ return tolower(ch);});
    //将原字符串转换为小写
    cout << s;
    return 0;
}

22. swap & iter_swap

#include <algorithm>
#include <iostream>
#include <vector>

int main(){
    int a = 5, b = 10;
    swap(a, b); // 交换两个变量的值
    cout << "a: " << a << ", b: " << b << '\n';
    vector<int> v = {1, 2, 3, 4};
    iter_swap(v.begin(), v.begin() + 2); // 使用迭代器交换元素
    for (int n : v) cout << n << ' ';
    //输出 3 2 1 4
    cout << '\n';
}

23. fill & fill_n
#include <algorithm>
#include <vector>
#include <iostream>
int main(){
    vector<int> v(5); // 向量要有初始长度
    fill(v.begin(), v.end(), 1); // 将1填充到整个向量中
    for (int n : v) cout << n << ' ';
    cout << '\n';
    fill_n(v.begin(), 3, 2); // 只填充前3个元素为2
    for (int n : v) cout << n << ' ';
    cout << '\n';
}

24. generate & generate_n
#include <algorithm>
#include <vector>
#include <iostream>
int main(){
    vector<int> v(5);
    int current = 1;
    generate(v.begin(), v.end(), [&current]() { return current *= 2; });
    //[外部变量](参数列表){}
    // 用生成器函数填充，每次值翻倍
    // 注意是&current
    for (int n : v) cout << n << ' ';
    cout << '\n';
}

25. replace & replace_if
#include <algorithm>
#include <vector>
#include <iostream>
int main(){
    vector<int> v = {1, 2, 3, 4, 5};
    replace(v.begin(), v.end(), 3, 8); // 将3替换为8, 就地算法
    for (int n : v) cout << n << ' ';
    //输出1 2 8 4 5
    cout << '\n';
    replace_if(v.begin(), v.end(), [](int n) { return n % 2 == 0; }, 10); // 将偶数替换为10
    for (int n : v) cout << n << ' '; //输出1 10 10 10 5
    cout << '\n';
}

26. all_of, any_of, none_of 
#include <algorithm>
#include <iostream>
#include <vector>
//不改序列
int main(){
    vector<int> v = {2, 4, 6, 8, 10};
    bool allEven = all_of(v.begin(), v.end(), [](int i) { return i % 2 == 0; });
    cout << "All are even: " << allEven << '\n';
    bool anyEven = any_of(v.begin(), v.end(), [](int i) { return i % 2 == 0; });
    cout << "Any is even: " << anyEven << '\n';
    bool noneEven = none_of(v.begin(), v.end(), [](int i) { return i % 2 == 0; });
    cout << "None are even: " << noneEven << '\n';
}

27. for_each
#include <algorithm>
#include <vector>
#include <iostream>

int main(){
    vector<int> v = {1, 2, 3, 4, 5};
    for_each(v.begin(), v.end(), [](int& n) { n *= 2; }); // 对每个元素执行函数，不改
    for (int n : v) cout << n << ' ';
    cout << '\n';
}

28. count & count_if

统计在给定范围内等于某个值的元素的数量
它可以用于任何容器，如 vector, list, array, string 等
#include <algorithm>
#include <vector>
#include <iostream>
//不改序列
int main(){
    vector<int> v = {1, 2, 3, 4, 5, 2};
    int count2 = count(v.begin(), v.end(), 2); // 计算值为2的元素数量
    cout << "Count of 2: " << count2 << '\n';
    int countEven = count_if(v.begin(), v.end(), [](int n) { return n % 2 == 0; });
    // 计算偶数的数量
    cout << "Count of even numbers: " << countEven << '\n';
}


29. mismatch
#include <algorithm>
#include <vector>
#include <iostream>
//不改序列
int main(){
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {1, 2, 0, 4, 5};

    auto mismatch_pair = mismatch(v1.begin(), v1.end(), v2.begin());

    if (mismatch_pair.first != v1.end())
        cout << "First mismatch: " << *mismatch_pair.first << " and " << *mismatch_pair.second << '\n';
        //输出不匹配的元素
        //cout << mismatch_pair.first - v1.begin() << " " << mismatch_pair.second - v2.begin();
        //输出不匹配的元素位置
    else cout << "No mismatch\n";
    //输出First mismatch: 3 and 0
}


30. find, find_if, find_if_not
#include <algorithm>
#include <vector>
#include <iostream>
//不改序列
int main(){
    vector<int> v = {1, 2, 3, 4, 5};

    auto it = find(v.begin(), v.end(), 3);

    if (it != v.end()) cout << "Found 3 at position " << (it - v.begin()) << '\n';
    //输出Found 3 at position 2

    it = find_if(v.begin(), v.end(), [](int n) { return n % 2 == 0; });

    if (it != v.end()) cout << "Found even number: " << *it << '\n';
    //输出Found even number: 2

    it = find_if_not(v.begin(), v.end(), [](int n) { return n % 2 == 0; });

    if (it != v.end()) cout << "Found odd number: " << *it << '\n';
    //输出Found odd number: 1
}

31. unique 和 erase 结合使用
unique 函数模板用于重新排列容器中的元素,使得每个元素只出现一次,
删除的是连续重复元素的多余部分,而不是所有重复的元素.
它仅移除相邻重复元素,留下每组相邻重复元素中的第一个元素
为了从容器中彻底移除这些重复的元素,需要与容器的 erase 方法结合使用,这种结合被称为“擦除-删除”惯用法

#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    vector<int> vec = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 1, 1};

    auto last = unique(vec.begin(), vec.end());
    // unique 仅将连续的重复元素中的多余部分移动到向量的末尾

    vec.erase(last, vec.end());
    // 使用 erase 移除向量末尾的所有重复元素

    //可以合起来写 vec.erase(unique(vec.begin(), vec.end()), vec.end())

    for (int num : vec) cout << num << " ";
    //输出结果为：1 2 3 4 5 1
    cout << "\n";

    return 0;
}
注意到最后的两个 1 没有被视为重复，因为 unique 只处理相邻的重复元素

32. remove() 和 remove_if()

remove 从序列中移除所有等于指定值的元素
它并不真正从容器中删除元素，而是将不应被移除的元素移到序列的开始位置, because remove()是一个STL函数不是STL方法
然后返回一个指向"新序列"末尾的迭代器,与 erase 方法结合使用时,它可以实现真正的元素移除
remove_if 类似于 remove,但它允许指定一个谓词(predicate)函数来决定哪些元素应该被移除

使用 remove
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;
int main(){
    vector<int> vec = {1, 2, 3, 4, 5, 2, 2, 3};
    auto last = remove(vec.begin(), vec.end(), 2); // 移除所有等于2的元素
    vec.erase(last, vec.end());
    //可以合起来写vec.erase(remove(vec.begin(), vec.end(), value), vec.end());
    for (int num : vec) cout << num << " ";
    //输出结果为：1 3 4 5 3
    cout << "\n";

    vector<int> vec = {1, 2, 3, 4, 5, 2, 2, 3};
    //vec.remove(2); //错误， vector没有 remove 成员函数（只有 list 有）

    list<int> l = {1, 2, 3, 4, 5, 2, 2, 3};
    auto last = remove(l.begin(), l.end(), 2); // 移除所有等于2的元素
    l.erase(last, l.end());
    //可以合起来写l.erase(remove(l.begin(), l.end(), value), l.end());
    for (int num : l) cout << num << " ";
    //输出结果为：1 3 4 5 3
    cout << "\n";

    l = {1, 2, 3, 4, 5, 2, 2, 3};
    l.remove(2);
    for (int num : l) cout << num << " ";
    //输出结果为：1 3 4 5 3
    cout << "\n";
    return 0;
}


使用 remove_if
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8};
    auto last = remove_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });//移除所有偶数元素
    vec.erase(last, vec.end());
    //可以合起来写vec.erase(remove_if(vec.begin(), vec.end(), predicate), vec.end())
    for (int num : vec) cout << num << " ";
    //输出结果为：1 3 5 7
    cout << "\n";

    return 0;
}


综合运用：
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;
char toUpper(char c){ return toupper(c);}
string& ToUpper(string &s){ 
    //for(char &i : s) toupper(i); 
    transform(s.begin(), s.end(), s.begin(), toUpper);
    return s;
}
int main(){
    vector<string> v;
    string s;
    while(cin >> s && s != "quit") v.push_back(s);
    set<string> se;
    transform(v.begin(), v.end(), inserter(se, se.begin()), ToUpper);//移动
    for(string i : se) cout << i << " ";
    cout << endl;
    map<string, int> m;
    for(string i : se) m[i] = count(se.begin(), se.end(), i);
    for(auto i : m) cout << i.first << " " << i.second << endl;
    cout << endl;
    return 0;
}






