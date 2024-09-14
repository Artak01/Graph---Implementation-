#include <iostream>
#include "graph.hpp"

int main() {
    // Create a graph with 5 vertices
    Vertex graph(5);

    // Add edges
    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    // Print adjacency list
    std::cout << "Adjacency List:" << std::endl;
    graph.print();
    
    // Perform DFS
    std::cout << "DFS (starting from vertex 0):" << std::endl;
    graph.DFS(0);

    // Perform recursive DFS
    std::cout << "Recursive DFS (starting from vertex 0):" << std::endl;
    graph.DFS_REC(0);

    // Perform BFS
    std::cout << "BFS (starting from vertex 0):" << std::endl;
    graph.BFS(0);

    // Get shortest path
    std::vector<int> path = graph.getShortPath(0, 3);
    std::cout << "Shortest Path from 0 to 3:" << std::endl;
    for (int vertex : path) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    // Transpose the graph
    graph.Transpose();
    std::cout << "Transposed Graph:" << std::endl;
    graph.print();

    // Check if the graph is cycled (undirected)
    std::cout << "Undirected Cycle Detected: " << (graph.isCycledUndirected() ? "Yes" : "No") << std::endl;

    // Check if the graph is cycled (directed)
    std::cout << "Directed Cycle Detected: " << (graph.isCycledDirected() ? "Yes" : "No") << std::endl;

    // Perform topological sorting
    std::cout << "Topological Sorting:" << std::endl;
    graph.topSort();

    // Count vertices at a specific level in BFS
    int level = 2;
    std::cout << "Number of vertices at level " << level << " in BFS:" << std::endl;
    std::cout << graph.getCountNthLevel(0, level) << std::endl;

    // Count vertices at a specific level in DFS
    std::cout << "Number of vertices at level " << level << " in DFS:" << std::endl;
    std::cout << graph.getCountNthLevelWithDFS(0, level) << std::endl;

    // Get all possible paths from vertex 0 to 3
    std::vector<std::vector<int>> allPaths = graph.getAllPossiblePaths(0, 3);
    std::cout << "All possible paths from 0 to 3:" << std::endl;
    for (const auto& p : allPaths) {
        for (int vertex : p) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
    }

    // Perform Kahn's algorithm for topological sorting
    std::vector<int> kahnOrder = graph.Kahn();
    std::cout << "Topological Sorting using Kahn's Algorithm:" << std::endl;
    for (int vertex : kahnOrder) {
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
