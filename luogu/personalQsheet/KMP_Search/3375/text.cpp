#include <iostream>
#include <string>
#include <vector>
using namespace std;
string s1, s2;
vector<int> matches, Next;
void Next_pre(string p, vector<int> &Next){
    for(int i = 1, j = 0; i < p.size(); i++){
        while(j && p[i] != p[j]) j = Next[j - 1];
        if(p[i] == p[j]) Next[i] = ++j;
    }
}
vector<int> KMP_search(string s, string p, int begin){
    vector<int> match;
    Next_pre(p, Next);
    for(int i = begin, j = 0; i < s.size(); i++){
        while(j && s[i] != p[j]) j = Next[j - 1];
        if(s[i] == p[j]) j++;
        if(j == p.size()){
            match.push_back(i - (j - 1) + 1);
            j = Next[j - 1];
        }
    }
    return match;
}
int main(){
    cin >> s1 >> s2;
    Next.resize(s2.size());
    matches = KMP_search(s1, s2, 0);
    for(auto val : matches) cout << val << "\n"; 
    for(auto val : Next) cout << val << " ";
    return 0;
}