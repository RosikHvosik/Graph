#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <limits>
#include <queue>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <stack>
#include<algorithm>

class Graph {
private:
    unsigned int** adjacencyMatrix;
    std::size_t n;

public:
    Graph(unsigned int** matrix, std::size_t size)
        : adjacencyMatrix(matrix), n(size) {}

    std::size_t size() const { return n; }

    void print() const {
        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = 0; j < n; ++j) {
                std::cout << adjacencyMatrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    std::vector<unsigned int> dijkstra(std::size_t start) const {
        const unsigned int INF = std::numeric_limits<unsigned int>::max();
        std::vector<unsigned int> dist(n, INF);
        if (start >= n) return dist;

        dist[start] = 0;
        using P = std::pair<unsigned int, std::size_t>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;

            for (std::size_t v = 0; v < n; ++v) {
                if (adjacencyMatrix[u][v] > 0) {
                    unsigned int weight = adjacencyMatrix[u][v];
                    if (dist[v] > dist[u] + weight) {
                        dist[v] = dist[u] + weight;
                        pq.push({dist[v], v});
                    }
                }
            }
        }

        return dist;
    }

    std::vector<std::vector<unsigned int>> dijkstraAll() const {
        std::vector<std::vector<unsigned int>> allDistances(n);
        for (std::size_t i = 0; i < n; ++i) {
            allDistances[i] = dijkstra(i);
        }
        return allDistances;
    }

std::vector<std::size_t> dfs_non_recursive() const {
    std::vector<bool> visited(n, false);
    std::vector<std::size_t> traversal;
    std::stack<std::size_t> s;

    for (std::size_t i = 0; i < n; ++i) {
        if (!visited[i]) {
            s.push(i);
            while (!s.empty()) {
                std::size_t node = s.top();
                s.pop();

                if (!visited[node]) {
                    visited[node] = true;
                    traversal.push_back(node);

                    for (std::size_t j = n; j-- > 0;) { // Чтобы порядок был как у рекурсивного DFS
                        if (adjacencyMatrix[node][j] > 0 && !visited[j]) {
                            s.push(j);
                        }
                    }
                }
            }
        }
    }

    return traversal;
}


    ~Graph() {
        for (std::size_t i = 0; i < n; ++i) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }
};

#endif
