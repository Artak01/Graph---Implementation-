#include "graph.hpp"

// Constructor for the Graph class that initializes the adjacency matrix
Graph::Graph(int n) 
    : sizeVertex(n)
    , adjMatrix(n, std::vector<int>(n, 0)) 
{}

// Adds a directed edge from vertex u to vertex v
void Graph::addEdge(int u, int v)
{
    if (u >= 0 && u < sizeVertex && v >= 0 && v < sizeVertex) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;   // Uncomment for undirected graph
    }
}

// Adds a new vertex to the graph by increasing the size of the adjacency matrix
void Graph::addVetex()
{
    ++sizeVertex;
    adjMatrix.resize(sizeVertex);
    for (int i = 0; i < adjMatrix.size(); ++i) {
        adjMatrix[i].resize(sizeVertex);
    }
}

// Depth First Search (DFS) iterative method
void Graph::DFS(int start) const
{
    std::stack<int> st;
    std::vector<int> visit(sizeVertex, false);
    st.push(start);
    visit[start] = true;
    while (!st.empty()) {
        int element = st.top();
        std::cout << element << " ";
        st.pop();
        for (int i = 0; i < adjMatrix[element].size(); ++i) {
            int tmp = adjMatrix[element][i];
            if (!visit[i] && tmp == 1) {
                st.push(i);
                visit[i] = true;
            }
        }
    }
    std::cout << std::endl;
}

// Depth First Search (DFS) recursive method
void Graph::DFS_REC(int start) const
{
    std::vector<int> visit(sizeVertex, false);
    dfsHelper(start, visit);
    std::cout << std::endl;
}

// DFS helper function for recursion
void Graph::dfsHelper(int start, std::vector<int>& visit) const
{
    visit[start] = true;
    std::cout << start << " ";
    for (int i = 0; i < adjMatrix[start].size(); ++i) {
        if (!visit[i] && adjMatrix[start][i] == 1) {
            dfsHelper(i, visit);
        }
    }
}

// Breadth First Search (BFS)
void Graph::BFS(int start) const
{
    std::vector<int> visit(sizeVertex, false);
    std::queue<int> q;
    q.push(start);
    visit[start] = true;
    while (!q.empty()) {
        int ele = q.front();
        std::cout << ele << " ";
        q.pop();
        for (int i = 0; i < adjMatrix[ele].size(); ++i) {
            if (adjMatrix[ele][i] == 1 && !visit[i]) {
                q.push(i);
                visit[i] = true;
            }
        }
    }
    std::cout << std::endl;
}

// Get the shortest path between vertices u and v
std::vector<int> Graph::getShortPath(int u, int v)
{
    std::vector<bool> visit(sizeVertex, false);
    std::queue<int> q;
    std::vector<int> perent(sizeVertex, -1);
    q.push(u);
    visit[u] = true;
    while (!q.empty()) {
        int n = q.front();
        q.pop();
        if (n == v) {
            std::vector<int> path;
            for (int i = v; i != -1; i = perent[i]) {
                path.push_back(i);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }
        for (int elem : adjMatrix[n]) {
            if (!visit[elem] && adjMatrix[n][elem] == 1) {
                visit[elem] = true;
                perent[elem] = n;
                q.push(elem);
            }
        }
    }
    return {};
}

// Print the adjacency matrix of the graph
void Graph::print() const {
    for (const auto& row : adjMatrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Transpose the graph (reverse all edges)
void Graph::Transpose()
{
    for (int i = 0; i < sizeVertex; ++i) {
        for (int j = i + 1; j < sizeVertex; ++j) {
            std::swap(adjMatrix[i][j], adjMatrix[j][i]);
        }
    }
}

// Check if the undirected graph contains a cycle
bool Graph::isCycledUndirected() const
{
    std::vector<bool> visit(sizeVertex, false);
    int parent = -1;
    for (int i = 0; i < sizeVertex; ++i) {
        if (!visit[i]) {
            if (dfsCycledUndirected(i, visit, parent)) {
                return true;
            }
        }
    }
    return false;
}

// Helper function for detecting a cycle in an undirected graph using DFS
bool Graph::dfsCycledUndirected(int start, std::vector<bool>& visit, int parent) const
{
    visit[start] = true;
    for (auto u : adjMatrix[start]) {
        if (!visit[u] && adjMatrix[start][u] == 1) {
            if (dfsCycledUndirected(u, visit, start)) {
                return true;
            } 
        } else if (u != parent) {
            return true;
        }
    }
    return false;
}
// Check if the directed graph contains a cycle
bool Graph::isCycledDirected() const
{
    std::vector<bool> visit(sizeVertex, false);
    std::vector<bool> onStack(sizeVertex, false);

    for (int i = 0; i < sizeVertex; ++i) {
        if (!visit[i]) {
            if (dfsCycledDirected(i, visit, onStack)) {
                return true;
            }
        }
    } 
    return false;
}

// Helper function for detecting a cycle in a directed graph using DFS
bool Graph::dfsCycledDirected(int src, std::vector<bool>& visit, std::vector<bool>& onStack) const
{
    visit[src] = true;
    onStack[src] = true;

    for (int i = 0; i < sizeVertex; ++i) {
        if (adjMatrix[src][i] == 1) {
            if (!visit[i]) {
                if (dfsCycledDirected(i, visit, onStack)) {
                    return true;
                }
            } else if (onStack[i]) {
                return true;
            }
        }
    }

    onStack[src] = false;
    return false;
}

// Topological sort using DFS
std::vector<int> Graph::topSort() const
{
    if (isCycledDirected()) {
        throw std::runtime_error("Graph is Cycled!");
    }
    std::vector<bool> visit(sizeVertex, false);
    std::stack<int> st;
    for (int i = 0; i < sizeVertex; ++i) {
        if (!visit[i]) {
            dfsTopSort(i, visit, st);
        }
    }
    std::vector<int> result;
    while (!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }
    return result;
}

// Helper function for DFS used in topological sort
void Graph::dfsTopSort(int src, std::vector<bool>& visit, std::stack<int>& st) const
{
    visit[src] = true;
    for (int i = 0; i < sizeVertex; ++i) {
        if (adjMatrix[src][i] == 1) {
            if (!visit[i]) {
                dfsTopSort(i, visit, st);
            }
        }
    }
    st.push(src);
}

// Get the count of nodes at a specific level from a source node
int Graph::getCountNthLevel(int src, int level) const
{
    if (level < 0) {
        throw std::invalid_argument("Invalid level!!");
    }
    std::vector<int> visit(sizeVertex, false);
    std::queue<std::pair<int, int>> q;
    int count = 0;
    q.push({src, 0});
    while (!q.empty()) {
        auto [currNode, currLevel] = q.front();
        q.pop();
        if (level == currLevel) {
            ++count;
        } else if (currLevel < level) {
            for (int i = 0; i < sizeVertex; ++i) {
                if (adjMatrix[currNode][i] == 1) {
                    if (!visit[i]) {
                        visit[i] = true;
                        q.push({i, currLevel + 1});
                    }
                }
            }
        }
    }
    return count;
}

// Get all possible paths between source and destination nodes
std::vector<std::vector<int>> Graph::getAllPossiblePaths(int src, int dest) const
{
    std::vector<std::vector<int>> result;
    std::vector<int> tmp;
    std::vector<bool> visit(sizeVertex, false);
    dfsAllPaths(src, dest, tmp, result, visit);
    return result;
}

// Helper function for DFS to find all paths between two nodes
void Graph::dfsAllPaths(int src, int dest, std::vector<int>& tmp, std::vector<std::vector<int>>& res, std::vector<bool>& visit) const
{
    visit[src] = true;
    tmp.push_back(src);

    if (src == dest) {
        res.push_back(tmp);
    } else {
        for (int i = 0; i < sizeVertex; ++i) {
            if (adjMatrix[src][i] == 1 && !visit[i]) {
                dfsAllPaths(i, dest, tmp, res, visit);
            }
        }
    }
    tmp.pop_back();
    visit[src] = false;
}

// Kahn's algorithm for topological sorting
std::vector<int> Graph::Kahn() const
{
    std::vector<int> indegree(sizeVertex, 0);
    for (int i = 0; i < sizeVertex; ++i) {
        for (int j = 0; j < sizeVertex; ++j) {
            if (adjMatrix[i][j] == 1) {
                indegree[j]++;
            }
        }
    }
    std::queue<int> q;
    for (int i = 0; i < indegree.size(); ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    std::vector<int> res;
    while (!q.empty()) {
        int tmp = q.front();
        q.pop();
        res.push_back(tmp);
        for (int i = 0; i < sizeVertex; ++i) {
            indegree[i]--;
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
    }
    if (res.size() == sizeVertex) {
        return res;
    }
    return {};
}

// Kosaraju's algorithm for finding strongly connected components
std::vector<std::vector<int>> Graph::Kosarajou()
{
    std::vector<std::vector<int>> result;
    std::vector<bool> visit(sizeVertex, false);
    std::stack<int> st;
    for (int i = 0; i < sizeVertex; ++i) {
        fillinorder(i, visit, st);
    }
    visit.assign(sizeVertex, false);
    Transpose();
    while (!st.empty()) {
        int tmp = st.top();
        st.pop();
        for (int i = 0; i < sizeVertex; ++i) {
            if (adjMatrix[tmp][i] == 1 && !visit[i]) {
                std::vector<int> vec;
                dfsKosarajou(i, visit, vec);
                result.push_back(vec);
            }
        }
    }
    Transpose();
    return result;
}

// Fill the stack with nodes in decreasing finish time for Kosaraju's algorithm
void Graph::fillinorder(int src, std::vector<bool>& visit, std::stack<int>& st) const
{
    visit[src] = true;
    for (int i = 0; i < sizeVertex; ++i) {
        if (adjMatrix[src][i] && !visit[i]) {
            fillinorder(i, visit, st);
        }
    }
    st.push(src);
}

// DFS used by Kosaraju's algorithm to find SCCs
void Graph::dfsKosarajou(int src, std::vector<bool>& visit, std::vector<int>& vec) const
{
    visit[src] = true;
    vec.push_back(src);
    for (int i = 0; i < sizeVertex; ++i) {
        if (adjMatrix[src][i] && !visit[i]) {
            dfsKosarajou(i, visit, vec);
        }
    }
}

// Tarjan's algorithm for finding strongly connected components
std::vector<std::vector<int>> Graph::TarjansAlgorithm() const
{
    std::vector<std::vector<int>> SCCs;
    std::vector<int> ids(sizeVertex, 0);
    std::vector<int> lowLink(sizeVertex, 0);
    std::vector<bool> onStack(sizeVertex, false);
    std::stack<int> st;
    for (int i = 0; i < sizeVertex; ++i) {
        if (ids[i] == -1) {
            TarjanHelper(i, ids, lowLink, st, onStack, SCCs);
        }
    }
    return SCCs;
}

// Helper function for Tarjan's algorithm
void Graph::TarjanHelper(int src, std::vector<int>& ids, std::vector<int>& lowLink, std::stack<int>& st,
                         std::vector<bool>& onStack, std::vector<std::vector<int>>& SCCs) const
{
    static int time = 0;
    ids[src] = lowLink[src] = ++time;
    onStack[src] = true;
    st.push(src);
    for (int i = 0; i < sizeVertex; ++i) {
        if (ids[i] == -1) {
            TarjanHelper(i, ids, lowLink, st, onStack, SCCs);
        }
        if (onStack[i]) {
            lowLink[src] = std::min(lowLink[src], lowLink[i]);
        }
    }
    if (lowLink[src] == ids[src]) {
        std::vector<int> currSCC;
        while (st.top() != src) {
            int elem = st.top();
            currSCC.push_back(elem);
            st.pop();
            onStack[elem] = false;
        }
        currSCC.push_back(st.top());
        onStack[st.top()] = false;
        st.pop();
        SCCs.push_back(currSCC);
    }
}
