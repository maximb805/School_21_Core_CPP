#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(3), cols_(3), matrix_(nullptr) {
  InitializeMatrix();
}

S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (rows > 0 && cols > 0) {
    InitializeMatrix();
  } else {
    throw std::invalid_argument("Rows and cols could not be less than 1");
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(nullptr) {
  if (this != &other) {
    if (other.matrix_) {
      InitializeMatrix();
      CopyMatrix(other);
    } else {
      throw std::runtime_error("Source matrix is null");
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    delete[] matrix_[0];
    delete[] matrix_;
  }
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

void S21Matrix::InitializeMatrix() {
  matrix_ = new double*[rows_]();
  matrix_[0] = new double[rows_ * cols_]();
  for (int i = 1; i < rows_; i++) {
    matrix_[i] = matrix_[0] + i * cols_;
  }
}

void S21Matrix::CopyMatrix(const S21Matrix& other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool result;
  if (other.matrix_ && matrix_) {
    if (other.rows_ == rows_ && other.cols_ == cols_) {
      result = true;
      for (int i = 0; i < rows_ && result; i++) {
        for (int j = 0; j < cols_ && result; j++) {
          if (fabs(fabs(matrix_[i][j]) - fabs(other.matrix_[i][j])) >= EPS ||
              matrix_[i][j] != matrix_[i][j] ||
              other.matrix_[i][j] != other.matrix_[i][j]) {
            result = false;
          }
        }
      }
    } else {
      result = false;
    }
  } else {
    result = matrix_ == other.matrix_;
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) { SumOrSubMatrix(other, 1); }

void S21Matrix::SubMatrix(const S21Matrix& other) { SumOrSubMatrix(other, -1); }

void S21Matrix::SumOrSubMatrix(const S21Matrix& other, int minus) {
  if (matrix_ && other.matrix_) {
    if (rows_ == other.rows_ && cols_ == other.cols_) {
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
          matrix_[i][j] = matrix_[i][j] + (other.matrix_[i][j] * minus);
        }
      }
    } else {
      throw std::invalid_argument("Matrix sizes are not equal");
    }
  } else {
    throw std::runtime_error("This or other matrix is null");
  }
}

void S21Matrix::MulNumber(const double num) {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = matrix_[i][j] * num;
      }
    }
  } else {
    throw std::runtime_error("Matrix is null");
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (matrix_ && other.matrix_) {
    if (cols_ == other.rows_) {
      S21Matrix temp(rows_, other.cols_);
      for (int i = 0; i < temp.rows_; i++) {
        for (int j = 0; j < temp.cols_; j++) {
          for (int k = 0; k < cols_; k++) {
            temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
          }
        }
      }
      SwapMatrices(temp);
    } else {
      throw std::invalid_argument(
          "This matrix cols number is not equal other matrix rows number");
    }
  } else {
    throw std::runtime_error("This or other matrix is null");
  }
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(const int rows) {
  if (rows != rows_) {
    S21Matrix temp(rows, cols_);
    CopyResized(temp);
    SwapMatrices(temp);
  }
}

void S21Matrix::SetCols(const int cols) {
  if (cols != cols_) {
    S21Matrix temp(rows_, cols);
    CopyResized(temp);
    SwapMatrices(temp);
  }
}

void S21Matrix::SwapMatrices(S21Matrix& temp) {
  std::swap(rows_, temp.rows_);
  std::swap(cols_, temp.cols_);
  std::swap(matrix_, temp.matrix_);
}

void S21Matrix::CopyResized(const S21Matrix& temp) {
  for (int i = 0; i < temp.rows_; i++) {
    for (int j = 0; j < temp.cols_; j++) {
      if (i < rows_ && j < cols_) {
        temp.matrix_[i][j] = matrix_[i][j];
      } else {
        temp.matrix_[i][j] = 0.0;
      }
    }
  }
}

S21Matrix S21Matrix::Transpose() {
  if (matrix_) {
    S21Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        result.matrix_[j][i] = matrix_[i][j];
      }
    }
    return result;
  } else {
    throw std::runtime_error("Matrix is null");
  }
}

S21Matrix S21Matrix::CalcComplements() {
  if (matrix_) {
    if (rows_ == cols_) {
      S21Matrix result(rows_, cols_);
      if (result.rows_ == 1) {
        result.matrix_[0][0] = matrix_[0][0] ? 1.0 : 0.0;
      } else {
        S21Matrix temp(result.rows_ - 1, result.cols_ - 1);
        int sign = 1;
        for (int i = 0; i < result.rows_; i++) {
          sign = i % 2 ? -1 : 1;
          for (int j = 0; j < result.cols_; j++) {
            FillMinorMatrix(temp, i, j);
            double det = temp.Determinant();
            result.matrix_[i][j] = det * sign;
            sign *= -1;
          }
        }
      }
      return result;
    } else {
      throw std::logic_error("Cols number is not equal rows number");
    }
  } else {
    throw std::runtime_error("Matrix is null");
  }
}

double S21Matrix::Determinant() {
  if (matrix_) {
    double result = 0;
    if (rows_ == cols_) {
      if (rows_ == 1) {
        result = matrix_[0][0];
      } else {
        result = CalcDeterminant();
      }
      return result;
    } else {
      throw std::logic_error("Cols number is not equal rows number");
    }
  } else {
    throw std::runtime_error("Matrix is null");
  }
}

double S21Matrix::CalcDeterminant() {
  double result = 0;
  if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    S21Matrix temp(rows_ - 1, cols_ - 1);
    int sign = 1;
    for (int col = 0; col < cols_; col++) {
      FillMinorMatrix(temp, 0, col);
      result += matrix_[0][col] * temp.CalcDeterminant() * sign;
      sign *= -1;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (matrix_) {
    double det = Determinant();
    if (det != 0) {
      S21Matrix trans = Transpose();
      S21Matrix comp = trans.CalcComplements();
      comp.MulNumber(1.0 / det);
      return comp;
    } else {
      throw std::logic_error("Determinant is 0");
    }
  } else {
    throw std::runtime_error("Matrix is null");
  }
}

void S21Matrix::FillMinorMatrix(S21Matrix& minor, int row, int col) {
  int minor_row = 0;
  for (int i = 0; i < rows_; i++) {
    int minor_col = 0;
    if (i != row) {
      for (int j = 0; j < cols_; j++) {
        if (j != col) {
          minor.matrix_[minor_row][minor_col] = matrix_[i][j];
          minor_col++;
        }
      }
      minor_row++;
    }
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix temp(*this);
  temp.SumMatrix(other);
  return temp;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix temp(*this);
  temp.SubMatrix(other);
  return temp;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix temp(*this);
  temp.MulMatrix(other);
  return temp;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix temp(*this);
  temp.MulNumber(num);
  return temp;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

bool S21Matrix::operator==(const S21Matrix& other) const {
  S21Matrix temp(*this);
  return temp.EqMatrix(other);
}

S21Matrix S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    S21Matrix temp(std::move(other));
    SwapMatrices(temp);
  }
  return *this;
}

S21Matrix S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    this->~S21Matrix();
    SwapMatrices(other);
  }
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(int rows, int cols) {
  if (rows < 0 || cols < 0 || rows >= rows_ || cols >= cols_) {
    throw std::invalid_argument("Index is out of range");
  } else {
    return matrix_[rows][cols];
  }
}

double S21Matrix::operator()(int rows, int cols) const {
  if (rows < 0 || cols < 0 || rows >= rows_ || cols >= cols_) {
    throw std::invalid_argument("Index is out of range");
  } else {
    return matrix_[rows][cols];
  }
}
