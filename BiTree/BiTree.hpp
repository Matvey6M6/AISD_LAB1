#pragma once
#include <iostream>
#include <vector>

struct Node
{
    int data;
    Node* left;
    Node* right;
    //Node* m_shot_through;

    Node* parrent;

    int depth;

    //Node* Next;

    Node(int data,int depth, Node* parrent , Node* left = nullptr, Node* right = nullptr, Node* Next = nullptr): data(data), depth(depth),parrent(parrent) {}
};

static std::string ch_hor = "-", ch_ver = "|", ch_ddia = "/", ch_rddia = "\\", ch_udia = "\\", ch_ver_hor = "|-", ch_udia_hor = "\\-", ch_ddia_hor = "/-", ch_ver_spa = "| ";


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
        while(tree)
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
            return nullptr; // no right tree
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

    Node* search(int data) //returns pointer at exact node
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

    void print_Tree(Node * p,int level)
    {
        if(p)
        {
            print_Tree(p->left,level + 1);
            for(int i = 0;i< level;i++) std::cout<<"   ";
            std::cout << p->data << std::endl;
            print_Tree(p->right,level + 1);
        }
    }

    BiTree() { root=nullptr; }

    BiTree(const BiTree& other) { copy_nodes(other.root); }

    ~BiTree() { clear_tree(); }

    bool contains(int value)    {   return find(root, value);   }

    bool erase(int value)
    {
        if(root->data == value) 
        {
            std::cout<<"You can't erase root!!!\n"<<std::endl;
            throw std::exception();
        }

        //if(!contains(value)) return false;

        Node* victim = search(value); // elem to change value

        Node* src = nullptr;

        if(victim == nullptr) return false;

        src = find_min(victim->right);  // elem to get value from

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

        if(!root) {root = new Node(data, depth, nullptr, nullptr); return true;}
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
        this->clear_tree();
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
