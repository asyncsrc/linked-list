#include <iostream>
#include "linkedlist.h"

using std::cout;
using std::endl;

int main() {
	
	LinkedList<int> myList;
	
	cout << "Adding nodes to list..." << endl;
	myList.addNode(50);
	myList.addNode(30);
	myList.addNode(10);
	myList.addNode(80);	
	myList.addNode(5);
	myList.addNode(23);
	
	cout << "Iterating list..." << endl;
	myList.iterateList();
	
	cout << "Sorting list..." << endl;
	myList.sortNodes();
	
	cout << "Iterating list..." << endl;
	myList.iterateList();
	
	cout << "Inserting new node in list with value 325" << endl;
	myList.insertNode(325, myList[2]);
	
	cout << "Iterating list..." << endl;
	myList.iterateList();
	
	cout << "Sorting list..." << endl;
	myList.sortNodes();
	
	cout << "Iterating list..." << endl;
	myList.iterateList();
	
	cout << "Sorting list descending..." << endl;
	myList.sortAscending = false;
	myList.sortNodes();
	
	cout << "Iterating list..." << endl;
	myList.iterateList();
	
	return 0;
}