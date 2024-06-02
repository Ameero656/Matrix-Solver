#include <vector>

class Solver {
public:
    Solver(std::vector<std::vector<int>, int> matrix, std::vector<int> augments) : matrix(matrix), augments(augments) {
        ROWS = matrix.size();
        COLS = matrix[0].size();
    }

private:
    std::vector<std::vector<int>, int> matrix;
    std::vector<int> augments;
    int ROWS;
    int COLS;
};


int main() {
    std::vector<std::vector<int>> matrix1 = {
        {2, 5, 1},
        {1, 1, 1},
        {1, -6, -4}
    };
    std::vector<int> augments = {1, 6, 5};

}