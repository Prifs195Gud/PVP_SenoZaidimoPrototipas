
#include "CppUnitTest.h"
#include "../PVP_SenoZaidimoPrototipas/HUD.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:

		TEST_METHOD(laikoInicilizacija)
		{
			PlayerHUD* hud = new PlayerHUD();

			Assert::AreEqual(hud->GetTime(), 160);

			delete hud;
		}

		TEST_METHOD(laikoEjimas)
		{
			PlayerHUD* hud = new PlayerHUD();

			for (size_t i = 0; i < 60; i++)
				hud->Tick();

			Assert::AreEqual(hud->GetTime(), 159);

			delete hud;
		}
	};
}
