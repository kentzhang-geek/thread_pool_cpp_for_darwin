#include "gtest/gtest.h"
#include <iostream>

TEST(aa, 001) {
	;
}

int main(int argc, char ** argv) {
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}
