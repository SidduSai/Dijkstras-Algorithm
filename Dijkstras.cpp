#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

//data in a linked list are of type pair to store the name and value of graph node
class Pair
{
	public:
		int name;
		int value;
		Pair(const int& n, const int v): name(n), value(v) {}
};

//Nodeinfo is used to implement min heap
class Nodeinfo
{
public:
	int name;
	int val;
	
	Nodeinfo(){}
	Nodeinfo(const int& s, const int v): name(s), val(v) {} 
};

//NodeinfoComp is used to implement min heap
class NodeinfoComp
{
	public:
	bool operator() (const Nodeinfo& a, const Nodeinfo& b)
	{
		return a.val > b.val;
	}
};

//This will assign a number to each node name(of type string) for easy traversing of the graph
void findyourplace(map<string,int>& a,string& s, int& token)
{
	if(a.find(s) == a.end())
	{
		a[s] = token;
		token++;		
	}
}

//This function will explore all the connected nodes from a given node
void explore(const int num,vector < list < Pair > >& graph, priority_queue<Nodeinfo, vector<Nodeinfo>, NodeinfoComp>& heap, vector<int>& arr)
{
	list<Pair>::iterator it;
	for(it = graph[num].begin();it != graph[num].end(); it++)
	{
		if((*it).value + arr[num] < arr[(*it).name])
		{
			arr[(*it).name] = (*it).value + arr[num];
			heap.push(Nodeinfo((*it).name,arr[(*it).name]));
		}
		else
		continue;
	}
}

int main()
{
	int numofplaces;
	priority_queue<Nodeinfo, vector<Nodeinfo>, NodeinfoComp> heap;
	vector < list < Pair > > graph;
	map<string,int> a;
	cin>>numofplaces;
	for(int k = 0;k<numofplaces;k++)
	{
		int token = 0,z;
		int numofnodes,links,cost;
		string nodename,node,conn;
		list<Pair>::iterator it;
		cin >> nodename >> numofnodes;
		vector<int> arr(numofnodes,INT_MAX);	//vector array to keep track of the cost to go to each node
		graph.resize(numofnodes);
		for(int i = 0;i<numofnodes;i++)
		{	
			cin>>nodename>>links;
			findyourplace(a,nodename,token);	//This function will assign a number to each place name
			for(int j = 0 ;j<links;j++)
			{
				cin>>conn>>cost;
				findyourplace(a,conn,token);	//This function will assign a number to each place name
				z = a.find(conn)->second;
				graph[i].push_back( Pair(z,cost) );		//pushing the values into the graph
			}
		}

		heap.push(Nodeinfo(0,0));		//initializing the heap
		arr[0] = 0;
		
		while(!heap.empty())	//while heap is empty i.e until min cost for all the nodes is obtained
		{
			Nodeinfo temp;
			temp = heap.top();		//extracting the node with least cost
			explore(temp.name,graph,heap,arr);		//explore all the edges from that node
			heap.pop();		//pop that node from the heap after extracting it
		}
		cout<<"The shortest distance to the last node is "<<endl;
		cout<<"#"<<k+1<<" : "<<nodename<<", "<<arr[arr.size()-1]<<" tokens."<<endl;
		a.clear();		//clearing all the data structures for using it for next graph
		graph.clear();
		arr.clear();
	}
}
