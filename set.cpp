#include <iostream>
//#include <algorithm>
using namespace std;

class set
{
	public:
	
	set(int n)
	{
		ar = new int[n];
		this->n = n;
		components = n;
		
		for(int i = 0; i < n; i++)
			ar[i] = -1; // all start as roots
	} // constructor
	~set()
	{
		delete[] ar;
	}
	int find(int i) // return canonical representation of set
	{
		if(ar[i] > 0)
			return find(ar[i]);
		else
			return i;
	}
	void unite(int i, int j)
	{
		// apply weight rule
		
		int x = find(i);
		int y = find(j);
		int sizeX = -ar[x];
		int sizeY = -ar[y];
		
		if(sizeX <= sizeY)
		{
			ar[x] = y;
			ar[y] = -sizeX - sizeY;
		}
		else
		{
			ar[y] = x;
			ar[x] = -sizeX - sizeY;
		}
		
	}
	
	int min(int v)
	{ // find min of v's set
		for(int i = 0; i < n; i++)
			if(find(i) == find(v))
				return i;
				
		return -1;
	}
	
	int max(int v)
	{ // find max of v's set
		for(int i = n - 1; i >= 0; i--)
			if(find(i) == find(v))
				return i;
				
		return -1;
	}
	
	void findComponents()
	{ // calculate number of separate components
		components = 0; // reset
		
		for(int i = 0; i < n; i++)
			if(ar[i] < 0) // root
				components++;
				
	}
	
	int getComponents()
	{
		return components;
	}
	
	int findNextMin()
	{ // WARNING: destroys the set. use last!
		int smallest = 4e8;
		int index = -1;
		
		for(int i = 0; i < n; i++)
			if( ar[i] < 0 )
			{
				if(smallest == 4e8) // proceed normally
				{	
					smallest = -ar[i];
					index = i;
				}
				else if(-ar[i] < smallest)
				{
					smallest = -ar[i];
					index = i;
				}
				else if(-ar[i] == smallest && min(i) < min(index))
				{
					smallest = -ar[i];
					index = i;
				}
			}
			
		return index;
	}
	
	int *ar;
	int n;
	int components;
	
	
}; // set class

class adjmat
{
	public:
	adjmat(int n)
	{
		for(int i = 0; i < n; i++)
		{
			ar[i] = new int[n];
			fill(ar[i], ar[i] + n, 0);
			ar[i][i] = 1;
		}
	}
	void adjacent(int v, int u)
	{
		ar[u][v] = 1;
		ar[v][u] = 1;
	}
	
	int **ar;
}; // adjmat


class linkedAdj
{
	
};


//int main()
//{
	
	//adjmat a(5);
	//a.adjacent(1,2);
	//a.adjacent(3,4);
	//a.adjacent(2,4);
	
	//for(int i = 0; i < 5; i++)
	//{
		//for(int j = 0; j < 5; j++)
			//cout << a.ar[i][j];
			
		//cout << endl;
	//}
	
	//return 0;
	
//} // main




