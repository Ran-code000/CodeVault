#include <iostream>
#include <queue>
using namespace std;
priority_queue<int> q;
int main(){
    for(int i = 1; i < 10; i++){
        if(i % 2) q.push(i * 2);
        else q.push(i);
    }
    for(int i = 1; i < 10; i++){
        cout << q.top() << " ";
        q.pop();
    }
    cout << "\n";
    return 0;
}