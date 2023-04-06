#pragma once
#include "./BiTree/BiTree.hpp"
#include <vector>

std::vector<int> no_repeatings(std::vector<int> src)
{
    BiTree BufferTree;
    for(auto i : src)
    {
        BufferTree.insert(i);
    }
}
