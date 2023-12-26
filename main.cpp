#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Matrix {
private:
    std::vector<std::vector<int>> data;
    int rows, cols;

public:
    Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows, std::vector<int>(cols, 0)) {}

    // Set value at position (row, col)
    void setValue(int row, int col, int value) {
        data[row][col] = value;
    }

    // Get value at position (row, col)
    int getValue(int row, int col) const {
        return data[row][col];
    }

    // Get number of columns
    int getCols() const {
        return cols;
    }

    // Print matrix to console
    void printMatrix() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Write matrix to file
    void writeToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << rows << " " << cols << std::endl;
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    file << data[i][j] << " ";
                }
                file << std::endl;
            }
            file.close();
            std::cout << "Matrix written to file: " << filename << std::endl;
        } else {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }

    // Read matrix from file
    void readFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            file >> rows >> cols;
            data.resize(rows, std::vector<int>(cols, 0));
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    file >> data[i][j];
                }
            }
            file.close();
            std::cout << "Matrix read from file: " << filename << std::endl;
        } else {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }

    // Edit matrix elements interactively
    void editMatrix() {
        int row, col, value;
        std::cout << "Enter row and column indices to edit: ";
        std::cin >> row >> col;
        std::cout << "Enter new value: ";
        std::cin >> value;

        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            setValue(row, col, value);
            std::cout << "Value updated successfully." << std::endl;
        } else {
            std::cerr << "Invalid indices. Edit failed." << std::endl;
        }
    }

    // Find number of columns in A that occur more than once in B
    int findDuplicateColumns(const Matrix& B) const {
        int count = 0;
        for (int j = 0; j < cols; ++j) {
            std::vector<int> columnA, columnB;
            for (int i = 0; i < rows; ++i) {
                columnA.push_back(data[i][j]);
                columnB.push_back(B.getValue(i, j));
            }
            std::sort(columnA.begin(), columnA.end());
            std::sort(columnB.begin(), columnB.end());

            if (columnA == columnB) {
                count++;
            }
        }
        return count;
    }
};

// Function prototypes
void displayMenu();
void processMenuChoice(Matrix& A, Matrix& B, Matrix& C);

int main() {
    // Initialize matrices A, B, and C with dimensions
    int rows, cols;
    std::cout << "Enter number of rows and columns for matrices: ";
    std::cin >> rows >> cols;

    Matrix A(rows, cols);
    Matrix B(rows, cols);
    Matrix C(rows, cols);

    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice (0 to exit): ";
        std::cin >> choice;
        if (choice != 0) {
            processMenuChoice(A, B, C);
        }
    } while (choice != 0);

    return 0;
}

void displayMenu() {
    std::cout << "\n------ Menu ------" << std::endl;
    std::cout << "1. Input/Output for Matrix A" << std::endl;
    std::cout << "2. Input/Output for Matrix B" << std::endl;
    std::cout << "3. Input/Output for Matrix C" << std::endl;
    std::cout << "4. Edit Matrix A" << std::endl;
    std::cout << "5. Edit Matrix B" << std::endl;
    std::cout << "6. Edit Matrix C" << std::endl;
    std::cout << "7. Find Duplicate Columns in A and B" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

void processMenuChoice(Matrix& A, Matrix& B, Matrix& C) {
    int choice;
    std::cout << "\nEnter your choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            A.readFromFile("matrixA.txt");
            break;
        case 2:
            B.readFromFile("matrixB.txt");
            break;
        case 3:
            C.readFromFile("matrixC.txt");
            break;
        case 4:
            A.editMatrix();
            break;
        case 5:
            B.editMatrix();
            break;
        case 6:
            C.editMatrix();
            break;
        case 7:
            int duplicateColumns = A.findDuplicateColumns(B);
            std::cout << "Number of columns in A occurring more than once in B: " << duplicateColumns << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
    }
}
