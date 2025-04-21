# 排序算法

## 一、概述

#### 1. 内部排序

(1) [冒泡排序](#1-冒泡排序)

(2) [选择排序](#2-选择排序)

[a. 简单选择排序](#1-简单选择排序)

[b. 堆排序](#2-堆排序)

(3) [插入排序](#3-插入排序)

[a. 直接插入排序](#1-直接插入排序)

[b. 希尔排序](#2-希尔排序)

(4) [快速排序](#4-快速排序)

[快速排序 hoare 版本](#1快速排序-hoare-版本)

[快速排序挖坑法](#2快速排序挖坑法)

[优化一随机化快速排序](#1优化一随机化快速排序)

[优化二中位数三分法](#2-优化二中位数三分法)

(5) [归并排序](#5-归并排序)

(6) [基数排序](#5-归并排序)

![1](https://www.runoob.com/wp-content/uploads/2019/03/sort.png)
   
#### 2. 外部排序

外部归并排序、置换选择排序、多路归并等 这里不做涉及

---

## 二、排序算法代码详解



### 一、 内部排序

---

#### 1. 冒泡排序

![`](https://i-blog.csdnimg.cn/blog_migrate/c13373922b3862f43cd7e444c78176aa.gif)

通过反复比较相邻元素并交换来将最大元素“冒泡”到数组末尾

        时间复杂度：

            最坏情况：O(n²)

            最佳情况：O(n)（当数组已排序时）

            平均情况：O(n²)

        空间复杂度：O(1)（原地排序）

            稳定性：稳定

##### 代码实现

```cpp

// bubbleSort 优化前
void bubbleSort(vector<int> &v)
{
  int n = v.size();
  for (int i = 0; i < n; i++)           // 控制比较次数
    for (int j = 0; j < n - i - 1; j++) // 遍历数组
      if (v[j] > v[j + 1])
        swap(v[j], v[j + 1]);
}

// bubbleSort 优化后
// 若后续序列已经有序，算法直接退出
void bubbleSort_Optimize(vector<int> &v)
{
  int n = v.size();
  for (int i = 0; i < n; i++)
  {
    int flag = 0;
    for (int j = 0; j < n - i - 1; j++)
      if (v[j] > v[j + 1])
        swap(v[j], v[j + 1]), flag = 1;
    if (!flag)
      break; // 若某一轮没有经过交换，说明后续序列已经有序，算法直接退出
  }
}

```

---

#### 2. 选择排序

##### (1) 简单选择排序

![1](https://i-blog.csdnimg.cn/blog_migrate/be071b4b7b61a7d9b746b75d7ec3e0c7.gif)

每次从未排序部分选择最小（或最大）元素，放入已排序部分的开始（末尾）

        时间复杂度：

            最坏情况：O(n²)

            最佳情况：O(n²)

            平均情况：O(n²)

        空间复杂度：O(1)（原地排序）

            稳定性：不稳定

###### 代码实现

```cpp

void selectionSort(vector<int> &v)
{
  int n = v.size();
  for (int i = 0; i < n; i++)
  {
    int minId = i;
    // 遍历未排序部分，找到最小（或最大）元素的下标
    for (int j = i + 1; j < n; j++)
      if (v[j] < v[minId])
        minId = j;
    swap(v[minId], v[i]);
  }
}
```

##### (2) 堆排序

注意：实际中并没有删除堆中元素，图中为了方便表示，将交换后的位置画成了空

![1](https://i-blog.csdnimg.cn/blog_migrate/6b8296d2edd78b26f8ae4ba47e19cfb5.gif)

        这里将所有元素后移时下标从 1 开始

        将待排序的序列构造成一个大顶堆（从后往前调整所有非终端节点（i <= len / 2）），然后将堆顶元素与末尾元素交换，然后将剩余未排序元素重新构造成一个大顶堆（小元素下坠），如此反复(len - 1 次)，直到整个序列有序

        大根堆排序为升序，小根堆排序为降序

        三步：（1）建堆 ———— （2）交换元素 ———— （3）维护堆（重复执行 VertexNum - 1 次）

        时间复杂度：

            最坏情况：O(n log n)

            最佳情况：O(n log n)

            平均情况：O(n log n)

        空间复杂度：O(1)（原地排序）

            稳定性：不稳定

---

###### 1）大根堆排正序

```cpp

void MaxHeap_Down_Adjust(vector<int> &MaxHeap, int k, int Unsort_VertexNum)
{
  // 第三个参数是边界！！！表示每次未排序的节点个数，堆的大小边界
  MaxHeap[0] = MaxHeap[k]; // 由于下标移动后从 1 开始，用第 0 位保存当前根节点
  // 维护堆（小元素下坠）
  for (int i = k * 2; i <= Unsort_VertexNum; i *= 2)
  {
    // 找左右子节点中更大的值去替换当前根节点，移动根节点下标
    //（先判断要判断的下标是否合法 ———— CurrentIndex <= VertexNum）
    if (i + 1 <= Unsort_VertexNum && MaxHeap[i + 1] > MaxHeap[i])
      i++;
    // 当前判断的节点大于其左右子节点，则已经满足大根堆，不需要调整直接退出
    if (MaxHeap[0] >= MaxHeap[i])
      break; 
    // 此时当前判断的节点已被 MaxHeap[0] 保存，所以 v[k] 空出，用左右子节点中更大的值去替换，移动根节点下标
    else
      MaxHeap[k] = MaxHeap[i], k = i; 
    // 空出的做法类比快速排序中根据 pivot 分区的过程
  }
  MaxHeap[k] = MaxHeap[0];
}

void MaxHeapBuild(vector<int> &MaxHeap)
{
  int VertexNum = MaxHeap.size() - 1;
  // 从最后一个非叶子结点开始：下标为 [len / 2](向下取整用整数除法代替)
  for (int i = VertexNum >> 1; i >= 1; i--)
    MaxHeap_Down_Adjust(MaxHeap, i, VertexNum);
}

void VIndexAdjust(vector<int> &Heap)
{
  Heap.insert(Heap.begin(), 0);
}

void MaxHeapSort(vector<int> &MaxHeap)
{
  // 调整下标为 1 开始（所有元素整体后移一位）
  VIndexAdjust(MaxHeap);

  //（1） 建堆
  MaxHeapBuild(MaxHeap);

  int VertexNum = MaxHeap.size() - 1;
  for (int i = VertexNum; i > 1; i--)
  {
    //（2） 交换元素：将堆顶元素（v[1]）与当前末尾元素（v[i]）交换
    swap(MaxHeap[1], MaxHeap[i]);

    //（3）维护堆：将剩余未排序元素（i - 1）(VertexNum - (i - 1) 个元素已排序)重新构造成一个大顶堆
    // swap 前有 VertexNum - i 个元素已排好序，swap 后已排序的元素个数加 1，开始本轮堆的维护
    MaxHeap_Down_Adjust(MaxHeap, 1, i - 1); // 调整堆时传入的 VertexNum 为 Unsort_VertexNum，
  }
  // 删除哨兵节点，恢复原数组长度
  MaxHeap.erase(MaxHeap.begin());
}

```

###### 2）小根堆排逆序

```cpp

void MinHeap_Down_Adjust(vector<int> &MinHeap, int k, int Unsort_VertexNum)
{
  MinHeap[0] = MinHeap[k];
  for (int i = k * 2; i <= Unsort_VertexNum; i *= 2)
  {
    if (i + 1 <= Unsort_VertexNum && MinHeap[i + 1] < MinHeap[i])
      i++;
    if (MinHeap[0] <= MinHeap[i])
      break;
    else
      MinHeap[k] = MinHeap[i], k = i;
  }
  MinHeap[k] = MinHeap[0];
}

void MinHeapBuild(vector<int> &MinHeap)
{
  int VertexNum = MinHeap.size() - 1;
  for (int i = VertexNum >> 1; i >= 1; i--)
    MinHeap_Down_Adjust(MinHeap, i, VertexNum);
}

void VIndexAdjust(vector<int> &Heap)
{
  Heap.insert(Heap.begin(), 0);
}

void MinHeapSort(vector<int> &MinHeap)
{
  VIndexAdjust(MinHeap);
  MinHeapBuild(MinHeap);
  int VertexNum = MinHeap.size() - 1;
  for (int i = VertexNum; i > 1; i--)
  {
    swap(MinHeap[1], MinHeap[i]);
    MinHeap_Down_Adjust(MinHeap, 1, i - 1); 
  }
 
  MinHeap.erase(MinHeap.begin());
}
```

---

###### 堆模拟插入和删除过程

---

（1）利用大根堆模拟插入和删除过程

---

```cpp

void MaxHeap_Up_Adjust(vector<int> &MaxHeap, int k, int VertexNum)
{
  // 过程类比 MaxHeap_Down_Adjust；不同点：当前节点 k 只有一个父节点(k >> 1)，不用 i++;
  MaxHeap[0] = MaxHeap[k];
  for (int i = k >> 1; i >= 1; i >>= 1)
  {
    if (MaxHeap[i] >= MaxHeap[0])
      break;
    else
      MaxHeap[k] = MaxHeap[i], k = i;
  }
  MaxHeap[k] = MaxHeap[0];
  // 其实可以变得更优雅 ......
  // while(k >= 1 && MaxHeap[k >> 1] < MaxHeap[k]) swap(MaxHeap[k], MaxHeap[k >> 1]), k /= 2;
}

// 末尾插入新元素，新元素上浮
void MaxHeapInsert(vector<int> &MaxHeap, int val)
{
  // 这两句一般是冗余的，这里只是为了确保后续操作是对下标从 1 开始的最大堆进行的（如果已知传进来的是确定下标的最大堆则无需这两句代码）
  VIndexAdjust(MaxHeap);
  MaxHeapBuild(MaxHeap);
  // cout << "After MaxHeapBuild（now 0 position is invaild）:\n";
  // printVector(MaxHeap);

  MaxHeap.push_back(val);
  int VertexNum = MaxHeap.size() - 1, k = VertexNum;
  MaxHeap_Up_Adjust(MaxHeap, k, VertexNum);

  // 删除哨兵节点，恢复原数组长度（insert 长度加 1）
  MaxHeap.erase(MaxHeap.begin());
}

// 删除新元素(交换待删除元素和末尾元素，pop_back()) ———— 判断交换到 pos 的末尾元素与其当前位置父节点的大小，决定是上浮还是下沉
void MaxHeapDelete(vector<int> &MaxHeap, int pos)
{
  //......
  VIndexAdjust(MaxHeap);
  MaxHeapBuild(MaxHeap);
  // cout << "After MaxHeapBuild（now 0 position is invaild）:\n";
  // printVector(MaxHeap);

  int VertexNum = MaxHeap.size() - 1, parent = pos / 2, lc = pos * 2, rc = pos * 2 + 1;
  MaxHeap[pos] = MaxHeap[VertexNum], MaxHeap.pop_back(), VertexNum--;
  if (parent >= 1 && MaxHeap[parent] < MaxHeap[pos])
    MaxHeap_Up_Adjust(MaxHeap, pos, pos);
  // 逻辑冗余：这里的 if 条件检查其实在 MaxHeap_Down_Adjust 中存在，只需根据父节点的值判断是上浮还是下调即可
  // else if(lc <= VertexNum){
  //     if(rc <= VertexNum && MaxHeap[pos] < max(MaxHeap[lc], MaxHeap[rc]) || rc > VertexNum && MaxHeap[pos] < MaxHeap[lc]) MaxHeap_Down_Adjust(MaxHeap, pos, VertexNum - pos);
  // }
  else
    MaxHeap_Down_Adjust(MaxHeap, pos, VertexNum); // 使用 VertexNum 而不是 VertexNum - pos 是为了传递堆的大小边界

  // 删除哨兵节点，恢复原数组长度（delete 长度减 1）
  MaxHeap.erase(MaxHeap.begin());
}

```

---

（2）利用小根堆模拟插入和删除过程

---

```cpp

void MinHeap_Up_Adjust(vector<int> &MinHeap, int k, int VertexNum)
{
  MinHeap[0] = MinHeap[k];
  for (int i = k >> 1; i >= 1; i >>= 1)
  {
    if (MinHeap[i] <= MinHeap[0])
      break;
    else
      MinHeap[k] = MinHeap[i], k = i;
  }
  MinHeap[k] = MinHeap[0];
  // 其实一样可以变得更优雅 ......
  // while(k >= 1 && MaxHeap[k >> 1] > MaxHeap[k]) swap(MaxHeap[k], MaxHeap[k >> 1]), k /= 2;
}

void MinHeapInsert(vector<int> &MinHeap, int val)
{
  // 这两句一般是冗余的，这里只是为了确保后续操作是对下标从 1 开始的最大堆进行的（如果已知传进来的是确定下标的最大堆则无需这两句代码）
  VIndexAdjust(MinHeap);
  MinHeapBuild(MinHeap);
  // cout << "After MinHeapBuild（now 0 position is invaild）:\n";
  // printVector(MinHeap);

  MinHeap.push_back(val);
  int VertexNum = MinHeap.size() - 1, k = VertexNum;
  MinHeap_Up_Adjust(MinHeap, k, VertexNum);

  // 删除哨兵节点，恢复原数组长度（insert 长度加 1）
  MinHeap.erase(MinHeap.begin());
}

void MinHeapDelete(vector<int> &MinHeap, int pos)
{
  //......
  VIndexAdjust(MinHeap);
  MinHeapBuild(MinHeap);
  // cout << "After MinHeapBuild（now 0 position is invaild）:\n";
  // printVector(MinHeap);

  int VertexNum = MinHeap.size() - 1, parent = pos / 2, lc = pos * 2, rc = pos * 2 + 1;
  MinHeap[pos] = MinHeap[VertexNum], MinHeap.pop_back(), VertexNum--;
  if (parent >= 1 && MinHeap[parent] > MinHeap[pos])
    MinHeap_Up_Adjust(MinHeap, pos, pos);
  else
    MinHeap_Down_Adjust(MinHeap, pos, VertexNum);

  // 删除哨兵节点，恢复原数组长度（delete 长度减 1）
  MinHeap.erase(MinHeap.begin());
}

```

---

#### 3. 插入排序

    
##### (1) 直接插入排序  

![1](https://i-blog.csdnimg.cn/blog_migrate/4e9085c78edb1fdee471165b19e0cc05.gif)

将数组分为已排序和未排序部分，逐步将未排序的元素插入到已排序部分的适当位置

        时间复杂度：
        
            最坏情况：O(n²)
            最佳情况：O(n)
            平均情况：O(n²)
        
        空间复杂度：O(1)（原地排序）
        
            稳定性：不稳定

###### 1）不带哨兵

```cpp

void InsertionSort_Without_SentinelNode(vector<int> &v)
{
  int n = v.size();
  for (int i = 1; i < n; i++)
  {
    // 此轮不符合插入条件（当前元素已经大于左边已排序元素），直接进行下一轮
    if (v[i] >= v[i - 1])
      continue;

    int temp = v[i], j;
    // 注意这里 for 循环内部千万不要再定义一遍 j ！！！在内层 for 循环中再定义 j，将导致外层 j 的值不会被更新，无法正确地插入元素，最终导致逻辑错误
    for (j = i - 1; j >= 0 && v[j] > temp; j--)
      v[j + 1] = v[j]; // 移动元素
    v[j + 1] = temp;
  }
}

```

###### 2）带哨兵

```cpp

void InsertionSort_With_SentinelNode(vector<int> &v)
{
  int n = v.size();
  VIndexAdjust(v);

  for (int i = 2; i <= n; i++)
  {
    if (v[i] >= v[i - 1])
      continue;

    v[0] = v[i]; //v[0] 哨兵节点
    int j;
    
    for (j = i - 1; v[j] > v[0]; j--)
      v[j + 1] = v[j]; 
    v[j + 1] = v[0];
  }
  v.erase(v.begin());
}

```

###### 3）折半查找优化插入排序

```cpp

// 先用折半查找找到应该插入的位置后再移动元素
// 用折半查找优化（减少元素移动次数（虽然时间复杂度不变还是 O(n ^ 2）；保持稳定性）
void InsertionSort_Optimize(vector<int> &v)
{
  int n = v.size();
  VIndexAdjust(v);
  for (int i = 2; i <= n; i++)
  {
    // 此轮不符合插入条件（当前元素已经大于左边已排序元素），直接进行下一轮
    if (v[i] >= v[i - 1])
      continue;

    v[0] = v[i];
    int l = 0, r = i - 1;
    // 终止条件为 l > r (即 l = r + 1)，r 为其插入位置下界， l 为其插入位置上界
    /*
    双指针过程类比（插入排序折半查找优化；二分查找；快速排序找枢轴元素）

   （1）终止条件

        折半查找优化和二分查找： l > r ———— 当 l = r + 1 时，
        
            二分查找终止循环，未找到目标；
            插入排序折半查找找到插入上界和下界，插入 l 所指位置

        快速排序找枢轴元素：l == r ———— 当 l == r 时，
        
            找到枢轴元素（从第二轮开始 ———— 第一轮一般随机找或者用中位数三分法找）

    (2) 对于相等条件的处理

        折半查找优化：为保证算法的稳定性，找到相等的元素时继续再其右边寻找插入位置

        二分查找：找到目标

        快速排序找枢轴元素：找到目标

    (3) 序列是否有序

        折半查找优化和二分查找：针对有序序列（通过 mid ———— 找目标元素或位置）

        快速排序：针对无序序列（通过 l++, r-- ———— 分区）
    */

    while (l <= r)
    {
      // int mid = l + (r - l) / 2;
      // int mid = l + (r - l) >> 1; 不正确
      // ！！！ '+'的优先级大于'>>' ！！！！！
      int mid = l + ((r - l) >> 1);
      
      if (v[0] < v[mid])
        r = mid - 1;
      else
        l = mid + 1; // 为保证算法的稳定性，找到相等的元素时继续再其右边寻找插入位置
    }
    for (int j = i - 1; j >= l; j--)
      v[j + 1] = v[j];
    v[l] = v[0];
  }
  // 删除哨兵节点，恢复原数组长度
  v.erase(v.begin());
}

```

##### (2) 希尔排序

![1](https://i-blog.csdnimg.cn/blog_migrate/420f5c5abac4bb459aaee2f95aaaf35f.gif)

希尔排序是一种改进的插入排序，通过将元素分组并对每个组进行插入排序，逐步减少组的大小，最终实现整体排序。

核心思想：“局部有序可以促进整体有序”

        时间复杂度：

            最坏情况：O(n²)（依赖于增量的选择）

            平均情况：O(n log n)（具体性能依赖于增量序列）

            最佳情况：O(n)（当数组已经有序时）

        空间复杂度：O(1)（原地排序）
            
            稳定性：不稳定（因为在插入过程中可能会移动相同的元素）

```cpp

void shellSort(vector<int> &v)
{
  int n = v.size();
  v.insert(v.begin(), 0);

  // 将整个数组视为多个子数组，通常选择一个较大的增量（如数组长度的一半），并逐步减小增量
  for (int d = n >> 1; d > 0; d >>= 1)
  {
    for (int i = d + 1; i <= n; i++)
    {
      v[0] = v[i];
      int j;
      // 注意添加边界条件 j >= 1 ！！！，不然会越界访问，且如果 v[0] 比所有元素都小，j 会减到负数，因为没有 j >= 1 的限制，会导致死循环
      for (j = i - d; j >= 1 && v[j] > v[0]; j -= d)
        v[j + d] = v[j];
      v[j + d] = v[0];
    }
  }
  v.erase(v.begin());
}

```

#### 4. 快速排序

选择一个“基准”元素，将数组分为两部分：小于基准的和大于基准的。递归地对这两部分进行排序。

        时间复杂度：

            最坏情况：O(n²)（当数组已排序或逆序时）(二叉树树高最高时)
            平均情况：O(n log n)
            最佳情况：O(n log n)
        
        空间复杂度：O(log n)（递归栈的空间）（含有 n 个节点的二叉树的高度）
        
            稳定性：不稳定

---

##### （1）快速排序 hoare 版本

![1](https://i-blog.csdnimg.cn/blog_migrate/4d9e05d79724d6636efa8c0509c57415.gif)

```cpp

int Partition(vector<int> &v, int l, int r)
{
  int pivot = l;
  // 终止条件 l == r；找到枢轴元素
  while (l < r)
  {
    // 选左边为基准值，右指针先走
    while (l < r && v[r] >= pivot_key)
      r--;
    while (l < r && v[l] <= pivot_key)
      l++;
    swap(v[r], v[l]);
  }
  swap(v[l], v[pivot])

  return l;
}

// 类似于前序遍历的二叉树
void QuickSort(vector<int> &v, int l, int r)
{
  if (l >= r)
    return;
  int pivot = Partition(v, l, r);
  QuickSort(v, l, pivot - 1);
  QuickSort(v, pivot + 1, r);
}

void QuickSort_With_Optimize(vector<int> &v, int l, int r)
{
  if (l >= r)
    return;
  if (r - l < 20)
  {
    InsertionSort_Optimize(v);
    return;
  }
  int pivot = Partition(v, l, r);
  QuickSort(v, l, pivot - 1);
  QuickSort(v, pivot + 1, r);
}

```


##### （2）快速排序挖坑法

![1](https://i-blog.csdnimg.cn/blog_migrate/41634b27110105ad2f4ba59692e4dfec.gif)

```cpp

int Partition(vector<int> &v, int l, int r)
{
  int pivot_key = v[l];
  // 终止条件 l == r；找到枢轴元素
  while (l < r)
  {
    // 注意！！！写while 不是 if
    while (l < r && v[r] >= pivot_key)
      r--;
    v[l] = v[r];
    while (l < r && v[l] <= pivot_key)
      l++;
    v[r] = v[l];
  }
  v[l] = pivot_key;
  return l;
}

// 类似于前序遍历的二叉树
void QuickSort(vector<int> &v, int l, int r)
{
  if (l >= r)
    return;
  int pivot = Partition(v, l, r);
  QuickSort(v, l, pivot - 1);
  QuickSort(v, pivot + 1, r);
}

void QuickSort_With_Optimize(vector<int> &v, int l, int r)
{
  if (l >= r)
    return;
  if (r - l < 20)
  {
    InsertionSort_Optimize(v);
    return;
  }
  int pivot = Partition(v, l, r);
  QuickSort(v, l, pivot - 1);
  QuickSort(v, pivot + 1, r);
}

```

---

##### （3）优化的快速排序

---

###### 1）优化一：随机化快速排序

```cpp

int randomizedPartition(vector<int> &v, int l, int r)
{
  // int pivot_key = v[l]; //选 v[l] 为基准元素，则 v[l] 位置空出来，所以先从 r-- 开始遍历
  int pivot = l + rand() % (r - l + 1); // 随机选择枢纽
  swap(v[pivot], v[l]);                 // 将随机选择的枢纽移到 l 处，其他做法不变

  int pivot_key = v[l];

  while (l < r)
  {
    while (l < r && v[r] >= pivot_key)
      r--;
    v[l] = v[r];
    while (l < r && v[l] <= pivot_key)
      l++;
    v[r] = v[l];
  }
  v[l] = pivot_key; // 将枢轴元素放回最终位置
  return l;
}

// 类似于前序遍历的二叉树
void randomizedQuickSort(vector<int> &v, int l, int r)
{
  if (l >= r)
    return;
  // if(r - l < 20){ InsertionSort_Optimize(v); return;}
  int pivot = randomizedPartition(v, l, r);
  randomizedQuickSort(v, l, pivot - 1);
  randomizedQuickSort(v, pivot + 1, r);
}

```

---

###### 2） 优化二：中位数三分法

```cpp

int medianOfThree(int a, int b, int c)
{
  return a < b ? (b < c ? b : (a < c ? c : a)) : (a < c ? a : (b < c ? c : b));
}

int medianOfThreePartition(vector<int> &v, int l, int r)
{
  // int pivot = v[l];//选 v[l] 为基准元素，则 v[l] 位置空出来，所以先从 r-- 开始遍历
  int mid = l + ((r - l) >> 1); // '+' 优先级高于 '>>'
  int pivot_key = medianOfThree(v[l], v[mid], v[r]);
  int pivot = v[l] == pivot_key ? l : (v[r] == pivot_key ? r : mid);
  swap(v[pivot], v[l]); // 将中位数三分法选择的枢纽移到 l 处，其他做法不变

  while (l < r)
  {
    while (l < r && v[r] >= pivot_key)
      r--;
    v[l] = v[r];
    while (l < r && v[l] <= pivot_key)
      l++;
    v[r] = v[l];
  }
  v[l] = pivot_key; // 将枢轴元素放回最终位置
  return l;
}

// 类似于前序遍历的二叉树
void medianOfThreeQuickSort(vector<int> &v, int l, int r)
{
  if (l >= r)
    return;
  // if(r - l < 20){ InsertionSort_Optimize(v); return;}
  int medianOfThreePivot = medianOfThreePartition(v, l, r);
  medianOfThreeQuickSort(v, l, medianOfThreePivot - 1);
  medianOfThreeQuickSort(v, medianOfThreePivot + 1, r);
}
```

---

#### 5. 归并排序

将数组分为两半（一般），递归地对这两半进行排序，然后合并已排序的部分。

***局部有序到整体有序***

        时间复杂度：
        
            最坏情况：O(n log n)
            最佳情况：O(n log n)
            平均情况：O(n log n)
        
        空间复杂度：O(n)（需要额外的存储空间（辅助数组 B ）用于合并）
        
            稳定性：稳定

![1](https://i-blog.csdnimg.cn/blog_migrate/bef0e90755b602a480cb722bf4b8f311.gif)

```cpp
void Merge(vector<int> &v, int l, int mid, int r)
{
  vector<int> B; // 用辅助数组
  int i, j, k;
  for (int val : v)
    B.push_back(val); // 将 v 中的数据复制到 B 中

  // 双指针，较小值存回 v （覆盖）（类比链表合并）
  for (i = l, j = mid + 1, k = i; i <= mid && j <= r; k++)
  {
    if (B[i] <= B[j])
      v[k] = B[i++];
    else
      v[k] = B[j++];
  }

  while (i <= mid)
    v[k++] = B[i++];
  while (j <= r)
    v[k++] = B[j++];
}

void MergeSort(vector<int> &v, int l, int r)
{
  /*
    使用 l >= r 作为递归终止条件可以确保每个递归调用都会对至少两个元素进行操作，从而保证每次递归都会缩小问题的规模
      假设数组长度为 5，即 v.size() = 5，...当递归到 l = 2 和 r = 3 时，l < r 为真，递归会继续；最后，当 l = 3 和 r = 3 时，l < r 为假，递归停止
    使用 l > r 作为递归终止条件可能会导致某些递归调用不进行任何操作，可能会影响算法的效率，尤其是在处理小数组时
      使用同样的数组长度为 5，即 v.size() = 5，...当递归到 l = 2 和 r = 3 时，l <= r 为真，递归会继续；最后，当 l = 3 和 r = 3 时，l <= r 仍然为真，递归会继续，但这次递归调用不会进行任何操作，因为 l 和 r 指向同一个元素。
    在归并排序中，通常推荐使用 l >= r 作为递归终止条件
  */
  if (l >= r)
    return;
  int n = v.size();
  // int mid = (l + r) >> 1;
  // int mid = l + (r - l) >> 1; 错
  int mid = l + ((r - l) >> 1); //'+' 优先级高于 '>>' 优先级
  /*
    使用 l + (r - l) >> 1 计算中点是为了避免在某些情况下发生整数溢出

    当 l 和 r 都是非常大的整数时，l + r 的值可能会超过 int 类型的最大值，导致溢出
    
    例如，假设 l = 2 ^ 30 和 r = 2 ^ 30，则 l + r = 2^31，会超出 int 的上限（通常为 (2^{31}-1)）
    l + (r - l) 避免了这个问题，因为 (r - l) 在范围内，并且加上 l 不会导致溢出

    示例：
    假设 l = 2^30 = 1073741824，r = 2^30 + 2 = 1073741826。
    计算 mid 时，(l + r) / 2 会导致溢出，而 l + (r - l) >> 1 则安全。
  */
  MergeSort(v, l, mid);
  MergeSort(v, mid + 1, r);
  Merge(v, l, mid, r);
}

// ！！！！！！！对小数组进行归并排序的优化
// 性能大幅度提升
// 优化前对于 10000 的数据 took 1376.39 milliseconds.
// 优化后对于 10000 的数据 took 213.146 milliseconds.
void MergeSort_With_Optimize(vector<int> &v, int l, int r)
{
  if (l >= r)
    return;
  int mid = l + ((r - l) >> 1);
  if (r - l < 20)
    InsertionSort_Optimize(v);
  else
  {
    MergeSort(v, l, mid);
    MergeSort(v, mid + 1, r);
    Merge(v, l, mid, r);
  }
}
```

#### 6. 基数排序

基数排序是一种非比较排序算法，主要用于整数排序。通过将数字分解为各个数位（如个位、十位、百位等），按位进行排序，从最低有效位到最高有效位（或反向）逐步排好序
    
    时间复杂度：
        
        O(n k)（k 是基数的个数）
    
    空间复杂度：
        
        O(n k)
    
    稳定性：
    
        稳定

    三步：
        确定最大数：找到所有待排序数字中的最大值，确定其位数，即基数排序的“基数”
        分配和收集：从最低位（个位）开始，根据当前位对数字进行分配（放置到临时数组中）和收集（从临时数组中取出）
        重复步骤2：对每个数位重复步骤2，直到最高位（或反向）

![1](https://img2022.cnblogs.com/blog/3039354/202211/3039354-20221121121927458-1336059743.png)
![2](https://img2022.cnblogs.com/blog/3039354/202211/3039354-20221121121947116-238613222.png)
![2](https://img2022.cnblogs.com/blog/3039354/202211/3039354-20221121122016868-1290906052.png)
![2](https://img2022.cnblogs.com/blog/3039354/202211/3039354-20221121122058970-1801652074.png)


```cpp
int getMaxDigits(int x)
{
  if (x == 0)
    return 1;
  int digits = 0;
  while (x > 0)
    x /= 10, digits++;
  return digits;
}
void radixSort(vector<int> &v)
{
  // 1. 确定最大数的位数
  int maxDigits = getMaxDigits(*max_element(v.begin(), v.end()));
  vector<int> output(v.size()), count(10, 0);
  for (int i = 0; i < maxDigits; i++)
  {
    // 2. 分配
    for (int num : v)
    {
      int digit = num / (int)pow(10, i) % 10;
      count[digit]++;
    }
    // 累加计数：将 count 数组转化为累加数组，从而可以确定每个元素在当前位的排序中的正确位置
    for (int j = 1; j < 10; j++)
      count[j] += count[j - 1];
    // 3. 收集
    for (int j = v.size() - 1; j >= 0; j--)
    {
      int digit = v[j] / (int)pow(10, i) % 10;
      output[count[digit] - 1] = v[j];
      count[digit]--;
    }
    for (int j = 0; j < v.size(); j++)
      v[j] = output[j];
    // 在下一轮排序开始前时清空 count 数组，保证后续的计数累加正确
    fill(count.begin(), count.end(), 0);
  }
  /*
  // v 中每个元素的个位数为：
  170 -> 0
  45  -> 5
  75  -> 5
  90  -> 0
  802 -> 2
  24  -> 4
  2   -> 2
  66  -> 6

  // count 数组会被填充为：
  count[0] = 2  // 两个数个位为 0：170 和 90
  count[1] = 0  // 没有数个位为 1
  count[2] = 2  // 两个数个位为 2：802 和 2
  count[3] = 0  // 没有数个位为 3
  count[4] = 1  // 一个数个位为 4：24
  count[5] = 2  // 两个数个位为 5：45 和 75
  count[6] = 1  // 一个数个位为 6：66
  count[7] = 0  // 没有数个位为 7
  count[8] = 0  // 没有数个位为 8
  count[9] = 1  // 一个数个位为 9：90

  //累加计数后
  count[0] = 2  // 仍然表示个位为 0 的数有 2 个
  /count[1] = 2  // 位数 <= 1 的数共有 2 个（0位的数累加）
  count[2] = 4  // 位数 <= 2 的数共有 4 个
  /count[3] = 4  // 位数 <= 3 的数共有 4 个（因为没有 3）
  count[4] = 5  // 位数 <= 4 的数共有 5 个
  count[5] = 7  // 位数 <= 5 的数共有 7 个
  count[6] = 8  // 位数 <= 6 的数共有 8 个
  /count[7] = 8  // 位数 <= 7 的数共有 8 个
  /count[8] = 8  // 位数 <= 8 的数共有 8 个
  count[9] = 9  // 位数 <= 9 的数共有 9 个

  count[0] = 2 表示个位为 0 的元素应放在结果数组的第 1 位和第 2 位（索引 0 和 1）
  count[2] = 4 表示个位为 2 的元素应放在第 3 和第 4 位（索引 2 和 3）
  count[4] = 5 表示个位为 4 的元素应放在第 5 位（索引 4）
  count[5] = 7 表示个位为 5 的元素应放在第 6 和第 7 位（索引 5 和 6）
  count[6] = 8 表示个位为 6 的元素应放在第 8 位（索引 7）
  count[9] = 9 表示个位为 9 的元素应放在第 9 位（索引 8）

  第一次排序（个位数）
  提取个位数，digit = num % 10。
  v = {170, 45, 75, 90, 802, 24, 2, 66} 的个位数分别是 0, 5, 5, 0, 2, 4, 2, 6。
  计数排序后，数组变为 v = {170, 90, 802, 2, 24, 45, 75, 66}

  第二次排序（十位数）
  提取十位数，digit = (num / 10) % 10。
  v = {170, 90, 802, 2, 24, 45, 75, 66} 的十位数分别是 7, 9, 0, 0, 2, 4, 7, 6。
  计数排序后，数组变为 v = {802, 2, 24, 45, 66, 170, 75, 90}

  第三次排序（百位数）
  提取百位数，digit = (num / 100) % 10。
  v = {802, 2, 24, 45, 66, 170, 75, 90} 的百位数分别是 8, 0, 0, 0, 0, 1, 0, 0。
  计数排序后，数组最终排序为 v = {2, 24, 45, 66, 75, 90, 170, 802}
  */
}


```

### 完整代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <iomanip>
#include "MeasureTime.h"
using namespace std;
/*
    ！！！本代码可确保实现逻辑正确，打印无误，采用 10,000,000 的数据量，
    设置了展示开关，开启后会在每次调整后打印数组（！！！先调小数据量）
    ////printVector(v);    10000000;
    直接运行可看到每个操作的运行时间
*/
void printVector(vector<int> v)
{
  for (int i = 0; i < v.size(); i++)
    cout << v[i] << " ";
  cout << endl;
  for (int i = 0; i < v.size(); i++)
  {
    int cnt = 0;
    while (v[i])
      v[i] /= 10, cnt++;
    cout << left << setw(cnt) << i << " ";
  }
  cout << endl;
}
// 一. 内部排序
// 1. 冒泡排序

/*
时间复杂度：
  最坏情况：O(n²)
  最佳情况：O(n)（当数组已排序时）
  平均情况：O(n²)
空间复杂度：O(1)（原地排序）
稳定性：稳定
*/

// bubbleSort 优化前
void bubbleSort(vector<int> &v)
{
  int n = v.size();
  for (int i = 0; i < n; i++)           // 控制比较次数
    for (int j = 0; j < n - i - 1; j++) // 遍历数组
      if (v[j] > v[j + 1])
        swap(v[j], v[j + 1]);
}

// bubbleSort 优化后
// 通过反复比较相邻元素并交换来将最大元素“冒泡”到数组末尾，若后续序列已经有序，算法直接退出
void bubbleSort_Optimize(vector<int> &v)
{
  int n = v.size();
  for (int i = 0; i < n; i++)
  {
    int flag = 0;
    for (int j = 0; j < n - i - 1; j++)
      if (v[j] > v[j + 1])
        swap(v[j], v[j + 1]), flag = 1;
    if (!flag)
      break; // 若某一轮没有经过交换，说明后续序列已经有序，算法直接退出
  }
}

// 2. 选择排序

// 2.(1) 简单选择排序
// 每次从未排序部分选择最小（或最大）元素，放入已排序部分的开始（末尾）
//  时间复杂度：
//    最坏情况：O(n²)
//    最佳情况：O(n²)
//    平均情况：O(n²)
//  空间复杂度：O(1)（原地排序）
//  稳定性：不稳定
void selectionSort(vector<int> &v)
{
  int n = v.size();
  for (int i = 0; i < n; i++)
  {
    int minId = i;
    // 遍历未排序部分，找到最小（或最大）元素的下标
    for (int j = i + 1; j < n; j++)
      if (v[j] < v[minId])
        minId = j;
    swap(v[minId], v[i]);
  }
}
// 2.(2) 堆排序
//  这里将所有元素后移时下标从 1 开始
//   将待排序的序列构造成一个大顶堆（从后往前调整所有非终端节点（i <= len / 2）），然后将堆顶元素与末尾元素交换，然后将剩余未排序元素重新构造成一个大顶堆（小元素下坠），如此反复(len - 1 次)，直到整个序列有序
//   大根堆排序为升序，小根堆排序为降序
//   三步：（移位）———— 建堆 ———— （交换元素 ———— 维护堆）（重复执行 VertexNum - 1 次）
//  时间复杂度：
//  最坏情况：O(n log n)
//  最佳情况：O(n log n)
//  平均情况：O(n log n)
//  空间复杂度：O(1)（原地排序）
//  稳定性：不稳定
//  1）大根堆排正序
void MaxHeap_Down_Adjust(vector<int> &MaxHeap, int k, int Unsort_VertexNum)
{
  // 第三个参数是边界！！！表示每次未排序的节点个数，堆的大小边界
  MaxHeap[0] = MaxHeap[k]; // 由于下标移动后从 1 开始，用第 0 位保存当前根节点
  // 维护堆（小元素下坠）
  for (int i = k * 2; i <= Unsort_VertexNum; i *= 2)
  {
    // 找左右子节点中更大的值去替换当前根节点，移动根节点下标（先判断要判断的下标是否合法 ———— CurrentIndex <= VertexNum）
    if (i + 1 <= Unsort_VertexNum && MaxHeap[i + 1] > MaxHeap[i])
      i++;
    if (MaxHeap[0] >= MaxHeap[i])
      break; // 当前判断的节点大于其左右子节点，则已经满足大根堆，不需要调整直接退出
    else
      MaxHeap[k] = MaxHeap[i], k = i; // 此时当前判断的节点已被 MaxHeap[0] 保存所以 v[k] 空出，用左右子节点中更大的值去替换，移动根节点下标
    // 空出的做法类比快速排序中根据 pivot 分区的过程
  }
  MaxHeap[k] = MaxHeap[0];
}
void MaxHeapBuild(vector<int> &MaxHeap)
{
  int VertexNum = MaxHeap.size() - 1;
  // 从最后一个非叶子结点（下标为 [len/2](向下取整用整数除法代替)）开始
  for (int i = VertexNum >> 1; i >= 1; i--)
    MaxHeap_Down_Adjust(MaxHeap, i, VertexNum);
}
void VIndexAdjust(vector<int> &Heap) { Heap.insert(Heap.begin(), 0); }
void MaxHeapSort(vector<int> &MaxHeap)
{
  // 调整下标，所有元素整体后移
  VIndexAdjust(MaxHeap);
  // 建堆
  MaxHeapBuild(MaxHeap);
  // 将堆顶元素（v[1]）与当前末尾元素（v[i]）交换，然后将剩余未排序元素（i - 1）(VertexNum - i + 1 个元素已排序；共 VerexNum 个元素)重新构造成一个大顶堆
  int VertexNum = MaxHeap.size() - 1;
  for (int i = VertexNum; i > 1; i--)
  {
    swap(MaxHeap[1], MaxHeap[i]);
    MaxHeap_Down_Adjust(MaxHeap, 1, i - 1); // 调整堆时传入的 VertexNum 为 Unsort_VertexNum，
    // swap 前有 VertexNum - i 个元素已排好序，swap 后已排序的元素个数加 1，开始本轮堆的维护
  }
  // 删除哨兵节点，恢复原数组长度
  MaxHeap.erase(MaxHeap.begin());
}

// 3. 插入排序

// 3.(1) 普通插入排序
// 将数组分为已排序和未排序部分，逐步将未排序的元素插入到已排序部分的适当位置
//  时间复杂度：
//    最坏情况：O(n²)
//    最佳情况：O(n)
//    平均情况：O(n²)
//  空间复杂度：O(1)（原地排序）
//  稳定性：不稳定
//  （不带哨兵）
void InsertionSort_Without_SentinelNode(vector<int> &v)
{
  int n = v.size();
  for (int i = 1; i < n; i++)
  {
    // 此轮不符合插入条件（当前元素已经大于左边已排序元素），直接进行下一轮
    if (v[i] >= v[i - 1])
      continue;

    int temp = v[i], j;
    // 注意这里 for 循环内部千万不要再定义一遍 j ！！！在内层 for 循环中再定义 j，将导致外层 j 的值不会被更新，无法正确地插入元素，最终导致逻辑错误
    for (j = i - 1; j >= 0 && v[j] > temp; j--)
      v[j + 1] = v[j]; // 移动元素
    v[j + 1] = temp;
  }
}
// （带哨兵）
void InsertionSort_With_SentinelNode(vector<int> &v)
{
  int n = v.size();
  VIndexAdjust(v);
  for (int i = 2; i <= n; i++)
  {
    // 此轮不符合插入条件（当前元素已经大于左边已排序元素），直接进行下一轮
    if (v[i] >= v[i - 1])
      continue;

    v[0] = v[i];
    int j;
    // 注意这里 for 循环内部千万不要再定义一遍 j ！！！在内层 for 循环中再定义 j，将导致外层 j 的值不会被更新，无法正确地插入元素，最终导致逻辑错误
    for (j = i - 1; v[j] > v[0]; j--)
      v[j + 1] = v[j]; // 移动元素
    v[j + 1] = v[0];
  }
  // 删除哨兵节点，恢复原数组长度
  v.erase(v.begin());
}
// 插入排序优化
// 先用折半查找找到应该插入的位置后再移动元素
// 用折半查找优化（减少元素移动次数（虽然时间复杂度不变还是 O(n^2）；保持稳定性）
void InsertionSort_Optimize(vector<int> &v)
{
  int n = v.size();
  VIndexAdjust(v);
  for (int i = 2; i <= n; i++)
  {
    // 此轮不符合插入条件（当前元素已经大于左边已排序元素），直接进行下一轮
    if (v[i] >= v[i - 1])
      continue;

    v[0] = v[i];
    int l = 0, r = i - 1;
    // 终止条件为 l > r (即 l = r + 1)，r 为其插入位置下界， l 为其插入位置上界
    /*
    双指针过程类比（插入排序折半查找优化；二分查找；快速排序找枢轴元素）
   （1）终止条件
        折半查找优化和二分查找： l > r ———— 当 l = r + 1 时，二分查找终止循环，未找到目标；插入排序折半查找找到插入上界和下界，插入 l 所指位置
        快速排序找枢轴元素：l == r ———— 当 l == r 时，找到枢轴元素（从第二轮开始 ———— 第一轮一般随机找或者用中位数三分法找）
    (2) 对于相等条件的处理
        折半查找优化：为保证算法的稳定性，找到相等的元素时继续再其右边寻找插入位置
        二分查找：找到目标
        快速排序找枢轴元素：找到目标
    (3) 序列是否有序
        折半查找优化和二分查找：针对有序序列（通过 mid ———— 找目标元素或位置）
        快速排序：针对无序序列（通过 l++, r-- ———— 分区）
    */

    while (l <= r)
    {
      // int mid = l + (r - l) / 2;
      // int mid = l + (r - l) >> 1; 不正确
      // ！！！ '+'的优先级大于'>>' ！！！！！
      int mid = l + ((r - l) >> 1);
      if (v[0] < v[mid])
        r = mid - 1;
      else
        l = mid + 1; // 为保证算法的稳定性，找到相等的元素时继续再其右边寻找插入位置
    }
    for (int j = i - 1; j >= l; j--)
      v[j + 1] = v[j];
    v[l] = v[0];
  }
  // 删除哨兵节点，恢复原数组长度
  v.erase(v.begin());
}

// 3.(2) 希尔排序
//  希尔排序（Shell Sort）
//  希尔排序是一种改进的插入排序，通过将元素分组并对每个组进行插入排序，逐步减少组的大小，最终实现整体排序。它的核心思想是“局部有序可以促进整体有序”
//  时间复杂度：
//   最坏情况：O(n²)（依赖于增量的选择）
//   平均情况：O(n log n)（具体性能依赖于增量序列）
//   最佳情况：O(n)（当数组已经有序时）
//  空间复杂度：O(1)（原地排序）
//  稳定性：不稳定（因为在插入过程中可能会移动相同的元素）
void shellSort(vector<int> &v)
{
  int n = v.size();
  v.insert(v.begin(), 0);

  // 将整个数组视为多个子数组，通常选择一个较大的增量（如数组长度的一半），并逐步减小增量
  for (int d = n >> 1; d > 0; d >>= 1)
  {
    for (int i = d + 1; i <= n; i++)
    {
      v[0] = v[i];
      int j;
      // 注意添加边界条件 j >= 1 ！！！，不然会越界访问，且如果 v[0] 比所有元素都小，j 会减到负数，因为没有 j >= 1 的限制，会导致死循环
      for (j = i - d; j >= 1 && v[j] > v[0]; j -= d)
        v[j + d] = v[j];
      v[j + d] = v[0];
    }
  }
  v.erase(v.begin());
}

// 4.快速排序

// 选择一个“基准”元素，将数组分为两部分：小于基准的和大于基准的。递归地对这两部分进行排序。
// 最坏情况：O(n²)（当数组已排序或逆序时）(二叉树树高最高时)
// 平均情况：O(n log n)
// 最佳情况：O(n log n)
// 空间复杂度：O(log n)（递归栈的空间）（含有 n 个节点的二叉树的高度）
// 稳定性：不稳定
int Partition(vector<int> &v, int l, int r)
{
  int pivot_key = v[l];
  // 终止条件 l == r；找到枢轴元素
  while (l < r)
  {
    // 注意！！！写while 不是 if
    while (l < r && v[r] >= pivot_key)
      r--;
    v[l] = v[r];
    while (l < r && v[l] <= pivot_key)
      l++;
    v[r] = v[l];
  }
  v[l] = pivot_key;
  return l;
}
// 类似于前序遍历的二叉树
void QuickSort(vector<int> &v, int l, int r)
{
  if (l >= r)
    return;
  int pivot = Partition(v, l, r);
  QuickSort(v, l, pivot - 1);
  QuickSort(v, pivot + 1, r);
}
void QuickSort_With_Optimize(vector<int> &v, int l, int r)
{
  if (l >= r)
    return;
  if (r - l < 20)
  {
    InsertionSort_Optimize(v);
    return;
  }
  int pivot = Partition(v, l, r);
  QuickSort(v, l, pivot - 1);
  QuickSort(v, pivot + 1, r);
}
// 快速排序优化
// 优化一：随机化快速排序
int randomizedPartition(vector<int> &v, int l, int r)
{
  // int pivot_key = v[l];//选 v[l] 为基准元素，则 v[l] 位置空出来，所以先从 r-- 开始遍历
  int pivot = l + rand() % (r - l + 1); // 随机选择枢纽
  swap(v[pivot], v[l]);                 // 将随机选择的枢纽移到 l 处，其他做法不变

  int pivot_key = v[l];

  while (l < r)
  {
    while (l < r && v[r] >= pivot_key)
      r--;
    v[l] = v[r];
    while (l < r && v[l] <= pivot_key)
      l++;
    v[r] = v[l];
  }
  v[l] = pivot_key; // 将枢轴元素放回最终位置
  return l;
}
// 类似于前序遍历的二叉树
void randomizedQuickSort(vector<int> &v, int l, int r)
{
  if (l >= r)
    return;
  // if(r - l < 20){ InsertionSort_Optimize(v); return;}
  int pivot = randomizedPartition(v, l, r);
  randomizedQuickSort(v, l, pivot - 1);
  randomizedQuickSort(v, pivot + 1, r);
}

// 优化二：中位数三分法
int medianOfThree(int a, int b, int c)
{
  return a < b ? (b < c ? b : (a < c ? c : a)) : (a < c ? a : (b < c ? c : b));
}
int medianOfThreePartition(vector<int> &v, int l, int r)
{
  // int pivot = v[l];//选 v[l] 为基准元素，则 v[l] 位置空出来，所以先从 r-- 开始遍历
  int mid = l + ((r - l) >> 1); // '+' 优先级高于 '>>'
  int pivot_key = medianOfThree(v[l], v[mid], v[r]);
  int pivot = v[l] == pivot_key ? l : (v[r] == pivot_key ? r : mid);
  swap(v[pivot], v[l]); // 将中位数三分法选择的枢纽移到 l 处，其他做法不变

  while (l < r)
  {
    while (l < r && v[r] >= pivot_key)
      r--;
    v[l] = v[r];
    while (l < r && v[l] <= pivot_key)
      l++;
    v[r] = v[l];
  }
  v[l] = pivot_key; // 将枢轴元素放回最终位置
  return l;
}
// 类似于前序遍历的二叉树
void medianOfThreeQuickSort(vector<int> &v, int l, int r)
{
  if (l >= r)
    return;
  // if(r - l < 20){ InsertionSort_Optimize(v); return;}
  int medianOfThreePivot = medianOfThreePartition(v, l, r);
  medianOfThreeQuickSort(v, l, medianOfThreePivot - 1);
  medianOfThreeQuickSort(v, medianOfThreePivot + 1, r);
}

void text_Sort(vector<int> &v)
{
  sort(v.begin(), v.end());
}
// 5. 归并排序

// 将数组分为两半（一般），递归地对这两半进行排序，然后合并已排序的部分。
// 局部有序到整体有序
// 时间复杂度：
// 最坏情况：O(n log n)
// 最佳情况：O(n log n)
// 平均情况：O(n log n)
// 空间复杂度：O(n)（需要额外的存储空间（辅助数组 B ）用于合并）
// 稳定性：稳定
// void Merge(vector<int>& v, int l, int mid, int r){
//     vector<int> B; //辅助数组
//     int i, j, k;
//     for(i = l, j = mid + 1; i <= mid && j <= r; k++){
//         if(v[i] <= v[j]) B.push_back(v[i++]);
//         else B.push_back(v[j++]);
//     }
//     while(i <= mid) B.push_back(v[i++]);
//     while(j <= r) B.push_back(v[j++]);
//     for(k = l; k <= r; k++) v[k] = B[k - l];//复制元素（下一段实现优化掉了这一步）
// }
void Merge(vector<int> &v, int l, int mid, int r)
{
  vector<int> B; // 用辅助数组
  int i, j, k;
  for (int val : v)
    B.push_back(val); // 将 v 中的数据复制到 B 中
  // 双指针，较小值存回 v （覆盖）（类比链表合并）
  for (i = l, j = mid + 1, k = i; i <= mid && j <= r; k++)
  {
    if (B[i] <= B[j])
      v[k] = B[i++];
    else
      v[k] = B[j++];
  }
  while (i <= mid)
    v[k++] = B[i++];
  while (j <= r)
    v[k++] = B[j++];
}
void MergeSort(vector<int> &v, int l, int r)
{
  // 使用 l < r 作为递归终止条件可以确保每个递归调用都会对至少两个元素进行操作，从而保证每次递归都会缩小问题的规模
  //    假设数组长度为 5，即 v.size() = 5，...当递归到 l = 2 和 r = 3 时，l < r 仍然为真，递归会继续；最后，当 l = 3 和 r = 3 时，l < r 为假，递归停止
  // 使用 l <= r 作为递归终止条件可能会导致某些递归调用不进行任何操作，可能会影响算法的效率，尤其是在处理小数组时
  //    使用同样的数组长度为 5，即 v.size() = 5，...当递归到 l = 2 和 r = 3 时，l <= r 为真，递归会继续；最后，当 l = 3 和 r = 3 时，l <= r 仍然为真，递归会继续，但这次递归调用不会进行任何操作，因为 l 和 r 指向同一个元素。
  // 在归并排序中，通常推荐使用 l < r 作为递归终止条件
  if (l >= r)
    return;
  int n = v.size();
  // int mid = (l + r) >> 1;
  // int mid = l + (r - l) >> 1; 错
  int mid = l + ((r - l) >> 1); //'+' 优先级高于 '>>' 优先级
  /*
  使用 l + (r - l) >> 1 计算中点是为了避免在某些情况下发生整数溢出。
  当 l 和 r 都是非常大的整数时，l + r 的值可能会超过 int 类型的最大值，导致溢出。例如，假设 l = 2^30 和 r = 2^30，则 l + r = 2^31，会超出 int 的上限（通常为 (2^{31}-1)）。
  l + (r - l) 避免了这个问题，因为 (r - l) 在范围内，并且加上 l 不会导致溢出。
  示例：
  假设 l = 2^30 = 1073741824，r = 2^30 + 2 = 1073741826。
  计算 mid 时，(l + r) / 2 会导致溢出，而 l + (r - l) >> 1 则安全。
  */
  MergeSort(v, l, mid);
  MergeSort(v, mid + 1, r);
  Merge(v, l, mid, r);
}
// ！！！！！！！对小数组进行归并排序的优化
// 性能大幅度提升
// 优化前对于 10000 的数据 took 1376.39 milliseconds.
// 优化后对于 10000 的数据 took 213.146 milliseconds.
void MergeSort_With_Optimize(vector<int> &v, int l, int r)
{
  if (l >= r)
    return;
  int mid = l + ((r - l) >> 1);
  if (r - l < 20)
    InsertionSort_Optimize(v);
  else
  {
    MergeSort(v, l, mid);
    MergeSort(v, mid + 1, r);
    Merge(v, l, mid, r);
  }
}

void text_stable_sort(vector<int> &v)
{
  stable_sort(v.begin(), v.end());
}

// 6. 基数排序
//  基数排序是一种非比较排序算法，主要用于整数排序。通过将数字分解为各个数位（如个位、十位、百位等），按位进行排序，从最低有效位到最高有效位（或反向）逐步排好序
//  时间复杂度：O(n k)（k 是基数的个数）
//  空间复杂度：O(n k)
//  稳定性：稳定
//  三步：
//      确定最大数：找到所有待排序数字中的最大值，确定其位数，即基数排序的“基数”
//      分配和收集：从最低位（个位）开始，根据当前位对数字进行分配（放置到临时数组中）和收集（从临时数组中取出）
//      重复步骤2：对每个数位重复步骤2，直到最高位（或反向）
int getMaxDigits(int x)
{
  if (x == 0)
    return 1;
  int digits = 0;
  while (x > 0)
    x /= 10, digits++;
  return digits;
}
void radixSort(vector<int> &v)
{
  // 1. 确定最大数的位数
  int maxDigits = getMaxDigits(*max_element(v.begin(), v.end()));
  vector<int> output(v.size()), count(10, 0);
  for (int i = 0; i < maxDigits; i++)
  {
    // 2. 分配
    for (int num : v)
    {
      int digit = num / (int)pow(10, i) % 10;
      count[digit]++;
    }
    // 累加计数：将 count 数组转化为累加数组，从而可以确定每个元素在当前位的排序中的正确位置
    for (int j = 1; j < 10; j++)
      count[j] += count[j - 1];
    // 3. 收集
    for (int j = v.size() - 1; j >= 0; j--)
    {
      int digit = v[j] / (int)pow(10, i) % 10;
      output[count[digit] - 1] = v[j];
      count[digit]--;
    }
    for (int j = 0; j < v.size(); j++)
      v[j] = output[j];
    // 在下一轮排序开始前时清空 count 数组，保证后续的计数累加正确
    fill(count.begin(), count.end(), 0);
  }
  /*
  // v 中每个元素的个位数为：
  170 -> 0
  45  -> 5
  75  -> 5
  90  -> 0
  802 -> 2
  24  -> 4
  2   -> 2
  66  -> 6

  // count 数组会被填充为：
  count[0] = 2  // 两个数个位为 0：170 和 90
  count[1] = 0  // 没有数个位为 1
  count[2] = 2  // 两个数个位为 2：802 和 2
  count[3] = 0  // 没有数个位为 3
  count[4] = 1  // 一个数个位为 4：24
  count[5] = 2  // 两个数个位为 5：45 和 75
  count[6] = 1  // 一个数个位为 6：66
  count[7] = 0  // 没有数个位为 7
  count[8] = 0  // 没有数个位为 8
  count[9] = 1  // 一个数个位为 9：90

  //累加计数后
  count[0] = 2  // 仍然表示个位为 0 的数有 2 个
  /count[1] = 2  // 位数 <= 1 的数共有 2 个（0位的数累加）
  count[2] = 4  // 位数 <= 2 的数共有 4 个
  /count[3] = 4  // 位数 <= 3 的数共有 4 个（因为没有 3）
  count[4] = 5  // 位数 <= 4 的数共有 5 个
  count[5] = 7  // 位数 <= 5 的数共有 7 个
  count[6] = 8  // 位数 <= 6 的数共有 8 个
  /count[7] = 8  // 位数 <= 7 的数共有 8 个
  /count[8] = 8  // 位数 <= 8 的数共有 8 个
  count[9] = 9  // 位数 <= 9 的数共有 9 个

  count[0] = 2 表示个位为 0 的元素应放在结果数组的第 1 位和第 2 位（索引 0 和 1）
  count[2] = 4 表示个位为 2 的元素应放在第 3 和第 4 位（索引 2 和 3）
  count[4] = 5 表示个位为 4 的元素应放在第 5 位（索引 4）
  count[5] = 7 表示个位为 5 的元素应放在第 6 和第 7 位（索引 5 和 6）
  count[6] = 8 表示个位为 6 的元素应放在第 8 位（索引 7）
  count[9] = 9 表示个位为 9 的元素应放在第 9 位（索引 8）

  第一次排序（个位数）
  提取个位数，digit = num % 10。
  v = {170, 45, 75, 90, 802, 24, 2, 66} 的个位数分别是 0, 5, 5, 0, 2, 4, 2, 6。
  计数排序后，数组变为 v = {170, 90, 802, 2, 24, 45, 75, 66}

  第二次排序（十位数）
  提取十位数，digit = (num / 10) % 10。
  v = {170, 90, 802, 2, 24, 45, 75, 66} 的十位数分别是 7, 9, 0, 0, 2, 4, 7, 6。
  计数排序后，数组变为 v = {802, 2, 24, 45, 66, 170, 75, 90}

  第三次排序（百位数）
  提取百位数，digit = (num / 100) % 10。
  v = {802, 2, 24, 45, 66, 170, 75, 90} 的百位数分别是 8, 0, 0, 0, 0, 1, 0, 0。
  计数排序后，数组最终排序为 v = {2, 24, 45, 66, 75, 90, 170, 802}
  */
}

// 二. 外部排序
//......

int main()
{
  // 初始化测试数据
  srand(time(0));
  vector<int> v;
  for (int i = 0; i < 30000; i++)
    v.push_back(rand() % 1000); // 生成随机数组
  // printVector(v);
  vector<int> temp = v;
  cout << "bubbleSort :\n";
  v.clear();
  v = temp;
  Timer::measureTime("bubbleSort", bubbleSort, v); // 测量exampleFunction运行时间

  // printVector(v);
  cout << "selectionSort :\n";
  v.clear();
  v = temp;
  Timer::measureTime("selectionSort", selectionSort, v); // 测量exampleFunction运行时间

  // printVector(v);
  cout << "MaxHeapSort :\n";
  v.clear();
  v = temp;
  Timer::measureTime("MaxHeapSort", MaxHeapSort, v); // 测量exampleFunction运行时间
  // printVector(v);

  cout << "MinHeapSort: \n";
  v.clear();
  v = temp;
  Timer::measureTime("MinHeapSort", MinHeapSort, v);
  // printVector(v);

  cout << "MaxHeapInsert:\n";
  v.clear();
  v = temp;
  Timer::measureTime("MaxHeapInsert", MaxHeapInsert, v, 1000);
  // printVector(v);

  cout << "MaxHeapDelete:\n";
  v.clear();
  v = temp;
  Timer::measureTime("MaxHeapDelete", MaxHeapDelete, v, 1);
  cout << "After MaxHeapDelete:\n";
  // printVector(v);

  cout << "MinHeapInsert:\n";
  v.clear();
  v = temp;
  Timer::measureTime("MinHeapInsert", MinHeapInsert, v, 0);
  // printVector(v);

  cout << "MinHeapDelete:\n";
  v.clear();
  v = temp;
  Timer::measureTime("MinHeapDelete", MinHeapDelete, v, 1);
  cout << "After MinHeapDelete:\n";
  // printVector(v);

  cout << "InsertionSort_Without_SentinelNode:\n";
  v.clear();
  v = temp;
  Timer::measureTime("InsertionSort_Without_SentinelNode", InsertionSort_Without_SentinelNode, v);
  // printVector(v);

  cout << "InsertionSort_With_SentinelNode:\n";
  v.clear();
  v = temp;
  Timer::measureTime("InsertionSort_With_SentinelNode", InsertionSort_With_SentinelNode, v);
  // printVector(v);

  cout << "InsertionSort_Optimize:\n";
  v.clear();
  v = temp;
  Timer::measureTime("InsertionSort_Optimize", InsertionSort_Optimize, v);
  // printVector(v);

  cout << "shellSort:\n";
  v.clear();
  v = temp;
  Timer::measureTime("shellSort", shellSort, v);
  // printVector(v);

  cout << "MyQuickSort:\n";
  v.clear();
  v = temp;
  Timer::measureTime("QuickSort", QuickSort, v, 0, v.size() - 1);
  // printVector(v);

  cout << "QuickSort_With_Optimize:\n";
  v.clear();
  v = temp;
  Timer::measureTime("QuickSort_With_Optimize", QuickSort_With_Optimize, v, 0, v.size() - 1);
  // printVector(v);

  cout << "C++ STL sort()\n";
  v.clear();
  v = temp;
  Timer::measureTime("C++ STL sort()", text_Sort, v);
  // printVector(v);

  cout << "randomizedQuickSort:\n";
  v.clear();
  v = temp;
  Timer::measureTime("randomizedQuickSort", randomizedQuickSort, v, 0, v.size() - 1);
  // printVector(v);

  cout << "medianOfThreeQuickSort:\n";
  v.clear();
  v = temp;
  Timer::measureTime("medianOfThreeQuickSort", medianOfThreeQuickSort, v, 0, v.size() - 1);
  // printVector(v);

  // 为啥啊为啥啊我的归并排序这么慢
  cout << "MergeSort:\n";
  v.clear();
  v = temp;
  Timer::measureTime("MergeSort", MergeSort, v, 0, v.size() - 1);
  // printVector(v);

  cout << "MergeSort_With_Optimize:\n";
  v.clear();
  v = temp;
  Timer::measureTime("MergeSort_With_Optimize", MergeSort_With_Optimize, v, 0, v.size() - 1);
  // printVector(v);

  cout << "C++ STL stable_sort()\n";
  v.clear();
  v = temp;
  Timer::measureTime("C++ STL stable_sort()", text_stable_sort, v);
  // printVector(v);

  cout << "radixSort:\n";
  v.clear();
  v = temp;
  Timer::measureTime("radixSort", radixSort, v);
  // printVector(v);
  return 0;
}
```

## 三、STL中封装的排序算法

        1. sort 
   
            sort(vec.begin(), vec.end());

            sort 是一种非稳定排序算法，通常使用 Introsort 算法

            Introsort 是一种混合排序算法，它结合了快速排序（Quick Sort）、堆排序（Heap Sort）和插入排序（Insertion Sort）

            退化条件与阈值：
            
                当递归深度过深即超过某个阈值（通常为 2 * log(n)），Introsort 从快速排序切换到堆排序。

                当子数组的大小小于某个阈值（通常是 16 或 32），Introsort 从快速排序切换到插入排序。

        2. stable_sort 
        
            stable_sort(vec.begin(), vec.end());

            stable_sort 是一种稳定排序算法，通常使用 归并排序（Merge Sort）或 Timsort

            Timsort 是一种混合排序算法，结合了归并排序和插入排序

            退化条件与阈值：

                使用 Timsort 时，当数据部分有序时，算法性能可以接近 O(n)

        3. partial_sort
        
            partial_sort(vec.begin(), vec.begin() + k, vec.end()); 

            partial_sort 用于对部分数据进行排序（通常是前 k 个元素）

            一般使用 堆排序（Heap Sort）或 选择排序（Selection Sort）

            堆排序：堆排序适用于需要找到前 k 个元素的情况，具有 O(n log k) 的时间复杂度

            选择排序：选择排序在 k 很小的情况下表现良好，因为它每次只选择当前未排序部分的最小值放到已排序部分的末尾

            退化条件与阈值： 

                当 k 很小时，堆排序可能退化为选择排序。

        4. nth_element 
        
            nth_element 用于部分排序，使得第 n 个元素处于其最终位置，通常使用 快速选择算法（Quickselect）

            退化条件与阈值：

                在最差情况下（如每次选择的枢纽都位于极端位置），快速选择的时间复杂度会退化为 O(n^2)。
                
                为了避免这种情况，通常使用随机化版本的快速选择或中位数三分法来选择枢纽，从而降低退化的概率

        5. inplace_merge
        
            实现与算法

                inplace_merge 用于合并两个已经排序的区间，通常使用 就地归并排序（In-place Merge Sort）

            退化条件与阈值：

                对于非常大的数据集，虽然就地归并可以节省空间，但其时间复杂度仍然是 O(n log n)

        6. partial_sort_copy 
   
            将数组的一部分复制到一个新的位置，并保持剩余部分的顺序

            一般使用 堆排序（Heap Sort）或 选择排序（Selection Sort）

        7. sort_copy 
        
            会复制整个数组

            sort 是一种非稳定排序算法，通常使用 Introsort 算法

            Introsort 是一种混合排序算法，它结合了快速排序（Quick Sort）、堆排序（Heap Sort）和插入排序（Insertion Sort）

        8. is_sorted 
        
            检查一个范围是否已经排序

            不进行排序：只是检查数组是否已经是有序的

        9.  is_sorted_until 
        
            检查一个范围是否已经排序，并返回第一个不满足排序条件的位置

            不进行排序：只是检查数组是否已经是有序的

深度思考：

        为什么使用这些算法？

            快速排序：通常具有很好的平均性能（时间复杂度为 O(n log n)），并且的常数因子较小，使得在实际应用中非常快

            归并排序：提供了稳定的排序，这对于需要保持元素相对顺序的应用场景非常重要

            堆排序：在最坏情况下（比如说快速排序算法中每次选择的枢纽都位于极端位置）仍然具有 O(n log n) 的时间复杂度，这使得在数据量较大时非常有效

            插入排序：在数据量小或几乎已经排序时非常快，并且实现简单

## 常见误区 Q&A

        1. 为什么 Introsort 会在子数组大小小于 16 或 32 时切换到插入排序

        Introsort 在子数组大小小于 16 或 32 时切换到插入排序，这是通过经验和实际应用中的性能优化得出的结论

        (1) 算法的常数开销

            快速排序是一种递归算法，递归的每一层都有一定的常数开销，如递归函数调用、栈操作等。在处理小数组时，这些开销会显得非常明显

            插入排序虽然是 O(n ^ 2) 的时间复杂度，但由于其常数因子较小，对于小规模数组来说，插入排序的开销实际上低于快速排序或其他排序算法

            根据实际的硬件架构和算法效率研究，经验表明，子数组的大小大约在 10 到 32 的范围内时，插入排序表现优于快速排序

            因此 16 或 32 是一个较优的经验值，能平衡递归快速排序的开销与插入排序的性能。

        (2) 缓存效率和分支预测

            在现代 CPU 架构中，缓存效率和分支预测对排序算法的性能有很大影响。插入排序在处理小数组时具有以下优势：

            缓存友好：插入排序访问的内存是连续的，能更好地利用 CPU 的缓存，提高数据访问的速度

            分支预测：由于插入排序的操作是线性扫描和插入，分支预测命中的概率较高，而快速排序的分支预测效果可能不如插入排序好，尤其是在小规模数组上

            16 和 32 是通过实践中分析和测试得出的较好切换点，在这个范围内，插入排序能够比快速排序和其他排序算法更好地利用缓存。

        (3) 经验法则

            不同的排序算法在不同数据规模和分布上表现不同，现代排序库（如 C++ 的 sort 或 Python 的 Timsort）都是经过多次优化调整得出的

            虽然 15、18、19 这些值理论上也可以作为切换点，但大量实际测试表明 16 和 32 能够在不同规模的数据上表现出最佳的平衡效果

            16 和 32 是两个典型的值，足以保证在大多数硬件环境下得到较好的性能


        2. partial_sort 中堆排序退化为选择排序的原因
        
            具体的 k 值范围通常依赖于实际的硬件、编译器优化和输入数据的分布情况

            通常，经验法则指出，当 k 小于或等于 10 到 20 的范围时，选择排序的表现往往优于堆排序

            选择排序的常数开销低
            堆排序的维护成本高：
                
                虽然堆排序的时间复杂度是 O(n log k)，但是在 k 非常小时，维护堆的额外开销（如上移和下移操作）可能会使得堆排序的效率比不上选择排序。


        3. 如何避免快速排序中每次选择的枢纽都位于极端位置
   
            快速排序中每次选择的枢纽都位于极端位置（即出现 O(n^2) 的最差情况），可以通过以下两种方式来选择更合适的枢纽（优化）：
            (1) 随机化版本的快速排序

                int pivotIndex = l + rand() % (r - l + 1);  // 随机选择枢纽
                swap(v[pivotIndex], v[r]);  // 将随机选择的枢纽移到末尾
                int pivot = v[r];

            (2) 使用中位数三分法选择枢纽并进行分区

                int mid = l + (r - l) / 2;
                int pivot = medianOfThree(v[l], v[mid], v[r]);
                int pivotIndex = (v[l] == pivot) ? l : (v[mid] == pivot) ? mid : r;
                swap(v[pivotIndex], v[r]);  // 将中位数作为枢纽移到末尾


        4. 数据量很小时使用插入排序还是选择排序
   
        当数据量较小时（如少于 16 或 32 个元素），通常使用 插入排序 而不是选择排序。
        
        原因如下：

            插入排序在小规模数据上表现较好，当数组接近有序时，插入排序的比较次数会显著减少

            插入排序是稳定的排序算法

            插入排序具有较低的常数开销，因为它只需要逐步插入元素到正确的位置

            选择排序的劣势：选择排序的时间复杂度总是 O(n ^ 2)，无论数组是否接近有序

                        每次都要扫描未排序部分来找到最小元素，并将其交换到正确的位置

            因此在小规模数据上，选择排序并不如插入排序高效。


        5. 哪些排序算法是稳定的？
        
            （1）稳定的排序算法包括:

            归并排序（Merge Sort）：稳定，时间复杂度 O(n log n)

            冒泡排序（Bubble Sort）：稳定，时间复杂度 O(n^2)

            插入排序（Insertion Sort）：稳定，时间复杂度 O(n^2)

            计数排序（Counting Sort）：稳定，时间复杂度 O(n + k)，适合整数排序

            基数排序（Radix Sort）：稳定，时间复杂度 O(nk)（其中 k 为位数），适合大整数排序

            桶排序（Bucket Sort）：在某些情况下稳定，时间复杂度 O(n + k)

            （2）非稳定排序包括：

            快速排序（Quick Sort）：非稳定

            堆排序（Heap Sort）：非稳定

            选择排序（Selection Sort）：非稳定


        6. 时间复杂度为 O(n log n) 的排序算法有哪些？
   
            归并排序（Merge Sort）：
                    无论在最优、平均还是最差情况下，时间复杂度都是 O(n log n)，且是稳定的排序算法

            堆排序（Heap Sort）：
                    在最优、平均和最差情况下，时间复杂度都是 O(n log n)，但不是稳定的排序算法

            快速排序（Quick Sort）：平均时间复杂度为 O(n log n)，但最差情况（如每次选择枢纽都位于极端位置）为 O(n ^ 2)。
                            
                            通过（1）随机化 或（2）三数取中法 可以避免最坏情况
                            
                            快速排序是非稳定的

            Timsort：Timsort 是 Python 和 Java 中的排序算法，时间复杂度为 O(n log n)，在处理部分有序数据时表现极佳，是稳定的


        7. 堆排序与归并排序的区别与联系
        
            算法原理：

                堆排序：基于堆（通常是最大堆或最小堆）的性质，逐步从无序数组中选出最大或最小元素，构造堆来进行排序。堆排序通过每次从堆顶删除元素并重建堆来实现排序

                归并排序：基于分治思想，递归地将数组分成两个子数组，分别排序后再合并。每次合并两个有序数组时，保持排序的稳定性。

            时间复杂度：

                堆排序和归并排序的时间复杂度在最优、平均和最差情况下都为 O(n log n)

                归并排序有更好的最坏情况表现，而堆排序的实际效率可能比归并排序低，尤其在需要频繁交换的情况下

            空间复杂度：

                堆排序：在原地进行排序，因此其空间复杂度是 O(1)，只需要额外的常数空间

                归并排序：需要 O(n) 的辅助空间来存储中间结果，尤其在合并操作中需要额外的临时数组

            稳定性：
            
                堆排序：不是稳定的，因为元素在堆中交换时，可能打乱相同元素的相对顺序

                归并排序：是稳定的，因为在合并阶段，相等的元素保持了它们原来的相对顺序

            联系：

                时间复杂度：堆排序和归并排序的时间复杂度都是 O(n log n)，在数据量较大时都能提供良好的性能
            
                适用场景：两者都适合对大规模数据进行排序，其中归并排序适合稳定性要求较高的场合，而堆排序则更适合需要原地排序的场景


        8. 插入排序与选择排序的区别与联系
   
        算法原理：
        
            插入排序：从第二个元素开始，将其插入到已排序的部分中，找到合适的位置插入。它是通过逐步构建有序序列来完成排序

            选择排序：通过每次选择最小或最大元素进行排序

        时间复杂度：

            两者的时间复杂度在最优、平均和最差情况下均为 O(n ^ 2)
            但插入排序在部分有序数组上表现更好，在最优情况下（数组已经完全有序），插入排序的时间复杂度可以降为 O(n)

        稳定性：

            插入排序：是稳定的排序算法，因为它在插入时不会改变相同元素的相对顺序

            选择排序：不是稳定的排序算法，因为在找到最小元素时，它可能会与后面的元素交换位置，破坏相同元素的相对顺序

        交换次数：

            插入排序：插入排序在需要交换时才进行操作，因此在部分有序的数组上，交换次数很少

            选择排序：选择排序每一轮都要进行交换，即使没有必要，因此交换次数相对较多

        联系：

            时间复杂度：两者在平均情况下的时间复杂度都是 O(n ^ 2)，但在小规模数据集上，它们的性能差异可能不大

            适用场景：插入排序在小规模、部分有序的数据上表现优越，而选择排序适合在不考虑稳定性、交换次数不多的场合使用

        总结

            a.稳定的排序算法：包括归并排序、插入排序、冒泡排序等

            b.时间复杂度为 O(n log n) 的算法：包括归并排序、堆排序、快速排序、Timsort 等

            c.堆排序和归并排序的区别：堆排序是原地非稳定排序，归并排序需要额外的空间但稳定

            d.插入排序和选择排序的区别：插入排序是稳定的，选择排序不是。插入排序在部分有序的数组上表现更好

        9.  什么是分支预测？
   
            分支预测（Branch Prediction）是现代处理器（CPU）中的一种技术，
            目的是提高指令执行效率。在程序运行过程中，经常会遇到条件分支（如 if-else 语句或循环），CPU 需要根据条件判断是否执行某个分支

            例如，在执行 if (a > b) 这样的代码时，CPU 需要检查条件是否成立，并根据结果跳转到不同的执行路径。
            这种条件判断会影响流水线（pipeline）的执行，因为如果 CPU 不能预先知道条件的结果，它就无法决定应该继续加载哪条指令。

            分支预测的作用：
            
                为了避免在遇到条件分支时停顿（等待条件的计算结果），现代 CPU 使用 “分支预测器” 来猜测分支的方向

                也就是说，CPU 会尝试提前猜测分支执行的路径，从而继续执行指令。如果预测正确，程序将顺利执行；

                如果预测错误，CPU 需要清空流水线并重新加载正确的指令，这会产生性能损耗，称为 “分支预测失误” 或 “分支错误”


            分支预测的原理和过程：分支预测器根据历史信息和模式来猜测分支的执行路径

            它的工作过程可以分为几个步骤：

                1）分支指令的执行：当 CPU 执行一条分支指令时，它会尝试预测分支将会跳转到哪里（例如：条件成立时跳转到 if 块，条件不成立时跳转到 else 块）

                2）历史记录和模式识别：分支预测器通常基于历史模式进行预测。现代 CPU 会记录每个分支之前执行的结果，并根据这些历史数据来做出猜测。
                                   
                    例如，如果一个分支之前 90% 的时间都走了 if 块，那么 CPU 很可能会继续猜测下次也会走同一个路径

                3）流水线执行：如果 CPU 猜测的分支方向正确，后续的指令已经准备好并可以直接执行

                    如果猜测错误，CPU 需要丢弃已经加载的错误指令，重新加载正确的指令，这会导致流水线暂停，降低性能

                4）更新历史信息：每次分支执行完毕后，分支预测器会根据实际结果更新它的历史记录，来提高下一次的预测准确性

            分支预测器有不同的实现方式，包括：

            1）静态分支预测：根据简单的规则（如总是预测条件为真或假，或者总是猜测向前跳转）

            2）动态分支预测：根据分支的历史行为进行预测，这是现代 CPU 中常见的方式。
            

        10. 为什么插入排序分支预测命中率高，而快速排序分支预测效果差？
   
            在讨论排序算法时，分支预测主要与以下方面有关：
        
            1）条件判断：如比较两个元素的大小。
            2）跳转逻辑：是否根据比较结果进行跳转、交换操作或递归调用

            （1）插入排序的分支预测优势：

                1）线性扫描和插入：插入排序的核心操作是逐一遍历数组，并在已排序部分中找到合适的位置插入元素。这意味着其内循环的逻辑是相对简单且线性的
                
                如果元素已经接近有序（如部分有序或完全有序的数组），内循环的条件判断 if (v[j] > key) 大多数时候会产生一个固定的模式（即大部分情况下不需要进行交换），

                从而使 CPU 的分支预测器很容易预测正确，此时 CPU 可以更高效地执行流水线操作，因为它能正确预测大多数分支指令，减少分支错误的发生

                2）少量条件判断：插入排序的逻辑简单，只有一个主要的条件判断 if (v[j] > key)，预测的模式更容易。插入排序通常遍历较短的区间，分支模式更为固定，这进一步提高了预测的命中率。

            （2）快速排序的分支预测劣势：

                1）递归和复杂条件：快速排序中有更多的复杂分支，尤其是分区操作（partition）中，涉及对枢轴（pivot）元素和其他元素的比较和交换，分区过程中，元素的分布并不均匀，导致分支判断的模式较为复杂

                例如，在分区操作中，左右指针分别从数组的两端向中间移动，进行条件判断 if (v[i] <= pivot) 和 if (v[j] > pivot)

                这些判断的分布不均匀且随机性较大，分支预测器难以正确预测每次条件的结果

                2）递归结构：快速排序的递归结构也会影响分支预测器的性能。每次递归调用都意味着新的条件判断和执行路径，
                而这些路径可能和之前的递归层次完全不同，因此，预测的历史信息不再适用，导致分支预测失败的概率增大

                3）分支失误成本高：快速排序中一旦分支预测失败，尤其是在递归深度较大的情况下，重新加载正确指令的开销会更高。每次分支失误都可能导致较大的流水线停顿和性能损耗


            总结

            a.分支预测 是现代 CPU 中用来提高执行效率的一项关键技术，它通过历史信息来猜测程序的执行路径，避免在分支处停顿等待条件判断结果

            b.插入排序 由于其简单的线性结构和稳定的条件判断模式，分支预测器容易猜测出正确的执行路径，尤其在处理小规模或部分有序数据时，分支预测命中率较高，因此插入排序在这些场合下表现更好

            c.快速排序 的复杂性导致其分支预测较为困难，尤其是在处理不规则数据和递归调用时，分支预测失误的概率更高。这使得快速排序在小规模数组上可能不如插入排序高效

            d.这种现象是现代排序算法优化的一部分，尤其在现代硬件环境下，充分利用分支预测可以显著提升算法的实际运行效率

---