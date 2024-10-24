#include <iostream>
#include <chrono>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;
struct HuffmanNode{
    char data;
    int freq;
    HuffmanNode* l;
    HuffmanNode* r;
    HuffmanNode(char data, int freq) : data(data), freq(freq), l(nullptr), r(nullptr){}
};
//此时可以实现第 16 句的代码，因为节点定义在了类的外面，而不是作为私有成员
//相应的可以实现第 42 行代码
bool COMP (HuffmanNode* a, HuffmanNode* b){ return a->freq > b->freq;}
class HuffmanTree{
    // struct HuffmanNode{
    //     char data;
    //     int freq;
    //     HuffmanNode* l;
    //     HuffmanNode* r;
    //     HuffmanNode(char data, int freq) : data(data), freq(freq), l(nullptr), r(nullptr){}
    // };
    //定义比较函数法二（最好还是把节点写在类的外面）
    // struct _Compare{
    //     bool operator() (HuffmCOMPanNode* a, HuffmanNode* b){ return a->freq > b->freq;}
    // };
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
        //<模板参数类型> ： 构造比较函数的时候若是函数对象（传入类名（因为类名是自定义的类型名） ———— 见 HT_COMP1.cpp）
        //                                  若是函数（传入decltype(&函数名)（因为函数名不是类型名，decltype 用来推断类型名，decltype传入的是待推断类型的地址））
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
    //哈夫曼编码
    const string encode(const string& a, unordered_map<char, string> huffmanCodes){
        string encodedStr;
        for(const char& c : a) encodedStr += huffmanCodes[c];
        return encodedStr;
    }
    //哈夫曼译码
    const string decode(const string& a){
        HuffmanNode* curr = root;
        string decodedStr;
        for(const char& c : a){
            curr = (c == '1') ? curr->r : curr->l;
            if(curr->l == nullptr && curr->r == nullptr) decodedStr += curr->data, curr = root;
        }
        return decodedStr;
    }
};
//text fun
int main() {
   auto start = chrono::high_resolution_clock::now();
    // 示例字符频率
    vector<pair<char, int>> frequencies = {{'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}};
    cout << "{'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}\n\n";
    // 构建哈夫曼树
    HuffmanTree huffmantree;
    huffmantree.buildHuffmanTree(frequencies);
    // 生成哈夫曼编码
    unordered_map<char, string> huffmanCodes;
    huffmantree.generateHuffmanCodes("", huffmanCodes);
    // 输出哈夫曼编码
    cout << "Huffman Codes:\n";
    for(const auto& pair : huffmanCodes) cout << pair.first << ": " << pair.second << endl;
    //哈夫曼编码
    const string input = "abcdef";
    cout << input << endl;
    const string encoded = huffmantree.encode(input, huffmanCodes);
    cout << "Encoded: " << encoded << endl;
    //哈夫曼解码
    const string decoded = huffmantree.decode(encoded);
    cout << "Decoded: " << decoded << endl;

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "runnning time: " << duration << "μs" << endl;
    return 0;
}
