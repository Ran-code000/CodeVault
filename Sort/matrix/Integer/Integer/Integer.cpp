#include <iostream>
using namespace std;
class Integer{
private:
	int x;
public:
	Integer(int x = 0): x(x) {};
	void print(){ std::cout << x;}
	const void print() const {std::cout << x;}
};
class IntArray {
	private:
		Integer *data;
		int n;
	public:
		IntArray(int n = 1);
		~IntArray();
		void print();
		void print() const;
		Integer &operator[](int i);
		const Integer &operator[](int i) const;

};
IntArray::IntArray(int n): n(n) {
	cout << "constructor is executed" << endl;
	data = new Integer[n];
	for (int i = 0; i < n; i++) data[i] = i;
}
IntArray::~IntArray() {
	cout << "destructor is executed" << endl;
	delete[] data;
}
void IntArray::print() {
	cout << "print:";
	for (int i = 0; i < n; i++){ data[i].print(); cout << " ";}
	cout << endl;
}

void IntArray::print() const {
	cout << "const print:";
	for (int i = 0; i < n; i++){ data[i].print(); cout << " ";}
	cout << endl;
}
Integer &IntArray::operator[](int i) {
	cout << "operator[] is executed" << endl;
	if (i >= 0 && i < n){ return data[i];}
	throw out_of_range("out of range");
}

const Integer &IntArray::operator[](int i) const {
	cout << "const operator[] is executed" << endl;
	if (i >= 0 && i < n){ return data[i];}
	throw out_of_range("out of range");
}
int main() {
	IntArray a(5);
	a.print();
	a[4].print();
	cout << endl;
	cout << "--------------------" << endl;

	const IntArray b(5);
	b.print();
	b[4].print();
	cout << endl;
	cout << "--------------------" << endl;

	return 0;
}