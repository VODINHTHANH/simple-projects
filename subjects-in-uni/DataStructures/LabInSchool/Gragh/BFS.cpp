#include <iostream>
#include <list>
#include <queue>
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
private:
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
        adj[w].push(v);
    }

    void printGraph()
    {
        for (int v = 0; v < V; ++v)
        {
            cout << "\nAdjacency list of vertex " << v << "\nhead ";
            adj[v].print();
        }
    }
    bool isPresentInQueue(int key, queue<int> &keys)
    {
        queue<int> temp;
        bool flag = false;
        while (keys.empty() == false)
        {
            if (keys.front() == key)
            {
                temp.push(keys.front());
                keys.pop();
                flag = true;
            }
            else
            {
                temp.push(keys.front());
                keys.pop();
            }
        }
        while (temp.empty() == false)
        {
            keys.push(temp.front());
            temp.pop();
        }
        return flag;
    }
    Adjacency *BFS(int v)
    {
        queue<int> s;
        // v is a vertex we start BFS
        s.push(v);
        int temp = v;
        queue<int> c;
        while (s.empty() == false)
        {
            for (int i = 0; i < V; i++)
            {
                if (temp == i)
                {
                    s.pop();
                    for (int j = 0; j < adj[i].getSize(); j++)
                    {
                        if (isPresentInQueue(temp, c) == false)
                            s.push(adj[i].getElement(j));
                    }
                    if (isPresentInQueue(temp, c) == false)
                    {
                        c.push(temp);
                    }
                    temp = s.front();
                    break;
                }
            }
        }
        Adjacency *re = new Adjacency();
        for (int i = 0; i < V; i++)
        {
            int x = c.front();
            re->push(x);
            c.pop();
        }
        return re;
    }
};
int main()
{
    int V = 6;
    int visited = 2;

    Graph g(V);
    Adjacency *arr = new Adjacency(V);
    int edge[][2] = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 4}, {3, 4}, {3, 5}, {4, 5}};

    for (int i = 0; i < 8; i++)
    {
        g.addEdge(edge[i][0], edge[i][1]);
    }

    arr = g.BFS(visited);
    arr->printArray();
    delete arr;
}