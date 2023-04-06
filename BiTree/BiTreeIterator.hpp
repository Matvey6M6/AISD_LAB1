#pragma once
#include "BiTree.hpp"

class BiTreeItreator
{
    Node* current;
    Node* root;
    Node* last;

public:
    BiTreeItreator(Node* root, Node* pt, Node* last): root(root), current(pt), last(last) {}

    Node* next()
    {
        if(!current)
        {
            throw std::exception();
            std::cout<< "Iterator error\n";
        } 
        if(current->left) return current->left;
        else return current->right;
    }
    Node* begin()
    {
        return root;
    }
    Node* end()
    {
        return last;
    }

    Node* operator++(int empty)
    {
        return next();
    }
};