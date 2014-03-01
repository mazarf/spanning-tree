// creates mincost span tree and prints it

#include <iostream>
#include "edge.cpp"
#include "heap.cpp"
#include "set.cpp"

using namespace std;

void minCost(Edge *edges, Edge *spanTree, set& regions, int e, int n, int& spanEdges);
void printTree(Edge *spanTree, int spanEdges, set& regions, int n);

int main()
{
	// store inputs
	
	int n, e; // # of vertices, edges
	cin >> n >> e;
	
	Edge *edges = new Edge[e];
	set regions(n);
	
	for(int i = 0; i < e; i++) // get all edges
	{
		cin >> edges[i].source
			>> edges[i].dest
			>> edges[i].weight;
			
		if(edges[i].source > edges[i].dest) // switch
		{
			int temp = edges[i].source;
			edges[i].source = edges[i].dest;
			edges[i].dest = temp;
		}
			
	}
	
	// inputs stored
			
	// sort the edges
	
	Heap<Edge> h(e);
	
	for(int i = 0; i < e; i++)
		h.push(edges[i]);
		
	Edge *temp = new Edge[e]; // store sorted list
		
	for(int i = 0; i < e; i++)
	{
		temp[i] = h.top();
		h.pop();
	}
	
	delete[] edges;
	edges = temp; // now edges contains the list
	
	// edges sorted
	
	// create span tree
	
	int spanEdges;
	Edge *spanTree = new Edge[e]; // will contain mincost span tree
	minCost(edges, spanTree, regions, e, n, spanEdges);
	
	// span tree created
	
	//for(int i = 0; i < spanEdges; i++)
	//cout    << spanTree[i].source << ' '
	//		<< spanTree[i].dest << ' '
	//		<< spanTree[i].weight << endl;
	
	printTree(spanTree, spanEdges, regions, n); 
	
	delete[] edges;
	delete[] spanTree; // clean up
	
	return 0;
}

void minCost(Edge *edges, Edge *spanTree, set& regions, int e, int n, int &spanEdges)
{
	/*while(T.e < n - 1 && U.e != 0)
	{
		
		ListNode edge = edges.top();
		edges.pop();
		
		if(s.find(edge.source) != s.find(edge.key)) // no cycle
		{
			T.addEdge(edge.source, edge.key, edge.weight);
			s.unite(edge.source, edge.key);
		}
		
		U.discardEdge(edge.source, edge.key);
		
	}*/
	
	int graphSize = e; // start with all edges in old graph
	int treeSize = 0; // none in min cost span tree
	
	while(treeSize < n - 1 && graphSize > 0)
	{
		Edge smallest = edges[0];
		
		if(regions.find(smallest.source) != regions.find(smallest.dest)) // no cycle created
		{
			spanTree[treeSize] = smallest;
			treeSize++; // added edge to tree
			
			regions.unite(smallest.source, smallest.dest);
		} // if
		
		edges++;
		graphSize--; // removed edge from graph
		
	} // while
	
	spanEdges = treeSize; // keep track of edges in spantree
	
} // minCost



void printTree(Edge *spanTree, int spanEdges, set& regions, int n)
{
	cout << "<?xml version=\"1.5\"?>" << endl;
	cout << "<country>" << endl;
	
	regions.findComponents();
	int numRegions = regions.getComponents();
	
	for(int i = 0; i < numRegions; i++)
	{
		int root = regions.findNextMin();
		Heap<Edge> h;
		
		for(int j = 0; j < spanEdges; j++)
		{
			if(regions.find(spanTree[j].source) == root)
			{
				h.push(spanTree[j]);
			}
		}
		
		cout << "<region>" << endl;
		
		while(!h.empty())
		{
			cout << "<road>" << h.top().source << " " << h.top().dest 
			<< " " << h.top().weight << "</road>" << endl;
			
			h.pop();
		}
		
		cout << "</region>" << endl;
		regions.ar[root] = -4e8;
		
			
	}
	
	cout << "</country>" << endl;
	
} // printTree
