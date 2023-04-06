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

    Node* find_min(Node* tree)
    {
        if (tree->left != nullptr) {
            return find_min(tree->left);
        } 
        else {
            return tree;
        }
    }

    void insert_obj(Node* newbie)
    {
        Node* tmp = root;
        while(tmp)
        {
            if(newbie->data < tmp->data)
            {
                if(tmp->left) tmp = tmp->left;
                else
                {
                    tmp->left = newbie;
                }
            }
            else if(newbie->data > tmp->data)
            {
                if(tmp->right) tmp = tmp->right;
                else
                {
                    tmp->right = newbie;
                }
            }
        }
    }

    //find_sutable();
public:
    BiTree() { root=nullptr; }

    BiTree(const BiTree& other) { copy_nodes(other.root); }

    ~BiTree() { clear_tree(); }

    bool contains(int value)    {   return find(root, value);   }

    bool erase(int data)
    {
        Node* tmp = root;
        while (tmp)
        {
           if(data < tmp->data)
            {
                if(tmp->left) tmp = tmp->left;
                else
                {
                    Node buffer = *tmp;
                    delete tmp;
                    insert_obj(find_mid(tmp->right))

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

    void print(Node* tree, int level = 0)
    {
        if(!tree) tree = root;
        if(root->right) {
            print(root->right, level++);
            for(int i = 0; i < level; i++) std::cout<<" ";
            std::cout<<root->data<<std::endl;
        }
        if(root->left) {
            print(root->left, level++);
            for(int i = 0; i < level; i++) std::cout<<" ";
            std::cout<<root->data<<std::endl;
        }
    }

    BiTree operator=(const BiTree* src)
    {
        this->clear_tree();
        copy_nodes(src->root);
        return (*this);
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
