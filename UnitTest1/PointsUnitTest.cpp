#include "CppUnitTest.h"
#include "../PVP_SenoZaidimoPrototipas/Points.h"
#include "../PVP_SenoZaidimoPrototipas/Vectors.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PointsUnitTest
{
	TEST_CLASS(PointsUnitTest)
	{
	public:


		TEST_METHOD(getPoints)
		{

			Points points(Vector2(0.5, 0.5), Vector2(1,1));
			Vector2 result = points.GetPosition();
			Assert::AreEqual(Vector2(0.5, 0.5), result);
		}


	};
}
