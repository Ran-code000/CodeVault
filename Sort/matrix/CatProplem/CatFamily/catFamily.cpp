#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class Cat{
	string name;
	Cat ** family;
	int size = 0;
public:
	Cat(string name = "") : name(name) {
		family = new Cat*[0];
		size = 0;
	}
	~Cat() { delete [] family; }
	// 添加一个家庭成员
	void add_family_member(Cat * cat){
        Cat** new_family = new Cat*[size + 1];
        //for(int i = 0; i < size; i++) new_family[i] = family[i];
		memcpy(new_family, family, sizeof(Cat*) * size);
        new_family[size] = cat;
        size++;
        delete[] family;
        family = new_family;
	}
	void print_family(){ for (int i = 0; i < size; i++) cout << family[i]->name << endl;}
    //To implement;
    void _copy(const Cat & cat);
    Cat(const Cat & cat);
    Cat& operator=(const Cat & cat);
};
void Cat::_copy(const Cat & cat){
    size = cat.size;
    name = cat.name;
    family = new Cat*[size];
    //for(int i = 0; i < size; i++) family[i] = cat.family[i];
	memcpy(family, cat.family, sizeof(Cat*) * size);
}
Cat::Cat(const Cat & cat){
	_copy(cat);
}
Cat& Cat::operator=(const Cat & cat) {
    if(this == &cat) return *this;
	delete[] family;
	_copy(cat);
	return *this;
}
int main(){
	int num_of_cats;
    cout << "Input the number of Cats:";
	cin >> num_of_cats;
	Cat* cats = new Cat[num_of_cats];
	string name;
	for (int i = 0; i < num_of_cats; ++ i){
        cout << "Input the Cat's name :";
		cin >> name;
		cats[i] = Cat(name); // operator =
	}
	for (int i = 0; i < num_of_cats; i++) cats[0].add_family_member(&cats[i]);
	Cat cat = cats[0]; // copy constructor
	cat.print_family();
	delete [] cats;
}