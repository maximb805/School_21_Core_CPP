#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

TEST(MatrixTest, Constructor1Test) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
  EXPECT_EQ(matrix(0, 0), 0.0);
  EXPECT_EQ(matrix(0, 1), 0.0);
  EXPECT_EQ(matrix(0, 2), 0.0);
  EXPECT_EQ(matrix(1, 0), 0.0);
  EXPECT_EQ(matrix(1, 1), 0.0);
  EXPECT_EQ(matrix(1, 2), 0.0);
  EXPECT_EQ(matrix(0, 0), 0.0);
  EXPECT_EQ(matrix(0, 1), 0.0);
  EXPECT_EQ(matrix(0, 2), 0.0);
}

TEST(MatrixTest, Constructor2Test) {
  S21Matrix matrix(2, 3);
  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 3);
  EXPECT_EQ(matrix(0, 0), 0.0);
  EXPECT_EQ(matrix(0, 1), 0.0);
  EXPECT_EQ(matrix(1, 0), 0.0);
  EXPECT_EQ(matrix(1, 1), 0.0);
  EXPECT_EQ(matrix(0, 0), 0.0);
  EXPECT_EQ(matrix(0, 1), 0.0);
}

TEST(MatrixTest, Constructor2TestException1) {
  EXPECT_THROW(S21Matrix matrix(0, 3), std::invalid_argument);
}

TEST(MatrixTest, Constructor2TestException2) {
  EXPECT_THROW(S21Matrix matrix(3, 0), std::invalid_argument);
}

TEST(MatrixTest, Constructor2TestException3) {
  EXPECT_THROW(S21Matrix matrix(-2, 0), std::invalid_argument);
}

TEST(MatrixTest, Constructor3Test) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  S21Matrix matrix1(matrix);
  EXPECT_EQ(matrix1.GetRows(), 3);
  EXPECT_EQ(matrix1.GetCols(), 2);
  EXPECT_EQ(matrix1(0, 0), 1.0);
  EXPECT_EQ(matrix1(0, 1), 2.0);
  EXPECT_EQ(matrix1(1, 0), 4.0);
  EXPECT_EQ(matrix1(1, 1), 5.0);
  EXPECT_EQ(matrix1(2, 0), 7.0);
  EXPECT_EQ(matrix1(2, 1), 8.0);
}

TEST(MatrixTest, Constructor3TestException) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  S21Matrix tmp(std::move(matrix));  // sets matrix.matrix_ = null
  EXPECT_THROW(S21Matrix matrix1(matrix), std::runtime_error);
}

TEST(MatrixTest, Constructor4Test) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  S21Matrix matrix1(std::move(matrix));
  EXPECT_EQ(matrix1.GetRows(), 3);
  EXPECT_EQ(matrix1.GetCols(), 2);
  EXPECT_EQ(matrix1(0, 0), 1.0);
  EXPECT_EQ(matrix1(0, 1), 2.0);
  EXPECT_EQ(matrix1(1, 0), 4.0);
  EXPECT_EQ(matrix1(1, 1), 5.0);
  EXPECT_EQ(matrix1(2, 0), 7.0);
  EXPECT_EQ(matrix1(2, 1), 8.0);
  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 0);
}

TEST(MatrixTest, EqMatrixTest1) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  S21Matrix matrix1(matrix);
  EXPECT_EQ(matrix1.EqMatrix(matrix1), true);
}

TEST(MatrixTest, EqMatrixTest2) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8;

  EXPECT_EQ(matrix.EqMatrix(matrix1), false);
}

TEST(MatrixTest, EqMatrixTest3) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8.000002;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8.000001;

  EXPECT_EQ(matrix.EqMatrix(matrix1), false);
}

TEST(MatrixTest, EqMatrixTest4) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8.00000001;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8.00000002;

  EXPECT_EQ(matrix.EqMatrix(matrix1), true);
}

TEST(MatrixTest, EqMatrixTest5) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;

  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8;

  EXPECT_EQ(matrix.EqMatrix(matrix1), false);
}

TEST(MatrixTest, EqMatrixTest6) {
  S21Matrix matrix;
  S21Matrix matrix1;
  S21Matrix temp(std::move(matrix));
  EXPECT_EQ(matrix.EqMatrix(matrix1), false);
}

TEST(MatrixTest, EqMatrixTest7) {
  S21Matrix matrix;
  S21Matrix matrix1;
  S21Matrix temp(std::move(matrix1));
  EXPECT_EQ(matrix.EqMatrix(matrix1), false);
}

TEST(MatrixTest, EqMatrixTest8) {
  S21Matrix matrix;
  S21Matrix matrix1;
  S21Matrix temp(std::move(matrix));
  S21Matrix temp1(std::move(matrix1));
  EXPECT_EQ(matrix.EqMatrix(matrix1), true);
}

TEST(MatrixTest, SumMatrixTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 21;
  matrix1(0, 1) = -242;
  matrix1(1, 0) = 10;
  matrix1(1, 1) = 0.5;
  matrix1(2, 0) = 73.25;
  matrix1(2, 1) = 8;

  matrix.SumMatrix(matrix1);

  matrix1(0, 0) = 26.2;
  matrix1(0, 1) = -236;
  matrix1(1, 0) = 7.6;
  matrix1(1, 1) = 45.5;
  matrix1(2, 0) = 197.55;
  matrix1(2, 1) = -16115;
  EXPECT_EQ(matrix.EqMatrix(matrix1), true);
}

TEST(MatrixTest, SumMatrixTestException1) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 21;
  matrix1(0, 1) = -242;
  matrix1(1, 0) = 10;
  matrix1(1, 1) = 0.5;
  matrix1(2, 0) = 73.25;
  matrix1(2, 1) = 8;

  EXPECT_THROW(matrix.SumMatrix(matrix1), std::logic_error);
}

TEST(MatrixTest, SumMatrixTestException2) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix matrix1(3, 2);
  S21Matrix temp(std::move(matrix1));
  EXPECT_THROW(matrix.SumMatrix(matrix1), std::runtime_error);
}

TEST(MatrixTest, SumMatrixTestException3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix matrix1(3, 2);
  S21Matrix temp(std::move(matrix1));
  EXPECT_THROW(matrix1.SumMatrix(matrix), std::runtime_error);
}

TEST(MatrixTest, SubMatrixTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 21;
  matrix1(0, 1) = -242;
  matrix1(1, 0) = 10;
  matrix1(1, 1) = 0.5;
  matrix1(2, 0) = 73.25;
  matrix1(2, 1) = 8;

  matrix.SubMatrix(matrix1);

  matrix1(0, 0) = 5.2 - 21;
  matrix1(0, 1) = 6 + 242;
  matrix1(1, 0) = -2.4 - 10;
  matrix1(1, 1) = 45 - 0.5;
  matrix1(2, 0) = 124.3 - 73.25;
  matrix1(2, 1) = -16123 - 8;
  EXPECT_EQ(matrix.EqMatrix(matrix1), true);
}

TEST(MatrixTest, MulNumberTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  matrix.MulNumber(5.2);

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 5.2 * 5.2;
  matrix1(0, 1) = 6 * 5.2;
  matrix1(1, 0) = -2.4 * 5.2;
  matrix1(1, 1) = 45 * 5.2;
  matrix1(2, 0) = 124.3 * 5.2;
  matrix1(2, 1) = -16123 * 5.2;
  EXPECT_EQ(matrix.EqMatrix(matrix1), true);
}

TEST(MatrixTest, MulNumberTestException) {
  S21Matrix matrix(3, 2);
  S21Matrix test(std::move(matrix));
  EXPECT_THROW(matrix.MulNumber(5.2), std::runtime_error);
}

TEST(MatrixTest, MulMatrixTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 21;
  matrix1(0, 1) = -242;
  matrix1(0, 2) = 10;
  matrix1(1, 0) = 0.5;
  matrix1(1, 1) = 73.25;
  matrix1(1, 2) = 8;

  matrix.MulMatrix(matrix1);

  S21Matrix expected(3, 3);
  expected(0, 0) = 112.2;
  expected(0, 1) = -818.9;
  expected(0, 2) = 100;
  expected(1, 0) = -27.9;
  expected(1, 1) = 3877.05;
  expected(1, 2) = 336;
  expected(2, 0) = -5451.2;
  expected(2, 1) = -1211090.35;
  expected(2, 2) = -127741;
  EXPECT_EQ(matrix.EqMatrix(expected), true);
}

TEST(MatrixTest, MulMatrixTestException1) {
  S21Matrix matrix(3, 2);
  S21Matrix matrix1(2, 3);
  S21Matrix test(std::move(matrix));
  EXPECT_THROW(matrix.MulMatrix(matrix1), std::runtime_error);
}

TEST(MatrixTest, MulMatrixTestException2) {
  S21Matrix matrix(3, 2);
  S21Matrix matrix1(2, 3);
  S21Matrix test(std::move(matrix1));
  EXPECT_THROW(matrix.MulMatrix(matrix1), std::runtime_error);
}

TEST(MatrixTest, MulMatrixTestException3) {
  S21Matrix matrix(3, 2);
  S21Matrix matrix1(3, 3);
  EXPECT_THROW(matrix.MulMatrix(matrix1), std::invalid_argument);
}

TEST(MatrixTest, TransposeTest1) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(0, 2) = -2.4;
  matrix(1, 0) = 45;
  matrix(1, 1) = 124.3;
  matrix(1, 2) = -16123;
  matrix(2, 0) = 0.5;
  matrix(2, 1) = 73.25;
  matrix(2, 2) = 8;

  S21Matrix matrix1 = matrix.Transpose();

  S21Matrix expected(3, 3);
  expected(0, 0) = 5.2;
  expected(0, 1) = 45;
  expected(0, 2) = 0.5;
  expected(1, 0) = 6;
  expected(1, 1) = 124.3;
  expected(1, 2) = 73.25;
  expected(2, 0) = -2.4;
  expected(2, 1) = -16123;
  expected(2, 2) = 8;

  EXPECT_EQ(matrix1.EqMatrix(expected), true);
}

TEST(MatrixTest, TransposeTest2) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = 45;
  matrix(1, 1) = 124.3;
  matrix(2, 0) = 0.5;
  matrix(2, 1) = 73.25;

  S21Matrix matrix1 = matrix.Transpose();

  S21Matrix expected(2, 3);
  expected(0, 0) = 5.2;
  expected(0, 1) = 45;
  expected(0, 2) = 0.5;
  expected(1, 0) = 6;
  expected(1, 1) = 124.3;
  expected(1, 2) = 73.25;

  EXPECT_EQ(matrix1.EqMatrix(expected), true);
}

TEST(MatrixTest, TransposeTest3) {
  S21Matrix matrix(1, 3);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(0, 2) = -2.4;

  S21Matrix matrix1 = matrix.Transpose();

  S21Matrix expected(3, 1);
  expected(0, 0) = 5.2;
  expected(1, 0) = 6;
  expected(2, 0) = -2.4;

  EXPECT_EQ(matrix1.EqMatrix(expected), true);
}

TEST(MatrixTest, TransposeTestException) {
  S21Matrix matrix;
  S21Matrix temp(std::move(matrix));
  EXPECT_THROW(matrix.Transpose(), std::runtime_error);
}

TEST(MatrixTest, CalcComplementsTest1) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(0, 2) = -2.4;
  matrix(1, 0) = 45;
  matrix(1, 1) = 124.3;
  matrix(1, 2) = -16123;
  matrix(2, 0) = 0.5;
  matrix(2, 1) = 73.25;
  matrix(2, 2) = 8;

  S21Matrix matrix1 = matrix.CalcComplements();

  S21Matrix expected(3, 3);
  expected(0, 0) = 1182004.15;
  expected(0, 1) = -8421.5;
  expected(0, 2) = 3234.1;
  expected(1, 0) = -223.8;
  expected(1, 1) = 42.8;
  expected(1, 2) = -377.9;
  expected(2, 0) = -96439.68;
  expected(2, 1) = 83731.6;
  expected(2, 2) = 376.36;

  EXPECT_EQ(matrix1.EqMatrix(expected), true);
}

TEST(MatrixTest, CalcComplementsTest2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 6;

  S21Matrix matrix1 = matrix.CalcComplements();

  S21Matrix expected(2, 2);
  expected(0, 0) = 6;
  expected(0, 1) = -3;
  expected(1, 0) = -2;
  expected(1, 1) = 1;

  EXPECT_EQ(matrix1.EqMatrix(expected), true);
}

TEST(MatrixTest, CalcComplementsTestException1) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 6;
  EXPECT_THROW(matrix.CalcComplements(), std::logic_error);
}

TEST(MatrixTest, CalcComplementsTestException2) {
  S21Matrix matrix(2, 2);
  S21Matrix temp(std::move(matrix));
  EXPECT_THROW(matrix.CalcComplements(), std::runtime_error);
}

TEST(MatrixTest, DeterminantTest1) {
  double result;
  double expected_result = 0;
  S21Matrix matrix(5, 5);
  int counter = 0;
  for (int i = 0; i < matrix.GetRows(); i++) {
    for (int j = 0; j < matrix.GetCols(); j++) {
      counter++;
      matrix(i, j) = counter * 1.2;
    }
  }
  result = matrix.Determinant();
  EXPECT_TRUE(fabs(result - expected_result) < 1e-7);
}

TEST(MatrixTest, DeterminantTest2) {
  double result;
  double expected_result = -82978775.55372475;
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 127.0;
  matrix(0, 1) = 2476.7;
  matrix(0, 2) = 845.673;
  matrix(1, 0) = -161.67;
  matrix(1, 1) = 516.23;
  matrix(1, 2) = -1.341;
  matrix(2, 0) = 0;
  matrix(2, 1) = 651.225;
  matrix(2, 2) = 12.76;
  result = matrix.Determinant();
  EXPECT_TRUE(fabs(result - expected_result) < 1e-7);
}

TEST(MatrixTest, DeterminantTestException1) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 6;
  EXPECT_THROW(matrix.Determinant(), std::logic_error);
}

TEST(MatrixTest, DeterminantTestException2) {
  S21Matrix matrix(2, 2);
  S21Matrix temp(std::move(matrix));
  EXPECT_THROW(matrix.Determinant(), std::runtime_error);
}

TEST(MatrixTest, InverseTest1) {
  S21Matrix matrix1(3, 3);
  S21Matrix expected_result(3, 3);

  matrix1(0, 0) = 0.73;
  matrix1(0, 1) = -0.19;
  matrix1(0, 2) = -0.12;
  matrix1(1, 0) = -0.07;
  matrix1(1, 1) = 0.72;
  matrix1(1, 2) = -0.17;
  matrix1(2, 0) = -0.12;
  matrix1(2, 1) = -0.15;
  matrix1(2, 2) = -0.92;

  expected_result(0, 0) = 1.3610058662;
  expected_result(0, 1) = 0.3102278236;
  expected_result(0, 2) = -0.2348472108;
  expected_result(1, 0) = 0.0870537260;
  expected_result(1, 1) = 1.3572467281;
  expected_result(1, 2) = -0.2621504249;
  expected_result(2, 0) = -0.1917160466;
  expected_result(2, 1) = -0.2617547261;
  expected_result(2, 2) = -1.0135823597;

  S21Matrix result = matrix1.InverseMatrix();
  EXPECT_TRUE(result.EqMatrix(expected_result));
}

TEST(MatrixTest, InverseTest2) {
  S21Matrix matrix1(3, 3);
  S21Matrix expected_result(3, 3);

  matrix1(0, 0) = 2;
  matrix1(0, 1) = 5;
  matrix1(0, 2) = 7;
  matrix1(1, 0) = 6;
  matrix1(1, 1) = 3;
  matrix1(1, 2) = 4;
  matrix1(2, 0) = 5;
  matrix1(2, 1) = -2;
  matrix1(2, 2) = -3;

  expected_result(0, 0) = 1;
  expected_result(0, 1) = -1;
  expected_result(0, 2) = 1;
  expected_result(1, 0) = -38;
  expected_result(1, 1) = 41;
  expected_result(1, 2) = -34;
  expected_result(2, 0) = 27;
  expected_result(2, 1) = -29;
  expected_result(2, 2) = 24;

  S21Matrix result = matrix1.InverseMatrix();
  EXPECT_TRUE(result.EqMatrix(expected_result));
}

TEST(MatrixTest, InverseTest3) {
  S21Matrix matrix1(2, 2);
  S21Matrix expected_result(2, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 0;
  matrix1(1, 1) = 4;

  expected_result(0, 0) = 1;
  expected_result(0, 1) = -0.5;
  expected_result(1, 0) = 0;
  expected_result(1, 1) = 0.25;

  S21Matrix result = matrix1.InverseMatrix();
  EXPECT_TRUE(result.EqMatrix(expected_result));
}

TEST(MatrixTest, InverseTest4) {
  S21Matrix matrix1(1, 1);
  S21Matrix expected_result(1, 1);
  matrix1(0, 0) = -8;
  expected_result(0, 0) = -1 / 8.0;
  S21Matrix result = matrix1.InverseMatrix();
  EXPECT_TRUE(result.EqMatrix(expected_result));
}

TEST(MatrixTest, InverseTestException1) {
  S21Matrix matrix1(3, 4);
  EXPECT_THROW(matrix1.InverseMatrix(), std::logic_error);
}

TEST(MatrixTest, InverseTestException2) {
  S21Matrix matrix1;
  S21Matrix temp(std::move(matrix1));
  EXPECT_THROW(matrix1.InverseMatrix(), std::runtime_error);
}

TEST(MatrixTest, InverseTestException3) {
  S21Matrix matrix1(4, 4);
  EXPECT_THROW(matrix1.InverseMatrix(), std::logic_error);
}

TEST(MatrixTest, InverseTestException4) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 2;
  matrix1(1, 1) = 4;
  EXPECT_THROW(matrix1.InverseMatrix(), std::logic_error);
}

TEST(MatrixTest, InverseTestException5) {
  S21Matrix matrix1(1, 1);
  matrix1(0, 0) = 0;
  EXPECT_THROW(matrix1.InverseMatrix(), std::logic_error);
}

TEST(MatrixTest, SetterTest1) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 2;
  matrix1(1, 1) = 4;

  matrix1.SetCols(5);

  S21Matrix expected_result(2, 5);
  expected_result(0, 0) = 1;
  expected_result(0, 1) = 2;
  expected_result(0, 2) = 0;
  expected_result(0, 3) = 0;
  expected_result(0, 4) = 0;
  expected_result(1, 0) = 2;
  expected_result(1, 1) = 4;
  expected_result(0, 2) = 0;
  expected_result(0, 3) = 0;
  expected_result(0, 4) = 0;

  EXPECT_TRUE(matrix1.EqMatrix(expected_result));
}

TEST(MatrixTest, SetterTest2) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 2;
  matrix1(1, 1) = 4;

  matrix1.SetRows(5);

  S21Matrix expected_result(5, 2);
  expected_result(0, 0) = 1;
  expected_result(0, 1) = 2;
  expected_result(1, 0) = 2;
  expected_result(1, 1) = 4;
  expected_result(2, 0) = 0;
  expected_result(2, 1) = 0;
  expected_result(3, 0) = 0;
  expected_result(3, 1) = 0;
  expected_result(4, 0) = 0;
  expected_result(4, 1) = 0;

  EXPECT_TRUE(matrix1.EqMatrix(expected_result));
}

TEST(MatrixTest, SetterTest3) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8;
  matrix1(2, 2) = 9;

  matrix1.SetRows(1);

  S21Matrix expected_result(1, 3);
  expected_result(0, 0) = 1;
  expected_result(0, 1) = 2;
  expected_result(0, 2) = 3;

  EXPECT_TRUE(matrix1.EqMatrix(expected_result));
}

TEST(MatrixTest, SetterTest4) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8;
  matrix1(2, 2) = 9;

  matrix1.SetCols(2);

  S21Matrix expected_result(3, 2);
  expected_result(0, 0) = 1;
  expected_result(0, 1) = 2;
  expected_result(1, 0) = 4;
  expected_result(1, 1) = 5;
  expected_result(2, 0) = 7;
  expected_result(2, 1) = 8;

  EXPECT_TRUE(matrix1.EqMatrix(expected_result));
}

TEST(MatrixTest, SetterTestException1) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 2;
  matrix1(1, 1) = 4;

  EXPECT_THROW(matrix1.SetRows(0), std::invalid_argument);
}

TEST(MatrixTest, SetterTestException2) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 2;
  matrix1(1, 1) = 4;

  EXPECT_THROW(matrix1.SetCols(-5), std::invalid_argument);
}

TEST(MatrixTest, BracketTestException1) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix(2, 1), std::invalid_argument);
}

TEST(MatrixTest, BracketTestException2) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix(-1, 1), std::invalid_argument);
}

TEST(MatrixTest, BracketTestException3) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix(1, 2), std::invalid_argument);
}

TEST(MatrixTest, BracketTestException4) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix(1, -1), std::invalid_argument);
}

TEST(MatrixTest, BracketTestConst) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 2;
  matrix(1, 1) = 4;

  const S21Matrix matrix1(matrix);
  EXPECT_TRUE(matrix1(0, 0) == 1);
  EXPECT_TRUE(matrix1(0, 1) == 2);
  EXPECT_TRUE(matrix1(1, 0) == 2);
  EXPECT_TRUE(matrix1(1, 1) == 4);
}

TEST(MatrixTest, BracketTestConstException) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 2;
  matrix(1, 1) = 4;

  const S21Matrix matrix1(matrix);
  EXPECT_THROW(matrix1(1, -1), std::invalid_argument);
}

TEST(MatrixTest, PlusOperatorTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 21;
  matrix1(0, 1) = -242;
  matrix1(1, 0) = 10;
  matrix1(1, 1) = 0.5;
  matrix1(2, 0) = 73.25;
  matrix1(2, 1) = 8;

  S21Matrix expected(3, 2);
  expected(0, 0) = 26.2;
  expected(0, 1) = -236;
  expected(1, 0) = 7.6;
  expected(1, 1) = 45.5;
  expected(2, 0) = 197.55;
  expected(2, 1) = -16115;
  EXPECT_EQ(expected.EqMatrix(matrix + matrix1), true);
  EXPECT_EQ(expected.EqMatrix(matrix), false);
}

TEST(MatrixTest, PlusOperatorConstTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 21;
  matrix1(0, 1) = -242;
  matrix1(1, 0) = 10;
  matrix1(1, 1) = 0.5;
  matrix1(2, 0) = 73.25;
  matrix1(2, 1) = 8;

  const S21Matrix matrixConst(matrix);

  S21Matrix expected(3, 2);
  expected(0, 0) = 26.2;
  expected(0, 1) = -236;
  expected(1, 0) = 7.6;
  expected(1, 1) = 45.5;
  expected(2, 0) = 197.55;
  expected(2, 1) = -16115;
  EXPECT_EQ(expected.EqMatrix(matrixConst + matrix1), true);
  EXPECT_EQ(expected.EqMatrix(matrixConst), false);
}

TEST(MatrixTest, MinusOperatorTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 21;
  matrix1(0, 1) = -242;
  matrix1(1, 0) = 10;
  matrix1(1, 1) = 0.5;
  matrix1(2, 0) = 73.25;
  matrix1(2, 1) = 8;

  S21Matrix expected(3, 2);
  expected(0, 0) = 5.2 - 21;
  expected(0, 1) = 6 + 242;
  expected(1, 0) = -2.4 - 10;
  expected(1, 1) = 45 - 0.5;
  expected(2, 0) = 124.3 - 73.25;
  expected(2, 1) = -16123 - 8;
  EXPECT_EQ(expected.EqMatrix(matrix - matrix1), true);
  EXPECT_EQ(expected.EqMatrix(matrix), false);
}

TEST(MatrixTest, MinusOperatorConstTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 21;
  matrix1(0, 1) = -242;
  matrix1(1, 0) = 10;
  matrix1(1, 1) = 0.5;
  matrix1(2, 0) = 73.25;
  matrix1(2, 1) = 8;

  const S21Matrix matrixConst(matrix);

  S21Matrix expected(3, 2);
  expected(0, 0) = 5.2 - 21;
  expected(0, 1) = 6 + 242;
  expected(1, 0) = -2.4 - 10;
  expected(1, 1) = 45 - 0.5;
  expected(2, 0) = 124.3 - 73.25;
  expected(2, 1) = -16123 - 8;
  EXPECT_EQ(expected.EqMatrix(matrixConst - matrix1), true);
  EXPECT_EQ(expected.EqMatrix(matrixConst), false);
}

TEST(MatrixTest, MulOperatorTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 21;
  matrix1(0, 1) = -242;
  matrix1(0, 2) = 10;
  matrix1(1, 0) = 0.5;
  matrix1(1, 1) = 73.25;
  matrix1(1, 2) = 8;

  S21Matrix expected(3, 3);
  expected(0, 0) = 112.2;
  expected(0, 1) = -818.9;
  expected(0, 2) = 100;
  expected(1, 0) = -27.9;
  expected(1, 1) = 3877.05;
  expected(1, 2) = 336;
  expected(2, 0) = -5451.2;
  expected(2, 1) = -1211090.35;
  expected(2, 2) = -127741;
  EXPECT_EQ(expected.EqMatrix(matrix * matrix1), true);
  EXPECT_EQ(expected.EqMatrix(matrix), false);
}

TEST(MatrixTest, MulOperatorConstTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 21;
  matrix1(0, 1) = -242;
  matrix1(0, 2) = 10;
  matrix1(1, 0) = 0.5;
  matrix1(1, 1) = 73.25;
  matrix1(1, 2) = 8;

  const S21Matrix matrixConst(matrix);

  S21Matrix expected(3, 3);
  expected(0, 0) = 112.2;
  expected(0, 1) = -818.9;
  expected(0, 2) = 100;
  expected(1, 0) = -27.9;
  expected(1, 1) = 3877.05;
  expected(1, 2) = 336;
  expected(2, 0) = -5451.2;
  expected(2, 1) = -1211090.35;
  expected(2, 2) = -127741;
  EXPECT_EQ(expected.EqMatrix(matrixConst * matrix1), true);
  EXPECT_EQ(expected.EqMatrix(matrixConst), false);
}

TEST(MatrixTest, MulNumOperatorTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix expected(3, 2);
  expected(0, 0) = 5.2 * 5.2;
  expected(0, 1) = 6 * 5.2;
  expected(1, 0) = -2.4 * 5.2;
  expected(1, 1) = 45 * 5.2;
  expected(2, 0) = 124.3 * 5.2;
  expected(2, 1) = -16123 * 5.2;
  EXPECT_EQ(expected.EqMatrix(matrix * 5.2), true);
  EXPECT_EQ(expected.EqMatrix(matrix), false);
}

TEST(MatrixTest, MulNumOperatorConstTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  const S21Matrix matrixConst(matrix);

  S21Matrix expected(3, 2);
  expected(0, 0) = 5.2 * 5.2;
  expected(0, 1) = 6 * 5.2;
  expected(1, 0) = -2.4 * 5.2;
  expected(1, 1) = 45 * 5.2;
  expected(2, 0) = 124.3 * 5.2;
  expected(2, 1) = -16123 * 5.2;
  EXPECT_EQ(expected.EqMatrix(matrixConst * 5.2), true);
  EXPECT_EQ(expected.EqMatrix(matrixConst), false);
}

TEST(MatrixTest, EqOperatorTest1) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8.00000001;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8.00000002;

  EXPECT_EQ(matrix == matrix1, true);
}

TEST(MatrixTest, EqOperatorConstTest1) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8.00000001;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8.00000002;

  const S21Matrix matrixConst(matrix);
  const S21Matrix matrix1Const(matrix1);

  EXPECT_EQ(matrixConst == matrix1Const, true);
}

TEST(MatrixTest, EqOperatorTest2) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 6;
  matrix(1, 1) = 5;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8.00000001;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8.00000002;

  EXPECT_EQ(matrix == matrix1, false);
}

TEST(MatrixTest, EqOperatorConstTest2) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 6;
  matrix(1, 1) = 5;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8.00000001;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8.00000002;

  const S21Matrix matrixConst(matrix);
  const S21Matrix matrix1Const(matrix1);

  EXPECT_EQ(matrixConst == matrix1Const, false);
}

TEST(MatrixTest, PlusAndAssignOperatorTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 21;
  matrix1(0, 1) = -242;
  matrix1(1, 0) = 10;
  matrix1(1, 1) = 0.5;
  matrix1(2, 0) = 73.25;
  matrix1(2, 1) = 8;

  matrix += matrix1;

  matrix1(0, 0) = 26.2;
  matrix1(0, 1) = -236;
  matrix1(1, 0) = 7.6;
  matrix1(1, 1) = 45.5;
  matrix1(2, 0) = 197.55;
  matrix1(2, 1) = -16115;
  EXPECT_EQ(matrix.EqMatrix(matrix1), true);
}

TEST(MatrixTest, MinusAndAssignOperatorTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 21;
  matrix1(0, 1) = -242;
  matrix1(1, 0) = 10;
  matrix1(1, 1) = 0.5;
  matrix1(2, 0) = 73.25;
  matrix1(2, 1) = 8;

  matrix -= matrix1;

  matrix1(0, 0) = 5.2 - 21;
  matrix1(0, 1) = 6 + 242;
  matrix1(1, 0) = -2.4 - 10;
  matrix1(1, 1) = 45 - 0.5;
  matrix1(2, 0) = 124.3 - 73.25;
  matrix1(2, 1) = -16123 - 8;
  EXPECT_EQ(matrix.EqMatrix(matrix1), true);
}

TEST(MatrixTest, MulAndAssignOperatorTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 21;
  matrix1(0, 1) = -242;
  matrix1(0, 2) = 10;
  matrix1(1, 0) = 0.5;
  matrix1(1, 1) = 73.25;
  matrix1(1, 2) = 8;

  matrix *= matrix1;

  S21Matrix expected(3, 3);
  expected(0, 0) = 112.2;
  expected(0, 1) = -818.9;
  expected(0, 2) = 100;
  expected(1, 0) = -27.9;
  expected(1, 1) = 3877.05;
  expected(1, 2) = 336;
  expected(2, 0) = -5451.2;
  expected(2, 1) = -1211090.35;
  expected(2, 2) = -127741;
  EXPECT_EQ(matrix.EqMatrix(expected), true);
}

TEST(MatrixTest, MulNumAndAssignOperatorTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  matrix *= 5.2;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 5.2 * 5.2;
  matrix1(0, 1) = 6 * 5.2;
  matrix1(1, 0) = -2.4 * 5.2;
  matrix1(1, 1) = 45 * 5.2;
  matrix1(2, 0) = 124.3 * 5.2;
  matrix1(2, 1) = -16123 * 5.2;
  EXPECT_EQ(matrix.EqMatrix(matrix1), true);
}

TEST(MatrixTest, AssignOperatorTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix matrix1(5, 5);

  matrix1 = matrix;

  EXPECT_EQ(matrix.EqMatrix(matrix1), true);
}

TEST(MatrixTest, AssignRvalueOperatorTest) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 5.2;
  matrix(0, 1) = 6;
  matrix(1, 0) = -2.4;
  matrix(1, 1) = 45;
  matrix(2, 0) = 124.3;
  matrix(2, 1) = -16123;

  S21Matrix matrix1(5, 5);

  matrix1 = std::move(matrix);

  S21Matrix expected(3, 2);
  expected(0, 0) = 5.2;
  expected(0, 1) = 6;
  expected(1, 0) = -2.4;
  expected(1, 1) = 45;
  expected(2, 0) = 124.3;
  expected(2, 1) = -16123;

  EXPECT_EQ(expected.EqMatrix(matrix1), true);
}

int main() {
  testing::InitGoogleTest();
  if (RUN_ALL_TESTS()) {
    std::cout << "Tests failed\n";
  }
  return 0;
}
