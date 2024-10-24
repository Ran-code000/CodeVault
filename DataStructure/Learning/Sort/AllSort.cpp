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
void printVector(vector<int> v){ 
    for(int i = 0; i < v.size(); i++) cout << v[i] << " "; 
    cout << endl;
    for(int i = 0; i < v.size(); i++){
        int cnt = 0;
        while(v[i]) v[i] /= 10, cnt++;
        cout << left << setw(cnt) << i << " ";
    }
    cout << endl; 
}
//一. 内部排序
//1. 冒泡排序

// bubbleSort 优化前
void bubbleSort(vector<int>& v){
    int n = v.size();
    for(int i = 0; i < n; i++)//控制比较次数
        for(int j = 0; j < n - i - 1; j++)//遍历数组
            if(v[j] > v[j + 1]) swap(v[j], v[j + 1]);
}

//冒泡排序优化
// bubbleSort 优化后
//通过反复比较相邻元素并交换来将最大元素“冒泡”到数组末尾，若后续序列已经有序，算法直接退出
// 时间复杂度：
//   最坏情况：O(n²)
//   最佳情况：O(n)（当数组已排序时）
//   平均情况：O(n²)
// 空间复杂度：O(1)（原地排序）
// 稳定性：稳定
void bubbleSort_Optimize(vector<int>& v){
    int n = v.size();
    for(int i = 0; i < n; i++){
        int flag = 0;
        for(int j = 0; j < n - i - 1; j++) if(v[j] > v[j + 1]) swap(v[j], v[j + 1]), flag = 1;
        if(!flag) break; //若某一轮没有经过交换，说明后续序列已经有序，算法直接退出
    }
}


//2. 选择排序

//2.(1) 简单选择排序
//每次从未排序部分选择最小（或最大）元素，放入已排序部分的开始（末尾）
// 时间复杂度：
//   最坏情况：O(n²)
//   最佳情况：O(n²)
//   平均情况：O(n²)
// 空间复杂度：O(1)（原地排序）
// 稳定性：不稳定
void selectionSort(vector<int>& v){
    int n = v.size();
    for(int i = 0; i < n; i++){
        int minId = i;
        //遍历未排序部分，找到最小（或最大）元素的下标
        for(int j = i + 1; j < n; j++) if(v[j] < v[minId]) minId = j;
        swap(v[minId], v[i]);
    }
}
//2.(2) 堆排序
// 这里将所有元素后移时下标从 1 开始
//  将待排序的序列构造成一个大顶堆（从后往前调整所有非终端节点（i <= len / 2）），然后将堆顶元素与末尾元素交换，然后将剩余未排序元素重新构造成一个大顶堆（小元素下坠），如此反复(len - 1 次)，直到整个序列有序
//  大根堆排序为升序，小根堆排序为降序
//  三步：（移位）———— 建堆 ———— （交换元素 ———— 维护堆）（重复执行 VertexNum - 1 次）
// 时间复杂度：
// 最坏情况：O(n log n)
// 最佳情况：O(n log n)
// 平均情况：O(n log n)
// 空间复杂度：O(1)（原地排序）
// 稳定性：不稳定
// 1）大根堆排正序
void MaxHeap_Down_Adjust(vector<int>& MaxHeap, int k, int Unsort_VertexNum){
    //第三个参数是边界！！！表示每次未排序的节点个数，堆的大小边界
    MaxHeap[0] = MaxHeap[k];//由于下标移动后从 1 开始，用第 0 位保存当前根节点
    //维护堆（小元素下坠）
    for(int i = k * 2; i <= Unsort_VertexNum; i *= 2){
        //找左右子节点中更大的值去替换当前根节点，移动根节点下标（先判断要判断的下标是否合法 ———— CurrentIndex <= VertexNum）
        if(i + 1 <= Unsort_VertexNum && MaxHeap[i + 1] > MaxHeap[i]) i++;
        if(MaxHeap[0] >= MaxHeap[i]) break;//当前判断的节点大于其左右子节点，则已经满足大根堆，不需要调整直接退出
        else MaxHeap[k] = MaxHeap[i], k = i;//此时当前判断的节点已被 MaxHeap[0] 保存所以 v[k] 空出，用左右子节点中更大的值去替换，移动根节点下标
        //空出的做法类比快速排序中根据 pivot 分区的过程
    }
    MaxHeap[k] = MaxHeap[0];
}
void MaxHeapBuild(vector<int>& MaxHeap){
    int VertexNum = MaxHeap.size() - 1;
    //从最后一个非叶子结点（下标为 [len/2](向下取整用整数除法代替)）开始
    for(int i = VertexNum >> 1; i >= 1; i--) MaxHeap_Down_Adjust(MaxHeap, i, VertexNum);
}
void VIndexAdjust(vector<int>& Heap){ Heap.insert(Heap.begin(), 0);}
void MaxHeapSort(vector<int>& MaxHeap){
    //调整下标，所有元素整体后移
    VIndexAdjust(MaxHeap);
    //建堆
    MaxHeapBuild(MaxHeap);
    //将堆顶元素（v[1]）与当前末尾元素（v[i]）交换，然后将剩余未排序元素（i - 1）(VertexNum - i + 1 个元素已排序；共 VerexNum 个元素)重新构造成一个大顶堆
    int VertexNum = MaxHeap.size() - 1;
    for(int i = VertexNum; i > 1; i--){
        swap(MaxHeap[1], MaxHeap[i]);
        MaxHeap_Down_Adjust(MaxHeap, 1, i - 1); //调整堆时传入的 VertexNum 为 Unsort_VertexNum，
        //swap 前有 VertexNum - i 个元素已排好序，swap 后已排序的元素个数加 1，开始本轮堆的维护
    }
    //删除哨兵节点，恢复原数组长度
    MaxHeap.erase(MaxHeap.begin());
}
//2）小根堆排逆序
void MinHeap_Down_Adjust(vector<int>& MinHeap, int k, int Unsort_VertexNum){
    MinHeap[0] = MinHeap[k];
    for(int i = k * 2; i <= Unsort_VertexNum; i *= 2){
        if(i + 1 <= Unsort_VertexNum && MinHeap[i + 1] < MinHeap[i]) i++;
        if(MinHeap[0] <= MinHeap[i]) break;
        else MinHeap[k] = MinHeap[i], k = i;
    }
    MinHeap[k] = MinHeap[0];
}
void MinHeapBuild(vector<int>& MinHeap){
    int VertexNum = MinHeap.size() - 1;
    for(int i = VertexNum >> 1; i >= 1; i--) MinHeap_Down_Adjust(MinHeap, i, VertexNum);
}
void MinHeapSort(vector<int>& MinHeap){
    VIndexAdjust(MinHeap);
    MinHeapBuild(MinHeap);
    int VertexNum = MinHeap.size() - 1;
    for(int i = VertexNum; i > 1; i--){
        swap(MinHeap[1], MinHeap[i]);
        MinHeap_Down_Adjust(MinHeap, 1, i - 1);//第三个参数是边界！！！表示每次未排序的节点个数，堆的大小边界
    }
    //删除哨兵节点，恢复原数组长度
    MinHeap.erase(MinHeap.begin());
}
//利用大根堆模拟插入和删除过程
void MaxHeap_Up_Adjust(vector<int>& MaxHeap, int k, int VertexNum){
    //过程类比 MaxHeap_Down_Adjust；不同点：当前节点 k 只有一个父节点(k >> 1)，不用 i++;
    MaxHeap[0] = MaxHeap[k];
    for(int i = k >> 1; i >= 1; i >>= 1){
        if(MaxHeap[i] >= MaxHeap[0]) break;
        else MaxHeap[k] = MaxHeap[i], k = i;
    }
    MaxHeap[k] = MaxHeap[0];
    //其实可以变得更优雅 ......
    //while(k >= 1 && MaxHeap[k >> 1] < MaxHeap[k]) swap(MaxHeap[k], MaxHeap[k >> 1]), k /= 2;
}
//末尾插入新元素，新元素上浮
void MaxHeapInsert(vector<int>& MaxHeap, int val){
    //这两句一般是冗余的，这里只是为了确保后续操作是对下标从 1 开始的最大堆进行的（如果已知传进来的是确定下标的最大堆则无需这两句代码）
    VIndexAdjust(MaxHeap);
    MaxHeapBuild(MaxHeap);
    // cout << "After MaxHeapBuild（now 0 position is invaild）:\n";
    // printVector(MaxHeap);

    MaxHeap.push_back(val);
    int VertexNum = MaxHeap.size() - 1, k = VertexNum;
    MaxHeap_Up_Adjust(MaxHeap, k, VertexNum);

    //删除哨兵节点，恢复原数组长度（insert 长度加 1）
    MaxHeap.erase(MaxHeap.begin());
}
//删除新元素(交换待删除元素和末尾元素，pop_back()) ———— 判断交换到 pos 的末尾元素与其当前位置父节点的大小，决定是上浮还是下沉
void MaxHeapDelete(vector<int>& MaxHeap, int pos){
    //......
    VIndexAdjust(MaxHeap);
    MaxHeapBuild(MaxHeap);
    // cout << "After MaxHeapBuild（now 0 position is invaild）:\n";
    // printVector(MaxHeap);

    int VertexNum = MaxHeap.size() - 1, parent = pos / 2, lc = pos * 2, rc = pos * 2 + 1;
    MaxHeap[pos] = MaxHeap[VertexNum], MaxHeap.pop_back(), VertexNum--;
    if(parent >= 1 && MaxHeap[parent] < MaxHeap[pos]) MaxHeap_Up_Adjust(MaxHeap, pos, pos);
    // 逻辑冗余：这里的 if 条件检查其实在 MaxHeap_Down_Adjust 中存在，只需根据父节点的值判断是上浮还是下调即可
    // else if(lc <= VertexNum){
    //     if(rc <= VertexNum && MaxHeap[pos] < max(MaxHeap[lc], MaxHeap[rc]) || rc > VertexNum && MaxHeap[pos] < MaxHeap[lc]) MaxHeap_Down_Adjust(MaxHeap, pos, VertexNum - pos);
    // }
    else MaxHeap_Down_Adjust(MaxHeap, pos, VertexNum);// 使用 VertexNum 而不是 VertexNum - pos 是为了传递堆的大小边界

    //删除哨兵节点，恢复原数组长度（delete 长度减 1）
    MaxHeap.erase(MaxHeap.begin());
}
//利用小根堆模拟插入和删除过程
void MinHeap_Up_Adjust(vector<int>& MinHeap, int k, int VertexNum){
    MinHeap[0] = MinHeap[k];
    for(int i = k >> 1; i >= 1; i >>= 1){
        if(MinHeap[i] <= MinHeap[0]) break;
        else MinHeap[k] = MinHeap[i], k = i;
    }
    MinHeap[k] = MinHeap[0];
    //其实一样可以变得更优雅 ......
    //while(k >= 1 && MaxHeap[k >> 1] > MaxHeap[k]) swap(MaxHeap[k], MaxHeap[k >> 1]), k /= 2;
}
void MinHeapInsert(vector<int>& MinHeap, int val){
    //这两句一般是冗余的，这里只是为了确保后续操作是对下标从 1 开始的最大堆进行的（如果已知传进来的是确定下标的最大堆则无需这两句代码）
    VIndexAdjust(MinHeap);
    MinHeapBuild(MinHeap);
    // cout << "After MinHeapBuild（now 0 position is invaild）:\n";
    // printVector(MinHeap);
    
    MinHeap.push_back(val);
    int VertexNum = MinHeap.size() - 1, k = VertexNum;
    MinHeap_Up_Adjust(MinHeap, k, VertexNum);

    //删除哨兵节点，恢复原数组长度（insert 长度加 1）
    MinHeap.erase(MinHeap.begin());
}
void MinHeapDelete(vector<int>& MinHeap, int pos){
    //......
    VIndexAdjust(MinHeap);
    MinHeapBuild(MinHeap);
    // cout << "After MinHeapBuild（now 0 position is invaild）:\n";
    // printVector(MinHeap);

    int VertexNum = MinHeap.size() - 1, parent = pos / 2, lc = pos * 2, rc = pos * 2 + 1;
    MinHeap[pos] = MinHeap[VertexNum], MinHeap.pop_back(), VertexNum--;
    if(parent >= 1 && MinHeap[parent] > MinHeap[pos]) MinHeap_Up_Adjust(MinHeap, pos, pos);
    else MinHeap_Down_Adjust(MinHeap, pos, VertexNum);

    //删除哨兵节点，恢复原数组长度（delete 长度减 1）
    MinHeap.erase(MinHeap.begin());
}

//3. 插入排序

//3.(1) 普通插入排序
//将数组分为已排序和未排序部分，逐步将未排序的元素插入到已排序部分的适当位置
// 时间复杂度：
//   最坏情况：O(n²)
//   最佳情况：O(n)
//   平均情况：O(n²)
// 空间复杂度：O(1)（原地排序）
// 稳定性：不稳定
// （不带哨兵）
void InsertionSort_Without_SentinelNode(vector<int>& v){
    int n = v.size();
    for(int i = 1; i < n; i++){
        //此轮不符合插入条件（当前元素已经大于左边已排序元素），直接进行下一轮
        if(v[i] >= v[i - 1]) continue;

        int temp = v[i], j;
        //注意这里 for 循环内部千万不要再定义一遍 j ！！！在内层 for 循环中再定义 j，将导致外层 j 的值不会被更新，无法正确地插入元素，最终导致逻辑错误
        for(j = i - 1; j >= 0 && v[j] > temp; j--) v[j + 1] = v[j]; //移动元素
        v[j + 1] = temp;
    }
}
// （带哨兵）
void InsertionSort_With_SentinelNode(vector<int>& v){
    int n = v.size();
    VIndexAdjust(v);
    for(int i = 2; i <= n; i++){
        //此轮不符合插入条件（当前元素已经大于左边已排序元素），直接进行下一轮
        if(v[i] >= v[i - 1]) continue;

        v[0] = v[i];
        int j;
        //注意这里 for 循环内部千万不要再定义一遍 j ！！！在内层 for 循环中再定义 j，将导致外层 j 的值不会被更新，无法正确地插入元素，最终导致逻辑错误
        for(j = i - 1; v[j] > v[0]; j--) v[j + 1] = v[j]; //移动元素
        v[j + 1] = v[0];
    }
    //删除哨兵节点，恢复原数组长度
    v.erase(v.begin());
}
//插入排序优化
//先用折半查找找到应该插入的位置后再移动元素
//用折半查找优化（减少元素移动次数（虽然时间复杂度不变还是 O(n^2）；保持稳定性）
void InsertionSort_Optimize(vector<int>& v){
    int n = v.size();
    VIndexAdjust(v);
    for(int i = 2; i <= n; i++){
        //此轮不符合插入条件（当前元素已经大于左边已排序元素），直接进行下一轮
        if(v[i] >= v[i - 1]) continue;

        v[0] = v[i];
        int l = 0, r = i - 1;
        //终止条件为 l > r (即 l = r + 1)，r 为其插入位置下界， l 为其插入位置上界
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
        
        while(l <= r){
            //int mid = l + (r - l) / 2;
            //int mid = l + (r - l) >> 1; 不正确
            //！！！ '+'的优先级大于'>>' ！！！！！
            int mid = l + ((r - l) >> 1);
            if(v[0] < v[mid]) r = mid - 1;
            else l = mid + 1;//为保证算法的稳定性，找到相等的元素时继续再其右边寻找插入位置
        }
        for(int j = i - 1; j >= l; j--) v[j + 1] = v[j];
        v[l] = v[0];
    }
    //删除哨兵节点，恢复原数组长度
    v.erase(v.begin());
}

//3.(2) 希尔排序
// 希尔排序（Shell Sort）
// 希尔排序是一种改进的插入排序，通过将元素分组并对每个组进行插入排序，逐步减少组的大小，最终实现整体排序。它的核心思想是“局部有序可以促进整体有序”
// 时间复杂度：
//  最坏情况：O(n²)（依赖于增量的选择）
//  平均情况：O(n log n)（具体性能依赖于增量序列）
//  最佳情况：O(n)（当数组已经有序时）
// 空间复杂度：O(1)（原地排序）
// 稳定性：不稳定（因为在插入过程中可能会移动相同的元素）
void shellSort(vector<int>& v){
    int n = v.size();
    v.insert(v.begin(), 0);

    //将整个数组视为多个子数组，通常选择一个较大的增量（如数组长度的一半），并逐步减小增量
    for(int d = n >> 1; d > 0; d >>= 1){
        for(int i = d + 1; i <= n; i++){
            v[0] = v[i];
            int j;
            //注意添加边界条件 j >= 1 ！！！，不然会越界访问，且如果 v[0] 比所有元素都小，j 会减到负数，因为没有 j >= 1 的限制，会导致死循环
            for(j = i - d; j >= 1 && v[j] > v[0]; j -= d) v[j + d] = v[j];
            v[j + d] = v[0];
        }
    }
    v.erase(v.begin());
}

//4.快速排序

// 选择一个“基准”元素，将数组分为两部分：小于基准的和大于基准的。递归地对这两部分进行排序。
// 最坏情况：O(n²)（当数组已排序或逆序时）(二叉树树高最高时)
// 平均情况：O(n log n)
// 最佳情况：O(n log n)
// 空间复杂度：O(log n)（递归栈的空间）（含有 n 个节点的二叉树的高度）
// 稳定性：不稳定
int Partition(vector<int>& v, int l, int r){
    int pivot_key = v[l];
    //终止条件 l == r；找到枢轴元素
    while(l < r){
        //注意！！！写while 不是 if
        while(l < r && v[r] >= pivot_key) r--;
        v[l] = v[r];
        while(l < r && v[l] <= pivot_key) l++;
        v[r] = v[l];
    }
    v[l] = pivot_key;
    return l;
}
//类似于前序遍历的二叉树
void QuickSort(vector<int>& v, int l, int r){
    if(l >= r) return;
    int pivot =  Partition(v, l, r);
    QuickSort(v, l, pivot - 1);
    QuickSort(v, pivot + 1, r);
}
void QuickSort_With_Optimize(vector<int>& v, int l, int r){
    if(l >= r) return;
    if(r - l < 20){ InsertionSort_Optimize(v); return;}
    int pivot =  Partition(v, l, r);
    QuickSort(v, l, pivot - 1);
    QuickSort(v, pivot + 1, r);
}
// 快速排序优化
// 优化一：随机化快速排序
int randomizedPartition(vector<int>& v, int l, int r){
    //int pivot_key = v[l];//选 v[l] 为基准元素，则 v[l] 位置空出来，所以先从 r-- 开始遍历
    int pivot = l + rand() % (r - l + 1);  // 随机选择枢纽
    swap(v[pivot], v[l]);  // 将随机选择的枢纽移到 l 处，其他做法不变

    int pivot_key = v[l];

    while(l < r){
        while(l < r && v[r] >= pivot_key) r--;
        v[l] = v[r];
        while(l < r && v[l] <= pivot_key) l++;
        v[r] = v[l];        
    }
    v[l] = pivot_key; //将枢轴元素放回最终位置
    return l;
}
//类似于前序遍历的二叉树
void randomizedQuickSort(vector<int>& v, int l, int r){
    if(l >= r) return;
    //if(r - l < 20){ InsertionSort_Optimize(v); return;}
    int pivot = randomizedPartition(v, l, r);
    randomizedQuickSort(v, l, pivot - 1);
    randomizedQuickSort(v, pivot + 1, r);
}

// 优化二：中位数三分法
int medianOfThree(int a, int b, int c){
    return a < b ? (b < c ? b : (a < c ? c : a)) : (a < c ? a : (b < c ? c : b));
}
int medianOfThreePartition(vector<int>& v, int l, int r){
    //int pivot = v[l];//选 v[l] 为基准元素，则 v[l] 位置空出来，所以先从 r-- 开始遍历
    int mid = l + ((r - l) >> 1); // '+' 优先级高于 '>>'
    int pivot_key = medianOfThree(v[l], v[mid], v[r]);
    int pivot = v[l] == pivot_key ? l : (v[r] == pivot_key ? r : mid);
    swap(v[pivot], v[l]);  // 将中位数三分法选择的枢纽移到 l 处，其他做法不变

    while(l < r){
        while(l < r && v[r] >= pivot_key) r--;
        v[l] = v[r];
        while(l < r && v[l] <= pivot_key) l++;
        v[r] = v[l];        
    }
    v[l] = pivot_key; //将枢轴元素放回最终位置
    return l;
}
//类似于前序遍历的二叉树
void medianOfThreeQuickSort(vector<int>& v, int l, int r){
    if(l >= r) return;
    //if(r - l < 20){ InsertionSort_Optimize(v); return;}
    int medianOfThreePivot = medianOfThreePartition(v, l, r);
    medianOfThreeQuickSort(v, l, medianOfThreePivot - 1);
    medianOfThreeQuickSort(v, medianOfThreePivot + 1, r);
}

void text_Sort(vector<int>& v){
    sort(v.begin(), v.end());
}
//5. 归并排序

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
void Merge(vector<int>& v, int l, int mid, int r){
    vector<int> B;//用辅助数组
    int i, j, k;
    for(int val : v) B.push_back(val);//将 v 中的数据复制到 B 中
    //双指针，较小值存回 v （覆盖）（类比链表合并）
    for(i = l, j = mid + 1, k = i; i <= mid && j <= r; k++){
        if(B[i] <= B[j]) v[k] = B[i++];
        else v[k] = B[j++];
    }
    while(i <= mid) v[k++] = B[i++];
    while(j <= r) v[k++] = B[j++];
}
void MergeSort(vector<int>& v, int l, int r){
    //使用 l < r 作为递归终止条件可以确保每个递归调用都会对至少两个元素进行操作，从而保证每次递归都会缩小问题的规模
    //   假设数组长度为 5，即 v.size() = 5，...当递归到 l = 2 和 r = 3 时，l < r 仍然为真，递归会继续；最后，当 l = 3 和 r = 3 时，l < r 为假，递归停止
    //使用 l <= r 作为递归终止条件可能会导致某些递归调用不进行任何操作，可能会影响算法的效率，尤其是在处理小数组时
    //   使用同样的数组长度为 5，即 v.size() = 5，...当递归到 l = 2 和 r = 3 时，l <= r 为真，递归会继续；最后，当 l = 3 和 r = 3 时，l <= r 仍然为真，递归会继续，但这次递归调用不会进行任何操作，因为 l 和 r 指向同一个元素。
    //在归并排序中，通常推荐使用 l < r 作为递归终止条件
    if(l >= r) return;
    int n = v.size();
    //int mid = (l + r) >> 1;
    //int mid = l + (r - l) >> 1; 错
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
//！！！！！！！对小数组进行归并排序的优化
//性能大幅度提升
//优化前对于 10000 的数据 took 1376.39 milliseconds.
//优化后对于 10000 的数据 took 213.146 milliseconds.
void MergeSort_With_Optimize(vector<int>& v, int l, int r){
    if(l >= r) return;
    int mid = l + ((r - l) >> 1); 
    if(r - l < 20) InsertionSort_Optimize(v);
    else{
        MergeSort(v, l, mid);
        MergeSort(v, mid + 1, r);
        Merge(v, l, mid, r);
    }
}

void text_stable_sort(vector<int>& v){
    stable_sort(v.begin(), v.end());
}

//6. 基数排序
// 基数排序是一种非比较排序算法，主要用于整数排序。通过将数字分解为各个数位（如个位、十位、百位等），按位进行排序，从最低有效位到最高有效位（或反向）逐步排好序
// 时间复杂度：O(n k)（k 是基数的个数）
// 空间复杂度：O(n k)
// 稳定性：稳定
// 三步：
//     确定最大数：找到所有待排序数字中的最大值，确定其位数，即基数排序的“基数”
//     分配和收集：从最低位（个位）开始，根据当前位对数字进行分配（放置到临时数组中）和收集（从临时数组中取出）
//     重复步骤2：对每个数位重复步骤2，直到最高位（或反向）
int getMaxDigits(int x){
    if(x == 0) return 1;
    int digits = 0;
    while(x > 0) x /= 10, digits++;
    return digits;
}
void radixSort(vector<int>& v){
    //1. 确定最大数的位数
    int maxDigits = getMaxDigits(*max_element(v.begin(), v.end()));
    vector<int> output(v.size()), count(10, 0);
    for(int i = 0; i < maxDigits; i++){
        //2. 分配
        for(int num : v){
            int digit = num / (int)pow(10, i) % 10;
            count[digit]++;
        }
        //累加计数：将 count 数组转化为累加数组，从而可以确定每个元素在当前位的排序中的正确位置
        for(int j = 1; j < 10; j++) count[j] += count[j - 1];
        //3. 收集
        for(int j = v.size() - 1; j >= 0; j--){
            int digit = v[j] / (int)pow(10, i) % 10;
            output[count[digit] - 1] = v[j];
            count[digit]--;
        }
        for(int j = 0; j < v.size(); j++) v[j] = output[j];
        //在下一轮排序开始前时清空 count 数组，保证后续的计数累加正确
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


//二. 外部排序
//......


int main() {
    // 初始化测试数据
    srand(time(0));
    vector<int> v;
    for(int i = 0; i < 30000; i++) v.push_back(rand() % 1000); // 生成随机数组
    //printVector(v);
    vector<int> temp = v;
    cout << "bubbleSort :\n";
    v.clear();
    v = temp;
    Timer::measureTime("bubbleSort", bubbleSort, v); // 测量exampleFunction运行时间

    //printVector(v);
    cout << "selectionSort :\n";
    v.clear();
    v = temp;
    Timer::measureTime("selectionSort", selectionSort, v); // 测量exampleFunction运行时间

    //printVector(v);
    cout << "MaxHeapSort :\n";
    v.clear();
    v = temp;
    Timer::measureTime("MaxHeapSort", MaxHeapSort, v); // 测量exampleFunction运行时间
    //printVector(v);

    cout << "MinHeapSort: \n";
    v.clear();
    v = temp;
    Timer::measureTime("MinHeapSort", MinHeapSort, v);
    //printVector(v);

    cout << "MaxHeapInsert:\n";
    v.clear();
    v = temp;
    Timer::measureTime("MaxHeapInsert", MaxHeapInsert, v, 1000);
    //printVector(v);

    cout << "MaxHeapDelete:\n";
    v.clear();
    v = temp;
    Timer::measureTime("MaxHeapDelete", MaxHeapDelete, v, 1);
    cout << "After MaxHeapDelete:\n";
    //printVector(v);

    cout << "MinHeapInsert:\n";
    v.clear();
    v = temp;
    Timer::measureTime("MinHeapInsert", MinHeapInsert, v, 0);
    //printVector(v);

    cout << "MinHeapDelete:\n";
    v.clear();
    v = temp;
    Timer::measureTime("MinHeapDelete", MinHeapDelete, v, 1);
    cout << "After MinHeapDelete:\n";
    //printVector(v);

    cout << "InsertionSort_Without_SentinelNode:\n";
    v.clear();
    v = temp;
    Timer::measureTime("InsertionSort_Without_SentinelNode", InsertionSort_Without_SentinelNode, v);
    //printVector(v);

    cout << "InsertionSort_With_SentinelNode:\n";
    v.clear();
    v = temp;
    Timer::measureTime("InsertionSort_With_SentinelNode", InsertionSort_With_SentinelNode, v);
    //printVector(v);

    cout << "InsertionSort_Optimize:\n";
    v.clear();
    v = temp;
    Timer::measureTime("InsertionSort_Optimize", InsertionSort_Optimize, v);
    //printVector(v);

    cout << "shellSort:\n";
    v.clear();
    v = temp;
    Timer::measureTime("shellSort", shellSort, v);
    //printVector(v);

    cout << "MyQuickSort:\n";
    v.clear();
    v = temp;
    Timer::measureTime("QuickSort", QuickSort, v, 0, v.size() - 1);
    //printVector(v);

    cout << "QuickSort_With_Optimize:\n";
    v.clear();
    v = temp;
    Timer::measureTime("QuickSort_With_Optimize", QuickSort_With_Optimize, v, 0, v.size() - 1);
    //printVector(v);

    cout << "C++ STL sort()\n";
    v.clear();
    v = temp;
    Timer::measureTime("C++ STL sort()", text_Sort, v);
    // printVector(v);

    cout << "randomizedQuickSort:\n";
    v.clear();
    v = temp;
    Timer::measureTime("randomizedQuickSort", randomizedQuickSort, v, 0, v.size() - 1);
    //printVector(v);

    cout << "medianOfThreeQuickSort:\n";
    v.clear();
    v = temp;
    Timer::measureTime("medianOfThreeQuickSort", medianOfThreeQuickSort, v, 0, v.size()-  1);
    //printVector(v);

    //为啥啊为啥啊我的归并排序这么慢
    cout << "MergeSort:\n";
    v.clear();
    v = temp;
    Timer::measureTime("MergeSort", MergeSort, v, 0, v.size()-  1);
    //printVector(v);

    cout << "MergeSort_With_Optimize:\n";
    v.clear();
    v = temp;
    Timer::measureTime("MergeSort_With_Optimize", MergeSort_With_Optimize, v, 0, v.size()-  1);
    //printVector(v);

    cout << "C++ STL stable_sort()\n";
    v.clear();
    v = temp;
    Timer::measureTime("C++ STL stable_sort()", text_stable_sort, v);
    //printVector(v);

    cout << "radixSort:\n";
    v.clear();
    v = temp;
    Timer::measureTime("radixSort", radixSort, v);
    //printVector(v);
    return 0;
}
