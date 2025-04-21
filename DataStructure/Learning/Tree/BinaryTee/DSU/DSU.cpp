#include <iostream>
#include <vector>
using namespace std;

class DisjointSet
{
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int size) : parent(size), rank(size, 0)
    {
        for (int i = 0; i < size; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]); // 路径压缩
        }
        return parent[x];
    }

    void unionSets(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY)
        {
            if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

int main()
{
    int N = 5; // 实际大小根据题目而定
    DisjointSet dsu(N);
    dsu.unionSets(1, 2);
    dsu.unionSets(2, 3);
    dsu.unionSets(3, 4);
    int connected = dsu.find(1) == dsu.find(4) ? 1 : 0; // 判断 1 和 4 是否连通
    cout << connected << endl;                          // 应输出 1
    return 0;
}