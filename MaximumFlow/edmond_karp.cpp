#include<bits/stdc++.h>
using namespace std;

//function to traverse bfs in residual graph
bool bfs(vector< vector<int> > residual_Graph, int s, int t, int parent[],int V) 
{ 
    // bool visited[V]; 
    // Create a visited array and mark all vertices as not visited 
    vector<bool> visited(V,false);
    // memset(visited, 0, sizeof(visited)); 
  
    queue <int> q; 
    q.push(s); 
    visited[s] = true; 
    parent[s] = -1; 
  
    while (!q.empty()) 
    { 
        int u = q.front(); 
        q.pop(); 
        for (int v=0; v<V; v++) 
        { 
            if (visited[v]==false && residual_Graph[u][v] > 0) 
            { 
                q.push(v); 
                parent[v] = u; 
                visited[v] = true; 
            } 
        } 
    } 
    // if termianl reached return true
    return (visited[t] == true); 
} 
  
//function which perform edmond-karp algo 
int edmond_karp(vector< vector<int> > graph, int s, int t,int V) 
{ 
    int u, v; 
    //creating residual graph and filling it
    vector< vector<int> > residual_Graph(V, vector<int>(V,0));
    for (u = 0; u < V; u++) 
        for (v = 0; v < V; v++) 
             residual_Graph[u][v] = graph[u][v]; 
  
    int parent[V];  // This array is filled by BFS and to store path 
    int max_flow = 0; 
  
    while (bfs(residual_Graph, s, t, parent,V)) 
    { 
        int path_flow = INT_MAX; 
        for (v=t; v!=s; v=parent[v]) 
        { 
            u = parent[v]; 
            path_flow = min(path_flow, residual_Graph[u][v]); 
        } 
    
        //updating residual graph
        for (v=t; v != s; v=parent[v]) 
        { 
            u = parent[v]; 
            residual_Graph[u][v] -= path_flow; 
            residual_Graph[v][u] += path_flow; 
        } 
  
        // Add path flow to overall flow 
        max_flow += path_flow; 
    } 
  
    // Return the overall flow 
    return max_flow; 
} 
int main()
{
    cout<<"\t_______Welcome to Edmond-karp Algo______\n";
	int V,E;
	cout<<"Enter number of nodes\t";
	cin>>V;
	cout<<"\nEnter number of canals\t";
	cin>>E;

	//graph
	vector< vector<int> > graph(V, vector<int>(V,0));
	
	// input of graph
	for(int i=0; i<E; i++)
	{
		cout<<"\nEnter canal "<<i<<" in format \nSRC\tDEST\tcapacity\n";
		int src,dest,cap;
		cin >>src>>dest>>cap;
        graph[src][dest]=cap;
	}
    int s,t;
	cout<<"Enter source\t";
	cin>>s;
	cout<<"\nEnter Terminal\t";
	cin>>t;
    cout<<"Maximum flow is : "<<edmond_karp(graph,s,t,V);

}