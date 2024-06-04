#include <map>
#include <vector>

namespace Data {
typedef std::vector<std::vector<int>> Matrix;
}

class Solver {
public:
  Solver(Data::Matrix matrix, std::vector<int> augments)
      : matrix(matrix), augments(augments) {
    ROWS = matrix.size();
    COLS = matrix[0].size();
  }

  std::vector<Data::Matrix> getPossibleInstances(
      std::map<int, std::pair<std::vector<int>, std::vector<int>>>
          &rowPermutations,
      std::vector<bool> avalibleRows) {
    bool emptyRows = false;
    for (const bool &avalibleRow : avalibleRows) {
      if (avalibleRow) {
        emptyRows = true;
        break;
      }
    }
    if (!emptyRows) {
      return;
    }

    std::vector<Data::Matrix> possibleInstances;
    for (const auto &data : rowPermutations) {
      int rowNumber = data.first;
      std::vector<int> rowData = data.second.first;
      std::vector<int> rowOptions = data.second.second;

      for (const int &row : rowOptions) {
        if (avalibleRows[row]) {
          avalibleRows[row] = 0;
          rowPermutations.erase(rowNumber);

          possibleInstances =
              getPossibleInstances(rowPermutations, avalibleRows);
        }
      }
    }
  }

  void orderMatrix() {
    std::map<int, std::pair<std::vector<int>, std::vector<int>>>
        rowPermutations;
    for (int r = 0; r < ROWS; r++) {
      std::vector<int> possibleRows;
      for (int c = 0; c < COLS; c++) {
        int n = matrix[r][c];
        if (n != 0) {
          possibleRows.push_back(r);
        }
      }
      rowPermutations[r] = std::make_pair(matrix[r], possibleRows);
    }
    std::vector<bool> avalibleRows = {1, 1, 1};
    std::vector<Data::Matrix> instances =
        getPossibleInstances(rowPermutations, avalibleRows);
  }

    void combineRow(int r1, std::pair<int, int> r2pos, Data::Matrix& matrix, std::vector<int>& augments) {
        double r1Multiplier = -r2pos.second / r1;
        for (int& c : matrix[r2pos.first]) {
            c+=matrix[r1][r2pos.second]* r1Multiplier;
        }
        augments[r2pos.first] += augments[r1]*r1Multiplier;
    }

  void rowEchelonSolverV1(Data::Matrix &matrix, std::vector<int> &augments) {
      for (int r=ROWS-2; r>= 0; r--) {
          if (matrix[r][0] != 0) {
              combineRow(0, std::make_pair(r, 0), matrix, augments);
          }
      }
      for (int c=0; c <=COLS-2; c++) {
          if (matrix[ROWS-1][c] != 0) {
              combineRow(0, std::make_pair(0, c), matrix, augments);
          }
      }
  }

      private : std::vector<std::vector<int>, int> matrix;
  std::vector<int> augments;
  int ROWS;
  int COLS;
};

int main() {
  std::vector<std::vector<int>> matrix1 = {{2, 5, 1}, {1, 1, 1}, {1, -6, -4}};
  std::vector<int> augments = {1, 6, 5};
}