// graph class
// uses LinkedList

#include "list.cpp"
#include "set.cpp"
#include "heap.cpp"
#include <iostream>


#ifndef GRAPH_CPP
#define GRAPH_CPP

using namespace std;

class Graph
{
	public:
		Graph(int n);
		~Graph();
		void addEdge(int i, int j, int weight = 0);
		void printList();
		bool hasEdge(int i, int j);
		Graph minCost();
		void dfs(int n);
		void dfsAll();
		void discardEdge(int v, int u);
	private:
		List *adjList;
		int n; // vertices
		int e; // edges
		int **weights;
		set *region; // keep track of all regions
		bool *visited;
};

Graph::Graph(int n)
{
	adjList = new List[n];
	this->n = n;
	e = 0;
	
	// init weights
	weights = new int*[n];
	for(int i = 0; i < n; i++)
	{
		weights[i] = new int[n];
		for(int j = 0; j < n; j++)
			weights[i][j] = 0;
	}
	
	region = new set(n);
	visited = new bool[n];
	
	for(int i = 0; i < n; i++)
		visited[n] = false;
	
} // constructor

Graph::~Graph()
{
	//delete[] weights;
	//delete region;
	//delete[] visited;
} // destructor

void Graph::addEdge(int i, int j, int weight)
{ // adds edge if not already there
	if(!hasEdge(i,j))
	{
		adjList[i].addBack(j, weight, i);
		adjList[j].addBack(i, weight, j);
		weights[i][j] = weight;
		weights[j][i] = weight;
		e++;
	}
} // addEdge

void Graph::printList()
{
	
	cout << "<?xml version=\"1.5\"?>" << endl;
	cout << "<country>" << endl;
	
	region->findComponents();
	int numRegions = region->getComponents();
	
	for(int i = 0; i < numRegions; i++)
	{
		int root = region->findNextMin();
		Heap<ListNode> h;
		for(int j = 0; j < n; j++)
		{
			for(int k = 0; k < adjList[j].getNodes(); k++)
				if(region->find(j) == root && j < adjList[j][k].key)
					h.push(adjList[j][k]);
					
		}
		
		cout << "<region>" << endl;
		
		while(!h.empty())
		{
			cout << "<road>" << h.top().source << " " << h.top().key 
			<< " " << h.top().weight << "</road>" << endl;
			
			h.pop();
		}
		
		cout << "</region>" << endl;
		region->ar[root] = -4e8;
		
			
	}
	
	//for(int i = 0; i < n; i++)
	//{
		////int status = 0;
		////while(status != -1) // reached end of adjacency list
		////{
			////status = adjList[i].printDest(i);
		////}
		
		//for(int j = 0; j < n; j++)
		//{
			
				//try {
					//if(i < adjList[i][j].key) // prevents duplicate printing
						//cout << "<road>" << i << " " << adjList[i][j].key 
						//<< " " << weights[i][adjList[i][j].key] << "</road>" << endl;
				//} catch(const char * s) {
					 //break;
				//}
				
		//}
		
	//}
	
	cout << "</country>" << endl;
	
}

bool Graph::hasEdge(int i, int j)
{
	for(int k = 0; k < adjList[i].getNodes(); k++)
	{
		if(adjList[i][k].key == j)
			return true;
	}

	return false;
} // hasEdge

Graph Graph::minCost()
{ // generate min cost spanning tree (kruskal's algorithm)
	Graph T(n); // tree to be created
	Graph U = *this; // copy of this graph
	set &s = (*T.region); // keep track of cycles
	
	Heap<ListNode> edges(e);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < adjList[i].getNodes(); j++)
		{
			//ListNode edge = adjList[i][j];
			//cout << edge.source << " " << edge.key << " " << edge.weight << endl;
			if(i < adjList[i][j].key)
				edges.push(adjList[i][j]);
		}
				
	//for(int i = 0; i < e; i++)
	//{
	//	ListNode v = edges.top();
	//	cout << v.source << " " << v.key << " " << v.weight << endl;
	//	edges.pop();
	//}
	
	while(T.e < n - 1 && U.e != 0)
	{
		
		ListNode edge = edges.top();
		edges.pop();
		//cout << edge.source << ' ' << edge.key << ' ' << edge.weight << endl;
		
		if(s.find(edge.source) != s.find(edge.key)) // no cycle
		{
			T.addEdge(edge.source, edge.key, edge.weight);
			s.unite(edge.source, edge.key);
		}
		
		U.discardEdge(edge.source, edge.key);
		
		//int smallest = 4e8;
		//int sx = -1, sy = -1;
		//// choose edge with lowest cost
		//for(int i = 0; i < n; i++)
		//{
			//for(int j = 0; j < adjList[i].getNodes(); j++)
			//{
				//int vertex = adjList[i][j].key; // actual vertex, not just location in list
				//int vertexWeight = adjList[i][j].weight; // to make this somewhat readable
				
				//if(vertexWeight != 0 && vertexWeight < smallest)
				//{
					//if(s.find(i) != s.find(vertex)) // cycle ?
					//{
						//smallest = vertexWeight;
						//sx = i; sy = j;
					//}
					//else // discard edge
					//{
						//U.discardEdge(i, vertex);
						//U.e--;
					//}
				//}
			//}
		//}
		
		//if(sx != -1 && sy != -1)
		//{
			//int vertex = adjList[sx][sy].key; // same as before
			//s.unite(sx, vertex);
			//T.addEdge(sx, vertex, smallest);
			//U.e--;
		//}
	} // while
	
	T.printList();
	return T;
	
}

void Graph::dfs(int n)
{
	if(!visited[n])
	{
		//cout << n << endl;
		visited[n] = true;
		for(int j = 0; j < adjList[n].getNodes(); j++)
		{
				
				if(region->find(n) != region->find(adjList[n][j].key)) // weird error
				{
					cout << n << adjList[n][j].key << endl;
					region->unite(n, adjList[n][j].key); // mark as same region
					dfs(adjList[n][j].key);
				} // if
			
		} // for all adjacent vertices
	} // if visited
		
}

void Graph::dfsAll()
{
	for(int i = 0; i < n; i++)
	{
		if(!visited[i])
		{
			cout << "r" << endl;
			dfs(i);
			cout << "/r" << endl;
		}
	}
	
	//for(int i = 0; i < n; i++)
	//{
	//	cout << region->find(i) << endl;
	//}
}

void Graph::discardEdge(int v, int u)
{ // marks the edge between vertices v and u as 0

	for(int i = 0; i < adjList[v].getNodes(); i++)
	{
		if(adjList[v][i].key == u)
			adjList[v][i].weight = 0;
	}
	
	for(int i = 0; i < adjList[u].getNodes(); i++)
	{
		if(adjList[u][i].key == v)
			adjList[u][i].weight = 0;		
	}
	
	e--;

} // discardEdge
#endif
