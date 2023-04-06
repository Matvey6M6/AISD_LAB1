#pragma once
#include "./BiTree/BiTree.hpp"
#include <vector>

std::vector<int> no_repeatings(std::vector<int> src)
{
    BiTree BufferTree;
    for(auto cur = src.begin(); cur!=src.end(); cur++)  {   BufferTree.insert((*cur));  }

    std::vector<int> ans;

    BufferTree.write_up(&ans);

    return ans;
}
