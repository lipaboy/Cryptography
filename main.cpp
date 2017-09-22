
//#define TEST_MODE

#ifdef TEST_MODE
#include <gtest/gtest.h>
#else
#include "main/CryptographyMath.h"
#endif

using namespace std;

int main(int argc, char *argv[])
{
#ifdef TEST_MODE
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
#else
	return CryptographyMath::mainCrypto(argc, argv);
#endif

}

