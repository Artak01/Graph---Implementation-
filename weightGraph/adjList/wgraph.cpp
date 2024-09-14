#include "wgraph.h"

Graph::Graph(int n) 
    : numVertices(n) 
    , adjList(n) 
{
    adjList.resize(numVertices);
}

void Graph::addVertex()
{
    ++numVertices;
    adjList.resize(numVertices);
}

void Graph::addEdge(int u, int v, double weight)
{
    adjList[u].push_back({v, weight});
    adjList[v].push_back({u, weight});
}

void Graph::BFS(int start) const
{
    std::vector<bool> visit (numVertices, false);
    std::queue<int> q;
    visit[start] = true;
    q.push(start);

    while (!q.empty()) {
        int tmp = q.front();
        std::cout << tmp << " ";
        q.pop();
        for (auto i : adjList[tmp]) {
            if (!visit[i.first]) {
                visit[i.first] = true;
                q.push(i.first);
            }
        }
    }
    std::cout << std::endl;
}

void Graph::DFS_Iterative(int start) const
{
    std::vector<bool> visit(numVertices, false);
    std::stack<int> st;

    visit[start] = true;
    st.push(start);

    while (!st.empty()) {
        int tmp = st.top();
        std::cout << tmp << " ";
        st.pop();
        for (auto i : adjList[tmp]) {
            if (!visit[i.first]) {
                visit[i.first] = true;
                st.push(i.first);
            }
        }
    }
    std::cout << std::endl;
}

void Graph::DFS_Recursive(int start) const
{
    std::vector<bool> visit(numVertices, false);
    dfsHelper(start, visit);
    std::cout << std::endl;
}

void Graph::print() const
{
    for(int i = 0; i < adjList.size(); ++i) {
        std::cout << i << " : ";
        for(auto u : adjList[i]) {
            std::cout << "{" << u.first << ", " << u.second << "}" << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::transpose()
{
    Graph tmp(numVertices);
    for(int i = 0; i < numVertices; ++i) {
        for(auto [u, w] : adjList[i]) {
            tmp.adjList[u].emplace_back(i, w);
        }
    }
    *this = tmp;
}

int Graph::ShortestPath(int start, int end) const {
    std::vector<bool> visit(numVertices, false);
    std::stack<int> st;
    for (int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
            dfstopSort(i, visit, st);
        }
    }
    std::vector<int> dist(numVertices, INT_MAX);
    dist[start] = 0;

    while (!st.empty()) {
        int tmp = st.top();
        st.pop();

        if (dist[tmp] != INT_MAX) {
            for (auto& u : adjList[tmp]) {
                if (dist[tmp] + u.second < dist[u.first]) {
                    dist[u.first] = dist[tmp] + u.second;
                }
            }
        }
    }
    int res = dist[end] - dist[start];
    if (res < 0 || res == INT_MAX) {
        std::cerr << "Don't way!" << std::endl;
        exit(0);
    }
    return res;
}

int Graph::nthLevelNodeCount (int src, int level) const
{
    if (level < 0) {
        throw std::invalid_argument("Is the negative number!");
    }
    std::vector<int> visit (numVertices, false);
    std::queue<std::pair<int, int>> q;
    int count = 0;
    q.push({src, 0});
    while (!q.empty()) {
        auto [currNode, currLevel] = q.front();
        q.pop();
        if (currLevel == level) {
            ++count;
        } else if (currLevel < level) {
            for(auto u : adjList[currNode]) {
                if(!visit[u.first]) {
                    visit[u.first] = true;
                    q.push({u.first, currLevel + 1});
                }
            }
        }
    }
    return count;
}

std::vector<std::vector<int>> Graph::getAllPaths(int src, int dest) const
{
    std::vector<bool> visit (numVertices, false);
    std::vector<std::vector<int>> Paths;
    std::vector<int> path;
    dfsAllPathsHelper(src, dest, Paths, path, visit);
    return Paths;
}

bool Graph::isCycledDirected() const
{
    std::vector<bool> visit (numVertices, false);
    std::vector<bool> recStack (numVertices, false);
    for (int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
            if (dfsisCycledDirected(i, visit, recStack)) {
                return true;
            }
        }
    }
    return false;
}

bool Graph::isCycledUndirected() const
{
    std::vector<bool> visit (numVertices, false);
    int parent = -1;
    for (int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
            if (dfsisCycledUndirected(i, visit, parent)) {
                return true;
            }
        }
    }
    return false;
}

int Graph::DFS_ExtraCase() const
{
    std::vector<bool> visit (numVertices, false);
    int count = 0;
    for(int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
            dfsExtraCases(i, visit);
            ++count;
        }
    }   
    return count;
}

std::vector<int> Graph::topSort() const
{
    if (isCycledDirected()) {
        throw std::runtime_error("Cycled graph!!");    
    }
    std::vector<bool> visit (numVertices, false);
    std::stack<int> st;
    for (int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
            dfstopSort(i, visit, st);
        }
    }
    std::vector<int> res;
    while (!st.empty()) {
        int tmp = st.top();
        st.pop();
        res.push_back(tmp);
    }
    return res;
}

std::vector<int> Graph::Kahn() const
{
    if (isCycledDirected()) {
        throw std::runtime_error("Cycled graph!!");
    }
    std::vector<int> indgree (numVertices, 0);
    for(int i = 0; i < numVertices; ++i) {
        for (auto u : adjList[i]) {
            indgree[u.first];
        }
    }
    std::queue<int> q;
    for(int i = 0; i < numVertices; ++i) {
        if (indgree[i] == 0) {
            q.push(i);
        }
    }
    std::vector<int> res;
    while(!q.empty()) {
        int tmp = q.front();
        q.pop();
        res.push_back(tmp);
        for(auto u : adjList[tmp]) {
            --indgree[u.first];
            if (indgree[u.first] == 0) {
                q.push(u.first);
            }
        }
    }
    return res;
}

std::vector<std::vector<int>> Graph::Kosaraju()
{
    std::vector<bool> visit (numVertices, false);
    std::stack<int> st;
    for(int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
            fillInOrder(i, visit, st);
        }
    } 
    transpose();
    visit.assign(numVertices, false);
    std::vector<std::vector<int>> SCC;
    while (!st.empty()) {
        int tmp = st.top();
        st.pop();
        if (!visit[tmp]) {
            std::vector<int> component;
            dfsKosaraju(tmp, visit, component);
            SCC.push_back(component);
        }
    }
    return SCC;
}

std::vector<std::vector<int>> Graph::Tarjan() const
{
    std::vector<std::vector<int>> SCC;
    std::vector<bool> onStack(numVertices, false);
    std::vector<int> ids(numVertices, -1);
    std::vector<int> lowlink(numVertices, -1);
    std::stack<int> st;

    for (int i = 0; i < numVertices; ++i) {
        if (ids[i] == -1) {
            dfs_tarjan(i, ids, lowlink, st, onStack, SCC);
        }
    }
    return SCC;
}

////////////////////////////////////////////
///////////////////////////////////////////

void Graph::dfsHelper(int start, std::vector<bool>& visit) const
{
    visit[start] = true;
    std::cout << start << " ";
    for (auto i : adjList[start]) {
        if(!visit[i.first]) {
            dfsHelper(i.first, visit);
        }
    }
}

void Graph::dfstopSort(int src, std::vector<bool>& visit, std::stack<int>& st) const 
{
    visit[src] = true;
    for (auto& u : adjList[src]) {
        if (!visit[u.first]) {
            dfstopSort(u.first, visit, st);
        }
    }
    st.push(src);
}

void Graph::dfsAllPathsHelper(int src, int dest, std::vector<std::vector<int>>& Paths, std::vector<int>& path, std::vector<bool>& visit) const
{
    visit[src] = true;
    path.push_back(src);
    if (src == dest) {
        Paths.push_back(path);
    }
    for(auto u : adjList[src]) {
        if (!visit[u.first]) {
            dfsAllPathsHelper(u.first, dest, Paths, path, visit);
        }
    }
    visit[src] = false;
    path.pop_back();
}

bool Graph::dfsisCycledDirected(int src, std::vector<bool>& visit, std::vector<bool>& recStack) const
{
    visit[src] = true;
    recStack[src] = true;
    for (auto u : adjList[src]) {
        if (!visit[u.first]) {
            if (dfsisCycledDirected(u.first, visit, recStack)) {
                return true;
            }
        } else if (recStack[u.first]) {
            return true;
        }
    }
    recStack[src] = false;
    return false;
}

bool Graph::dfsisCycledUndirected(int src, std::vector<bool>& visit, int parent) const
{
    visit[src] = true;
    for (auto u : adjList[src]) {
        if (!visit[u.first]) {
            if (dfsisCycledUndirected(u.first, visit, parent)) {
                return true;
            }
        } else if (u.first != parent) {
            return true;
        }
    }
    return false;
}

void Graph::dfsKosaraju(int src, std::vector<bool>& visit, std::vector<int>& component) const
{
    visit[src] = true;
    component.push_back(src);
    for (auto& u : adjList[src]) {
        if (!visit[u.first]) {
            dfsKosaraju(u.first, visit, component);
        }
    }
}

void Graph::dfsExtraCases(int src, std::vector<bool>& visit) const
{
    visit[src] = true;
    for(auto u : adjList[src]) {
        if (!visit[u.first]) {
            dfsExtraCases(u.first, visit);
        }
    }
}

void Graph::fillInOrder(int src, std::vector<bool>& visit, std::stack<int>& st) const
{
    dfstopSort(src, visit, st);
}

void Graph::dfs_tarjan(int src, std::vector<int>& ids, std::vector<int>& lowlink, std::stack<int>& st, std::vector<bool>& onStack, std::vector<std::vector<int>>& SCC) const
{
    static int visitingTime = 0;
    ids[src] = lowlink[src] = ++visitingTime;
    st.push(src);
    onStack[src] = true;

    for (auto v : adjList[src]) {
        if (ids[v.first] == -1) {
            dfs_tarjan(v.first, ids, lowlink, st, onStack, SCC);
        }
        if (onStack[v.first]) {
            lowlink[src] = std::min(lowlink[src], lowlink[v.first]);
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
        SCC.push_back(currSCC);
    }
}

void Graph::Dijkstra(int source) {
    std::vector<int> dist(numVertices, std::numeric_limits<int>::max());
    std::priority_queue<std::pair<int, int>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto v : adjList[u]) {
            int weight = v.second;

            if (dist[u] + weight < dist[v.first]) {
                dist[v.first] = dist[u] + weight;
                pq.push({dist[v.first], v.first});
            }
        }
    }

    for (int i = 0; i < numVertices; ++i) {
        std::cout << dist[i] << " ";
    }
    std::cout << std::endl;
}