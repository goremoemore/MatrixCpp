#include "Matrix_oop.h"

Matrix::Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr){};

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 0 || cols < 0)
    throw std::length_error("Matrix size must be zero or positive");

  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  } 
}

Matrix::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double*[rows_];

  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < rows_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

Matrix::Matrix(Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.cols_ = 0;
  other.rows_ = 0;
}

Matrix::~Matrix() noexcept {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

int Matrix::GetRows() const noexcept { return rows_; }

int Matrix::GetCols() const noexcept { return cols_; }

void Matrix::SetRows(const int new_rows) {
  if (new_rows < 0) throw std::length_error("Rows must be zero or positive");

  if (new_rows != rows_) {
    Matrix temp(new_rows, cols_);

    int min_row = std::min(rows_, new_rows);

    for (int i = 0; i < min_row; ++i) {
      for (int j = 0; j < cols_; j++) {
        temp(i, j) = (*this)(i, j);
      }
    }

    *this = std::move(temp);
  }
}

void Matrix::SetCols(const int new_cols) {
  if (new_cols < 0) throw std::length_error("Cols must be zero or positive");

  if (new_cols != cols_) {
    Matrix temp(rows_, new_cols);

    int min_col = std::min(cols_, new_cols);

    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < min_col; j++) {
        temp(i, j) = (*this)(i, j);
      }
    }

    *this = std::move(temp);
  }
}

bool Matrix::EqMatrix(const Matrix& other) const {
  bool is_equal = true;

  if (rows_ != other.GetRows() || cols_ != other.GetCols())
    is_equal = false;
  else {
    for (int i = 0; i < rows_ && is_equal; ++i) {
      for (int j = 0; j < cols_ && is_equal; ++j) {
        if (std::abs((*this)(i, j) - other(i, j)) > 1e-7) is_equal = false;
      }
    }
  }

  return is_equal;
}

void Matrix::SumMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("Matrix sizes do not match");

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      (*this)(i, j) += other(i, j);
    }
  }
}

void Matrix::SubMatrix(const Matrix& other) {
  if (rows_ != other.GetRows() || cols_ != other.GetCols())
    throw std::logic_error("Matrix sizes do not match");

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      (*this)(i, j) -= other(i, j);
    }
  }
}

void Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      (*this)(i, j) *= num;
    }
  }
}

void Matrix::MulMatrix(const Matrix& other) {
  if (cols_ != other.GetRows()) {
    throw std::logic_error("Bad matrix size");
  }

  Matrix result{rows_, other.GetCols()};

  for (int i = 0; i < result.GetRows(); ++i) {
    for (int j = 0; j < result.GetCols(); ++j) {
      for (int k = 0; k < cols_; ++k) {
        result(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  *this = std::move(result);
}

Matrix Matrix::Transpose() const {
  Matrix result{cols_, rows_};

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result(j, i) = (*this)(i, j);
    }
  }

  return result;
}

Matrix Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::logic_error("Matrix must be square");
  }

  if (rows_ == 0) return Matrix(0, 0);
  if (rows_ == 1) return Matrix(1, 1);

  Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      Matrix minor(rows_ - 1, cols_ - 1);
      int minor_row = 0;
      for (int k = 0; k < rows_; ++k) {
        if (k == i) continue;
        int minor_col = 0;
        for (int l = 0; l < cols_; ++l) {
          if (l == j) continue;
          minor(minor_row, minor_col++) = (*this)(k, l);
        }
        minor_row++;
      }

      double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
      result(i, j) = sign * minor.Determinant();
    }
  }

  return result;
}

double Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::logic_error("Matrix must be square");
  }

  if (rows_ == 0) return 0.0;
  if (rows_ == 1) return (*this)(0, 0);
  if (rows_ == 2) {
    return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
  }

  double det = 0.0;
  for (int j = 0; j < cols_; ++j) {
    Matrix minor(rows_ - 1, cols_ - 1);
    for (int i = 1; i < rows_; ++i) {
      int minor_col = 0;
      for (int k = 0; k < cols_; ++k) {
        if (k == j) continue;
        minor(i - 1, minor_col++) = (*this)(i, k);
      }
    }

    double sign = (j % 2 == 0) ? 1.0 : -1.0;
    det += sign * (*this)(0, j) * minor.Determinant();
  }

  return det;
}

Matrix Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::logic_error("Matrix must be square");
  }

  double det = Determinant();
  if (std::abs(det) < 1e-7) {
    throw std::logic_error("Determinant is zero");
  }

  if (rows_ == 1) {
    Matrix inverse(1, 1);
    inverse(0, 0) = 1.0 / (*this)(0, 0);
    return inverse;
  }

  Matrix complements = CalcComplements();
  Matrix complements_t = complements.Transpose();

  Matrix inverse(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      inverse(i, j) = complements_t(i, j) / det;
    }
  }

  return inverse;
}

Matrix Matrix::operator+(const Matrix& other) const {
  Matrix temp{*this};
  temp.SumMatrix(other);
  return temp;
}

Matrix Matrix::operator-(const Matrix& other) const {
  Matrix temp{*this};
  temp.SubMatrix(other);
  return temp;
}

Matrix Matrix::operator*(const Matrix& other) const {
  Matrix temp{*this};
  temp.MulMatrix(other);
  return temp;
}

Matrix Matrix::operator*(const double number) const noexcept {
  Matrix temp{*this};
  temp.MulNumber(number);
  return temp;
}

bool Matrix::operator==(const Matrix& other) const {
  return EqMatrix(other);
}

Matrix& Matrix::operator=(const Matrix& other) {
  Matrix copy{other};
  *this = std::move(copy);
  return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
  return *this;
}

Matrix Matrix::operator+=(const Matrix& other) {
  SumMatrix(other);
  return (*this);
}

Matrix Matrix::operator-=(const Matrix& other) {
  SubMatrix(other);
  return (*this);
}

Matrix Matrix::operator*=(const Matrix& other) {
  MulMatrix(other);
  return (*this);
}

Matrix Matrix::operator*=(const double number) noexcept {
  MulNumber(number);
  return (*this);
}

double& Matrix::operator()(int row, int col) & {
  if (rows_ * cols_ == 0)
    throw std::logic_error("Matrix is empty. Cannot access to this element");

  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("index out of range");
  }

  return matrix_[row][col];
}

const double& Matrix::operator()(int row, int col) const& {
  if (rows_ * cols_ == 0)
    throw std::logic_error("Matrix is empty. Cannot access to this element");

  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("index out of range");
  }

  return matrix_[row][col];
}