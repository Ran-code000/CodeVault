#include <iostream>
#include <string>
#include <vector>

using namespace std;

void Next_pre(string p, vector<int> &Next){
    for(int i = 1, j = 0; i < (int)p.length(); i++){
        while(j && p[i] != p[j]) j = Next[j - 1];
        if(p[i] == p[j]) Next[i] = ++j;
    }
}

vector<int> KMP_match(string s, string p, int begin){
    vector<int> Next(p.length()), matches;
    Next_pre(p, Next);
    
    for(int i = begin, j = 0; i < (int)s.length(); i++){
        while(j && s[i] != p[j]) j = Next[j - 1];
        if(s[i] == p[j]) j++;
        if(j == (int)p.length()){
            matches.push_back(i - (p.length() - 1) + 1);
            j = Next[j - 1];
        }
    }
    return matches;
}

int main(){
    string s1, s2;
    cin >> s1 >> s2;

    int begin = 0;
    //为降低时间复杂度优化代码，应避免对 KMP_match 函数的多次调用，因为每次调用 KMP_match 都会重新计算 Next 数组，这是不必要的
    /*int result;
    while((result = KMP_match(s1, s2, begin)) != -1){
        cout << result + 1 << "\n";
        begin = result + 1; 
        if(s1.length() - 1 - begin < s2.length()) break;
    }*/

    vector<int> Next(s2.length());
    Next_pre(s2, Next);
    vector<int> matches = KMP_match(s1, s2, 0);
    for(auto val : matches) cout << val << "\n";
    for(auto val : Next) cout << val << " ";
    return 0;
}