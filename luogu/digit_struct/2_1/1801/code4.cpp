#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
int a[200001],b[200001];
priority_queue<int,vector<int>,greater<int> >qs;//小根堆 
priority_queue<int> qb;//大根堆 
int main(){
    int m,n;
    int s,k=1;
    cin>>m>>n;
    for(int i=1;i<=m;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int i=1;i<=m;i++){
        qb.push(a[i]);
        if(qb.size()>s){
            qs.push(qb.top());//如果b堆中堆数大于目前应取的总共i个元素,就把多余的放入c堆中,也就是把更大的放入c堆中 
            qb.pop();//在b堆中把它删掉 
        }
        while(b[k]==i){
            s++;
            cout<<qs.top()<<"\n";
            qb.push(qs.top());//如果有多次就把它多高到另一个数组里,之后再重新来一遍
            //这样就能保证第n..n+m都不重复,因为a[n]>a[n+1]>a[n+2]>...>a[n+m] 
            qs.pop();
            k++;
        }
    }
    return 0;
}