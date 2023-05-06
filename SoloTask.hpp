#pragma once
#include "./BiTree/BiTree.hpp"
#include <vector>
#include <algorithm>

using namespace std;

std::vector<int> no_repeatings(std::vector<int> src)
{
    BiTree BufferTree;

    vector<int> Used;

    for (auto cur = src.begin(); cur != src.end(); cur++)
    {
        BufferTree.insert((*cur));
        if (find(Used.begin(), Used.end(), *cur) != Used.end())
        {
            BufferTree.erase(*cur);
        }
        Used.push_back(*cur);
    }

    std::vector<int> ans;

    BufferTree.write_up(&ans);

    return ans;
}
