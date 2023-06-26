#include <iostream>
#include <NTL/mat_ZZ.h>
#include <NTL/vec_ZZ.h>
#include <vector>
#include <fstream>
#include <chrono>

using namespace NTL;
using namespace std;

void GenerateAndWrite(int n) {
	const std::string filename = "input.txt";
    mat_ZZ matrix;
    vec_ZZ vector;

    matrix.SetDims(n, n);
    vector.SetLength(n);

    for (int i = 0; i < n; ++i) {
        vector[i] = RandomBits_ZZ(42);
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = RandomBits_ZZ(42);
        }
    }

    std::ofstream file(filename);
    if (file.is_open()) {
        file << n << std::endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                file << matrix[i][j] << " ";
            }
            file << std::endl;
        }
        for (int i = 0; i < n; ++i) {
            file << vector[i] << std::endl;
        }
        file.close();
    }
}

void ReadAndPrint(const std::string& filename, NTL::mat_ZZ& matrix, NTL::vec_ZZ& vector) {
    std::ifstream file(filename);
    if (file.is_open()) {
        int n;
        file >> n;

        matrix.SetDims(n, n);
        vector.SetLength(n);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                file >> matrix[i][j];
            }
        }
        for (int i = 0; i < n; ++i) {
            file >> vector[i];
        }

        file.close();
    } else {
        std::cout << "Unable to open the file: " << filename << "\n";
    }
}
int main() {

	const int n = 1000;
    const std::string filename = "input.txt";

    // Generate and write the matrix and vector to the file.
    //GenerateAndWrite(n);

    // Read the matrix and vector from the file.
    NTL::mat_ZZ A;
    NTL::vec_ZZ b;
    ReadAndPrint(filename, A, b);

    // Create a vector to store the result
    NTL::vec_ZZ x;
    x.SetLength(n);
    
    // Initialize d
    NTL::ZZ d;

    // Start timing.
    auto start = std::chrono::high_resolution_clock::now();

    // Call the solve function
    NTL::solve(d, x, A, b);

    // Stop timing.
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration.
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Time taken by NTL::solve: " << duration << " microseconds" << std::endl;

    // Check if the system is solvable
    if (d != 0) {
        std::cout << "The system is solvable." << std::endl;
    } else {
        std::cout << "The system is not solvable." << std::endl;
    }

	return 0;
}