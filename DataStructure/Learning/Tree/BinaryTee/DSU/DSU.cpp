#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>
using namespace std;
class DisjointSetUnion{
    vector<int> parents;
    vector<int> rank;
public: 
    DisjointSetUnion(int n){
        parents.resize(n);
        rank.resize(n);
        for(int i = 0; i < n; i++) parents[i] = -1;
    }
    int Find_Without_Optimize(int x){
        while(parents[x]) x = parents[x];
        return parents[x];
    }
    int Find_With_Optimize(int x){
        int root = x;
        while(parents[root] >= 0) root = parents[root];
        while(x != root){
            int temp = parents[x];
            parents[x] = root;
            x = temp;
        }
        return root;
    }
    void Union_Sets_Without_Optimize(int root1, int root2){
        if(root1 == root2) return;
        parents[root2] = root1;
    }
    void Union_Sets_With_Optimize(int root1, int root2){
        if(root1 == root2) return;
        if(abs(parents[root1]) > abs(parents[root2])) parents[root1] += parents[root2], parents[root2] = root1;
        else if(abs(parents[root1]) < abs(parents[root2])) parents[root2] += parents[root1], parents[root1] = root2;
        else parents[root1] = root2, parents[root2]++;

    }
    bool connected(int a, int b){ return Find_With_Optimize(a) == Find_With_Optimize(b);}
};
int main(){
    cout << "Without optimize:\n";
    auto start1 = chrono::high_resolution_clock::now();
    DisjointSetUnion dsu1(10);
    dsu1.Union_Sets_Without_Optimize(1, 2);
    dsu1.Union_Sets_Without_Optimize(2, 3);
    dsu1.Union_Sets_Without_Optimize(4, 5);
    dsu1.Union_Sets_Without_Optimize(6, 7);
    dsu1.Union_Sets_Without_Optimize(5, 6);

    cout << "1 and 3 connected: " << dsu1.connected(1, 3) << endl;  // 输出 1 (true)
    cout << "1 and 4 connected: " << dsu1.connected(1, 4) << endl;  // 输出 0 (false)
    cout << "5 and 7 connected: " << dsu1.connected(5, 7) << endl;  // 输出 1 (true)

    dsu1.Union_Sets_Without_Optimize(1, 5);
    cout << "1 and 4 connected after union: " << dsu1.connected(1, 4) << endl;  // 输出 1 (true)
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
    cout << "runnning time: " << duration1 << "μs" << endl;

    cout << "With optimize:\n";
    auto start2 = chrono::high_resolution_clock::now();
    DisjointSetUnion dsu2(10);
    dsu2.Union_Sets_With_Optimize(1, 2);
    dsu2.Union_Sets_With_Optimize(2, 3);
    dsu2.Union_Sets_With_Optimize(4, 5);
    dsu2.Union_Sets_With_Optimize(6, 7);
    dsu2.Union_Sets_With_Optimize(5, 6);

    cout << "1 and 3 connected: " << dsu2.connected(1, 3) << endl;  // 输出 1 (true)
    cout << "1 and 4 connected: " << dsu2.connected(1, 4) << endl;  // 输出 0 (false)
    cout << "5 and 7 connected: " << dsu2.connected(5, 7) << endl;  // 输出 1 (true)

    dsu2.Union_Sets_With_Optimize(1, 5);
    cout << "1 and 4 connected after union: " << dsu2.connected(1, 4) << endl;  // 输出 1 (true)
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
    cout << "runnning time: " << duration2 << "μs" << endl;
    return 0;
}
