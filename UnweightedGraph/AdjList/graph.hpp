#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <stack>

// Constructor
class Vertex 
{
public:
    Vertex(int n);

    // Adds an edge between two vertices
    void addEdge(int u, int v);

    // Adds a new vertex
    void addVertex();

    // Depth First Search (DFS) iterative method
    void DFS(int start) const;

    // Depth First Search (DFS) recursive method
    void DFS_REC(int start) const;

    // Breadth First Search (BFS)
    void BFS(int start) const; 

    // Prints the adjacency list
    void print() const;

    // Returns the shortest path between vertices u and v
    std::vector<int> getShortPath(int u, int v);

    // Transposes the graph (reverse all edges)
    void Transpose();

    // Checks if the undirected graph contains a cycle
    bool isCycledUndirected() const;

    // Checks if the directed graph contains a cycle
    bool isCycledDirected() const;

    // Topological sorting
    void topSort() const;

    // Counts the number of vertices at a given level in BFS
    int getCountNthLevel(int start, int level) const;

    // Counts the number of vertices at a given level in DFS
    int getCountNthLevelWithDFS(int start, int level) const;

    // Returns all possible paths between two vertices
    std::vector<std::vector<int> > getAllPossiblePaths(int src, int dest) const;

    // Kahn's algorithm for topological sorting
    std::vector<int> Kahn() const;

    // Kosaraju's algorithm for finding strongly connected components
    std::vector<std::vector<int>> Kosarajou();

    // Tarjan's algorithm for finding strongly connected components
    std::vector<std::vector<int>> TarjansAlgorithm() const;

private:
    int sizeVertexs;
    std::vector<std::vector<int>> adjList; 

    // DFS helper function
    void dfsHelper(int start, std::vector<bool>& visit) const;

    // Helper function for detecting a cycle in an undirected graph
    bool dfsCycledUndirected(int start, std::vector<bool>& visit, int perent) const;

    // Helper function for detecting a cycle in a directed graph
    bool dfsCycledDirected(int start, std::vector<bool>& visit, std::vector<bool>& recStack) const;

    // DFS helper function for topological sorting
    void dfsTopSort(int start, std::vector<bool>& visit, std::stack<int>& st) const;

    // DFS helper function to count vertices at a specific level
    void dfsNthLevel(int start, int currLevel, int level, int& count, std::vector<bool>& visit) const;

    // DFS helper function for finding all paths between two vertices
    void dfsAllPaths(int src, int dest, std::vector<int>& tmp, std::vector<std::vector<int> >& res, std::vector<bool>& visit) const;

    // Helper function to fill the stack for Kosaraju's algorithm
    void fillinorder(int src, std::vector<bool>& visit, std::stack<int>& st) const;

    // DFS helper function for Kosaraju's algorithm
    void dfsKosarajou(int src, std::vector<bool>& visit, std::vector<int>& vec) const;

    // Tarjan's algorithm helper function
    void TarjanHelper(int src, std::vector<int>& ids, std::vector<int>& lowlink, std::stack<int>& st, std::vector<bool>& onStack, std::vector<std::vector<int>>& SCCs) const;

};

#endif
