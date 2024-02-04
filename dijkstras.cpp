#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <list>
#include <climits>

using namespace std;

typedef pair<int, int> iPair;

class Graph
{
    int V;
    list<pair<int, int>> *adj;

public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void shortestPath(int s, int dest);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair>[V];
}

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

void Graph::shortestPath(int src, int dest)
{
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);
    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        list<pair<int, int>>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;

            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
                parent[v] = u;
            }
        }
    }

    cout << "\nShortest path length is " << dist[dest];

    cout << "\nPath is ";
    vector<int> path;
    for (int v = dest; v != src; v = parent[v])
        path.push_back(v);
    path.push_back(src);
    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++)
        cout << path[i] << " ";
}

int main()
{
    int V = 6;
    Graph g(V);

    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 1, 8);
    g.addEdge(2, 3, 6);
    g.addEdge(3, 4, 9);
    g.addEdge(4, 5, 3);

    int start, end;
    cout << "Enter the start vertex: ";
    cin >> start;
    cout << "Enter the end vertex: ";
    cin >> end;

    g.shortestPath(start, end);

    return 0;
}
