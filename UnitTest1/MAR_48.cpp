
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
	};
}
