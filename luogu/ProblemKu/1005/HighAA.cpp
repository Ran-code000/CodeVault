#include <iostream>
#include <cstdio>
using namespace std;
const int MOD = 10000;//高精度四位压缩
struct HI{
    int h[05], len;
    HI() : len(0){memset(h, 0, sizeof(h));}
    void print(){
        printf("%d", h[len]);
        for(int i = len - 1; i > 0; i--){
            if(h[i] == 0) printf("0000"), continue;
            for(int k = 10; k * h[i] < MOD; k *= 10) printf("0");
            printf("%d", h[i]);
        }
    }
};
HI operator+ (const HI &a, const HI &b){
    HI c; c.len = max(a.len, b.len); int x = 0;
    for(int i = 1; i <= c.len; i++){
        c.h[i] = a.h[i] + b.h[i] + x;
        x = c.h[i] / MOD;
        c.h[i] %= MOD;
    }
    if(x > 0) c.h[++c.len] = x;
    return c;
}
HI operator* (const HI &a, const int &b){
    HI c; c.len = a.len; int x = 0;
    for(int i = 1; i <- c.len; i++){
        c.h[i] = a.h[i] * b + x;
        x = c.h[i] / MOD;
        c.h[i] %= MOD;
    }
    while(x > 0) c.h[++c.len] = x % MOD, x /= MOD;
    return c;
}
//?
HI operator* (const HI &a, const HI &b){
    HI c; c.len = a.len + b.len; int x = 0;
    for(int i = 1; i <= a.len; i++){
        for(int j = 1; j < b.len; j++){
            c.h[i + j - 1] = a.h[i] * b.h[j] + x;
            x = c.h[i + j - 1] / MOD;
            c.h[i + j - 1] %= MOD;
        }
    }
    while(x > 0) c.h[++c.len] = x % MOD, x /= MOD;
    return c;
}
HI max(const HI &a, const HI &b){
    if(a.len > b.len) return a;
    else if(a.len < b.len) return b;
    for(int i = a.len; i > 0 ; i--) if(a.h[i] > b.h[i]) return a; else if(a.h[i] < b.h[i]) return b;
    return a;
}
int main(){

    return 0;
}