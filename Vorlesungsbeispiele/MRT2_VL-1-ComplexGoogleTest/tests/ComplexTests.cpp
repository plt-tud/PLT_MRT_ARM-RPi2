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
	EXPECT_EQ(3, r.Re());
	EXPECT_EQ(4, r.Im());

	r = c * 2;
	EXPECT_EQ(4, r.Re());
	EXPECT_EQ(2, r.Im());

	r = 2 * c;
	EXPECT_EQ(4, r.Re());
	EXPECT_EQ(2, r.Im());
}

TEST_F(ComplexTests, Addition) {
	r = c + c;
	EXPECT_EQ(4, r.Re());
	EXPECT_EQ(2, r.Im());

	r = c + j;
	EXPECT_EQ(2, r.Re());
	EXPECT_EQ(2, r.Im());
}

TEST_F(ComplexTests, Division) {
	r = c / j;
	EXPECT_EQ(1, r.Re());
	EXPECT_EQ(-2, r.Im());

	r = c / c;
	EXPECT_EQ(1, r.Re());
	EXPECT_EQ(0, r.Im());
}
} // end namespace
