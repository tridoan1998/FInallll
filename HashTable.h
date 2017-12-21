
#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>
#include "List.h"
#include <iostream>
#include <cstddef> //for NULL
#include <assert.h>
#include "Book.h"
using namespace std;

class HashTable {
public:
    /**Constructors*/

    HashTable(){}
    //constructor

    ~HashTable(){}
    //destructor


    /**Access Functions*/

    int hash(string key) const;
    //returns the hash value for the given key
    //the hash value is the sum of
    //of the ASCII values of each char in the key
    //% the size the of the table
    //Key for this table: title + author

    int countBucket(int index) const;
    //counts the number of Books at this index
    //returns the count
    //pre: 0<= index < SIZE

    int search(Book b) const;
    //Searches for b in the table
    //returns the index at which b is located
    //returns -1 if b is not in the table

    /**Manipulation Procedures*/

    void insert(Book b);
    //inserts a new book into the table
    //calls the hash function on the key to determine
    //the correct bucket

    void remove(Book b);
    //removes b from the table
    //calls the hash function on the key to determine
    //the correct bucket
    //pre: b is in the table

    /**Additional Functions*/

    void printBucket(ostream& out, int index) const;
    //Prints all the books at index
    //pre: 0<= index < SIZE
    //Should print according to the following formula:
    //Prints each book at that index in the format:
    //<title> by <author>
    //$<X.XX>
    //ISBN#: <isbn>
    //followed by a blank line

    void printTable(ostream& out) const;
    //Prints the first book at each index
    //along with a count of the total books
    //at each index by calling count_bucket
    //as a helper function
    //Prints in the format:
    //Books in the Catalogue:
    //<new line>
    //Group <bucket>
    //<title> by <author>
    //$<X.XX>
    //ISBN: <isbn>
    //+<number of elements at this index> -1 more similar book(s)
    //<new line><new line><new line>

private:
    static const int SIZE = 10;
    List<Book> Table[SIZE];
};


int HashTable::hash(string key) const
{
	int index, sum = 0;
	for (unsigned int i = 0; i < key.length(); i++)
	{
		sum += (int)key[i];
	}
	index = sum % 10;
	return index;
}

int HashTable::countBucket(int index) const
{
	assert(0 <= index && index < SIZE);
	return Table[index].getSize();
}

int HashTable::search(Book b) const
{
	string key = b.get_title() + b.get_author();
	int index = hash(key);
	if(Table[index].isEmpty())
		return -1;
	else if (Table[index].linearSearch(b) == -1)
	{
		return -1;
	}
	else
	{
		return index;
	}
}

void HashTable::insert(Book b)
{
	string key = b.get_title() + b.get_author();
	int index = hash(key);
	Table[index].insertStop(b);
}

void HashTable::remove(Book b)
{

	string key = b.get_title() + b.get_author();
	int index = hash(key);
	if(!Table[index].isEmpty())
	{
		Table[index].pointIterator();
		int position = Table[index].linearSearch(b);
		Table[index].advanceToIndex(position);
		Table[index].removeIterator();
	}
	else
	{
		cout << "The book is not on the list."<< endl;
	}
	/*assert(search(b) != -1);
		int index = search(b);
		int Index_In_Bucket = Table[index].linearSearch(b);
		Table[index].pointIterator();
		for (int i = 1; i < Index_In_Bucket; i++)
		{
			Table[index].advanceIterator();
		}
		Table[index].removeIterator();
		*/
}

void HashTable::printBucket(ostream& out, int index) const
{
	assert(0 <= index && index < SIZE);
	Table[index].print();
}

void HashTable::printTable(ostream& out) const
{
	cout << "Books in the Catalogue:" << endl;
	for(int index = 0; index < SIZE; index++)
	{
		if(Table[index].isEmpty())
		{
			continue;
		}
		else
		{
			cout << "Group " << index+1 << endl;
			cout << Table[index].getStart() << endl;
			cout << "+" << countBucket(index) -1 << " more similar book(s)" << endl << endl << endl;
		}
	}
}

#endif /* HASHTABLE_H_ */
