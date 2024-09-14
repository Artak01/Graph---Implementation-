#include <iostream>
#include "graph.hpp"

int main() {
    // Create a graph with 5 vertices
    Graph graph(5);

    // Add edges
    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    // Print adjacency matrix
    std::cout << "Adjacency Matrix:" << std::endl;
    graph.print();

    // Perform iterative DFS starting from vertex 0
    std::cout << "Iterative DFS (starting from vertex 0):" << std::endl;
    graph.DFS(0);

    // Perform recursive DFS starting from vertex 0
    std::cout << "Recursive DFS (starting from vertex 0):" << std::endl;
    graph.DFS_REC(0);

    // Perform BFS starting from vertex 0
    std::cout << "BFS (starting from vertex 0):" << std::endl;
    graph.BFS(0);

    // Get and print shortest path from vertex 0 to vertex 3
    std::vector<int> path = graph.getShortPath(0, 3);
    std::cout << "Shortest Path from 0 to 3: ";
    for (int vertex : path) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    // Transpose the graph
    graph.Transpose();
    std::cout << "Transposed Graph Adjacency Matrix:" << std::endl;
    graph.print();

    // Check for cycles in the undirected graph
    std::cout << "Cycle Detected in Undirected Graph: " << (graph.isCycledUndirected() ? "Yes" : "No") << std::endl;

    // Check for cycles in the directed graph
    std::cout << "Cycle Detected in Directed Graph: " << (graph.isCycledDirected() ? "Yes" : "No") << std::endl;

    // Perform topological sort
    std::vector<int> topoSort = graph.topSort();
    std::cout << "Topological Sort: ";
    for (int vertex : topoSort) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    // Get and print number of vertices at level 2 from vertex 0
    int level = 2;
    std::cout << "Number of vertices at level " << level << " from vertex 0: " << graph.getCountNthLevel(0, level) << std::endl;

    // Get and print all possible paths from vertex 0 to vertex 3
    std::vector<std::vector<int>> allPaths = graph.getAllPossiblePaths(0, 3);
    std::cout << "All possible paths from 0 to 3:" << std::endl;
    for (const auto& path : allPaths) {
        for (int vertex : path) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
    }

    // Perform Kahn's algorithm for topological sorting
    std::vector<int> kahnSort = graph.Kahn();
    std::cout << "Topological Sort using Kahn's Algorithm: ";
    for (int vertex : kahnSort) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    // Perform Kosaraju's algorithm for strongly connected components
    std::vector<std::vector<int>> kosarajuSCCs = graph.Kosarajou();
    std::cout << "Strongly Connected Components (Kosaraju's Algorithm):" << std::endl;
    for (const auto& component : kosarajuSCCs) {
        for (int vertex : component) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
    }

    // Perform Tarjan's algorithm for strongly connected components
    std::vector<std::vector<int>> tarjansSCCs = graph.TarjansAlgorithm();
    std::cout << "Strongly Connected Components (Tarjan's Algorithm):" << std::endl;
    for (const auto& component : tarjansSCCs) {
        for (int vertex : component) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
