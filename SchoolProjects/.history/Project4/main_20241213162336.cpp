#include <iostream>
#include <unordered_map>
#include <string>
#include "graph.h"
#include "test.h"

std::unordered_map<int, std::string> provinces;
Graph graph(33);

int main()
{
    init();
    test();
    return 0;
}