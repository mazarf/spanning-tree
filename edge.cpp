// generic list node
// has a key/data integer
// and points to the next node

// uses: lists, stacks, queues
#ifndef EDGE_CPP
#define EDGE_CPP

class Edge
{
	
	friend class List;
	friend class Stack;
	friend class Queue;
	
	public:
		Edge(int value, int wt, int src);
		Edge();
		int source;
		int dest;
		int weight;
		
		int min(int s, int t);
		int max(int s, int t);
		
		bool operator<(Edge v); // for heap
		bool operator<=(Edge v);
		bool operator>(Edge v);
		
}; // Edge


Edge::Edge(int value, int wt, int src)
{ // initializes node

	dest = value;
	weight = wt;
	source = src;
	
} // constructor

Edge::Edge()
{
};

int Edge::min(int s, int t)
{
	if(s < t)
		return s;
		
	return t;
}

int Edge::max(int s, int t)
{
	if(s > t)
		return s;
		
	return t;
}

bool Edge::operator<(Edge v)
{
	if(weight < v.weight)
		return true;
	else if(weight == v.weight)
	{
		if(min(source, dest) < min(v.source, v.dest))
		{
			return true;
		}
		else if(min(source,dest) == min(v.source, v.dest))
		{
			if(max(source, dest) < max(v.source, v.dest))
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

bool Edge::operator<=(Edge v)
{
	if(weight < v.weight)
		return true;
	else if( weight == v.weight && source == v.source && dest == v.dest )
		return true;
	else
		return false;
}

bool Edge::operator>(Edge v)
{
	if(weight > v.weight)
		return true;
	else if(weight == v.weight)
	{
		if(min(source, dest) > min(v.source, v.dest))
		{
			return true;
		}
		else if(min(source,dest) == min(v.source, v.dest))
		{
			if(max(source, dest) > max(v.source, v.dest))
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