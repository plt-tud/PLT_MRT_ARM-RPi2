/**
 * @file ComplexTests.cpp
 *
 * @brief test cases defining the interface and behavior of the class Complex
 *
 * @author uleon, leon.urbas@tu-dresden.de
 * @date   2016/04/04
 *
 */
#include "Complex.h"
#include "gtest/gtest.h"

namespace {
class ComplexTests : public ::testing::Test {
protected:
	const Complex c, j, d;
	Complex r;
	ComplexTests() : c(2,1), j(0,1), d(5), r() {}
};

TEST_F(ComplexTests, Initialization) {
	EXPECT_EQ(2, c.Re()) << "Initialize c(2,1)";
	EXPECT_EQ(1, c.Im()) << "Initialize c(2,1)";

	EXPECT_EQ(0, r.Re()) << "Initialize r()";
	EXPECT_EQ(0, r.Im()) << "Initialize r()";

	EXPECT_EQ(5, d.Re()) << "Initialize d(5)";
	EXPECT_EQ(0, d.Im()) << "Initialize d(5)";
}
TEST_F(ComplexTests, Multiplication) {
	r = j * j;
	EXPECT_EQ(-1, r.Re()) << "j * j";
	EXPECT_EQ(0, r.Im()) << "j * j";

	r = c * j;
	EXPECT_EQ(-1, r.Re()) << "c * j";
	EXPECT_EQ(2, r.Im()) << "c * j";

	r = c * c;
	EXPECT_EQ(3, r.Re()) << "c * c";
	EXPECT_EQ(4, r.Im()) << "c * c";

	r = c * 2;
	EXPECT_EQ(4, r.Re()) << "c * 2";
	EXPECT_EQ(2, r.Im()) << "c * 2";

	r = 2 * c;
	EXPECT_EQ(4, r.Re()) << "2 * c";
	EXPECT_EQ(2, r.Im()) << "2 * c";
}

TEST_F(ComplexTests, Addition) {
	r = c + c;
	EXPECT_EQ(4, r.Re()) << "c + c";
	EXPECT_EQ(2, r.Im()) << "c + c";

	r = c + j;
	EXPECT_EQ(2, r.Re()) << "c + j";
	EXPECT_EQ(2, r.Im()) << "c + j";
}

TEST_F(ComplexTests, Division) {
	r = c / j;
	EXPECT_EQ(1, r.Re()) << "c / j";
	EXPECT_EQ(-2, r.Im()) << "c / j";

	r = c / c;
	EXPECT_EQ(1, r.Re()) << "c / c";
	EXPECT_EQ(0, r.Im()) << "c / c";

	r = c / 2;
	EXPECT_EQ(2, r.Re()) << "c / 2";
	EXPECT_DOUBLE_EQ(0.5, r.Im()) << "c / 2";

	r = 1 / c;
	EXPECT_DOUBLE_EQ(0.4, r.Re()) << "1 / c";
	EXPECT_DOUBLE_EQ(0.2, r.Im()) << "1 / c";
}
} // end namespace
