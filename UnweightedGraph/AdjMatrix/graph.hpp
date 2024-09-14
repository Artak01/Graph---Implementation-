#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

class Graph
{
public:
    // Constructor to initialize a graph with 'n' vertices
    Graph(int n);

    // Adds an edge between vertex 'u' and vertex 'v'
    void addEdge(int u, int v);

    // Adds a new vertex to the graph
    void addVetex();

    // Performs an iterative Depth First Search (DFS) starting from 'start' vertex
    void DFS(int start) const;

    // Performs a recursive Depth First Search (DFS) starting from 'start' vertex
    void DFS_REC(int start) const;

    // Performs a Breadth First Search (BFS) starting from 'start' vertex
    void BFS(int start) const;

    // Prints the adjacency matrix of the graph
    void print() const;

    // Returns the shortest path between vertex 'u' and vertex 'v'
    std::vector<int> getShortPath(int u, int v);

    // Transposes the graph by reversing all edges
    void Transpose();

    // Checks if the undirected graph contains a cycle
    bool isCycledUndirected() const;

    // Checks if the directed graph contains a cycle
    bool isCycledDirected() const;

    // Returns a topological sort of the graph (only for Directed Acyclic Graphs)
    std::vector<int> topSort() const;

    // Returns the number of vertices at the nth level from 'src'
    int getCountNthLevel(int src, int level) const;

    // Returns all possible paths from vertex 'src' to vertex 'dest'
    std::vector<std::vector<int>> getAllPossiblePaths(int src, int dest) const;

    // Performs Kahn's algorithm to return a topological sort
    std::vector<int> Kahn() const;

    // Uses Kosarajou's algorithm to find Strongly Connected Components (SCCs)
    std::vector<std::vector<int>> Kosarajou();

    // Uses Tarjan's algorithm to find Strongly Connected Components (SCCs)
    std::vector<std::vector<int>> TarjansAlgorithm() const;

private:
    // Number of vertices in the graph
    int sizeVertex;

    // Adjacency matrix to represent the graph
    std::vector<std::vector<int>> adjMatrix;

    // Helper function for Depth First Search (DFS)
    void dfsHelper(int src, std::vector<int>& visit) const;

    // Helper function for detecting a cycle in an undirected graph
    bool dfsCycledUndirected(int src, std::vector<bool>& visit, int perent) const;

    // Helper function for detecting a cycle in a directed graph
    bool dfsCycledDirected(int start, std::vector<bool>& visit, std::vector<bool>& onStack) const;

    // Helper function for topological sorting using DFS
    void dfsTopSort(int src, std::vector<bool>& visit, std::stack<int>& st) const;

    // Helper function for finding all paths from 'src' to 'dest'
    void dfsAllPaths(int src, int dest, std::vector<int>& tmp, std::vector<std::vector<int>>& res, std::vector<bool>& visit) const;

    // Helper function to fill vertices in order of their finishing times (Kosarajou's algorithm)
    void fillinorder(int src, std::vector<bool>& visit, std::stack<int>& st) const;

    // Helper function to perform DFS in Kosarajou's algorithm
    void dfsKosarajou(int src, std::vector<bool>& visit, std::vector<int>& vec) const;

    // Helper function for Tarjan's algorithm to find SCCs
    void TarjanHelper(int src, std::vector<int>& ids, std::vector<int>& lowlink, std::stack<int>& st, std::vector<bool>& onStack, std::vector<std::vector<int>>& SCCs) const;
};

#endif
