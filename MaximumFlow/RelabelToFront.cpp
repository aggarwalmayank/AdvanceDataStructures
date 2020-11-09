#include<bits/stdc++.h>
using namespace std;

int inf = 1000000000;

int n;//no of vertices
vector<vector<int>> capacity, flow;//capacity and flow array
vector<int> height, excess, seen;//array to store height excess flow and neighbour
queue<int> excess_vertices;

//function to pass extra flow to near node ( push from u to v )
void push(int u, int v)
{
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
    if (d && excess[v] == d)
        excess_vertices.push(v);
}

//function to relabel the height of a node
void relabel(int u)
{
    int d = inf;
    for (int i = 0; i < n; i++) {
        if (capacity[u][i] - flow[u][i] > 0)
            d = min(d, height[i]);
    }
    if (d < inf)
        height[u] = d + 1;
}
//if excess flow vertex then calling discharge function
void discharge(int u)
{
    while (excess[u] > 0) {
        if (seen[u] < n) {
            int v = seen[u];
            if (capacity[u][v] - flow[u][v] > 0 && height[u] > height[v])
                push(u, v);
            else 
                seen[u]++;
        } else {
            relabel(u);
            seen[u] = 0;
        }
    }
}
//function to perform all initial initializations 
void init(int s)
{
    height.assign(n, 0);
    height[s] = n;
    flow.assign(n, vector<int>(n, 0));
    excess.assign(n, 0);
    excess[s] = inf;
    for (int i = 0; i < n; i++) {
        if (i != s)
            push(s, i);
    }
    seen.assign(n, 0);

}
//main function of relabel to front
int relabelToFront(int s, int t)
{
    init(s);
    while (!excess_vertices.empty()) 
    {
        int u = excess_vertices.front();
        excess_vertices.pop();
        if (u != s && u != t)
            discharge(u);
    }

    int max_flow = 0;
    for (int i = 0; i < n; i++)
        max_flow += flow[i][t];
    return max_flow;
}
int main()
{
    cout<<"\t_______Welcome to Relabel To Front Algo______\n";
	int E;
	cout<<"Enter number of nodes\t";
	cin>>n;
	cout<<"\nEnter number of canals\t";
	cin>>E;

	//graph
	capacity.assign(n, vector<int>(n, 0));
	
    // input of graph
	for(int i=0; i<E; i++)
	{
		cout<<"\nEnter canal "<<i<<" in format \nSRC\tDEST\tcapacity\n";
		int src,dest,cap;
		cin >>src>>dest>>cap;
        capacity[src][dest]=cap;
	}
    int s,t;
	cout<<"Enter source\t";
	cin>>s;
	cout<<"\nEnter Terminal\t";
	cin>>t;
    cout<<"Maximum flow is : "<<relabelToFront(s,t);

}