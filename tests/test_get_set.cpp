#include <gtest/gtest.h>

#include "Matrix_oop.h"

TEST(MatrixTest, SetGetRows) {
  Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;

  matrix.SetRows(3);
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 4.0);

  matrix.SetRows(1);
  EXPECT_EQ(matrix.GetRows(), 1);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);
}

TEST(MatrixTest, SetRowsThrow) {
  Matrix matrix;
  EXPECT_THROW(matrix.SetRows(-1), std::length_error);
}

TEST(MatrixTest, SetGetCols) {
  Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;

  matrix.SetCols(3);
  EXPECT_EQ(matrix.GetCols(), 3);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);

  matrix.SetCols(1);
  EXPECT_EQ(matrix.GetCols(), 1);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
}

TEST(MatrixTest, SetColsThrow) {
  Matrix matrix;
  EXPECT_THROW(matrix.SetCols(-1), std::length_error);
}