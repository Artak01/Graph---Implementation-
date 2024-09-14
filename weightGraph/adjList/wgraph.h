#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <map>  

class Graph
{
public:
    Graph(int n);
    void addVertex();
    void addEdge(int src, int dest, double weight);  
    void BFS(int start) const;
    void DFS_Iterative(int start) const;
    void DFS_Recursive(int start) const;
    void print() const;
    void transpose();
    int ShortestPath(int start, int end) const;
    int nthLevelNodeCount (int src, int level) const;
    std::vector<std::vector<int>> getAllPaths(int src, int dest) const;
    bool isCycledDirected() const;
    bool isCycledUndirected() const;
    int DFS_ExtraCase() const;
    std::vector<int> topSort() const;
    std::vector<int> Kahn() const;
    std::vector<std::vector<int>> Kosaraju();
    std::vector<std::vector<int>> Tarjan() const;
    void Dijkstra(int source);

private:
    void dfsHelper(int start, std::vector<bool>& visit) const;
    void dfstopSort(int src, std::vector<bool>& visit, std::stack<int>& st) const; 
    void dfsAllPathsHelper(int src, int dest, std::vector<std::vector<int>>& Paths, std::vector<int>& path, std::vector<bool>& visit) const;
    bool dfsisCycledDirected(int src, std::vector<bool>& visit, std::vector<bool>& recstack) const;
    bool dfsisCycledUndirected(int src, std::vector<bool>& visit, int parent) const;
    void dfsKosaraju(int src, std::vector<bool>& visit, std::vector<int>& component) const;
    void dfsExtraCases(int src, std::vector<bool>& visit) const;
    void fillInOrder(int src, std::vector<bool>& visit, std::stack<int>& st) const;
    // Graph scc_transpose() const;
    void dfs_tarjan(int src, std::vector<int>& ids, std::vector<int>& lowlink, std::stack<int>& st, std::vector<bool>& onStack, std::vector<std::vector<int>>& SCC) const;

private:
    int numVertices;
    std::vector<std::vector<std::pair<int, int>>> adjList;
};

#endif  // GRAPH_H
