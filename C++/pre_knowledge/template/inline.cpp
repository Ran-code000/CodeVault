# include <iostream>
# include <string>

template <typename T>
class Stack
{
public:
    Stack(unsigned int size = 100)
    {
        this->size = size;
        data = new T[size];
        sp = 0;
    }
    ~Stack()
    {
        delete[] data;;
    }

    void push(T value)
    {
        data[sp++] = value;
    }
    T pop()
    {
        return data[--sp];
    }

private:
    unsigned int size;
    unsigned int sp;
    T* data;
};

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