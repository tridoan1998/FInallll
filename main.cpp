#include <iostream>
#include <string>
#include <fstream>

#include "BST.h"

using namespace std;


int main()
{

    BST<book> bst;

    string name, space;
    int age;
    ifstream fin;
    fin.open("data.txt");
        if(fin.fail())
        {
            cout << "Fail to open!";
        }
        else
        {
            while(!fin.eof())
            {
                getline(fin, name);
                fin >> age;
                fin.ignore();
                fin.ignore();
                cout << name << endl<< age << endl;
            }
        }


    return 0;
}

class Book
{



};
