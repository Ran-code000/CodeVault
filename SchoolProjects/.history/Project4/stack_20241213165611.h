#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class Stack
{
private:
    std::vector<T> container;

public:
    Stack() = default;
    bool empty() const { return container.empty(); }
    size_t size() const { return container.size(); }
    T &top()
    {
        if (empty())
            throw out_of_range("Stack is empty");
        return container.back();
    }
    const T &top() const
    {
        if (empty())
            throw out_of_range("Stack is empty");
        return container.back();
    }
    void push(const T &value) { container.push_back(value); }
    void pop()
    {
        if (empty())
            throw out_of_range("Stack is empty");
        container.pop_back();
    }
};

#endif
