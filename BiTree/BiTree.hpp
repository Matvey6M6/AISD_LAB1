#pragma once
#include <iostream>
#include <vector>
#include <set>

struct Node
{
    int data;
    Node* left;
    Node* right;
    //Node* m_shot_through;

    Node* parrent;

    int depth;

    //Node* Next;

    Node(int data,int depth, Node* parrent , Node* left = nullptr, Node* right = nullptr): data(data), depth(depth),parrent(parrent),left(left), right(right) {}
};

//static std::string ch_hor = "-", ch_ver = "|", ch_ddia = "/", ch_rddia = "\\", ch_udia = "\\", ch_ver_hor = "|-", ch_udia_hor = "\\-", ch_ddia_hor = "/-", ch_ver_spa = "| ";


class BiTree
{
    Node* root;

    /*Node* find_first_right(Node* src)
    {
        Node* pt = src;
        while(!pt->right) pt = pt->parrent;
        return pt->right;
    }*/

    /*Node* shot_through(Node* src) // прошиваемся, парни
    {
        return find_first_right(src);
    }*/

    void copy_nodes(const Node* src_root) //перепривязывает к руту другие Node
    {
        if(!src_root) return;
        this->insert(src_root->data);
        if(src_root->left) copy_nodes(src_root->left);
        if(src_root->right) copy_nodes(src_root->right);
    }

    void clear_tree(Node*tree) //delete all nodes
    {
        if(!tree) return;
        if(tree->left) clear_tree(tree->left);
        //if(tree->parrent)tree->parrent->left = nullptr;
        tree->left = nullptr;
        if(tree->right) clear_tree(tree->right);
        //if(tree->parrent)tree->parrent->right = nullptr;
        tree->right = nullptr;
        delete tree; 
    }

    bool find(Node* tree, int value) 
    {
        while(tree!=nullptr)
        {
            if(value > tree->data) tree = tree->right;
            else if (value < tree-> data) tree = tree->left;
            else {return true;}
        }

        return false;
    }

    Node* find_min(Node* tree)
    {
        if (tree == nullptr) {
            return nullptr; // exit or no right tree
        } 
        
        Node* pt = tree; // pointer at field with pointer

        while(pt->left!= nullptr)
        {
            pt = pt->left;
        }
        if(pt->right) return pt->right;
        else return pt;
    }

    

    /*void dump0(Node const * node, std::string const & prefix = "", bool root = true, bool last = true) {
    std::cout << prefix << (root ? "" : (last ? ch_udia_hor : ch_ver_hor)) << (node ? std::to_string(node->data) : "") << std::endl;
    if (!node || (!node->left && !node->right))
        return;
    std::vector<Node*> v{node->left, node->right};
    for (size_t i = 0; i < v.size(); ++i)
        dump0(v[i], prefix + (root ? "" : (last ? "  " : ch_ver_spa)), false, i + 1 >= v.size());
    }*/


  /*Node* findMin(Node* start, Node*&parent)
    {
        while (start->left!=NULL)
        {
            parent = start;
            start = start->left;
        }
        return start;
    }*/

    Node* find_node(int data) //returns pointer at exact node
    {
        Node* tmp = root;
        while(tmp)
        {
            if(tmp->data == data) return tmp;
            if(tmp->data > data) tmp = tmp->left;
            else tmp = tmp->right;
        }
        return nullptr;
    }
public:

    void walk_by(Node*tree, std::vector<int>* dest)
    {
        if(!tree) return;
        dest->push_back(tree->data);
        if(tree->right)walk_by(tree->right, dest);
        if(tree->left)walk_by(tree->left, dest);
    }

    void write_up(std::vector<int>* dest)
    {
        walk_by(root, dest);
    }

    //friend std::vector<int> no_repeatings(std::vector<int> src);

    void print_Tree(Node * p,int level)
    {
        if(p)
        {
            print_Tree(p->left,level + 1);
            for(int i = 0;i< level;i++) std::cout<<"\t";
            std::cout << p->data << std::endl;
            print_Tree(p->right,level + 1);
        }
    }

    BiTree() { root=nullptr; }

    BiTree(const BiTree& other) { copy_nodes(other.root); }

    ~BiTree() { clear_tree(root); }

    bool contains(int value)    {   return find(root, value);   }

    bool erase(int value)
    {
        if(root->data == value) 
        {
            std::cout<<"You can't erase root!!!\n"<<std::endl;
            throw std::exception();
        }

        Node* victim = find_node(value); // elem to change value

        if(victim == nullptr) return false;

        Node* src = find_min(victim->right);; // elem to take value from (if exists) (will be deleted)

        if(src == nullptr) //no right root
        {
            Node* victim_parrent = victim->parrent;
            if(victim == victim_parrent->right)
            {
                delete victim;
                victim_parrent->right = nullptr;
            }
            else
            {
                delete victim;
                victim_parrent->left = nullptr;
            }
        }
        else
        {       
            victim->data = src->data;

            Node* tmp = src->parrent;

            if(tmp->right == src)
            {
                delete src;
                tmp->right = nullptr;
            }
            else
            {
                delete src;
                tmp->left = nullptr;
            }
        }

        return true;
    }   

    bool insert(int data, int depth = 0)
    {
        if(contains(data))return false;

        if(!root) {root = new Node(data, depth, nullptr); return true;}
        if(data == root->data) return false;

        Node* tmp = root;

        while(tmp)
        {
            depth ++;
            if(data < tmp->data)
            {
                if(tmp->left) tmp = tmp->left;
                else
                {
                    tmp->left = new Node(data,depth, tmp);
                    return true;
                }
            }
            else if(data > tmp->data)
            {
                if(tmp->right) tmp = tmp->right;
                else
                {
                    tmp->right = new Node(data, depth, tmp);
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

    BiTree operator=(const BiTree* src)
    {
        this->clear_tree(root);
        copy_nodes(src->root);
        return (*this);
    }
};

/*class MyIterator
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
};*/
