#include "wgraph.h"
#include <iostream>

int main() {
    // Create a graph with 5 vertices
    Graph g(5);

    // Add edges (directed graph for this example)
    g.addEdge(0, 1, 1.0);
    g.addEdge(0, 2, 1.0);
    g.addEdge(1, 2, 1.0);
    g.addEdge(2, 0, 1.0);
    g.addEdge(2, 3, 1.0);
    g.addEdge(3, 3, 1.0);

    // Print the graph's adjacency list
    std::cout << "Graph adjacency list:" << std::endl;
    g.print();
    std::cout << std::endl;
    g.Dijkstra(0);
/*
    // Check if the graph contains a cycle
    try {
        if (g.isCycledDirected()) {
            throw std::runtime_error("Cycled graph!!");
        } else {
            std::cout << "Graph is acyclic." << std::endl;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << std::endl;

    // Perform BFS starting from vertex 2
    std::cout << "BFS starting from vertex 2:" << std::endl;
    g.BFS(2);
    std::cout << std::endl;

    // Perform DFS (iterative) starting from vertex 2
    std::cout << "DFS (Iterative) starting from vertex 2:" << std::endl;
    g.DFS_Iterative(2);
    std::cout << std::endl;

    // Perform DFS (recursive) starting from vertex 2
    std::cout << "DFS (Recursive) starting from vertex 2:" << std::endl;
    g.DFS_Recursive(2);
    std::cout << std::endl;

    // Find the shortest path between vertices 2 and 3
    int shortestPath = g.ShortestPath(2, 3);
    std::cout << "Shortest path from 2 to 3: " << shortestPath << std::endl;
    std::cout << std::endl;

    // Get all paths from vertex 2 to vertex 3
    std::vector<std::vector<int>> allPaths = g.getAllPaths(2, 3);
    std::cout << "All paths from 2 to 3:" << std::endl;
    for (const auto& path : allPaths) {
        for (int node : path) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }*/
    std::cout << std::endl;
    return 0;
}
