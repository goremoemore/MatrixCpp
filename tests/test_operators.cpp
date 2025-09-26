#include <gtest/gtest.h>

#include "Matrix_oop.h"

TEST(MatrixTest, AssignmentOperator) {
  Matrix original(2, 2);
  original(0, 0) = 1.0;
  original(0, 1) = 2.0;

  Matrix assigned;
  assigned = original;

  EXPECT_EQ(assigned.GetRows(), 2);
  EXPECT_EQ(assigned.GetCols(), 2);
  EXPECT_DOUBLE_EQ(assigned(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(assigned(0, 1), 2.0);
}

TEST(MatrixTest, AdditionOperator) {
  Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  Matrix B(2, 2);
  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 8.0;

  Matrix C = A + B;

  EXPECT_DOUBLE_EQ(C(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(C(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(C(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(C(1, 1), 12.0);

  A += B;
  EXPECT_DOUBLE_EQ(A(0, 0), 6.0);
}

TEST(MatrixTest, AdditionOperatorThrow) {
  Matrix A(2, 2);
  Matrix B(3, 3);

  EXPECT_THROW(A + B, std::logic_error);
}

TEST(MatrixTest, SubOperator) {
  Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  Matrix B(2, 2);
  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 8.0;

  Matrix C = A - B;

  EXPECT_DOUBLE_EQ(C(0, 0), -4.0);
  EXPECT_DOUBLE_EQ(C(0, 1), -4.0);
  EXPECT_DOUBLE_EQ(C(1, 0), -4.0);
  EXPECT_DOUBLE_EQ(C(1, 1), -4.0);

  A -= B;
  EXPECT_DOUBLE_EQ(A(0, 0), -4.0);
}

TEST(MatrixTest, SubOperatorThrow) {
  Matrix A(2, 2);
  Matrix B(3, 3);

  EXPECT_THROW(A - B, std::logic_error);
}

TEST(MatrixTest, MulNumber) {
  Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  Matrix C = A * 2;

  EXPECT_DOUBLE_EQ(C(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(C(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(C(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(C(1, 1), 8.0);

  A *= 2;
  EXPECT_DOUBLE_EQ(A(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(A(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(A(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 8.0);
}

TEST(MatrixTest, MulMatrixOk) {
  Matrix A(2, 2);
  A(0, 0) = 2.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  Matrix B(2, 2);
  B(0, 0) = 25.0;
  B(0, 1) = 2.0;
  B(1, 0) = 3.0;
  B(1, 1) = 4.0;

  A *= B;
  EXPECT_EQ(A(0, 0), 56.0);
}

TEST(MatrixTest, MulMatrixthrow) {
  Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  Matrix B(3, 3);

  EXPECT_THROW(A * B, std::logic_error);
}

TEST(MatrixTest, EqualityOperator) {
  Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;

  Matrix B(2, 2);
  B(0, 0) = 1.0;
  B(0, 1) = 2.0;

  Matrix C(2, 2);
  C(0, 0) = 1.0;
  C(0, 1) = 3.0;

  Matrix D(3, 2);

  EXPECT_TRUE(A == B);
  EXPECT_FALSE(A == C);
  EXPECT_FALSE(A == D);
}

TEST(MatrixTest, ParenthesisOperator) {
  Matrix matrix(2, 2);
  const Matrix matrix2(2, 2);
  matrix(0, 0) = 1.0;
  matrix(1, 1) = 2.0;

  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 2.0);

  EXPECT_THROW(matrix(5, 5), std::out_of_range);
  EXPECT_THROW(matrix2(5, 5), std::out_of_range);
}

TEST(MatrixTest, ParenthesisOperatorEmptyMatrix) {
  Matrix empty1(0, 0);
  EXPECT_THROW(empty1(0, 0), std::logic_error);

  Matrix empty2(0, 5);
  EXPECT_THROW(empty2(0, 0), std::logic_error);
  EXPECT_THROW(empty2(0, 2), std::logic_error);
  EXPECT_THROW(empty2(0, 4), std::logic_error);

  Matrix empty3(5, 0);
  EXPECT_THROW(empty3(0, 0), std::logic_error);
  EXPECT_THROW(empty3(2, 0), std::logic_error);
  EXPECT_THROW(empty3(4, 0), std::logic_error);
}

TEST(MatrixTest, ParenthesisOperatorConstEmptyMatrix) {
  const Matrix empty1(0, 0);
  EXPECT_THROW(empty1(0, 0), std::logic_error);

  const Matrix empty2(0, 5);
  EXPECT_THROW(empty2(0, 0), std::logic_error);

  const Matrix empty3(5, 0);
  EXPECT_THROW(empty3(0, 0), std::logic_error);
}