// spanning tree program
#include <iostream>
#include "graph.cpp"

using namespace std;

int main()
{
	int n = 0, e = 0; // vertices, edges
	cin >> n >> e;
	
	int source[e], dest[e], weight[e];
	for(int i = 0; i < e; i++)
	{
		cin >> source[i] >> dest[i] >> weight[i];
		if(source[i] == dest[i])
		{
			cout << "Found self loop." << endl;
			return 0;
		}
	}
	
	Graph g(n);
	
	for(int i = 0; i < e; i++)
		g.addEdge(source[i], dest[i], weight[i]);
	
	//g.dfsAll();
	g.minCost();
	
	return 0;
}
