#include <iostream>
#include <cmath>
using namespace std;
int main(){
    cout << "0.0 / 0.0 : " << 0.0 / 0.0 << endl;
    cout << "0.0 / inf : " << 1.0 /  << endl;
    cout << std::isnan(0.0 / 0.0) << endl;
    cout << 1 << endl;
    return 0;
}