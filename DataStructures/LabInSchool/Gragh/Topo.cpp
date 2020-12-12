#include <iostream>
#include <list>
#include <stack>
using namespace std;

class Adjacency
{
private:
    list<int> adjList;
    int size;

public:
    Adjacency() {}
    Adjacency(int V) {}
    void push(int data)
    {
        adjList.push_back(data);
        size++;
    }
    void print()
    {
        for (auto const &i : adjList)
            cout << " -> " << i;
    }
    void printArray()
    {
        for (auto const &i : adjList)
            cout << i << " ";
    }
    int getSize() { return adjList.size(); }
    int getElement(int idx)
    {
        auto it = adjList.begin();
        advance(it, idx);
        return *it;
    }
};
class Graph
{

    int V;
    Adjacency *adj;

public:
    Graph(int V)
    {
        this->V = V;
        adj = new Adjacency[V];
    }
    void addEdge(int v, int w)
    {
        adj[v].push(w);
    }
    void topologicalSortUtil(int v, bool visited[],
                             stack<int> &Stack)
    {
        // Mark the current node as visited.
        visited[v] = true;

        // Recur for all the vertices
        // adjacent to this vertex
        for (int i = 0; i < adj[v].getSize(); i++)
        {
            int x = adj[v].getElement(i);
            if (visited[x] == false)
                topologicalSortUtil(x, visited, Stack);
        }
        // Push current vertex to stack
        // which stores result
        Stack.push(v);
    }
    //Heling functions

    void topologicalSort()
    {
        stack<int> Stack;

        // Mark all the vertices as not visited
        bool *visited = new bool[V];
        for (int i = 0; i < V; i++)
            visited[i] = false;

        // Call the recursive helper function
        // to store Topological
        // Sort starting from all
        // vertices one by one
        for (int i = 0; i < V; i++)
        {
            if (visited[i] == false)
                topologicalSortUtil(i, visited, Stack);
        }
        // Print contents of stack
        while (Stack.empty() == false)
        {
            cout << Stack.top() << " ";
            Stack.pop();
        }
    }
};
int main()
{
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    g.topologicalSort();
}