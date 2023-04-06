#include "./BiTree/BiTree.hpp"
#include "./Test/test.hpp"
#include<string>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "SoloTask.hpp"
//#include <set>
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
    bool res = MyTreePt->insert(value);
   if(!res)
   {
        cout<<"Elem is already in the tree!!!\\Press any key"<<endl;
        getch();
   }
    else
    {
        cout<<"Success! Elem "<<value<<" is inserted!"<<endl;
    }
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
        MyTreePt->print();
        cout<<"Choose an option:"<<endl;
        cout<<"[1] - add new elem\n[2] - check if elem in the tree\n[3] - erase an elem\n[0] - Exit"<<endl;

        int opt = getch();

        cout<<opt<<endl;

        switch (opt)
        {
            case 48:
            return;
            break;
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
        cout<<"[1] - Create a binary tree\n[2] - Start tests\n[3] - Exit"<<endl;

        int opt = getch();

        //cout<<opt<<endl;

        if(opt == 51) return;
        if(opt == 50)
        {
            tests();
        }
        
        BiTree Tree;
        BiTree* pt = &Tree;

        while (true)
        {
            int exit_f = 0;

            while (exit_f != 27)
            {
                system("clear");
                cout<<"Input value to be written: ";

                int value;
                cout<<"Value = ";
                value = read_value();

                bool res = Tree.insert(value);
                if(!res)
                {
                    cout<<"Elem is already in the tree!!!\nPress any key"<<endl;
                }
                else
                {
                    cout<<"New elem is added!"<<endl<<"Press ESC to stop"<<endl<<"Press ENTER to input more"<<endl;
                    exit_f = getch();
                }
            }

            menu_2(pt);
            return;
        }
    }
}

int main()
{
    menu();
    return 0;
}