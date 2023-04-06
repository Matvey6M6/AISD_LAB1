#include "BiTree.hpp"

#include<string>
#include <iostream>
#include <termios.h>
#include <unistd.h>
using namespace std;

char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

int read_value()
{
    while(true)
    {   
        string value;
        try
        {
            cin>>value;
            return stoi(value);
        }
        catch(exception e)
        {
            cout<<"Input an intenger!!!!!!!!!"<<endl;
        }
    }
}

void add_new_elem(BiTree* MyTreePt)
{
    system("clear");
        
    cout<<"MyTree add an elem menu"<<endl;

    cout<<"Value = ";
    int value = 0;
    value = read_value();
    MyTreePt->insert(value);
    cout<<"Success! Elem "<<value<<" is inserted!"<<endl;
}

void check_if_elem_in_tree(BiTree* MyTreePt)
{
    system("clear");
        
    cout<<"MyTree check if elem in tree menu"<<endl;

    cout<<"Value = ";
    int value = 0;
    value = read_value();
    if(MyTreePt->contains(value)) cout<<value<<" WAS found the tree."<<endl;
    else {cout<<value<<" WAS NOT found in the tree."<<endl;}
}

void erase_an_elem(BiTree* MyTreePt)
{
    system("clear");
        
    cout<<"MyTree erase an elem menu"<<endl;

    cout<<"Value = ";
    int value = 0;
    value = read_value();

    if(MyTreePt->erase(value)) cout<<value<<" has been erased."<<endl;
    else {cout<<value<<" WAS NOT found in the tree => not deleted";}
}

void menu_2(BiTree* MyTreePt)
{
    while(true){
        system("clear");
            
        cout<<"MyTree menu"<<endl;
        cout<<"Choose an option:"<<endl;
        cout<<"[1] - add new elem\n[2] - check if elem in the tree\n[3] - erase an elem\n[0] - Exit"<<endl;

        int opt = getch();

        cout<<opt<<endl;

        switch (opt)
        {
        case 49:
            add_new_elem(MyTreePt);
            break;
        case 50:
            check_if_elem_in_tree(MyTreePt);
            break;
        case 51:
            erase_an_elem(MyTreePt);
            break;
        default:
            break;
        }
        getch();
    }
}

void menu()
{
    while(true)
    {
        system("clear");

        cout<<"Welcome to BeTrii menu"<<endl;
        cout<<"Choose an option:"<<endl;
        cout<<"[1] - Create a binary tree\n[2] - Exit"<<endl;

        int opt = getch();

        //cout<<opt<<endl;

        if(opt == 50) return;
        
        BiTree Tree;
        BiTree* pt = &Tree;

        while (true)
        {
            system("clear");
            cout<<"Input values to be written (0 - stop):"<<endl;

            int value = 1; //value

            while (value != 0)
            {
                cout<<"Value = ";
                value = read_value();
                Tree.insert(value);
            }

            menu_2(pt);
        }
        
    }
}

int main()
{
    menu();
    return 0;
}