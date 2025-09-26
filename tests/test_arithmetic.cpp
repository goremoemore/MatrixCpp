#include <gtest/gtest.h>

#include "Matrix_oop.h"

TEST(MatrixTest, Transpose) {
  Matrix A(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;

  Matrix B = A.Transpose();

  EXPECT_EQ(B.GetRows(), 3);
  EXPECT_EQ(B.GetCols(), 2);
  EXPECT_DOUBLE_EQ(B(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(B(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(B(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(B(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(B(2, 0), 3.0);
  EXPECT_DOUBLE_EQ(B(2, 1), 6.0);
}

TEST(MatrixTest, Determinant) {
  Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;
  A(2, 0) = 7;
  A(2, 1) = 8;
  A(2, 2) = 9;

  EXPECT_DOUBLE_EQ(A.Determinant(), 0.0);

  Matrix B(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;

  EXPECT_DOUBLE_EQ(B.Determinant(), -2.0);
}

TEST(MatrixTest, DeterminantThrow) {
  Matrix A(2, 3);
  EXPECT_THROW(A.Determinant(), std::logic_error);
}

TEST(MatrixTest, InverseMatrix) {
  Matrix A(2, 2);
  A(0, 0) = 4;
  A(0, 1) = 7;
  A(1, 0) = 2;
  A(1, 1) = 6;

  Matrix inv = A.InverseMatrix();

  Matrix identity = A * inv;

  EXPECT_NEAR(identity(0, 0), 1.0, 1e-10);
  EXPECT_NEAR(identity(0, 1), 0.0, 1e-10);
  EXPECT_NEAR(identity(1, 0), 0.0, 1e-10);
  EXPECT_NEAR(identity(1, 1), 1.0, 1e-10);
}

TEST(MatrixTest, InverseMatrix1x1) {
  Matrix A(1, 1);
  A(0, 0) = 4;

  Matrix inv = A.InverseMatrix();

  EXPECT_EQ(inv(0, 0), 0.25);
}

TEST(MatrixTest, InverseMatrixThrow) {
  Matrix A(2, 3);
  EXPECT_THROW(A.InverseMatrix(), std::logic_error);

  Matrix singular(2, 2);
  singular(0, 0) = 1;
  singular(0, 1) = 2;
  singular(1, 0) = 2;
  singular(1, 1) = 4;

  EXPECT_THROW(singular.InverseMatrix(), std::logic_error);
}

TEST(MatrixTest, CalcComplThrow) {
  Matrix A(2, 3);
  EXPECT_THROW(A.CalcComplements(), std::logic_error);
}