#include "pch.h"
#include "CppUnitTest.h"
#include "../PVP_SenoZaidimoPrototipas/GMHelper.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GMHelperTests
{
	TEST_CLASS(GMHelperTests)
	{
	public:

		TEST_METHOD(testFlagCount)
		{
			GMHelper GMH = GMHelper();
			GMH.AddFlag(3168);
			Assert::AreEqual(2, (int)GMH.GetMapTiles().size());
		}
	};
}