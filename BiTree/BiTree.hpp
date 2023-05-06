#pragma once
#include <iostream>
#include <vector>
#include <set>

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node *parrent;

    Node(int data, Node *parrent, Node *left = nullptr, Node *right = nullptr) : data(data), parrent(parrent), left(left), right(right) {}
};
class BiTree
{
    Node *root;

    void copy_nodes(const Node *src_root) // перепривязывает к руту другие Node
    {
        if (!src_root)
            return;
        this->insert(src_root->data);
        if (src_root->left)
            copy_nodes(src_root->left);
        if (src_root->right)
            copy_nodes(src_root->right);
    }

    void clear_tree(Node *tree) // delete all nodes
    {
        if (!tree)
            return;
        if (tree->left)
            clear_tree(tree->left);
        // if(tree->parrent)tree->parrent->left = nullptr;
        tree->left = nullptr;
        if (tree->right)
            clear_tree(tree->right);
        // if(tree->parrent)tree->parrent->right = nullptr;
        tree->right = nullptr;
        delete tree;
    }

    bool find(Node *tree, int value)
    {
        while (tree != nullptr)
        {
            if (value > tree->data)
                tree = tree->right;
            else if (value < tree->data)
                tree = tree->left;
            else
            {
                return true;
            }
        }

        return false;
    }

    Node *find_min(Node *tree)
    {
        if (tree == nullptr)
        {
            return nullptr; // exit or no right tree
        }

        Node *pt = tree; // pointer at field with pointer

        while (pt->left != nullptr)
        {
            pt = pt->left;
        }
        return pt;
    }

    Node *find_node(int data) // returns pointer at exact node
    {
        Node *tmp = root;
        while (tmp)
        {
            if (tmp->data == data)
                return tmp;
            if (tmp->data > data)
                tmp = tmp->left;
            else
                tmp = tmp->right;
        }
        return nullptr;
    }

public:
    void walk_by(Node *tree, std::vector<int> *dest)
    {
        if (!tree)
            return;
        dest->push_back(tree->data);
        if (tree->right)
            walk_by(tree->right, dest);
        if (tree->left)
            walk_by(tree->left, dest);
    }

    void write_up(std::vector<int> *dest)
    {
        walk_by(root, dest);
    }

    void print_Tree(Node *p, int level)
    {
        if (p)
        {
            print_Tree(p->left, level + 1);
            for (int i = 0; i < level; i++)
                std::cout << "\t";
            std::cout << p->data << std::endl;
            print_Tree(p->right, level + 1);
        }
    }

    BiTree() { root = nullptr; }

    BiTree(const BiTree &other) { copy_nodes(other.root); }

    ~BiTree() { clear_tree(root); }

    bool contains(int value) { return find(root, value); }

    bool erase(int data)
    {
        if (!root)
            return false;
        Node *erase_root = find_node(data);
        if (erase_root == NULL)
            return false;
        if (erase_root == root)
        {
            if (root->left == NULL && root->right == NULL)
            {
                root = NULL;
                return true;
            }
            if (erase_root->left != NULL && erase_root->right == NULL) // åñëè åñòü ëåâîå ïîääåðåâî, íî íåò ïðàâîãî
            {
                root = root->left;
                delete erase_root;
                return true;
            }
            if (erase_root->left == NULL && erase_root->right != NULL) // åñëè åñòü ïðàâîå ïîääåðåâî, íî íåò ëåâîãî
            {
                root = root->right;
                delete erase_root;
                return true;
            }
        }

        Node *parent_erase = erase_root->parrent;

        if (erase_root->left == NULL && erase_root->right == NULL) // óäàëåíèå ëèñòà
        {
            Node *parent_erase = erase_root->parrent;
            if (parent_erase->left == erase_root)
                parent_erase->left = NULL;
            else
                parent_erase->right = NULL;
            delete erase_root;
            return true;
        }
        if (erase_root->left != NULL && erase_root->right == NULL) // åñëè åñòü ëåâîå ïîääåðåâî, íî íåò ïðàâîãî
        {
            // bin_tree *parent_erase = find_parent(data, root);
            if (parent_erase->left == erase_root)
                parent_erase->left = erase_root->left;
            else
                parent_erase->right = erase_root->left;
            delete erase_root;
            return true;
        }
        if (erase_root->left == NULL && erase_root->right != NULL) // åñëè åñòü ïðàâîå ïîääåðåâî, íî íåò ëåâîãî
        {
            // bin_tree *parent_erase = find_parent(data, root);
            if (parent_erase->left == erase_root)
                parent_erase->left = erase_root->right;
            else
                parent_erase->right = erase_root->right;
            delete erase_root;
            return true;
        }
        if (erase_root->left != NULL && erase_root->right != NULL) // åñòü îáà ïîääåðåâà
        {
            Node *min_node = find_min(erase_root->right);
            Node *parent_min_node = min_node->parrent;
            if (min_node->right == NULL) // ó ìèíèìàëüíîãî íåò ïîääåðåâüåâ
            {
                erase_root->data = min_node->data;
                if (parent_min_node->right == min_node)
                    parent_min_node->right = NULL;
                else
                    parent_min_node->left = NULL;
                delete min_node;
                return true;
            }
            else // ó ìèíèìàëüíîãî åñòü ïðàâîå ïîääåðåâî
            {
                erase_root->data = min_node->data;
                if (parent_min_node->right == min_node)
                    parent_min_node->right = min_node->right;
                else
                    parent_min_node->left = min_node->right;

                delete min_node;
                return true;
            }
        }
        return false;
    }

    bool insert(int data)
    {
        if (contains(data))
            return false;

        if (!root)
        {
            root = new Node(data, nullptr);
            return true;
        }
        if (data == root->data)
            return false;

        Node *tmp = root;

        while (tmp)
        {
            if (data < tmp->data)
            {
                if (tmp->left)
                    tmp = tmp->left;
                else
                {
                    tmp->left = new Node(data, tmp);
                    return true;
                }
            }
            else if (data > tmp->data)
            {
                if (tmp->right)
                    tmp = tmp->right;
                else
                {
                    tmp->right = new Node(data, tmp);
                    return true;
                }
            }
        }
        return false;
    }

    void print()
    {
        print_Tree(root, 0);
    }

    BiTree operator=(const BiTree *src)
    {
        this->clear_tree(root);
        copy_nodes(src->root);
        return (*this);
    }
};
