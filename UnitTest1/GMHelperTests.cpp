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

		TEST_METHOD(testTopFlagSprite)
		{
			GMHelper GMH = GMHelper();
			GMH.AddFlag(3168);
			Assert::AreEqual((float)257, GMH.GetMapTiles()[0]->GetSprite().GetCoords().GetX());
			Assert::AreEqual((float)8, GMH.GetMapTiles()[0]->GetSprite().GetCoords().GetY());
			Assert::AreEqual((float)20, GMH.GetMapTiles()[0]->GetSprite().GetX());
			Assert::AreEqual((float)89, GMH.GetMapTiles()[0]->GetSprite().GetY());
		}
	};
}