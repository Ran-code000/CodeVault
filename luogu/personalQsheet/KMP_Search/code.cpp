#include <iostream>
#include <string>
#include <vector>

using namespace std;
//预处理 next 数组
void Next_pre(string p, vector<int> &Next){
    //i 从 1 开始处理，因为第一位必然是 0
    //p.size() 的返回类型是 unsigned， 但如果p.length() 为 0 ，p.length() - 1 是一个很大的数， 需要严谨的写为(int)
    for(int i = 1, j = 0; i < (int)p.length(); i++){
        //先对 j 判空，若已经在 0 的位置则不跳转
        while(j && p[i] != p[j]) j = Next[j - 1]; //如果不相等 j 跳到 j 的上一个字母的 Next 数组所标的位置
        if(p[i] == p[j]) Next[i] = ++j; //如果一样，先将 j 往后移动一位，将此时 j 的位置保存到此时 i 的 next 的数组中
    }
}

int KMP_match(string s, string p, int begin){
    vector<int> Next(p.length()); //封装性，函数内定义 Next 数组
    Next_pre(p, Next);
    for(int i = begin, j = 0; i < (int)s.length(); i++){
        while(j && s[i] != p[j]) j = Next[j - 1];
        if(s[i] == p[j]) j++; 
        if(j == (int)p.length()){
            //匹配成功
            return i - (int)p.length() + 1; //返回第一个找到目标字串在母串中的索引
        }
    }
    return -1;
}
int main()
{
#ifdef debug
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    string s = "abcxabcabxabcdabcdabcy";
    string p1 = "abcdabcy";
    string p2 = "xabc";
    cout << KMP_match(s, p1, 0) << endl; //返回第一个找到的位置
    cout << KMP_match(s, p2, KMP_match(s, p2, 0)) << endl; // //返回第二个找到的位置，以此类推
    //Next 数组可以求出最小的前缀循环节：i + 1 - Next[i]
    string p3 = "abbabbabbabb";
    vector<int> Next(p3.length());
    Next_pre(p3, Next);
    for(int i = 0; i < (int)p3.length(); i++) cout << i + 1 - Next[i] << " ";
    
    return 0;
}