// generic list node
// has a key/data integer
// and points to the next node

// uses: lists, stacks, queues
#ifndef LIST_NODE
#define LIST_NODE

class ListNode
{
	
	friend class List;
	friend class Stack;
	friend class Queue;
	
	public:
		ListNode(int value, int wt, int src);
		ListNode();
		int source;
		int key;
		int weight;
		ListNode *next;
		
		int min(int s, int t);
		int max(int s, int t);
		
		bool operator<(ListNode v); // for heap
		bool operator<=(ListNode v);
		bool operator>(ListNode v);
		
}; // listnode


ListNode::ListNode(int value, int wt, int src)
{ // initializes node

	key = value;
	weight = wt;
	source = src;
	next = 0;
	
} // constructor

ListNode::ListNode()
{
};

int ListNode::min(int s, int t)
{
	if(s < t)
		return s;
		
	return t;
}

int ListNode::max(int s, int t)
{
	if(s > t)
		return s;
		
	return t;
}

bool ListNode::operator<(ListNode v)
{
	if(weight < v.weight)
		return true;
	else if(weight == v.weight)
	{
		if(min(source, key) < min(v.source, v.key))
		{
			return true;
		}
		else if(min(source,key) == min(v.source, v.key))
		{
			if(max(source, key) < max(v.source, v.key))
			{
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

bool ListNode::operator<=(ListNode v)
{
	if(weight < v.weight)
		return true;
	else if( weight == v.weight && source == v.source && key == v.key )
		return true;
	else
		return false;
}

bool ListNode::operator>(ListNode v)
{
	if(weight > v.weight)
		return true;
	else if(weight == v.weight)
	{
		if(min(source, key) > min(v.source, v.key))
		{
			return true;
		}
		else if(min(source,key) == min(v.source, v.key))
		{
			if(max(source, key) > max(v.source, v.key))
			{
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}
#endif
