#include <bits/stdc++.h>
using namespace std;

#define INF 1e9
int result = INT_MAX;

//function of bidirectional dijkstra
void biDijkstra(int s, int t,vector< vector<pair<int,int>> > graph,vector< vector<pair<int,int>> > reversegraph)
{
	vector<int> df(V,INF);//arracy to store forward dist
	vector<int> db(V,INF);// array to store backward distance
	df[s]=0;
	db[t]=0;
	
	set<int> visited;//set to store visited node

	//priority queue for forward
	priority_queue< pair<int,int>, vector< pair<int,int> >, greater<pair<int,int>> > queueF;
	queueF.push(pair<int,int>(0,s));
	
	//priority queue for forward
	priority_queue< pair<int,int>, vector< pair<int,int> >, greater<pair<int,int>> > queueB; 
	queueB.push(pair<int,int>(0,t));
	
	while(1)
	{
		//dijkstra on forward graph
		pair<int,int> topFor = queueF.top();
		queueF.pop();
		int d=topFor.first, u=topFor.second;
		for(int j=0; j<graph[u].size(); j++)
		{
			pair<int,int> v = graph[u][j];
			if(df[u] + v.second < df[v.first])
			{
				df[v.first] = df[u] + v.second;
				queueF.push(pair<int,int>(df[v.first],v.first));
			}
		}

		//updating the result
		if(result > df[u]+db[u])
			result = df[u]+db[u];

		//inserting the node in the list of processed nodes
		if(visited.insert(u).second == false)
			break;


		//dijkstra on reverse graph
		pair<int,int> topBack = queueB.top(); 
		queueB.pop();
		d = topBack.first;u = topBack.second;
		for(int j=0; j<reversegraph[u].size(); j++)
		{
			pair<int,int> v = reversegraph[u][j];
			if(db[u] + v.second < db[v.first])
			{
				db[v.first] = db[u] + v.second;
				queueB.push(pair<int,int>(db[v.first],v.first));
			}
		}

		//updating the result
		if(result > df[u]+db[u])
			result = df[u]+db[u];

		//inserting the nodes in the list of processed nondes
		if(visited.insert(u).second == false)
			break;
		
		if(queueF.empty() || queueB.empty())//breaking condition
			break;
	}
	return;	
}
//main function
int main()
{
	cout<<"\t_______Welcome to Bi-Directional Dijkstra______\n";
	int V,E;
	cout<<"Enter number of vertices\t";
	cin>>V;
	cout<<"\nnter number of edges\t";
	cin>>E;

	//graph and reverse graph initialization
	vector< vector<pair<int,int>> > graph(V, vector<pair<int,int>>());
	vector< vector<pair<int,int>> > reversegraph(V, vector<pair<int,int>>());
	
	// input og graph
	for(int i=0; i<E; i++)
	{
		cout<<"\nEnter Edge "<<i<<" in format \nSRC\tDEST\tWeight\n";
		int src,dest,wt;
		cin >>src>>dest>>wt;
		graph[src].push_back(pair<int,int>(dest,wt));
		reversegraph[dest].push_back(pair<int,int>(src,wt));
	}

	int src,dest;
	cout<<"\nEnter source and destination whose distance we want to find\n";
	cin>>src>>dest;
	
	//calling bidirectional dijkstra function
	biDijkstra(src,dest,graph,reversegraph);
	
	if(result==INF)
		cout <<"No Path Exist\n";
	else
		cout <<"\nShortest Distance is  "<<result;
	return 0;
}