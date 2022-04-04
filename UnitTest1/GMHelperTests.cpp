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

		TEST_METHOD(testTopFlagPosition)
		{
			GMHelper GMH = GMHelper();
			GMH.AddFlag(3168);
			Assert::AreEqual((float)3168 + 2, GMH.GetMapTiles()[0]->GetPosition().GetX());
			Assert::AreEqual((float)83.5, GMH.GetMapTiles()[0]->GetPosition().GetY());
		}

		TEST_METHOD(testCastleCount)
		{
			GMHelper GMH = GMHelper();
			GMH.AddCastle(3232);
			Assert::AreEqual(1, (int)GMH.GetMapTiles().size());
		}

		TEST_METHOD(testCastleSprite)
		{
			GMHelper GMH = GMHelper();
			GMH.AddCastle(3232);
			Assert::AreEqual((float)177, GMH.GetMapTiles()[0]->GetSprite().GetCoords().GetX());
			Assert::AreEqual((float)8, GMH.GetMapTiles()[0]->GetSprite().GetCoords().GetY());
			Assert::AreEqual((float)80, GMH.GetMapTiles()[0]->GetSprite().GetX());
			Assert::AreEqual((float)80, GMH.GetMapTiles()[0]->GetSprite().GetY());
		}
	};
}