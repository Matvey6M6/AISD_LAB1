#pragma once
#include <iostream>

struct Node
{
    int data;
    Node* left;
    Node* right;

    //Node* Next;

    Node(int data, Node* left = nullptr, Node* right = nullptr, Node* Next = nullptr): data(data) {}
};

class BiTree
{
    Node* root;

    void copy_nodes(const Node* src_root) 
    {
        if(!src_root) return;
        if(src_root->left) copy_nodes(src_root->left);
        if(src_root->right) copy_nodes(src_root->right);
        this->insert(root->data);
    }

    void clear_tree()
    {
        if(!root) return;
        if(root->left) copy_nodes(root->left);
        if(root->right) copy_nodes(root->right);
        delete root; 
    }

    bool find(Node* tree, int value)
    {
        if(!tree) return false;
        if(tree->data == value) return true;
        if(tree->left) find(tree->left, value);
        if(tree->right) find(tree->right, value);
    }

    //find_sutable();
public:
    BiTree() { root=nullptr; }

    BiTree(const BiTree& other) { copy_nodes(other.root); }

    ~BiTree() { clear_tree(); }

    bool contains(int value)    {   return find(root, value);   }

    bool insert(int data)
    {
        Node* tmp = root;
        while(tmp)
        {
            if(data < tmp->data)
            {
                if(tmp->left) tmp = tmp->left;
                else
                {
                    tmp->left = new Node(data);
                    return true;
                }
            }
            else if(data > tmp->data)
            {
                if(tmp->right) tmp = tmp->right;
                else
                {
                    tmp->right = new Node(data);
                    return true;
                }
            }
        }
        return false;
    }
};

class MyIterator
{
    Node *Current;
public:

    MyIterator(Node *obj) : Current(obj)
    {}

    int operator*()
    {
        return Current->data;
    }

    bool operator!=(const MyIterator& obj)
    {
        if(this->Current != obj.Current) return true;
        return false;
    }

    void go_left() 
    { 
        if(Current!=nullptr) Current = Current->left;
        else { std::cout<<"Iterator has reached last value";}
    }
    
    void go_rigth()
    {
        if(Current!=nullptr) Current = Current->right;
        else { std::cout<<"Iterator has reached last value";}
    }
};
