/* Ultra commented linked list I was working on for practice. */

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
//#include <vector>

using namespace std;

template <class N>
class LinkedList {
	
protected:
	struct Node {
		N *data;
		int nodeNum;
		Node* next;
		Node* prev;
	};
	
public:
	 Node** index;
	 Node* head;
	 Node* currentNode;
	int nodeCount;
	
	//vector< Node*>nodeVec;

public:
	LinkedList() : nodeCount(1) {
		index = ( Node**) malloc(sizeof( Node) * nodeCount);
		index[nodeCount-1] = ( Node*) malloc(sizeof( Node));
		index[nodeCount-1]->nodeNum = nodeCount;
		index[nodeCount-1]->data = (N*) malloc(sizeof(N));
		*index[nodeCount-1]->data = -1;
		head = index[nodeCount-1];
	};
	
	void addNode(N data);
	void deleteNode( Node* deleteNode);
	
	static bool compareNodes(const Node* left, const Node* right);
	void sortNodes();
	
	void iterateList();
	 Node* operator[](int nodeSub) {
		return index[nodeSub];
	}
	
};

void LinkedList::addNode(N data) {
	
	nodeNum++;
	
	// create the next node in our linked list in memory
	Node * newNode = NULL;
	newNode = (Node*) malloc(sizeof(Node));
	
	// assign the data variable value to be what the data variable value is that was passed in to this function
	// e.g. since we called addNode(5, current), 5 is passed in to the int data argument which is then passed into the data variable
	// of our new node
	newNode->data = data;
	
	// give an ID (node number) to each node
	newNode->nodeNum = nodeNum;
	
	std::cout << "- Creating node #[" << newNode->nodeNum << "] with value [" << newNode->data << "]" << std::endl;
	
	// we want a way to traverse backwards through our linked list, so we create a previous pointer
	// it will point to the node before it
	newNode->prev = currentNode;  // ability to traverse backward
	
	// we want a way to traverse forward through our linked list, so we create a next pointer
	// it will point to the node after it
	currentNode->next = newNode;  // ability to traverse forward
	
	// we set the next pointer of our new node to NULL because this is now the end of the linked list
	// i.e. there are no nodes after this newly created one because we've appended this to the end of the list, making it the last one
	newNode->next = NULL;
	
	// we move the currentNode pointer down to our newly created node
	// this allows us to further grow the linked list by allowing us to modify newNode's next and previous pointer...
	// when this function is called again
	currentNode = newNode;
	
	// increase node count by 1
	nodeNum++;
	
	// return currentNode which pointers to our newly created node
	return currentNode;
}

void deleteNode(struct node* currentNode) {
	// illustration:
	// let's say that currentNode is like the 5th node in the linked list.
	// currentNode->prev will be equal to node #4, currentNode->next will be equal to node #6 or null if this is the last node
	// so since we're deleting node #5, we point node#4's next pointer to the next pointer of node#5, essentially skipping right over node #5...
	// since node #5's next pointer points to node #6, node #4's next pointer will now point to node#6, which skipped node#5
	
	//node4->next = node6
	currentNode->prev->next = currentNode->next;
	
	// node6->prev = node4
	if (currentNode->next != NULL)
		currentNode->next->prev = currentNode->prev;
	
	// since there's no pointer currently pointing to node#5 (as per hypothetical illustration above) anymore, we delete it since it's just taking up space
	std::cout << "Freeing up node with data value: " << currentNode->data << std::endl;
	free(currentNode);  // prevent memory leaks i hope!
}

// delete first instance of node with argument value in data
bool deleteNodeWithValue(int data, struct node* headNode) {
	
	bool matchFound = false;
	std::string sInput = "";
	
	while (headNode != NULL)
	{
		if (headNode->data == data)
		{
			matchFound = true;
			
			std::cout << "MATCH :: Node #[" << headNode->nodeNum << "] has value [" << headNode->data << "]" << std::endl;
			std::cout << "Delete this one? (y/n)";
			std::getline(std::cin, sInput);
			
			if (tolower(sInput[0]) == 'y') {
				
				headNode->prev->next = headNode->next;
				
				if (headNode->next != NULL)
					headNode->next->prev = headNode->prev;
				
				std::cout << "Deleting Node #[" << headNode->nodeNum << "]" << std::endl;
				
				if (headNode != NULL) {
					free(headNode);
				}
			}
			else {
				std::cout << "Node #[" << headNode->nodeNum << "] will not be deleted." << std::endl;
			}
		}
		
		headNode = headNode->next;
	}
	
	return matchFound == false ? false : true;
}

void iterateNodes(struct node* headNode) {
	
	// our head node has no data value
	// our head node's purpose is simply to point to the head/top of the list
	// and since we're printing out data values, we skip to the next node which actually has a data value
	struct node* currentNode = headNode->next;
	
	
	//iterate forward
	
	std::cout << std::endl << "- Iterating through linked list from top to bottom..." << std::endl;
	std::cout << "|";
	std::cout.width(30);
	std::cout.fill('*');
	std::cout << "|" << std::endl;
	
	while (currentNode != NULL)
	{
		// print out the current data value of the current node
		std::cout << "\tNode #[" << currentNode->nodeNum << "] has value [" << currentNode->data << "]" << std::endl;
		
		// our we at the end of the list yet? if so, let's break out of this while loop
		if (currentNode->next == NULL)
			break;
		
		// apparently there are more nodes to go through, so let's point our current node to the next node
		currentNode = currentNode->next;
	}
	std::cout << "|";
	std::cout.width(30);
	std::cout.fill('*');
	std::cout << "|" << std::endl;
	
	
	//iterate backward
	// this code works fine; it just makes the output too verbose
	 /*
	 std::cout << "Iterating through linked list from bottom to top..." << std::endl;
	 while (currentNode->prev != NULL)
	 {
	 // print out the current node's data value
	 std::cout << "Node #[" << currentNode->nodeNum << "] has value [" << currentNode->data << "]" << std::endl;
	 
	 // move backwards by pointing to the previous node and keep going until we reach the head
	 currentNode = currentNode->prev;
	 }
	 
	 std::cout << "Exiting playNodes function." << std::endl;
	*/
	 
}

void cleanupList(struct node* headNode)
{
	
	// our head node has no data value
	// our head node's purpose is simply to point to the head/top of the list
	// and since we're printing out data values, we skip to the next node which actually has a data value
	struct node* currentNode = headNode->next;
	struct node* cleanupNode = currentNode;
	
	// clean up memory
	while (currentNode != NULL)
	{
		// store the next pointer in our cleanupNode because we need it after we delete this node, so we know where the next node is located
		// then we can do the same thing to the next node and so on...
		cleanupNode = currentNode->next;  
		
		// delete the current node
		free(currentNode);
		
		// point the current node back to our cleanupNode which points to the next node in the list
		currentNode  = cleanupNode;  
	}
}



int main() {
	struct node* head = NULL;
	struct node* currentNode = NULL;
	std::string sData = "";
	int data = 0;
	
	// allocate memory for our head node (the start of the linked list)
	head = (struct node*) malloc(sizeof(struct node));
	
	/* we want to keep "head" always pointing at the top of the linked list
	 * so we use current as a pointer to help build the list (with addNode())
	 * current will equal each new node so we can move further and further down the list when doing current->next
	*/
	
	currentNode = head;
	
	while (true) {
		std::cout << std::endl << "Enter value to add to linked list.  Enter no value to finish." << std::endl;
		getline(std::cin, sData);
		
		
		// this will copy our data into a stringstream object which will allow us to check if...
		// whatever data the user entered is a valid number (as per the next line: ssDataCheck >> data)
		std::stringstream ssDataCheck(sData);
		
		if (ssDataCheck >> data) {
			// add the data to a new node and add to the linked list
			currentNode = addNode(data, currentNode);
		}
		else {
			break;
		}
	}
	
	
	// here we just move forward and backward through the list, printing out the values of each node
	iterateNodes(head);
	
	std::cout << "Which value would you like to delete? " << std::endl;
	std::cin >> data;
	
	// clear out any '\n' that may still be in the c++ input stream
	std::cin.ignore();
	
	if (deleteNodeWithValue(data, head))	{
		std::cout << std::endl << "- Iterating with changes introduced into list..." << std::endl;
		iterateNodes(head);
	}
	else
		std::cout << std::endl << "- No node with that value was found." << std::endl;
	
	cleanupList(head);
	
	return 0;
	
}
