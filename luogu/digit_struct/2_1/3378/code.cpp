
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

inline long long read() {
    long long x = 0;
    char c = getchar();
    for (; !isdigit(c); c = getchar());
    for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - '0';
    return x;
}

#define MAX_N 1000000
#define fa(i) (i >> 1)
#define lc(i) (i << 1)
#define rc(i) ((i << 1) | 1)
long long data[MAX_N + 5], cnt;

void up_update(int ind) {
    if (ind == 1) return;
    if (data[ind] < data[fa(ind)]) {
        swap(data[ind], data[fa(ind)]);
        up_update(fa(ind));
    }
    return ;
}

void down_update(int x) {
    if (lc(x) > cnt) return;
    int ind = x;
    if (data[x] < data[lc(x)]) ind = lc(x);
    if (rc(x) <= cnt && data[ind] < data[rc(x)]) ind = rc(x);
    if (ind == x) return ;
    swap(data[x], data[ind]);
    down_update(ind);
    return ;
}

void push(long long x) {
    data[++cnt] = x;
    up_update(cnt);
    return ;
}

void pop() {
    data[1] = data[cnt--];
    down_update(1);
    return ;
}

int main() {
    int n;
    n = read();
    for (int i = 0, op; i < n; i++) {
        op = read();
        switch (op) {
            case 1 : {
                long long x;
                x = read();
                push(x);
            } break;
            case 2 : {
                printf("%lld\n", data[1]);
            } break;
            case 3 : {
                pop();
            } break;
        }
    }
    return 0;
}