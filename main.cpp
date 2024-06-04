#include <vector>
#include <map>

namespace Data {
    typedef std::vector<std::vector<int>, int> Matrix;
}

class Solver {
public:
    Solver(Data::Matrix matrix, std::vector<int> augments) : matrix(matrix), augments(augments) {
        ROWS = matrix.size();
        COLS = matrix[0].size();
    }

    std::vector<Data::Matrix> getPossibleInstances(std::map<int, std::pair<std::vector<int>, std::vector<int>>>& rowPermutations, std::vector<bool> avalibleRows) {
        bool emptyRows = false;
        for (const bool& avalibleRow : avalibleRows) {
            if (avalibleRow)  {
                emptyRows = true;
                break; 
            }
        }
        if (!emptyRows) {
            return;
        }


        std::vector<Data::Matrix> possibleInstances;
        for (const auto& data : rowPermutations) {
            int rowNumber = data.first;
            std::vector<int> rowData = data.second.first;
            std::vector<int> rowOptions = data.second.second;

            for (const int& row : rowOptions) {
                if (avalibleRows[row]) {
                    avalibleRows[row] = 0;
                    rowPermutations.erase(rowNumber);
                    
                    possibleInstances = getPossibleInstances(rowPermutations, avalibleRows);
                }
            }
        }
    }

    void orderMatrix() {
        std::map<int, std::pair<std::vector<int>, std::vector<int>>> rowPermutations; 
        for (int r=0; r<ROWS; r++) {
            std::vector<int> possibleRows;
            for (int c=0; c<COLS; c++) {
                int n = matrix[r][c];
                if (n != 0) {
                    possibleRows.push_back(r);
                }
            }
            rowPermutations[r] = std::make_pair(matrix[r], possibleRows);
        }
        std::vector<bool> avalibleRows = {1, 1, 1};
        std::vector<Data::Matrix> instances = getPossibleInstances(rowPermutations, avalibleRows);
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