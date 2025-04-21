#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
class String{
public:
    String() : n(0), ca(16), str(new char[16]) { str[0] = '\0';}
    String(const char* s) : n(strlen(s)), ca(n * 2), str(new char[ca]) { strcpy(str, s);}
    String(const String& ot) : n(ot.n), ca(ot.ca), str(new char[ca]) { strcpy(str, ot.str);}
    ~String() { delete[] str;}
    const char* c_str() const { return str;}
    void clear(){ 
        delete[] str;
        n = 0;
        ca = 16;
        str = new char[ca];
        str[0] = '\0';
    }
    String& operator+=(char c) {
        if (n + 1 >= ca) {
            ca *= 2;
            if (size() < 0) { // Too many elements
                n = 1 << 30;  // Good luck allocating 2 ^ 30 elements
            }
            char* newStr = new char[ca];
            strcpy(newStr, str);
            delete[] str;
            str = newStr;
        }
        str[n++] = c;  // Append c to the end of str
        str[n] = '\0'; // Null terminate the string
        return *this;
    }
    int size() const { return n; }
    int capacity() const { return ca; }
    const char& operator[](int index) const {return str[index];}
    friend ostream& operator<<(ostream& os, const String& s){
        os << "s.size = " << s.size() << endl;
        os << "s.ca = " << s.capacity() << endl;
        os << "s.str = " << s.c_str() << endl;
        return os;
    }
    friend istream& operator>>(istream& is, String& s){
        s.clear();
        char c;
        while (is.get(c)) {
            if (isspace(c)) break;
            s += c;
        }
        return is;
    }
private:
    int n;
    int ca; 
    char* str;
};
class StringJoiner {
public:
    StringJoiner(char c = ' ') : c(c) {}
    String operator()(const String& a, const String& b) const;
private:
    char c;
};
String StringJoiner::operator()(const String& a, const String& b) const {
    const char* x = a.c_str();
    const char* y = b.c_str();
    int n1 = strlen(x);
    int n2 = strlen(y);
    char* temp = new char[n1 + n2 + 2];
    strcpy(temp, x);
    temp[n1] = c;
    strcpy(temp + n1 + 1, y);
    String res(temp);
    delete[] temp;
    return res;
}
int main(){
    String s1, s2;
    cin >> s1;
    cin >> s2;
    cout << s1;
    cout << s2;
    StringJoiner join(',');
    cout << "join: \n" << join(s1, s2);
    cin >> s1;
    int size = s1.size();
    for (int i = 0; i < size; i++) cout << s1[i];
    return 0;
}
