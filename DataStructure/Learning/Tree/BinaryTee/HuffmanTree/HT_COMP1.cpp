#include <iostream>
#include <chrono>
#include <queue>
#include <vector>
#include <unordered_map>
#include <functional>
using namespace std;
class HuffmanTree{
    struct HuffmanNode{
        char data;
        int freq;
        HuffmanNode* l;
        HuffmanNode* r;
        HuffmanNode(char data, int freq) : data(data), freq(freq), l(nullptr), r(nullptr){}
        //bool operator< (HuffmanNode* a){ return freq > a->freq;}
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
    //定义比较函数法一
    //定义比较函数时，如果作为类成员函数，一定要声明 static； 如果不是，必须是全局函数
    static bool COMP(HuffmanTree::HuffmanNode* a, HuffmanTree::HuffmanNode* b) { return a->freq > b->freq;}

    //function<bool(HuffmanNode *, HuffmanNode *)> b = COMP;
    void buildHuffmanTree(const vector<pair<char, int>>& frequencies){
        //定义比较函数法一
        //自己实现的函数，需要在模板中传入函数的类型，形参中还得传入函数实体，否则构造不出来；调用的是带参数的构造函数；
        //priority_queue<HuffmanNode*, vector<HuffmanNode*>, decltype(&COMP)> minHeap(COMP); 
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, decltype(&COMP)> minHeap(COMP); 
        
        //创建叶节点并加入优先队列
        for(const auto& pair : frequencies) minHeap.push(new HuffmanNode(pair.first, pair.second));
        //构建 HuffmanTree
        while(minHeap.size() > 1){
            HuffmanNode* l = minHeap.top();
            minHeap.pop();
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
