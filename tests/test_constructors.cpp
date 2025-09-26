#include <gtest/gtest.h>

#include "Matrix_oop.h"

TEST(MatrixTest, DefaultConstructor) {
  Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 0);
}

TEST(MatrixTest, ParameterizedConstructor) {
  Matrix matrix(3, 4);
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 4);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_DOUBLE_EQ(matrix(i, j), 0.0);
    }
  }
}

TEST(MatrixTest, ParameterizedConstructorThrow) {
  EXPECT_THROW(Matrix matrix(-3, 4), std::length_error);
  EXPECT_THROW(Matrix matrix(3, -4), std::length_error);
}

TEST(MatrixTest, CopyConstructor) {
  Matrix original(2, 2);
  original(0, 0) = 1.0;
  original(0, 1) = 2.0;
  original(1, 0) = 3.0;
  original(1, 1) = 4.0;

  Matrix copy(original);
  EXPECT_EQ(copy.GetRows(), 2);
  EXPECT_EQ(copy.GetCols(), 2);
  EXPECT_DOUBLE_EQ(copy(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(copy(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(copy(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(copy(1, 1), 4.0);

  copy(0, 0) = 99.0;
  EXPECT_DOUBLE_EQ(original(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(copy(0, 0), 99.0);
}

TEST(MatrixTest, MoveConstructor) {
  Matrix original(2, 2);
  original(0, 0) = 1.0;
  original(0, 1) = 2.0;

  Matrix moved(std::move(original));

  EXPECT_EQ(moved.GetRows(), 2);
  EXPECT_EQ(moved.GetCols(), 2);
  EXPECT_DOUBLE_EQ(moved(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(moved(0, 1), 2.0);

  EXPECT_EQ(original.GetRows(), 0);
  EXPECT_EQ(original.GetCols(), 0);
}