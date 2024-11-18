#include <iostream>
#include <chrono>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;
class HuffmanTree{
    struct HuffmanNode{
        char data;
        int freq;
        HuffmanNode* l;
        HuffmanNode* r;
        HuffmanNode(char data, int freq) : data(data), freq(freq), l(nullptr), r(nullptr){}
    };
    struct _Compare{
        bool operator() (HuffmanNode* a, HuffmanNode* b){ return a->freq > b->freq;}
    };
    void generateHuffmanCodes(HuffmanNode* root, const string& code, unordered_map<char, string>& HuffmanCodes){
        if(root == nullptr) return;
        if(root->l == nullptr && root->r == nullptr) HuffmanCodes[root->data] = code;
        generateHuffmanCodes(root->l, code + '0', HuffmanCodes);
        generateHuffmanCodes(root->r, code + '1', HuffmanCodes);
    }
    HuffmanNode* root;
public:
    HuffmanTree() : root(nullptr){}
    ~HuffmanTree(){ DeleteHuffmanTree(root);}
    void buildHuffmanTree(const vector<pair<char, int>>& frequencies){
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, _Compare> minHeap;
        //创建叶节点并加入优先队列
        for(const auto& pair : frequencies) minHeap.push(new HuffmanNode(pair.first, pair.second));
        //构建 HuffmanTree
        while(minHeap.size() > 1){
            HuffmanNode* l = minHeap.top(); minHeap.pop();
            HuffmanNode* r = minHeap.top();
            minHeap.pop();
            //创建新节点（freq = 左右节点之和）
            HuffmanNode* newnode = new HuffmanNode('\0', l->freq + r->freq);
            //连接节点！！！！！！
            newnode->l = l;
            newnode->r = r;
            minHeap.push(newnode);
        }
        root =  minHeap.top();
    }
    void generateHuffmanCodes(const string& code, unordered_map<char, string>& HuffmanCodes){
       generateHuffmanCodes(root, code, HuffmanCodes);
    }
    void DeleteHuffmanTree(HuffmanNode* node){
        if(node){
            DeleteHuffmanTree(node->l);
            DeleteHuffmanTree(node->r);
            delete node;
        }
    }
    //friend class _Compare;
};
//text fun
int main() {
   auto start = chrono::high_resolution_clock::now();
    // 示例字符频率
    vector<pair<char, int>> frequencies = {{'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}};
    // 构建哈夫曼树
    HuffmanTree huffmantree;
    huffmantree.buildHuffmanTree(frequencies);
    // 生成哈夫曼编码
    unordered_map<char, string> huffmanCodes;
    huffmantree.generateHuffmanCodes("", huffmanCodes);
    // 输出哈夫曼编码
    cout << "Huffman Codes:\n";
    for(const auto& pair : huffmanCodes) cout << pair.first << ": " << pair.second << endl;
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "runnning time: " << duration << "μs" << endl;
    return 0;
}
