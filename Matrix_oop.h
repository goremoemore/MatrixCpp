#ifndef SRC_MATRIX_OOP_H
#define SRC_MATRIX_OOP_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

class Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  Matrix() noexcept;
  explicit Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other) noexcept;
  ~Matrix() noexcept;

  Matrix operator+(const Matrix& other) const;
  Matrix operator-(const Matrix& other) const;
  Matrix operator*(const Matrix& other) const;
  Matrix operator*(const double number) const noexcept;
  bool operator==(const Matrix& other) const;
  Matrix& operator=(const Matrix& other);
  Matrix& operator=(Matrix&& other) noexcept;
  Matrix operator+=(const Matrix& other);
  Matrix operator-=(const Matrix& other);
  Matrix operator*=(const Matrix& other);
  Matrix operator*=(const double number) noexcept;
  double& operator()(int row, int col) &;
  const double& operator()(int row, int col) const&;

  bool EqMatrix(const Matrix& other) const;
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const Matrix& other);
  Matrix Transpose() const;
  Matrix CalcComplements() const;
  double Determinant() const;
  Matrix InverseMatrix() const;

  int GetCols() const noexcept;
  int GetRows() const noexcept;
  void SetRows(const int new_rows);
  void SetCols(const int new_cols);
};

#endif