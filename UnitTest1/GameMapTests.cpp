#include "pch.h"
#include "CppUnitTest.h"
#include "../PVP_SenoZaidimoPrototipas/GameMap.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameMapTests
{
	TEST_CLASS(GameMapTests)
	{
	public:

		TEST_METHOD(testFlagCount)
		{
			GameMap GM = GameMap();
			GM.AddFlag(3168);
			Assert::AreEqual(2, (int)GM.GetMapTiles()->size());
		}

		TEST_METHOD(testCastleCount)
		{
			GameMap GM = GameMap();
			GM.AddCastle(3232);
			Assert::AreEqual(1, (int)GM.GetMapTiles()->size());
		}
	};
}