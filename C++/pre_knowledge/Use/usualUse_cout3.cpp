# include <iostream>
# include <iomanip>

using namespace std ;

int main()
{
    cout << left << setw(10) << setfill('*') << dec << 123 << endl;

    cout << right << hex << setw(10) << setfill('*') << 123 << endl;

    cout << internal << oct << setw(10) << setfill('*') << 123 << endl;

    cout << setprecision(4) << 3.1415926 << endl;

    cout << fixed << setprecision(3) << 3.1415 <<endl;

    cout << scientific << setprecision(2) << 31415.92 << endl;

    cout << setbase(16) << 255 << endl;

    cout << showbase << 255 << endl;

    cout << showpos << 50 << endl;

    cout << noshowpos << endl;

    cout << noshowbase << endl;

    cout << boolalpha << true << endl;

    cout << noboolalpha << true << endl;

    cout << uppercase << 1.23 << endl;

    return 0;
}

