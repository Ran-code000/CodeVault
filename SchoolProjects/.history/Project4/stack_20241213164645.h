#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class Stack
{
private:
    std::vector<T> container; // 使用 std::vector

public:
    Stack() = default;
    bool empty() const { return container.empty(); }
    size_t size() const { return container.size(); }
    T &top()
    {
        if (empty())
            throw std::out_of_range("Stack is empty"); // 使用 std::out_of_range
        return container.back();
    }
    const T &top() const
    {
        if (empty())
            throw std::out_of_range("Stack is empty");
        return container.back();
    }
    void push(const T &value) { container.push_back(value); }
    void pop()
    {
        if (empty())
            throw std::out_of_range("Stack is empty");
        container.pop_back();
    }
};

#endif
