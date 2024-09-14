#include <iostream>
#include "graph.hpp"
#include <stack>
#include <queue>

// Constructor
Vertex::Vertex(int n) 
    : sizeVertexs {n}
    , adjList {}
{
    adjList.resize(sizeVertexs);
}

// Adds an edge between two vertices
void Vertex::addEdge(int u, int v)
{
    adjList[u].push_back(v);
    adjList[v].push_back(u); //  undirected
}

// Adds a new vertex
void Vertex::addVertex() 
{
    ++sizeVertexs;
    adjList.resize(sizeVertexs);
}

// Depth First Search (DFS) iterative method
void Vertex::DFS(int start) const
{
    std::vector<bool> visit (sizeVertexs, false);
    std::stack<int>  st;
    st.push(start);
    visit[start] = true;
    while (!st.empty()) {
        int x = st.top();
        std::cout << x <<  " ";
        st.pop();
        for(int i = 0; i < adjList[x].size(); ++i) {
            if (!visit[adjList[x][i]]) {
                st.push(adjList[x][i]);
                visit[adjList[x][i]] = true;
            }
        }
    }
    std::cout << std::endl;
}

// Depth First Search (DFS) recursive method
void Vertex::DFS_REC(int start) const
{
    std::vector<bool> visit (sizeVertexs, false);
    dfsHelper(start, visit);
    std::cout << std::endl;
}

// DFS helper function
void Vertex::dfsHelper(int start, std::vector<bool>& visit) const
{
    visit[start] = true;
    std::cout << start << " ";
    for(int i = 0; i < adjList[start].size(); ++i) {
        int tmp = adjList[start][i];
        if (!visit[tmp]) {
            dfsHelper(tmp, visit);
        }
    }
}

// Breadth First Search (BFS)
void Vertex::BFS(int start) const
{
    std::vector<bool> visit (sizeVertexs, false);
    std::queue<int> q;
    q.push(start);
    visit[start] = true;
    while (!q.empty()) {
        int x = q.front();
        std::cout << x << " ";
        q.pop();
        for (int i = 0; i < adjList[x].size(); ++i) {
            int tmp = adjList[x][i];
            if (!visit[tmp]) {
                visit[tmp] = true;
                q.push(tmp);
            }
        }
    } 
    std::cout << std::endl;
}

// Returns the shortest path between vertices u and v
std::vector<int> Vertex::getShortPath(int u, int v)
{
    std::vector<bool> visit (sizeVertexs, false);
    std::queue<int> q;
    std::vector<int> perent (sizeVertexs, -1);
    q.push(u);
    visit[u] = true;
    while(!q.empty()) {
        int n = q.front();
        q.pop();
        if (n == v) {
            std::vector<int> path;
            for(int i = v; i != -1; i = perent[i]) {
                path.push_back(i);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }
        for(int elem : adjList[n]) {
            if (!visit[elem]) {
                visit[elem] = true;
                perent[elem] = n;
                q.push(elem);
            }
        }
    }
    return {};
}

// Transposes the graph (reverse all edges)
void Vertex::Transpose()
{
    Vertex tmp(sizeVertexs);
    for(int i = 0; i < sizeVertexs; ++i) {
        for(int j : adjList[i]) {
            tmp.adjList[j].push_back(i);
        }
    }
    this -> adjList = tmp.adjList;
}

// Checks if the undirected graph contains a cycle
bool Vertex::isCycledUndirected() const
{
    std::vector<bool> visit (sizeVertexs, false);
    int parent = -1;
    for (int i = 0; i < sizeVertexs; ++i) {
        if (!visit[i]) {
            if (dfsCycledUndirected(i, visit, parent)) {
                return true;
            }
        }
    }
    return false;
}

// Helper function for detecting a cycle in an undirected graph
bool Vertex::dfsCycledUndirected(int start, std::vector<bool>& visit, int perent) const
{
    visit[start] = true;
    for(auto u : adjList[start]) {
        if (!visit[u]) {
            if (dfsCycledUndirected(u, visit, start)) {
                return true;
            } 
        } else if (u != perent) {
            return true;
        }
    }
    return false;
}

// Checks if the directed graph contains a cycle
bool Vertex::isCycledDirected() const
{
    std::vector<bool> visit (sizeVertexs, false);
    std::vector<bool> recStack (sizeVertexs, false);
    for (int i = 0; i < sizeVertexs; ++i) {
        if (!visit[i]) {
            if (dfsCycledDirected(i, visit, recStack)) {
                return true;
            } 
        }
    }
    return false;
}

// Helper function for detecting a cycle in a directed graph
bool Vertex::dfsCycledDirected(int start, std::vector<bool>& visit, std::vector<bool>& recStack) const
{
    visit[start] = true;
    recStack[start] = true;
    for(auto i : adjList[start]) {
        if (!visit[i]) {
            if (dfsCycledDirected(i, visit, recStack)) {
                return true;
            }
        } else if (recStack[i]) {
            return true;
        }
    }
    recStack[start] = false;
    return false;
}

// Prints the adjacency list
void Vertex::print() const
{
    for(int i = 0; i < adjList.size(); ++i) {
        std::cout << i << " : ";
        for(int j = 0; j < adjList[i].size(); ++j) {
            std::cout << adjList[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Topological sorting
void Vertex::topSort() const
{
    if (isCycledDirected()) {
        std::cout << "Cycled graph!!" << std::endl;
        return;
    }  
    std::vector<bool> visit (sizeVertexs, false);
    std::stack<int> st;
    for(int i = 0; i < sizeVertexs; ++i) {
        if (!visit[i]) {
            dfsTopSort(i, visit, st);
        }
    }
    while(!st.empty()) {
        std::cout << st.top() << " ";
        st.pop();
    }
    std::cout << std::endl;
}

// DFS helper function for topological sorting
void Vertex::dfsTopSort(int start, std::vector<bool>& visit, std::stack<int>& st) const
{
    visit[start] = true;
    for(auto i : adjList[start]) {
        if (!visit[i]) {
            dfsTopSort(i, visit, st);
        }
    }
    st.push(start);
}

// Counts the number of vertices at a given level in BFS
int Vertex::getCountNthLevel(int start, int level) const
{
    if (level < 0) {
        throw std::invalid_argument("Invalid level!!");
    }
    std::vector<bool> visit (sizeVertexs, false);
    std::queue<std::pair<int, int>> q;
    int count = 0;
    q.push({start, 0});
    visit[start] = true;
    while (!q.empty()) {
        auto [currVertex, currLevel] = q.front();
        q.pop();
        if (currLevel == level) {
            ++count;
        } else if (currLevel < level) {
            for(auto i : adjList[currVertex]) {
                if (!visit[i]) {
                    visit[i] = true;
                    q.push({i, currLevel + 1});
                }
            }
        }
    }
    return count;
}

// Counts the number of vertices at a given level in DFS
int Vertex::getCountNthLevelWithDFS(int start, int level) const
{
    if (level < 0) {
        throw std::invalid_argument("Invalid level!!");
    }
    std::vector<bool> visit (sizeVertexs, false);
    int count = 0;
    int currLevel = 0;
    dfsNthLevel(start, currLevel, level, count, visit);
    return count;
}

// DFS helper function to count vertices at a specific level
void Vertex::dfsNthLevel(int start, int currLevel, int level, int& count, std::vector<bool>& visit) const
{
    visit[start] = true;
    if (currLevel == level) {
        ++count;
    } else if (currLevel < level) {
       for (auto i : adjList[start]) {
            if (!visit[i]) {
                dfsNthLevel(i, currLevel + 1, level, count, visit);
            }
       } 
    }
}

// Returns all possible paths between two vertices
std::vector<std::vector<int>> Vertex::getAllPossiblePaths(int src, int dest) const
{
    std::vector<bool> visit (sizeVertexs, false);
    std::vector<int> tmp;
    std::vector<std::vector<int>> res;
    dfsAllPaths(src, dest, tmp, res, visit);
    return res;
}

// DFS helper function to find all possible paths
void Vertex::dfsAllPaths(int src, int dest, std::vector<int>& tmp, std::vector<std::vector<int> >& res, std::vector<bool>& visit) const
{
    visit[src] = true;
    tmp.push_back(src);
    if (src == dest) {
        res.push_back(tmp);
    }
    for(auto i : adjList[src]) {
        if (!visit[i]) {
            dfsAllPaths(i, dest, tmp, res, visit);
        }
    }
    tmp.pop_back();
    visit[src] = false;
}

// Kahn's Algorithm for topological sorting
std::vector<int> Vertex::Kahn() const
{
    if (isCycledDirected()) {
        throw std::invalid_argument("Graph is cycled!!");
    }
    std::vector<int> indegree (sizeVertexs, 0);
    for(int i = 0; i < sizeVertexs; ++i) {
        for (auto v : adjList[i]) {
            ++indegree[v];
        }
    } 
    std::queue<int> q;
    for(int i = 0; i < indegree.size(); ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        } 
    }
    
    std::vector<int> res;
    while (!q.empty()) {
        int tmp = q.front();
        q.pop();
        res.push_back(tmp);
        for(auto u : adjList[tmp]) {
            indegree[u]--;
            if (indegree[u] == 0) {
                q.push(u);
            }
        }
    }
    return res;
}

// Kosaraju's Algorithm for Strongly Connected Components (SCCs)
std::vector<std::vector<int>> Vertex::Kosarajou() 
{
    std::vector<bool> visit (sizeVertexs, false);
    std::stack<int> st;
    for(int i = 0; i < sizeVertexs; ++i) {
        if (!visit[i]) {
            fillinorder(i, visit, st);
        }
    }

    Transpose();
    visit.assign (sizeVertexs, false);
    std::vector<std::vector<int>> res;
    while (!st.empty()) {
        int tmp = st.top();
        st.pop();
        if (!visit[tmp]) {
            std::vector<int> component;
            dfsKosarajou(tmp, visit, component);
            res.push_back(component);
        }
    }
    Transpose();
    return res;
}

// Fills the stack with vertices in finishing order
void Vertex::fillinorder(int src, std::vector<bool>& visit, std::stack<int>& st) const
{
    visit[src] = true;
    for(auto u : adjList[src]) {
        if (!visit[u]) {
            fillinorder(u, visit, st);
        }
    }
    st.push(src);
}

// DFS helper function for Kosaraju's Algorithm
void Vertex::dfsKosarajou(int src, std::vector<bool>& visit, std::vector<int>& vec) const
{
    visit[src] = true;
    vec.push_back(src);
    for(auto u : adjList[src]) {
        if (!visit[u]) {
            dfsKosarajou(u, visit, vec);
        }
    }
}

// Tarjan's Algorithm for Strongly Connected Components (SCCs)
std::vector<std::vector<int>> Vertex::TarjansAlgorithm() const
{
    std::vector<std::vector<int>> SCCs;
    std::vector<bool> onStack(sizeVertexs, false);
    std::vector<int> ids(sizeVertexs, -1);
    std::vector<int> lowlink(sizeVertexs, -1);
    std::stack<int> st;

    for (int i = 0; i < sizeVertexs; ++i) {
        if (ids[i] == -1) {
            TarjanHelper(i, ids, lowlink, st, onStack, SCCs);
        }
    }

    return SCCs;
}

// Tarjan's Algorithm helper function
void Vertex::TarjanHelper(int src, std::vector<int>& ids, std::vector<int>& lowlink, std::stack<int>& st, std::vector<bool>& onStack, std::vector<std::vector<int>>& SCCs) const
{
    static int visitingTime = 0;
    ids[src] = lowlink[src] = ++visitingTime;
    st.push(src);
    onStack[src] = true;

    for (int v : adjList[src]) {
        if (ids[v] == -1) {
            TarjanHelper(v, ids, lowlink, st, onStack, SCCs);
        }
        if (onStack[v]) {
            lowlink[src] = std::min(lowlink[src], lowlink[v]);
        }
    }

    if (lowlink[src] == ids[src]) {
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