#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
//#include <vector>

using namespace std;

template <class N>
class LinkedList {
	
protected:
	typedef struct Node {
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
	
	// create new node with N data as its value
	void addNode(N data);
	
	void deleteNode( Node* deleteNode);
	
	// custom compare functions used in conjunction with std::sort
	static bool compareNodes(const Node* left, const Node* right);
	
	
	void insertNode(N data, Node* shiftPoint);
	
	// function to sort nodes by doing std::sort()
	void sortNodes();
	
	// iterate through list and print out values
	void iterateList();
	
	// this allows us to subscript our linked list, so we can access each node as if it were an array
	Node* operator[](int nodeSub) {
		return index[nodeSub];
	}
	
};

template<class N>
void LinkedList<N>::sortNodes() {
	
	// I had initially tried a qsort to no avail.  the compareNodes() definition was different then.
	//qsort((void*)*index, nodeCount, sizeof(*index[0]), compareNodes);
	
	/* vector crap that thankfully i don't need
	 Node* temp = index[0];
	 
	 // push back all our nodes in the linked list into this vector
	 while (temp != NULL)
	 {
	 nodeVec.push_back(temp);
	 temp = temp->next;
	 }
	 
	 // sort the vector
	 std::sort(nodeVec.begin(), nodeVec.end(), compareNodes);
	 
	 // necessary?
	 // reorganize all our actual nodes so they correspond with the sorted nodes in the vector container
	 
	 for (int nodeElem = 0; nodeElem < nodeVec.size(); nodeElem++)
	 index[nodeElem] = nodeVec[nodeElem];
	 */
	
	
	std::sort(index, index+nodeCount, compareNodes);
	
	// readjust next and prev ptrs (loops are always bottlenecks, huh?)	
	for (int nodeElem = 0; nodeElem < nodeCount-1; nodeElem++) {
		index[nodeElem]->next = index[nodeElem+1];
		index[nodeElem+1]->prev = index[nodeElem];
	}
	
	index[nodeCount-1]->next = NULL;
}


template<class N>
bool LinkedList<N>::compareNodes(const Node* left, const Node* right) {
	
	return (*left->data < *right->data);
}

template<class N>
void LinkedList<N>::insertNode(N data, Node* shiftPoint) {
	
	nodeCount++;
	
	//reallocate more space
	index = ( Node**) realloc(index, sizeof( Node) * nodeCount);
	index[nodeCount-1] = ( Node*)malloc(sizeof( Node));
	index[nodeCount-1]->data = (N*) malloc(sizeof(N));
	
	// Point to our newly created node
	Node* temp = index[nodeCount-1];
	
	// link this new node's prev pointer to point to our last node in the list
	index[nodeCount-1]->prev = index[nodeCount-2];
	
	// link the last node to this new node we just created
	index[nodeCount-2]->next = index[nodeCount-1];
	
	// set the next pointer to NULL for our new node so we know this is the end of the list
	index[nodeCount-1]->next = NULL;
	
	while (temp != shiftPoint) {
		// shift all spots forward up until we're at our newly allocated space
		// that way we have essentially a break to set our inserted value in
		*temp->data = *temp->prev->data;
		temp = temp->prev;
	}
	
	// update data at shift point to the data we want at that spot
	*temp->data = data;
	
}


template<class N>
void LinkedList<N>::deleteNode( Node* shiftPoint) {
	
	Node* temp = shiftPoint;
	
	while (temp->next != NULL) {
		// shift all the pointers down!
		// this will overwrite the current node we want to get rid of...
		// and in essence, move all the other ones down one so they're all contiguous again
		*temp->data = *temp->next->data;
		temp = temp->next;
	}
	
	// free up the memory so the OS can use it somewhere else
	free(temp);
	
	//point the previous node's next ptr to NULL so the linked list ends at the previous node
	// i.e. so when we iterate through our list, it stops before it gets to our now deleted node
	temp->prev->next = NULL;
	
	// point to null, so there are no potential errors from freeing same memory again
	temp = NULL;
	
	// resize index again?
	//nodeCount--;
	//index = (Node**) realloc(index, sizeof(Node) * nodeCount);
	
	// drop our nodeCount down to account for deletion of node
	nodeCount--;
}

template <class N>
void LinkedList<N>::addNode(N data) {
	
	nodeCount++;
	
	index = ( Node**) realloc(index, sizeof( Node) * nodeCount);
	index[nodeCount-1] = ( Node*)malloc(sizeof( Node));
	index[nodeCount-1]->data = (N*) malloc(sizeof(N));
	
	*index[nodeCount-1]->data = data;
	index[nodeCount-1]->nodeNum = nodeCount;
	
	// link this new node's prev pointer to point to our last node in the list
	index[nodeCount-1]->prev = index[nodeCount-2];
	
	// link the last node to this new node we just created
	index[nodeCount-2]->next = index[nodeCount-1];
	
	// set the next pointer to NULL for our new node so we know this is the end of the list
	index[nodeCount-1]->next = NULL;
	
}

template <class N>
void LinkedList<N>::iterateList() {
	
	/*
	 for (int x = 0; x < nodeCount; x++)
	 std::cout << "Node num: " << index[x]->nodeNum << " has value " << *index[x]->data << std::endl;
	 */
	
	Node *temp = index[0];
		
	while (temp != NULL) {
		std::cout << "Node [" << temp->nodeNum << "] has value [" << *temp->data << "]" << std::endl;
		temp = temp->next;
	}
	
}