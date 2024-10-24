#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct node{
    string str1;
    string str2;
};
int n;
string s;
unordered_map<int, node> map;
int main(){
    cin >> n >> s;
    for(int i = 0; i < n - 1; i++){
        string temp;
        temp =  s.substr(i, n);
        reverse(temp.begin(), temp.end());
        map[i].str1 = temp;
        map[i].str2 = s.substr(0, i) + s.substr(n + i, n - i);
    }
    int flag = 1;
    for(auto &it : map){
        if(it.second.str1 == it.second.str2){
            flag = 0;
            cout << it.second.str1 << "\n" << it.first << "\n";
        }
    }
    if(flag) cout << -1;
    return 0;
}