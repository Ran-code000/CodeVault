# include <iostream>
# include <string>

template <typename T>
class Stack
{
public:
    Stack(unsigned int size = 100);
    ~Stack();

    void push(T value);
    T pop();

private:
    unsigned int size;
    unsigned int sp;
    T* data;
};

template <typename T>
Stack<T>::Stack(unsigned int size)
{
    this->size = size;
    data = new T[size];
    sp = 0;
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] data;
}

template <typename T>
void Stack<T>::push(T value)
{
    data[sp++] = value;
}

template <typename T>
T Stack<T>::pop()
{
    return data[--sp];
}

int main()
{
    Stack<int> intstack(100);

    intstack.push(1);
    intstack.push(2);
    intstack.push(3);

    std::cout << intstack.pop() << "\n";
    std::cout << intstack.pop() << "\n";
    std::cout << intstack.pop() << "\n";

    return 0;
}