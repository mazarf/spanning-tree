// list class
// manages listnodes and functions relating to them

#ifndef LIST
#define LIST

#include "listnode.cpp"
#include <iostream>
using namespace std;

class List
{
	public:
		List();
		void addBack(int value, int wt, int src);
		void delBack();
		
		void addFront(int value, int wt, int src);
		void delFront();
		
		bool empty();
		
		void printNodes();
		int printDest(int src); // prints a single adjacency
		int getNodes();
		
		ListNode& operator[](int i);
		
	
	protected:
		ListNode *front; // self explanatory
		ListNode *back;
		int numNodes; // could be useful
		
};

List::List()
{
	front = back = 0;
	numNodes = 0;
} // constructor

void List::addBack(int value, int wt, int src)
{ // add a node to the back
	
	// if no node yet
	if(front == 0)
	{
		front = back = new ListNode(value, wt, src);
	}
	else // already nodes, just add to back
	{
		back->next = new ListNode(value, wt, src);
		back = back->next; // move back pointer
	}
	
	numNodes++;
	
} // add to back

void List::delBack()
{ // remove a node from the back

	if(front == 0) // no nodes
	{
		cout << "No nodes!" << endl;
	}
	else if(front == back) // only one node
	{
		delete front;
		front = back = 0;
		numNodes--;
	}
	else
	{
		// go to next-to-last node
		ListNode *currNode = front;
		while(currNode->next != back)
		{
			currNode = currNode->next;
		} // while
		
		// now at next-to-last. delete last node
		delete back;
		currNode->next = 0;
		back = currNode; // new back
		numNodes--;
	}

} // delBack

void List::addFront(int value, int wt, int src)
{
	
	if(front == 0)
	{
		front = back = new ListNode(value, wt, src);
	}
	else 
	{
	
		ListNode *temp;
		temp = front; // holds old front
		front = new ListNode(value, wt, src);
		front->next = temp; // new front points to old front
		
	}
	numNodes++;
} // addFront

void List::delFront()
{
	
	if(front == 0)
	{
		cout << "Empty!" << endl;
	}
	else if(front == back)
	{
		delete front;
		front = back = 0;
		numNodes--;
	}
	else
	{
		ListNode *temp = front;
		front = front->next;
		delete temp;
		
		numNodes--;
	}
	
} // delFront

bool List::empty()
{
	if(front == 0)
		return true;
		
	return false;
}

void List::printNodes()
{ // what do you think?

	if(front == 0) // print nothing
	{
		cout << "Empty!" << endl;
		return;
	} // if empty

	ListNode *currNode = front;
	while(currNode)
	{
		cout << currNode->key << " ";
		currNode = currNode->next;
	} // while there are nodes to print
	
	cout << endl;

} // printNodes

int List::getNodes()
{
	return numNodes;
}

ListNode& List::operator[](int i)
{
	if(i >= numNodes)
		throw "NOPE";
		
	ListNode *currNode = front;
		
	for(int j = 0; j < i; j++)
	{
		currNode = currNode->next;
	}
	
	return (*currNode);
}

#endif
