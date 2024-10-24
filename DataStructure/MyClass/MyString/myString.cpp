#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
class MyString{
public:
    MyString();
    MyString(const char* s);
    MyString(size_t len, char c);
    MyString(const char* s, size_t len);
    MyString(const MyString& a);
    MyString(const MyString& a, size_t pos, size_t len = npos);
    MyString(MyString&& str) noexcept;
    template<typename Iter>
    MyString(Iter begin, Iter end);
    MyString(initializer_list<char> il);
    ~MyString();
    const char* c_str() const;
    void clear();
    MyString& operator= (const char c);
    MyString& operator= (const MyString& a);
    Mystring& operator= (const char* a);
    MyString& operator+ (const char c);
    MyString& operator+ (const MyString& a);
    MyString& operator+ (const char* s);
    MyString& operator+= (const char c);
    MyString& operator+= (const MyString& a);
    MyString& operator+= (const char* s);
    MyString& append(const char c);
    MyString& append(const MyString& a);
    bool operator== (const MyString& a);
    bool operator!= (const MyString& a);
    bool operator< (const MyString& a);
    bool operator<= (const MyString& a);
    bool operator> (const MyString& a);
    bool operator>= (const MyString& a);
    bool isempty() const;
    int compare(const string &a) const;
    int compare(const char *s) const;
    int compare (size_t pos1, size_t len1, const MyString& a) const;
    int compare (size_t pos1, size_t len1, const MyString& a, size_t pos2, size_t len2) const;
    int compare (size_t pos1, size_t len1, const char* p, size_t = npos) const;
    size_t length() const;
    size_t capacity() const;
    MyString& resize(size_t len);
    char& at(size_t index);
    const char& at(size_t index) const;
    char& operator[](size_t index);
    const char& operator[](size_t index) const;
    size_t find(const MyString& a, size_t pos = 0) const;
    size_t find(const char* s, size_t pos = 0) const;
    size_t find(const char c, size_t pos = 0) const; 
    size_t find(const char* s, size_t pos, size_t len) const; 
    size_t rfind(const MyString& a, size_t pos = npos) const;
    size_t rfind(const char* s, size_t pos = npos) const; 
    size_t rfind(const char* s, size_t pos, size_t len) const;
    size_t rfind(const char c, size_t pos = 0) const;
    size_t find_first_of(char c);
    size_t find_last_of(char c);
    size_t find_first_not_of(char c);
    size_t find_last_not_of(char c);
    size_t find_s_first_of(const char *s);
    size_t find_s_last_of(const char *s);
    MyString& replace(size_t pos, size_t len, const string& a); 
    MyString& replace(size_t pos, size_t len, const char* s);
    MyString& insert(size_t pos, const char* s);
    MyString& insert(size_t pos, const MyString& a);
    MyString& insert(size_t pos, size_t len, char c);
    MyString& erase(size_t pos, size_t len = npos);
    MyString substr(size_t pos = 0, size_t len = npos) const; 
    friend ostream& operator<< (ostream& os, const MyString& s);
    friend istream& operator>> (istream& is, const MyString& s);
    static unsigned int npos;
private:
    size_t length;
    size_t capacity;
    char* str;
};
unsigned int MyString::npos = UINT_MAX;
template<typename T>
MyString to_string(T item);
// class StringJoiner{
// public:
//     StringJoiner(char c = ' ') : c(c){}
//     MyString operator() (const MyString& a, const MyString& b) const;
// private:
//     char c;
// };
MyString::MyString() : size(0), capacity(16), str(new char[capacity]){
    str[0] = '\0';
}
MyString::MyString(const char* s) : size(strlen(s)), capacity(size * 2), str(new char[capacity]){
    strcpy(str, s);
}
MyString::MyString(const MyString& a) : size(a.size), capacity(a.capacity), str(new char[capacity]){
    strcpy(str, a.c_str());
}
MyString::~MyString(){ delete[] str;}
const char* MyString::c_str() const{ return str;}
void MyString::clear(){ 
    if(str) delete[] str;
    size = 0;
    capacity = 16;
    str = new char[capacity];
    str[0] = '\0';
}
MyString& MyString::operator= (const MyString& a){
    if(this == &a) return *this;
    if(str) delete[] str;
    str = nullptr;
    size = a.getSize();
    capacity = a.getCapacity();
    str = new char[capacity];
    strcpy(str, a.c_str());
    str[size] = '\0';
    return *this;
}
MyString& MyString::operator+= (const char c){
    if(size + 1 >= capacity){
        capacity *= 2;
        char* newstr = new char[capacity];
        strcpy(newstr, str);
        if(str) delete str;
        str = newstr;
    }
    str[size++] = c;
    str[size] = '\0';
    return *this;
}
MyString& MyString::operator+ (const MyString& a){
    size += a.size;
    while(size >= capacity) capacity *= 2;
    char* newstr = new char[capacity];
    strcpy(newstr, str);
    strcat(newstr, a.c_str());
    if(str) delete[] str;
    str = newstr;
    str[size] = '\0';
    return *this;
}
MyString& MyString::operator+= (const MyString& a){
    return *this + a;
}
bool MyString::operator== (const MyString& a){
    return strcmp(str, a.c_str()) == 0;
}
bool MyString::operator!= (const MyString& a){
    return !(*this == a);
}
bool MyString::operator> (const MyString& a){
    return strcmp(str, a.c_str()) > 0;
}
bool MyString::operator< (const MyString& a){
    return strcmp(str, a.c_str()) < 0;
}
bool MyString::operator>= (const MyString& a){
    return !(*this < a);
}
bool MyString::operator<= (const MyString& a){
    return !(*this > a);
}
size_t MyString::getSize() const{ return size;}
size_t MyString::getCapacity() const{ return capacity;}
char& MyString::operator[] (size_t index){
    if(index >= 0 && index < size) return str[index];
    throw out_of_range("out of range!");
}
const char& MyString::operator[](size_t index) const{
    if(index >= 0 && index < size) return str[index];
    throw out_of_range("out of range!");
}
ostream& operator<< (ostream& os, const MyString& s){ 
    cout << s.c_str() << endl;
    return os;
}
istream& operator>> (istream& is, const MyString& s){
    char c;
    while(is.get(c)) if(isspace(c)) break;
    return is;
}
MyString StringJoiner::operator() (const MyString& a, const MyString& b) const{
    size_t newsize = a.getSize() + b.getSize();
    char* newstr = new char[newsize + 1];
    strcpy(newstr, a.c_str());
    strcat(newstr, b.c_str());
    newstr[newsize] = '\0';
    return newstr;
}
size_t main(){
    cout << "------------------------------------------------------------------------------------\n";
    cout << "Text << \n";
    MyString s1("Sandy");
    MyString s2("Good");
    MyString s3("HelloHello");
    MyString s4("aaaaaaaaaa");
    MyString s5("aaaaabbbbb");
    cout << "s1 :" << s1 << "\n" << "s2 :" << s2 << "\n" << "s3 :" << s3 << "\n" <<  "s4 :" << s4 << "\n" <<  "s5 :" << s5 << "\n";
    cout << "------------------------------------------------------------------------------------\n";
    cout << "Text >> \n";    
    MyString ss;
    cin >> ss;
    cout << "You just input: " << ss << endl;
    cout << "------------------------------------------------------------------------------------\n";
    cout << "Text + and =\n";
    cout << "+:\n";
    cout << "s1 + s2 = " << s1 + s2 << endl;
    MyString s6;
    s6 =  s1 + s2;
    cout <<  "s6 = s1 + s2\n";
    cout << "s6:" << s6;
    cout << "------------------------------------------------------------------------------------\n";
    cout << "Text += \n";
    cout << "s1:" << s1 << "\ns2:" << s2 << "\n";
    cout << "s1 += p\n " << (s1 += 'p') << endl;
    cout << "s1 += s2\n" << (s1 += s2) << endl;
    cout << "------------------------------------------------------------------------------------\n";
    cout << "Text () \n";
    //cout << "StringJoiner(s1, s2) " << StringJoiner(s1, s2) << endl;
    cout << "------------------------------------------------------------------------------------\n";
    cout << "Text == \n";
    s1 = "SandyGood";
    cout << "s6 == s1 + s2 : " << (s6 == s1 + s2) << endl;
    cout << "------------------------------------------------------------------------------------\n";
    cout << "Text != \n";
    cout << "s1 != s2 : " << (s1 != s2) << endl;
    cout << "------------------------------------------------------------------------------------\n";
    cout << "Text > \n";
    cout << "s4 > s5 : " << (s4 > s5) << endl;
    cout << "------------------------------------------------------------------------------------\n";
    cout << "Text <= \n";
    cout << "s4 <= s5 : " << (s4 <= s5) << endl;
    cout << "------------------------------------------------------------------------------------\n";
    cout << "Text < \n";
    cout << "s4 < s5 : " << (s4 < s5) << endl;
    cout << "------------------------------------------------------------------------------------\n";
    cout << "Text >= \n";
    cout << "s4 >= s5 : " << (s4 >= s5) << endl;
    cout << "------------------------------------------------------------------------------------\n";
    cout << "Text [] \n";
    cout << "s3:" << s3 << endl;
    cout << "s3[4]: " <<  s3[4] << endl;
    cout << "s3[10]: " << s3[10] << endl;
    return 0;
}