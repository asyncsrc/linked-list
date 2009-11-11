#include <iostream>
#include "linkedlist.h"

using std::cout;
using std::endl;

int main() {

	LinkedList<int> myList;
	
	myList.addNode(50);
	myList.addNode(30);
	myList.addNode(10);
	myList.addNode(80);
	
	myList.sortNodes();
	
	myList.iterateList();
	
	myList.deleteNode(myList[2]);
	myList.addNode(5);
	myList.addNode(23);
	
	myList.sortNodes();
	
	myList.iterateList();
		
	return 0;
}