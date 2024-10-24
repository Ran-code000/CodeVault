#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include "MeasureTime.h"
/*
！！！本代码可确保实现逻辑正确，打印无误，因为采用 10,000,000 的数据量，
设置了堆展示开关，开启后会在每次调整后打印堆（！！！先调小数据量）
   //printVector(v);    10000000;
直接运行可看到每个操作的运行时间
*/
using namespace std;
void printVector(vector<int> v){ 
    for(int i = 0; i < v.size(); i++) cout << v[i] << " "; 
    cout << endl;
    for(int i = 0; i < v.size(); i++){
        int cnt = 0;
        while(v[i]) v[i] /= (11 - 1), cnt++;
        cout << left << setw(cnt) << i + 1 << " ";
    }
    cout << endl; 
}
void HeapIndexAdjust(vector<int>& Heap){ Heap.insert(Heap.begin(), 0);}
//大根堆排正序
void MaxHeap_Down_Adjust(vector<int>& MaxHeap, int k, int VertexNum){
    MaxHeap[0] = MaxHeap[k];
    for(int i = 2 * k; i <= VertexNum; i *= 2){
        if(i + 1 <= VertexNum && MaxHeap[i + 1] > MaxHeap[i]) i++;
        if(MaxHeap[0] >= MaxHeap[i]) break;
        else MaxHeap[k] = MaxHeap[i], k = i;
    }
    MaxHeap[k] = MaxHeap[0];
}
void MaxHeapBuild(vector<int>& MaxHeap){
    int VertexNum = MaxHeap.size() - 1;
    for(int i = VertexNum / 2; i >= 1; i--) MaxHeap_Down_Adjust(MaxHeap, i, VertexNum);
}
void MaxHeapSort(vector<int>& MaxHeap){
    HeapIndexAdjust(MaxHeap);
    int VertexNum = MaxHeap.size() - 1;
    MaxHeapBuild(MaxHeap);
    for(int i = VertexNum; i > 1; i--){
        swap(MaxHeap[1], MaxHeap[i]);
        MaxHeap_Down_Adjust(MaxHeap, 1, i - 1);
    }
    MaxHeap.erase(MaxHeap.begin());
}
//小根堆排逆序
void MinHeap_Down_Adjust(vector<int>& MinHeap, int k, int VertexNum){
    MinHeap[0] = MinHeap[k];
    for(int i = 2 * k; i <= VertexNum; i *= 2){
        if(i + 1 <= VertexNum && MinHeap[i + 1] < MinHeap[i]) i++;
        if(MinHeap[0] <= MinHeap[i]) break;
        else MinHeap[k] = MinHeap[i], k = i;
    }
    MinHeap[k] =MinHeap[0];
}
void MinHeapBuild(vector<int>& MinHeap){
    int VertexNum = MinHeap.size() - 1;
    for(int i = VertexNum / 2; i >= 1; i--) MinHeap_Down_Adjust(MinHeap, i, VertexNum);
}
void MinHeapSort(vector<int>& MinHeap){
    HeapIndexAdjust(MinHeap);
    MinHeapBuild(MinHeap);
    int VertexNum = MinHeap.size() - 1;
    for(int i = VertexNum; i > 1; i--){
        swap(MinHeap[1], MinHeap[i]);
        MinHeap_Down_Adjust(MinHeap, 1, i - 1);
    }
    MinHeap.erase(MinHeap.begin());
}
//利用大根堆模拟插入和删除过程
void MaxHeap_Up_Adjust(vector<int>& MaxHeap, int k, int VertexNum){
    // MaxHeap[0] = MaxHeap[k];
    // for(int i = k / 2; i >= 1; i /= 2){
    //     if(MaxHeap[i] >= MaxHeap[0]) break;
    //     else MaxHeap[k] = MaxHeap[i], k = i;
    // }
    // MaxHeap[k] = MaxHeap[0];
    //因为人需要变得优雅，码也是
    while(k / 2 >= 1 && MaxHeap[k / 2] < MaxHeap[k]) swap(MaxHeap[k], MaxHeap[k / 2]), k /= 2;
}
void MaxHeapInsert(vector<int>& MaxHeap, int val){
    //......
    HeapIndexAdjust(MaxHeap);
    MaxHeapBuild(MaxHeap);
    // cout << "After MaxHeapBuild:\n";
    // printVector(MaxHeap);

    MaxHeap.push_back(val);
    int VertexNum = MaxHeap.size() - 1, k = VertexNum;
    MaxHeap_Up_Adjust(MaxHeap, k, VertexNum);
    MaxHeap.erase(MaxHeap.begin());
}
void MaxHeapDelete(vector<int>& MaxHeap, int pos){
    //......
    HeapIndexAdjust(MaxHeap);
    MaxHeapBuild(MaxHeap);
    // cout << "After MaxHeapBuild:\n";
    // printVector(MaxHeap);

    int VertexNum = MaxHeap.size() - 1, parent = pos / 2, lc = pos * 2, rc = pos * 2 + 1;
    MaxHeap[pos] = MaxHeap[VertexNum], MaxHeap.pop_back(), VertexNum--;
    if(parent >= 1 && MaxHeap[parent] < MaxHeap[pos]) MaxHeap_Up_Adjust(MaxHeap, pos, pos);
    // else if(lc <= VertexNum){
    //     if(rc <= VertexNum && MaxHeap[pos] < max(MaxHeap[lc], MaxHeap[rc]) || rc > VertexNum && MaxHeap[pos] < MaxHeap[lc]) MaxHeap_Down_Adjust(MaxHeap, pos, VertexNum - pos);
    //  使用 VertexNum 而不是 VertexNum - pos 是为了传递堆的大小边界
    // }
    else MaxHeap_Down_Adjust(MaxHeap, pos, VertexNum);

    MaxHeap.erase(MaxHeap.begin());
}
//利用小根堆模拟插入和删除过程
void MinHeap_Up_Adjust(vector<int>& MinHeap, int k, int VertexNum){
    // MinHeap[0] = MinHeap[k];
    // for(int i = k / 2; i >= 1; i /= 2){
    //     if(MinHeap[i] <= MinHeap[0]) break;
    //     else MinHeap[k] = MinHeap[i], k = i;
    // }
    // MinHeap[k] = MinHeap[0];
    while(k / 2 >= 1 && MinHeap[k / 2] > MinHeap[k]) swap(MinHeap[k], MinHeap[k / 2]), k /= 2;
}
void MinHeapInsert(vector<int>& MinHeap, int val){
    //......
    HeapIndexAdjust(MinHeap);
    MinHeapBuild(MinHeap);
    // cout << "After MinHeapBuild:\n";
    // printVector(MinHeap);

    MinHeap.push_back(val);
    int VertexNum = MinHeap.size() - 1, k = VertexNum;
    MinHeap_Up_Adjust(MinHeap, k, VertexNum);

    MinHeap.erase(MinHeap.begin());
}
void MinHeapDelete(vector<int>& MinHeap, int pos){
    //......
    HeapIndexAdjust(MinHeap);
    MinHeapBuild(MinHeap);
    // cout << "After MinHeapBuild:\n";
    // printVector(MinHeap);

    int VertexNum = MinHeap.size() - 1, parent = pos / 2, lc = pos * 2, rc = pos * 2 + 1;
    MinHeap[pos] = MinHeap[VertexNum], MinHeap.pop_back(), VertexNum--;
    if(parent >= 1 && MinHeap[parent] > MinHeap[pos]) MinHeap_Up_Adjust(MinHeap, pos, pos);
    else MinHeap_Down_Adjust(MinHeap, pos, VertexNum);

    MinHeap.erase(MinHeap.begin());
}
int main(){
    srand(time(0));
    vector<int> v;
    for(int i = 0; i < 10000000; i++) v.push_back(rand() % 100);
    //cout << "The vector is :\n";
    //for(int i : v) cout << i << " "; cout << endl;
    cout << "MaxHeapSort :\n";
    vector<int> temp = v;
    Timer::measureTime("MaxHeapSort", MaxHeapSort, v); // 测量exampleFunction运行时间
    //printVector(v);
    cout << "MinHeapSort: \n";
    v = temp;
    Timer::measureTime("MinHeapSort", MinHeapSort, v);
    //printVector(v);
    cout << "MaxHeapInsert:\n";
    v = temp;
    Timer::measureTime("MaxHeapInsert", MaxHeapInsert, v, 1000);
    //printVector(v);
    cout << "MaxHeapDelete:\n";
    v = temp;
    Timer::measureTime("MaxHeapDelete", MaxHeapDelete, v, 1);
    cout << "After MaxHeapDelete:\n";
    //printVector(v);
    cout << "MinHeapInsert:\n";
    v = temp;
    Timer::measureTime("MinHeapInsert", MinHeapInsert, v, 0);
    //printVector(v);
    cout << "MinHeapDelete:\n";
    v = temp;
    Timer::measureTime("MinHeapDelete", MinHeapDelete, v, 1);
    cout << "After MinHeapDelete:\n";
    //printVector(v);
    v = temp;
    return 0;
}