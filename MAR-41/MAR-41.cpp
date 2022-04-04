#include "CppUnitTest.h"
#include "../PVP_SenoZaidimoPrototipas/Rendering.h"
#include "../PVP_SenoZaidimoPrototipas/Vectors.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MAR41
{
	TEST_CLASS(MAR41)
	{
	public:
		
		TEST_METHOD(TestGetDesktopResolution)
		{
			Rendering renderer = Rendering();
			Vector2 resolution = renderer.GetDesktopResolution();
			Assert::AreEqual(resolution, Vector2(1920, 1080));
		}

		TEST_METHOD(TestGetMaxRenderScale)
		{
			Rendering renderer = Rendering();
			Vector2 renderScale = renderer.GetMaxRenderScale();
			Assert::AreEqual(renderScale, Vector2(4, 4));
		}
	};
}
