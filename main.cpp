#include "generator.hpp"
#include "Graph.hpp"
#include <iostream>
#include <limits>
#include <iomanip>

int main() {
    try {
        std::string filename = "input.txt";
        std::size_t n;
        std::size_t tops;

        std::cout << "Введите количество вершин графа: ";
        std::cin >> tops;

        GraphIO::generateAndWriteRandomGraph(filename, tops, 10, 0.4);
        std::cout << "Граф сгенерирован и записан в " << filename << "\n\n";

        unsigned int** matrix = GraphIO::readAdjacencyMatrix(filename, n);
        std::cout << "Матрица смежности:\n";
        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = 0; j < n; ++j) {
                std::cout << std::setw(4) << matrix[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";

        Graph g(matrix, n);

        std::cout << "Кратчайшие пути от всех вершин ко всем (алгоритм Дейкстры):\n";
        auto allDistances = g.dijkstraAll();
        for (std::size_t i = 0; i < allDistances.size(); ++i) {
            std::cout << "Вершина " << i + 1 << ": ";
            for (auto d : allDistances[i]) {
                if (d == std::numeric_limits<unsigned int>::max())
                    std::cout << " ∞ ";
                else
                    std::cout << std::setw(3) << d << " ";
            }
            std::cout << "\n";
        }

        std::cout << "\nТопологическая сортировка (нерекурсивный DFS):\n";
        try {
            auto order = g.topologicalSortDFS();
            for (auto v : order) std::cout << v + 1 << " ";
            std::cout << "\n";
        } catch (const std::exception& ex) {
            std::cerr << ex.what() << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
