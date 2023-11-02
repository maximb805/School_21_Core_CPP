#ifndef __S21_MATRIX_OOP_H__
#define __S21_MATRIX_OOP_H__

#include <cmath>
#include <iostream>

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  int GetRows() const;
  int GetCols() const;
  void SetRows(const int rows);
  void SetCols(const int cols);

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  bool operator==(const S21Matrix& other);
  bool operator==(const S21Matrix& other) const;
  S21Matrix operator=(const S21Matrix& other);
  S21Matrix operator=(S21Matrix&& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(const double num);
  double& operator()(int rows, int cols);
  double operator()(int rows, int cols) const;

 private:
  int rows_, cols_;
  double** matrix_;
  const double EPS = 1e-7;
  void InitializeMatrix();
  void CopyMatrix(const S21Matrix& other);
  bool IsValid(const S21Matrix& matrix);
  void SumOrSubMatrix(const S21Matrix& other, int minus);
  void FillMinorMatrix(S21Matrix& minor, int row, int col);
  double CalcDeterminant();
  void SwapMatrices(S21Matrix& temp);
  void CopyResized(const S21Matrix& temp);
};

#endif /* __S21_MATRIX_OOP_H__ */
