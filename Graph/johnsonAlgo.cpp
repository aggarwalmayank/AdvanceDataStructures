#include<bits/stdc++.h>
using namespace std;

int minDistance(vector<int> dist,vector<bool> sptset,int V) 
{ 
    int min = INT_MAX, min_index; 
  
    for (int v=0;v<V;v++) 
        if (sptset[v]==false && dist[v]<=min) 
            min=dist[v], min_index=v; 
    return min_index; 
}
//function to calculate shortest path from a src node to every node of a graph
void dijkstra(vector<vector<int>> graph,vector<vector<int>> modGraph,int src,int V,vector<int>distFromNewVertex)
{
	vector<bool> sptset(V,false);
	vector<int> dist(V,INT_MAX);
  
    dist[src]=0;

  	for (int i=0; i<V;i++) 
  	{ 
        int currentVert = minDistance(dist, sptset,V); 
        sptset[currentVert] = true; 
        for (int v = 0; v < V; v++) 
            if (!sptset[v] && dist[v] >dist[currentVert]+modGraph[currentVert][v] && graph[currentVert][v]!=0) 
			{	
				dist[v] = dist[currentVert]+modGraph[currentVert][v]; 
			} 
    } 
    for(int i=0;i<V;i++)
    	cout<<"vertex "<<i<<" : "<<dist[i]+distFromNewVertex[i]-distFromNewVertex[src]<<endl;
  
}
//function to implement bellman ford to remove negative weights and find distance of each vertex from new vertex added
vector<int> BellmanFord(vector<vector<int>> &edge,int V)
{
	vector<int> dist(V+1,INT_MAX);
	dist[V]=0;

	for(int i=0;i<V;i++)
		edge.push_back({V,i,0});

	for(int i=0;i<V;i++)
	{
		for(int j=0;j<edge.size();j++)
		{
			int src=edge[j][0],dest=edge[j][1],weight=edge[j][2];
			if(dist[src]!=INT_MAX && dist[src] + weight < dist[dest] )
			{
				dist[dest] = dist[src] + weight;
			}
		}
	}
	vector<int> finaldist(V);
	for(int i=0;i<V;i++)
		finaldist[i]=dist[i];
	return finaldist;
}
//function to implement johnson algo
void Johnson(vector<vector<int>> graph,vector<vector<int>> &edge,int V)
{
	vector<int> distFromNewVertex=BellmanFord(edge,V);
	vector<vector<int>> modGraph( V , vector<int> (V, 0));
	for(int i=0;i<V;i++)
		for(int j=0;j<V;j++)
		{
			if(graph[i][j]!=0)
			{
				modGraph[i][j]=graph[i][j]+distFromNewVertex[i]-distFromNewVertex[j];
			}
		}
	//now running dijkstra for each vertex
	for(int i=0;i<V;i++)
	{
		cout<<"Shortest dist with vertex "<<i<<" as source are as follows\n";
		dijkstra(graph,modGraph,i,V,distFromNewVertex);
	}


}
//main function
int main()
{
	cout<<"\t_______Welcome to Johnson all Pair shortest distance______\n";
	int V,E;
	cout<<"Enter number of vertices\t";
	cin>>V;
	cout<<"\nnter number of edges\t";
	cin>>E;
	vector<vector<int>> graph( V , vector<int> (V, 0));
	vector<vector<int>> edge;
	cout<<"\nEnter edges with cost";
	for(int i=0;i<E;i++)
	{
		cout<<"\nEnter Edge "<<i<<" in format \nSRC\tDEST\tWeight\n";
		int src,dest,Cost;
		cin>>src>>dest>>Cost;
		graph[src][dest]=Cost;
		edge.push_back({src,dest,Cost});

	}
	Johnson(graph,edge,V);

}