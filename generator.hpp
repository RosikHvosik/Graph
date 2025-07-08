#ifndef GRAPH_IO_HPP2
#define GRAPH_IO_HPP2

#include <fstream>
#include <string>
#include <stdexcept>
#include <random>
#include <ctime>
#include <iostream>

class GraphIO {
public:
    static unsigned int** readAdjacencyMatrix(const std::string& filename, std::size_t& n) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл: " + filename);
        }

        file >> n;
        if (n < 5 || n > 100) {
            throw std::out_of_range("Количество вершин должно быть от 5 до 100.");
        }

        unsigned int** matrix = new unsigned int*[n];
        for (std::size_t i = 0; i < n; ++i) {
            matrix[i] = new unsigned int[n];
            for (std::size_t j = 0; j < n; ++j) {
                if (!(file >> matrix[i][j])) {
                    throw std::runtime_error("Ошибка чтения данных матрицы из файла.");
                }
            }
        }

        return matrix;
    }

    static void writeAdjacencyMatrix(const std::string& filename, unsigned int** matrix, std::size_t n) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
        }

        file << n << "\n";
        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = 0; j < n; ++j) {
                file << matrix[i][j];
                if (j < n - 1) file << " ";
            }
            file << "\n";
        }
    }

    static void generateAndWriteRandomGraph(const std::string& filename, std::size_t n, int maxWeight = 20, double density = 0.3) {
        if (n < 5 || n > 100) {
            throw std::invalid_argument("n должно быть в пределах [5, 100]");
        }

        unsigned int** matrix = new unsigned int*[n];
        for (std::size_t i = 0; i < n; ++i) {
            matrix[i] = new unsigned int[n];
            for (std::size_t j = 0; j < n; ++j) {
                matrix[i][j] = 0;
            }
        }

        std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
        std::uniform_real_distribution<> edgeProb(0.0, 1.0);
        std::uniform_int_distribution<> weightDist(1, maxWeight);

        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = 0; j < n; ++j) {
                if (i != j && edgeProb(rng) < density) {
                    matrix[i][j] = weightDist(rng);
                }
            }
        }

        writeAdjacencyMatrix(filename, matrix, n);

        for (std::size_t i = 0; i < n; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
};

#endif
